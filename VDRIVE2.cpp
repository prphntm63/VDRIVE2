#include "Arduino.h"
#include "VDRIVE2.h"

VDRIVE2::VDRIVE2(int baudrate, int CTS, int CTR) {
  _CTS = CTS;
	_CTR = CTR;
	_baudrate = baudrate;
}

void VDRIVE2::Initialize() {
  byte cr = 0x0d;
  pinMode(_CTS, OUTPUT);
  pinMode(_CTR, INPUT);
  digitalWrite(_CTS, LOW);
  
  Serial.begin(9600);
  Serial1.begin(9600);
   
  delay(20);
  digitalWrite(_CTS, HIGH);
  Serial1.print("ECS");
  Serial1.write(cr);

  delay(20);
  Serial1.print("IPA");
  Serial1.write(cr);
  delay(20);
//  digitalWrite(_CTS, LOW);  
  while (Serial1.available() > 0) {
    Serial1.read();
  }
  delay(20);
//  digitalWrite(_CTS, HIGH);
  
/*   if (_baudrate != 9600) {
	byte a;
	byte b;
	byte c;
	switch (_baudrate) {
		case 300:
			 a = 0x10;
			 b = 0x27;
			 c = 0x00;
		break;
		case 600:
			 a = 0x88;
			 b = 0x13;
			 c = 0x00;
		break;
		case 1200:
			 a = 0xc4;
			 b = 0x09;
			 c = 0x00;
		break;
		case 2400:
			 a = 0xe2;
			 b = 0x04;
			 c = 0x00;
		break;
		case 4800:
			 a = 0x71;
			 b = 0x02;
			 c = 0x00;
		break;
		case 9600:
			 a = 0x38;
			 b = 0x41;
			 c = 0x00;
		break;
		case 19200:
			 a = 0x9c;
			 b = 0x80;
			 c = 0x00;
		break;
		case 38400:
			 a = 0x4e;
			 b = 0xc0;
			 c = 0x00;
		break;
		case 57600:
			 a = 0x34;
			 b = 0xc0;
			 c = 0x00;
		break;
		case 115200:
			 a = 0x1a;
			 b = 0x00;
			 c = 0x00;
		break;
	}
	
	Serial1.print("SBD ");
	Serial1.write(a);
	Serial1.write(b);
	Serial1.write(c);
	Serial1.write(cr);
	
	Serial1.begin(_baudrate);
	delay(50);
	
  } */
}

void VDRIVE2::OpenFile(String FILENAME, byte* DATETIME, bool n) {
    byte cr = 0x0d;
    char filename[FILENAME.length()+1];
    FILENAME.toCharArray(filename, FILENAME.length()+1);
    Serial1.print("OPW ");
    Serial1.print(filename);
    Serial1.print(" ");
    Serial1.write(DATETIME[0]);
    Serial1.write(DATETIME[1]);
    Serial1.write(cr);
    
    digitalWrite(_CTS, LOW);
    while (Serial1.available() > 0) {
		if (n == true) {
			char a = Serial1.read();
			if (a == 0x0d) {
				Serial.println();
			}
			else {
				Serial.write(a);
			}
		}
		else {
			Serial1.read();
		}
	}
    delay(10);
    digitalWrite(_CTS, HIGH);
}

void VDRIVE2::WriteFileData(double* DATA, int columns, bool n) { 
    byte cr = 0x0d;
    int i=0;
    String WriteVal;
    while (i < columns) {  //4=size of int
      String DATA2 = printDouble( DATA[i], 6);
      WriteVal += DATA2;
      WriteVal += ", ";
      i++;
    }
    
    char data[WriteVal.length()+1];
    WriteVal.toCharArray(data, WriteVal.length()+1);
    Serial1.print("WRF ");
    int Size = WriteVal.length()+2;
    Serial1.print(Size, DEC);
    Serial1.write(cr);
    i = 0;
    while (i < WriteVal.length()+1) {
      Serial1.write(data[i]);
      i++;
    }
    Serial1.write(0x0a); //LineFeed
    Serial1.write(cr);
    delay(10);
    
    digitalWrite(_CTS, LOW);
    while (Serial1.available() > 0) {
		if (n == true) {
			char a = Serial1.read();
			if (a == 0x0d) {
				Serial.println();
			}
			else {
				Serial.write(a);
			}
		}
		else {
			Serial1.read();
		}
	}
    delay(10);
    digitalWrite(_CTS, HIGH);
}


void VDRIVE2::WriteFileString(String DATA, bool n) {
    byte cr = 0x0d;
    char data[DATA.length()+1];
    DATA.toCharArray(data, DATA.length()+1);
    Serial1.print("WRF ");
    int Size = DATA.length()+2;
    Serial1.print(Size, DEC);
    Serial1.write(cr);
    int i = 0;
    while (i < DATA.length()+1) {
      Serial1.write(data[i]);
      i++;
    }
    Serial1.write(0x0a); //LineFeed
    Serial1.write(cr);
    delay(10);
    
    digitalWrite(_CTS, LOW);
    while (Serial1.available() > 0) {
		if (n == true) {
			char a = Serial1.read();
			if (a == 0x0d) {
				Serial.println();
			}
			else {
				Serial.write(a);
			}
		}
		else {
			Serial1.read();
		}
	}
    delay(10);
    digitalWrite(_CTS, HIGH);
}


void VDRIVE2::CloseFile(String FILENAME, bool n) {
    byte cr = 0x0d;
    char filename[FILENAME.length()+1];
    FILENAME.toCharArray(filename, FILENAME.length()+1);
    Serial1.print("CLF ");
    Serial1.print(filename);
    Serial1.write(cr);
	
    digitalWrite(_CTS, LOW);
    while (Serial1.available() > 0) {
		if (n == true) {
			char a = Serial1.read();
			if (a == 0x0d) {
				Serial.println();
			}
			else {
				Serial.write(a);
			}
		}
		else {
			Serial1.read();
		}
	}
    delay(10);
    digitalWrite(_CTS, HIGH);
}


bool VDRIVE2::QueryDisk() {
    byte cr = 0x0d;
    String disk;
    Serial1.write(cr);
    digitalWrite(_CTS, LOW);
    delay(10);
    while (Serial1.available() > 0) {
      char a = Serial1.read();
      if (a == 0x0d) {}
      else {
        disk += a;
        delay(5);
      }
    }
    digitalWrite(_CTS, HIGH);
    
    if (disk == "No Disk") {
      return false;
    }
    else {
      return true;
    }
}


void VDRIVE2::ViewStatus() {
  digitalWrite(11, LOW);
  while (Serial1.available() > 0) {
    char a = Serial1.read();
    if (a == 0x0d) {
      Serial.println();
    }
    else {
      Serial.write(a);
    }
  }
  delay(10);
  digitalWrite(11, HIGH);
}


String VDRIVE2::printDouble( double val, byte precision){
  // prints val with number of decimal places determine by precision
  // precision is a number from 0 to 6 indicating the desired decimial places
  // example: lcdPrintDouble( 3.1415, 2); // prints 3.14 (two decimal places)
  String DATA;
  
  if(val < 0.0){
    DATA += "-";
    val = -val;
  }

  DATA += (int(val));  //prints the int part
  if( precision > 0) {
    DATA += "."; // print the decimal point
    unsigned long frac;
    unsigned long mult = 1;
    byte padding = precision -1;
    while(precision--)
  mult *=10;
 
    if(val >= 0)
 frac = (val - int(val)) * mult;
    else
 frac = (int(val)- val ) * mult;
    unsigned long frac1 = frac;
    while( frac1 /= 10 )
 padding--;
    while(  padding--)
 DATA += "0";
    DATA += frac ;
  }
  
  return DATA;
}
