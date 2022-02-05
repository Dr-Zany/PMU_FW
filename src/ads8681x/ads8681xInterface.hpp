/**
 * @file ads8681x_i.hpp
 * @author zany
 * @brief
 * @version 0.1
 * @date 2022-01-31
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "hardware/spi.h"

#pragma once

class ads8681x_i
{
public:
  virtual bool Init(spi_inst_t *spi, uint baudrate, uint32_t clk, uint32_t rx, uint32_t tx, uint32_t csn) = 0;

protected:
  virtual ~ads8681x_i() = default;

  spi_inst_t *m_spi;
  uint m_baudrate;
  uint32_t m_clk;
  uint32_t m_rx;
  uint32_t m_tx;
  uint32_t m_csn;
};
