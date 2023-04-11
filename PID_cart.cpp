/*
超音波センサーとPIDを使って台車の位置をｴｴ感じにするプログラム
参考：https://www.youtube.com/watch?v=oy58S4beC9c
*/
#include "mbed.h"
#include "hcsr04.h"
#include "PID.h"
#include <type_traits>

#define add 0x20

HCSR04  fuga(NC, NC);           //超音波センサー
Thread  hoge;                   //I2C送信用
PID     controller(2,0,0,0.001);  //
I2C     i2c(D14,D15);

unsigned int dist;
char power;

void send(char, char);

int main(void){
    dist = 0;
    // PIDの初期設定たち
    controller.setInputLimits(0, 30);       //ブツの長さによる
    controller.setSetPoint(10);             //目的とする距離[cm]
    // PIDの初期設定、以上
    while(true){
        fuga.start();
        wait_us(50000);
        dist = fuga.get_dist_cm();

        // distの値によって回転方向を決める
        if(dist >= 10 && dist <= 30){
            controller.setOutputLimits(128,256);
            controller.setProcessValue((float)dist);
        }
        else if(dist < 10){
            controller.setOutputLimits(128,0);
            controller.setProcessValue(float(dist));
        }
        
        power = controller.compute();
        send(add,(char)power);
    }
}

void send(char address,char duty){
    i2c.start();
    i2c.write(address);
    i2c.write(duty);
    i2c.stop();
    ThisThread::sleep_for(10ms);
}