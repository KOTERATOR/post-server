#pragma once
#include "Sensor.h"
#include "List.h"

class TemperatureSensor : public Sensor
{
private:
    float temp = 0.0f;
public:
    TemperatureSensor(String mac) : Sensor(mac)
    {
        
    }
    float getTemp() { return temp; }
    void setTemp(float temp) { this->temp = temp; }
};