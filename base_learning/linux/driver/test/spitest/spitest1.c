#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/spi/spidev.h>
#include <string.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <stdint.h>

#define SPI_DEV "/dev/spidev6.0"
#define SPI_MODE SPI_MODE_0
#define SPI_BITS_PER_WORD 8
#define SPI_SPEED 30000000  // 1MHz

int main() {
    int fd;
    int choice;
    int ret;

    fd = open(SPI_DEV, O_RDWR);
    if (fd < 0) {
        perror("Failed to open SPI device");
        return 1;
    }

    // 设置 SPI 模式、位宽和速率
    uint8_t mode = SPI_MODE;
    uint8_t bits = SPI_BITS_PER_WORD;
    uint32_t speed = SPI_SPEED;

    ioctl(fd, SPI_IOC_WR_MODE, &mode);
    ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);

    printf("SPI device opened: %s\n", SPI_DEV);
    printf("1. Read\n2. Write\nChoose (1 or 2): ");
    scanf("%d", &choice);
    getchar(); // 读掉换行符

    if (choice == 1) {
        // SPI read (dummy write)
        uint8_t tx[32] = {0x00};  // 发送空数据读取
        uint8_t rx[32] = {0};

        struct spi_ioc_transfer tr = {
            .tx_buf = (unsigned long)tx,
            .rx_buf = (unsigned long)rx,
            .len = sizeof(tx),
            .speed_hz = speed,
            .bits_per_word = bits,
        };

        ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
        if (ret < 1) {
            perror("SPI read failed");
        } else {
            printf("SPI read (%d bytes):", ret);
            for (int i = 0; i < ret; i++)
                printf(" %02x", rx[i]);
            printf("\n");
        }
    } else if (choice == 2) {
        // SPI write
        char input[32] = {0};
        printf("Input data to write (max 31 chars): ");
        fgets(input, sizeof(input), stdin);

        size_t len = strnlen(input, sizeof(input));
        if (input[len - 1] == '\n') input[len - 1] = '\0';

        struct spi_ioc_transfer tr = {
            .tx_buf = (unsigned long)input,
            .rx_buf = 0,
            .len = strlen(input),
            .speed_hz = speed,
            .bits_per_word = bits,
        };

        ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
        if (ret < 1) {
            perror("SPI write failed");
        } else {
            printf("SPI write success: \"%s\"\n", input);
        }
    } else {
        printf("Invalid choice.\n");
    }

    close(fd);
    printf("SPI device closed.\n");
    return 0;
}

