// Broker.cpp
#include "Broker.h"

void Broker::subscribe(const std::string& topic, Callback cb) {
    subscribers[topic].push_back(cb);
}

void Broker::publish(const std::string& topic, const std::string& message) {
    auto it = subscribers.find(topic);
    if (it != subscribers.end()) {
        for (auto& cb : it->second) {
            cb(message);
        }
    }
}
