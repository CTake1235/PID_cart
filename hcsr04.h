#ifndef MBED_HCSR04_H
#define MBED_HCSR04_H

#include "mbed.h"   

class HCSR04{
    public:
        /** Create a HCSR04 object connected to the specified pin
        * @param pin i/o pin to connect to
        */
        
        HCSR04(PinName TrigPin,PinName EchoPin);
        ~HCSR04();

        /** Return the distance from obstacle in cm
        * @param distance in cms and returns -1, in case of failure
        */
        unsigned int get_dist_cm(void);
        /** Return the pulse duration equal to sonic waves travelling to obstacle and back to receiver.
        * @param pulse duration in microseconds.
        */
        unsigned int get_pulse_us(void);
        /** Generates the trigger pulse of 10us on the trigger PIN.
        */
        void start(void );
        void isr_rise(void);
        void isr_fall(void);
        void fall (void (*fptr)(void));
        void rise (void (*fptr)(void));

    private:

        Timer pulsetime;
        DigitalOut  trigger;
        InterruptIn echo;
        unsigned int pulsedur;
        unsigned int distance;
};

#endif