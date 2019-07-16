/*
 * MIT License
 *
 * Copyright(c) 2011-2019 The Maintainers of Nanvix
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifdef __qemu_x86__

/**
 * it seems that I should add some doxygen stuff here, but I don't know what
 */


#ifndef RTL8139_H_
#define RTL8139_H_

#include <stdint.h>
#include <nanvix/hal/hal.h>

#define RTL8139_VENDOR_ID 0x10EC
#define RTL8139_DEVICE_ID 0x8139

#define RX_BUF_SIZE 8192 + 16
/* Adding 1500 bytes when allocating to prevent overflows */
#define RX_BUF_ALLOC_SIZE RX_BUF_SIZE + 1500 

#define RX_READ_POINTER_MASK (~3)
#define ROK (1 << 0)
#define TOK (1 << 2)

/* Register offests */
#define RX_BUFFER 0x30
#define COMMAND 0x37
#define CAPR 0x38
#define TX_CONFIG 0x40
#define RX_CONFIG 0x44
#define CONFIG1 0x52
#define INTERRUPT_MASK 0x3C
#define INTERRUPT_STATUS 0x3E

struct rtl8139_dev
{
	uint16_t io_base;
	uint8_t mac_addr[6];
	uint8_t rx_buffer[RX_BUF_ALLOC_SIZE];
	uint8_t tx_cur;
	uint32_t rx_cur;
};

EXTERN void network_test_driver(void);

void dev_net_rtl8139_init(void);
void dev_net_rtl8139_send_packet(void *data, uint32_t len);

struct rtl8139_dev* dev_net_rtl8139_get_device(void);

bool dev_net_rtl8139_packet_status_valid(uint16_t status);


#endif /* RTL8139_H_ */

#else
extern int make_iso_compilers_happy;
#endif /* __qemu_x86__ */