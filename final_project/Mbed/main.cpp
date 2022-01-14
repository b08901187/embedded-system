#include <DS18B20.h>
#include "mbed.h"
#include "sound.h"
#include "socket.h"
#include "teaadd.h"
#include "heater.h"


int main()
{
    turn_off_heater();   
    while (!socket_start()) 
    {
        printf("reject\n");
    }
    
    //printf("what ? \n");
    
    //Cody();
    setup(get_temp());
    temp_indi();
    tea_add();
    
    thread_sleep_for(100);
    Radetzky_March();

    while (true)
    {
        loop();
    }
}