cmake_minimum_required(VERSION 3.10)
project(PubSubDemo)

set(CMAKE_CXX_STANDARD 11)

# 添加源文件
set(SOURCES
    main.cpp
    Broker.cpp
    Publisher.cpp
    Subscriber.cpp
)

add_executable(pubsub_demo ${SOURCES})
