cmake_minimum_required(VERSION 3.12)
find_library(LIBEVENT2_CORE event_core)

add_executable(select-rot13-serv select-rot13-server.c)
add_executable(select-serv select.c)
add_executable(libevent-rot13 libevent-rot13-server.c)

target_link_libraries(libevent-rot13 ${LIBEVENT2_CORE})

add_executable(libevent-demo libevent-demo.c)

target_link_libraries(libevent-demo ${LIBEVENT2_CORE})

add_executable(libevent-bufevent-demo libevent_bufferevent_demo.c)
target_link_libraries(libevent-bufevent-demo ${LIBEVENT2_CORE})

add_executable(libevent-evbuffer-demo libevent_evbuffer_demo.c)
target_link_libraries(libevent-evbuffer-demo ${LIBEVENT2_CORE})

#add_custom_target(format
#        COMMAND clang-format --style=file -i ${ALL_SOURCE_FILES} )