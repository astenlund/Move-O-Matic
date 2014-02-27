#include <PinChangeInt.h>
#include <Timer.h>

// Pin configuration
#define STOP_BUTTON_PIN 2

// General settings
#define DEBOUNCING_TIME 10

// Variables
Timer t;

void inputSetup()
{
  pinMode(STOP_BUTTON_PIN, INPUT);
  digitalWrite(STOP_BUTTON_PIN, HIGH);
  attachInterrupt(0, stopButtonISR, FALLING);
}

void updateInput()
{
  t.update();
}

void stopButtonISR()
{
  static unsigned long stopButtonTime;
  unsigned long now = millis();

  if (now - stopButtonTime > DEBOUNCING_TIME)
  {
    t.after(DEBOUNCING_TIME, doReadStopButton);
    stopButtonTime = now;
  }
}

void doReadStopButton()
{
  if (digitalRead(STOP_BUTTON_PIN) == LOW)
  {
    stopMotors();
  }
}

