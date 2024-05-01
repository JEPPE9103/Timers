#ifndef COMMAND_H
#define COMMAND_H

#include "timer.h"

class CommandParser {
private:
    Timer* timer; // Pekare till Timer-objekt

public:
    CommandParser(Timer* t); // Konstruktor för att ange Timer-objekt
    void parseCommand(); // Funktion för att tolka kommandon
};

#endif // COMMAND_H
