The nultithreading function was associtaed with reading the pixel
in a specific order to print all the colors.

The output should be formatted.

Also, I used command to do perfoemance comparison

$ time ./srt 1-test.ppm > 1-test

real    0m53.044s
user    0m53.020s
sys     0m0.002s

$ time ./srt 2-test.ppm > 2-test

real    0m26.747s
user    0m52.954s
sys     0m0.026s

$ time ./srt 4-test.ppm > 4-test

real    0m13.717s
user    0m54.169s
sys     0m0.009s

$ time ./srt 8-test.ppm > 8-test

real    0m7.297s
user    0m56.303s
sys     0m0.004s

The real time is reduced but the user and sys time are stay the same.
