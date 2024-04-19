// API for complete bit-banged I2C library (since ch554_sdcc one doesn't really work)

#pragma once

#include <stdint.h>

// Change SDA_PORT/PIN and SCL_PORT/PIN to set your desired I2C ports
#define SDA_PORT_PU     P1_DIR_PU
#define SDA_PORT_OC     P1_MOD_OC
#define SDA_PORT        P1
#define SDA_PIN         6
#define SCL_PORT_PU     P1_DIR_PU
#define SCL_PORT_OC     P1_MOD_OC
#define SCL_PORT        P1
#define SCL_PIN         7

/*
 * Usage:
 *
 * At start of program:
 *     i2c_bb_init();
 *
 * To write data:
 *     i2c_bb_start(SLAVE_ADDRESS);
 *     i2c_bb_write(<data 1>);
 *     i2c_bb_write(<data 2>);
 *     ...
 *     i2c_bb_stop();
 * or something like:
 *     i2c_bb_start(SLAVE_ADDRESS);
 *     for (size_t i = 0; i < DATA_LEN; i++) {
 *         i2c_bb_write(data[i]);
 *     }
 *     i2c_bb_stop();
 *
 * To read data:
 *     i2c_bb_start(SLAVE_ADDRESS);
 *     uint8_t data = i2c_read();
 *     i2c_bb_stop();
 */

void i2c_bb_init(void);
void i2c_bb_start(const uint8_t addr);
void i2c_bb_write(const uint8_t data);
uint8_t i2c_bb_read(void);
void i2c_bb_stop(void);

