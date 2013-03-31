#ifndef VDRIVE2_h
#define VDRIVE2_h

#include "Arduino.h"


class VDRIVE2
{
  public:
  VDRIVE2(int baudrate, int CTS, int CTR);
	void Initialize();
    void OpenFile(String FILENAME, byte* DATETIME, bool n);
	void CloseFile(String FILENAME, bool n);
	void WriteFileData(double* DATA, int columns, bool n);
	void WriteFileString(String DATA, bool n);
	bool QueryDisk();
	void ViewStatus();
  private:
    String printDouble( double val, byte precision);
	int _CTS;
	int _CTR;
	int _baudrate;
};

#endif
