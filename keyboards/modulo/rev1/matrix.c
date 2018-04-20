/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ch.h"
#include "hal.h"

/*
 * scan matrix
 */
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "wait.h"

#ifndef DEBOUNCE
#   define DEBOUNCE 5
#endif
static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];
static uint8_t matrix_row_read[2] = { 0xff, 0xff };

static matrix_row_t read_cols(void);
static void init_cols(void);
static void unselect_rows(void);
static void select_row(uint8_t row);

/* I2C control setting */
static const uint16_t row_addrs[MATRIX_ROWS] = {
    0b0111000, \
    0b0111000
};
static const uint8_t io_setting = 0b11111111;

inline
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

/* generic STM32F103C8T6 board */
#ifdef BOARD_GENERIC_STM32_F103
#define LED_ON()    do { palClearPad(GPIOC, GPIOC_LED) ;} while (0)
#define LED_OFF()   do { palSetPad(GPIOC, GPIOC_LED); } while (0)
#define LED_TGL()   do { palTogglePad(GPIOC, GPIOC_LED); } while (0)
#endif

/* Maple Mini */
#ifdef BOARD_MAPLEMINI_STM32_F103
#define LED_ON()    do { palSetPad(GPIOB, 1) ;} while (0)
#define LED_OFF()   do { palClearPad(GPIOB, 1); } while (0)
#define LED_TGL()   do { palTogglePad(GPIOB, 1); } while (0)
#endif

/*
 * I2C1 config.
 */
static const I2CConfig i2ccfg1 = {
    OPMODE_I2C,
    100000,
    STD_DUTY_CYCLE,
};

void matrix_init(void)
{
    // initialize row and col
    unselect_rows();
    init_cols();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }

    // debug
    // debug_enable = true;
    debug_matrix = true;
    LED_ON();
    wait_ms(500);
    LED_OFF();
}

uint8_t matrix_scan(void)
{
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        select_row(i);
        wait_us(30);  // without this wait read unstable value.
        matrix_row_t cols = read_cols();
        if (matrix_debouncing[i] != cols) {
            matrix_debouncing[i] = cols;
            if (debouncing) {
                debug("bounce!: "); debug_hex(debouncing); debug("\n");
            }
            debouncing = DEBOUNCE;
        }
        unselect_rows();
    }

    if (debouncing) {
        if (--debouncing) {
            wait_ms(1);
        } else {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
        }
    }

    return 1;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_row_t)1<<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        phex(row); print(": ");
        pbin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

/* Column pin configuration
 */
static void init_cols(void)
{
    msg_t status = MSG_OK;

    // setup I2C hardware
    palSetPadMode(GPIOB, 6, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);   /* SCL */
    palSetPadMode(GPIOB, 7, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);   /* SDA */
    palSetPadMode(GPIOB, 10, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);   /* SCL */
    palSetPadMode(GPIOB, 11, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);   /* SDA */

    // setup I2C bus
    i2cStart(&I2CD1, &i2ccfg1);
    i2cStart(&I2CD2, &i2ccfg1);

    // setup IO expanders
    // for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    //     status = i2cMasterTransmit(&I2CD1, row_addrs[row], &io_setting, 1, NULL, 0);
    // }
    status = i2cMasterTransmit(&I2CD1, row_addrs[0], &io_setting, 1, NULL, 0);
    status = i2cMasterTransmit(&I2CD2, row_addrs[1], &io_setting, 1, NULL, 0);

    if (MSG_OK != status) {
        // error
    } else {
        // success
    }
}

/* Returns status of switches(1:on, 0:off) */
static matrix_row_t read_cols(void)
{
    return ~matrix_row_read[0];
}

/* Row pin configuration
 */
static void unselect_rows(void)
{
    // palSetPadMode(GPIOA, GPIOA_PIN10, PAL_MODE_INPUT); // hi-Z
}

static void select_row(uint8_t row)
{
    msg_t status = MSG_OK;

    // read from IO expander
    if (row == 0) {
        status = i2cMasterReceive(&I2CD1, row_addrs[row], matrix_row_read, 2);
    } else {
        status = i2cMasterReceive(&I2CD2, row_addrs[row], matrix_row_read, 2);
    }

    if (MSG_OK != status) {
        // error
    } else {
        // success
    }
}

