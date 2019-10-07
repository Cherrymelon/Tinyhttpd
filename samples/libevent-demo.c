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

int main() {
    struct event_base* base;
    struct event_config* config = event_config_new();
    event_config_set_flag(config, EV_FEATURE_ET);

    base = event_base_new_with_config(config);

    base = event_base_new();


}