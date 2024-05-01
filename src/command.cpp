#include "command.h"
#include "uart.h"
#include <string.h> // Lägg till detta för att inkludera strcmp
#include <stdint.h>
#include <stdio.h>

CommandParser::CommandParser(Timer* t) : timer(t) {}

void CommandParser::parseCommand() {
    UART uart;

    // Läs inkommande tecken från UART
    char command[20];
    uart.readString(command);

    if (strcmp(command, "ledpowerfreq") == 0) {
        // Läs in effekten (0-255) och tiden (200-5000 ms) från kommandot
        uint8_t led_intensity;
        uint16_t time_ms;
        sscanf(command, "ledpowerfreq %hhu %hu", &led_intensity, &time_ms);

        // Utför åtgärder baserat på kommandot
        if (time_ms >= 200 && time_ms <= 5000) {
            uint16_t timer_value = time_ms * 2;
            timer->configureTimer1(timer_value);
            timer->setPWMIntensity(led_intensity); // Sätt LED-intensitet med PWM
        }
    }
}
