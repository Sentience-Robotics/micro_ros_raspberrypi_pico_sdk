#pragma once

#include <hardware/pwm.h>

extern pwm_config config;

void init_pwm(void);
void init_pwm_port(int16_t pin);
