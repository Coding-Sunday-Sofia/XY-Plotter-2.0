### Note from shimpe:
My makeblock plotter kit shipped with an arduino UNO based board instead of arduino Leonardo.
Beware to choose arduino UNO when uploading the firmware from the arduino environment.

In practice this also means that the pin assignments used by the arduino are different, so the firmware needs to be adapted for this. I got my arduino uno based plotter fully working with the code modifications in this repository.

Because of this, changes were also needed in electrical connections:

1. connect cable from port 7 to top of pen holder
2. connect cable from port 6 (NOT 8!!!) to bottom pen holder (which itself is connected to the left and right limit switches: upper connector to the right limit switch, lower connector to the left limit switch)
3. connect furthest limit switch (top right corner) to the LEFT side of the board that connects with port 3
4. connect limit switch closest to the motors to the RIGHT side of the board that connects with port 3

This repo also fixes an important bug that sometimes causes spurious circles or wrong paths to be drawn out of nowhere.

Pull requests have been made to the official repository, but it seems to be no longer maintained.
Which is a pity because the plotter results can be stunning!

In GRemoteFull, 
 1. I've set X PPM, Y PPM to 350 to get an exact correspondence between measures in inkscape and measures on paper.
 2. Settings: set up correct pin assignments:
  * X DIR = 11; Y DIR = 3; Z DIR = -1 (not used); X PPM = 350
  * X STEP = 10; Y STEP = 9; Z STEP = 15; Y PPM = 350
  * X MIN = 16; YMIN = 13; Z MIN = -1 (not used); Z PPM = 350
  * Z MAX = 17; Y MAX = 12; ZMAX = -1 (not used)

[![alt text](images/Logo.png "Makeblock Logo") ](https://www.Makeblock.cc)

The package consists of the software(Arduino firmware and GRemote), structure assembly instruction and program instruction.

### Brief Procedure

1. Download and install Arduino-1.0.5，http://arduino.cc/en/Main/Software

2. Download the software package and decompress it，https://github.com/Makeblock-official/XY-Plotter-2.0/archive/master.zip

3. Connect Me baseboard to computer with micro USB cable.

4. Open GCodepraser->GCodeParser.ino by Arduino IDE. Click Tools->Serial Ports, choose COM XX (Not COM1 and COM2). Click Tools->Boards, choose Arduino Leonardo. At last, click "upload" button on the right-top corner.
                                                                                  [![alt text](images/Upload.png "Upload program to Me Baseboard")](https://raw.githubusercontent.com/Makeblock-official/XY-Plotter-2.0/master/images/Upload.png)

5. Close Arduino IDE, open GRemoteFull->GRemote.bat. 

6. Set the COM port, then GRemote will show you the UI as follows. That all for this part.
[![alt text](images/GRemote.jpg "Set the COM port")](https://raw.githubusercontent.com/Makeblock-official/XY-Plotter-2.0/master/images/GRemote.jpg)

7. Now, you could control the XY-Plotter 2.0 by mouse and keyboard. And, you can also run it with Gcode. You could generate Gcode file by another software (dxf2gcode(https://code.google.com/p/dxf2gcode/) or any other capable). You should save the Gcode file with .cnc and open it by GRemote.

For more details, please refer to the software instruction.

### How to DIY

If you want change the source code, you could find it in GRemotFull/source/GRemote.pde.

1. Download and install Processing-2.1.2. http://processing.org/
2. Install the Processing library, controlP5 -- copy the whole folder to C:\Users\xxx\Documents\Processing\libraries
3. Open the GRemote.pde by Processing, DIY the code and click the “run” button to test it.

[![alt text](images/XY Plotter 2.0.jpg "Makeblock XY Plotter 2.0")](http://www.makeblock.cc/xy-plotter-robot-kit-2-0/)

### Learn more from Makeblock official website: www.makeblock.com
