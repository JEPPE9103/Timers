#include "command.h"
#include "uart.h"
#include <stdint.h>

CommandParser::CommandParser(Timer* t) : timer(t) {}

void CommandParser::parseCommand() {
    UART uart;

    // Läs inkommande tecken från UART
    char command = uart.read();

    if (command == 'l') {
        // Läs in effekten (0-255)
        uint8_t led_intensity = uart.read() - '0';

        // Läs in tiden (200-5000 ms)
        char temp = uart.read(); // Läs och kasta bort mellanslag
        uint16_t time_ms = 0;
        while (temp != ' ') {
            time_ms = time_ms * 10 + (temp - '0');
            temp = uart.read();
        }

        // Utför åtgärder baserat på kommandot
        if (time_ms >= 200 && time_ms <= 5000) {
            uint16_t timer_value = time_ms * 2;
            timer->configureTimer1(timer_value);
            timer->setPWMIntensity(led_intensity); // Sätt LED-intensitet med PWM
        }
    }
}
