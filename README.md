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

          $ ./wrk -c100 -t8 -d60s -s benchmark_microsvc.lua http://192.168.100.6:6502 --latency --rate 200
          
   and see results similar to these:
   
            Running 1m test @ http://192.168.100.16:6502
              8 threads and 100 connections
              Thread calibration: mean lat.: 1.884ms, rate sampling interval: 10ms
              Thread calibration: mean lat.: 1.854ms, rate sampling interval: 10ms
              Thread calibration: mean lat.: 1.782ms, rate sampling interval: 10ms
              Thread calibration: mean lat.: 1.787ms, rate sampling interval: 10ms
              Thread calibration: mean lat.: 1.717ms, rate sampling interval: 10ms
              Thread calibration: mean lat.: 1.749ms, rate sampling interval: 10ms
              Thread calibration: mean lat.: 1.897ms, rate sampling interval: 10ms
              Thread calibration: mean lat.: 1.753ms, rate sampling interval: 10ms
              Thread Stats   Avg      Stdev     Max   +/- Stdev
                Latency     1.68ms  774.31us  16.56ms   81.85%
                Req/Sec    29.50     72.80   555.00     86.90%
              Latency Distribution (HdrHistogram - Recorded Latency)
             50.000%    1.59ms
             75.000%    1.99ms
             90.000%    2.44ms
             99.000%    3.41ms
             99.900%   10.98ms
             99.990%   16.45ms
             99.999%   16.58ms
            100.000%   16.58ms

              Detailed Percentile spectrum:
                   Value   Percentile   TotalCount 1/(1-Percentile)

                   0.302     0.000000            1         1.00
                   0.946     0.100000         1004         1.11
                   1.156     0.200000         1999         1.25
                   1.315     0.300000         2999         1.43
                   1.457     0.400000         3995         1.67
                   1.593     0.500000         4995         2.00
                   1.664     0.550000         5498         2.22
                   1.739     0.600000         5994         2.50
                   1.815     0.650000         6492         2.86
                   1.901     0.700000         6990         3.33
                   1.986     0.750000         7489         4.00
                   2.035     0.775000         7740         4.44
                   2.097     0.800000         7988         5.00
                   2.163     0.825000         8241         5.71
                   2.247     0.850000         8493         6.67
                   2.331     0.875000         8737         8.00
                   2.383     0.887500         8863         8.89
                   2.445     0.900000         8993        10.00
                   2.527     0.912500         9111        11.43
                   2.619     0.925000         9238        13.33
                   2.717     0.937500         9360        16.00
                   2.763     0.943750         9424        17.78
                   2.811     0.950000         9486        20.00
                   2.861     0.956250         9548        22.86
                   2.919     0.962500         9611        26.67
                   2.995     0.968750         9673        32.00
                   3.041     0.971875         9704        35.56
                   3.103     0.975000         9735        40.00
                   3.151     0.978125         9766        45.71
                   3.197     0.981250         9797        53.33
                   3.273     0.984375         9828        64.00
                   3.297     0.985938         9844        71.11
                   3.329     0.987500         9860        80.00
                   3.375     0.989062         9875        91.43
                   3.435     0.990625         9892       106.67
                   3.511     0.992188         9906       128.00
                   3.547     0.992969         9914       142.22
                   3.611     0.993750         9922       160.00
                   3.681     0.994531         9930       182.86
                   3.851     0.995313         9938       213.33
                   3.987     0.996094         9945       256.00
                   4.095     0.996484         9949       284.44
                   4.283     0.996875         9953       320.00
                   4.579     0.997266         9957       365.71
                   5.167     0.997656         9961       426.67
                   5.699     0.998047         9966       512.00
                   5.763     0.998242         9967       568.89
                   9.263     0.998437         9969       640.00
                  10.367     0.998633         9971       731.43
                  10.967     0.998828         9973       853.33
                  10.983     0.999023         9975      1024.00
                  11.423     0.999121         9976      1137.78
                  15.607     0.999219         9977      1280.00
                  15.799     0.999316         9978      1462.86
                  15.983     0.999414         9979      1706.67
                  15.991     0.999512         9980      2048.00
                  15.991     0.999561         9980      2275.56
                  16.287     0.999609         9981      2560.00
                  16.287     0.999658         9981      2925.71
                  16.343     0.999707         9982      3413.33
                  16.343     0.999756         9982      4096.00
                  16.343     0.999780         9982      4551.11
                  16.447     0.999805         9983      5120.00
                  16.447     0.999829         9983      5851.43
                  16.447     0.999854         9983      6826.67
                  16.447     0.999878         9983      8192.00
                  16.447     0.999890         9983      9102.22
                  16.575     0.999902         9984     10240.00
                  16.575     1.000000         9984          inf
            #[Mean    =        1.677, StdDeviation   =        0.774]
            #[Max     =       16.560, Total count    =         9984]
            #[Buckets =           27, SubBuckets     =         2048]
            ----------------------------------------------------------
              12008 requests in 1.00m, 1.24MB read
            Requests/sec:    200.13
            Transfer/sec:     21.11KB            
**IMPORTANT**
The results above will depend on the system where the test is executed and please to avoid execisve I/O during the test comment the following line on any of the scripts:

            response = function(status, headers, body)
               -- comment the following line to avoid server's excesive I/O to console on heavy load
               -- io.write("response: \n" .. body .. "\n---------------------------------------------\n")
            end
            
You can copy the histogram section ( [sample here](https://github.com/HdrHistogram/HdrHistogram/blob/master/GoogleChartsExample/example1.txt) ) and see a nice graph unsing [HdrHistogram Ploter](http://hdrhistogram.github.io/HdrHistogram/plotFiles.html).
