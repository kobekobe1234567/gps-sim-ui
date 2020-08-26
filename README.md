# GPS-SIM-UI

本软件基于GPS-SDR-SIM(https://github.com/osqzss/gps-sdr-sim)修改制作图形界面。使用USRP B210作为发射装置。
this software is based on GPS-SDR-SIM(https://github.com/osqzss/gps-sdr-sim) and make UI. this software use USRP B210 as the transmit equipment

### SOFTWARE environment(软件环境)

linux或者windows, chinese-win64-release里面是已经编译好的支持Windows 64位系统。
linux or windows, english-win64-release folder contains the compiled binaries for windows 64bit system.

### hardware requirment(硬件要求）

使用I5 3代或更高的CPU，如果运行时命令行界面打出大量的‘U’那就说明CPU性能不够，需要性能更好的CPU。
use I5 3 generation or above CPU, if it print a lot of 'U' in the command line terminal it means CPU performance is not good enough, you need to use more powerful CPU.

### install and configure(安装配置）

chinese-win64-release里面是已经编译好的程序，可以直接运行。B210的windows驱动需要另外安装，插入B210之后设备管理器里面有未知设备，选择更新驱动程序，选择搜索目录erllc_uhd_winusb_driver。
english-win64-release contains the compiled binaries which can be directly run. you may need to install B210 driver for windows. Connect B210, there is unkown device in device manager, update its driver, choose search in erllc_uhd_winusb_driver folder.

