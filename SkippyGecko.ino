#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>


// --- Start Page Background Bitmap (128x64)
static const uint8_t START_BG_128x64[1024] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x60,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0xF0,
  0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x03, 0xC0,
  0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x03, 0x1C,
  0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x03, 0x34,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x03, 0x6C,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x03, 0x9C,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB8, 0x1C, 0x01, 0xF8,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x49, 0x80, 0x00, 0x00, 0x00, 0x44, 0x47, 0xE2, 0x00, 0x60,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x49, 0x92, 0xB7, 0x62, 0x23, 0x75, 0x00, 0x01, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 0x49, 0x2A, 0xA5, 0x61, 0x17, 0x50, 0x80, 0x01, 0x00, 0x02,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0x29, 0x13, 0xA5, 0x77, 0x73, 0x53, 0x80, 0x00, 0xF1, 0xED,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x10,
  0x00, 0x00, 0x00, 0x00, 0x03, 0xD3, 0xCF, 0x3D, 0xFC, 0x1F, 0xC7, 0xCF, 0x80, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xFE, 0x0F, 0xEF, 0xCF, 0x3D, 0xFF, 0x1F, 0xE3, 0xCF, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x03, 0x01, 0x8F, 0xF3, 0xDE, 0x3D, 0xFF, 0x9F, 0xF9, 0xFE, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x04, 0x00, 0x6F, 0xE3, 0xFE, 0x3D, 0xFF, 0xDF, 0xF9, 0xFE, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x08, 0x00, 0x1F, 0x03, 0xFC, 0x3D, 0xE3, 0xDE, 0x3D, 0xFE, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x10, 0x0C, 0x0F, 0x83, 0xF8, 0x3D, 0xE3, 0xDE, 0x7C, 0xFE, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x20, 0x0C, 0x07, 0xF3, 0xF8, 0x3D, 0xFF, 0x9F, 0xF8, 0x78, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x20, 0x0C, 0x03, 0xF3, 0xF8, 0x3D, 0xFF, 0x9F, 0xF0, 0x78, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x60, 0x0C, 0x02, 0xF3, 0xFC, 0x3D, 0xFE, 0x1F, 0xE0, 0x78, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x40, 0x08, 0x01, 0xF3, 0xFC, 0x3D, 0xFC, 0x1F, 0x80, 0x78, 0x00, 0x00, 0x00, 0x00,
  0x80, 0x00, 0x40, 0x00, 0x01, 0xF3, 0xDF, 0x3D, 0xE0, 0x1E, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00,
  0x5C, 0x0E, 0x40, 0x00, 0x01, 0xF3, 0xCF, 0x3D, 0xE0, 0x1E, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00,
  0x23, 0xF1, 0x40, 0x00, 0x01, 0xE3, 0xCF, 0x3D, 0xE0, 0x1E, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xC0, 0x0F, 0xFE, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xC0, 0x00, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x40, 0x00, 0x07, 0xF0, 0x00, 0x00, 0xE0, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x80, 0x00, 0x0F, 0xF0, 0x7F, 0xC1, 0xFC, 0xF1, 0xE1, 0xFC, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x80, 0x00, 0x1F, 0xF8, 0x7F, 0xC7, 0xFE, 0xF3, 0xE7, 0xFE, 0x00, 0x12, 0x00, 0x00,
  0x00, 0x01, 0x00, 0x00, 0x6F, 0xF8, 0x7F, 0xC7, 0xFE, 0xF3, 0xCF, 0xFE, 0x01, 0x3C, 0x00, 0x00,
  0x10, 0x03, 0x00, 0x38, 0xBE, 0x10, 0x78, 0x1F, 0x0C, 0xF7, 0x9F, 0x0F, 0x80, 0xE3, 0x40, 0x00,
  0x28, 0x04, 0x00, 0x07, 0xBE, 0x00, 0x78, 0x1E, 0x00, 0xFF, 0x1E, 0x07, 0x80, 0x90, 0x80, 0x00,
  0x24, 0x04, 0x00, 0x07, 0xBC, 0xFF, 0x7F, 0x9E, 0x00, 0xFE, 0x1E, 0x07, 0x81, 0x80, 0x80, 0x00,
  0x23, 0xF8, 0x04, 0x0F, 0xBC, 0xFF, 0x7F, 0x9E, 0x00, 0xFE, 0x1E, 0x07, 0x81, 0x82, 0xC0, 0x00,
  0x10, 0x00, 0x03, 0xF4, 0x3C, 0xFF, 0x78, 0x1E, 0x00, 0xFF, 0x1E, 0x07, 0x83, 0x80, 0x94, 0x00,
  0x10, 0x00, 0x00, 0x06, 0x3E, 0x0F, 0x78, 0x1F, 0x0C, 0xFF, 0x9F, 0x0F, 0x81, 0x80, 0x8E, 0x80,
  0x08, 0x00, 0x00, 0x09, 0x1F, 0x3F, 0x7F, 0xCF, 0xDC, 0xF7, 0xDF, 0xDF, 0x01, 0xA0, 0xD1, 0x00,
  0x04, 0x00, 0x04, 0x09, 0x1F, 0xFE, 0x7F, 0xCF, 0xFE, 0xF3, 0xCF, 0xFF, 0x01, 0x80, 0xB0, 0x80,
  0x00, 0x00, 0x02, 0x01, 0x07, 0xF8, 0x7F, 0xC1, 0xFC, 0xF1, 0xE3, 0xFE, 0x21, 0x80, 0xB4, 0xC0,
  0x02, 0x00, 0x02, 0x09, 0x01, 0xF0, 0x7F, 0xC1, 0xF8, 0xF1, 0xE1, 0xF0, 0x7B, 0x80, 0xF0, 0x80,
  0x01, 0x00, 0x02, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC5, 0x88, 0xB1, 0x80,
  0x00, 0xE1, 0x83, 0xF9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xD5, 0x80, 0xB0, 0xC0,
  0x00, 0x1C, 0x02, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC7, 0x80, 0xB2, 0x80,
  0x00, 0x08, 0x04, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC5, 0xA0, 0xE1, 0x00,
  0x00, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xD5, 0x82, 0x89, 0x00,
  0x00, 0x08, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC5, 0x80, 0x82, 0x80,
  0x00, 0x07, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xC3, 0xA0, 0x92, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE1, 0x80, 0x84, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC5, 0x80, 0x9A, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0x84, 0xE0, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xBF, 0x80, 0x90, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x80, 0x80, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0xA0, 0xC0, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x80, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x91, 0x80, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x80, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0xC0, 0x00,
  0x0E, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xA0, 0x80, 0x00,
  0x03, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x80, 0x00,
  0x03, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x84, 0x80, 0x00
};

// -------------------- Display/Inputs --------------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define BTN_ENTER 3   // D3 (INT1)
#define BTN_NEXT  7   // Jump
#define BTN_PREV  6   // Duck

// -------------------- Early Types & Global State --------------------
#define SPR_W 31
#define SPR_H 24
static const int16_t GROUND_Y = 56;
static const int16_t PLAYER_X = 12;

// Predeclare structs early to avoid Arduino auto-proto issues
struct Cloud { int16_t x; int8_t y; bool active; };
struct Bird  { int16_t x; int8_t top; bool active; };
struct Cactus{ int16_t x; int16_t top; uint8_t idx; bool active; };

// World scroll Q8.8
static uint32_t gScrollQ = 0;
static uint32_t gLifeScrollQ = 0; // Q8.8, distance within current life
static const uint16_t RUN_BASE_SPEED_Q = (82 << 8); // 82 px/s
static uint16_t gWorldSpeedQ = RUN_BASE_SPEED_Q;
// Progressive speed growth with distance (Chrome-Dino style)
// +10 px/s per 1000 px traveled, capped to +64 px/s (Q8.8 units)
static const uint16_t SPEED_GROWTH_PER_1000PX_Q = (10 << 8);
static const uint16_t SPEED_GROWTH_MAX_Q        = (64 << 8);


// -------------------- Pages --------------------
enum Page : uint8_t { PAGE_START=0, PAGE_GAME=1, PAGE_MENU=2, PAGE_ABOUT=3, PAGE_GAMEOVER=4 };
static Page page = PAGE_START;


static bool gFirstPageGate = false;
// -------------------- Blink --------------------
static bool blinkOn = true;
static unsigned long blinkMs = 0;

// -------------------- Highscore --------------------
static const uint16_t EE_SIG = 0x51C3;
static const int EE_ADDR_SIG_LO = 0;
static const int EE_ADDR_SIG_HI = 1;
static const int EE_ADDR_HS     = 2;
static uint32_t gHighScore = 0;
static bool gNewHigh = false;

static inline void saveSignature(){
  EEPROM.update(EE_ADDR_SIG_LO, (uint8_t)(EE_SIG & 0xFF));
  EEPROM.update(EE_ADDR_SIG_HI, (uint8_t)(EE_SIG >> 8));
}
static inline bool signatureOk(){
  uint16_t s = (uint16_t)EEPROM.read(EE_ADDR_SIG_LO) | ((uint16_t)EEPROM.read(EE_ADDR_SIG_HI) << 8);
  return s == EE_SIG;
}
static inline uint32_t eeReadU32(int a){
  return (uint32_t)EEPROM.read(a+0) | ((uint32_t)EEPROM.read(a+1)<<8) | ((uint32_t)EEPROM.read(a+2)<<16) | ((uint32_t)EEPROM.read(a+3)<<24);
}
static inline void eeWriteU32(int a, uint32_t v){
  EEPROM.update(a+0, (uint8_t)(v>>0));
  EEPROM.update(a+1, (uint8_t)(v>>8));
  EEPROM.update(a+2, (uint8_t)(v>>16));
  EEPROM.update(a+3, (uint8_t)(v>>24));
}
static inline void loadHighScore(){
  if (!signatureOk()){
    gHighScore = 0;
    saveSignature();
    eeWriteU32(EE_ADDR_HS, gHighScore);
  } else {
    gHighScore = eeReadU32(EE_ADDR_HS);
  }
}
static inline void resetHighScore(){
  gHighScore = 0;
  saveSignature();
  eeWriteU32(EE_ADDR_HS, gHighScore);
}

// -------------------- Standby --------------------
void wakeISR(){}
static void enterStandby(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor((SCREEN_WIDTH-6*2*3)/2, 28);
  display.print(F("Bye"));
  display.setTextSize(1);
  display.display();
  delay(900);

  display.ssd1306_command(SSD1306_DISPLAYOFF);
  attachInterrupt(digitalPinToInterrupt(BTN_ENTER), wakeISR, LOW);
  ADCSRA &= ~(1 << ADEN);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  noInterrupts();
  EIFR = bit(INTF1);
  interrupts();
  sleep_cpu();
  sleep_disable();
  detachInterrupt(digitalPinToInterrupt(BTN_ENTER));
  ADCSRA |= (1 << ADEN);
  while (digitalRead(BTN_ENTER) == LOW) { delay(5); }
  display.ssd1306_command(SSD1306_DISPLAYON);
  delay(10);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.display();
  page = PAGE_START;
}

// -------------------- UI helpers --------------------
static inline void drawCenteredText(const __FlashStringHelper* s, int16_t y){
  PGM_P p = reinterpret_cast<PGM_P>(s);
  size_t len = strlen_P(p);
  int16_t x = (SCREEN_WIDTH - (int)len * 6) / 2;
  if (x < 0) x = 0;
  display.setCursor(x, y);
  display.print(s);
}
static inline void drawCenteredTextRAM(const char* s, int16_t y){
  size_t len = strlen(s);
  int16_t x = (SCREEN_WIDTH - (int)len * 6) / 2;
  if (x < 0) x = 0;
  display.setCursor(x, y);
  display.print(s);
}

// -------------------- Menu --------------------
static int8_t menuSel = 0;
const char MI0[] PROGMEM = "About";
const char MI1[] PROGMEM = "Reset Highscore";
const char MI2[] PROGMEM = "Back";
const char* const MENU_ITEMS[] PROGMEM = { MI0, MI1, MI2 };

static inline void drawHS(){
  display.setCursor(0, 2);
  display.print(F("HS:"));
  display.print(gHighScore);
}

static void pageStart(bool nextPressed, bool prevPressed, bool enterShort, bool enterLong){

  // Gate: require releasing NEXT/PREV once after Game Over before starting from the first page
  if (gFirstPageGate) {
    if (!(nextPressed || prevPressed)) {
      gFirstPageGate = false;
    } else {
      return; // still held → ignore
    }
  }
// Gate: require releasing NEXT/PREV once before accepting start
  if (gFirstPageGate) {
    if (!(nextPressed || prevPressed)) {
      gFirstPageGate = false;
    } else {
      return;
    }
  }
if (enterLong){ page = PAGE_MENU; menuSel = 0; display.clearDisplay(); display.display(); return; }
  if (enterShort){ enterStandby(); return; }
  if (nextPressed || prevPressed){ page = PAGE_GAME; display.clearDisplay(); return; }

  display.clearDisplay();
  display.drawBitmap(0, 0, START_BG_128x64, 128, 64, SSD1306_WHITE);
  drawHS();
  if (blinkOn) drawCenteredText(F("Press any Key "), 53);
  display.display();
}

static void pageMenu(bool nextEdge, bool prevEdge, bool selectEdge){
  if (nextEdge) menuSel = (menuSel + 1) % 3;
  if (prevEdge) menuSel = (menuSel + 3 - 1) % 3;
  if (selectEdge){
    if (menuSel == 0){ page = PAGE_ABOUT; }
    else if (menuSel == 1){ resetHighScore(); page = PAGE_START; }
    else { page = PAGE_START; }
    return;
  }
  display.clearDisplay();
  int16_t y0 = 20;
  for (uint8_t i=0;i<3;i++){
    display.setCursor(16, y0 + i*12);
    const char* p = (const char*)pgm_read_ptr(&MENU_ITEMS[i]);
    display.print((const __FlashStringHelper*)p);
  }
  display.setCursor(4, y0 + menuSel*12); display.print('>');
  display.display();
}

static void pageAbout(bool anyEdge){
  display.clearDisplay();
  drawCenteredText(F("Created By"), 26);
  drawCenteredText(F("Ali Pournasseh"), 40);
  display.display();
  if (anyEdge){ page = PAGE_MENU; }
}

// -------------------- Sprites --------------------
#define SPR_BYTES ((SPR_W+7)/8)
static uint16_t gRunDuckMs = 110;

static const uint8_t idle0_bits[SPR_H][SPR_BYTES] PROGMEM = {
  { 0x00,0x00,0x3E,0x00},{0x00,0x00,0x41,0x00},{0x00,0x00,0x81,0x80},{0x00,0x01,0x08,0x40},
  { 0x00,0x02,0x18,0x40},{0x00,0x02,0x00,0x40},{0x00,0x04,0x00,0x80},{0x00,0x04,0x1F,0x00},
  { 0x00,0x08,0x10,0x00},{0x00,0x10,0x10,0x00},{0x02,0x20,0x10,0x00},{0x06,0x20,0x10,0x00},
  { 0x0A,0x43,0x08,0x00},{0x0A,0x83,0x08,0x00},{0x11,0x01,0x68,0x00},{0x10,0x00,0x50,0x00},
  { 0x08,0x00,0x40,0x00},{0x04,0x00,0x40,0x00},{0x02,0x00,0x40,0x00},{0x01,0xCE,0x40,0x00},
  { 0x00,0x8C,0x80,0x00},{0x00,0xB5,0x00,0x00},{0x00,0x94,0x80,0x00},{0x00,0x63,0x00,0x00},
};
static const uint8_t idle1_bits[SPR_H][SPR_BYTES] PROGMEM = {
  { 0x00,0x00,0x3E,0x00},{0x00,0x00,0x41,0x00},{0x00,0x00,0x81,0x80},{0x00,0x01,0x00,0x40},
  { 0x00,0x02,0x18,0x40},{0x00,0x02,0x00,0x40},{0x00,0x04,0x00,0x80},{0x00,0x04,0x1F,0x00},
  { 0x00,0x08,0x10,0x00},{0x00,0x10,0x10,0x00},{0x02,0x20,0x10,0x00},{0x06,0x20,0x10,0x00},
  { 0x0A,0x43,0x08,0x00},{0x0A,0x83,0x08,0x00},{0x11,0x01,0x68,0x00},{0x10,0x00,0x50,0x00},
  { 0x08,0x00,0x40,0x00},{0x04,0x00,0x40,0x00},{0x02,0x00,0x40,0x00},{0x01,0xCE,0x40,0x00},
  { 0x00,0x8C,0x80,0x00},{0x00,0xB5,0x00,0x00},{0x00,0x94,0x80,0x00},{0x00,0x63,0x00,0x00},
};
static const uint8_t run0_bits[SPR_H][SPR_BYTES] PROGMEM = {
  { 0x00,0x00,0x3E,0x00},{0x00,0x00,0x41,0x00},{0x00,0x00,0x81,0x80},{0x00,0x01,0x08,0x40},
  { 0x00,0x02,0x18,0x40},{0x00,0x02,0x00,0x40},{0x00,0x04,0x07,0x80},{0x00,0x04,0x01,0x00},
  { 0x00,0x08,0x1F,0x00},{0x00,0x10,0x10,0x00},{0x02,0x20,0x10,0x00},{0x06,0x20,0x10,0x00},
  { 0x0A,0x43,0x08,0x00},{0x0A,0x83,0x08,0x00},{0x11,0x01,0x68,0x00},{0x10,0x00,0x50,0x00},
  { 0x08,0x00,0x40,0x00},{0x04,0x00,0x40,0x00},{0x02,0x00,0x40,0x00},{0x01,0xDE,0x40,0x00},
  { 0x00,0x4C,0x80,0x00},{0x00,0x35,0x00,0x00},{0x00,0x04,0x80,0x00},{0x00,0x03,0x00,0x00},
};
static const uint8_t run1_bits[SPR_H][SPR_BYTES] PROGMEM = {
  { 0x00,0x00,0x3E,0x00},{0x00,0x00,0x41,0x00},{0x00,0x00,0x81,0x80},{0x00,0x01,0x08,0x40},
  { 0x00,0x02,0x18,0x40},{0x00,0x02,0x00,0x40},{0x00,0x04,0x07,0x80},{0x00,0x04,0x01,0x00},
  { 0x00,0x08,0x1F,0x00},{0x00,0x10,0x10,0x00},{0x02,0x20,0x10,0x00},{0x06,0x20,0x10,0x00},
  { 0x0A,0x43,0x08,0x00},{0x0A,0x83,0x08,0x00},{0x11,0x01,0x68,0x00},{0x10,0x00,0x50,0x00},
  { 0x08,0x00,0x40,0x00},{0x04,0x00,0x40,0x00},{0x02,0x00,0x40,0x00},{0x01,0xCE,0x80,0x00},
  { 0x00,0x8A,0x40,0x00},{0x00,0xB1,0x80,0x00},{0x00,0x90,0x00,0x00},{0x00,0x60,0x00,0x00},
};
static const uint8_t duck0_bits[SPR_H][SPR_BYTES] PROGMEM = {
  {0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},
  {0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},
  {0x00,0x00,0x01,0xF0},{0x00,0x3F,0x02,0x08},{0x40,0x40,0xC4,0x08},{0x40,0x40,0x44,0x04},
  {0xB1,0x80,0x38,0x82},{0x8F,0x00,0x01,0x82},{0x80,0x00,0x00,0x06},{0x40,0x00,0x00,0x04},
  {0x20,0x00,0x01,0xF8},{0x10,0x00,0x0E,0x00},{0x09,0x02,0xD0,0x00},{0x07,0x3C,0x90,0x00},
  {0x01,0xEB,0x60,0x00},{0x00,0x0E,0x00,0x00},{0x00,0x09,0x00,0x00},{0x00,0x06,0x00,0x00},
};
static const uint8_t duck1_bits[SPR_H][SPR_BYTES] PROGMEM = {
  {0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},
  {0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},
  {0x00,0x00,0x01,0xF0},{0x00,0x3F,0x02,0x08},{0x40,0x40,0xC4,0x08},{0x40,0x40,0x44,0x04},
  {0xB1,0x80,0x38,0x82},{0x8F,0x00,0x01,0x82},{0x80,0x00,0x00,0x06},{0x40,0x00,0x00,0x04},
  {0x20,0x00,0x01,0xF8},{0x10,0x00,0x0E,0x00},{0x08,0x05,0xD0,0x00},{0x07,0x39,0x90,0x00},
  {0x01,0x26,0x60,0x00},{0x02,0xC0,0x00,0x00},{0x02,0x40,0x00,0x00},{0x01,0x80,0x00,0x00},
};
static const uint8_t jump0_bits[SPR_H][SPR_BYTES] PROGMEM = {
  { 0x00,0x00,0x3E,0x00},{0x00,0x00,0x41,0x00},{0x00,0x00,0x81,0x80},{0x00,0x01,0x18,0x40},
  { 0x00,0x02,0x00,0x40},{0x00,0x02,0x00,0x40},{0x00,0x04,0x07,0x80},{0x00,0x04,0x01,0x00},
  { 0x00,0x08,0x1F,0x00},{0x00,0x10,0x10,0x00},{0x02,0x20,0x10,0x00},{0x06,0x20,0x10,0x00},
  { 0x0A,0x43,0x08,0x00},{0x0A,0x83,0x08,0x00},{0x11,0x01,0x68,0x00},{0x10,0x00,0x50,0x00},
  { 0x08,0x00,0x40,0x00},{0x04,0x00,0x40,0x00},{0x02,0x00,0x40,0x00},{0x01,0xCE,0x40,0x00},
  { 0x00,0x8C,0x80,0x00},{0x00,0xB5,0x00,0x00},{0x00,0x94,0x80,0x00},{0x00,0x63,0x00,0x00},
};
static const uint8_t hit0_bits[SPR_H][SPR_BYTES] PROGMEM = {
  {0x00,0x00,0x00,0x00},{0x00,0x00,0x01,0xF0},{0x00,0x00,0x02,0x08},{0x00,0x00,0x04,0x0C},
  {0x00,0x00,0x08,0x82},{0x00,0x00,0x10,0x02},{0x00,0x00,0x10,0x02},{0x01,0x00,0xE0,0x3C},
  {0x02,0x81,0x00,0x08},{0x05,0x06,0x01,0xF8},{0x08,0x98,0x02,0x00},{0x08,0x60,0x02,0x00},
  {0x04,0x00,0x04,0x00},{0x04,0x00,0xC4,0x00},{0x02,0x00,0xD2,0x00},{0x01,0x00,0x1A,0x00},
  {0x00,0x80,0x24,0x00},{0x00,0x80,0xC0,0x00},{0x01,0x39,0x00,0x00},{0x01,0x45,0x00,0x00},
  {0x00,0xA9,0x00,0x00},{0x00,0x4A,0x00,0x00},{0x00,0x05,0x00,0x00},{0x00,0x06,0x00,0x00},
};
static const uint8_t hit1_bits[SPR_H][SPR_BYTES] PROGMEM = {
  {0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},
  {0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},
  {0x00,0x18,0x00,0x00},{0x00,0x26,0x00,0x00},{0x00,0x41,0x00,0x00},{0x00,0x47,0x00,0x00},
  {0x01,0x89,0x00,0x00},{0x01,0x08,0x00,0x00},{0x0F,0x06,0x00,0x00},{0x11,0x01,0x00,0x00},
  {0x14,0x01,0x01,0xF0},{0x0C,0x00,0xC2,0x08},{0x03,0x00,0x24,0x0C},{0x0F,0x00,0x18,0x02},
  {0x11,0x07,0x01,0x82},{0x14,0x06,0x00,0x02},{0x0A,0x00,0x00,0x04},{0x01,0xFF,0xFF,0xF8},
};

static void drawSpriteBits(int16_t left, int16_t bottom, const uint8_t frame[][SPR_BYTES]){
  for (uint8_t ry=0; ry<SPR_H; ++ry){
    int16_t y = bottom - (SPR_H - 1 - ry);
    if (y < 0 || y >= SCREEN_HEIGHT) continue;
    for (uint8_t bx=0; bx<SPR_BYTES; ++bx){
      uint8_t b = pgm_read_byte(&frame[ry][bx]);
      for (uint8_t bi=0; bi<8; ++bi){
        uint8_t bitX = bx*8 + bi; if (bitX >= SPR_W) break;
        if (b & (0x80 >> bi)){
          int16_t x = left + bitX;
          if (x >= 0 && x < SCREEN_WIDTH) display.drawPixel(x, y, SSD1306_WHITE);
        }
      }
    }
  }
}

// -------------------- Terrain --------------------
static const uint16_t TERR_W = 128;
#define TERR_BYTES ((TERR_W+7)/8)
static const uint8_t TERR_ROWS = 18;
static const uint8_t TERR_BITS[TERR_ROWS][TERR_BYTES] PROGMEM = {
  { 0x00,0x00,0x00,0x00,0x21,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00 },
  { 0x00,0x00,0x00,0x00,0x92,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x80,0x00,0x00,0x00 },
  { 0x00,0x00,0x00,0x00,0x54,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x00,0x00,0x00,0x00 },
  { 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF },
  { 0x00,0x81,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x02,0x00,0x00,0x00 },
  { 0x00,0x00,0x00,0x80,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x01,0x00,0x00,0x00 },
  { 0x00,0x00,0x20,0x00,0x04,0x41,0x00,0x40,0x01,0x04,0x00,0x20,0x10,0x00,0x04,0x20 },
  { 0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
  { 0x04,0x00,0x00,0x10,0x20,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00 },
  { 0x00,0x00,0x20,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00 },
  { 0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x08,0x02,0x01,0x00,0x10,0x00,0x00,0x00 },
  { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
  { 0x00,0x04,0x00,0x00,0x80,0x00,0x40,0x00,0x00,0x00,0x40,0x00,0x20,0x10,0x10,0x02 },
  { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x00 },
  { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
  { 0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
  { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00 },
  { 0x02,0x00,0x00,0x80,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00 },
};

static void drawTerrain(uint16_t xOffsetPx){
  const int baseY = GROUND_Y + 1;
  const int anchorRow = 3;
  const uint8_t tw = (uint8_t)128;
  uint8_t off = (uint8_t)(xOffsetPx % tw);
  for (uint8_t r=0; r<18; ++r){
    int y = baseY + (int)r - anchorRow;
    if (y < 0 || y >= SCREEN_HEIGHT) continue;
    for (int x=0; x<SCREEN_WIDTH; ++x){
      uint16_t idx = (uint16_t)x + off;
      uint16_t idxm = idx % tw;
      uint8_t byteIndex = (uint8_t)(idxm >> 3);
      uint8_t bitMask = (uint8_t)(0x80 >> (idxm & 7));
      uint8_t b = pgm_read_byte(&TERR_BITS[r][byteIndex]);
      if (b & bitMask) display.drawPixel(x, y, SSD1306_WHITE);
    }
  }
}

// -------------------- Clouds --------------------
#define CLOUD_H 16
static const uint8_t CLOUD_W = 38;
#define CLOUD_BYTES ((CLOUD_W+7)/8)
static const uint8_t CLOUD_BITS[CLOUD_H][CLOUD_BYTES] PROGMEM = {
  {0x00,0x00,0xB8,0x00,0x00},{0x00,0x0B,0x46,0x00,0x00},{0x00,0x14,0x01,0x00,0x00},{0x00,0x10,0x01,0x20,0x00},
  {0x00,0x10,0x00,0xD0,0x00},{0x00,0xE0,0x00,0x0F,0x00},{0x11,0x00,0x00,0x00,0x80},{0x2E,0x00,0x00,0x00,0x80},
  {0x40,0x00,0x00,0x00,0xA0},{0x80,0x00,0x00,0x00,0x58},{0x70,0x00,0x00,0x00,0x04},{0x0B,0x0C,0x00,0x00,0x18},
  {0x04,0xF2,0x00,0x00,0x20},{0x00,0x02,0x00,0x98,0x40},{0x00,0x01,0xCD,0x67,0x80},{0x00,0x00,0x32,0x00,0x00},
};
static int8_t gCloudYMin = -13;
static int8_t gCloudYMax = -8;
static const uint16_t CLOUD_SPEED_Q = (8 << 8); // 8 px/s
static const uint16_t CLOUD_SPAWN_BASE_MS = 500;
static const uint16_t CLOUD_SPAWN_JITTER_MS = 250;
static const uint8_t  CLOUD_MIN_X_GAP = 62;
static const uint8_t  CLOUD_MAX_ACTIVE = 6;
static Cloud gClouds[6];
static unsigned long gCloudClockMs = 0;
static unsigned long gCloudNextSpawnDue = 0;
static uint16_t gCloudCarryQ = 0;
static void cloudsReset(){ for (uint8_t i=0;i<6;i++) gClouds[i].active = false; gCloudClockMs=0; gCloudNextSpawnDue=0; }
static uint8_t cloudsActiveCount(){ uint8_t c=0; for(uint8_t i=0;i<6;i++) if (gClouds[i].active) c++; return c; }
static int16_t cloudsRightmostX(){ int16_t mx=-32768; for(uint8_t i=0;i<6;i++) if (gClouds[i].active && gClouds[i].x>mx) mx=gClouds[i].x; return (mx==-32768)?-1000:mx; }
static void cloudSpawn(){
  if (cloudsActiveCount() >= CLOUD_MAX_ACTIVE) return;
  int16_t rx = cloudsRightmostX();
  if (rx > (int16_t)(SCREEN_WIDTH - CLOUD_MIN_X_GAP)) return;
  int8_t idx=-1; for(uint8_t i=0;i<6;i++){ if(!gClouds[i].active){ idx=i; break; } }
  if (idx<0) return;
  int8_t ymin = gCloudYMin; if (ymin < -CLOUD_H) ymin = -CLOUD_H;
  int8_t ymax = gCloudYMax; if (ymax > (GROUND_Y - CLOUD_H)) ymax = (GROUND_Y - CLOUD_H);
  if (ymax < ymin) ymax = ymin;
  int8_t y = ymin + (int8_t)(random((long)(ymax - ymin + 1)));
  gClouds[idx].x = SCREEN_WIDTH;
  gClouds[idx].y = y;
  gClouds[idx].active = true;
  gCloudNextSpawnDue = gCloudClockMs + CLOUD_SPAWN_BASE_MS + (uint16_t)random((long)(CLOUD_SPAWN_JITTER_MS + 1));
}
static void cloudsUpdate(unsigned long dt){
  gCloudClockMs += dt;
  if (gCloudClockMs >= gCloudNextSpawnDue){ cloudSpawn(); if (gCloudClockMs >= gCloudNextSpawnDue) gCloudNextSpawnDue = gCloudClockMs + 50; }
  uint32_t stepQ = ((uint32_t)CLOUD_SPEED_Q * dt) / 1000U;
  uint32_t totalQ = (uint32_t)gCloudCarryQ + stepQ;
  uint8_t dx = (uint8_t)(totalQ >> 8);
  gCloudCarryQ = (uint16_t)(totalQ & 0xFF);
  if (dx == 0) return;
  uint8_t cw = CLOUD_W;
  for (uint8_t i=0;i<6;i++){
    if (!gClouds[i].active) continue;
    gClouds[i].x -= dx;
    if ((int16_t)(gClouds[i].x + cw) < 0) gClouds[i].active = false;
  }
}
static void cloudDrawOne(const Cloud& c){
  uint8_t cw = CLOUD_W;
  for (uint8_t ry=0; ry<CLOUD_H; ++ry){
    int16_t y = c.y + ry;
    if (y < 0 || y >= SCREEN_HEIGHT) continue;
    for (uint8_t bx=0; bx<CLOUD_BYTES; ++bx){
      uint8_t b = pgm_read_byte(&CLOUD_BITS[ry][bx]);
      for (uint8_t bi=0; bi<8; ++bi){
        uint8_t bitX = bx*8 + bi; if (bitX >= cw) break;
        if (b & (uint8_t)(0x80 >> bi)){
          int16_t x = c.x + bitX;
          if (x >= 0 && x < SCREEN_WIDTH) display.drawPixel(x, y, SSD1306_WHITE);
        }
      }
    }
  }
}
static void cloudsDraw(){ for (uint8_t i=0;i<6;i++) if (gClouds[i].active) cloudDrawOne(gClouds[i]); }

// -------------------- HUD --------------------
static const uint8_t HUD_ICON[8] PROGMEM = { 0x06,0x0F,0x18,0xB8,0xF4,0xF8,0x28,0x28 };
static uint16_t hudScoreFromScroll(){ return (uint16_t)((uint16_t)( (uint32_t)(gScrollQ>>8) ) / 10U ); }
static void hudDraw(uint8_t lives){
  uint16_t score = hudScoreFromScroll();
  char s[7]; uint8_t n=0; uint16_t t=score;
  if(t==0) s[n++]='0'; else { while(t>0 && n<6){ s[n++] = '0' + (t%10); t/=10; } for(uint8_t i=0;i<n/2;i++){ char c=s[i]; s[i]=s[n-1-i]; s[n-1-i]=c; } }
  s[n]=0;
  display.setTextSize(1); display.setTextColor(SSD1306_WHITE); display.setCursor(0,0); display.print(s);
  int16_t x = SCREEN_WIDTH - 8; int16_t y = 0;
  uint8_t icons = lives>0 ? (uint8_t)min( (int)3, (int)(lives-1) ) : 0;
  for(uint8_t k=0;k<icons;k++){
    for(uint8_t ry=0; ry<8; ++ry){
      uint8_t b = pgm_read_byte(&HUD_ICON[ry]);
      for(uint8_t bi=0; bi<8; ++bi){
        if (b & (uint8_t)(0x80 >> bi)) display.drawPixel(x+bi, y+ry, SSD1306_WHITE);
      }
    }
    x -= 10;
  }
}

// -------------------- Player --------------------
enum PlayerState : uint8_t { PST_IDLE=0, PST_RUN=1, PST_JUMP=2, PST_DUCK=3, PST_HIT=4 };
struct Player {
  int16_t x;
  int16_t y;       // bottom y
  int16_t vy;      // vertical velocity
  enum PlayerState st;
  uint8_t animIdx;
  unsigned long animMs;
  bool started;
} gP;

static void playerInit(){
  gP.x = PLAYER_X;
  gP.y = GROUND_Y;
  gP.vy = 0;
  gP.st = PST_IDLE;
  gP.animIdx = 0;
  gP.animMs = 0;
  gP.started = false;
}

// -------------------- Bird (ASCII masks in PROGMEM) --------------------
#define BIRD_W 25
#define BIRD_H 21

// Frame 1
static const char b1_00[] PROGMEM = "-----------x-------------";
static const char b1_01[] PROGMEM = "----------x-x------------";
static const char b1_02[] PROGMEM = "-------xx-x--x-----------";
static const char b1_03[] PROGMEM = "------x-x--x--x----------";
static const char b1_04[] PROGMEM = "----xx-x---x---x---------";
static const char b1_05[] PROGMEM = "---x---x---x---x---------";
static const char b1_06[] PROGMEM = "---x----x-x----x---------";
static const char b1_07[] PROGMEM = "--x--x--x-x-----x--------";
static const char b1_08[] PROGMEM = "-x-------x------x--------";
static const char b1_09[] PROGMEM = "x---------x------x-------";
static const char b1_10[] PROGMEM = "-xxxxxxx----------xxxxxxx";
static const char b1_11[] PROGMEM = "--------x------------xxxx";
static const char b1_12[] PROGMEM = "---------x-------------x-";
static const char b1_13[] PROGMEM = "----------x---------xxxx-";
static const char b1_14[] PROGMEM = "-----------x-------x-----";
static const char b1_15[] PROGMEM = "------------xxxxxxx------";
static const char b1_16[] PROGMEM = "-------------------------";
static const char b1_17[] PROGMEM = "-------------------------";
static const char b1_18[] PROGMEM = "-------------------------";
static const char b1_19[] PROGMEM = "-------------------------";
static const char b1_20[] PROGMEM = "-------------------------";
static const char* const BIRD1[BIRD_H] PROGMEM = {
  b1_00,b1_01,b1_02,b1_03,b1_04,b1_05,b1_06,b1_07,b1_08,b1_09,
  b1_10,b1_11,b1_12,b1_13,b1_14,b1_15,b1_16,b1_17,b1_18,b1_19,b1_20
};

// Frame 2
static const char b2_00[] PROGMEM = "-------------------------";
static const char b2_01[] PROGMEM = "-------------------------";
static const char b2_02[] PROGMEM = "-------xx----------------";
static const char b2_03[] PROGMEM = "------x-x----------------";
static const char b2_04[] PROGMEM = "----xx-x-----------------";
static const char b2_05[] PROGMEM = "---x---x-----------------";
static const char b2_06[] PROGMEM = "---x----x----------------";
static const char b2_07[] PROGMEM = "--x--x--x-xxxxxx---------";
static const char b2_08[] PROGMEM = "-x-------x------x--------";
static const char b2_09[] PROGMEM = "x---------xx-----x-------";
static const char b2_10[] PROGMEM = "-xxxxxxx----------xxxxxxx";
static const char b2_11[] PROGMEM = "--------x------------xxxx";
static const char b2_12[] PROGMEM = "---------x-------------x-";
static const char b2_13[] PROGMEM = "---------x----------xxxx-";
static const char b2_14[] PROGMEM = "---------x---------x-----";
static const char b2_15[] PROGMEM = "---------x----xxxxx------";
static const char b2_16[] PROGMEM = "-------xxx---x-----------";
static const char b2_17[] PROGMEM = "-------x----x------------";
static const char b2_18[] PROGMEM = "-------x---x-------------";
static const char b2_19[] PROGMEM = "-------x--x--------------";
static const char b2_20[] PROGMEM = "-------xxx---------------";
static const char* const BIRD2[BIRD_H] PROGMEM = {
  b2_00,b2_01,b2_02,b2_03,b2_04,b2_05,b2_06,b2_07,b2_08,b2_09,
  b2_10,b2_11,b2_12,b2_13,b2_14,b2_15,b2_16,b2_17,b2_18,b2_19,b2_20
};

static inline void drawBirdMask(int16_t left, int16_t top, bool frame1){
  for (uint8_t r=0; r<BIRD_H; ++r){
    int16_t y = top + r;
    if (y < 0 || y >= SCREEN_HEIGHT) continue;
    const char* row = (const char*)pgm_read_ptr( frame1 ? &BIRD1[r] : &BIRD2[r] );
    for (uint8_t c=0; c<BIRD_W; ++c){
      char ch = (char)pgm_read_byte(&row[c]);
      if (ch == 'x'){
        int16_t x = left + c; if (x>=0 && x<SCREEN_WIDTH) display.drawPixel(x, y, SSD1306_WHITE);
      }
    }
  }
}

// Bird pool & anim
static Bird gBirds[3];
static unsigned long gBirdAnimMs = 0;
static bool gBirdFrame1 = true;
static unsigned long gBirdClockMs = 0;
static unsigned long gBirdNextSpawn = 1200;
static uint16_t gBirdCarryQ = 0;
static const uint16_t BIRD_SPAWN_BASE_MS = 1400;
static const uint16_t BIRD_SPAWN_JITTER_MS = 900;
static const uint8_t  BIRD_MAX_ACTIVE = 3;
static const uint8_t  BIRD_MIN_X_GAP = 54;
// Fixed duckable altitude: bottom ~GROUND_Y-8
static const int16_t BIRD_FIXED_TOP = (GROUND_Y - 27) - (BIRD_H/2);

static void birdsReset(){ for(uint8_t i=0;i<3;i++) gBirds[i].active=false; gBirdClockMs=0; gBirdNextSpawn=900; gBirdCarryQ=0; gBirdAnimMs=0; gBirdFrame1=true; }
static uint8_t birdsActiveCount(){ uint8_t c=0; for(uint8_t i=0;i<3;i++) if(gBirds[i].active) c++; return c; }
static int16_t birdsRightmostX(){ int16_t mx=-32768; for(uint8_t i=0;i<3;i++) if(gBirds[i].active && gBirds[i].x>mx) mx=gBirds[i].x; return (mx==-32768)?-1000:mx; }
static void birdSpawn(){
  if (birdsActiveCount()>=BIRD_MAX_ACTIVE) return;
  int16_t rx = birdsRightmostX();
  if (rx > (int16_t)(SCREEN_WIDTH - BIRD_MIN_X_GAP)) return;
  int8_t idx=-1; for(uint8_t i=0;i<3;i++){ if(!gBirds[i].active){ idx=i; break; } }
  if (idx<0) return;
  gBirds[idx].x = SCREEN_WIDTH;
  int8_t __baseTop = (int8_t)BIRD_FIXED_TOP;
int8_t __laneOffset = (random(2) ? -12 : 0);
gBirds[idx].top = (int8_t)(__baseTop + __laneOffset);
gBirds[idx].active = true;
  gBirdNextSpawn = gBirdClockMs + BIRD_SPAWN_BASE_MS + (uint16_t)random((long)(BIRD_SPAWN_JITTER_MS+1));
}
static void birdsUpdate(unsigned long dt, bool allowSpawn){
  gBirdClockMs += dt;
  gBirdAnimMs += dt;
  if (gBirdAnimMs >= 250){ gBirdAnimMs -= 250; gBirdFrame1 = !gBirdFrame1; } // 0.25s loop
  if (allowSpawn && gBirdClockMs >= gBirdNextSpawn) birdSpawn();
  uint32_t stepQ = ((uint32_t)currentSpeedQ() * 11U * dt) / (1000U * 10U);
  uint32_t totalQ = (uint32_t)gBirdCarryQ + stepQ;
  uint8_t dx = (uint8_t)(totalQ >> 8);
  gBirdCarryQ = (uint16_t)(totalQ & 0xFF);
  if (dx){
    for(uint8_t i=0;i<3;i++){
      if(!gBirds[i].active) continue;
      gBirds[i].x -= dx;
      if ((int16_t)(gBirds[i].x + BIRD_W) < 0) gBirds[i].active=false;
    }
  }
}
static void birdsDraw(){
  for(uint8_t i=0;i<3;i++) if(gBirds[i].active) drawBirdMask(gBirds[i].x, gBirds[i].top, gBirdFrame1);
}

// -------------------- CACTUS (5 sprites, 20x20) --------------------
#define CACTUS_W 20
#define CACTUS_H 20

// sprite1
static const char c1_00[] PROGMEM = "--------------------";
static const char c1_01[] PROGMEM = "--------------------";
static const char c1_02[] PROGMEM = "------------xxxx----";
static const char c1_03[] PROGMEM = "-----------x----x---";
static const char c1_04[] PROGMEM = "----------x-----x---";
static const char c1_05[] PROGMEM = "------xxx-x-x----x--";
static const char c1_06[] PROGMEM = "-----x---x-------x--";
static const char c1_07[] PROGMEM = "----x-x---x---x-x---";
static const char c1_08[] PROGMEM = "----x---x-x--x---x--";
static const char c1_09[] PROGMEM = "----x-----x------x--";
static const char c1_10[] PROGMEM = "--xxx--x--x-----x---";
static const char c1_11[] PROGMEM = "--x--x----x---x--x--";
static const char c1_12[] PROGMEM = "-x--xx--x-x-------x-";
static const char c1_13[] PROGMEM = "x----x------x------x";
static const char c1_14[] PROGMEM = "x--x-x----x--------x";
static const char c1_15[] PROGMEM = "-x---x--x-x----x--xx";
static const char c1_16[] PROGMEM = "xx---x-x--x--------x";
static const char c1_17[] PROGMEM = "x-x-x--------x----xx";
static const char c1_18[] PROGMEM = "xxx--x----x------xx-";
static const char c1_19[] PROGMEM = "-x-xxx----x-----x---";
static const char* const CACTUS1[CACTUS_H] PROGMEM = {
  c1_00,c1_01,c1_02,c1_03,c1_04,c1_05,c1_06,c1_07,c1_08,c1_09,
  c1_10,c1_11,c1_12,c1_13,c1_14,c1_15,c1_16,c1_17,c1_18,c1_19
};
// sprite2
static const char c2_00[] PROGMEM = "---------xxx--------";
static const char c2_01[] PROGMEM = "--------x---x-------";
static const char c2_02[] PROGMEM = "-------x----x-------";
static const char c2_03[] PROGMEM = "------x-x----x------";
static const char c2_04[] PROGMEM = "------x-x--x-x------";
static const char c2_05[] PROGMEM = "------x--x---x------";
static const char c2_06[] PROGMEM = "-------x------x-----";
static const char c2_07[] PROGMEM = "------x-x--x--x-----";
static const char c2_08[] PROGMEM = "------x-x----x------";
static const char c2_09[] PROGMEM = "------x-------x-----";
static const char c2_10[] PROGMEM = "-----xxx--x---x-----";
static const char c2_11[] PROGMEM = "----xx--x--x-x------";
static const char c2_12[] PROGMEM = "----x---x----x------";
static const char c2_13[] PROGMEM = "----xx---x-x-x------";
static const char c2_14[] PROGMEM = "----x--x----x-------";
static const char c2_15[] PROGMEM = "----xx---x--x-------";
static const char c2_16[] PROGMEM = "-----x-----x-x------";
static const char c2_17[] PROGMEM = "------x------x------";
static const char c2_18[] PROGMEM = "-------x-x-x-x------";
static const char c2_19[] PROGMEM = "-------x----x-------";
static const char* const CACTUS2[CACTUS_H] PROGMEM = {
  c2_00,c2_01,c2_02,c2_03,c2_04,c2_05,c2_06,c2_07,c2_08,c2_09,
  c2_10,c2_11,c2_12,c2_13,c2_14,c2_15,c2_16,c2_17,c2_18,c2_19
};
// sprite3
static const char c3_00[] PROGMEM = "--------------------";
static const char c3_01[] PROGMEM = "--------xxx---------";
static const char c3_02[] PROGMEM = "-------x---x--------";
static const char c3_03[] PROGMEM = "------x-----x-------";
static const char c3_04[] PROGMEM = "------x-x---x-------";
static const char c3_05[] PROGMEM = "----xx-x-----xx-xx--";
static const char c3_06[] PROGMEM = "---x--x-----x--x-x--";
static const char c3_07[] PROGMEM = "--x---x--x-x----x---";
static const char c3_08[] PROGMEM = "--x-x-x-x--x-----x--";
static const char c3_09[] PROGMEM = "--x---x----x--x--x--";
static const char c3_10[] PROGMEM = "--x-----x--x----x---";
static const char c3_11[] PROGMEM = "--x--------x--x-x---";
static const char c3_12[] PROGMEM = "---xx--x---------x--";
static const char c3_13[] PROGMEM = "-----x----x--x--x---";
static const char c3_14[] PROGMEM = "------x--------x----";
static const char c3_15[] PROGMEM = "-----x--x----xx-----";
static const char c3_16[] PROGMEM = "-----x----x-x-------";
static const char c3_17[] PROGMEM = "-----x------x-------";
static const char c3_18[] PROGMEM = "------x-----x-------";
static const char c3_19[] PROGMEM = "------x----x--------";
static const char* const CACTUS3[CACTUS_H] PROGMEM = {
  c3_00,c3_01,c3_02,c3_03,c3_04,c3_05,c3_06,c3_07,c3_08,c3_09,
  c3_10,c3_11,c3_12,c3_13,c3_14,c3_15,c3_16,c3_17,c3_18,c3_19
};
// sprite4
static const char c4_00[] PROGMEM = "--------------------";
static const char c4_01[] PROGMEM = "--------------------";
static const char c4_02[] PROGMEM = "--------------------";
static const char c4_03[] PROGMEM = "--------------------";
static const char c4_04[] PROGMEM = "--------------------";
static const char c4_05[] PROGMEM = "--------xxx---------";
static const char c4_06[] PROGMEM = "-------x---x--------";
static const char c4_07[] PROGMEM = "------x----x--------";
static const char c4_08[] PROGMEM = "------x--x-x-x------";
static const char c4_09[] PROGMEM = "-------x---xx-xx----";
static const char c4_10[] PROGMEM = "--xx-xxx-x-x----x---";
static const char c4_11[] PROGMEM = "--x-x--x---x-x--x---";
static const char c4_12[] PROGMEM = "---x---x--x----xx---";
static const char c4_13[] PROGMEM = "--x----x--------x---";
static const char c4_14[] PROGMEM = "--x--x-x----x---x---";
static const char c4_15[] PROGMEM = "---x---x------xx----";
static const char c4_16[] PROGMEM = "--xx-----x--xx------";
static const char c4_17[] PROGMEM = "--x---x------x------";
static const char c4_18[] PROGMEM = "--xx--------x-------";
static const char c4_19[] PROGMEM = "---x-------x--------";
static const char* const CACTUS4[CACTUS_H] PROGMEM = {
  c4_00,c4_01,c4_02,c4_03,c4_04,c4_05,c4_06,c4_07,c4_08,c4_09,
  c4_10,c4_11,c4_12,c4_13,c4_14,c4_15,c4_16,c4_17,c4_18,c4_19
};
// sprite5
static const char c5_00[] PROGMEM = "--------------------";
static const char c5_01[] PROGMEM = "--------xxx---------";
static const char c5_02[] PROGMEM = "------xx---x--------";
static const char c5_03[] PROGMEM = "------x-----x-------";
static const char c5_04[] PROGMEM = "-----x---x--x-------";
static const char c5_05[] PROGMEM = "-----x-----x--------";
static const char c5_06[] PROGMEM = "----xx---x-x--------";
static const char c5_07[] PROGMEM = "---x--x----x--------";
static const char c5_08[] PROGMEM = "--x---x-x--xxxxx----";
static const char c5_09[] PROGMEM = "--x-x-x--x-x----x---";
static const char c5_10[] PROGMEM = "--x---x----x---x----";
static const char c5_11[] PROGMEM = "--x-----x--x-x--x---";
static const char c5_12[] PROGMEM = "--x--x-----x----x---";
static const char c5_13[] PROGMEM = "--x--------x---x----";
static const char c5_14[] PROGMEM = "---x-xx--x-----x----";
static const char c5_15[] PROGMEM = "----x-x-----x---x---";
static const char c5_16[] PROGMEM = "------x-x-------x---";
static const char c5_17[] PROGMEM = "------x----x--xxx---";
static const char c5_18[] PROGMEM = "-----x--x--x-xx-----";
static const char c5_19[] PROGMEM = "-----xx----x-x------";
static const char* const CACTUS5[CACTUS_H] PROGMEM = {
  c5_00,c5_01,c5_02,c5_03,c5_04,c5_05,c5_06,c5_07,c5_08,c5_09,
  c5_10,c5_11,c5_12,c5_13,c5_14,c5_15,c5_16,c5_17,c5_18,c5_19
};

static const char* const* const CACTUS_FRAMES[5] PROGMEM = { CACTUS1, CACTUS2, CACTUS3, CACTUS4, CACTUS5 };

static inline void drawCactusMask(int16_t left, int16_t top, uint8_t idx){
  const char* const* rows = (const char* const*)pgm_read_ptr(&CACTUS_FRAMES[idx % 5]);
  for (uint8_t r=0; r<CACTUS_H; ++r){
    int16_t y = top + r;
    if (y < 0 || y >= SCREEN_HEIGHT) continue;
    const char* row = (const char*)pgm_read_ptr(&rows[r]);
    for (uint8_t c=0; c<CACTUS_W; ++c){
      char ch = (char)pgm_read_byte(&row[c]);
      if (ch == 'x'){
        int16_t x = left + c; if (x>=0 && x<SCREEN_WIDTH) display.drawPixel(x, y, SSD1306_WHITE);
      }
    }
  }
}

// Pool & logic
static Cactus gCactus[3];
static unsigned long gCactusClockMs = 0;
static unsigned long gCactusNextSpawn = 900;
static uint16_t gCactusCarryQ = 0;
static const uint16_t CACTUS_SPAWN_BASE_MS = 1100;
static const uint16_t CACTUS_SPAWN_JITTER_MS = 700;
static const uint8_t  CACTUS_MAX_ACTIVE = 3;
static const uint8_t  CACTUS_MIN_X_GAP = 56;

static void cactiReset(){ for(uint8_t i=0;i<3;i++) gCactus[i].active=false; gCactusClockMs=0; gCactusNextSpawn=700; gCactusCarryQ=0; }
static uint8_t cactiActiveCount(){ uint8_t c=0; for(uint8_t i=0;i<3;i++) if(gCactus[i].active) c++; return c; }
static int16_t cactiRightmostX(){ int16_t mx=-32768; for(uint8_t i=0;i<3;i++) if(gCactus[i].active && gCactus[i].x>mx) mx=gCactus[i].x; return (mx==-32768)?-1000:mx; }
static void cactusSpawn(){
  if (cactiActiveCount()>=CACTUS_MAX_ACTIVE) return;
  int16_t rx = cactiRightmostX();
  if (rx > (int16_t)(SCREEN_WIDTH - CACTUS_MIN_X_GAP)) return;
  int8_t idx=-1; for(uint8_t i=0;i<3;i++){ if(!gCactus[i].active){ idx=i; break; } }
  if (idx<0) return;
  gCactus[idx].x = SCREEN_WIDTH;
  gCactus[idx].top = GROUND_Y - (CACTUS_H - 1);
  gCactus[idx].idx = (uint8_t)random(5);
  gCactus[idx].active = true;
  gCactusNextSpawn = gCactusClockMs + CACTUS_SPAWN_BASE_MS + (uint16_t)random((long)(CACTUS_SPAWN_JITTER_MS+1));
}
static void cactiUpdate(unsigned long dt, bool allowSpawn){
  gCactusClockMs += dt;
  if (allowSpawn && gCactusClockMs >= gCactusNextSpawn) cactusSpawn();
  uint32_t stepQ = ((uint32_t)currentSpeedQ() * dt) / 1000U;
  uint32_t totalQ = (uint32_t)gCactusCarryQ + stepQ;
  uint8_t dx = (uint8_t)(totalQ >> 8);
  gCactusCarryQ = (uint16_t)(totalQ & 0xFF);
  if (dx){
    for(uint8_t i=0;i<3;i++){
      if(!gCactus[i].active) continue;
      gCactus[i].x -= dx;
      if ((int16_t)(gCactus[i].x + CACTUS_W) < 0) gCactus[i].active=false;
    }
  }
}
static void cactiDraw(){ for(uint8_t i=0;i<3;i++) if(gCactus[i].active) drawCactusMask(gCactus[i].x, gCactus[i].top, gCactus[i].idx); }


// -------------------- Unified Obstacle Spawner --------------------
static unsigned long gObsClockMs = 0;
static unsigned long gObsNextSpawn = 800;  // soft initial delay
static const uint16_t OBS_SPAWN_BASE_MS   = 1200;  // overall cadence similar to prior tuning
static const uint16_t OBS_SPAWN_JITTER_MS = 900;

// Immediate spawn readiness checks (bypass each class's internal timers)
static inline bool canSpawnCactusNow(){
  if (cactiActiveCount() >= CACTUS_MAX_ACTIVE) return false;
  int16_t rx = cactiRightmostX();
  if (rx > (int16_t)(SCREEN_WIDTH - CACTUS_MIN_X_GAP)) return false;
  return true;
}
static inline bool canSpawnBirdNow(){
  if (birdsActiveCount() >= BIRD_MAX_ACTIVE) return false;
  int16_t rx = birdsRightmostX();
  if (rx > (int16_t)(SCREEN_WIDTH - BIRD_MIN_X_GAP)) return false;
  return true;
}

// Weights chosen so P(cactus) ≈ 1400/(1100+1400) and P(bird) ≈ 1100/(1100+1400)
static inline uint8_t pickObsTypeWeighted(){ // 0=cactus, 1=bird
  const uint16_t wC = BIRD_SPAWN_BASE_MS;    // 1400
  const uint16_t wB = CACTUS_SPAWN_BASE_MS;  // 1100
  uint16_t r = (uint16_t)random((long)(wC + wB));
  return (r < wC) ? 0 : 1;
}

// Unified update: only one type gets to spawn per tick; movement for both always updates
static void obstaclesUpdateUnified(unsigned long dt, bool allowSpawn){
  gObsClockMs += dt;

  if (allowSpawn && gObsClockMs >= gObsNextSpawn){
    uint8_t t = pickObsTypeWeighted();  // 0=cactus, 1=bird
    // Try chosen type first; if no room, try the other
    for (uint8_t i=0; i<2; ++i){
      if (t == 0){
        if (canSpawnCactusNow()) { cactusSpawn(); break; }
      }else{
        if (canSpawnBirdNow())   { birdSpawn();   break; }
      }
      t ^= 1; // toggle between types
    }
    /* Distance-locked spawn cadence: keep ~constant world-distance between spawns.
   Convert the legacy time-based BASE_MS/JITTER_MS into base/jitter distances at RUN_BASE_SPEED,
   then scale the *time* until next spawn by the current speed. Faster speed → sooner spawn (same distance).
*/
{
  uint32_t speed_px_s = ((uint32_t)currentSpeedQ()) >> 8;     // px/s
  if (speed_px_s == 0) speed_px_s = 1;                        // guard
  uint32_t base_dist_px   = (((uint32_t)RUN_BASE_SPEED_Q >> 8) * (uint32_t)OBS_SPAWN_BASE_MS) / 1000U;
  uint32_t jitter_dist_px = (((uint32_t)RUN_BASE_SPEED_Q >> 8) * (uint32_t)OBS_SPAWN_JITTER_MS) / 1000U;
  uint32_t dist_px = base_dist_px + (uint32_t)random((long)(jitter_dist_px + 1));
  uint32_t delta_ms = (dist_px * 1000U) / speed_px_s;         // time to cover that distance at current speed
  gObsNextSpawn = gObsClockMs + (uint16_t)delta_ms;
}
  }

  // Always update movement/cleanup; internal spawns disabled (false)
  cactiUpdate(dt, false);
  birdsUpdate(dt, false);
}



// AABB for player & enemies
static inline bool aabbOverlap(int16_t ax0,int16_t ay0,int16_t ax1,int16_t ay1, int16_t bx0,int16_t by0,int16_t bx1,int16_t by1){
  return !(ax1 < bx0 || bx1 < ax0 || ay1 < by0 || by1 < ay0);
}
static void getPlayerAABB(int16_t* x0,int16_t* y0,int16_t* x1,int16_t* y1){
  int16_t cx = gP.x + (SPR_W/2);
  int16_t w = 16;
  int16_t h = (gP.st == PST_DUCK) ? 6 : 24;
  int16_t left = cx - (w/2);
  int16_t right = left + (w-1);
  int16_t bottom = gP.y;
  int16_t top = bottom - (h-1);
  *x0 = left; *x1 = right; *y0 = top; *y1 = bottom;
}
static void getBirdAABB(const Bird& b, int16_t* x0,int16_t* y0,int16_t* x1,int16_t* y1){
  int16_t cx = b.x + (BIRD_W/2);
  int16_t cy = b.top + (BIRD_H/2);
  *x0 = cx - 4;
  *x1 = cx + 4 - 1;
  *y0 = cy - 5;
  *y1 = cy + 5 - 1;
}
// Cactus collision box: 8x14 centered horizontally, bottom at GROUND_Y
static void getCactusAABB(const Cactus& c, int16_t* x0,int16_t* y0,int16_t* x1,int16_t* y1){
  int16_t cx = c.x + (CACTUS_W/2);
  int16_t w = 7;
  int16_t h = 13;
  int16_t left = cx - (w/2);
  int16_t right = left + (w-1);
  int16_t bottom = GROUND_Y;
  int16_t top = bottom - (h-1);
  *x0 = left; *x1 = right; *y0 = top; *y1 = bottom;
}

// -------------------- Game State (lives, hit flow) --------------------
static uint8_t gLives = 4; // 1 + 3 extra
static bool gInHit = false;
static unsigned long gHitStartMs = 0;
static int16_t gHitOrigX = 0;
static int16_t gHitTargetX = 0;
static int16_t gHitOrigY = 0;
static uint16_t gHitDecelFromQ = RUN_BASE_SPEED_Q;

static void startHit(unsigned long now){
  gInHit = true;
  gHitStartMs = now;
  gHitOrigX = gP.x;
  gHitOrigY = gP.y;   // capture current Y (may be mid-air)
  gHitTargetX = (SCREEN_WIDTH/2) - (SPR_W/2);
  if (gHitTargetX < 4) gHitTargetX = 4;
  gHitDecelFromQ = gWorldSpeedQ;
  gP.st = PST_HIT;
  gP.animMs = 0;
  gP.vy = 0;
  birdsReset();
  cactiReset();
}

static inline uint16_t currentSpeedQ(){
  // During hit flow or before start, honor the scripted world speed only
  if (gInHit || !gP.started) return gWorldSpeedQ;
  uint32_t distPx = (gLifeScrollQ >> 8);                      // distance in pixels
  uint32_t growthQ = ((uint32_t)SPEED_GROWTH_PER_1000PX_Q * distPx) / 1000U;
  if (growthQ > SPEED_GROWTH_MAX_Q) growthQ = SPEED_GROWTH_MAX_Q;
  uint32_t sp = (uint32_t)gWorldSpeedQ + growthQ;
  // Absolute cap to keep sanity: base + max_growth
  uint32_t cap = (uint32_t)RUN_BASE_SPEED_Q + (uint32_t)SPEED_GROWTH_MAX_Q;
  if (sp > cap) sp = cap;
  return (uint16_t)sp;
}

static void updateHitFlow(unsigned long now, unsigned long dt){
  int16_t flowduration = 500; 
  if (!gInHit) return;
  (void)dt;
  unsigned long t = now - gHitStartMs;
  if (t < (flowduration / 2)) {
    gP.animIdx = 0; 
  } else {
    gP.animIdx = 1;
  }

  int16_t dx = gHitTargetX - gHitOrigX;
  if (t < flowduration){
    gWorldSpeedQ = (uint16_t)(( (uint32_t)gHitDecelFromQ * (uint32_t)(flowduration - t) ) / (flowduration * 2));
    gP.x = gHitOrigX + (int16_t)( ( (int32_t)dx * (int32_t)t ) / flowduration );
    if (gP.y < GROUND_Y){
      int16_t dy = GROUND_Y - gHitOrigY;
      gP.y = gHitOrigY + (int16_t)( (3 * (int32_t)dy * (int32_t)t ) / flowduration );
      if (gP.y > GROUND_Y){ gP.y = GROUND_Y; }
    } else {
      gP.y = GROUND_Y;
    }
  } else {
    gP.x = gHitTargetX;
    gP.y = GROUND_Y;
    gWorldSpeedQ = 0;
  }
  if (t >= 1300){
    if (gLives > 0) gLives--;
    if (gLives > 0){
      gWorldSpeedQ = RUN_BASE_SPEED_Q;
      gLifeScrollQ = 0;
      gP.x = gHitOrigX;
      gP.y = GROUND_Y; gP.vy = 0;
      gP.st = PST_IDLE; gP.animIdx = 0; gP.animMs = 0;
      gP.started = false;
      gInHit = false;
      birdsReset();
    } else {
      uint16_t score = hudScoreFromScroll();
      gNewHigh = (score > gHighScore);                    
      if (gNewHigh){                                      
        gHighScore = score;
        saveSignature();
        eeWriteU32(EE_ADDR_HS, gHighScore);
      }
      page = PAGE_GAMEOVER;
      gInHit = false;
      gWorldSpeedQ = RUN_BASE_SPEED_Q;
    }
  }
}

// -------------------- Player Update/Draw --------------------
static void playerUpdate(unsigned long now, unsigned long dt, bool btnJumpHeld, bool btnDuckHeld, bool edgeJump, bool edgeDuck){
  if (!gP.started && (edgeJump || edgeDuck)){
    gP.started = true; gP.st = PST_RUN; gP.animIdx = 0; gP.animMs = 0;
    gObsClockMs = 0;           // reset unified spawn clock
    gObsNextSpawn = 800;       // same soft start delay
  }

  switch (gP.st){
    case PST_IDLE: {
      gP.animMs += dt;
      if (gP.animIdx == 0){ if (gP.animMs >= 2000){ gP.animMs = 0; gP.animIdx = 1; } }
      else { if (gP.animMs >= 250){ gP.animMs = 0; gP.animIdx = 0; } }
    } break;

    case PST_RUN: {
      if (gP.y == GROUND_Y && edgeJump){ gP.st = PST_JUMP; gP.vy = -18; gP.animMs = 0; break; }
      if (btnDuckHeld){ gP.st = PST_DUCK; gP.animIdx = 0; gP.animMs = 0; break; }
      gP.animMs += dt;
      uint16_t spq = currentSpeedQ(); const uint16_t REF_SPEED_Q = (64<<8);
      uint16_t msPerFrame = (uint16_t)((uint32_t)gRunDuckMs * (uint32_t)REF_SPEED_Q / (uint32_t)spq);
      if (msPerFrame<60) msPerFrame=60;
      if (gP.animMs >= msPerFrame){ gP.animMs = 0; gP.animIdx ^= 1; }
    } break;

    case PST_DUCK: {
      if (!btnDuckHeld){ gP.st = PST_RUN; gP.animIdx = 0; gP.animMs = 0; break; }
      gP.animMs += dt;
      uint16_t spq = currentSpeedQ(); const uint16_t REF_SPEED_Q = (64<<8);
      uint16_t msPerFrame = (uint16_t)((uint32_t)gRunDuckMs * (uint32_t)REF_SPEED_Q / (uint32_t)spq);
      if (msPerFrame<60) msPerFrame=60;
      if (gP.animMs >= msPerFrame){ gP.animMs = 0; gP.animIdx ^= 1; }
    } break;

    case PST_JUMP: {
      gP.vy += 2;
      gP.y += gP.vy / 3;
      if (gP.y >= GROUND_Y){
        gP.y = GROUND_Y; gP.vy = 0;
        gP.st = gP.started ? PST_RUN : PST_IDLE;
        gP.animIdx = 0; gP.animMs = 0;
      }
      (void)btnDuckHeld; (void)edgeDuck; (void)now;
    } break;

    case PST_HIT: {
      // handled in updateHitFlow()
    } break;
  }

  if (gP.started && (gP.st==PST_RUN || gP.st==PST_DUCK || gP.st==PST_JUMP || gInHit)){
    uint32_t add = ((uint32_t)currentSpeedQ() * (uint32_t)dt) / 1000U;
    gScrollQ += add;
    gLifeScrollQ += add;
  }

  cloudsUpdate(dt);
}

static void playerDraw(){
  extern const uint8_t idle0_bits[SPR_H][SPR_BYTES];
  switch (gP.st){
    case PST_IDLE: drawSpriteBits(gP.x, gP.y, (gP.animIdx==0)?idle0_bits:idle1_bits); break;
    case PST_RUN:  drawSpriteBits(gP.x, gP.y, (gP.animIdx==0)?run0_bits:run1_bits); break;
    case PST_DUCK: drawSpriteBits(gP.x, gP.y, (gP.animIdx==0)?duck0_bits:duck1_bits); break;
    case PST_JUMP: drawSpriteBits(gP.x, gP.y, jump0_bits); break;
    case PST_HIT:  drawSpriteBits(gP.x, gP.y, (gP.animIdx==0)?hit0_bits:hit1_bits); break;
  }
}
// -------------------- Game Page --------------------
static bool gGameInit = false;
static unsigned long lastTickMs = 0;
static bool gInputGate = false;

static void pageGame(){
  unsigned long now = millis();
  static bool prevJump=false, prevDuck=false;

  if (!gGameInit){
    playerInit();
    gLives = 4;
    gWorldSpeedQ = RUN_BASE_SPEED_Q;
    gScrollQ = 0;
    gLifeScrollQ = 0;
    birdsReset();
    cactiReset();
    cloudsReset();
    lastTickMs = now;
    gGameInit = true;
    gInputGate = true;
    gNewHigh = false;
    prevJump = prevDuck = false;
    gObsClockMs = 0;
    gObsNextSpawn = 800;
  }

  unsigned long dt = (now - lastTickMs);
  if (dt > 50) dt = 50;
  lastTickMs = now;

  bool jumpHeld = (digitalRead(BTN_NEXT) == LOW);
  bool duckHeld = (digitalRead(BTN_PREV) == LOW);
  bool edgeJump = (!prevJump && jumpHeld);
  bool edgeDuck = (!prevDuck && duckHeld);

  if (gInputGate){
    if (!jumpHeld && !duckHeld){ gInputGate = false; }
    else { jumpHeld = duckHeld = false; edgeJump = edgeDuck = false; }
  }

  prevJump = jumpHeld; 
  prevDuck = duckHeld;

  playerUpdate(now, dt, jumpHeld, duckHeld, edgeJump, edgeDuck);

  // Update enemies (no spawning while hit flow active)
  obstaclesUpdateUnified(dt, (!gInHit && gP.started));

  // Collisions
  if (!gInHit){
    int16_t ax0,ay0,ax1,ay1; getPlayerAABB(&ax0,&ay0,&ax1,&ay1);
    // Cactus first (ground obstacles)
    for(uint8_t i=0;i<3;i++){
      if(!gCactus[i].active) continue;
      int16_t bx0,by0,bx1,by1; getCactusAABB(gCactus[i], &bx0,&by0,&bx1,&by1);
      if (aabbOverlap(ax0,ay0,ax1,ay1, bx0,by0,bx1,by1)){ startHit(now); break; }
    }
    // Birds
    if (!gInHit){
      for(uint8_t i=0;i<3;i++){
        if(!gBirds[i].active) continue;
        int16_t bx0,by0,bx1,by1; getBirdAABB(gBirds[i], &bx0,&by0,&bx1,&by1);
        if (aabbOverlap(ax0,ay0,ax1,ay1, bx0,by0,bx1,by1)){ startHit(now); break; }
      }
    }
  }


  display.clearDisplay();
  updateHitFlow(now, dt);
  cloudsDraw();
  hudDraw(gLives);
  uint16_t xoff = (uint16_t)(gScrollQ >> 8);
  drawTerrain(xoff);
  cactiDraw();
  birdsDraw();
  playerDraw();

  // hint text when idle
  if (gP.st == PST_IDLE){
    display.setTextColor(SSD1306_WHITE);
    drawCenteredText(F("READY?"), 18);
  } else if (gP.st == PST_HIT){
    display.setTextColor(SSD1306_WHITE);
    drawCenteredText(F("OUCH!!"), 18);
  }

  display.display();
}

// -------------------- Game Over Page --------------------
static void pageGameOver(bool anyKey){
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  const uint8_t goSz = 2;
  const int16_t charH = 9;
  const int16_t goH = charH * 2 * goSz;
  const int16_t goY = (SCREEN_HEIGHT - goH) / 2;
  display.setTextSize(2);
  display.setCursor(goY, 28);
  display.print(F("GAME OVER"));
  display.setTextSize(1);

  const int16_t goBottom = goY + goH;
  const char* prefix = "Score: ";
  uint16_t score = hudScoreFromScroll();
  char sScore[24];
  snprintf(sScore, sizeof(sScore), "%s%u", prefix, (unsigned)score);
  const int16_t scoreY = goBottom + ((SCREEN_HEIGHT - goBottom) - charH) / 2;
  drawCenteredTextRAM(sScore, scoreY);

  if (gNewHigh){
    const int16_t hsY = 10;
    drawCenteredText(F("HIGHSCORE"), hsY);
  }

  display.display();
  if (anyKey){ gFirstPageGate = true; page = PAGE_START; }
}

// -------------------- Setup/Loop --------------------
static bool enterPrev = false;
static unsigned long enterDownAt = 0;
static bool enterLongFired = false;
static const unsigned long ENTER_LONG_MS = 650;
static const unsigned long ENTER_DEBOUNCE_MS = 30;
static bool nextPrevPressedPrev = false;
static bool nextNextPressedPrev = false;

void setup(){
  randomSeed(1);
  pinMode(BTN_ENTER, INPUT_PULLUP);
  pinMode(BTN_NEXT,  INPUT_PULLUP);
  pinMode(BTN_PREV,  INPUT_PULLUP);
  Wire.begin();
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) for(;;);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.display();
  loadHighScore();
}

void loop(){
  unsigned long now = millis();

  bool enterNow = (digitalRead(BTN_ENTER) == LOW);
  bool nextNow  = (digitalRead(BTN_NEXT)  == LOW);
  bool prevNow  = (digitalRead(BTN_PREV)  == LOW);

  bool enterShort = false, enterLong = false;
  if (!enterPrev && enterNow){ enterDownAt = now; enterLongFired = false; }
  else if (enterPrev && enterNow){
    if (!enterLongFired && (now - enterDownAt) >= ENTER_LONG_MS){ enterLong = true; enterLongFired = true; }
  } else if (enterPrev && !enterNow){
    unsigned long dur = now - enterDownAt;
    if (!enterLongFired && dur >= ENTER_DEBOUNCE_MS && dur < ENTER_LONG_MS){ enterShort = true; }
  }
  enterPrev = enterNow;

  bool nextEdge = (!nextNextPressedPrev && nextNow);
  bool prevEdge = (!nextPrevPressedPrev && prevNow);
  nextNextPressedPrev = nextNow;
  nextPrevPressedPrev = prevNow;

  if (now - blinkMs >= 500){ blinkMs = now; blinkOn = !blinkOn; }

  static Page lastPage = PAGE_START;
  if (page != lastPage){ if (page == PAGE_GAME) gGameInit = false; lastPage = page; }

  switch (page){
    case PAGE_START:    pageStart(nextNow, prevNow, enterShort, enterLong); break;
    case PAGE_GAME:     pageGame(); break;
    case PAGE_MENU:     pageMenu(nextEdge, prevEdge, (enterShort||enterLong)); break;
    case PAGE_ABOUT:    pageAbout(enterShort||enterLong||nextEdge||prevEdge); break;
    case PAGE_GAMEOVER: pageGameOver(enterShort||enterLong||nextEdge||prevEdge); break;
  }
}
