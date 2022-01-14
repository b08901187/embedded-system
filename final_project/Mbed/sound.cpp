#include "sound.h"


#include "mbed.h"
#include <cstdio>

const float volume = 0.2; 

PwmOut beep(D10);

void stop(int time){
    beep.period(1);
    beep.write(0.00);
    ThisThread::sleep_for(time);
}

void Do(float multiple, int time){
    float period = 1/261.6 / multiple;
    beep.period(period);
    beep.write(volume); 
    ThisThread::sleep_for(time);
}

void Do_s(float multiple, int time){
    float period = 1/277.18 / multiple;
    beep.period(period);
    beep.write(volume); 
    ThisThread::sleep_for(time);
}

void Re(float multiple, int time){
    float period = 1/293.66 / multiple;
    beep.period(period);
    beep.write(volume); 
    ThisThread::sleep_for(time);
}
void Re_s(float multiple, int time){
    float period = 1/311.13 / multiple;
    beep.period(period);
    beep.write(volume); 
    ThisThread::sleep_for(time);
} 
void Mi(float multiple, int time){
    float period = 1/329.63 / multiple;
    beep.period(period);
    beep.write(volume); 
    ThisThread::sleep_for(time);
} 
void Fa(float multiple, int time){
    float period = 1/349.23 / multiple;
    beep.period(period);
    beep.write(volume); 
    ThisThread::sleep_for(time);
} 
void Fa_s(float multiple, int time){
    float period = 1/369.99 / multiple;
    beep.period(period);
    beep.write(volume); 
    ThisThread::sleep_for(time);
} 
void So(float multiple, int time){
    float period = 1/392.00 / multiple;
    beep.period(period);
    beep.write(volume);
    ThisThread::sleep_for(time);
} 
void So_s(float multiple, int time){
    float period = 1/415.30 / multiple;
    beep.period(period);
    beep.write(volume); 
    ThisThread::sleep_for(time);
} 
void La(float multiple, int time){
    float period = 1/440.00 / multiple;
    beep.period(period);
    beep.write(volume); 
    ThisThread::sleep_for(time);
} 
void La_s(float multiple, int time){
    float period = 1/466.16 / multiple;
    beep.period(period);
    beep.write(volume);
    ThisThread::sleep_for(time);
} 
void Si(float multiple, int time){
    float period = 1/493.88 / multiple;
    beep.period(period);
    beep.write(volume); 
    ThisThread::sleep_for(time);
} 


/*void Lizz_and_blue_bird()
{

}*/
void Radetzky_March()
{  
    //1
    Do(2, Eighthnote-100); stop(100);
    Do(2, Eighthnote-100); stop(100);
    Do(2, Eighthnote-100); stop(100);
    stop(Eighthnote-100);  stop(100);
    Do(2, Eighthnote-100); stop(100);
    Do(2, Eighthnote-100); stop(100);
    Do(2, Eighthnote-100); stop(100);
    stop(Eighthnote-100);  stop(100);
    //2
    Mi(2, Quarternote-50); stop(50);
    Re(2, Quarternote-50); stop(50);
    Do(2, Quarternote + Eighthnote-50); stop(50);
    Si(1, Eighthnote-80); stop(80);
    //3    
    La(1, Eighthnote-80); stop(80);
    So_s(1, Eighthnote-80);stop(80);
    La(1, Eighthnote-80); stop(80);
    Si(1, Eighthnote-80); stop(80);
    Do(2, Quarternote-150); stop(150);
    Re(2, Quarternote-150); stop(150);
    //4
    So(1, Quarternote-150); stop(150);
    stop(2 * Quarternote);
    Fa(2, 30); Mi(2, Eighthnote-80); stop(50);
    Re_s(2, Eighthnote-70); stop(70); 
    //5
    Mi(2, Eighthnote-50); stop(50);
    stop(Eighthnote);
    Fa(2, 30); Mi(2, Eighthnote-80); stop(50);
    Re_s(2, Eighthnote-70); stop(70);
    Mi(2, Eighthnote-50); stop(50);
    stop(Eighthnote);
    Fa(2, 30); Mi(2, Eighthnote-80); stop(50);
    Re_s(2, Eighthnote-70); stop(70);
    //6
    Mi(2, Eighthnote-70); stop(70);
    stop(Eighthnote);
    Re(2, Eighthnote-70); stop(70);
    stop(Eighthnote);
    Do(2, Eighthnote-70); stop(70);
    stop(Eighthnote);
    Fa(2, 30); Mi(2, Eighthnote-80); stop(50);
    Re_s(2, Eighthnote-70); stop(70);
    //7
    Mi(2, Eighthnote-50); stop(50);
    stop(Eighthnote);
    Fa(2, 30); Mi(2, Eighthnote-80); stop(50);
    Re_s(2, Eighthnote-70); stop(70);
    Mi(2, Eighthnote-50); stop(50);
    stop(Eighthnote);
    Fa(2, 30); Mi(2, Eighthnote-80); stop(50);
    Re_s(2, Eighthnote-70); stop(70);
    //8
    Mi(2, Eighthnote-70); stop(70);
    stop(Eighthnote);
    La(2, Eighthnote-70); stop(70);
    stop(Eighthnote);
    So(2, Eighthnote-70); stop(70);
    stop(Eighthnote);
    So(2, Eighthnote-70); stop(70);
    Mi(2, Eighthnote-70); stop(70);
    //9
    Fa(2, Eighthnote-70); stop(70);
    stop(Eighthnote);
    La(2, Eighthnote-70); stop(70);
    stop(Eighthnote);
    So(2, Eighthnote-70); stop(70);
    stop(Eighthnote);
    So(2, Eighthnote-70); stop(70);
    Re(2, Eighthnote-70); stop(70);
    //10
    Mi(2, Eighthnote-70); stop(70);
    stop(Eighthnote);
    La(2, Eighthnote-70); stop(70);
    stop(Eighthnote);
    So(2, Eighthnote-70); stop(70);
    stop(Eighthnote);
    So(2, Eighthnote-70); stop(70);
    Mi(2, Eighthnote-70); stop(70);
    //11
    Re(2, Eighthnote-70); stop(70);
    stop(Eighthnote);
    Si(2, Eighthnote + Quarternote - 70); stop(70);
    /*stop(Eighthnote);
    Do(2, Eighthnote-70); stop(70);*/
    stop(Eighthnote);
    La(2, Eighthnote-70); stop(70);
    stop(Eighthnote);
    //12
    So(2, Eighthnote-70); stop(70);

}

void Cody()
{
    //1
    Re(4, 400);
    Do_s(4, 400);
    La(2, 400);
    //2
    Re(4, 400);
    Do_s(4, 400);
    La(2, 400);
    //3
    Si(2, 400);
    La(2, 400);
    So(2, 400);
    //4
    La(2, 2000);
    stop(400);
    //6
    Re(4, 400);
    Do_s(4, 400);
    La(2, 400);
    //7
    Re(4, 400);
    Do_s(4, 400);
    La(2, 400);
    //8
    Si(2, 400);
    Do_s(4, 400);
    Re(4, 400);
    //9
    La(2, 2000);
    stop(400);
    
    //11
    Re(4, 400);
    Do_s(4, 400);
    La(2, 400);
    //12
    Re(4, 400);
    Do_s(4, 400);
    La(2, 400);
    //13
    Si(2, 400);
    La(2, 400);
    So(2, 400);
    //14
    La(2, 2000);
    stop(400);

    //15
    Fa_s(2, 400);
    So(2, 400);
    Fa_s(2, 400);
    //16
    Mi(2, 350);
    stop(50);
    Mi(2, 400);
    Re(2, 400);
    //17
    Do_s(2, 400);
    Re(2, 2000);

    stop(1000);
}

