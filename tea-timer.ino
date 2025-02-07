#include <Arduino.h>
#include <TM1637Display.h>

#define CLK 19
#define DIO 18

#define SENSOR_PIN 5

TM1637Display display(CLK, DIO);

void setup()
{
    display.setBrightness(7);
    pinMode(SENSOR_PIN, INPUT);
}

int time_val = 0;

uint64_t timer = esp_timer_get_time();
uint64_t pretime = esp_timer_get_time();

void loop()
{
    int state = digitalRead(SENSOR_PIN);

    if (state == true) {
        time_val = 0;
    }

    if (timer - pretime >= 1000000) {
        int time_min = time_val / 60;
        int time_sec = time_val % 60;
        display.showNumberDecEx(time_min * 100 + time_sec, 0b01000000);

        time_val++;
        pretime = timer;
    }

    timer = esp_timer_get_time();
}
