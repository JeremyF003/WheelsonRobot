/*****
    Pololu 3pi
    Slave program header file
 
    09-MAR-2021
*****/

#define READ_CALIBRATED_SENSORS 0x87
#define READ_BATTERY            0xB1
#define CALIBRATE               0xB4
#define AUTO_CALIBRATE          0xBA
#define CLEAR_LCD               0xB7
#define PRINT_LCD               0xB8
#define POSITION_LCD            0xB9
#define FORWARD_LEFT            0xC1
#define BACKWARD_LEFT           0xC2
#define FORWARD_RIGHT           0xC5
#define BACKWARD_RIGHT          0xC6

//  Calibrates sensors using a 3pi algorithm.
//  Returns a 2-byte value for each of the five sensors - total of 10 bytes returned.
unsigned int* Calibrate_Sensors(void);


//  Auto-calibration swivels the robot across a black line to calibrate using a 3pi algorithm
//  Calibration is complete when robot returns the 'c' character
void Auto_Calibrate(void);


//  Reads each of the sensor values and returns a 2-byte value for each of the 
//  five sensors - total of 10 bytes are returned.
unsigned int* Read_Calibrated_Sensors(void);


//  Returns battery voltage in mV
unsigned int Read_Battery_Voltage(void);


//  Print a string of up to 8-characters to the LCD screen
//  First byte transmitted is for the length of the string.
//  Following bytes are for the actual string
void LCD_Print(char *str, char length);


//  Print a single character to the LCD screen
void LCD_PrintCharacter(char byte);


//  Clear LCD screen
void LCD_Clear(void);


//  Set the cursor position on the LCD screen by sending two bytes after
//  the command code - x position (column number, 0-7), then y position (row
//  number, 0 or 1.
void LCD_Position(char x, char y);


//  Both wheels are set to spin forwards at a speed, 0 (stop) to 127 (full speed)
void Forward(char speed);


//  Both wheels are set to spin backwards at a speed, 0 (stop) to 127 (full speed)
void Backward(char speed);


//  Wheels move at different speeds to turn the robot
//  Right wheel turns at speed + differential - limit speed + differential < 127
//  Left wheel turns at speed - differential
void Left_Turn(char speed, char differential);


//  Wheels move at different speeds to turn the robot
//  Left wheel turns at speed + differential - limit speed + differential < 127
//  Right wheel turns at speed - differential
void Right_Turn(char speed, char differential);


//  Both wheels move at speed zero
void Stop (void);

/*Personalized Functions
 * 
 * Created on  27/03/2024
 *
 * 
 */


// Turn on PID default function
void Turn_PID_ON (void);

//Turn off PID 
void Turn_PID_OFF (void);

//Spin function for right turn
void Spin_Right (char speed);

//Spin function for turning left
void Spin_Left (char speed);

//Rotate 180 degrees at 30cm/s
void Full_Rotation_30 (void);

//Get the sum of the main 3 sensors (0,1 and 3)
unsigned int Get_sum (void);

//Get the total sum of the sensors
unsigned int Get_Total_sum(void);

void Landing_Pad(void);

void Correct_Path_To_Right(void);

void Correct_Path_To_Left(void);

void Go_1cm (void);

void Gap(void);

/*  END FILE    */
