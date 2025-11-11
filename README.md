# SkippyGecko (Arduino Game)

An endless runner for Arduino Nano/Uno with a 128x64 I2C SSD1306 OLED. Features jumping/ducking obstacles (cacti/birds), parallax clouds, distance-based speed scaling, EEPROM high score, a start/menu/about flow, and standby sleep/wake.

This is an original hobby project; not affiliated with any third-party brand. Recommended board: “Arduino Nano Super Mini” (ATmega328P).

## Requirements
- Arduino IDE or Arduino CLI
- Target board: Arduino Nano/Uno (ATmega328P)
- 128x64 SSD1306 OLED via I2C (default address 0x3C)
- Libraries:
  - Adafruit GFX Library
  - Adafruit SSD1306
  - Wire (bundled)
  - EEPROM (bundled on AVR)

Install libraries from Arduino IDE:
- Sketch → Include Library → Manage Libraries
- Search and install “Adafruit GFX Library” and “Adafruit SSD1306”

## Wiring (Nano/Uno)
- SSD1306 OLED (I2C):
  - SDA → A4
  - SCL → A5
  - VCC → 5V
  - GND → GND
- Buttons (internal pull-ups, active-LOW):
  - `BTN_NEXT` on D7 (Jump)
  - `BTN_PREV` on D6 (Duck)
  - `BTN_ENTER` on D3 (short = sleep/wake, long = open menu on Start)

Note: For other boards, adjust I2C pins accordingly.

## Repo Layout
- `project.ino`: main game sketch
- `src/`: assets (images used for design; the sketch embeds 1-bit bitmaps)

## Build & Upload
1) Open `project.ino` in Arduino IDE.
2) Tools:
   - Board: Arduino Nano (or Uno)
   - Processor: ATmega328P (Old Bootloader if your Nano clone needs it)
   - Port: select the correct COM port
3) Ensure required libraries are installed.
4) Click Upload.

Notes:
- I2C address is `0x3C`; if your display differs, change it in `display.begin(...)`.
- High score is stored in EEPROM.
- Arduino IDE may prompt to rename the folder to match `project.ino`. You can accept or keep your folder and open the file directly.

## Controls
- D7 (hold/tap): jump
- D6 (hold): duck
- D3 short-press: standby/sleep; press again to wake (from Start)
- D3 long-press (Start): open menu (About, Reset Highscore, Back)

## License
MIT — see `LICENSE`.


