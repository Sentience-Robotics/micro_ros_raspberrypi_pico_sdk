#include "sensor.h"

#include <hardware/adc.h>

#include "board.h"
#include "ws2812_set_rgb.h"

float sensors_value[NB_SENSORS] = {};
rcl_publisher_t sensor_publisher = {};
lucy_msgs__msg__RawSensor sensor_publisher_data = {
    .values = {
        .data = sensors_value,
        .size = NB_SENSORS,
        .capacity = NB_SENSORS,
    }

};

void internal_sensor_init(struct board_s *board, sensor_t *sensor) {
}

static void select_mux_channel(struct analog_multiplexer *mux, uint address) {
    gpio_put(mux->addr0_pin, address & 0b001);
    gpio_put(mux->addr1_pin, address & 0b010);
    gpio_put(mux->addr2_pin, address & 0b100);
    sleep_us(10);
}

float internal_sensor_read(struct board_s *board, sensor_t *sensor) {
    select_mux_channel(&board->data.internal.mux, sensor->config.physical_pin);
    sensor->value = (float)adc_read();
    return sensor->value;
}