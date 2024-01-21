IS32FL3216 Datasheet https://www.lumissil.com/assets/pdf/core/IS31FL3216_DS.pdf

[x] Turn on/off leds individually
[ ] Audio modulation
[ ] Frame animation



```yaml
esp32:
  board: esp-wrover-kit
  framework:
    type: esp-idf
esphome:
  name: smart-speaker-lyratd
  min_version: 2023.11.0b5
  on_boot:
    priority: -100
    then: # blink red+green LEDs on boot
      - lambda: lyrard_leds->setBrightness(12,255);
      - delay: 200ms
      - lambda: lyrard_leds->setBrightness(13,255);
      - delay: 200ms
      - lambda: lyrard_leds->setBrightness(12,100);
      - lambda: lyrard_leds->setBrightness(13,100);
      - delay: 200ms
      - lambda: lyrard_leds->setBrightness(12,20);
      - lambda: lyrard_leds->setBrightness(13,20);
      - delay: 200ms
      - lambda: lyrard_leds->setBrightness(12,0);
      - lambda: lyrard_leds->setBrightness(13,0);

is31fl3216:
  id: lyrard_leds
  address: 0x74
# ....
esp_adf:

external_components:
  - source: github://pr#5230
    components:
      - esp_adf
    refresh: 0s
#  - source:
#      type: local
#      path: custom_components
#    components: ["is31fl3216"]
```