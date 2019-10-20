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

#include <nanvix/const.h>
#include <nanvix/hlib.h>
#include <nanvix/hal/hal.h>
#include <nanvix/kernel/mm.h>
#include <posix/stdint.h>

/**
 * @brief Write buffer size.
 */
#define WRITE_BUFFER_SIZE 512

/**
 * @brief Write buffer.
 */
PRIVATE char bigbuf[WRITE_BUFFER_SIZE + 1];

/**
 * @brief Kernel buffer.
 */
PRIVATE char buf2[WRITE_BUFFER_SIZE + 1];

/**
 * @brief Writes a formated string on the kernels's output device.
 *
 * @param fmt Formated string.
 */
PRIVATE void kprintf2(const char *fmt, ...)
{
	size_t len;   /* String length.           */
	va_list args; /* Variable arguments list. */

	/* Convert to raw string. */
	va_start(args, fmt);
	len = kvsprintf(bigbuf, fmt, args);
	bigbuf[len++] = '\0';
	va_end(args);

	stdout_write(bigbuf, len);
}

/**
 * @brief Writes to a device.
 */
PUBLIC ssize_t kernel_write(int fd, const char *buf, size_t n)
{
	int clusternum;

	UNUSED(fd);

	/* Invalid file descriptor. */
	if (fd < 0)
		return (-EINVAL);

	/* Invalid buffer. */
	if (buf == NULL)
		return (-EINVAL);

	/* Invalid buffer size. */
	if (n > WRITE_BUFFER_SIZE)
		return (-EINVAL);

	/* Invalid buffer location. */
	if (!mm_check_area(VADDR(buf), n, UMEM_AREA))
		return (-EFAULT);

	/* Avoid overflow. */
	kmemcpy(buf2, buf, n);
	buf2[n] = '\0';

	clusternum = cluster_get_num();
	kprintf2("cluster %d: %s", clusternum, buf2);

	return (n);
}
