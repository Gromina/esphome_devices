#pragma once

#include "esphome/core/component.h"
#include "esphome/components/output/float_output.h"

#include "esphome/components/i2c/i2c.h"

const uint8_t FRAME_REGISTER=0x00;
const uint8_t FRAME_DELAY_REGISTER=0xb6;
const uint8_t FRAME_LEN=0x12;

const uint8_t PWM_REGISTER=0x10;
const uint8_t PWM_UPDATE_REGISTER=0xb0;

const uint8_t LED_CONROL_H_REGISTER = 0x01;
const uint8_t LED_CONROL_L_REGISTER = 0x02;


namespace esphome {
namespace lyratd_light {

class LyraTDLightOutput : public output::FloatOutput, public Component, public i2c::I2CDevice {
 public:
  void setup() override;
  void write_state(float state) override;
  void dump_config() override;
  void setBrightness(int led_num, uint8_t val);
  void setAnimationRate(uint8_t val);

  void set_leds_range(uint8_t minled, uint8_t maxled) {leda=minled, ledb=maxled;};
 
private:
    void writeLedsStatus();
    uint16_t my_leds{0};
    uint8_t leda, ledb;
    output::FloatOutput *output_;
};

} //namespace empty_light
} //namespace esphome