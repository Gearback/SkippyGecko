# SkippyGecko

A tiny monochrome endless runner for Arduino Nano/Uno and a 128×64 SSD1306 OLED.

![SkippyGecko start screen](assets/splash.jpg)

Part of **MonoPocket** — a small collection of self-contained Arduino/OLED games built around the same compact three-button setup.

This is an original hobby project and is not affiliated with any third-party game or brand.

## Highlights

- Jump and duck around cacti and birds
- Distance-based speed progression
- Parallax clouds and scrolling terrain
- EEPROM-backed high score
- Start, menu, about, game-over, and standby flows
- Designed for ATmega328P-class boards

## Hardware

- Arduino Nano or Uno (ATmega328P)
- 128×64 SSD1306 OLED over I2C, default address `0x3C`
- Three momentary buttons

### Libraries

- Adafruit GFX Library
- Adafruit SSD1306
- Wire (bundled with Arduino)
- EEPROM (bundled on AVR)

## Wiring

| Function | Pin |
| --- | --- |
| OLED SDA | A4 |
| OLED SCL | A5 |
| OLED VCC | 5V |
| OLED GND | GND |
| Jump | D7 |
| Duck | D6 |
| Enter / menu / sleep | D3 |

Buttons use the MCU's internal pull-ups and are active-low.

## Build and upload

1. Open `SkippyGecko.ino` in Arduino IDE or build it with Arduino CLI.
2. Select an Arduino Nano or Uno with an ATmega328P.
3. Install the required Adafruit libraries.
4. Select the correct serial port and upload.

Some Nano clones may require the **Old Bootloader** processor option.

## Controls

- D7: jump
- D6: duck
- D3 short press on the start screen: standby / wake
- D3 long press on the start screen: open menu

## Repository layout

- `SkippyGecko.ino` — complete game sketch
- `assets/` — source/reference artwork used while designing the monochrome game graphics

The 128×64 start background and gameplay bitmaps used at runtime are embedded directly in the sketch.

## License

MIT — see `LICENSE`.
