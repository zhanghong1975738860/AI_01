// Subscriber.cpp
#include "Subscriber.h"
#include <iostream>

Subscriber::Subscriber(const std::string& name) : name(name) {}

void Subscriber::subscribeTo(Broker& broker, const std::string& topic) {
    broker.subscribe(topic, [this](const std::string& msg) {
        std::cout << "订阅者 [" << name << "] 收到消息: " << msg << std::endl;
    });
}
