# micro-service
This is a sample that shows how to implement a micro-serivce on C++ using the C++ REST SDK

## How to build

1. Install git, CMake, boost, openssl on your system, if you are using macOS this can be acomplished easily with the following command: 

          $ brew install cmake git openssl boost
          
2. Clone the repository.
3. Go to the directory micro-service/libs and execute the script: ```./build_dependencies.sh``` that'll clone the [C++ REST SDK](https://github.com/Microsoft/cpprestsdk) repository and will build the static version of the library, if you want to build the dynamic link version of the library just on the **build_dependencies.sh** script remove the flag: ```-DBUILD_SHARED_LIBS=OFF```.
4. Go to the directory micro-service and type the following commands:

          $ mkdir build
          $ cd build
          $ cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ..
          
5. Finally type the command:

          $ make -j 8
          
6. On ```./build``` directory type and you should see the following output:

          $ ./micro-service   
          $ Copyright © ivmeroLabs 2016. C++ Microservice now listening for requests at: http://<your computer's IP>:6502/v1/ivmero/api