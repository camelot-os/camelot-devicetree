/*
 * Copyright (c) 2024 Ledger SA
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef STM32_SPI_H
#define STM32_SPI_H

/**
 * @file this file complete the generic spi dt-bindings with
 * STM32Ux familly SPI controller specificities
 */
#include <dt-bindings/spi/spi.h>

#define STM32_SPI_MBR_PRESCALER_DIV2     0x0
#define STM32_SPI_MBR_PRESCALER_DIV4     0x1
#define STM32_SPI_MBR_PRESCALER_DIV8     0x2
#define STM32_SPI_MBR_PRESCALER_DIV16    0x3
#define STM32_SPI_MBR_PRESCALER_DIV32    0x4
#define STM32_SPI_MBR_PRESCALER_DIV64    0x5
#define STM32_SPI_MBR_PRESCALER_DIV128   0x6
#define STM32_SPI_MBR_PRESCALER_DIV256   0x7

/**
 * @name SPI data byte encoding mode
 *
 * emit data with MSB or LSB first
 */
#define STM32_SPI_BO_MSBFIRST   0x0
#define STM32_SPI_BO_LSBFIRST   0x1

/**
 * @name SPI CRC support
 *
 * enable emission of CRC frame at controller level
 */
#define STM32_SPI_HWCRC_DISABLE   0x0
#define STM32_SPI_HWCRC_ENABLE    0x1

#define STM32_SPI_SSVAL_SW            0x0 /**< SS value under the pad configuration control */
#define STM32_SPI_SSVAL_HW            0x1 /**< SS value hold by the HW SS configuration */

/**
 * @name SST output enable
 * @note master only
 */
#define STM32_SPI_SSOE_MULTIMASTER      0x0 /**< SS output disabled (master mode) allows multi-master exchange */
#define STM32_SPI_SSOE_SSFORCED         0x1 /**< SS output forced, disable multi-master mode */

/**
 * @name DMA-based transmission support
 */
#define STM32_SPI_TXDMA_DISABLE         0x0
#define STM32_SPI_TXDMA_ENABLE          0x1

#define STM32_SPI_RXDMA_DISABLE         0x0
#define STM32_SPI_RXDMA_ENABLE          0x1

#endif/*!STM32_SPI_H*/
