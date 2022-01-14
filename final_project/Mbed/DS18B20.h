#ifndef DS18B20_h
#define DS18B20_h

#include <OneWire.h>
#include <mbed.h>

// Change the definition to your pin!
#define DS18B20_DATA_PIN D2
#define FOURDIGIT_CLK_PIN A4
#define FOURDIGIT_DIO_PIN A5

void setup(int v);
void temp_indi(void);
void loop(void);

#endif
