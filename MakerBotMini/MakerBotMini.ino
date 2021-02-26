

#include <AsyncUDP.h>
#include "camera.h"
#include "motors.h"
#include "wifi.h"
#include "utils.h"

AsyncUDP udp;

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();

  initCamera();
  initWifi();
  startCameraServer();
  initMotors();


  // Setup command server
  if (udp.listen(1234)) {
    Serial.print("UDP Listening on IP: ");
    Serial.println(WiFi.localIP());
    udp.onPacket([](AsyncUDPPacket packet) {
      Serial.print("UDP Packet Type: ");
      Serial.print(packet.isBroadcast()   ? "Broadcast"
                   : packet.isMulticast() ? "Multicast"
                                          : "Unicast");
      Serial.print(", From: ");
      Serial.print(packet.remoteIP());
      Serial.print(":");
      Serial.print(packet.remotePort());
      Serial.print(", To: ");
      Serial.print(packet.localIP());
      Serial.print(":");
      Serial.print(packet.localPort());
      Serial.print(", Length: ");
      Serial.print(packet.length());  // dlzka packetu
      Serial.print(", Data: ");
      Serial.write(packet.data(), packet.length());
      Serial.println();
      String received_data = (const char*)packet.data();
      float left_motor_speed = getValue(received_data, ' ', 0).toFloat();
      float right_motor_speed = getValue(received_data, ' ', 1).toFloat();
      setSpeed(left_motor_speed, right_motor_speed);
    });
  }
}

void loop() {
  delay(2000);
}
