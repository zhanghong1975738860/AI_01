// ====== include/Message.h ======
#pragma once
#include <cstring>

struct Message {
    char sender;                // 'A' or 'B'
    char data[256];             // message content

    Message() : sender('A') {
        memset(data, 0, sizeof(data));
    }

    Message(char s, const char* d) : sender(s) {
        strncpy(data, d, sizeof(data) - 1);
        data[sizeof(data) - 1] = '\0';
    }
};
