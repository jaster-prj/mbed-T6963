#ifndef T6963CMD_h
#define T6963CMD_h

#include "mbed.h"
#include "../GPIOLib/inc/PortOutInterface.h"
#include "../GPIOLib/inc/DigitalOutInterface.h"

#define T6963_CMD_CD  0x1
#define T6963_CMD_WR  0x2
#define T6963_CMD_RD  0x4
#define T6963_CMD_CE  0x8
#define T6963_CMD_FS  0x10
#define T6963_CMD_RST 0x20

class T6963Cmd{
public:
    T6963Cmd(PortOutInterface *port, int cd_mask, int wr_mask, int rd_mask, int ce_mask, int fs_mask, int rst_mask);
    T6963Cmd(DigitalOutInterface *cd, DigitalOutInterface *wr, DigitalOutInterface *rd, DigitalOutInterface *ce, DigitalOutInterface *fs, DigitalOutInterface *rst);

    void write(int value);
    void set(int mask);
    void reset(int mask);

private:
    PortOutInterface *_port;
    int _port_mask[6];
    DigitalOutInterface *_pins[6];
    bool _use_port;
};

#endif