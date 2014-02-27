// User settings
#define GAIN_DEFAULT_P 0.5
#define GAIN_DEFAULT_I 0
#define GAIN_DEFAULT_D 0

// Debug options
#define DEBUG_PRINT_LOOP_TIME false

// Variables
unsigned long elapsed;
unsigned long loopStartTime;
float orientationCurrent;
float orientationPrevious;
float orientationIntegrated;
bool gotData = false;
bool running = true;

struct gain
{
  float p;
  float i;
  float d;
} gainCurrent, gainDefault;

void setup()
{
  gainDefault.p = GAIN_DEFAULT_P;
  gainDefault.i = GAIN_DEFAULT_I;
  gainDefault.d = GAIN_DEFAULT_D;

  inputSetup();
  motorSetup();

  Serial.begin(57600);
}

void loop()
{
  loopStartTime = millis();
  
  updateInput();
  
  gotData = updateOrientation();
  
  if (gotData)
  {
    updateGain();
    updateMotorSpeed(updateSpeed());
  }

#if DEBUG_PRINT_LOOP_TIME
  Serial.print("Loop time: ");
  Serial.println(millis() - loopStartTime);
#endif
}

bool updateOrientation()
{
  if (Serial.available() < 24)
  {
    return false;
  }

  orientationPrevious = orientationCurrent;

  Serial.readBytesUntil('=', NULL, 24);
  Serial.parseFloat();
  Serial.read();
  Serial.parseFloat();
  Serial.read();
  
  orientationCurrent = Serial.parseFloat();

  return true;
}

void updateGain()
{
  gainCurrent.p = gainDefault.p;
  gainCurrent.i = gainDefault.i;
  gainCurrent.d = gainDefault.d;
}

float updateSpeed()
{
  float speed = 0;

  speed += updateProportional();
  speed += updateIntegral();
  speed += updateDerivative();
  
  return speed;
}

int updateProportional()
{
  int angle = orientationCurrent * 100;
  return map(angle, -7500, -10500, -256, 255);
}

float updateIntegral()
{
  orientationIntegrated += orientationCurrent;
  return orientationIntegrated * gainCurrent.i;
}

float updateDerivative()
{
  return (orientationCurrent - orientationPrevious) * gainCurrent.d;
}

