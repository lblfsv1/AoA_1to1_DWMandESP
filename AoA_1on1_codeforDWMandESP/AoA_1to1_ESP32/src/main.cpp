#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
//#include <cmath.h>

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);


void setup()
{
    Serial.begin(115200);
    Serial2.begin(115200, SERIAL_8N1, 18, 17);
    Serial3.begin(115200, SERIAL_8N1, 44, 43);

    Wire.begin(8, 9);

    if (!bno.begin()) {
        Serial.println("BNO055 not found");
        while (1);
    }

    delay(1000);
    bno.setExtCrystalUse(true);
}


int commands[] = {40001, 40002};

String data[4];

// Distance between A1 and A2
float LA = 1;

void loop() {

    // Send poll from A1 to B1 and B2
    for (int i = 0; i < 2; i++) {

        Serial2.println(commands[i]);

        while (!(Serial2.available())) {
        };

        String received = Serial2.readStringUntil('\n');

        data[i] = received; // no \n
    }

    // Send poll from A2 to B1 and B2
    for (int i = 0; i < 2; i++) {

        Serial3.println(commands[i]);

        while (!(Serial3.available())) {
        };

        String received = Serial3.readStringUntil('\n');

        data[i + 2] = received; // no \n
    }

    // Output four distance data and heading on the terminal
    Serial.println("--------------------------------");
    Serial.println("Four distance and heading data:");
    for (int i = 0; i < 4; i++) {
        Serial.println(data[i]);
    }
    Serial.println("--------------------------------");

    // Calculate the coordinate
    // float y1 = ((data[2])*(data[2]) - (data[0])*(data[0]) - LA*LA) / (2*LA);
    // float x11 = sqrt(data[0]*data[0] - y1*y1);
    // float x12 = -x11;

    // float y2 = ((data[3])*(data[3]) - (data[1])*(data[1]) - LA*LA) / (2*LA);
    // float x21 = sqrt(data[2]*data[2] - y2*y2);
    // float x22 = -x21;

    // Serial.print(x11);
    // Serial.print(",");
    // Serial.print(y1);
    // Serial.print(",");
    // Serial.print(x12);
    // Serial.print(",");
    // Serial.print(y1);
    // Serial.print(",");
    // Serial.print(x21);
    // Serial.print(",");
    // Serial.print(y2);
    // Serial.print(",");
    // Serial.print(x22);
    // Serial.print(",");
    // Serial.println(y2);

}