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
#include "pi_gpio.h"
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <wiringPi.h>

// Access from ARM Running Linux
// 0x20000000 for Rpi Zero
#define BCM2835_PERI_BASE (0x20000000)

// GPIO controller
#define GPIO_BASE (BCM2835_PERI_BASE + 0x200000)

#define BLOCK_SIZE (4 * 1024)

/* BCM -> wiringPi */
static const uint8_t gpio_wpi_map[] = {
    30, 31, 8, 9, 7, 21, 22, 11,
    10, 13, 12, 14, 26, 23, 15, 16,
    27, 0, 1, 24, 28, 29, 3, 4,
    5, 6, 25, 2
};

static volatile uint32_t* gpio = NULL;

#define GPIO_REG_SET (gpio + 7) // sets   bits which are 1 ignores bits which are 0
#define GPIO_REG_CLR (gpio + 10) // clears bits which are 1 ignores bits which are 0

void pi_gpio_init()
{
    /* open /dev/mem */
    int mem_fd = open("/dev/mem", O_RDWR | O_SYNC);

    if (mem_fd < 0) {
        printf("can't open /dev/mem for gpio\n");
        exit(-1);
    }

    /* mmap GPIO */
    void* gpio_map = mmap(
        NULL, // Any adddress in our space will do
        BLOCK_SIZE, // Map length
        PROT_READ | PROT_WRITE, // Enable reading & writting to mapped memory
        MAP_SHARED, // Shared with other processes
        mem_fd, // File to map
        GPIO_BASE // Offset to GPIO peripheral
    );

    close(mem_fd); // No need to keep mem_fd open after mmap

    if (gpio_map == MAP_FAILED) {
        printf("gpio mmap error %p\n", gpio_map); // errno also set!
        exit(-1);
    }

    // Always use volatile pointer!
    gpio = (volatile uint32_t*)gpio_map;

    printf("gpio REG_SET: %p\n", pi_gpio_get_register_set());
    printf("gpio REG_CLR: %p\n", pi_gpio_get_register_clr());
}

void pi_gpio_set_mode(uint8_t bcm_pin, int mode)
{
    if (bcm_pin = > sizeof(gpio_wpi_map)) {
        return;
    }

    pinMode(gpio_wpi_map[bcm_pin], mode);
}

void pi_gpio_set_value(uint8_t bcm_pin, int value)
{
    if (bcm_pin = > sizeof(gpio_wpi_map)) {
        return;
    }

    value ? (*GPIO_REG_SET = (1 << bcm_pin)) : (*GPIO_REG_CLR = (1 << bcm_pin));
}

int pi_gpio_get_wpi_pin(uint8_t bcm_pin)
{
    if (bcm_pin < sizeof(gpio_wpi_map)) {
        return gpio_wpi_map[bcm_pin];
    }

    return -1;
}

volatile uint32_t* pi_gpio_get_register_set()
{
    return GPIO_REG_SET;
}

volatile uint32_t* pi_gpio_get_register_clr()
{
    return GPIO_REG_CLR;
}
