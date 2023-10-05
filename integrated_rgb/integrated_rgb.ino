#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 16

// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 3
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];

int trigPin = 9;    // ultrasonic sensor Trig pin 9
int echoPin = 10;    // ultrasonic sensor Echo pin 10
int speakerpin = 7;  // beeper pin 7
long duration, cm ;  // variables needed to calculate distance
long depth = 0;
long movement = 0; 
 
void setup() {

  // setup for LCD
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical

  Serial.begin (9600);           // Setup the transmission rate between Serial Monitor and Arduino is 9600 bps (Bits Per Second)
  pinMode(trigPin, OUTPUT);      // Arduino activates ultrasonic sensor
  pinMode(echoPin, INPUT);       // Arduino calculate the time lapse when receiving echo
  pinMode(speakerpin, OUTPUT);   // Arduino activates beeper
}

void loop()
{

  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = (duration/2) / 29.1;

  Serial.println(cm);

  // delay(500);
  if (cm <= 6) {
    Serial.println("< 6");

    // buzzer
    digitalWrite(speakerpin, HIGH);
    delay (100);
    digitalWrite(speakerpin, LOW);
    delay (100);

    // LED lights
    // our LED is connected wrong, calling Green will get Red
    fill_solid(leds, 16 - cm, CRGB::Green);
    // Now turn the LED off, then pause
    for ( int i = 0; i < 16; ++i) {
      leds[i] = CRGB::Black;
      FastLED.show();
      }
  }
  else if (cm > 6 && cm <= 10) {
    Serial.println("6~10");
    // noTone(speakerpin);

    // LED lights
    // our LED is connected wrong, calling Red will get Green
    fill_solid(leds, 16 - cm, CRGB::DarkRed);
    // Now turn the LED off, then pause
    for ( int i = 0; i < 16; ++i) {
      leds[i] = CRGB::Black;
      FastLED.show();
      }
  }
  else if (10 < cm) {
    Serial.println("> 10");
    // noTone(speakerpin);

    // LED lights
    fill_solid(leds, 16 - cm, CRGB::Yellow);
    // Now turn the LED off, then pause
    for ( int i = 0; i < 16; ++i) {
      leds[i] = CRGB::Black;
      FastLED.show();
      }
    }
  }