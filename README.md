KernelProject
=============

Plain project for usege with github/zer0mem/common.git


**1. clone all (automatically)**

    git clone --recursive https://github.com/zer0mem/KernelProject.git


**2. manual clone**

    git clone https://github.com/zer0mem/KernelProject.git
    cd ./KernelProject/libc/
    git clone https://github.com/zer0mem/libc.git .
    cd ../capstone/
    git clone -b next https://github.com/aquynh/capstone.git .

if you also want to test *boost*, do:

    cd ../boost
    git clone --recursive https://github.com/boostorg/boost


**3. build Capstone library**

- rebuild capstone_static

- rebuild test_x86


**4. build**

- architecture for build : Win7 Release -> x64;
- rebuild solution

  KernelProject -> Projects -> Configuration Properties -> Driver Signing -> General :
  ---> Sign Mode : "Test Sign"
  ---> Test Certificate : "<Create Test Certificate ...>"
