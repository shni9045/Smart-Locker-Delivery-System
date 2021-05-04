/*
 * CBFIFO.h
 *
 *  Created on: 29-Apr-2021
 *      Author: Shrikant
 */

#ifndef CBFIFO_H_
#define CBFIFO_H_

#include <stdio.h>
#include <stdint.h>
#include <MKL25Z4.h>

/*structure to hold Circular Buffer*/

typedef struct cbfifo{
    uint8_t buffer[256];
    uint8_t write;
    uint8_t read;

}cbfifo;

/*
 * Enqueues data onto the FIFO, up to the limit of the available FIFO
 * capacity.
 *
 * Parameters:
 *   buf1     Instance of buffer to operate on
 *   buf      Pointer to the data
 *   nbyte    Max number of bytes to enqueue
 *
 * Returns:
 *   The number of bytes actually enqueued, which could be 0. In case
 * of an error, returns -1.
 */

size_t cbfifo_enqueue(cbfifo *buf1,void * buf,size_t nbyte);

/*
 * Attempts to remove ("dequeue") up to nbyte bytes of data from the
 * FIFO. Removed data will be copied into the buffer pointed to by buf.
 *
 * Parameters:
 *   buf1     Instance of buffer to operate on
 *   buf      Destination for the dequeued data
 *   nbyte    Bytes of data requested
 *
 * Returns:
 *   The number of bytes actually copied, which will be between 0 and
 * nbyte.
 */

size_t cbfifo_dequeue(cbfifo *buf1,void *buf, size_t nbyte);

/*
 * Checks if buffer is full
 *
 * Parameters:
 *    buf1     Instance of buffer to operate on
 *
 * Returns:
 *   1 if true ,0 if false
 */

int buf_isfull(cbfifo *buf1);

/*
 * Checks if buffer is empty
 *
 * Parameters:
 *    buf1     Instance of buffer to operate on
 *
 * Returns:
 *   1 if true ,0 if false
 */

int buf_isempty(cbfifo *buf1);

/*
 * Returns the number of bytes currently on the FIFO.
 *
 * Parameters:
 *    buf1     Instance of buffer to operate on
 *
 * Returns:
 *   Number of bytes currently available to be dequeued from the FIFO
 */

size_t cbfifo_length(cbfifo *buf);

/*
 * Returns the FIFO's capacity
 *
 * Parameters:
 *   buf1     Instance of buffer to operate on
 *
 * Returns:
 *   The capacity, in bytes, for the FIFO
 */

size_t cbfifo_capacity(cbfifo *buf);

#endif /* CBFIFO_H_ */
