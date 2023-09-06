# neon_game

安装qemu仿真平台：

sudo apt-get install qemu-user-static

安装交叉编译器：

sudo apt-get install gcc-arm-linux-gnueabihf g++-arm-linux-gnueabihf

安装交叉编译依赖包：

sudo apt-get install libc6-armhf-cross

编译完成后，执行：
./run.sh xxx
即可运行