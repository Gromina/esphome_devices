#include "esphome/core/log.h"
#include "lyratd_light.h"

namespace esphome {
namespace lyratd_light {

static const char *TAG = "output.lyratd_light";
const uint8_t CONFIG_REGISTER=0x00;

const uint8_t FRAME_REGISTER=0x00;
const uint8_t FRAME_DELAY_REGISTER=0xb6;
const uint8_t FRAME_LEN=0x12;

const uint8_t PWM_REGISTER=0x10;
const uint8_t PWM_UPDATE_REGISTER=0xb0;

const uint8_t LED_CONROL_H_REGISTER = 0x01;
const uint8_t LED_CONROL_L_REGISTER = 0x02;
void LyraTDLightOutput::setup() {
    //set_i2c_address(I2C_ADDRESS);
    write_byte(CONFIG_REGISTER, 0b00000000); // onfiguration Register
    write_byte(LED_CONROL_H_REGISTER,0xff); // LED Control Registerr
    write_byte(LED_CONROL_L_REGISTER,0xff); // LED Control Registerr
    write_byte(0x03,0x07); // Lighting Effect Register
    write_byte(0x07,0xff); // Interrupt Registerr
    write_byte(0x04,0x00); // Channel config  Registerr
    
    write_byte(0x09,0b10110100); // ADC Sample Rate Register

    for (size_t i = 0; i < 14; i++)
    {
      setBrightness((int)i,0);
    }
}


void LyraTDLightOutput::write_state(float state) {

    auto is_on = state>0.f;
    uint8_t brightness = is_on ? floorf(state*255) : 0;
    for (size_t i = leda; i <= ledb; i++)
    {
      setBrightness((int)i, brightness);
    }    

}
void LyraTDLightOutput::setBrightness(int led_num, uint8_t val) {

    write_byte(PWM_REGISTER +  (15-led_num), val ); 
    my_leds ^= 0x01<<led_num; // clear led
    my_leds |= val>0 ? (1 << led_num) : 0; // set as passed


    write_byte(PWM_UPDATE_REGISTER, 0); // PWM update
    writeLedsStatus();
}


void LyraTDLightOutput::writeLedsStatus(){

        write_byte(LED_CONROL_H_REGISTER, my_leds>>8); 
        write_byte(LED_CONROL_L_REGISTER, my_leds&0xff);
}

void LyraTDLightOutput::dump_config(){
    ESP_LOGCONFIG(TAG, "LyraTDLightOutput custom light");
}

} //namespace empty_light
} //namespace esphome