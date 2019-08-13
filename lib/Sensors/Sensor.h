#pragma once

#include "IPAddress.h"

class Sensor
{
protected:
    IPAddress ip;
    int _id = 0;
public:
    Sensor(IPAddress ip, int id)
    {
        this->ip = ip;
        _id = id;
    }

    int getID() { return _id; }
    IPAddress getIP() { return ip; }

    void requestData();
     
};