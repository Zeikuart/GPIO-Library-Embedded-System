#ifndef GPIO_H
#define GPIO_H

void gpioInitPtrs();

// Sets GPIO N to function
void gpioSetMode(unsigned int, unsigned int);

// Sets ALL GPIOS to a Function
void gpioSetModeAll(unsigned int);

// Reads and get the GPIOs's current Mode 
void getGpioMode(unsigned int);

// Reads and gets all the GPIOS's current mode
void getAllGpioMode();

// Writes to GPIO N ( N = Position starting from 0)
void gpioWrite(unsigned char, unsigned int);

// Writes to all of the GPIOS
void gpioWriteAll(unsigned char);

#endif
