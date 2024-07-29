/*
 * Copyright (c) 2021 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef ZEPHYR_INCLUDE_DT_BINDINGS_SPI_SPI_H_
#define ZEPHYR_INCLUDE_DT_BINDINGS_SPI_SPI_H_

/**
 * @brief SPI Interface
 * @defgroup spi_interface SPI Interface
 * @ingroup io_interfaces
 *
 * @{
 *
 */

/**
 * @name SPI controller mode
 * @{
 *
 * 2 SPI controllers support master and slave mode. Master mode control the
 * line access and schedule access over slaves, while slave is under the control
 * of the master in order to communicate.
 *
 *
 * By default, SPI_MODE is set to master.
 */
#define SPI_MODE_MASTER    0x0
#define SPI_MODE_SLAVE     0x1
/** @} */


/**
 * @name SPI duplex mode
 * @{
 *
 * Some controllers support half duplex transfer, which results in 3-wire usage.
 * By default, full duplex will prevail.
 */
#define SPI_MODE_FULL_DUPLEX	    0x0
#define SPI_MODE_HALF_DUPLEX	    0x1
/** @} */

/**
 * @name SPI Frame Format
 * @{
 *
 * 2 frame formats are exposed: Motorola and TI.
 * The main difference is the behavior of the CS line. In Motorola it stays
 * active the whole transfer. In TI, it's active only one serial clock period
 * prior to actually make the transfer, it is thus inactive during the transfer,
 * which ends when the clocks ends as well.
 * By default, as it is the most commonly used, the Motorola frame format
 * will prevail.
 */
#define SPI_FRAME_FORMAT_MOTOROLA   0x0
#define SPI_FRAME_FORMAT_TI         0x1
/** @} */

/**
 * @name SPI Clock phasing configuration
 * @{
 *
 * 2 SPI CPHA values are exposed: capture at first or second transition time.
 *
 * This define when exactly the data capture is made.
 *
 * By default, CPHA value set the captime at first transition edge.
 */
#define SPI_CPHA_CAPFIRST    0x0
#define SPI_CPHA_CAPSECOND   0x1
/** @} */

/**
 * @name SPI Clock polarity Format
 * @{
 *
 * 2 SPI CPOL values are exposed: logical low and logical high format.
 *
 * This define the polarty level at idle state, and thus the edge type
 * (going down or up) at data transmission time.
 *
 * By default, CPOL value is logical low voltage.
 */
#define SPI_CPOL_LOW        0x0
#define SPI_CPOL_HIGH       0x1
/** @} */

/**
 * @}
 */

#endif /* ZEPHYR_INCLUDE_DT_BINDINGS_SPI_SPI_H_ */
