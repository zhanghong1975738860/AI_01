#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include "common.h"

int main() {
    // 创建命名管道（只需创建一次）
    mkfifo(FIFO_C2S, 0666);
    mkfifo(FIFO_S2C, 0666);

    std::cout << "[Server] 等待客户端消息...\n";

    std::ifstream in(FIFO_C2S);
    std::ofstream out(FIFO_S2C);

    std::string msg;
    while (std::getline(in, msg)) {
        std::cout << "[Server 收到] " << msg << std::endl;

        std::string response = "服务端回复: 收到 response [" + msg + "]";
        out << response << std::endl;
        out.flush();
    }

    return 0;
}
