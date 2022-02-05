/**
 * @file main.cpp
 * @author zany
 * @brief
 * @version 0.1
 * @date 2022-01-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "main.hpp"
#include "hardware/spi.h"
#include "pico/stdlib.h"
#include "stdio.h"

typedef enum
{
  IDEL = 0,
  MEASRING
} state_t;

int main(void)
{
  absolute_time_t loopTime;
  state_t state = IDEL;
  uint8_t inputChar = 0;
  while (true)
  {
    loopTime = make_timeout_time_ms(10);
    /* Timed loop Start */
    switch (state)
    {
    case IDEL:
      inputChar = getchar_timeout_us(0);
      break;

    default:
      break;
    }
    /* Timed loop end */
    if (absolute_time_diff_us(get_absolute_time(), loopTime) >= 0)
    {
      printf("####### Loop to slow #########");
    }
    busy_wait_until(loopTime);
  }

  return 0;
}
