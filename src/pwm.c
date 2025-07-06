#include <stdint.h>
#include <hardware/pwm.h>
#include <hardware/gpio.h>

pwm_config config;

void init_pwm(void) {
  config = pwm_get_default_config();

  pwm_config_set_wrap(&config, 20000);
  pwm_config_set_clkdiv(&config, 125.f);
}

void init_pwm_port(int16_t pin) {
  uint32_t sliceNum = pwm_gpio_to_slice_num(pin);

  gpio_set_function(pin, GPIO_FUNC_PWM);
  pwm_init(sliceNum, &config, true);
}
