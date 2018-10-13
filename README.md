# micro-service
This is a sample that shows how to implement a micro-serivce on C++ using the C++ REST SDK

[![Twitter](https://img.shields.io/badge/Twitter-@iUberCoder-blue.svg?style=flat)](https://twitter.com/iUberCoder)

## How to build

1. Install git, CMake, boost, openssl on your system, if you are using macOS this can be acomplished easily with the following command: 

          $ brew install cmake git openssl boost zlib
          
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

          $ ./wrk -c100 -t8 -d60s -s benchmark_microsvc.lua http://192.168.100.6:6502 --latency --rate 2000
          
   and see results similar to these:
   
            Running 1m test @ http://192.168.100.16:6502
              8 threads and 100 connections
              Thread calibration: mean lat.: 1.524ms, rate sampling interval: 10ms
              Thread calibration: mean lat.: 1.536ms, rate sampling interval: 10ms
              Thread calibration: mean lat.: 1.485ms, rate sampling interval: 10ms
              Thread calibration: mean lat.: 1.505ms, rate sampling interval: 10ms
              Thread calibration: mean lat.: 1.490ms, rate sampling interval: 10ms
              Thread calibration: mean lat.: 1.496ms, rate sampling interval: 10ms
              Thread calibration: mean lat.: 1.486ms, rate sampling interval: 10ms
              Thread calibration: mean lat.: 1.508ms, rate sampling interval: 10ms
              Thread Stats   Avg      Stdev     Max   +/- Stdev
                Latency     1.51ms    0.85ms  25.66ms   86.53%
                Req/Sec   263.60     98.75     1.00k    78.74%
              Latency Distribution (HdrHistogram - Recorded Latency)
             50.000%    1.45ms
             75.000%    1.85ms
             90.000%    2.23ms
             99.000%    3.07ms
             99.900%   14.38ms
             99.990%   23.30ms
             99.999%   25.50ms
            100.000%   25.68ms

              Detailed Percentile spectrum:
                   Value   Percentile   TotalCount 1/(1-Percentile)

                   0.197     0.000000            1         1.00
                   0.758     0.100000        10021         1.11
                   0.975     0.200000        20018         1.25
                   1.153     0.300000        30007         1.43
                   1.309     0.400000        40011         1.67
                   1.453     0.500000        49964         2.00
                   1.526     0.550000        54957         2.22
                   1.601     0.600000        59976         2.50
                   1.677     0.650000        64919         2.86
                   1.760     0.700000        69927         3.33
                   1.850     0.750000        74946         4.00
                   1.898     0.775000        77400         4.44
                   1.950     0.800000        79900         5.00
                   2.007     0.825000        82423         5.71
                   2.071     0.850000        84903         6.67
                   2.147     0.875000        87415         8.00
                   2.191     0.887500        88683         8.89
                   2.235     0.900000        89922        10.00
                   2.285     0.912500        91143        11.43
                   2.341     0.925000        92421        13.33
                   2.405     0.937500        93643        16.00
                   2.443     0.943750        94257        17.78
                   2.485     0.950000        94884        20.00
                   2.533     0.956250        95498        22.86
                   2.591     0.962500        96139        26.67
                   2.661     0.968750        96766        32.00
                   2.699     0.971875        97060        35.56
                   2.743     0.975000        97384        40.00
                   2.787     0.978125        97689        45.71
                   2.841     0.981250        97995        53.33
                   2.909     0.984375        98310        64.00
                   2.941     0.985938        98466        71.11
                   2.977     0.987500        98619        80.00
                   3.027     0.989062        98776        91.43
                   3.091     0.990625        98931       106.67
                   3.165     0.992188        99090       128.00
                   3.207     0.992969        99166       142.22
                   3.263     0.993750        99245       160.00
                   3.317     0.994531        99321       182.86
                   3.405     0.995313        99399       213.33
                   3.485     0.996094        99477       256.00
                   3.537     0.996484        99519       284.44
                   3.623     0.996875        99557       320.00
                   3.767     0.997266        99594       365.71
                   4.111     0.997656        99633       426.67
                   6.319     0.998047        99672       512.00
                   8.943     0.998242        99692       568.89
                  10.247     0.998437        99711       640.00
                  11.415     0.998633        99731       731.43
                  12.871     0.998828        99750       853.33
                  14.503     0.999023        99770      1024.00
                  15.215     0.999121        99780      1137.78
                  15.759     0.999219        99789      1280.00
                  16.215     0.999316        99799      1462.86
                  16.911     0.999414        99809      1706.67
                  18.751     0.999512        99819      2048.00
                  19.279     0.999561        99825      2275.56
                  19.743     0.999609        99828      2560.00
                  20.383     0.999658        99834      2925.71
                  21.263     0.999707        99838      3413.33
                  21.375     0.999756        99843      4096.00
                  21.615     0.999780        99846      4551.11
                  21.647     0.999805        99848      5120.00
                  21.839     0.999829        99850      5851.43
                  22.303     0.999854        99853      6826.67
                  22.799     0.999878        99855      8192.00
                  23.295     0.999890        99857      9102.22
                  23.567     0.999902        99858     10240.00
                  23.631     0.999915        99859     11702.86
                  23.823     0.999927        99860     13653.33
                  24.415     0.999939        99861     16384.00
                  24.895     0.999945        99862     18204.44
                  25.135     0.999951        99863     20480.00
                  25.135     0.999957        99863     23405.71
                  25.183     0.999963        99864     27306.67
                  25.183     0.999969        99864     32768.00
                  25.391     0.999973        99865     36408.89
                  25.391     0.999976        99865     40960.00
                  25.391     0.999979        99865     46811.43
                  25.503     0.999982        99866     54613.33
                  25.503     0.999985        99866     65536.00
                  25.503     0.999986        99866     72817.78
                  25.503     0.999988        99866     81920.00
                  25.503     0.999989        99866     93622.86
                  25.679     0.999991        99867    109226.67
                  25.679     1.000000        99867          inf
            #[Mean    =        1.510, StdDeviation   =        0.851]
            #[Max     =       25.664, Total count    =        99867]
            #[Buckets =           27, SubBuckets     =         2048]
            ----------------------------------------------------------
              119986 requests in 1.00m, 12.36MB read
            Requests/sec:   1999.74
            Transfer/sec:    210.91KB
**IMPORTANT**
The results above will depend on the system where the test is executed and please to avoid execisve I/O during the test comment the following line on any of the scripts:

            response = function(status, headers, body)
               -- comment the following line to avoid server's excesive I/O to console on heavy load
               -- io.write("response: \n" .. body .. "\n---------------------------------------------\n")
            end
            
You can copy from the results above the histogram's section following the [sample format found here](https://github.com/HdrHistogram/HdrHistogram/blob/master/GoogleChartsExample/example1.txt), save it into a file and see a nice graph unsing [HdrHistogram Ploter](http://hdrhistogram.github.io/HdrHistogram/plotFiles.html).
