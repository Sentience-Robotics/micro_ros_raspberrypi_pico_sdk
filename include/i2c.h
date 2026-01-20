#pragma once

#include <hardware/i2c.h>

static void pca_write_reg(i2c_inst_t *port, uint8_t addr, uint8_t reg, uint8_t value) {
    uint8_t buf[2] = {reg, value};
    i2c_write_blocking(port, addr, buf, 2, false);
}