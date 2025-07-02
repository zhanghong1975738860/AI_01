// ====== src/server.cpp ======
#include "Message.h"
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <sys/stat.h>

const char* A2S = "/tmp/pipe_A2S";
const char* S2A = "/tmp/pipe_S2A";
const char* B2S = "/tmp/pipe_B2S";
const char* S2B = "/tmp/pipe_S2B";

int main() {
    mkfifo(A2S, 0666); mkfifo(S2A, 0666);
    mkfifo(B2S, 0666); mkfifo(S2B, 0666);

    int fd_a2s = open(A2S, O_RDONLY);
    int fd_b2s = open(B2S, O_RDONLY);
    int fd_s2a = open(S2A, O_WRONLY);
    int fd_s2b = open(S2B, O_WRONLY);

    fd_set readfds;
    Message msg;
    while (true) {
        FD_ZERO(&readfds);
        FD_SET(fd_a2s, &readfds);
        FD_SET(fd_b2s, &readfds);

        int maxfd = std::max(fd_a2s, fd_b2s) + 1;
        int ret = select(maxfd, &readfds, nullptr, nullptr, nullptr);
        if (ret > 0) {
            if (FD_ISSET(fd_a2s, &readfds)) {
                if (read(fd_a2s, &msg, sizeof(msg)) > 0) {
                    write(fd_s2b, &msg, sizeof(msg));
                    std::cout << "[S] A->B: " << msg.data << std::endl;
                }
            }
            if (FD_ISSET(fd_b2s, &readfds)) {
                if (read(fd_b2s, &msg, sizeof(msg)) > 0) {
                    write(fd_s2a, &msg, sizeof(msg));
                    std::cout << "[S] B->A: " << msg.data << std::endl;
                }
            }
        }
    }

    close(fd_a2s); close(fd_b2s); close(fd_s2a); close(fd_s2b);
    unlink(A2S); unlink(B2S); unlink(S2A); unlink(S2B);
    return 0;
}
