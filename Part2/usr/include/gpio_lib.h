#ifndef GPIO_H
#define GPIO_H

void gpioInitPtrs();

// Sets GPIO N to function
void gpioSetMode(unsigned int, unsigned int);

// Reads and get the GPIOs's current Mode 
void getGpioMode(unsigned int);

// Writes to GPIO N ( N = Position starting from 0)
void gpioWrite(unsigned char, unsigned int);

#endif
