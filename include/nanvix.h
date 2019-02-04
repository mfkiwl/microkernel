/*
 * MIT License
 *
 * Copyright(c) 2011-2018 Pedro Henrique Penna <pedrohenriquepenna@gmail.com>
 *              2015-2017 Davidson Francis     <davidsondfgl@gmail.com>
 *              2016-2016 Subhra S. Sarkar     <rurtle.coder@gmail.com>
 *              2017-2017 Romane Gallier       <romanegallier@gmail.com>
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

/**
 * @addtogroup nanvix Nanvix System
 */
/**@{*/

#ifndef NANVIX_H_
#define NANVIX_H_

	#include <nanvix/syscall.h>
	#include <sys/types.h>

	/**
	 * @brief Thread ID.
	 */
	typedef int kthread_t;

	/* System calls. */
	extern ssize_t nanvix_write(int, const char *, size_t);

	/**
	 * @name Thread Management Kernel Calls
	 */
	/**@{*/
	extern kthread_t kthread_self(void);
	extern int kthread_create(kthread_t *, void *(*)(void*), void *);
	extern void kthread_exit(void *);
	extern int kthread_join(kthread_t, void **);
	/**@}*/

#endif /* NANVIX_H_ */

/**@}*/
