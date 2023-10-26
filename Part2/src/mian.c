#include <gpio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    gpioInitPtrs();
    gpioSetMode();
    // toggle GPIO2
    gpioWrite(1);
    usleep(1000000);
    gpioWrite(0);
    return 0;
}