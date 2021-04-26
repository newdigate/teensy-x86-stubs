#include <sys/timeb.h>
#include "Arduino.h"
#include <unistd.h>
#include <sys/time.h>
timeb t_start;
unsigned tv_start_unsigned;

bool has_initialized_mock_arduino = false;

void initialize_mock_arduino() {
    if (!has_initialized_mock_arduino) {
        ftime(&t_start);
        struct timeval tv_start;
        gettimeofday(&tv_start, NULL);

        tv_start_unsigned = 1000000 * tv_start.tv_sec + tv_start.tv_usec;
        has_initialized_mock_arduino = true;
    }
}

myyieldfn yield_impl = NULL;
void yield()
{
    if (yield_impl)
        yield_impl();
    else
        usleep(1000);
}

void __disable_irq() {}
void __enable_irq() {}

extern void setup();
extern void loop();

int main(){
    initialize_mock_arduino();
    setup();
    while (true) {
        loop();
    }
}
