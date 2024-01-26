import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import output, i2c
from esphome.const import CONF_OUTPUT_ID, CONF_OUTPUT


from esphome.const import (
    CONF_FREQUENCY,
    CONF_ID,
    CONF_NUMBER,
    CONF_PIN,
    CONF_MIN_RANGE,
    CONF_MAX_RANGE,
)


DEPENDENCIES = ['i2c']
CONF_I2C_ADDR = 0x74

empty_light_ns = cg.esphome_ns.namespace('lyratd_light')
LyraTDLightOutput = empty_light_ns.class_('LyraTDLightOutput', output.FloatOutput, cg.Component)


valid_led_range = cv.All(cv.Range(min=0, max=13))

CONFIG_SCHEMA = cv.All(
    output.FLOAT_OUTPUT_SCHEMA.extend(
        {
            cv.Required(CONF_ID): cv.declare_id(LyraTDLightOutput),
            cv.Required(CONF_MIN_RANGE): valid_led_range,
            cv.Required(CONF_MAX_RANGE): valid_led_range,
        }
    ).extend(cv.COMPONENT_SCHEMA).extend(i2c.i2c_device_schema(CONF_I2C_ADDR)),

)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await  cg.register_component(var, config)
    await output.register_output(var, config)

    await i2c.register_i2c_device(var, config)

    minled = config[CONF_MIN_RANGE]
    maxled = config[CONF_MAX_RANGE]
    cg.add(var.set_leds_range(minled, maxled))
