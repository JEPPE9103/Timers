#ifndef UART_H
#define UART_H

class UART {
public:
    void init();
    char read();
    void sendChar(char c);
    void sendString(const char* str);
    void sendInteger(int num);
    void sendFloat(float num, int decimalPlaces = 2);
};

#endif // UART_H
