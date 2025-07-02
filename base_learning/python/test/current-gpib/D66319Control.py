import time

import pyvisa


class D66319Control(object):

    d66319 = None

    def __init__(self, GPIB_Addr: str, visa_dll='c:/Windows/System32/visa32.dll'):
        """
        安捷伦66319D电源控制模块
        by 郭子祥
        @param GPIB_Addr: 仪器visa地址
        @param visa_dll: visa.all地址
        """
        try:
            self.rm = pyvisa.ResourceManager(visa_dll)
            print(self.rm.list_resources())
            self.d66319 = self.rm.open_resource(GPIB_Addr)
        except Exception as e:
            print(e)
            exit(-1)

    @staticmethod
    def sacn_ports():
        """
        扫描GPIB端口
        """
        rm = pyvisa.ResourceManager()
        print(rm.list_resources())

    def __command_write(self, write_cmd):
        """
        命令写入
        @param write_cmd: 写入指令
        @return: 执行结果
        """
        ret_res = None
        try:
            ret_res = self.d66319.write(write_cmd)
        except Exception as e:
            print(e)
        return ret_res

    def __command_read(self, read_cmd):
        """
        命令读取
        @param read_cmd: 读取指令
        @return: 读取信息
        """
        ret_res = None
        try:
            ret_res = self.d66319.read(read_cmd)
        except Exception as e:
            print(e)
        return ret_res

    def __command_query(self, query_cmd):
        """
        命令查询
        @param query_cmd: 查询指令
        @return: 查询信息
        """
        ret_res = None
        try:
            ret_res = self.d66319.query(query_cmd)
        except Exception as e:
            print(e)
        return ret_res

    def open_output_1(self) -> bool:
        """
        打开电源1号输出口
        :return:
        """
        return self.__command_write('OUTP1 ON') is not None

    def close_output_1(self) -> bool:
        """
        关闭电源1号输出口
        :return:
        """
        return self.__command_write('OUTP1 OFF') is not None

    def set_voltage_1(self, voltage) -> bool:
        """
        设置电源1电压
        :param voltage: 电压值
        :return:
        """
        return self.__command_write(f'VOLT1 {voltage}') is not None

    def open_over_voltage_protection(self) -> bool:
        """
        开启过压保护
        :return:
        """
        return self.__command_write("CURR:PROT:ON") is not None

    def query_current_1(self) -> float:
        """
        查询电源1电流
        :return: 电流值
        """
        try:
            return float(self.__command_query('MEAS1:CURR?'))
        except ValueError:
            return 0


if __name__ == '__main__':
    # 测试模块
    d66319 = D66319Control('GPIB0::5::INSTR')
    # 打开电源1号输出口
    if not d66319.open_output_1():
        exit(-1)
    # 设置 电压12v
    d66319.set_voltage_1(4)
    # 查询十次电流，1秒查询一次
    for i in range(100000):
        t = d66319.query_current_1()
        print("{:.5f}".format(t))
        time.sleep(0.01)
    # 关闭电源输出
    d66319.close_output_1()
