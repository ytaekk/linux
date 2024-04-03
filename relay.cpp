#include<stdio.h>
#include<wiringPi.h>

#define RELAY 2 //Pin 설정

int main()
{
    int ON = 1;
    int OFF = 0;

    if(wiringPiSetup() == -1) return -1; //wiringPI 초기화

    pinMode(RELAY, OUTPUT); // 핀모드 출력 설정
    digitalWrite(RELAY, OFF); // 초기상태 : off

 
        int i;
        for(i = 0; i < 2; i++)
        {
            printf("Relay Test %d \n", i);
            digitalWrite(RELAY, ON); // Relay On
            delay(3000);
            digitalWrite(RELAY, OFF); // Relay Off
            delay(3000);
        }
 
    return 0;

}