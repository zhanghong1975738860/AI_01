// Publisher.h
#pragma once
#include <string>
#include "Broker.h"

class Publisher {
public:
    Publisher(const std::string& name);
    void publish(Broker& broker, const std::string& topic, const std::string& message);

private:
    std::string name;
};
