#include <TimerOne.h>

// tempature sensor pin
#define SENSOR_PIN A0

float gtemperatureC = 0;
static bool led_is_on = false;
volatile unsigned int gtimerCnt = 0;

/***************************/
/* LM35 Temperature Sensor value Reading ***/
void temperatureRead() {
  // Get a reading from the temperature sensor:
  int reading = analogRead(SENSOR_PIN);
  // Convert the reading into voltage:
  float voltage = reading * (5000 / 1024.0);
  // Convert the voltage into the temperature in degree Celsius:
  gtemperatureC = voltage / 10;
}

void blinkLed(void) {
  // led toggleing 13th pin for led
  digitalWrite(LED_BUILTIN, led_is_on);
  // Change our led state
  led_is_on = !led_is_on;
}

void Timer_Init() {
  // Initialize timer with 50mse second period
  Timer1.initialize(50000);
  Timer1.attachInterrupt(LED_TMR_Blink);
}

void setup() {
  // initialize digital pin LED_BUILTIN -- 13pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  // initialize timer module for blink
  Timer_Init();
}

/*
 * Application start here
 */

void loop() {
  // read temp sensor value
  temperatureRead();

  if (gtemperatureC > 30) {
    // tempature is more than 30c
    if (gtimerCnt > 5) {
      // blink led for every 250msec
      blinkLed();
      gtimerCnt = 0;
    } else {
      // do nothing
    }
  } else {
    // tempature is less than 30c

    if (gtimerCnt > 10) {
      // blink led for every 500 msec
      blinkLed();
      gtimerCnt = 0;
    } else {
      // do nothing
    }
  }
}

void LED_TMR_Blink() { gtimerCnt++; }
