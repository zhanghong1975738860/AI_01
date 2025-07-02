// ====== src/client.cpp ======
#include "Message.h"
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <sys/stat.h>

const char* A2S = "/tmp/pipe_A2S";
const char* S2A = "/tmp/pipe_S2A";
const char* B2S = "/tmp/pipe_B2S";
const char* S2B = "/tmp/pipe_S2B";

void receive_loop(const char* recv_pipe, char client) {
    int fd = open(recv_pipe, O_RDONLY);
    Message msg;
    while (read(fd, &msg, sizeof(msg)) > 0) {
        std::cout << "[" << client << "] From " << msg.sender << ": " << msg.data << std::endl;
    }
    close(fd);
}

int main(int argc, char* argv[]) {
    if (argc != 2 || (argv[1][0] != 'A' && argv[1][0] != 'B')) {
        std::cerr << "Usage: ./client A|B" << std::endl;
        return 1;
    }

    char self = argv[1][0];
    const char* send_pipe = (self == 'A') ? A2S : B2S;
    const char* recv_pipe = (self == 'A') ? S2A : S2B;

    int fd_send = open(send_pipe, O_WRONLY);
    std::thread t(receive_loop, recv_pipe, self);

    std::string line;
    while (std::getline(std::cin, line)) {
        Message msg(self, line.c_str());
        write(fd_send, &msg, sizeof(msg));
    }

    close(fd_send);
    t.join();
    return 0;
}
