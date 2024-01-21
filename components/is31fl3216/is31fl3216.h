#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"


namespace esphome {
    namespace is31fl3216 {

        class IS31FL3216Component :  public i2c::I2CDevice, public Component{
            uint16_t my_leds{0};
            public:
                IS31FL3216Component();
                void setup() override;
                void dump_config() override ;

                void setBrightness(int led_num, uint8_t val);
                void setAnimationRate(uint8_t val);
            private:
                void writeLedsStatus();

        };
    }
}
