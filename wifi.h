#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

void initWifi() {

    // Set these to your desired credentials.
    const char *ssid = "CamWifi";
    const char *password = "12345678";
    WiFiServer server(6789);

    Serial.println();
    Serial.println("Configuring access point...");

    // You can remove the password parameter if you want the AP to be open.
    WiFi.softAP(ssid, password);
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
    server.begin();
    Serial.println("Server started");

}