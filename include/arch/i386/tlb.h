/*
 * MIT License
 *
 * Copyright(c) 2011-2018 Pedro Henrique Penna <pedrohenriquepenna@gmail.com>
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

#ifndef ARCH_I386_TLB_H_
#define ARCH_I386_TLB_H_

/**
 * @addtogroup i386-tlb TLB
 * @ingroup i386-memory
 *
 * @brief Translation Lookaside Buffer
 */
/**@{*/

	/**
	 * @name Provided Interface
	 *
	 * @cond i386
	 */
	/**@{*/
	#define __tlb_flush_fn /**< tlb_flush() */
	/**@}*/
	/**@endcond**/

	/**
	 * The tlb_flush() function flushes the TLB of the underlying i386
	 * core.
	 *
	 * @cond i386
	 */
	static inline void tlb_flush(void)
	{
		__asm__ __volatile__ (
			"movl %%cr3, %%eax;\
			movl %%eax, %%cr3;"
			:
			: 
			:
		);
	}
	/**@endcond*/
	
#endif /* ARCH_I386_TLB_H_ */
