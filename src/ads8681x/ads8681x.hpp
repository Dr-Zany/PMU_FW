/**
 * @file ads8681x.hpp
 * @author zany
 * @brief
 * @version 0.1
 * @date 2022-01-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "ads8681xInterface.hpp"

#pragma once

class ADS8681x_c : public ads8681x_i
{
public:
  ADS8681x_c(/* args */);
  ~ADS8681x_c();
  bool Init(spi_inst_t *spi, uint baudrate, uint32_t clk, uint32_t rx, uint32_t tx, uint32_t csn) override;

private:
  inline void SelectChip(void);
  inline void DeselectChip(void);
  int16_t Read(void);
};
