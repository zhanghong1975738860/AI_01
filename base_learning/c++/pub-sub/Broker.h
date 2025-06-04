// Broker.h
#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>

class Broker {
public:
    using Callback = std::function<void(const std::string&)>;

    void subscribe(const std::string& topic, Callback cb);
    void publish(const std::string& topic, const std::string& message);

private:
    std::unordered_map<std::string, std::vector<Callback>> subscribers;
};
