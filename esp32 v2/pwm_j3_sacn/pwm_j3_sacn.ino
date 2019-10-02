#define DEBUG 1
#define DEBUGsacn 1

//// Setup PWM State(s)
int ledChannelOne = 0;
int ledChannelTwo = 0;

// SACN
#include <ESPAsyncE131.h>

#define UNIVERSE 1                     // First DMX Universe to listen for
#define UNIVERSE_COUNT 1                // Total number of Universes to listen for, starting at UNIVERSE

const char ssid[] = "riri_new";         // Replace with your SSID
const char passphrase[] = "B2az41opbn6397";   // Replace with your WPA2 passphrase

// ESPAsyncE131 instance with UNIVERSE_COUNT buffer slots
ESPAsyncE131 e131(UNIVERSE_COUNT);

void setup() {

  Serial.begin(115200);
  delay(1000);

  // Make sure you're in station mode
  WiFi.mode(WIFI_STA);

  Serial.println("");
  Serial.print(F("Connecting to "));
  Serial.print(ssid);

  if (passphrase != NULL)
    WiFi.begin(ssid, passphrase);
  else
    WiFi.begin(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print(F("Connected with IP: "));
  Serial.println(WiFi.localIP());

  // Choose one to begin listening for E1.31 data
//  if (e131.begin(E131_UNICAST))                               // Listen via Unicast
  if (e131.begin(E131_MULTICAST, UNIVERSE, UNIVERSE_COUNT))   // Listen via Multicast
    Serial.println(F("Listening for data..."));
  else
    Serial.println(F("*** e131.begin failed ***"));


  ledSetup();
  Serial.println("Starting ");
}//setup

void loop() {

  if (!e131.isEmpty()) {
    e131_packet_t packet;
    e131.pull(&packet);     // Pull packet from ring buffer

    if (htons(packet.universe) == UNIVERSE) {
      int ONE = packet.property_values[1];
      int TWO = packet.property_values[2];

      ledChannelOne = (ONE * ONE) / 255;
      ledChannelTwo = (TWO * TWO) / 255;

      leds();
    }

#ifdef DEBUGsacn
    Serial.printf("Universe %u / %u Channels | Packet#: %u / Errors: %u / CH1: %u/ CH2: %u/ CH3: %u\n",
                  htons(packet.universe),                 // The Universe for this packet
                  htons(packet.property_value_count) - 1, // Start code is ignored, we're interested in dimmer data
                  e131.stats.num_packets,                 // Packet counter
                  e131.stats.packet_errors,               // Packet error counter
                  packet.property_values[1],             // Dimmer data for Channel 1
                  packet.property_values[2],             // Dimmer data for Channel 2
                  packet.property_values[3]);             // Dimmer data for Channel 3
#endif
  }

}//loop
