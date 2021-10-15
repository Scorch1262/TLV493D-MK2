#define FCY 16000000UL

#include "xc.h"
#include <assert.h>
#include <stdbool.h>
#include <libpic30.h>
#include <stdint.h>
#include "mcc_generated_files/system.h"
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

#define TLV493_ADDR    0x5E //(0x5E, 0x1F)0x44

I2C1_MESSAGE_STATUS status;                                             // 

uint8_t Slave_Address;                                                  // definiert "Slave_Address" 

uint8_t  writeBuffer[10] = {0x00, 0x00, 0x00};                          // definiert "writeBuffer"
uint8_t  readBuffer[10] = {0x00, 0x00, 0x00};                           // definiert "readBuffer" 
uint16_t retryTimeOut1;                                                 // definiert "retryTimeOut1" 
uint16_t retryTimeOut2;                                                 // definiert "retryTimeOut2" 

void TLV493_Init(void){                                                 // "TLV493_Init"
    Slave_Address = TLV493_ADDR;                                        // schreibt "TLV493_ADDR" in "Slave_Address"    
    
    __delay_ms(100);                                                    // warte 100ms
    I2C1_MasterRead(&readBuffer[0], 10, Slave_Address, &status);        // liest von I2C1 in 10 Byte (readBuffer[0]) 
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf
    writeBuffer[0] = 0x00;                                              // 
    writeBuffer[1] = (readBuffer[7] && 0x71);                           // 
    writeBuffer[1] = (writeBuffer[1] || 0x00);                          // 
    writeBuffer[2] = readBuffer[8];                                     // 
    writeBuffer[3] = (readBuffer[9] && 0x1F);                           // 
    writeBuffer[3] = (writeBuffer[1] || 0x00);                          // 
    I2C1_MasterWrite(&writeBuffer[0], 10, Slave_Address, &status);      // schreibt 10 Byte (writeBuffer[0]) an I2C1                  
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf 
    __delay_ms(100);                                                    // warte 100ms
}                                                                       // 

void TLV493_Read(void){                                                 // "TLV493_Read"
    Slave_Address = TLV493_ADDR;                                        // schreibt "TLV493_ADDR" in "Slave_Address"    
  
    I2C1_MasterRead(&readBuffer[0], 7, Slave_Address, &status);         // liest von I2C1 in 7 Byte (readBuffer[0]) 
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf
}                                                                       // 

float TLV493_X_GetValue(void){                                          // "TLV493_X_GetValue"  
    float XDataAnz;                                                     // definiert "XDataAnz"   
    int16_t x_axis;                                                     // definiert "x_axis"
    
    TLV493_Read();                                                      // ruft "TLV493_Read" auf
    x_axis = readBuffer[0];                                             // "x_axis" gleich "readBuffer[0]"
    x_axis = x_axis << 4;                                               // "x_axis" 4 nach links
    x_axis |= ((readBuffer[4] >> 4 ) & 0x0F);                           // 
    if(x_axis > 2048){                                                  // wenn "x_axis" größer ist als 2048
        x_axis = x_axis - 4096;                                         // "x_axis" - 4096
    }                                                                   // 
    XDataAnz = x_axis * 0.098;                                          // "XDataAnz" gleich "x_axis" * 0.098
    return XDataAnz;                                                    // gibt "XDataAnz" zur?ck     
}                                                                       // 

float TLV493_Y_GetValue(void){                                          // "TLV493_Y_GetValue"  
    float YDataAnz;                                                     // definiert "YDataAnz"
    int16_t y_axis;                                                     // definiert "y_axis"
    
    TLV493_Read();                                                      // ruft "TLV493_Read" auf
    y_axis = readBuffer[1];                                             // "y_axis" gleich "readBuffer[1]"
    y_axis = y_axis << 4;                                               // "y_axis" 4 nach links
    y_axis |= (readBuffer[4] & 0x0F);                                   // 
    if(y_axis > 2048){                                                  // wenn "y_axis" größer ist als 2048
        y_axis = y_axis - 4096;                                         // "y_axis" - 4096
    }                                                                   // 
    YDataAnz = y_axis * 0.098;                                          // "YDataAnz" gleich "y_axis" * 0.098
    return YDataAnz;                                                    // gibt "YDataAnz" zur?ck     
}                                                                       // 

float TLV493_Z_GetValue(void){                                          // "TLV493_Z_GetValue"  
    float ZDataAnz;                                                     // definiert "ZDataAnz"
    int16_t z_axis;                                                     // definiert "z_axis"
    
    TLV493_Read();                                                      // ruft "TLV493_Read" auf
    z_axis = readBuffer[2];                                             // "z_axis" gleich "readBuffer[2]"
    z_axis = z_axis << 4;                                               // "z_axis" 4 nach links
    z_axis |= (readBuffer[5] & 0x0F);                                   // 
    if(z_axis > 2048){                                                  // wenn "z_axis" größer ist als 2048
        z_axis = z_axis - 4096;                                         // "z_axis" - 4096
    }                                                                   // 
    ZDataAnz = z_axis * 0.098;                                          // "ZDataAnz" gleich "z_axis" * 0.098
    return ZDataAnz;                                                    // gibt "ZDataAnz" zur?ck     
}                                                                       // 

float TLV493_Temp_GetValue(void){                                       // "TLV493_Temp_GetValue"  
    float TempDataAnz;                                                  // definiert "TempDataAnz"
    int16_t temp;                                                       // definiert "temp"
    
    TLV493_Read();                                                      // ruft "TLV493_Read" auf
    temp = readBuffer[3];                                               // "temp" gleich "readBuffer[3]"
    temp = temp << 4;                                                   // "temp" 4 nach links
    temp = temp & 0x0F00;                                               // "temp" UND 0x0F00
    temp = temp | readBuffer[6];                                        // 
    if(temp > 2048){                                                    // wenn "temp" größer ist als 2048
        temp = temp - 4096;                                             // "temp" - 4096
    }                                                                   // 
    TempDataAnz = (temp * 1.1) - 340;                                   // "TempDataAnz" gleich "temp" * 1.1 - 340
    return TempDataAnz;                                                 // gibt "TempDataAnz" zur?ck     
}                                                                       // 

void i2c1_message_pending_100(void){                                    // "i2c1_message_pending_100"
    retryTimeOut1 = 0;                                                  // setzt "retryTimeOut1" auf 0
    retryTimeOut2 = 0;                                                  // setzt "retryTimeOut2" auf 0
    while(status == I2C1_MESSAGE_PENDING){                              // solange "status" gleich "I2C1_MESSAGE_PENDING" ist
        if (retryTimeOut2 == 1000){                                      // wenn "retryTimeOut2" gleich 100 ist
            break;                                                      // Abbruch der Schleife
        }else{                                                          // sonst
            retryTimeOut2++;                                            // "retryTimeOut2" +1
        }                                                               // 
    }
    while(status != I2C1_MESSAGE_FAIL){                                 // solange "status" nicht gleich "I2C1_MESSAGE_FAIL" ist
        if (retryTimeOut1 == 1000){                                      // wenn "retryTimeOut1" gleich 100 ist
            break;                                                      // Abbruch der Schleife
        }else{                                                          // sonst
            retryTimeOut1++;                                            // "retryTimeOut1" +1
        }                                                               // 
    }                                                                   // 
}                                                                       // 