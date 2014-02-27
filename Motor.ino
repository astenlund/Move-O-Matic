// Enums
#define M_DIR_FORWARD 0
#define M_DIR_BACKWARD 1

// Pin configuration
#define M1_PWM_PIN 3
#define M2_PWM_PIN 11
#define M1_DIR_PIN 12
#define M2_DIR_PIN 13

void motorSetup()
{
  pinMode(M1_PWM_PIN, OUTPUT);
  pinMode(M2_PWM_PIN, OUTPUT);
  pinMode(M1_DIR_PIN, OUTPUT);
  pinMode(M2_DIR_PIN, OUTPUT);

  digitalWrite(M1_PWM_PIN, 0);
  digitalWrite(M2_PWM_PIN, 0);
  digitalWrite(M1_DIR_PIN, HIGH);
  digitalWrite(M1_DIR_PIN, LOW);
}

void updateMotorSpeed(float speed)
{
  if (running == false)
  {
    return;
  }
  
  int direction = speed < 0 ? M_DIR_BACKWARD : M_DIR_FORWARD;

  speed = speed < 0 ? -speed : speed;
  speed = speed > 255 ? 255 : speed;
  
  switch (direction)
  {
    case M_DIR_FORWARD:
      digitalWrite(M1_DIR_PIN, HIGH);
      digitalWrite(M2_DIR_PIN, LOW);
      break;
    case M_DIR_BACKWARD:
      digitalWrite(M1_DIR_PIN, LOW);
      digitalWrite(M2_DIR_PIN, HIGH);
  };

  analogWrite(M1_PWM_PIN, speed);
  analogWrite(M2_PWM_PIN, speed);
}

void stopMotors()
{
  analogWrite(M1_PWM_PIN, 0);
  analogWrite(M2_PWM_PIN, 0);
  running = false;
}

