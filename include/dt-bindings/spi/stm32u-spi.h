/*
 * Copyright (c) 2024 Ledger SA
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef STM32U_SPI_H
#define STM32U_SPI_H

/**
 * @file this file complete the generic stm32-spi dt-bindings with
 * STM32Ux familly SPI controller specificities
 */
#include <dt-bindings/spi/stm32-spi.h>


#define STM32_SPI_MBR_PRESCALER_BYPASS   0x0

/**
 * @name CRC frame length
 *
 * @note CRC frame length configuration do not exist in all stm32 SPI controllers
 *
 * on STM32U5, CRCSIZE field value equals to value minus 1, with a minimum of 4
 */
#define STM32_SPI_CRCSIZE(x) (((x)-1) & 0x1fUL)

/**
 * @name SPI frame data length
 *
 * starting at 4bits upto 32bits
 */
#define STM32_SPI_DSIZE(x) (((x) - 1) & 0x1fUL)

/**
 * @name behavior in case of emission underrun
 */
#define STM32_SPI_UNDERRUN_CFG_PATTERN 0x0 /**< emit fixed pattern in case of underrun */
#define STM32_SPI_UNDERRUN_CFG_LAST    0x1 /**< emit lastly received master data in case of underrun */


/**
 * @name FIFO threshold support, in number of data frame per data packet
 */
#define STM32_SPI_FIFO_THRESHOLD(x)     (((x)+1) & 0xfUL)

/**
 * @name SST output management
 * @note master only
 */
#define STM32_SPI_SSOM_KEPT             0x0 /**< SS level is kept active until end of transmission */
#define STM32_SPI_SSOM_INTERLEAVED      0x1 /**< SPI frames are interleaved with non-active SS level */


#define STM32_SPI_SSPOL_LOW            0x0 /**< SS polarity set to low level when active */
#define STM32_SPI_SSPOL_HIGH           0x1 /**< SS polarity set to high level when active */

/**
 * SPI mode support, on STM32U family. This include simplex mode
 */
/* spi generic value set half_duplex as 1, but in stm32, 4 modes are supported, with different values */
#ifdef SPI_MODE_HALF_DUPLEX
#undef SPI_MODE_HALF_DUPLEX
#endif

#define SPI_MODE_FULL_DUPLEX	    0x0
#define SPI_MODE_SIMPLEX_TX         0x1
#define SPI_MODE_SIMPLEX_RX         0x2
#define SPI_MODE_HALF_DUPLEX	    0x3

/**
 * @name MOSI and MISO lines swap
 */
#define SPI_IO_SWAP_DISABLE         0x0
#define SPI_IO_SWAP_ENABLE          0x1

/* number of cycles between data frame in Master mode */
#define SPI_INTERDATA_IDLECYCLES(x) ((x) & 0xfUL)

/* number of cycles between SS active edges in Master mode */
#define SPI_SSAINTERACTIVE_IDLECYCLES(x) ((x) & 0xfUL)

#endif/*!STM32U_SPI_H*/
