#include "mbed.h"
#include "../inc/T6963Cmd.h"

T6963Cmd::T6963Cmd(PortOutInterface *port, int cd_mask, int wr_mask, int rd_mask, int ce_mask, int fs_mask, int rst_mask) {
    _port = port;
    _port_mask[0] = cd_mask;
    _port_mask[1] = wr_mask;
    _port_mask[2] = rd_mask;
    _port_mask[3] = ce_mask;
    _port_mask[4] = fs_mask;
    _port_mask[5] = rst_mask;
    _use_port = true;
}

T6963Cmd::T6963Cmd(DigitalOutInterface *cd, DigitalOutInterface *wr, DigitalOutInterface *rd, DigitalOutInterface *ce, DigitalOutInterface *fs, DigitalOutInterface *rst) {
    _pins[0] = cd;
    _pins[1] = wr;
    _pins[2] = rd;
    _pins[3] = ce;
    _pins[4] = fs;
    _pins[5] = rst;
    _use_port = false;
}

void T6963Cmd::write(int value) {
    if (_use_port) {
        _port->write(value);
    }else {
        for(int i=0;i<6;i++){
            _pins[i]->write(0x01 & value>>i);
        }
    }
}

void T6963Cmd::set(int mask) {
    if (_use_port) {
        _port->write(_port->read() | mask);
    }else {
        for(int i=0;i<6;i++){
            if (0x01 & mask>>i) {
                _pins[i]->write(1);
            }
        }
    }
}

void T6963Cmd::reset(int mask) {
    if (_use_port) {
        _port->write(_port->read() & ~mask);
    }else {
        for(int i=0;i<6;i++){
            if (0x01 & mask>>i) {
                _pins[i]->write(0);
            }
        }
    }
}