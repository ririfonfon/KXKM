/////////////////////////////////////////Adresse/////////////////////////////////////

#define adr 1
#define NUM_LEDS_PER_STRIP 13

#define UNI 1
//const int numberOfChannels = NUM_LEDS_PER_STRIP * 3; // Total number of channels you want to receive (1 led = 3 channels)
const int startUniverse = 0;
bool sendFrame = 1;
int previousDataLength = 0;

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

///////////////////////////////Lib esp32_digital_led_lib//////////////////////////////
#include "esp32_digital_led_lib.h"
#define min(m,n) ((m)<(n)?(m):(n))
#define NUM_STRIPS 1
int PINS[NUM_STRIPS] = {23};
const int numberOfChannels = NUM_STRIPS * NUM_LEDS_PER_STRIP * 3;
const int numberOfLed = NUM_STRIPS * NUM_LEDS_PER_STRIP ;
strand_t STRANDS[NUM_STRIPS];
strand_t * strands [] = { &STRANDS[0]};
//bool randArray[numberOfLed];
const int maxUniverses = numberOfChannels / 512 + ((numberOfChannels % 512) ? 1 : 0);
bool universesReceived[maxUniverses];

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
  if ((universe - startUniverse) < maxUniverses)
    universesReceived[universe - startUniverse] = 1;
    
    for (int i = 0; i < length / 3; i++)
    {
      int led = i + (universe - startUniverse) * (previousDataLength / 3);
      if (led < NUM_LEDS_PER_STRIP)
        strands[0]->pixels[i] = pixelFromRGB(leds_square(data[i * 3]), leds_square(data[i * 3 + 1]), leds_square(data[i * 3 + 2]));
    }
    previousDataLength = length;

    if (sendFrame)
    {
      leds_show();
      // Reset universeReceived to 0
      memset(universesReceived, 0, maxUniverses);
    }
  
}


void setup()
{
  // set-up serial for debug output
  Serial.begin(115200);
  leds_init();
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
