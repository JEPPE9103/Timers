#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>

class Timer {
public:
    void init();
    void setPWMIntensity(uint8_t intensity);
    void configureTimer1(uint16_t compareValue);
};

#endif // TIMER_H
