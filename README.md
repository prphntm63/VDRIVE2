VDRIVE2
=======

An arduino library for basic commanding of the FTDI Vdrive2 module through UART serial

This library was made for use with an arudino board with multiple serial IO. 
The library communicates with the VDRIVE through Serial1 and with the Arduino environment
(i.e. the Serial Monitor) through Serial0.

I have been using this with an Arduino DUE, but a Mega should work right out of the box
as well. However, the source code can easily be modified to accomodate arduinos with only
a single serial IO.


## Usage
Functions as included in current release:

- `VDRIVE2 instance(baudrate, CTS pin, CTR pin)` - Creates an instance of the VDRIVE2

- `instance.Initialize()` - Initializes the instance. Should be run in setup.

- `instance.OpenFile("FILENAME.EXT", datetime, IterInfo)` - Opens a file for writing. 
The filename must be a string no longer than 8 characters with a 3 character extension. 
Datetime is [currently] a 2-byte constant (see example for more info on how to utilize it). 
IterInfo is a boolean that allows the VDRIVE's responses to commands to be displayed to the Serial Monitor.

- `instance.WriteFileData(DATA, columns, IterInfo)` - Writes an array to a new line the open file
DATA must be a double* array with the number of elements EQUAL TO the columns argument.
columns is an integer with the number of columns of data that will be written to the file.
IterInfo is a boolean that allows the VDRIVE's responses to commands to be displayed to the Serial Monitor.

- `instance.WriteFileString("String to Write", IterInfo)` - Writes the specified string to a new line in the open file
"String to Write" is the string that will be written.
IterInfo is a boolean that allows the VDRIVE's responses to commands to be displayed to the Serial Monitor.

- `instance.CloseFile("FILENAME.EXT", IterInfo)` - Closes the specified currently open file
The filename must be a string no longer than 8 characters with a 3 character extension.
The file must already be open (or else the VDRIVE will throw an error)
The filename must be a string no longer than 8 characters with a 3 character extension.

- `instance.QueryDisk()` - Returns a boolean whether or not a disk has been inserted
WARNING!! AS OF NOW THIS WILL ALSO RETURN TRUE IF THE VDRIVE UNIT IS NOT RESPONDING OR POWERED UP!!

- `instance.ViewStatus()` - Prints the most recent outputs from the VDRIVE to the serial monitor.
WARNING!! THIS PULLS DATA FROM THE SERIAL BUFFER. IT WILL PRINT ALL DATA, BE IT NEW OR OLD, FROM VDRIVE BUFFER


## Contact
Questions or ideas for code improvement can be sent to matt@westwick.dev
