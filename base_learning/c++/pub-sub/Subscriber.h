// Subscriber.h
#pragma once
#include <string>
#include "Broker.h"

class Subscriber {
public:
    Subscriber(const std::string& name);
    void subscribeTo(Broker& broker, const std::string& topic);

private:
    std::string name;
};
