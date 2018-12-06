/*
 * MIT License
 *
 * Copyright(c) 2018 Pedro Henrique Penna <pedrohenriquepenna@gmail.com>
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

#include <arch/k1b/int.h>
#include <arch/k1b/util.h>
#include <nanvix/const.h>
#include <nanvix/hal/memory.h>
#include <nanvix/hal/interrupt.h>
#include <nanvix/klib.h>
#include <errno.h>

/**
 * @brief Interrupt numbers.
 */
PRIVATE const int irqs[HAL_INT_NR] = {
	BSP_IT_TIMER_0, /* Clock 0              */
	BSP_IT_TIMER_1, /* Clock 1              */
	BSP_IT_WDOG,    /* Watchdog Timer       */
	BSP_IT_CN,      /* Control NoC          */
	BSP_IT_RX,      /* Data NoC             */
	BSP_IT_UC,      /* DMA                  */
	BSP_IT_NE,      /* NoC Error            */
	BSP_IT_WDOG_U,  /* Watchdog Timer Error */
	BSP_IT_PE_0,    /* Remote Core 0        */
	BSP_IT_PE_1,    /* Remote Core 1        */
	BSP_IT_PE_2,    /* Remote Core 2        */
	BSP_IT_PE_3,    /* Remote Core 3        */
	BSP_IT_PE_4,    /* Remote Core 4        */
	BSP_IT_PE_5,    /* Remote Core 5        */
	BSP_IT_PE_6,    /* Remote Core 6        */
	BSP_IT_PE_7,    /* Remote Core 7        */
	BSP_IT_PE_8,    /* Remote Core 8        */
	BSP_IT_PE_9,    /* Remote Core 9        */
	BSP_IT_PE_10,   /* Remote Core 10       */
	BSP_IT_PE_11,   /* Remote Core 11       */
	BSP_IT_PE_12,   /* Remote Core 12       */
	BSP_IT_PE_13,   /* Remote Core 14       */
	BSP_IT_PE_14,   /* Remote Core 14       */
	BSP_IT_PE_15,   /* Remote Core 15       */
};

/**
 * @brief Interrupt handlers.
 */
PRIVATE hal_interrupt_handler_t k1b_handlers[HAL_INT_NR] = {
	NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL
};

/**
 * @brief Hardware interrupt dispatcher.
 *
 * @param irq Interrupt request.
 * @param ctx Interrupted context.
 *
 * @note This function is called from mOS.
 */
PUBLIC void do_hwint(int irq, context_t *ctx)
{
	int num = 0;

	UNUSED(ctx);

	/* Get interrupt number. */
	for (int i = 0; i < HAL_INT_NR; i++)
	{
		if (irqs[i] == irq)
		{
			num = i;
			goto found;
		}
	}

	return;

found:

	k1b_handlers[num](num);
}

/**
 * The hal_interrupt_set_handler() function sets the function pointed
 * to by @p handler as the handler for the hardware interrupt whose
 * number is @p num.
 */
PUBLIC void hal_interrupt_set_handler(int num, hal_interrupt_handler_t handler)
{
	k1b_handlers[num] = handler;
	hal_dcache_invalidate();
}

/**
 * @brief Initializes interrupts
 */
PUBLIC void idt_setup(void)
{
	for (int i = 0; i < HAL_INT_NR; i++)
		bsp_register_it(do_hwint, irqs[i]);
}
