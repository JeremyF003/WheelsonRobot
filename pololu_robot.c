/*****
    Pololu 3pi
    Slave program source file
 
    09-MAR-2021
*****/

#include "pololu_robot.h"
#include <stdio.h>
#include "uart1.h"
#include "uart2.h"
#include "tmr0.h"
#include "device_config.h"


unsigned int* Calibrate_Sensors(void)
{
    unsigned char lbyte[5], ubyte[5], i;
    static unsigned int values[5];
    
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(CALIBRATE);
    for (i=0; i<5; i++)
    {
        while (!UART1_is_rx_ready()) continue;
        lbyte[i] = UART1_Read();
        while (!UART1_is_rx_ready()) continue;
        ubyte[i] = UART1_Read();
        values[i] = ubyte[i]*256 + lbyte[i];
    }
    return values;
}

void Auto_Calibrate(void)
{
    bool center = 0;
    char lbyte, ubyte;
    unsigned int position;
    
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(AUTO_CALIBRATE);
    while(!UART1_is_rx_ready()) continue;
    while(UART1_Read() != 'c')              //  Wait until Auto Calibrate signals that
    {                                       //  calibration is done, with 'c' character
        while(!UART1_is_rx_ready()) continue;
    }  
}

unsigned int* Read_Calibrated_Sensors(void)
{
    //this function is in case 'r'.
    unsigned char lbyte[5], ubyte[5], i;
    static unsigned int values[5];
    
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(READ_CALIBRATED_SENSORS);
    for (i=0; i<5; i++)
    {
        while (!UART1_is_rx_ready()) continue;
        lbyte[i] = UART1_Read();
        while (!UART1_is_rx_ready()) continue;
        ubyte[i] = UART1_Read();
        values[i] = ubyte[i]*256 + lbyte[i];
    }
    return values;
             
}

unsigned int Read_Battery_Voltage(void)
{
    unsigned char lbyte, ubyte;
       
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(READ_BATTERY);
    while (!UART1_is_rx_ready()) continue;
    lbyte = UART1_Read();
    while (!UART1_is_rx_ready()) continue;
    ubyte = UART1_Read();
    return (unsigned int)(ubyte*256 + lbyte);
}

void LCD_Clear(void)
{
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(CLEAR_LCD);
}

void LCD_Print(char *str, char length)
{
    char i=0;
    
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(PRINT_LCD);
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(length);
    while (i<length)
    {
        if(UART1_is_tx_ready())
        {
            UART1_Write(str[i]);
            i++;
        }
    }
}

void LCD_PrintCharacter(char byte)
{
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(PRINT_LCD);
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(1);
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(byte);
}

void LCD_Position(char x, char y)
{
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(POSITION_LCD);
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(x);
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(y);
}

void Forward(char speed) //try out at 20
{ //1.1875
    //for 80 and above: 1.05 is good
    
   while (!UART1_is_tx_ready()) continue;
   UART1_Write(FORWARD_RIGHT); //RIGHT IS THE STRONGER ONE
   while (!UART1_is_tx_ready()) continue;
   UART1_Write(speed);
   while (!UART1_is_tx_ready()) continue;
   UART1_Write(FORWARD_LEFT);
   while (!UART1_is_tx_ready()) continue;
   UART1_Write(speed*1.15);
   
}

void Backward(char speed)
{
    //  Add code
    while (!UART1_is_tx_ready()) continue;
   UART1_Write(BACKWARD_RIGHT);
   while (!UART1_is_tx_ready()) continue;
   UART1_Write(speed);
   while (!UART1_is_tx_ready()) continue;
   UART1_Write(BACKWARD_LEFT);
   while (!UART1_is_tx_ready()) continue; 
   UART1_Write(speed*1.15);
}

void Left_Turn(char speed, char differential) 
{  
    while (!UART1_is_tx_ready()) continue;
    UART1_Write(FORWARD_LEFT); 
    while (!UART1_is_tx_ready()) continue;
    UART1_Write(speed); //assign speed to go right
    while (UART1_is_tx_ready()) continue;
    UART1_Write(FORWARD_RIGHT);
    while (!UART1_is_tx_ready()) continue;
    UART1_Write(speed + differential); 
}

void Right_Turn(char speed, char differential)
{
    //  Add code
   while (!UART1_is_tx_ready()) continue;
   UART1_Write(FORWARD_LEFT);
   while (!UART1_is_tx_ready()) continue;
   UART1_Write(speed + differential);
   while (!UART1_is_tx_ready()) continue;
   UART1_Write(FORWARD_RIGHT);
   while (!UART1_is_tx_ready()) continue; 
   UART1_Write(speed);
}

void Stop (void)
{
    Forward(0);
}

/*
 * 
 * 
 * 
 * 
 */


void Turn_PID_ON (void)
{
    //  Start robot moving using 3pi PID function
        //  Speed = 30; a = 1; b = 20; c = 3; d = 2
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(0xBB); // Code to start the PID protocol
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(50);
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(1);
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(20);
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(3);
    while(!UART1_is_tx_ready()) continue;
    UART1_Write(2); 
}

void Turn_PID_OFF (void) 
{
     while(!UART1_is_tx_ready()) continue;
     UART1_Write(0xBC);
}

void Spin_Right (char speed)
{
   while (!UART1_is_tx_ready()) continue;
   UART1_Write(BACKWARD_RIGHT);
   while (!UART1_is_tx_ready()) continue;
   UART1_Write(speed);
   while (!UART1_is_tx_ready()) continue;
   UART1_Write(FORWARD_LEFT);
   while (!UART1_is_tx_ready()) continue; 
   UART1_Write(speed);
}

void Spin_Left (char speed)
{
   while (!UART1_is_tx_ready()) continue;
   UART1_Write(FORWARD_RIGHT);
   while (!UART1_is_tx_ready()) continue;
   UART1_Write(speed);
   while (!UART1_is_tx_ready()) continue;
   UART1_Write(BACKWARD_LEFT);
   while (!UART1_is_tx_ready()) continue; 
   UART1_Write(speed);
}
    
void Full_Rotation_30 (void)
{
   TMR0_Initialize(T0_16_BIT & T0_POST_1_1, T0_PRE_1_128 & T0_SYNC & T0_SOURCE_INT);
   TMR0_Write16BitTimer(28021);
   TMR0_StartTimer();
   
   while (!UART1_is_tx_ready()) continue;
   UART1_Write(FORWARD_RIGHT);
   while (!UART1_is_tx_ready()) continue;
   UART1_Write(30);
   while (!UART1_is_tx_ready()) continue;
   UART1_Write(BACKWARD_LEFT);
   while (!UART1_is_tx_ready()) continue; 
   UART1_Write(30);
  while(1)
   {
     if (TMR0_HasOverflowOccured())
     {
       TMR0_StopTimer();
       Stop();
       break;  
     }
   }
}

unsigned int Get_sum (void)
{
    unsigned int* value;
    value = Read_Calibrated_Sensors();
    return value[1] + value[2]+value[3];
}

unsigned int Get_Total_sum (void)
{
    unsigned int* value;
    value = Read_Calibrated_Sensors();
    return value [0] + value[1] + value[2] + value[3] + value[4];
}

void Go_1cm (void)
{
   TMR0IF = 0;
   TMR0_Initialize(T0_16_BIT & T0_POST_1_1, T0_PRE_1_64 & T0_SYNC & T0_SOURCE_INT);
   TMR0_Write16BitTimer(37500);
   Forward(10);
   TMR0_StartTimer();
   
  while(1)
   {
     if (TMR0_HasOverflowOccured())
     {
       Stop();
       return;
     }
  }
}

void Landing_Pad(void)
{
    unsigned int* sensor_value = Read_Calibrated_Sensors();
    unsigned int sum = sensor_value[0]+sensor_value[1]+sensor_value[3];
    unsigned int total_sum = sensor_value[0]+sensor_value[1]+sensor_value[2]+sensor_value[3]+sensor_value[4]; 
    unsigned int outside_sum=sensor_value[0]+ sensor_value[4];   

    for (int i = 0; i < 5; i++)
    {
         Go_1cm();
        sensor_value = Read_Calibrated_Sensors();
        total_sum = sensor_value[0]+sensor_value[1]+sensor_value[2]+sensor_value[3]+sensor_value[4]; 
        outside_sum = sensor_value[0]+sensor_value[4];
        sum= sensor_value[1]+sensor_value[2]+sensor_value[3];
        if(outside_sum<500 && sensor_value[2]>200)
        {
            Turn_PID_ON();
            return;
        }
    }
    
    while(1)
    {
        sensor_value = Read_Calibrated_Sensors();
        total_sum = sensor_value[0]+sensor_value[1]+sensor_value[2]+sensor_value[3]+sensor_value[4];
    
    if(sensor_value[0] < 100 && sensor_value[4] < 100)
    {
        Turn_PID_ON();
        return;
    }
    
    else if (total_sum == 5000)
    {
        Stop();
    }
    }
}

void Correct_Path_To_Right(void)
{
    unsigned int* sensor_values;
    
    while (1)
    {
        Spin_Right(20);
        sensor_values = Read_Calibrated_Sensors();
        if (sensor_values[2] > 500)
            return;
    }
}

void Correct_Path_To_Left(void)
{
    unsigned int* sensor_values;
    
    while (1)
    {
        Spin_Left(20);
        sensor_values = Read_Calibrated_Sensors();
        if (sensor_values[2] > 500)
            return;
    }
}

void Gap(void)
{
    unsigned int* sensor_value;
    unsigned int sum;
   
    TMR0_Initialize(T0_16_BIT & T0_POST_1_1, T0_PRE_1_512 & T0_SOURCE_INT & T0_SYNC);
    TMR0_Write16BitTimer(54000);
    
    TMR0IF = 0;
    TMR0_StartTimer();
    
    //while(1)
    while(TMR0IF == 0)
    {
        Forward(30);
        sensor_value = Read_Calibrated_Sensors();
        sum = sensor_value[1]+sensor_value[2]+sensor_value[3];
        
        if (sum > 300 && sensor_value[4] < 100 && sensor_value[0] < 100)
        {
        return;
        }
    }
   
    while (TMR0IF == 1)
        {
            //while(1)
            //{
               Backward(30);
                sensor_value = Read_Calibrated_Sensors();
                sum = sensor_value[1]+sensor_value[2]+sensor_value[3];
                
                if (sum > 500 || sensor_value[4] > 200 || sensor_value[0] > 200 || sensor_value[2] > 200)
                {
               
                  Correct_Path_To_Left();
                   return;
                }
            //}    
        }
    
}
/*  END FILE */