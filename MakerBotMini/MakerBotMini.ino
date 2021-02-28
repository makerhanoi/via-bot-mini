
//#include <AsyncUDP.h>
#include "camera.h"
#include "motors.h"
#include "wifi.h"
#include "utils.h"

#include <WiFiUdp.h>

WiFiUDP Udp; // Creation of wifi Udp instance
char packetBuffer[255];

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(false);
  Serial.println();
  
  initCamera();
  initWifi();
  startCameraServer();
  initMotors();
  Udp.begin(1234);

  Serial.println("Done setup!");
}

void loop() {
  
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) packetBuffer[len] = 0;
    Serial.print("Received (IP/Size/Data): ");
    Serial.print(Udp.remoteIP()); Serial.print(" / ");
    Serial.print(packetSize); Serial.print(" / ");
    Serial.println(packetBuffer);

    Udp.beginPacket(Udp.remoteIP(),Udp.remotePort());
    Udp.printf("received: ");
    Udp.printf(packetBuffer);
    Udp.printf("\n");
    Udp.endPacket();

    String received_data = (const char*)packetBuffer;
    Serial.println(received_data);
    float left_motor_speed = getValue(received_data, ' ', 0).toFloat();
    float right_motor_speed = getValue(received_data, ' ', 1).toFloat();
    Serial.print("Left speed:"); Serial.println(left_motor_speed);
    Serial.print("Right speed:"); Serial.println(right_motor_speed);
    setSpeed(left_motor_speed, right_motor_speed);
   }
 }
