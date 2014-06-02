KernelProject
=============

Plain project for usege with github/zer0mem/common.git


install : 

0. clone all : 
git clone --recursive https://github.com/zer0mem/KernelProject.git

1. clone :
git clone https://github.com/zer0mem/KernelProject.git
cd ./KernelProject/libc/
git clone https://github.com/zer0mem/libc.git .
cd ../capstone/
git clone -b next https://github.com/aquynh/capstone.git .

//and if you want to test also boost : 
cd ../boost
git clone --recursive https://github.com/boostorg/boost

2. build capstone .lib step : 
rebuild capstone_static
rebuild test_x86

3. build :
architecture for build : Win7 Release -> x64;
rebuild solution
+ KernelProject -> Projects -> Configuration Properties -> Driver Signing -> General :
---> Sign Mode : "Test Sign"
---> Test Certificate : "<Create Test Certificate ...>"
