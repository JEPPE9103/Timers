#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Definitioner av konstanter och variabler
#define LED_PIN 3
#define TIMER1_PRESCALER 8
#define TIMER1_COMPARE_VALUE 15625 // För 200 ms period

volatile uint16_t timer1_compare_value = TIMER1_COMPARE_VALUE;
volatile uint8_t led_intensity = 255; // Initial LED intensity (max)

// Funktionsprototyper
void setup();
void loop();
void timer1_compare_a_isr();
void adc_init();
void adc_start_conversion();
uint16_t adc_read_result();
void command_parser();
void uart_init();
char uart_read();
void set_pwm_intensity(uint8_t intensity);

// Huvudfunktion
int main() {
  setup();
  while (1) {
    loop();
  }
  return 0;
}

// Setup-funktion
void setup() {
  // Konfigurera GPIO för LED
  DDRD |= (1 << LED_PIN);

  // Konfigurera Timer1 för att styra LED-blinkfrekvens
  TCCR1B |= (1 << WGM12); // CTC mode
  TIMSK1 |= (1 << OCIE1A); // Enable compare match A interrupt
  OCR1A = TIMER1_COMPARE_VALUE;
  TCCR1B |= (1 << CS11); // Set prescaler to 8

  // Aktivera Timer2 för PWM
  TCCR2A |= (1 << WGM21) | (1 << WGM20); // Fast PWM mode
  TCCR2A |= (1 << COM2B1) | (1 << WGM22); // Non-inverted PWM
  TCCR2B |= (1 << CS21); // Set prescaler to 8

  // Starta Timer1
  TCCR1B |= (1 << CS10); // Start Timer1
  sei(); // Enable global interrupts

  // Initiera UART
  uart_init();
}

// Loop-funktion
void loop() {
  // Läs av ADC och skriv ut till serieporten (Deluppgift 2)
  adc_start_conversion();
  uint16_t adc_value = adc_read_result();
  float voltage = (adc_value * 5.0) / 1023.0;

  // Styr LED-blinkfrekvens med ADC-värde (Deluppgift 2)
  if (voltage > 4.5) {
    // Blinkfrekvens 100 ms
    timer1_compare_value = 7812;
  } else if (voltage > 4.0) {
    // Blinkfrekvens 200 ms
    timer1_compare_value = 15625;
  } else if (voltage > 3.0) {
    // Blinkfrekvens 500 ms
    timer1_compare_value = 31250;
  } else if (voltage > 2.0) {
    // Blinkfrekvens 1000 ms
    timer1_compare_value = 62500;
  } else {
    // Fast sken
    timer1_compare_value = 0;
    set_pwm_intensity(led_intensity); // Använd PWM för att styra lysdiodens intensitet
  }

  // Deluppgift 3: Kommandotolk för att ändra LED-effekt och blinkfrekvens
  command_parser();

  // Fördröjning för att inte blockera loopen
  _delay_ms(1000);
}

// Timer1 compare A interrupt
ISR(TIMER1_COMPA_vect) {
  // Toggla LED-status
  PORTD ^= (1 << LED_PIN);
}

// ADC-funktioner
void adc_init() {
  // Sätt ADC-referens till AVcc
  ADMUX |= (1 << REFS0);

  // Sätt prescaler till 128
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

  // Aktivera ADC
  ADCSRA |= (1 << ADEN);
}

void adc_start_conversion() {
  // Starta en ADC-konvertering
  ADCSRA |= (1 << ADSC);

  // Vänta tills konverteringen är klar
  while (ADCSRA & (1 << ADSC));
}

uint16_t adc_read_result() {
  // Läs av ADC-resultatet
  return (ADCL | (ADCH << 8));
}

// UART-funktioner
void uart_init() {
  // Sätt baudrate till 9600
  UBRR0H = (unsigned char)(103 >> 8);
  UBRR0L = (unsigned char)103;
  
  // Aktivera mottagare och sändare
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);
  
  // Ställ in frame format: 8data, 1 stop bit
  UCSR0C = (3 << UCSZ00);
}

char uart_read() {
  // Vänta på data som ska tas emot
  while (!(UCSR0A & (1 << RXC0)));
  
  // Returnera den mottagna datan
  return UDR0;
}

// Funktion för att sätta PWM-intensitet
void set_pwm_intensity(uint8_t intensity) {
  OCR2B = intensity;
}

// Kommandotolk för att ändra LED-effekt och blinkfrekvens
void command_parser() {
  // Läs inkommande tecken från UART
  char command = uart_read();
  
  // Implementera tolkning av kommandon här
  // Exempel: ledpowerfreq 100 200
  // där första siffran är effekten (0-255) och andra siffran är en på/av tid i millisekunder (200 - 5000)
}