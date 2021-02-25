

#include "motors.h"
#include "camera.h"
#include "wifi.h"



void setup() {

  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();

  initCamera();
  initMotors();
  initWifi();

  startCameraServer();

}

void loop() {
  delay(2000);
  Serial.println("Running");
}
