/*
VDRIVE2 Arduino Library Example Sketch

For use with an Arudino Mega or Due with the VDRIVE
attached to Serial1 and Serial0 going to the Serial
monitor in the Arduino environment.
*/

#include <VDRIVE2.h>  //Include the library

//Create an instance of the class
//CTS on pin 11, CTR on pin 10, 9600 baud
VDRIVE2 vdrive(9600, 11, 10);  

boolean feedback = true;  
/*Request feedback/confirmation through the Serial 
Monitor from the drive during read/write cycles 
(if FALSE the feedback data will not be displayed)
*/

byte datetime[] = {B11100001, B10100001};
/*  Should be 1/1/2013
 Time Bytes - NOTE: to use VDRIVE2::OpenFile() 
 must be modified to take 4 values intstead of 2
   Second = bits 0-4   int 0-29   seconds/2
   Minute = bits 5-10  int 0-59
   Hours =  bits 11-15 int 0-23
 Date Bytes
   Days =   bits 0-4   int 1-31    
   Months = bits 5-8   int 1-12    
   Years =  bits 9-15  int 0-127   0=1980, 127=2107
*/

//Make a filename
String filename = "TestFile.txt";

//Create an array to keep our data in
const int columns = 5;
double TestData[columns];

int i = 0; //Intial data "seed"


void setup() {
  pinMode(12, INPUT); //Button Pin input (normally HIGH)
  
  //Intialize the Vdrive2
  vdrive.Initialize();
}

void loop() {
  //Query the drive to see if there is a disk in it
  boolean DiskInserted = vdrive.QueryDisk();
  
  if ((digitalRead(12) == LOW)&&(DiskInserted)) {

    TestData[0] = i;    //Make some data
    TestData[1] = 2*i;  //Make some more data
    TestData[2] = 3*i;  //Continue making data
    TestData[3] = 4*i;  //This is getting old...
    TestData[4] = 5*i;  //Okay that's enough

    //Open the file for writing
    Serial.println("Opening File..");
    vdrive.OpenFile(filename, datetime, feedback);

    if (i == 0) {
      //Write a header at the beginning of the file 
      //but only if this is the first write (i == 0)
      Serial.println("Creating Headers...");
      vdrive.WriteFileString("N, N*2, N*3, N*4, N*5, ", feedback);
    }

    //Writes the data columns to the file (with 6 digit 
    //precision...this can be changed in the VDRIVE2.cpp file
    //NOTE: TestData MUST BE A DOUBLE PRECISION ARRAY 
    //with NUMBER OF ELEMENTS EQUAL TO COLUMNS! 
    Serial.println("Writing Data...");
    vdrive.WriteFileData(TestData, columns, feedback);

    //Reallocates the USB memory to include newly written data 
    //(i.e. permanently stores the newly written data)
    Serial.println("Closing File...");
    vdrive.CloseFile(filename, feedback);

    i++;  //increase the start integer
    delay(500);  //wait a bit
  }

  //Check the status of the drive (this will write to the serial
  //monitor whenever a disk is inserted or removed; it will also
  //inform aobut device upgrades on the drive (if available)
  vdrive.ViewStatus();
}
