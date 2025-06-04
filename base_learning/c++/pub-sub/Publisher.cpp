// Publisher.cpp
#include "Publisher.h"
#include <iostream>

Publisher::Publisher(const std::string& name) : name(name) {}

void Publisher::publish(Broker& broker, const std::string& topic, const std::string& message) {
    std::cout << "发布者 [" << name << "] 发布消息: " << message << std::endl;
    broker.publish(topic, message);
}
