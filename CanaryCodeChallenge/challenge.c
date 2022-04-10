#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>

#define NUM_THREADS 2
#define NUM_SAMPLES 11
#define THREAD_ONE_TIMER_MS 50
#define THRESHOLD 32000


int16_t soundBuff[NUM_SAMPLES];
uint32_t timeBuff[NUM_SAMPLES];
uint8_t curIdx;
uint8_t threshIdx;


static uint32_t sampleCounter = 0u;

static struct timespec remaining, request = {0, THREAD_ONE_TIMER_MS * 1000000};
static struct timespec progStart, loopStart, loopEnd, readTime;

// Condition variables for signalling between the threads
static pthread_mutex_t var_modify_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t output_write_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t output_write_cond = PTHREAD_COND_INITIALIZER;

static uint8_t endThreads = 0u;
static uint32_t readTime_ms = 0u;


void* inputReaderThread(void* arg)
{
  // Time counter to make sure second thread executes every 50ms
  uint64_t diffTime;
  time_t newTime;
  FILE* filePtr = (FILE*)arg;
  size_t retCode;
  int16_t threshIdx;
  while(1)
  {
    pthread_mutex_lock(&var_modify_mutex);
    retCode = fread(&soundBuff[curIdx], sizeof(int16_t), 1, filePtr);

    // Check if we have reached the end of the file or error so we know when to terminate
    if(feof(filePtr) || ferror(filePtr))
    {
      endThreads = 1;
      pthread_mutex_unlock(&var_modify_mutex);
      pthread_cond_signal(&output_write_cond);
      pthread_exit(NULL);
    }

    clock_gettime(CLOCK_REALTIME, &readTime);
    readTime_ms = (readTime.tv_sec - progStart.tv_sec) * 1000 + (readTime.tv_nsec - progStart.tv_nsec) / 1000000;
    timeBuff[curIdx] = readTime_ms;
    sampleCounter++;
    curIdx++;
    curIdx = curIdx % NUM_SAMPLES;
    threshIdx++;
    threshIdx = threshIdx % NUM_SAMPLES;
    pthread_mutex_unlock(&var_modify_mutex);

    if(soundBuff[threshIdx] > THRESHOLD)
    {
      pthread_cond_signal(&output_write_cond);
    }

    clock_gettime(CLOCK_REALTIME, &loopEnd);
    diffTime = (loopEnd.tv_sec - loopStart.tv_sec) * 1000 + (loopEnd.tv_nsec - loopStart.tv_nsec) / 1000000;

    printf("The difference in time was %d ms\n", diffTime);

    if(diffTime > THREAD_ONE_TIMER_MS)
    {
      request.tv_nsec = (THREAD_ONE_TIMER_MS - (diffTime - THREAD_ONE_TIMER_MS)) * 1000000;
    }

    clock_gettime(CLOCK_REALTIME, &loopStart);
    nanosleep(&request, &remaining);
  }
}

void* outputWriterThread(void* arg)
{
  FILE* filePtr = (FILE*)arg;
  uint32_t triggerNum = 0;
  uint32_t timestamp = 0;
  int16_t sample1 = 0;
  int16_t sample2 = 0;
  int16_t sample3 = 0;
  int16_t sample4 = 0;
  int16_t sample5 = 0;
  int16_t sample6 = 0;
  int16_t sample7 = 0;
  int16_t sample8 = 0;
  int16_t sample9 = 0;
  int16_t sample10 = 0;
  int16_t sample11 = 0;
  while(1)
  {
    pthread_mutex_lock( &output_write_mutex );
    pthread_cond_wait( &output_write_cond, &output_write_mutex);
    pthread_mutex_unlock( &output_write_mutex );

    if(endThreads)
    {
      pthread_exit(NULL);
    }

    pthread_mutex_lock(&var_modify_mutex);
    triggerNum = sampleCounter - 5;
    timestamp = timeBuff[threshIdx];
    sample1  = soundBuff[(threshIdx+5)%NUM_SAMPLES];;
    sample2  = soundBuff[(threshIdx+4)%NUM_SAMPLES];;
    sample3  = soundBuff[(threshIdx+3)%NUM_SAMPLES];;
    sample4  = soundBuff[(threshIdx+2)%NUM_SAMPLES];;
    sample5  = soundBuff[(threshIdx+1)%NUM_SAMPLES];;
    sample6  = soundBuff[threshIdx];
    sample7  = soundBuff[(threshIdx+10)%NUM_SAMPLES];
    sample8  = soundBuff[(threshIdx+9)%NUM_SAMPLES];
    sample9  = soundBuff[(threshIdx+8)%NUM_SAMPLES];
    sample10 = soundBuff[(threshIdx+7)%NUM_SAMPLES];
    sample11 = soundBuff[(threshIdx+6)%NUM_SAMPLES];
    pthread_mutex_unlock(&var_modify_mutex);

    fprintf(filePtr, "%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n", 
                      triggerNum,
                      timestamp,
                      sample1,
                      sample2,
                      sample3,
                      sample4,
                      sample5,
                      sample6,
                      sample7,
                      sample8,
                      sample9,
                      sample10,
                      sample11);
    printf("Wrote to file\n");
  }
}

int main(int argc, char **argv)
{
  // Input argument checking
  if(argc != 3)
  {
    printf("Useage: ./boom <inputFile> <outputFile>\n");
    printf("<inputFile> The input file that you wish to read samples from\n");
    printf("<outputFile> The filename where output will be stored\n");

    return EXIT_FAILURE;
  }

  FILE* inFilePtr = fopen(argv[1], (const char*)"rb");
  if(!inFilePtr)
  {
    printf("ERROR: Problem opening input file %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  FILE* outFilePtr = fopen(argv[2], (const char*)"w");
  if(!outFilePtr)
  {
    printf("ERROR: Problem opening output file %s\n", argv[2]);
    return EXIT_FAILURE;
  }

  pthread_t thr[NUM_THREADS];

  // Initialize our cyclical buffer
  for(int i = 0; i < NUM_SAMPLES; i++)
  {
    soundBuff[i] = 0;
    timeBuff[i] = 0;
  }
  curIdx = 0u;
  threshIdx = 5u;

  // Initialize the time variable
  clock_gettime(CLOCK_REALTIME, &progStart);
  clock_gettime(CLOCK_REALTIME, &loopStart);

  // Create threads
  int rc;
  if( (rc = pthread_create(&thr[1], NULL, outputWriterThread, (void*)outFilePtr)) )
  {
    fprintf(stderr, "ERROR: pthread_create outputWriterThread, rc: %d\n", rc);
    return EXIT_FAILURE;
  }
  if( (rc = pthread_create(&thr[0], NULL, inputReaderThread, (void*)inFilePtr)) )
  {
    fprintf(stderr, "ERROR: pthread_create inputReaderThread, rc: %d\n", rc);
    return EXIT_FAILURE;
  }

  // Wait until the threads are done
  pthread_join(thr[0], NULL);
  pthread_join(thr[1], NULL);

  // Close out our files that we have open
  fclose(outFilePtr);
  fclose(inFilePtr);

  printf("Done.\n");

  return EXIT_SUCCESS;
}