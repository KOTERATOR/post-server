#pragma once

class Sensor
{
protected:
    String mac = "";
public:
    Sensor(String mac)
    {
        this->mac = mac;
    }

    String getMAC() { return mac; }
     
};