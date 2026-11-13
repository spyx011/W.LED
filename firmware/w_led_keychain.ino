// W LED Keychain
// Chip: ATtiny1616 (megaTinyCore), programmed over UPDI
// Not tested on real hardware yet.

#define SER_PIN   PIN_PA1   // data to the first 74HC595
#define SRCLK_PIN PIN_PA3   // shift clock
#define RCLK_PIN  PIN_PA4   // latch
#define OE_PIN    PIN_PB0   // output enable (low = on), used for brightness
#define BTN_PIN   PIN_PA6   // push button to GND

#define NUM_MODES 4
#define ALL_LEDS  0x1FFF    // 13 LEDs

uint8_t mode = 0;

// Send one byte to the shift registers, first bit first
void shiftByte(uint8_t b) {
  for (int8_t i = 7; i >= 0; i--) {
    digitalWrite(SER_PIN, (b >> i) & 1);
    digitalWrite(SRCLK_PIN, HIGH);
    digitalWrite(SRCLK_PIN, LOW);
  }
}

// Show LEDs. Bit 0 = D1, bit 12 = D13
void show(uint16_t leds) {
  shiftByte((leds >> 7) & 0x3F);  // second chip (D8 to D13) gets sent first
  shiftByte(leds & 0x7F);         // first chip (D1 to D7)
  digitalWrite(RCLK_PIN, HIGH);
  digitalWrite(RCLK_PIN, LOW);
}

// 0 = off, 255 = full brightness (OE is active low, so it is flipped)
void setBrightness(uint8_t b) {
  analogWrite(OE_PIN, 255 - b);
}

// Wait for some milliseconds. Returns true if the button was pressed.
bool wait(uint16_t ms) {
  while (ms--) {
    if (digitalRead(BTN_PIN) == LOW) {
      delay(30);
      if (digitalRead(BTN_PIN) == LOW) {
        mode = (mode + 1) % NUM_MODES;
        while (digitalRead(BTN_PIN) == LOW) {}  // wait for release
        return true;
      }
    }
    delay(1);
  }
  return false;
}

// Mode 0: one LED runs along the W and back
void chase() {
  for (uint8_t i = 0; i < 13; i++) {
    show(1UL << i);
    if (wait(80)) return;
  }
  for (int8_t i = 11; i > 0; i--) {
    show(1UL << i);
    if (wait(80)) return;
  }
}

// Mode 1: the W fills up, then empties
void fill() {
  uint16_t leds = 0;
  for (uint8_t i = 0; i < 13; i++) {
    leds |= (1UL << i);
    show(leds);
    if (wait(70)) return;
  }
  if (wait(300)) return;
  for (uint8_t i = 0; i < 13; i++) {
    leds &= ~(1UL << i);
    show(leds);
    if (wait(70)) return;
  }
}

// Mode 2: every other LED, swapping
void alternate() {
  show(0x1555);
  if (wait(250)) return;
  show(0x0AAA);
  wait(250);
}

// Mode 3: whole W fades in and out
void breathe() {
  show(ALL_LEDS);
  for (int16_t b = 0; b <= 255; b += 5) {
    setBrightness(b);
    if (wait(10)) return;
  }
  for (int16_t b = 255; b >= 0; b -= 5) {
    setBrightness(b);
    if (wait(10)) return;
  }
}

void setup() {
  pinMode(OE_PIN, OUTPUT);
  digitalWrite(OE_PIN, HIGH);  // LEDs off while starting
  pinMode(SER_PIN, OUTPUT);
  pinMode(SRCLK_PIN, OUTPUT);
  pinMode(RCLK_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);

  show(0);
  setBrightness(255);
}

void loop() {
  if (mode != 3) setBrightness(255);
  switch (mode) {
    case 0: chase(); break;
    case 1: fill(); break;
    case 2: alternate(); break;
    case 3: breathe(); break;
  }
}
