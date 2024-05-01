#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define LED_PIN 3

void Timer::init() {
    // Konfigurera Timer1 för att styra LED-blinkfrekvens
    TCCR1B |= (1 << WGM12); // CTC mode
    TIMSK1 |= (1 << OCIE1A); // Enable compare match A interrupt
    TCCR1B |= (1 << CS11); // Set prescaler to 8
    sei(); // Enable global interrupts
}

void Timer::setPWMIntensity(uint8_t intensity) {
    OCR2B = intensity;
}

ISR(TIMER1_COMPA_vect) {
    // Toggla LED-status
    PORTD ^= (1 << LED_PIN);
}
