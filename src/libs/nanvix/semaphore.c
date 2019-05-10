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

#include <nanvix.h>
#include <errno.h>
#include <stdbool.h>

#if (CORES_NUM > 1)

/*============================================================================*
 * nanvix_semaphore_init()                                                    *
 *============================================================================*/

/**
 * @todo TODO provide a detailed description for this function.
 *
 * @author Pedro Henrique Penna
 */
int nanvix_semaphore_init(struct nanvix_semaphore *sem, int val)
{
	/* Invalid semaphore. */
	if (sem == NULL)
		return (-EINVAL);

	/* Invalid semaphore value. */
	if (val < 0)
		return (-EINVAL);

	sem->val = val;
	sem->lock = SPINLOCK_UNLOCKED;
	for (int i = 0; i < THREAD_MAX; i++)
		sem->tids[i] = -1;
	dcache_invalidate();

	return (0);
}

/*============================================================================*
 * nanvix_semaphore_down()                                                    *
 *============================================================================*/


/**
 * @todo TODO provide a detailed description for this function.
 *
 * @author Pedro Henrique Penna
 */
int nanvix_semaphore_down(struct nanvix_semaphore *sem)
{
	kthread_t tid;

	/* Invalid semaphore. */
	if (sem == NULL)
		return (-EINVAL);

	tid = kthread_self();

	do
	{
		spinlock_lock(&sem->lock);

			/* Dequeue kernel thread. */
			for (int i = 0; i < THREAD_MAX; i++)
			{
				if (sem->tids[i] == tid)
				{
					for (int j = i; j < (THREAD_MAX - 1); j++)
						sem->tids[j] = sem->tids[j + 1];
					sem->tids[THREAD_MAX - 1] = -1;
					break;
				}
			}

			/* Lock. */
			if (sem->val > 0)
			{
				sem->val--;
				spinlock_unlock(&sem->lock);
				break;
			}

			/* Enqueue kernel thread. */
			for (int i = 0; i < THREAD_MAX; i++)
			{
				if (sem->tids[i] == -1)
				{
					sem->tids[i] = tid;
					break;
				}
			}

		spinlock_unlock(&sem->lock);

		sleep();
	} while (true);

	return (0);
}

/*============================================================================*
 * nanvix_semaphore_up()                                                      *
 *============================================================================*/


/**
 * @todo TODO provide a detailed description for this function.
 *
 * @author Pedro Henrique Penna
 */
int nanvix_semaphore_up(struct nanvix_semaphore *sem)
{
	/* Invalid semaphore. */
	if (sem == NULL)
		return (-EINVAL);

again:

	spinlock_lock(&sem->lock);

		if (sem->tids[0] != -1)
		{
			if (wakeup(sem->tids[0]) != 0)
			{
				spinlock_unlock(&sem->lock);
				goto again;
			}
		}


		sem->val++;

	spinlock_unlock(&sem->lock);

	return (0);
}

#endif /* CORES_NUM > 1 */