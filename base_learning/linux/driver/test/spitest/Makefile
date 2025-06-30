#common linux

#编译工具配置
#CC := $(AC_PROG_CC)
#AR := $(AM_PROG_AR)


SYSROOT=LE.UM.7.4.1/build-qti-distro-tele-debug/tmp-glibc/work/sa525m-oe-linux/loc-qwes-iface/git-r1/recipe-sysroot/

CC := LE.UM.7.4.1/build-qti-distro-tele-debug/tmp-glibc/work/sa525m-oe-linux/loc-qwes-iface/git-r1/recipe-sysroot-native/usr/bin/aarch64-oe-linux/aarch64-oe-linux-gcc --sysroot=$(SYSROOT)
AR := LE.UM.7.4.1/build-qti-distro-tele-debug/tmp-glibc/work/sa525m-oe-linux/loc-qwes-iface/git-r1/recipe-sysroot-native/usr/bin/aarch64-oe-linux/aarch674-oe-linux-ar

####################################################################
#编译选项配置
# 编译参数
CFLAGS := -Wall -Wextra -O2 --sysroot=$(SYSROOT)
LDFLAGS := 

# 输出文件
TARGET := spitest

# 源文件
SRC := spitest.c

# 默认目标
all: $(TARGET)

# 编译规则
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

# 清理规则
clean:
	rm -f $(TARGET)

# 静默编译（可选）
.PHONY: all clean

 

 




