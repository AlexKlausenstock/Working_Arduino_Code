// lidar test setup
/*UART
Default baud rate
115200
*/
//https://github.com/benrugg/Arduino-Hex-Decimal-Conversion/blob/master/hex_dec.ino
//https://forum.arduino.cc/index.php?topic=288234.0
// serial commands list:
//https://www.arduino.cc/reference/en/language/functions/communication/serial/
//On Uno, Nano, Mini, and Mega, pins 0 and 1 are used for communication with the computer.

#include<SoftwareSerial.h>//header file of software serial port
//SoftwareSerial Serial1(1,2);
int dist;//actual distance measurements of LiDAR
int strength;//signal strength of LiDAR
int check;//save check value
int i;
int j = 0;
int uart[9];//save data measured by LiDAR
const int HEADER=0x59;//frame header of data package


void setup() {
  // put your setup code here, to run once:
  pinMode (13,OUTPUT);
  
Serial.begin(9600);
Serial1.begin(115200);// serial #RX/TX number. begin(baud)

}

void loop() {
  // put your main code here, to run repeatedly:
// send data only when you receive data:
while (j<100){
  
        if (Serial1.available()) {
                // read the incoming byte:
                //incomingByte = Serial.read(); what they said

                if(Serial1.read()==HEADER)//assess data package frame header 0x59
                { 
  uart[0]=HEADER;
if(Serial1.read()==HEADER)//assess data package frame header 0x59 {
uart[1]=HEADER;

//save data in array
for(i=2;i<9;i++){
uart[i]=Serial1.read();
} 
check=uart[0]+uart[1]+uart[2]+uart[3]+uart[4]+uart[5]+uart[6]+uart[7]; 

if(uart[8]==(check&0xff))//verify the received data as per protocol
{
dist=uart[2]+uart[3]*256;//calculate distance value 
strength=uart[4]+uart[5]*256;//calculate signal strength value 

}
}
}
j++;
}
while (Serial.available() > 0) {Serial.read();}

j=0;
if (strength>30){
  digitalWrite(13, HIGH);   
  delay(dist/2.5);                       
  digitalWrite(13, LOW);    
  delay(dist/2.5);   
}
if (strength<=30){
  digitalWrite(13,LOW);
  delay(2000);
  digitalWrite(13,HIGH);
  delay(2000);
}
//  takes multiple cycles to  pull data form serial
//  ask prof trevas about delay / wait timer for light to not interupt other functions like serial read stuff
  

//dist should be from 0-1200 (units in cm)
                // say what you got:
//                Serial.print("I received: ");
//                Serial.println(incomingByte, DEC);
Serial.print("Distance (cm): ");
Serial.println(dist);
}

// made into a function**********************************************************
//make sure to set up Serial communication Serial# (#= Tx/RX# NUMBER)
//Serial1.begin(115200);// serial #RX/TX number. begin(baud)
double readLaserRangeFinder(){
  
  // put your main code here, to run repeatedly:
// send data only when you receive data:
while (j<100){
  
        if (Serial1.available()) {
                // read the incoming byte:
                //incomingByte = Serial.read(); what they said
                if(Serial1.read()==HEADER)//assess data package frame header 0x59
                { 
  uart[0]=HEADER;
if(Serial1.read()==HEADER)//assess data package frame header 0x59 {
uart[1]=HEADER;

//save data in array
for(i=2;i<9;i++){
uart[i]=Serial1.read();
} 
check=uart[0]+uart[1]+uart[2]+uart[3]+uart[4]+uart[5]+uart[6]+uart[7]; 

if(uart[8]==(check&0xff))//verify the received data as per protocol
{
dist=uart[2]+uart[3]*256;//calculate distance value 
strength=uart[4]+uart[5]*256;//calculate signal strength value 

}
}
}
j++;
}
while (Serial.available() > 0) {Serial.read();}
j=0;
//  takes multiple cycles to  pull data form serial

//dist should be from 0-1200 (units in cm)
                // say what you got:
//                Serial.print("I received: ");
//                Serial.println(incomingByte, DEC);
Serial.print("Distance (cm): ");
Serial.println(dist);

return dist;
}
