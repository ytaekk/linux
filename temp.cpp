#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_TIMINGS 85
#define DHT_PIN 7

int data[5]={0, 0, 0, 0, 0};

void read_dht_data()
{
    uint8_t laststate = HIGH;
    uint8_t counter = 0;
    uint8_t j=0;
    uint8_t i;

    for(i=0;i<5;i++) {data[i] = 0;}
    //printf("1. Done\n");

    pinMode(DHT_PIN, OUTPUT);
    digitalWrite(DHT_PIN, LOW);
    delay(18);
    pinMode(DHT_PIN, INPUT);

    for(i=0; i<MAX_TIMINGS; i++)
    {
        //printf("1. 데이터 반복 읽기 for 문 진입\n [i: %d ]", i);

        counter = 0;
        
        while(digitalRead(DHT_PIN)==laststate)
        {
            //printf("3. while 문 진입 [DHT_PIN : %d , laststate : %d]\n", DHT_PIN, laststate);
            counter++;
            delayMicroseconds(1);
            //printf("3-1. while 문 진입 [counter : %d]\n", counter);
            if(counter==255) 
            {
            //    printf("4. 3while counter=255  break\n");
                break;
            }
        }

        laststate = digitalRead(DHT_PIN);
        //printf("4-1. [laststate:  %d] counter : %d\n", laststate, counter);
        if(counter==255) {
            //printf("break\n", i);
            break;}

        //printf("5. [i : %d]\n", i);
        if((i>=4)&&(i%2==0))
        {
            data[j/8]<<=1;
            if(counter>16){
                data[j/8] |= 1;
            }
            j++;
        
        }
    }
    
    if((j>=40)&&(data[4]==((data[0]+data[1]+data[2]+data[3])&0xFF)))
    {
        int h = (int)data[0];
        int c = (int)(data[2]&0x7F);
        if(data[2]&0x80) c=-c;
        printf("Humidity = %d %% Temp = %d *C \n",h,c);
    }
    else{
        printf("Data not good, skip \n");

    }
}
int main()
{
    printf("DHT11 TEMP / HUMIDITY TEST \n");

    if(wiringPiSetup()==-1)
        exit(1);
    while(1)
    {
        read_dht_data();
        delay(2000);
    }
    return 0;
}
