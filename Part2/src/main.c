#include <gpio_lib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    gpioInitPtrs();

    // Sets GPIO2 to output
    gpioSetMode(2, 1);

    getGpioMode(2);

    // toggle GPIO2
    gpioWrite(1, 2);
    usleep(1000000);
    gpioWrite(0, 2);

    return 0;
}