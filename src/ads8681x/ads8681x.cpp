/**
 * @file ads8681x.cpp
 * @author zany
 * @brief
 * @version 0.1
 * @date 2022-01-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "ads8681x.hpp"
#include "pico/binary_info.h"
#include "pico/stdlib.h"

typedef union {
  uint8_t map[4];
  uint32_t block;
} rawData_t;

ADS8681x_c::ADS8681x_c(/* args */)
{
}

ADS8681x_c::~ADS8681x_c()
{
}

bool ADS8681x_c::Init(spi_inst_t *spi, uint baudrate, uint32_t clk, uint32_t rx, uint32_t tx, uint32_t csn)
{
  // TODO test input vars
  // setting class vars
  m_spi = spi;
  m_baudrate = baudrate;
  m_rx = rx;
  m_tx = tx;
  m_clk = clk;

  //  initing spi interface with baudrate
  spi_init(m_spi, baudrate);

  // setting pins for the spi interface
  gpio_set_function(m_rx, GPIO_FUNC_SPI);
  gpio_set_function(m_tx, GPIO_FUNC_SPI);
  gpio_set_function(m_clk, GPIO_FUNC_SPI);
  // Make the SPI pins available to picotool
  bi_decl(bi_3pins_with_func(m_rx, m_tx, m_clk, GPIO_FUNC_SPI));

  // setting csn pin
  gpio_init(m_csn);
  gpio_set_dir(m_csn, GPIO_OUT);
  // Make thc CS pin available to picotool
  bi_decl(bi_1pin_with_name(m_csn, "SPI CS"));
  return true;
}

void ADS8681x_c::SelectChip()
{
  asm volatile("nop \n nop \n nop");
  gpio_put(m_csn, 0); // Active low
  asm volatile("nop \n nop \n nop");
}

void ADS8681x_c::DeselectChip()
{
  asm volatile("nop \n nop \n nop");
  gpio_put(m_csn, 1); // Inactive high
  asm volatile("nop \n nop \n nop");
}

int16_t ADS8681x_c::Read()
{
  rawData_t data;
  SelectChip();
  spi_read_blocking(m_spi, 0, data.map, 32);
  DeselectChip();
  return data.block;
}