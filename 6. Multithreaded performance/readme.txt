I needed to first check the code in main.c to
attempt to multithread it. I first thought about
using the pthread library using pthread_create
and pthread_join. First, I check main.c and find that
there are certain changes that can be made.
Thus I  attempt to use multithreading for the printing
of each pixel. So I first put the huge nested for loop into
another function so that it can be called by different
threads. However, within the main function were variables
that the function I created were needed for. So I made these
variables global which makes it work and allows my threads
to execute to completion.

I then proceeded to run the program but then saw that the
output was of all the pixels were out of order. After
looking at the code I finally realized that the pixels were printing
in random order due to race conditions. To fix this, I created
a global 3D array that would allow me to store the values within the
arrays. This will allow the arrays to contain and print the pixels in
order and thus make this work.

I then the create and join functions within for loops capped at the
number of threads. When looking at it, I also see that the threads evenly
divide up the work and thus make it work a lot faster and more efficiently.

Another issue I ran into was not having a bracket to match the for loop
but it's a small fix that took relatively a short amount of time. Other
than that, I felt like I was able to create this program within a
short amount of time. 


I then use make clean check and check out how it runs. I use a simple
test run: 

rm -f *.o *.tmp 1-test.ppm 2-test.ppm 4-test.ppm 8-test.ppm srt srt.tgz
gcc -std=gnu11 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o main.o main.c
gcc -std=gnu11 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o raymath.o raymath.c
gcc -std=gnu11 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o shaders.o shaders.c
gcc -std=gnu11 -g -O2 -Wall -Wextra -Wno-unused-parameter -o srt main.o raymath.o shaders.o -lm -lpthread
time ./srt 1-test.ppm >1-test.ppm.tmp

real    0m47.146s
user    0m47.137s
sys     0m0.003s
mv 1-test.ppm.tmp 1-test.ppm
time ./srt 2-test.ppm >2-test.ppm.tmp

real    0m23.302s
user    0m46.302s
sys     0m0.001s
mv 2-test.ppm.tmp 2-test.ppm
time ./srt 4-test.ppm >4-test.ppm.tmp

real    0m11.655s
user    0m46.308s
sys     0m0.001s
mv 4-test.ppm.tmp 4-test.ppm
time ./srt 8-test.ppm >8-test.ppm.tmp

real    0m7.073s
user    0m53.429s
sys     0m0.006s
mv 8-test.ppm.tmp 8-test.ppm
for file in 1-test.ppm 2-test.ppm 4-test.ppm 8-test.ppm; do \
  diff -u baseline.ppm $file || exit; \
done

and try to recognize some patterns. It is very clear that
the real time for this significantly decreases as we use more threads,
as it divides the work like previously stated, thus parallelizing the task. 
The user time however, slightly increases, and the sys time remains about the same.

