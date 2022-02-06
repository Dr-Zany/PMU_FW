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
#include "pico/binary_info.h"
#include "pico/stdlib.h"
#include "stdbool.h"
#include "stdio.h"

#define ADS_SPI_BAUDRATE 100000 // Hz = 0.5MHz
#define GPIO_ADS_SPI_CLK 2
#define GPIO_ADS_SPI_TX 3
#define GPIO_ADS_SPI_RX 0
#define GPIO_ADS_SPI_CS 5
#define GPIO_ADS_RST 4

typedef enum
{
  IDEL = 0,
  MEASRING
} state_t;

void SelectChip()
{
  asm volatile("nop \n nop \n nop");
  gpio_put(GPIO_ADS_SPI_CS, 0); // Active low
  asm volatile("nop \n nop \n nop");
}

void DeselectChip()
{
  asm volatile("nop \n nop \n nop");
  gpio_put(GPIO_ADS_SPI_CS, 1); // Inactive high
  asm volatile("nop \n nop \n nop");
}

uint16_t ADCRead()
{
  uint8_t data[2];
  SelectChip();
  spi_read_blocking(spi0, 0, data, 2);
  DeselectChip();
  return (int32_t)(data[0] << 8 | data[1]);
}

void ADCWriteRegister(uint8_t address, uint16_t data)
{
  uint8_t payload[4];
  payload[0] = 0b11010000;
  payload[1] = address;
  payload[2] = data >> 8;
  payload[3] = data;
  SelectChip();
  spi_write_blocking(spi0, payload, 4);
  DeselectChip();
}

int main(void)
{
  absolute_time_t loopTime;
  state_t state = IDEL;
  uint8_t inputChar = 0;

  /* Init */
  stdio_init_all();

  //  initing spi interface with baudrate
  spi_init(spi0, ADS_SPI_BAUDRATE);

  // setting pins for the spi interface
  gpio_set_function(GPIO_ADS_SPI_RX, GPIO_FUNC_SPI);
  gpio_set_function(GPIO_ADS_SPI_TX, GPIO_FUNC_SPI);
  gpio_set_function(GPIO_ADS_SPI_CLK, GPIO_FUNC_SPI);
  // Make the SPI pins available to picotool
  bi_decl(bi_3pins_with_func(GPIO_ADS_SPI_RX, GPIO_ADS_SPI_TX, GPIO_ADS_SPI_CLK, GPIO_FUNC_SPI));

  // setting csn pin
  gpio_init(GPIO_ADS_SPI_CS);
  gpio_set_dir(GPIO_ADS_SPI_CS, GPIO_OUT);
  gpio_put(GPIO_ADS_SPI_CS, true);
  // Make thc CS pin available to picotool
  bi_decl(bi_1pin_with_name(GPIO_ADS_SPI_CS, "SPI CS"));

  // setting rst pin
  gpio_init(GPIO_ADS_RST);
  gpio_set_dir(GPIO_ADS_RST, GPIO_OUT);
  gpio_put(GPIO_ADS_RST, true);
  // Make thc CS pin available to picotool
  bi_decl(bi_1pin_with_name(GPIO_ADS_RST, "SPI RST"));

  busy_wait_ms(10);

  ADCWriteRegister(0x14, 0b1011);

  printf("starting\n");
  while (true)
  {
    loopTime = make_timeout_time_ms(1);
    /* Timed loop Start */
    switch (state)
    {
    case IDEL:
      inputChar = getchar_timeout_us(0);
      if (inputChar == 's')
      {
        state = MEASRING;
        inputChar = 0;
      }
      break;
    case MEASRING:
      printf("%lu\n", ADCRead());
      inputChar = getchar_timeout_us(0);
      if (inputChar == 'e')
      {
        state = IDEL;
        inputChar = 0;
      }
      break;

    default:
      break;
    }
    /* Timed loop end */
    if (absolute_time_diff_us(get_absolute_time(), loopTime) < 0)
    {
      printf("####### Loop to slow #########");
    }
    busy_wait_until(loopTime);
  }

  return 0;
}
