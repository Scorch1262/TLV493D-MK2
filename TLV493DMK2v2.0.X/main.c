#define FCY 16000000UL 
#include <assert.h>
#include <stdbool.h>
#include "mcc_generated_files/system.h"
#include <stdio.h>
#include <stdlib.h>
#include <libpic30.h>
#include <xc.h>
#include <string.h>
#include "mcc_generated_files/i2c1.h"
#include "tlv493.h"

#if defined(__dsPIC33E__)
	#include <p33exxxx.h>
#elif defined(__dsPIC33F__)
	#include <p33fxxxx.h>
#elif defined(__dsPIC30F__)
	#include <p30fxxxx.h>
#elif defined(__PIC24E__)
	#include <p24exxxx.h>
#elif defined(__PIC24H__)
	#include <p24hxxxx.h>
#elif defined(__PIC24F__) || defined(__PIC24FK__)
	#include <p24fxxxx.h>
#endif

float XDataAnz;                                     // definiert "XDataAnz"        
float YDataAnz;                                     // definiert "YDataAnz"        
float ZDataAnz;                                     // definiert "ZDataAnz"
float TempDataAnz;                                  // definiert "TempDataAnz" 
    
/*
                         Main application
 */
int main(void){                                         // "main"
    SYSTEM_Initialize();                                // ruft "SYSTEM_Initialize" auf
    TLV493_Init();                                      // ruft "TLV493_Init" auf
    __delay_ms(500);                                    // warte 500ms
    
    while (1){                                          // Endloschleife
        XDataAnz = TLV493_X_GetValue();                 // schreibt ergebnis von "TLV493_X_GetValue" in "XDataAnz"        
        YDataAnz = TLV493_Y_GetValue();                 // schreibt ergebnis von "TLV493_Y_GetValue" in "YDataAnz"        
        ZDataAnz = TLV493_Z_GetValue();                 // schreibt ergebnis von "TLV493_Z_GetValue" in "ZDataAnz"
        TempDataAnz = TLV493_Temp_GetValue();           // schreibt ergebnis von "TLV493_Temp_GetValue" in "TempDataAnz"
        printf("X = %0.4fmT   ", XDataAnz);             // schreibt "X = %0.4fmT   " an UART 
        printf("Y = %0.4fmT   ", YDataAnz);             // schreibt "Y = %0.4fmT   " an UART 
        printf("Z = %0.4fmT   ",ZDataAnz);              // schreibt "Z = %0.4fmT   " an UART 
        printf("Temp = %0.2fC\r\n",TempDataAnz);        // schreibt "Z = %0.2fmT\r\n" an UART 
        __delay_ms(500);                                // warte 500ms
    }                                                   // 
}                                                       // 
    
