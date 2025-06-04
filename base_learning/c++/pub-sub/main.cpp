#include "Broker.h"
#include "Publisher.h"
#include "Subscriber.h"

int main() {
    Broker broker;

    Subscriber sub1("订阅者1");
    sub1.subscribeTo(broker, "MessageA");

    Publisher pub1("发布者1");
    pub1.publish(broker, "MessageA", "你好，这是消息A");

    return 0;
}
