/*****    
 * APSC 1299    
 * Lab 9 - Pololu 3pi Robot   
 * Student file - Robotmain.c source code    
 * 
 * The robot name is Wheelson (All members agreed)
 * Date:  09-MAR-2021
 *****/


#include <xc.h>
#include <stdio.h>
#include "device_config.h"
#include "initialize.h"
#include "pin_manager.h"
#include "pwm7.h"
#include "tmr0.h"
#include "tmr2.h"
#include "uart1.h"
#include "uart2.h"
#include "pololu_robot.h"

#define TRUE    1
#define FALSE   0

#define RUN         1
#define DIAGNOSE    0


void Diagnostic_Menu(void);
char Get_Number(void);
char Get_Key(void);
void Countdown(char time);

void main(void) 
{
    SYSTEM_Initialize();
    PIN_MANAGER_Initialize();
    UART1_Initialize();
    UART2_Initialize();
    
    //  Pin settings
    TRISBbits.TRISB5 = INPUT;      //  Monitors value of RUN / DIAGNOSE switch
    ANSELBbits.ANSELB5 = DIGITAL;
    
    //  Variable declarations
    char key, speed, differential;
    char i, length, any, sensor;
    char msg[9];
    unsigned int sum, battery;
    
    unsigned int total_sum;
    
    unsigned int* sensor_value;
    bool white, black;
            

    if (PORTBbits.RB5 == DIAGNOSE)      //  Run code in diagnostic mode
    {
        Diagnostic_Menu();
        LCD_Clear();
        LCD_Position(0,0);
        LCD_Print("Diagnose", 8);
        battery = Read_Battery_Voltage();
        length = sprintf(msg, "%u mV", battery);
        LCD_Position(0,1);
        LCD_Print(msg, length);
        while(1)
        {
            key = Get_Key();
            switch (key)
            {
                case 'b':
                   /* printf("\n\r");
                    printf("\t Please enter the forward speed, 0 - 127 \r\n");
                    speed = Get_Number();
                    */
                    Countdown(6);
                    Forward(20);
                    TMR0_Initialize(T0_16_BIT & T0_POST_1_1, T0_PRE_1_512 & T0_SYNC & T0_SOURCE_INT);
                    TMR0_Write16BitTimer(6940);
                    TMR0_StartTimer();
                    while(1)
                    {
                        if (TMR0_HasOverflowOccured())
                        {
                            TMR0_StopTimer();
                            Forward(0);
                         break;  
                        }
                    }
                    break;
                    
                case 'c':
                    LCD_Clear();
                    LCD_Position(0,0);
                    LCD_Print("Calibrate", 8);
                    LCD_Position(0,1);
                    LCD_Print("Sensors ", 8);
                    printf("\n\r");
                    white = FALSE;
                    while (!white)
                    {
                        printf("Place all five sensors on a white surface \n\r");
                        printf("Press any key to continue \n\r");
                        any = Get_Key();
                        sensor_value = Calibrate_Sensors();
                        sum = 0;
                        for (i=0; i<5; i++)
                        {
                            sum = sum + sensor_value[i];
                            printf("Sensor %u = %u \n\r", i, sensor_value[i]);
                        }
                        if (sum == 0)
                        {
                            white = TRUE;
                            printf("White calibration complete \n\r");
                        }
                    }
                    black = FALSE;
                    while (!black)
                    {
                        printf("Place all five sensors on a black surface \n\r");
                        printf("Press any key to continue \n\r");
                        any = Get_Key();
                        sensor_value = Calibrate_Sensors();
                        sum = 0;
                        for (i=0; i<5; i++)
                        {
                            sum = sum + sensor_value[i];
                            printf("Sensor %u = %u \n\r", i, sensor_value[i]);
                        }
                        if (sum == 5000)
                        {
                            black = TRUE;
                            printf("Black calibration complete \n\r");
                            printf("Calibration complete \n\r");
                            LCD_Position(0,1);
                            LCD_Print("Complete", 8);
                        }
                    }
                    break;
                case 'r':
                    LCD_Clear();
                    LCD_Position(0,0);
                    LCD_Print("  Read  ", 8);
                    LCD_Position(0,1);
                    LCD_Print("Sensors", 8);
                    printf("\n\r");

                    //  Add code to read calibrated values of all sensors
                    sensor_value = Read_Calibrated_Sensors();
                    
                        for (i=0; i<5; i++)
                        {
                            printf("Sensor %u = %u \n\r", i, sensor_value[i]);
                        }
                    //  and print sensor number and values to PuTTY

                    break;
                    
                case 'd':
                    
                    LCD_Clear();
                    LCD_Position(0,0);
                    LCD_Print("Sensor ", 7);
                    printf("\n\r");
                    printf("Enter sensor number, 0-4 \n\r");
                    sensor = Get_Number();
                    printf("\n");
    
                    while (sensor < '0' || sensor > '4')
                    {
                    printf("\n\r");
                    printf("Invalid entry.  Enter sensor number, 0-4 \n\r");
                    sensor = Get_Number();
                    }
    
                    LCD_Position(7,0);
                    LCD_PrintCharacter(sensor);

                    //  Add code to get sensor value of selected sensor and
                    sensor_value = Calibrate_Sensors();
                    //  display to second line of LCD as well as PuTTy
                    printf("\nSensor %d = %u \n\r", sensor, sensor_value[sensor]);
                    length = sprintf(msg,"  %u  ",sensor_value[sensor]);
                    LCD_Position(0,1);
                    LCD_Print(msg, length);
                    break;
    
                case 'v':
                    LCD_Clear();
                    LCD_Position(0,0);
                    LCD_Print("Battery ", 8);
                    printf("\n\r");
                    battery = Read_Battery_Voltage();
                    length = sprintf(msg, "%u mV", battery);
                    LCD_Position(0,1);
                    LCD_Print(msg, length);
                    printf("Battery voltage = %u \n\r", battery);
                    break;
                case 'F':
                    LCD_Clear();
                    LCD_Position(0,0);
                    LCD_Print("Forward ", 8);
                    printf("\n\r");
                    printf("\t Please enter the forward speed, 0 - 127 \r\n");
                    speed = Get_Number();
                    Forward(speed);
                    length = sprintf(msg, " %u ", speed);
                    LCD_Position(0,1);
                    LCD_Print(msg, length);
                    break;
                case 'B':
                    LCD_Clear();
                    LCD_Position(0,0);
                    LCD_Print("Backward", 8);
                    printf("\n\r");
                    printf("\t Please enter the backward speed, 0 - 127 \r\n");
                    speed = Get_Number();
                    Backward(speed);
                    length = sprintf(msg, " %u ", speed);
                    LCD_Position(0,1);
                    LCD_Print(msg, length);
                    break;
                case 'L':
                    LCD_Clear();
                    LCD_Position(0,0);
                    LCD_Print("  Left  ", 8);
                    printf("\n\r");
                    printf("\t Please enter the forward speed, 0 - 127 \r\n");
                    speed = Get_Number();
                    printf("\t Please enter the turning differential: speed + differential < 127 \r\n");
                    differential = Get_Number();
                    Left_Turn(speed, differential);
                    length = sprintf(msg, "%u %u", speed, differential);
                    LCD_Position(0,1);
                    LCD_Print(msg, length);
                    break;
                case 'R':
                    LCD_Clear();
                    LCD_Position(0,0);
                    LCD_Print(" Right  ", 8);
                    printf("\n\r");
                    printf("\t Please enter the forward speed, 0 - 127 \r\n");
                    speed = Get_Number();
                    printf("\t Please enter the turning differential: speed + differential < 127 \r\n");
                    differential = Get_Number();
                    Right_Turn(speed, differential);
                    length = sprintf(msg, "%u %u", speed, differential);
                    LCD_Position(0,1);
                    LCD_Print(msg, length);
                    break;
                case 'S':
                    LCD_Clear();
                    LCD_Position(0,0);
                    LCD_Print("  Stop  ", 8);
                    printf("\n\r");
                    Stop();
                    break;
                 
                case 'T':
                    
                    LCD_Clear();
                    LCD_Position(0, 0);
                    LCD_Print("TSensor",7);
                    LCD_Position (0,1);
                    LCD_Print("Run",3);
              
                    while (1)
                    {    
                    
                    sensor_value = Read_Calibrated_Sensors();
                        
                      for (i=0; i<5; i++)
                      {
                         printf("\nSensor %u = %u \n\r", i, sensor_value[i]);
                      }
                        printf("\n");
                        _delay(10000000); 
                       
                        if (UART2_is_rx_ready()) 
                        {
                            char input = UART2_Read();
                            if (input == 'q' || input == 'Q') {
                                break; //Exit the loop and return the diagnostic menu 
                            }
                        }
                    }
                    
                                     
                case 'm':
                LCD_Clear();
                    LCD_Position(0,0);
                    LCD_Print("Diagnose", 8);
                    battery = Read_Battery_Voltage();
                    length = sprintf(msg, "%u mV", battery);
                    LCD_Position(0,1);
                    LCD_Print(msg, length);
                    Diagnostic_Menu();
                    break;
                    
                case 'q':
                    LCD_Clear();
                    LCD_Position(0,0);
                    LCD_Print("Spin", 4);
                    printf("\n\r");
                    printf("\t Please enter the spin speed (right), 0 - 127 \r\n");
                    speed = Get_Number();
                    Spin_Right(speed);
                    length = sprintf(msg, " %u ", speed);
                    LCD_Position(0,1);
                    LCD_Print(msg, length);
                    break;
                    
                case 'w':
                    LCD_Clear();
                    LCD_Position(0,0);
                    LCD_Print("Spin", 4);
                    printf("\n\r");
                    printf("\t Please enter the spin speed (left), 0 - 127 \r\n");
                    speed = Get_Number();
                    Spin_Left(speed);
                    length = sprintf(msg, " %u ", speed);
                    LCD_Position(0,1);
                    LCD_Print(msg, length);
                    break;
                    
                case 'l':
                    LCD_Clear();
                    LCD_Position(0,0);
                    LCD_Print("180",3);
                    Full_Rotation_30();
                    break;
                    
                case 'z':
                    Go_1cm();
            }
        }
    }

    if (PORTBbits.RB5 == RUN)       //  Run line-following code
    {
       Diagnostic_Menu();
        LCD_Clear();
        LCD_Position(0,0);
        LCD_Print("  Run   ", 8);
        battery = Read_Battery_Voltage();
        length = sprintf(msg, "%u mV", battery);
        LCD_Position(0,1);
        LCD_Print(msg, length);
        __delay_ms(1000);       //  Delay allows user to quickly read voltage
        LCD_Position(0,0);
        LCD_Print("Auto Cal", 8);
       Auto_Calibrate();
	   LCD_Position(0,1);
       LCD_Print("  done  ", 8);
       Countdown(5);
       TMR0_Write16BitTimer(0);
       TMR0_Initialize(T0_16_BIT & T0_POST_1_1, T0_PRE_1_512 & T0_SOURCE_INT & T0_SYNC);
        
        //  Start robot moving using 3pi PID function
        //  Speed = 30; a = 1; b = 20; c = 3; d = 2
        while(1)
    {            
                   
    sensor_value = Read_Calibrated_Sensors();
    
    sum = sensor_value[0]+sensor_value[1]+sensor_value[3];
    total_sum = sensor_value[0]+sensor_value[1]+sensor_value[2]+sensor_value[3]+sensor_value[4];
    
    length = sprintf(msg, "%u/%u", sum, total_sum);
    LCD_Position(1,0);
    LCD_Print(msg, length);
    
   if (sensor_value[4] < 100 && sensor_value[0] < 100 && sensor_value[2] > 100) // PID default
    {
       LCD_Position(0,1);
       LCD_Print("PID", 3);
        Turn_PID_ON ();
    }

    if(total_sum > 4500)           //  this either a cross-over or the actual landing PAD
    {
       LCD_Clear();
       LCD_Position(0,1);
       LCD_Print("PAD", 3);
       Turn_PID_OFF();
       Landing_Pad();
    }

    if (total_sum < 100) // for gap, turn off PID and go forward 
    {
      Forward(20);
      LCD_Clear();
      LCD_Position(0,1);
      LCD_Print("GAP", 3);
      Turn_PID_OFF();
      Gap();
    }

    if (sensor_value[4] >= 990 && sum < 100) // If the right sensor[4] detects black,go right.
    { 
       LCD_Position(0,1);
       LCD_Print("RTURN", 4);

       Turn_PID_OFF();
       Correct_Path_To_Right();
       Turn_PID_ON();
    }

    if (sensor_value[3] > 200 && sensor_value[4] > 200)
    {
        LCD_Position(0,1);
        LCD_Print("RSHARP", 6);

        Turn_PID_OFF();
        for (int i = 0; i < 2; i++)
        {
            Go_1cm();
        }
        Correct_Path_To_Right();
        Turn_PID_ON();
    }

    if(sensor_value[0] > 200 && sensor_value[1] > 200)
    {
        LCD_Position(0,1);
        LCD_Print("LSHARP", 6);

        Turn_PID_OFF();
        for (int i = 0; i < 2; i++)
        {
            Go_1cm();
        }
        Correct_Path_To_Left();
        Turn_PID_ON();
    }

    if (sensor_value[0] >= 990 && sum < 100) //sensor[4] is the right one and sensor[0] is the left sensor
    {
       LCD_Clear();
       LCD_Position(0,1);
       LCD_Print("LTURN", 4);

       Turn_PID_OFF();
       Correct_Path_To_Left();
       Turn_PID_ON();
    }
        
    }
    }
}


void Diagnostic_Menu (void)
{
    printf("\r\n");
    printf("\t******************************\r\n");
    printf("\t*                            *\r\n");
    printf("\t*   APSC 1299 - Pololu 3pi   *\r\n");
    printf("\t*      Diagnostic Menu       *\r\n");
    printf("\t*                            *\r\n");
    printf("\t******************************\r\n");
    printf("\n\r");
    printf("Command Key \t Description \r\n");
    printf("  c \t\t (c)alibrate sensors \r\n");
    printf("  r \t\t (r)ead calibrated sensors \r\n");
    printf("  d \t\t (d)isplay sensor x value \r\n");
    printf("\r\n");
    printf("  v \t\t (v)oltage - Read and display battery voltage \r\n");
    printf("\r\n");
    printf("  F \t\t Wheels rotate (F)orward \r\n");
    printf("  B \t\t Wheels rotate (B)ackward \r\n");
    printf("  L \t\t (L)eft turn \r\n");
    printf("  R \t\t (R)ight turn \r\n");
    printf("  S \t\t (S)top motor \r\n");
    printf("  T \t\t (T)est sensor run \r\n");
    printf("\r\n");
    printf("  m \t\t Refresh (m)enu \r\n");
    printf("\n\r");
    printf(" q \t\t spin the robot right (clockwise)\r\n");
    printf(" w \t\t spin the robot left (counter-clockwise)\r\n");
    printf("l  \t\t do a 180 degree rotation at 30 cm/s \r\n");
}

//  Reads digit characters and returns a numerical value
//  Numerical value limited to 255
char Get_Number(void)
{
    char digit = 255;
    char value = 0;
    
    while(digit != '\r') 
    {
        digit = Get_Key();
        if (digit == '\r')
            continue;
        else if (digit < 48 || digit > 57)
        {
            printf("\n\r");
            printf("Invalid input. Please redo numerical input. \r\n");
            value = 0;
            digit = 255;
        }
        else
            value = value*10 + (digit-48);
    }
    return(value);
}

//  Code execution holds until valid keypress is detected
//  Valid keypress is any alpha-numeric key and/or 'ENTER'
char Get_Key(void)
{
    char rxdata = 255;
    
    //  execution holds until valid keypress detected
    while(((rxdata < 48) || (rxdata > 122)) && (rxdata != '\r'))
    {
        if (UART2_is_rx_ready()) 
        {
            rxdata = UART2_Read();
            if (UART2_is_tx_ready())
            {
                UART2_Write(rxdata);
                if(rxdata == '\r') 
                    UART2_Write('\n'); 
            }
        }
    }
    return(rxdata);
}

//  Timed delay before the robot starts moving
//  Parameter time is delay in seconds
void Countdown(char time)
{
    char length, msg[9];
    char i = time;
    unsigned int counts;
    
    LCD_Clear();
    LCD_Print("Counting", 8);
    TMR0_Initialize(T0_16_BIT & T0_POST_1_1, T0_SOURCE_INT & T0_SYNC & T0_PRE_1_256);
    TMR0_StartTimer();
    LCD_Position(0,1);
    length = sprintf(msg, "  %u s  ", i);
    LCD_Print(msg, length);
    while (i > 0)
    {
        counts = TMR0_Read16BitTimer();
        if (counts >= 46875)
        {
            i--;
            TMR0_Write16BitTimer(0);
            switch(i)
            {
                case 0:
                    LCD_Clear();
                    LCD_Position(0,1);
                    LCD_Print("   GO   ", 8);
                    break;
                case 1:
                    LCD_Position(0,1);
                    LCD_Print("  SET   ", 8);
                    break;
                case 2:
                    LCD_Position(0,1);
                    LCD_Print(" READY  ", 8);
                    break;
                default:
                    LCD_Position(0,1);
                    length = sprintf(msg, "  %u s  ", i);
                    LCD_Print(msg, length);
            }
        }
    }
    TMR0_StopTimer();
}

/*  END FILE    */
