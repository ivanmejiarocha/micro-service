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
   
            Running 1m test @ http://192.168.100.6:6502
              8 threads and 100 connections
              Thread calibration: mean lat.: 123.693ms, rate sampling interval: 516ms
              Thread calibration: mean lat.: 123.950ms, rate sampling interval: 518ms
              Thread calibration: mean lat.: 124.172ms, rate sampling interval: 516ms
              Thread calibration: mean lat.: 124.024ms, rate sampling interval: 515ms
              Thread calibration: mean lat.: 126.729ms, rate sampling interval: 518ms
              Thread calibration: mean lat.: 127.299ms, rate sampling interval: 519ms
              Thread calibration: mean lat.: 126.989ms, rate sampling interval: 518ms
              Thread calibration: mean lat.: 126.715ms, rate sampling interval: 517ms
              Thread Stats   Avg      Stdev     Max   +/- Stdev
                Latency   180.86ms  166.63ms 637.44ms   80.02%
                Req/Sec    24.76     15.93    46.00     50.85%
              Latency Distribution (HdrHistogram - Recorded Latency)
             50.000%  146.05ms
             75.000%  229.38ms
             90.000%  547.84ms
             99.000%  609.28ms
             99.900%  631.29ms
             99.990%  637.44ms
             99.999%  637.95ms
            100.000%  637.95ms

              Detailed Percentile spectrum:
                   Value   Percentile   TotalCount 1/(1-Percentile)

                   6.447     0.000000            1         1.00
                  15.287     0.100000          999         1.11
                  34.047     0.200000         1997         1.25
                  69.119     0.300000         2996         1.43
                 114.687     0.400000         3995         1.67
                 146.047     0.500000         4992         2.00
                 161.535     0.550000         5496         2.22
                 177.279     0.600000         5995         2.50
                 195.967     0.650000         6490         2.86
                 213.759     0.700000         6991         3.33
                 229.375     0.750000         7489         4.00
                 238.975     0.775000         7739         4.44
                 249.599     0.800000         7991         5.00
                 260.607     0.825000         8237         5.71
                 292.607     0.850000         8487         6.67
                 342.015     0.875000         8736         8.00
                 529.407     0.887500         8867         8.89
                 547.839     0.900000         8991        10.00
                 558.079     0.912500         9119        11.43
                 566.783     0.925000         9243        13.33
                 572.415     0.937500         9367        16.00
                 576.511     0.943750         9434        17.78
                 578.559     0.950000         9488        20.00
                 583.167     0.956250         9561        22.86
                 587.263     0.962500         9617        26.67
                 590.847     0.968750         9685        32.00
                 592.383     0.971875         9707        35.56
                 594.943     0.975000         9737        40.00
                 596.479     0.978125         9766        45.71
                 600.063     0.981250         9808        53.33
                 602.111     0.984375         9828        64.00
                 603.647     0.985938         9845        71.11
                 605.183     0.987500         9862        80.00
                 606.719     0.989062         9876        91.43
                 609.791     0.990625         9896       106.67
                 611.839     0.992188         9908       128.00
                 612.863     0.992969         9914       142.22
                 614.911     0.993750         9925       160.00
                 615.935     0.994531         9934       182.86
                 616.447     0.995313         9938       213.33
                 617.471     0.996094         9945       256.00
                 620.031     0.996484         9950       284.44
                 621.567     0.996875         9953       320.00
                 622.591     0.997266         9958       365.71
                 626.687     0.997656         9962       426.67
                 627.199     0.998047         9967       512.00
                 627.199     0.998242         9967       568.89
                 629.247     0.998437         9969       640.00
                 630.783     0.998633         9973       731.43
                 630.783     0.998828         9973       853.33
                 632.319     0.999023         9976      1024.00
                 632.319     0.999121         9976      1137.78
                 636.415     0.999219         9978      1280.00
                 636.415     0.999316         9978      1462.86
                 636.927     0.999414         9980      1706.67
                 636.927     0.999512         9980      2048.00
                 636.927     0.999561         9980      2275.56
                 637.439     0.999609         9983      2560.00
                 637.439     0.999658         9983      2925.71
                 637.439     0.999707         9983      3413.33
                 637.439     0.999756         9983      4096.00
                 637.439     0.999780         9983      4551.11
                 637.439     0.999805         9983      5120.00
                 637.439     0.999829         9983      5851.43
                 637.439     0.999854         9983      6826.67
                 637.439     0.999878         9983      8192.00
                 637.439     0.999890         9983      9102.22
                 637.951     0.999902         9984     10240.00
                 637.951     1.000000         9984          inf
            #[Mean    =      180.862, StdDeviation   =      166.626]
            #[Max     =      637.440, Total count    =         9984]
            #[Buckets =           27, SubBuckets     =         2048]
            ----------------------------------------------------------
              12000 requests in 1.00m, 1.24MB read
            Requests/sec:    199.55
            Transfer/sec:     21.05KB
            
**IMPORTANT**
The results above will depend on the system where the test is executed and please to avoid execisve I/O during the test comment the following line on any of the scripts:

            response = function(status, headers, body)
               -- comment the following line to avoid server's excesive I/O to console on heavy load
               -- io.write("response: \n" .. body .. "\n---------------------------------------------\n")
            end
            
You can copy the histogram section ( [sample here](https://github.com/HdrHistogram/HdrHistogram/blob/master/GoogleChartsExample/example1.txt) ) and see a nice graph unsing [HdrHistogram Ploter](http://hdrhistogram.github.io/HdrHistogram/plotFiles.html).
