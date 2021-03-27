// uLCD-144-G2 basic text demo program for uLCD-4GL LCD driver library
//
#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;
DigitalIn BT1(A3), BT2(A4), BT3(A5);
AnalogOut  aout(PA_4);
AnalogIn ain(A0);

int ULCD() {
    int S = 0;
    int CM = -1;
    uLCD.background_color(WHITE);
    uLCD.cls();
    uLCD.color(BLUE);
    uLCD.text_width(2); //4X size text
    uLCD.text_height(2);
    uLCD.locate(1,2);
    uLCD.printf("240 Hz \n"); //Default Green on black text
   //uLCD.printf("\n  Starting Demo...");
    uLCD.locate(1,4);
    uLCD.printf("720 Hz \n");
    while(true) {
        while(!S) {
            uLCD.locate(7,4);
            uLCD.printf(" ");
            uLCD.locate(7,2);
            uLCD.color(RED);
            uLCD.printf("<");
            if(!BT2) {
                S = 1;
            }; 
            if (!BT3) {
                CM = 0;
                uLCD.locate(7,2);
                uLCD.color(WHITE);
                uLCD.printf("<");
                return 0;
            };
        }
        while(S) {
            uLCD.locate(7,2);
            uLCD.printf(" ");
            uLCD.locate(7,4);
            uLCD.color(RED);
            uLCD.printf("<");
            if(!BT1) {
                S = 0;
            }; 
            if (!BT3) {
                CM = 1;
                uLCD.locate(7,4);
                uLCD.color(WHITE);
                uLCD.printf("<");
                return 1;
            };
        }
    }

}
int main()
{
    int x = ULCD();
  //  if(x == 1) printf("1\n");
  //  else printf("0\n");
    if(x == 1) {
        float ADCdata[300];
        int g = 0;
        while (1) {
            for (float i = 0.0f; i < 150.0f; i += 1.0f) {
                double sam = 0;
                if(i < 135) {
                   sam =  i / 150;
                }
                else {
                   sam = (150 - i) / 15 * 9 / 10;
                }
                aout = sam;
                if (g%5 == 0)
                ADCdata[g/5] = ain;
                g++;
             
            }
            if (g == 1500) {
                for (int i = 0; i < 300; i++) {
                    printf("%f\r\n", ADCdata[i] * 3.3);
                    ThisThread::sleep_for(100ms);
                }
                g = 0;
                return 0;
            }
        }

    } else if (x == 0) {
        float ADCdata[300];
        int g = 0;
        while (1) {
            for (float i = 0.0f; i < 300.0f; i += 1.0f) {
                double sam = 0;
                if(i < 270) {
                   sam =  i / 300;
                }
                else {
                   sam = (300 - i) / 30 * 9 / 10;
                }
                aout = sam;
                if (g%3 == 0)
                ADCdata[g/3] = ain;
                g++;
             
            }
            if (g == 900) {
                for (int i = 0; i < 300; i++) {
                    printf("%f\r\n", ADCdata[i] * 3.3);
                    ThisThread::sleep_for(100ms);
                }
                g = 0;
                return 0;
            }
        }
    }
    
}