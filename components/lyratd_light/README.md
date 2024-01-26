# Output platform
Output can actually manipulate any range of LEDs as one monochromatic Light, see an example

# example configuration:

```
esphome:
  name: smart-speaker-lyratd
  min_version: 2023.11.0b5
  on_boot:
    priority: -100
    then:
    - light.turn_on:
        id: leds
        brightness: 60%
        effect: "Slow Pulse"

....

external_components:
  - source: github://pr#5230
    components:
      - esp_adf
    refresh: 0s
  - source: github://Gromina/esphome_devices
    components: ["lyratd_light"]

light:
  id: leds
  platform: monochromatic
  name: Blue LEDs
  effects:
  - pulse:
      name: "Slow Pulse"
      transition_length: 250ms
      update_interval: 250ms
      min_brightness: 10%
      max_brightness: 40%
  - pulse:
      name: "Fast Pulse"
      transition_length: 100ms
      update_interval: 100ms
      min_brightness: 50%
      max_brightness: 100%
  output: lyraleds_red
output:
  - platform: lyratd_light
    address: 0x74
    min_range: 0
    max_range: 11
    id: lyraleds_blue
  - platform: lyratd_light
    address: 0x74
    min_range: 12
    max_range: 12
    id: lyraleds_red
  - platform: lyratd_light
    address: 0x74
    min_range: 13
    max_range: 13
    id: lyraleds_green


....


```