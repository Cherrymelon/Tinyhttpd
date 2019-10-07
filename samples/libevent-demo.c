//
// Created by 付旭炜 on 2019/10/7.
//

/* For sockaddr_in */
#include <netinet/in.h>
/* For socket functions */
#include <sys/socket.h>
/* For fcntl */
#include <fcntl.h>

#include <event2/event.h>

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

const int BUF_SIZE = 50;
char buf[BUF_SIZE];

void cb_sigint(evutil_socket_t fd, short what, void *arg) {
    perror("received sigint\n");
    exit(1);
}

void cb_func(evutil_socket_t fd, short what, void *arg)
{
    const char *data = arg;

    int readed = read(fd, buf, BUF_SIZE);
    if (readed == 0) {
        printf("read finished\n");
    } else if (readed == -1 && errno == EAGAIN) {
        buf[0] = '\0';
        printf("RAGAIN\n");
    } else if (readed == -1) {
        return;
    }
    printf("Got an event on socket %d:%s%s%s%s [%s] - buf %s\n",
           (int) fd,
           (what&EV_TIMEOUT) ? " timeout" : "",
           (what&EV_READ)    ? " read" : "",
           (what&EV_WRITE)   ? " write" : "",
           (what&EV_SIGNAL)  ? " signal" : "",
           data, buf);

}

void run_base_with_ticks(struct event_base *base)
{
    struct timeval ten_sec;

    ten_sec.tv_sec = 10;
    ten_sec.tv_usec = 0;

    /* The caller has already set up fd1, fd2 somehow, and make them
   nonblocking. */
    struct event *ev1, *ev2;
    struct event *evs1;

    evutil_make_socket_nonblocking(STDIN_FILENO);
//    evutil_make_socket_nonblocking(STDOUT_FILENO);

//    ev1 = event_new(base, STDIN_FILENO, EV_TIMEOUT|EV_READ|EV_PERSIST, cb_func,
//                    (char*)"Reading event");
    ev1 = event_new(base, STDIN_FILENO, EV_READ|EV_PERSIST, cb_func,
                    (char*)"Reading event");
    evs1 = evsignal_new(base, SIGINT, cb_sigint, NULL);
//    ev2 = event_new(base, STDOUT_FILENO, EV_WRITE|EV_PERSIST, cb_func,
//                    (char*)"Writing event");

    event_add(ev1, &ten_sec);
    evsignal_add(evs1, NULL);
//    event_add(ev2, NULL);

    /* Now we run the event_base for a series of 10-second intervals, printing
       "Tick" after each.  For a much better way to implement a 10-second
       timer, see the section below about persistent timer events. */
    while (1) {
        /* This schedules an exit ten seconds from now. */
        event_base_loopexit(base, &ten_sec);

        event_base_dispatch(base);
        puts("Tick");
    }
}

int main() {
    struct event_base* base;
    struct event_config* config = event_config_new();
    event_config_set_flag(config, EV_FEATURE_ET);

    base = event_base_new_with_config(config);

    base = event_base_new();

    run_base_with_ticks(base);
}