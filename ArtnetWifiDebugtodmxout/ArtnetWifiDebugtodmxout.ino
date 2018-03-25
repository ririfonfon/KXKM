
#include <LXESP32DMX.h>
#include "esp_task_wdt.h"

#define DMX_DIRECTION_PIN 21
#define DMX_SERIAL_OUTPUT_PIN 17

uint8_t level;
uint8_t dmxbuffer[DMX_MAX_FRAME];
#define UNI 1
/*
  Example, transmit all received ArtNet messages (DMX) out of the serial port in plain text.

  Stephan Ruloff 2016
  https://github.com/rstephan

*/
#if defined(ARDUINO_ARCH_ESP32)
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <WiFiUdp.h>
#include <ArtnetWifi.h>

//Wifi settings
const char* ssid = "riri";
const char* password = "288F42E7E8";

WiFiUDP UdpSend;
ArtnetWifi artnet;

// connect to wifi – returns true if successful or false if not
boolean ConnectWifi(void)
{
  boolean state = true;
  int i = 0;

  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20) {
      state = false;
      break;
    }
    i++;
  }
  if (state) {
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("");
    Serial.println("Connection failed.");
  }

  return state;
}

void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data)
{
  Serial.print("DMX: Univ: ");
  Serial.print(universe, DEC);
  Serial.print(", Seq: ");
  Serial.print(sequence, DEC);
  Serial.print(", Data (");
  Serial.print(length, DEC);
  Serial.print("): ");
  Serial.println();
  if (universe == UNI ) {
    // send out the buffer
    for (int i = 1; i < length + 1; i++)dmxbuffer[i] = (data[i] * data[i]) / 255;
    copyDMXToOutput();
    Serial.println("copyDMXToOutput()");
  }
}

void copyDMXToOutput(void) {
  xSemaphoreTake( ESP32DMX.lxDataLock, portMAX_DELAY );
  for (int i = 1; i < DMX_MAX_FRAME; i++) {
    ESP32DMX.setSlot(i , dmxbuffer[i]);
  }
  xSemaphoreGive( ESP32DMX.lxDataLock );
}

void setup()
{
  // set-up serial for debug output
  Serial.begin(115200);
  pinMode(DMX_DIRECTION_PIN, OUTPUT);
  digitalWrite(DMX_DIRECTION_PIN, HIGH);

  pinMode(DMX_SERIAL_OUTPUT_PIN, OUTPUT);
  ESP32DMX.startOutput(DMX_SERIAL_OUTPUT_PIN);
  Serial.println("ESP32DMX setup complete");
  ConnectWifi();

  // this will be called for each packet received
  artnet.setArtDmxCallback(onDmxFrame);
  artnet.begin();
}

void loop()
{
  // we call the read function inside the loop
  artnet.read();
}
