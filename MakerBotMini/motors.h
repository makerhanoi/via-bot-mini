#include <stdio.h>
#include "driver/ledc.h"
#include "esp_err.h"

#define MOTOR_FREQ 5000 // PWM MOTOR_FREQ for DC motor should be within 5-20kHz

#define MOTOR1_A 12 
#define MOTOR1_B 14
 
#define MOTOR2_A 15
#define MOTOR2_B 13
 
#define PWM_CHANNEL1 LEDC_CHANNEL_2
#define PWM_CHANNEL2 LEDC_CHANNEL_3
 
#define PWM_CHANNEL3 LEDC_CHANNEL_4
#define PWM_CHANNEL4 LEDC_CHANNEL_5
 
#define PWM_RES LEDC_TIMER_8_BIT // Resolution of pwm signal here is set to 8 bit, resolution can be set up to 15 bit with esp32

#define MIN_PWM 0
#define MAX_PWM 255
 

void initMotors() {

  ledc_channel_config_t ledc_timer1;
  ledc_timer1.channel = PWM_CHANNEL1;
  ledc_timer1.duty       = 0;
  ledc_timer1.gpio_num   = MOTOR1_A;
  ledc_timer1.speed_mode = LEDC_HIGH_SPEED_MODE;
  ledc_timer1.hpoint     = 0;
  ledc_timer1.timer_sel  = LEDC_TIMER_2;
  ledc_channel_config(&ledc_timer1);

  ledc_channel_config_t ledc_timer2;
  ledc_timer2.channel    = PWM_CHANNEL2;
  ledc_timer2.duty       = 0;
  ledc_timer2.gpio_num   = MOTOR1_B;
  ledc_timer2.speed_mode = LEDC_HIGH_SPEED_MODE;
  ledc_timer2.hpoint     = 0;
  ledc_timer2.timer_sel  = LEDC_TIMER_2;
  ledc_channel_config(&ledc_timer2);

  ledc_channel_config_t ledc_timer3;
  ledc_timer3.channel    = PWM_CHANNEL3;
  ledc_timer3.duty       = 0;
  ledc_timer3.gpio_num   = MOTOR2_A;
  ledc_timer3.speed_mode = LEDC_HIGH_SPEED_MODE;
  ledc_timer3.hpoint     = 0;
  ledc_timer3.timer_sel  = LEDC_TIMER_2;
  ledc_channel_config(&ledc_timer3);

  ledc_channel_config_t ledc_timer4;
  ledc_timer4.channel    = PWM_CHANNEL4;
  ledc_timer4.duty       = 0;
  ledc_timer4.gpio_num   = MOTOR2_B;
  ledc_timer4.speed_mode = LEDC_HIGH_SPEED_MODE;
  ledc_timer4.hpoint     = 0;
  ledc_timer4.timer_sel  = LEDC_TIMER_2;
  ledc_channel_config(&ledc_timer4);

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
