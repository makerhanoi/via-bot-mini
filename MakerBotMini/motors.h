#define MOTOR_FREQ 5000 // PWM MOTOR_FREQ for DC motor should be within 5-20kHz
 
// Motors pin number
#define MOTOR1_A 12 
#define MOTOR1_B 14
 
#define MOTOR2_A 4
#define MOTOR2_B 13
 
#define PWM_CHANNEL1 0
#define PWM_CHANNEL2 1
 
#define PWM_CHANNEL3 2
#define PWM_CHANNEL4 3
 
#define PWM_RES 8 // Resolution of pwm signal here is set to 8 bit, resolution can be set up to 15 bit with esp32

#define MIN_PWM 0
#define MAX_PWM 255
 

void initMotors() {
  ledcSetup(PWM_CHANNEL1, MOTOR_FREQ, PWM_RES);
  ledcSetup(PWM_CHANNEL2, MOTOR_FREQ, PWM_RES);
  ledcSetup(PWM_CHANNEL3, MOTOR_FREQ, PWM_RES);
  ledcSetup(PWM_CHANNEL4, MOTOR_FREQ, PWM_RES);
 // attatch motors pin to pwm channels
  ledcAttachPin(MOTOR1_A, PWM_CHANNEL1);
  ledcAttachPin(MOTOR1_B, PWM_CHANNEL2);
 
  ledcAttachPin(MOTOR2_A, PWM_CHANNEL3);
  ledcAttachPin(MOTOR2_B, PWM_CHANNEL4);
}


void stop() {
  ledcWrite(PWM_CHANNEL1, 0);
  ledcWrite(PWM_CHANNEL2, 0);
  ledcWrite(PWM_CHANNEL3, 0);
  ledcWrite(PWM_CHANNEL4, 0);
}


/**
 * Set speed and direction for 2 motors
 * 
 * @param left_motor_speed: speed with direction for left motor. Range from -1 to 1. 1: max speed forward, -1: max speed reverse
 * @param right_motor_speed: speed with direction for right motor. Range from -1 to 1. 1: max speed forward, -1: max speed reverse
 */
void setSpeed(float left_motor_speed, float right_motor_speed) {

  int c1 = 0, c2 = 0, c3 = 0, c4 = 0;

  if (left_motor_speed > 0) {
    c1 = min(MIN_PWM, max(int(abs(left_motor_speed) * MAX_PWM), MAX_PWM));
  } else {
    c2 = min(MIN_PWM, max(int(abs(left_motor_speed) * MAX_PWM), MAX_PWM));
  }

  if (right_motor_speed > 0) {
    c3 = min(MIN_PWM, max(int(abs(right_motor_speed) * MAX_PWM), MAX_PWM));
  } else {
    c4 = min(MIN_PWM, max(int(abs(right_motor_speed) * MAX_PWM), MAX_PWM));
  }
  
  ledcWrite(PWM_CHANNEL1, c1);
  ledcWrite(PWM_CHANNEL2, c2);
  ledcWrite(PWM_CHANNEL3, c3);
  ledcWrite(PWM_CHANNEL4, c4);

}
