#include <gpio.h>
#include <sys/mman.h> //mmap
#include <err.h>      //error handling
#include <fcntl.h>    //file ops
#include <unistd.h>   //usleep

// Static base
static unsigned GPIO_BASE = 0x3f200000;

// GPIOs Available
unsigned int GPIOS[] = {2, 3, 4, 17, 18, 22, 23, 24};

//** Regs pointers **//

// Reg0 = [GPIO 2, GPIO 3, GPIO 4]
volatile unsigned int *gpfsel0;

// Reg1 = [GPIO 17, GPIO 18, GPIO 22, GPIO 23, GPIO 24]
volatile unsigned int *gpfsel1;

// Setters
volatile unsigned int *gpset0;
volatile unsigned int *gpclr0;



// Initialize pointers: performs memory mapping, exits if mapping fails
void gpioInitPtrs()
{
    int fd = -1;
    // Loading /dev/mem into a file
    if ((fd = open("/dev/mem", O_RDWR, 0)) == -1) {
        err(1, "Error opening /dev/mem");
    }
        
    //** Mapping GPIO base physical address **//

    // Reg0
    gpfsel0 = (unsigned int *)mmap(0, getpagesize(), PROT_WRITE, MAP_SHARED, fd, GPIO_BASE);

    // Reg1
    gpfsel1 = gpfsel0 + 0x1;
    // Check for mapping errors
    if (gpfsel0 == MAP_FAILED) {
        errx(1, "Error during mapping GPIOs");
    }

    // Set regs pointers
    gpset0 = gpfsel0 + 0x7; // offset 0x1C = 0x0 + (4 * 0x7)
    gpclr0 = gpfsel0 + 0xA; // offset 0x28 = 0x0 + (4 * 0xA)
}

// Sets GPIO N to function
void gpioSetMode(unsigned int gpioN, unsigned int function) {

    int foundIndex;
    int valid = 0;

    // If it is a valid GPIO
    for (int i = 0; i < sizeof(GPIOS); i++) {
        
        if (gpioN == GPIOS[i]) {

            // Was found
            foundIndex = i;
            valid = 1;
            break;
        }
    }

    // Validation
    if (function > 7) {
        return;
    }

    // Register 0
    if ((foundIndex < 3) && valid) {

        // 3 bits mask
        unsigned int bitmask = 0x7; // 0000 0111

        // Bits Function
        unsigned int FunctionBits = function & 0x7;

        // Set GPIO N to its respective function
        *gpfsel0 = (*gpfsel0 & ~(bitmask << (gpioN * 3))) | (FunctionBits << (gpioN * 3));
    }

    // Register 1
    if ((3 >= foundIndex < sizeof(GPIOS)) && valid) {

        // 3 bits mask
        unsigned int bitmask = 0x7; // 0000 0111

        // Bits Function
        unsigned int FunctionBits = function & 0x7;

        // Set GPIO N to its respective function
        *gpfsel1 = (*gpfsel1 & ~(bitmask << (gpioN * 3))) | (FunctionBits << (gpioN * 3));
    }
}

// Reads and get the GPIOs's current Mode 
void getGpioMode(unsigned int gpioN) {

    int foundIndex;
    int valid = 0;

    // If it is a valid GPIO
    for (int i = 0; i < sizeof(GPIOS); i++) {
        
        if (gpioN == GPIOS[i]) {

            // Was found
            foundIndex = i;
            valid = 1;
            break;
        }
    }

    // Register 0
    if ((foundIndex < 3) && valid) {

        // Bitmask to extract the bits for the specified GPIO pin (bits 2-0)
        unsigned int bitmask = 0x7; // 0b0000 0111

        // Shift the bitmask to the appropriate position for the specified GPIO pin
        unsigned int shiftedMask = bitmask << (gpioN * 3);

        // Read the current gpfsel0 register value
        unsigned int gpfsel0Value = *gpfsel0;

        // Extract the bits for the specified GPIO pin
        unsigned int functionBits = (gpfsel0Value & shiftedMask) >> (gpioN * 3);

        // Prints the current Mode (input, output or any other function)
        printf("GPIO pin %d function is set to %u\n", gpioN, functionBits);
    }

    // Register 1
    if ((3 >= foundIndex < sizeof(GPIOS)) && valid) {

        // Bitmask to extract the bits for the specified GPIO pin (bits 2-0)
        unsigned int bitmask = 0x7; // 0b0000 0111

        // Shift the bitmask to the appropriate position for the specified GPIO pin
        unsigned int shiftedMask = bitmask << (gpioN * 3);

        // Read the current gpfsel0 register value
        unsigned int gpfsel0Value = *gpfsel1;

        // Extract the bits for the specified GPIO pin
        unsigned int functionBits = (gpfsel0Value & shiftedMask) >> (gpioN * 3);

        // Prints the current Mode (input, output or any other function)
        printf("GPIO pin %d function is set to %u\n", gpioN, functionBits);
    }
    
}

// Writes to GPIO N
void gpioWrite(unsigned char bit) {
    if (bit)
        *gpset0 = 0x4; // sets bit
    else
        *gpclr0 = 0x4; // clears bit
}