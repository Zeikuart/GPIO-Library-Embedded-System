#include <gpio_lib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    gpioInitPtrs();

    // Sets GPIO2 to output
    gpioSetMode(2, 1);

    // Sets ALL GPIOS to output
    gpioSetModeAll(1);

    // Print GPIO N
    getGpioMode(2);

    // Print ALL GPIOS
    getAllGpioMode();

    // toggle GPIO2
    gpioWrite(1, 2);
    usleep(1000000);
    gpioWrite(0, 2);

    // Toggle all GPIOS
    gpioWriteAll(1);
    usleep(1000000);
    gpioWriteAll(0);

    return 0;
}