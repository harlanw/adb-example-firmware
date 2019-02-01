#ifndef _TS_USART_H
#define _TS_USART_H

#include <stdio.h>

extern FILE usart_out;
extern FILE usart_in;

void usart_init(void);

int usart_putchar(char c, FILE *stream);
int usart_getchar(FILE *stream);

#endif
