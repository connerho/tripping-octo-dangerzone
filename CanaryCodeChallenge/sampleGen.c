#include <math.h>
#include <stdio.h>
#define NUM_SAMPLES 40
#define PI 3.1415926535
static short samples[NUM_SAMPLES];
int main(int argc, char *argv[])
{
  /*
  We want to scale the output of sin() below to the max
  range that will fit into a 16-bit signed integer;
  sin() returns values in the range [-1,1], so let's
  multiply by the max short int value.
  */
  const int scale_factor = (pow(2,15))-1; /* 32767 */
  printf("%d\n", scale_factor);
  const unsigned int FREQ = 2u; // Will generate two cycles from the sin wave
  const double SAMPLE_RATE = 2.0f * PI * FREQ / NUM_SAMPLES;

  /* Calculate the samples*/
  for (int i = 0; i < NUM_SAMPLES; i++)
  {
    samples[i] = (short)(scale_factor * sin(i * SAMPLE_RATE));
    printf("%d\n", samples[i]);
  }
  /* write the output file */
  FILE *f = fopen("samples.bin", "w");
  fwrite(samples, sizeof(short), NUM_SAMPLES, f);
  fclose(f);

  return 0;
}