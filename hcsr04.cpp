#include "hcsr04.h"
#include "Callback.h"

HCSR04::HCSR04(PinName TrigPin,PinName EchoPin): trigger(TrigPin), echo(EchoPin){
    pulsetime.stop();
    pulsetime.reset();
    echo.rise(Callback<void()>(this, &HCSR04::isr_rise));
    echo.fall(Callback<void()>(this, &HCSR04::isr_fall));
    trigger=0;
}

HCSR04::~HCSR04(){}

void HCSR04::isr_rise(void){
    pulsetime.start();
}

void HCSR04::start(void){
    trigger=1;
    wait_us(10);
    trigger=0;
}

void HCSR04::isr_fall(){
    pulsetime.stop();
    // pulsedur = pulsetime.read_us();
    pulsedur = pulsetime.elapsed_time().count();
    distance= (pulsedur*343)/20000;
    pulsetime.reset();
}

void HCSR04::rise (void (*fptr)(void)){
    echo.rise(fptr);
}

void HCSR04::fall (void (*fptr)(void)){
    echo.fall(fptr);
}

unsigned int HCSR04::get_dist_cm(){
    return distance;
}

unsigned int HCSR04::get_pulse_us(){
    return pulsedur;
}