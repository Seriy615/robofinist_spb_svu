#ifndef lib_h
#define lib_h
#include <lib.h>
#include <Servo.h>
Servo Servo1;
int BankaSensorPin = 25;
int banki = 0;
// робот стоит на левом(1) колесе , крутим воторе медленно по кругу,
// если види белую - пинает
Motor motor2(7,8); //поменять 
void white_beat(){
    motor2.stop();
    Servo1.write(120);
    delay(100);
    Servo1.write(0);
    delay(100);
}

void setup(){
    PinMode(BankaSensorPin, INPUT);
    Servo1.attach(servoPin);
}

void loop(){
    value = digitalRead(BankaSensorPin);
    if (value == HIGH){
        white_beat();
        banki++;
    } 
    else if (banki==4){
        return 0;
    }
    else{
        motor2.forward(100);
    }
}