#include <sys/timeb.h>
#include "Arduino.h"
#include <unistd.h>
#include <sys/time.h>
timeb t_start;
unsigned tv_start_unsigned;

unsigned long millis() {
  timeb t_now;
  ftime(&t_now);
  return (t_now.time  - t_start.time) * 1000 + (t_now.millitm - t_start.millitm);
}

unsigned long micros() {
  struct timeval tv_now;
  gettimeofday(&tv_now,NULL);
  unsigned long time_in_micros = 1000000 * tv_now.tv_sec + tv_now.tv_usec;
  return (time_in_micros - tv_start_unsigned);
}

void delay(unsigned long ms) {
  unsigned long start = millis();
  while(millis() - start < ms){
    yield();
  }
}

void initialize_mock_arduino() {
  ftime(&t_start);
  struct timeval tv_start;
  gettimeofday(&tv_start,NULL);

  tv_start_unsigned = 1000000 * tv_start.tv_sec + tv_start.tv_usec;
}

myyieldfn yield_impl = NULL;
void yield()
{
    if (yield_impl)
        yield_impl();
    else
        usleep(1000);
}