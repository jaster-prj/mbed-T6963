#ifndef T6963DATA_h
#define T6963DATA_h

#include "mbed.h"
#include "../GPIOLib/inc/PortInOutInterface.h"
#include "../GPIOLib/inc/DigitalInOutInterface.h"

class T6963Data{
public:
    T6963Data(PortInOutInterface *port, int mask);
    T6963Data(DigitalInOutInterface *d0, DigitalInOutInterface *d1, DigitalInOutInterface *d2, DigitalInOutInterface *d3, DigitalInOutInterface *d4, DigitalInOutInterface *d5, DigitalInOutInterface *d6, DigitalInOutInterface *d7);

    void write(int value);

    void set(int mask);

    void reset(int mask);

    int read();

    void output();

    void input();

private:
    PortInOutInterface *_port;
    int _port_mask;
    DigitalInOutInterface *_pins[8];
    bool _use_port;
};

#endif