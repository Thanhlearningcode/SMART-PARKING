#include <16F877A.h>
#include <RS232.h>

#use rs232(baud=9600, parity=N, xmit=PIN_C6, rcv=PIN_C7, bits=8)
#device ADC=10
#use delay(crystal=4000000)

// Pin definitions
#define hongngoai1 PIN_D0
#define hongngoai2 PIN_D1
#define servo1 PIN_C1
#define servo2 PIN_C2

// Constants for servo angles
#define ANGLE_MIN 1000
#define ANGLE_MAX 2000
#define ANGLE_STEP 50

// Variables
int16 angle1 = ANGLE_MIN;
int16 angle2 = ANGLE_MIN;
char c;
int a;

// Function prototypes
void control_servo1(int16 time1);
void control_servo2(int16 time2);

void main()
{ 
    // Configure PORTB as input and PORTD as output
    set_tris_b(0xFF);   // Set PORTB as input
    port_b_pullups(1);  // Enable pull-ups on PORTB
    set_tris_d(0x00);   // Set PORTD as output
    
    // Initial output settings
    output_high(PIN_D7);
    output_low(PIN_D6);

    // Main loop
    while(TRUE)
    {
        // Check for received data
        if(kbhit()) 
        {
            c = getch();
            
            switch(c)
            {
                case '1':
                    output_high(PIN_D6);
                    angle1 = ANGLE_MIN;
                    control_servo1(angle1);
                    delay_ms(50);
                    angle1 += ANGLE_STEP;
                    if(angle1 > ANGLE_MAX) angle1 = ANGLE_MAX;
                    break;
                    
                case '2':  
                    angle2 = ANGLE_MIN;
                    control_servo2(angle2);
                    delay_ms(50);
                    angle2 += ANGLE_STEP;
                    if(angle2 > ANGLE_MAX) angle2 = ANGLE_MAX;
                    break;
                    
                case '3':
                    output_low(PIN_D6);
                    angle1 = ANGLE_MAX;
                    control_servo1(angle1);
                    delay_ms(50);
                    angle1 -= ANGLE_STEP;
                    if(angle1 < ANGLE_MIN) angle1 = ANGLE_MIN;
                    break;
                    
                case '4':
                    angle2 = ANGLE_MAX;
                    control_servo2(angle2);
                    delay_ms(50);
                    angle2 -= ANGLE_STEP;
                    if(angle2 < ANGLE_MIN) angle2 = ANGLE_MIN;
                    break;
            }
        }

        // Handle external input for servo control
        if(!input(PIN_B0)) { a = 1; }
        if(!input(PIN_B1) || !input(hongngoai1)) { a = 2; }
        if(!input(PIN_B2) || !input(hongngoai2)) { a = 3; }
        if(!input(PIN_B3)) { a = 4; }
        
        switch(a)
        {
            case 1:  
                output_high(PIN_D6);
                angle1 = ANGLE_MIN;
                control_servo1(angle1);
                delay_ms(50);
                angle1 += ANGLE_STEP;
                if(angle1 > ANGLE_MAX) angle1 = ANGLE_MAX;
                break;
                
            case 2:
                angle2 = ANGLE_MIN;
                control_servo2(angle2);
                delay_ms(50);
                angle2 += ANGLE_STEP;
                if(angle2 > ANGLE_MAX) angle2 = ANGLE_MAX;
                break;
                
            case 3:
                output_low(PIN_D6);
                angle1 = ANGLE_MAX;
                control_servo1(angle1);
                delay_ms(50);
                angle1 -= ANGLE_STEP;
                if(angle1 < ANGLE_MIN) angle1 = ANGLE_MIN;
                break;
                
            case 4:
                angle2 = ANGLE_MAX;
                control_servo2(angle2);
                delay_ms(50);
                angle2 -= ANGLE_STEP;
                if(angle2 < ANGLE_MIN) angle2 = ANGLE_MIN;
                break;
        }
    }
}

// Function to control servo 1 with specified time in microseconds
void control_servo1(int16 time1)
{
    output_high(servo1);
    delay_us(time1);
    output_low(servo1);
    delay_us(20000 - time1);
}

// Function to control servo 2 with specified time in microseconds
void control_servo2(int16 time2)
{
    output_high(servo2);
    delay_us(time2);
    output_low(servo2);
    delay_us(20000 - time2);
}
