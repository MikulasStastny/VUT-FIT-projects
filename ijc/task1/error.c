/*******************************
 * autor: Mikulas Stastny, FIT *
 * uloha: IJC DU1, příklad B)  *
 * přeloženo: gcc 11.2         *
 * datum: 20. 3. 2022          *
 *******************************/

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "error.h"

void warning_msg(const char *fmt, ...){
	va_list valist;
	va_start(valist, fmt);
	
	fprintf(stderr, "CHYBA: ");
	vfprintf(stderr, fmt, valist);
	fprintf(stderr, "\n");

	va_end(valist);
}

void error_exit(const char *fmt, ...){
	va_list valist;
	va_start(valist, fmt);
	
	fprintf(stderr, "CHYBA: ");
	vfprintf(stderr, fmt, valist);
	fprintf(stderr, "\n");

	va_end(valist);

	exit(1);
}
