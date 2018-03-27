///////////////////////////////////////// debug /////////////////////////////////////
#define DEBUG

#define UNI 1

///////////////////////////////////////PWM setting/////////////////////////////////////////
int freq = 12000;
int resolution = 16;
int ledChannela = 4;
int ledChannelb = 5;
int ledChannelc = 6;
int ledPina = 22;
int ledPinb = 21;
int ledPinc = 04;
uint8_t ledArray[3] = {1, 2, 3}; // three led channels
const boolean invert = true; // set true if common anode, false if common cathode

#if defined(ARDUINO_ARCH_ESP32)
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <WiFiUdp.h>
#include <ArtnetWifi.h>

//Wifi settings
const char* ssid = "kxkm-wifi";
const char* password = "KOMPLEXKAPHARNAUM";

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
    #ifdef DEBUG
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("");
    Serial.println("Connection failed.");
    #endif
  }
  return state;
}
void pwm_init() {
  /////////////////////////////////////////////////PWM setup
  ledcAttachPin(ledPina, ledChannela);
  ledcAttachPin(ledPinb, ledChannelb);
  ledcAttachPin(ledPinc, ledChannelc);
  ledcSetup(ledChannela, freq, resolution);
  ledcSetup(ledChannelb, freq, resolution);
  ledcSetup(ledChannelc, freq, resolution);
}

void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data){
  #ifdef DEBUG
  Serial.print("DMX: Univ: ");
  Serial.print(universe, DEC);
  Serial.print(", Seq: ");
  Serial.print(sequence, DEC);
  Serial.print(", Data (");
  Serial.print(length, DEC);
  Serial.print("): ");
  Serial.println();
  #endif
  if (universe == UNI ) {
ledcWrite(ledChannela, (data[1] * data[1]) * 1.007852);
ledcWrite(ledChannelb, (data[2] * data[2]) * 1.007852);
ledcWrite(ledChannelc, (data[3] * data[3]) * 1.007852);
  }
}


void setup(){
  #ifdef DEBUG
  // set-up serial for debug output
  Serial.begin(115200);
  #endif
  pwm_init();
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
