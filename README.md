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
          $ Modern C++ Microservice now listening for requests at: http://<your computer's IP>:6502/v1/ivmero/api
             
7. To perform a benchmark on the Modern C++ Microservice I had included two **lua** scritps which can be executed using [WRK2](https://github.com/giltene/wrk2) HTTP Benckmark Tool, using the following command:

          $ ./wrk -c100 -t8 -d5s -s benchmark_microsvc.lua http://192.168.100.6:6502 --latency --rate 200
          
   and see results similar to these:
   
            Running 5s test @ http://192.168.100.6:6502
              8 threads and 100 connections
              Thread Stats   Avg      Stdev     Max   +/- Stdev
                Latency   121.80ms  101.13ms 306.94ms   44.67%
                Req/Sec        nan       nan   0.00      0.00%
              Latency Distribution (HdrHistogram - Recorded Latency)
             50.000%  125.57ms
             75.000%  210.94ms
             90.000%  268.80ms
             99.000%  302.33ms
             99.900%  305.66ms
             99.990%  307.20ms
             99.999%  307.20ms
            100.000%  307.20ms

              Detailed Percentile spectrum:
                   Value   Percentile   TotalCount 1/(1-Percentile)

                   9.287     0.000000            1         1.00
                  12.783     0.100000          105         1.11
                  14.463     0.200000          207         1.25
                  18.431     0.300000          310         1.43
                  43.839     0.400000          413         1.67
                 125.567     0.500000          516         2.00
                 137.727     0.550000          568         2.22
                 151.423     0.600000          621         2.50
                 172.927     0.650000          671         2.86
                 197.759     0.700000          724         3.33
                 210.943     0.750000          774         4.00
                 221.567     0.775000          800         4.44
                 238.207     0.800000          826         5.00
                 247.039     0.825000          853         5.71
                 253.439     0.850000          878         6.67
                 263.423     0.875000          905         8.00
                 267.775     0.887500          916         8.89
                 268.799     0.900000          930        10.00
                 272.383     0.912500          943        11.43
                 274.943     0.925000          955        13.33
                 279.039     0.937500          968        16.00
                 281.087     0.943750          974        17.78
                 282.367     0.950000          984        20.00
                 283.647     0.956250          988        22.86
                 285.183     0.962500          995        26.67
                 288.255     0.968750         1002        32.00
                 289.791     0.971875         1004        35.56
                 292.351     0.975000         1007        40.00
                 292.863     0.978125         1010        45.71
                 293.887     0.981250         1013        53.33
                 296.959     0.984375         1016        64.00
                 298.495     0.985938         1019        71.11
                 299.519     0.987500         1021        80.00
                 299.519     0.989062         1021        91.43
                 302.335     0.990625         1023       106.67
                 302.847     0.992188         1024       128.00
                 303.615     0.992969         1027       142.22
                 303.615     0.993750         1027       160.00
                 303.615     0.994531         1027       182.86
                 303.871     0.995313         1029       213.33
                 303.871     0.996094         1029       256.00
                 303.871     0.996484         1029       284.44
                 303.871     0.996875         1029       320.00
                 304.639     0.997266         1030       365.71
                 304.639     0.997656         1030       426.67
                 304.639     0.998047         1030       512.00
                 305.663     0.998242         1031       568.89
                 305.663     0.998437         1031       640.00
                 305.663     0.998633         1031       731.43
                 305.663     0.998828         1031       853.33
                 305.663     0.999023         1031      1024.00
                 307.199     0.999121         1032      1137.78
                 307.199     1.000000         1032          inf
            #[Mean    =      121.804, StdDeviation   =      101.130]
            #[Max     =      306.944, Total count    =         1032]
            #[Buckets =           27, SubBuckets     =         2048]
            ----------------------------------------------------------
              1040 requests in 5.55s, 115.03KB read
            Requests/sec:    187.40
            Transfer/sec:     20.73KB
            
**IMPORTANT**
The results above will depend on the system where the test is executed and please to avoid execisve I/O during the test comment the following line on any of the scripts:

            response = function(status, headers, body)
               -- comment the following line to avoid server's excesive I/O to console on heavy load
               -- io.write("response: \n" .. body .. "\n---------------------------------------------\n")
            end
            
You can copy the histogram section ( [sample here](https://github.com/HdrHistogram/HdrHistogram/blob/master/GoogleChartsExample/example1.txt) ) and see a nice graph unsing [HdrHistogram Ploter](http://hdrhistogram.github.io/HdrHistogram/plotFiles.html).
