/*******************************
 * autor: Mikulas Stastny, FIT *
 * uloha: IJC DU1, příklad B)  *
 * přeloženo: gcc 11.2         *
 * datum: 20. 3. 2022          *
 *******************************/

#ifndef ERROR
#define ERROR

// Funkce vypise chybu na standardni chybovy vystup. 
void warning_msg(const char *fmt, ...);

// Funkce vypise chybu na standardni chybovy vystup a ukonci program.
void error_exit(const char *fmt, ...);

#endif
