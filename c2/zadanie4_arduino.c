#include <DHT.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

// Define sensor pins and types
#define DHTPIN 2
#define DHTTYPE DHT22
#define LIGHT_SENSOR_PIN A0

DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

void setup()
{
    Serial.begin(9600);
    dht.begin();
    if (!bmp.begin())
    {
        Serial.print("No BMP085 sensor detected.");
        while (1)
            ;
    }
}

void loop()
{
    if (Serial.available() > 0)
    {
        char command = Serial.read();
        switch (command)
        {
        case 'H':
            Serial.println(getHumidity());
            break;
        case 'T':
            Serial.println(getTemperature());
            break;
        case 'L':
            Serial.println(getLightLevel());
            break;
        case 'P':
            Serial.println(getPressure());
            break;
        case 'A':
            Serial.print("H:");
            Serial.print(getHumidity());
            Serial.print(" T:");
            Serial.print(getTemperature());
            Serial.print(" L:");
            Serial.print(getLightLevel());
            Serial.print(" P:");
            Serial.println(getPressure());
            break;
        }
    }
}

float getHumidity()
{
    return dht.readHumidity();
}

float getTemperature()
{
    return dht.readTemperature();
}

int getLightLevel()
{
    return analogRead(LIGHT_SENSOR_PIN);
}

float getPressure()
{
    sensors_event_t event;
    bmp.getEvent(&event);
    if (event.pressure)
    {
        return event.pressure;
    }
    else
    {
        return -1.0; // Error value
    }
}
