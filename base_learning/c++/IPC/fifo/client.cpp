#include <iostream>
#include <fstream>
#include <unistd.h>
#include "common.h"

int main() {
    // 等待管道文件就绪
    sleep(1);  // 防止 server 还没启动时访问失败

    std::ofstream out(FIFO_C2S);
    std::ifstream in(FIFO_S2C);

    std::string input;
    std::cout << "[Client] 输入内容，输入 'exit' 退出:\n";

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        if (input == "exit") break;

        out << input << std::endl;
        out.flush();

        std::string response;
        std::getline(in, response);
        std::cout << "[Client 收到] " << response << std::endl;
    }

    return 0;
}
