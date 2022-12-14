// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        2 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 256 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

int greenArr[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,
                  30,29,28,27,26,25,24,23,22,21,20,19,18,
                  33,34,35,36,37,38,39,40,41,42,43,44,45, 
                  61,60,59,58,57,56,55,54,53,52,51,
                  66,67,68,69,70,71,72,73,74,75,76,
                  92,91,90,89,88,87,86,85,84,
                  99,100,101,102,103,104,105,106,107,
                  123,122,121,120,119,118,117,
                  132,133,134,135,136,137,138,
                  154,153,152,151,150,165,166,
                  167,168,169,185,184,183,
                  198,199,200,216,231};

int starArr[] = {216,230,231,232,248};

void setup() {

  // Initialize Serial Port
  Serial.begin(9600);
  
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.
  pixels.setBrightness(15); // Set BRIGHTNESS to about 1/5 (max = 255)
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

  Serial.println("Testing");
  pixels.clear();
  
  int sizeOfGreenArr = sizeof greenArr / sizeof *greenArr;
  
  for(int i=0; i<sizeOfGreenArr; i++)
    pixels.setPixelColor(greenArr[i], pixels.Color(0, 150, 0));

  int sizeOfStarArr = sizeof starArr / sizeof *starArr;
  
  for(int i=0; i<sizeOfStarArr; i++)
    pixels.setPixelColor(starArr[i], pixels.Color(255, 255, 0));
    
  pixels.show();
}

void loop() {
  rainbow(10);
  
}


void rainbow(int wait) {
  int colorArr[] = {0,3,8,13,20,34,36,38,45,54,68,75,88,86,100,102,119,121,133,138,152,165,183,199};
  int sizeOfColorArr = sizeof colorArr / sizeof *colorArr;
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<sizeOfColorArr; i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / pixels.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      pixels.setPixelColor(colorArr[i], pixels.gamma32(pixels.ColorHSV(pixelHue)));
    }
    pixels.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}
