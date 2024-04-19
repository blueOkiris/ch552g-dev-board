// Implement bit-banging for I2C

#include <stdint.h>
#include <8051.h>
#include <ch554.h>
#include <debug.h>
#include <i2c_bb.h>

uint8_t SDA_PIN_BIT = 0;
uint8_t SCL_PIN_BIT = 0;

void set_sda(uint8_t on) {
    if (on) {
        SDA_PORT |= SDA_PIN_BIT;
    } else {
        SDA_PORT &= ~SDA_PIN_BIT;
    }
}

uint8_t get_sda(void) {
    return SDA_PORT & SDA_PIN_BIT > 0;
}

void read_ack(void) {
    SDA_PORT |= SDA_PIN_BIT;
    SCL_PORT |= SCL_PIN_BIT;

    // Set SDA to input to "read"
    SDA_PORT_PU &= ~SDA_PIN_BIT;
    SCL_PORT &= ~SCL_PIN_BIT;

    SDA_PORT_PU |= SDA_PIN_BIT;
}

void i2c_bb_init(void) {
    SDA_PIN_BIT = 1 << SDA_PIN;
    SCL_PIN_BIT = (uint8_t) (1 << SCL_PIN);

    // Put SDA and SCL into output mode
    SDA_PORT_PU |= SDA_PIN;
    SDA_PORT_OC &= ~SDA_PIN;
    SCL_PORT_PU |= SCL_PIN;
    SCL_PORT_OC &= ~SDA_PIN;

    SDA_PORT |= SDA_PIN_BIT;
    SCL_PORT |= SCL_PIN_BIT;
}

void i2c_bb_start(const uint8_t addr) {
    // Begin transmission
    SDA_PORT &= ~SDA_PIN_BIT;
    SCL_PORT &= ~SCL_PIN_BIT;

    // Set addr & R/W
    const uint8_t data = (addr << 1) + 0; // Do "+ 1" for Read
    for (int8_t i = 7; i >= 0; i--) {
        set_sda((data >> i) & 0x01);
        SCL_PORT |= SCL_PIN_BIT;
        SCL_PORT &= ~SCL_PIN_BIT;
    }
    read_ack();
}

void i2c_bb_write(const uint8_t data) {
    for (int8_t i = 7; i >= 0; i--) {
        set_sda((data >> i) & 0x01);
        SCL_PORT |= SCL_PIN_BIT;
        SCL_PORT &= ~SCL_PIN_BIT;
    }
    read_ack();
}

uint8_t i2c_bb_read(void) {
    uint8_t data;

    SDA_PORT_PU &= ~SDA_PIN_BIT; // Set SDA to input to "read"
    for (int8_t i = 7; i >= 0; i--) {
        SCL_PORT |= SCL_PIN_BIT;
        data |= get_sda() << i;
        SCL_PORT &= ~SCL_PIN_BIT;
    }
    read_ack(); // Sets back to write for us

    return data;
}

void i2c_bb_stop(void) {
    SDA_PORT |= SDA_PIN_BIT;
    SCL_PORT |= SCL_PIN_BIT;
}

