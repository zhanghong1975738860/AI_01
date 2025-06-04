发布者（Publisher）
负责“发布消息”。
不关心消息是被谁接收、接收多少人，只管发送。
示例：一个传感器程序发布温度数据。

订阅者（Subscriber）
负责“接收消息”。
只关心自己订阅的内容，不关心谁发的，也不管有几个发布者。
示例：一个日志程序订阅了“温度事件”。

中介/消息代理（Broker）
负责“管理订阅关系”和“消息分发”。
订阅者向它注册要监听的消息；发布者向它发布消息。
示例：Redis、RabbitMQ、ROS Master、MQTT broker、EventBus 等。






         +---------------+          +-------------------+
         |   Publisher   |          |     Subscriber    |
         +---------------+          +-------------------+
                |                            ↑
                |        publish(topic)      |
                +-------------------------->|
                |                            |
                v                            |
         +-----------------------------+     |
         |     Message Broker (中介)    |-----+
         +-----------------------------+



订阅者向 Broker 注册：“我订阅了 topic A”
发布者发布 topic A 的消息
Broker 接收消息并推送给所有订阅 topic A 的订阅者


################################
编译

mkdir build
cd build
cmake ..
make
./pubsub_demo

输出
发布者 [发布者1] 发布消息: 你好，这是消息A
订阅者 [订阅者1] 收到消息: 你好，这是消息A

#################################
编译报错
CMake Error at CMakeLists.txt:2 (project):
  No CMAKE_CXX_COMPILER could be found.

apt install build-essential