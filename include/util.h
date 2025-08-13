#pragma once

#define EPSILON 0.0001

#define ABS(x)  ((x < 0) ? -x : x)
#define EQUAL(x, y) ((ABS(x) - ABS(y)) < EPSILON)
#define EQUAL_E(x, y, e)  ((ABS(x) - ABS(y)) < e)

static inline double map(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
