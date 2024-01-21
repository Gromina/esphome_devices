import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, sensor
from esphome.const import CONF_ID

DEPENDENCIES = ['i2c']

CONF_I2C_ADDR = 0x01

is31fl3216_component_ns = cg.esphome_ns.namespace('is31fl3216')
IS31FL3216Component = is31fl3216_component_ns.class_('IS31FL3216Component', cg.Component,i2c.I2CDevice)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(IS31FL3216Component)
}).extend(cv.COMPONENT_SCHEMA).extend(i2c.i2c_device_schema(CONF_I2C_ADDR))

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
