/*
 * cbfifo.c - Source file containing implementation of functions described in cbfifo.h
 *
 */

#include "CBFIFO.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define size 256        //Macro to store size of Circular buffer

size_t cbfifo_enqueue(cbfifo *buf1,void * buf,size_t nbyte){

	uint32_t masking_state;

	uint8_t *p;

	if (buf==NULL){
    return -1;
	}

    size_t current_length,current_space;
    current_length=cbfifo_length(buf1);
    current_space=size-current_length-1;    //To distinguish between empty & full one byte is kept as it is
    size_t bytes_written=0;

    if(nbyte>current_space){

       for(int i=0;i<current_space;i++){

    	   // save current masking state
    	   masking_state = __get_PRIMASK();
    	   // disable interrupts
    	   __disable_irq();

           p=(uint8_t*)buf+i;
           buf1->buffer[buf1->write]=*p;
           bytes_written++;
           buf1->write=(buf1->write+1) & (size-1);      //Increament write index with wraparound
           // restore  interrupt masking state
           __set_PRIMASK(masking_state);

           }
        }

    else if(nbyte<=current_space){

        for(int i=0;i<nbyte;i++){

     	   // save current masking state
     	   masking_state = __get_PRIMASK();
     	   // disable interrupts
     	   __disable_irq();

            p=(uint8_t*)buf+i;
            buf1->buffer[buf1->write]=*p;
            bytes_written++;
            buf1->write=(buf1->write+1) & (size-1);

            // restore  interrupt masking state
            __set_PRIMASK(masking_state);
            }
       }

    return bytes_written;
}

size_t cbfifo_dequeue(cbfifo *buf1,void *buf, size_t nbyte){

	uint32_t masking_state;

    uint8_t bytes_read;
    if (buf==NULL){
        return -1;
    }
    size_t current_length;
    current_length=cbfifo_length(buf1);
    if (current_length==0 || buf==NULL){
        return 0;
    }
     if (nbyte<=current_length){
           uint8_t i;

           for ( i=0;i<nbyte;i++){

         	   // save current masking state
         	   masking_state = __get_PRIMASK();
         	   // disable interrupts
         	   __disable_irq();

               *((uint8_t*)buf+i)=buf1->buffer[buf1->read];
               buf1->read=(buf1->read+1)&(size-1);             //Increament read index with wraparound

               // restore  interrupt masking state
               __set_PRIMASK(masking_state);

           }
           bytes_read=i;
        }

        else if (nbyte>current_length){
            uint8_t k;
            for ( k=0;k<current_length;k++){

          	   // save current masking state
          	   masking_state = __get_PRIMASK();
          	   // disable interrupts
          	   __disable_irq();

                *((uint8_t*)buf+k)=buf1->buffer[buf1->read];
                buf1->read=(buf1->read+1)&(size-1);

                // restore  interrupt masking state
                __set_PRIMASK(masking_state);
            }
            bytes_read=k;
        }
        return bytes_read;
}

int buf_isfull(cbfifo *buf1){

	return (cbfifo_length(buf1) == (size-1));

}

int buf_isempty(cbfifo *buf1){

	return (buf1->read == buf1->write);

}
size_t cbfifo_length(cbfifo *buf){

    return ((buf->write-buf->read)&(size-1));
}

size_t cbfifo_capacity(cbfifo *buf){
    return (sizeof(buf->buffer)-1);
}
