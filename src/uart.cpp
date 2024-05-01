#include "uart.h"
#include <avr/io.h>
#include <util/delay.h>

void UART::init() {
    // Sätt baudrate till 9600
    UBRR0H = (unsigned char)(103 >> 8);
    UBRR0L = (unsigned char)103;

    // Aktivera mottagare och sändare
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    // Ställ in frame format: 8data, 1 stop bit
    UCSR0C = (3 << UCSZ00);
}

char UART::read() {
    // Vänta på data som ska tas emot
    while (!(UCSR0A & (1 << RXC0)));

    // Returnera den mottagna datan
    return UDR0;
}

void UART::sendChar(char c) {
    // Vänta på att sändarregistret ska bli ledigt
    while (!(UCSR0A & (1 << UDRE0)));

    // Skicka tecknet
    UDR0 = c;
}

void UART::sendString(const char* str) {
    // Skicka varje tecken i strängen tills nolltecknet (avslutningen) nås
    while (*str != '\0') {
        sendChar(*str);
        str++;
    }
}

// Funktion för att konvertera heltal till sträng och skicka över UART
void UART::sendInteger(int num) {
    // Skapa en temporär buffert för att lagra det konverterade heltalsvärdet
    char buffer[20];
    uint8_t i = 0;
    bool isNegative = false;

    // Hantera negativa heltal
    if (num < 0) {
        isNegative = true;
        num = -num; // Gör om till positivt heltal för konvertering
    }

    // Konvertera heltal till sträng genom att arbeta baklänges
    do {
        buffer[i++] = '0' + (num % 10); // Lägg till siffran i bufferten
        num /= 10; // Gå vidare till nästa siffra
    } while (num > 0);

    // Lägg till minus-tecken om det är ett negativt heltal
    if (isNegative) {
        buffer[i++] = '-';
    }

    // Skicka strängen över UART i omvänd ordning
    while (i > 0) {
        sendChar(buffer[--i]);
    }
}

void UART::sendFloat(float num, int decimalPlaces) {
    // Implementera en egen metod för att hantera flyttal om det behövs
    // Exempel: Skicka heltalsdelen och decimaldelen separat som strängar
    // Beroende på dina behov och begränsningar på AVR-plattformen
}

void UART::readString(char* buffer) {
    uint8_t i = 0;
    char c;
    while ((c = read()) != '\n') {
        buffer[i++] = c;
    }
    buffer[i] = '\0'; // Avsluta strängen med nolltecken
}
