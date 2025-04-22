ASSUMPTIONS
- There are at least 6 samples in the input binary file
- There are no noise sounds in the last 5 samples of the binary file. Prompt said to have 5 samples AFTER the noise sample was detected.
- If noise occurs in the first 5 samples of the input binary file, the preceeding samples are assumed to be 0.
- The first sample is read at time ~0ms
- The first sample in the input binary file has an index of 1

TESTING METHODOLOGY
- I used the sampleGen.c (fixed) script to generate a sin wave as input
- I set the THRESHOLD parameter to be 32000 so that it would trigger two writes to the output file
- I checked to see that the sample number, timestamp, and values of the 11 samples matched with expectations
- I then lowered the THRESHOLD parameter so that more writes would occur to file
- I did the above check again to verify correctness

DESIGN THOUGHTS
- I developed this in a Windows environment using MinGW, I do not have a Linux environment setup at home
- I wanted to use two threads to implement the solution. One thread would be resposible for the 50ms reads from 
  the input file while the second thread would be responsible for writing to output.
- The reading thread would be assigned highest priority so that if we were writing to output and the 50ms timer went off
  the reading thread would pre-empt the output writing thread.
- I am not used to programming real-time with Linux. The timing for the 50ms thread was not exact and would vary call to call.
  I had to implement a very crude Proportional Controller to account for the timing error. If the system calls for a hard deadline
  of 50ms reads, perhaps using an RTOS would be in order (Keil, FreeRTOS, VxWorks if you like paying exorbinant licensing fees)
- I wrapped shared resources amongst threads via mutex so that there would not be any resource contention
- Since the output writer only needs to write when a sample is detected above the threshold, I just had the 50ms thread signal to the
  output writer when it needed to run
- Its possible if this is running on a much slower system that the implemented solution will not be sufficient. In Keil RTOS, there is 
  something called a Message Queue as a means of communication between threads. Threads using Message Queues can also pend off of waiting
  for a message. The idea would be that once a sample is detected above the THRESHOLD, that the 50ms thread would package a message containing
  all the data necessary to write to an output file and send it to the output writer thread. Even if the output writer was slow in writing out
  the data, each subsequent message would be placed into the queue and therefor no data would be overwritten inbetween writes. I did not find
  a similar setup in the <pthread> API.

FILES
- challenge.c is the program made for PART 1 of the programming prompt
- sampleGen.c is the program made for PART 2 of the programming prompt

USE
- "make all" will make the program for PART 1 of the programming assignment. "boom" is the name of the executable.
- "make samples" will make the program for generating *.bin files used as input to PART 1. "samples" is the name of the executable.
- Use of "boom" is as instructed in the programming prompt
- You will need to manually update the THRESHOLD variable in challenge.c and recompile if you would like to change the threshold