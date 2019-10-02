//// Setup PWM State(s)
int ledChannelOne = 0;
int ledChannelTwo = 0;
int ledChannelThree = 0;

void setup() {

  Serial.begin(115200);

  ledSetup();
  Serial.println("Starting ");
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0 ; i < 255 ; i++ ) {
    ledChannelOne = (i * i) / 255;
    ledChannelTwo = (i * i) / 255;
    ledChannelThree = (i * i) / 255;
    leds();
    delay(10);
  }
  ledChannelOne = 255;
  ledChannelTwo = 255;
  ledChannelThree = 255;
  leds();
  delay(2000);

  for (int i = 0 ; i < 255 ; i++ ) {
    ledChannelOne = (i * i) / 255;
    ledChannelTwo = (i * i) / 255;
    ledChannelThree = (i * i) / 255;
    leds();
    delay(10);
    ledChannelOne = 0;
    ledChannelTwo = 0;
    ledChannelThree = 0;
    leds();
    delay(90);
  }
}
