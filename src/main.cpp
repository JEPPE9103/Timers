#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "timer.h"
#include "command.h"

int main() {
    // Konfigurera GPIO för LED (pinne 3)
    DDRD |= (1 << PD3);

    // Skapa instanser av UART, Timer och CommandParser
    UART uart;
    Timer timer;
    CommandParser commandParser(&timer);

    // Initiera UART och Timer
    uart.init();
    timer.init();

    // Aktivera globala interrupts
    sei();

    while (1) {
        // Deluppgift 2: Läs och skriv ut ADC-värde varje sekund
        uint16_t adcValue = readADC();
        float voltage = (adcValue * 5.0) / 1023.0;
        uart.sendString("ADC Value: ");
        uart.sendInteger(adcValue);
        uart.sendString("\tVoltage: ");
        uart.sendFloat(voltage);
        uart.sendString("V\n");

        // Deluppgift 3: Kommandotolk för att ändra LED-effekt och blinkfrekvens
        commandParser.parseCommand();

        // Fördröjning för att inte blockera loopen
        _delay_ms(1000);
    }

    return 0;
}

// Funktion för att läsa ADC-värdet från pinne A0
uint16_t readADC() {
    // Konfigurera ADC för pinne A0
    ADMUX = (1 << REFS0); // AVcc som referens
    ADMUX |= 0x00; // Välj ADC0 (pinne A0)
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Aktivera ADC och sätt prescaler på 128

    // Starta ADC-konvertering
    ADCSRA |= (1 << ADSC);

    // Vänta på att konvertering är klar
    while (ADCSRA & (1 << ADSC));

    // Returnera ADC-värdet
    return ADC;
}
