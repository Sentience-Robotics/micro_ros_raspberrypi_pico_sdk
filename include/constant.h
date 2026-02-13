#pragma once

#define I2C_FREQUENCY   (100 * 1000)
#define PCA_ADDR    0x40
#define REG_MODE1   0x00
#define REG_PRESCALE    0xFE
#define REG_LED0_ON_L   0x06

#define NB_BOARDS 2

#define NB_SENSORS 6
#define NB_JOINTS 15

#define NB_INTERNAL_SENSORS   6
#define NB_INTERNAL_JOINTS    18

#define NB_ADAFRUIT_JOINTS    16

#define UPDATE_TIMER_INTERVAL RCL_MS_TO_NS(100)
#define UPTIME_TIMER_INTERVAL RCL_MS_TO_NS(1000)
#define SENSOR_TIMER_INTERVAL RCL_MS_TO_NS(100)

#define MIN_PULSE 544.f
#define MAX_PULSE 2400.f

#define DEBUG_LED_PIN 18
#define FREQ_HZ       800000.0f

#define PWM_FREQ_HZ 20000
#define PWM_CLKDIV  125.f

#define NB_ATTEMPTS 120
#define TIMEOUT_MS  1000

#define MAX_NAME_LENGTH 128 // TODO REMOVE ?

#define MAX_LOG_SIZE  256

#define UPTIME_PUBLISHER_TOPIC_NAME "uptime_publisher"
#define LOG_PUBLISHER_TOPIC_NAME  "log_publisher"
#define TRACE_PUBLISHER_TOPIC_NAME  "trace_publisher"


#ifdef USE_LEFT_ARM
    #define JOINTS_TOPIC_NAME  "actuators/left_arm"
    #define SENSORS_TOPIC_NAME  "sensors/left_arm"
#elif USE_RIGHT_ARM
    #define JOINTS_TOPIC_NAME  "actuators/right_arm"
    #define SENSORS_TOPIC_NAME  "sensors/right_arm"
#elif USE_TORSO
    #define JOINTS_TOPIC_NAME  "actuators/torso"
    #define SENSORS_TOPIC_NAME  "sensors/torso"
#else
    #define JOINTS_TOPIC_NAME  "actuators/default"
    #define SENSORS_TOPIC_NAME  "sensors/default"
#endif

#define NB_HANDLES    3  // TOPICS + TIMER, remember to increment
#define NODE_NAME     "pico_node"

#define CLAMP(val, min, max) ((val < min) ? min : (val > max) ? max : val)

#define SERVO_TYPE_180 180
#define SERVO_TYPE_270 270
#define SERVO_TYPE_300 300

#define EPSILON 0.0001

#define ABS(x)  ((x < 0) ? -x : x)
#define EQUAL(x, y) ((ABS(x) - ABS(y)) < EPSILON)
#define EQUAL_E(x, y, e)  ((ABS(x) - ABS(y)) < e)

#define INTERNAL_I2C_SDA    20
#define INTERNAL_I2C_SCL    21
#define INTERNAL_I2C_PORT   i2c0

#define INTERNAL_SERVO_1    0
#define INTERNAL_SERVO_2    1
#define INTERNAL_SERVO_3    2
#define INTERNAL_SERVO_4    3
#define INTERNAL_SERVO_5    4
#define INTERNAL_SERVO_6    5
#define INTERNAL_SERVO_7    6
#define INTERNAL_SERVO_8    7
#define INTERNAL_SERVO_9    8
#define INTERNAL_SERVO_10   9
#define INTERNAL_SERVO_11   10
#define INTERNAL_SERVO_12   11
#define INTERNAL_SERVO_13   12
#define INTERNAL_SERVO_14   13
#define INTERNAL_SERVO_15   14
#define INTERNAL_SERVO_16   15
#define INTERNAL_SERVO_17   16
#define INTERNAL_SERVO_18   17

#define INTERNAL_ADC_ADDR_0 22
#define INTERNAL_ADC_ADDR_1 24
#define INTERNAL_ADC_ADDR_2 25
#define INTERNAL_SHARED_ADC 29

#define INTERNAL_SENSOR_1_ADDR   0b000
#define INTERNAL_SENSOR_2_ADDR   0b001
#define INTERNAL_SENSOR_3_ADDR   0b010
#define INTERNAL_SENSOR_4_ADDR   0b011
#define INTERNAL_SENSOR_5_ADDR   0b100
#define INTERNAL_SENSOR_6_ADDR   0b101
#define INTERNAL_SENSOR_VOLTAGE_ADDR    0b110
#define INTERNAL_SENSOR_CURRENT_ADDR    0b111

static double map(double x, double in_min, double in_max, double out_min, double out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}