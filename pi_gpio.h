/*
 * MIT License
 * Copyright (c) 2022 - 2024 _VIFEXTech
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef __PI_GPIO_H
#define __PI_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void pi_gpio_init();
void pi_gpio_set_mode(uint8_t bcm_pin, int mode);
void pi_gpio_set_value(uint8_t bcm_pin, int value);
int pi_gpio_get_wpi_pin(uint8_t bcm_pin);
volatile uint32_t* pi_gpio_get_register_set();
volatile uint32_t* pi_gpio_get_register_clr();

#ifdef __cplusplus
}
#endif

#endif
