#include "../inc/T6963Data.h"

T6963Data::T6963Data(PortInOutInterface *port, int mask) {
    _port = port;
    _port_mask = mask;
    _use_port = true;
}

T6963Data::T6963Data(DigitalInOutInterface *d0, DigitalInOutInterface *d1, DigitalInOutInterface *d2, DigitalInOutInterface *d3, DigitalInOutInterface *d4, DigitalInOutInterface *d5, DigitalInOutInterface *d6, DigitalInOutInterface *d7) {
    _pins[0] = d0;
    _pins[1] = d1;
    _pins[2] = d2;
    _pins[3] = d3;
    _pins[4] = d4;
    _pins[5] = d5;
    _pins[6] = d6;
    _pins[7] = d7;
    _use_port = false;
}

void T6963Data::write(int value) {
    if (_use_port) {
        _port->write(value);
    }else {
        for(int i=0;i<8;i++){
            _pins[i]->write(0x01 & value>>i);
        }
    }
}

void T6963Data::set(int mask) {
    if (_use_port) {
        _port->write(_port->read() | mask);
    }else {
        for(int i=0;i<8;i++){
            if (0x01 & mask>>i) {
                _pins[i]->write(1);
            }
        }
    }
}

void T6963Data::reset(int mask) {
    if (_use_port) {
        _port->write(_port->read() & ~mask);
    }else {
        for(int i=0;i<8;i++){
            if (0x01 & mask>>i) {
                _pins[i]->write(0);
            }
        }
    }
}

int T6963Data::read() {
    int value = 0;
    if (_use_port) {
        return _port->read();
    }else{
        for(int i=0;i<8;i++){
            value |= _pins[i]->read()<<i;
        }
        return value;
    }
}

void T6963Data::output() {
    if (_use_port) {
        _port->output();
    }else{
        for(int i=0;i<8;i++){
            _pins[i]->output();
        }
    }
}

void T6963Data::input() {
    if (_use_port) {
        _port->input();
    }else{
        for(int i=0;i<8;i++){
            _pins[i]->input();
        }
    }
}
