# GkClock_App

# 简述

## 目录

[TOC]

# 开发环境搭建

## 仓库其他组件拉取

* 更新子模块：`/GkClock_App$ git submodule update --init --recursive`
* 添加子模块：`/GkClock_App$ git submodule add -b <branch> <repository> [<path>`

## Windows开发环境

### 下载资源

* 参考文档：[Get Started — ESP8266 RTOS SDK Programming Guide documentation](https://docs.espressif.com/projects/esp8266-rtos-sdk/en/latest/get-started/index.html#get-started-get-esp-idf)
* 乐鑫环境工具链一体包：[一体包](https://dl.espressif.com/dl/esp32_win32_msys2_environment_and_toolchain-20181001.zip)
* ESP8266工具链：[工具链](https://dl.espressif.com/dl/xtensa-lx106-elf-gcc8_4_0-esp-2020r3-win32.zip)
* ESP8266 RTOS SDK：[RTOS SDK](https://github.com/espressif/ESP8266_RTOS_SDK.git)

### 步骤

1. 下载上述windows资源；
2. 解压乐鑫工具链一体包（重命名为msys32），将ESP8266工具链解压拷贝到`./esp/msys32/opt`下；
3. 编辑`./esp/msys32/etc/profile.d/esp32_toolchain.sh`，将解压ESP8266工具链`xtensa-lx106-elf`路径添加到环境变量PATH中，将GKClock_APP下components下ESP8266 SDK`ESP8266_RTOS_SDK`添加到环境变量IDF_PATH中；
4. 重新打开`./esp/msys32/mingw32.exe`软件，查看环境变量是否设置成功；
5. 在家目录下安装SDK所需安装包`python -m pip install --user -r $IDF_PATH/requirements.txt`

```shell
## ./esp/msys32/etc/profile.d/esp32_toolchain.sh
# This file was created by ESP-IDF windows_install_prerequisites.sh
# and will be overwritten if that script is run again.
export PATH="$PATH:/opt/xtensa-esp32-elf/bin"
export PATH="$PATH:/opt/xtensa-lx106-elf/bin"
 
export IDF_PATH="F:/study_line/8-2022/02-LongMarchPlan/02-Clock/program/GkClock_App/components/ESP8266_RTOS_SDK"

### 查看环境变量

```



## Ubuntu 开发环境

### 下载资源

* IDF编程指南：[ESP-IDF Programming Guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)

### 步骤

* 进入SDK目录：`cd GkClock_App/components/ESP8266_RTOS_SDK`
* 运行SDK环境安装脚本：`GkClock_App/components/ESP8266_RTOS_SDK$ ./install.sh`
* 运行环境变量导出脚本：`GkClock_App/components/ESP8266_RTOS_SDK$ source export.sh`
* 进入项目源码目录：`GkClock_App/components/ESP8266_RTOS_SDK$ cd ../../app/`
* 根据需要执行下章节编译固件相关操作

# 编译固件

注：新的工程编译前使用`make menuconfig`设置串口

* 配置项目：`idf.py menuconfig`
* 编译固件：`idf.py all`
* 烧写固件：`idf.py flash`
* 查看串口输出：`idf.py monitor`
* 编译并烧写固件：`idf.py flash`
* 编译、烧写固件并打开串口助手：`idf.py flash monitor`
* 只编译烧写APP：`idf.py app-flash`
* 编译、烧写App并打开串口助手：`idf.py app-flash monitor`
* 并行编译烧写：`idf.py -j5 app-flash monitor`

# QA

## 未满足Python要求

```shell
### ERROR LOG
$ make all
The following Python requirements are not satisfied:
click>=5.0
pyelftools>=0.22
The recommended way to install a packages is via "pacman". Please run "pacman -Ss <package_name>" for searching the package database and if found then "pacman -S mingw-w64-i686-python2-<package_name>" for installing it.
NOTE: You may need to run "pacman -Syu" if your package database is older and run twice if the previous run updated "pacman" itself.
Please read https://github.com/msys2/msys2/wiki/Using-packages for further information about using "pacman"
Alternatively, you can run "D:/Program Files/esp/msys32/mingw32/bin/python.exe -m pip install --user -r F:/study_line/8-2022/02-LongMarchPlan/02-Clock/program/GkClock_App/components/ESP8266_RTOS_SDK/requirements.txt" for resolving the issue.
make: *** 没有规则可制作目标“check_python_dependencies”，由“all” 需求。 停止。

### 解决办法
$ python -m pip install --user -r $IDF_PATH/requirements.txt
```

## 文件格式错误

```shell
### ERROR LOG
$ make all
/usr/bin/env: ‘python\r’: No such file or directory
make: *** No rule to make target 'check_python_dependencies', needed by 'all'.  Stop.

### 解决办法
在vscode 中将文件格式由CRLF修改为LF
```

## Linux 串口打开失败

```shell
### ERROR LOG
File "/home/wh/.espressif/python_env/rtos3.4_py2.7_env/lib/python2.7/site-packages/serial/serialposix.py", line 325, in open
    raise SerialException(msg.errno, "could not open port {}: {}".format(self._port, msg))
serial.serialutil.SerialException: [Errno 13] could not open port /dev/ttyUSB0: [Errno 13] Permission denied: '/dev/ttyUSB0'

### 解决办法：给串口增加权限
$ sudo chmod -R 777 /dev/ttyUSB0
```

## idf.py menuconfig 无法找到curses.h

```
### ERROR LOG
$ idf.py menuconfig
<command-line>:0:12: fatal error: curses.h: No such file or directory

### 解决办法 安装libncurses5-dev库
$ sudo apt-get install libncurses5-dev
```

