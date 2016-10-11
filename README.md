[![alt text](images/Logo.png "Makeblock Logo") ](https://www.Makeblock.cc)

The package consists of the software(Arduino firmware and GRemote), structure assembly instruction and program instruction.
###My Unofficial Calibration Procedure

This procedure will use this repository but the only Makeblock software will be in the `XY-Plotter-2.0/software/GCodeParser`

1. Download and install/unzip the following pieces of software

  * [The Arduino software for programming the plotter main board](http://arduino.cc/en/Main/Software)

  * [This repository](https://github.com/charlieb/XY-Plotter-2.0/archive/master.zip)
  
  * [The Universal GCode Sender](http://winder.github.io/ugs_website/)
  
  * [This software requires Java 7+](https://www.java.com/en/download/)

1. Make sure that the main power to the board is either unplugged or the switch is turned off

   The Arduino board will draw enough power from the USB connection to allow it to be flashed (and drive the pen servo). As soon as the board is flashed it will start to drive the big stepper motors to try and find it's zero position as part of the initialization. It's better if the moment this happens is controlled rather than just as soon as the flash finishes.
   
1. Flash the main board with the GCodeParser using the arduino software
  1. Launch the Arduino software
  1. Hit File->Open and open XY-Plotter-2.0-master/software/GCodeParser/GCodeParser.ino from the location where you unzipped this repository's master.zip.
  1. Connect up the main board to your computer.
  1. Select the Uno board: Tools->Board->Arduino Uno
  1. Select the correct port: Tools->Port->*Your port*
  1. Install the two needed libraries (only needed the first time, if at all):
    * Sketch->Import Library->Software Serial
    * Sketch->Import Library->Servo
  1. Hit the arrow button at the top left to do the upload. If this fails ask on the forums
1. Figure out which limit switches correspond to which movement axes.
  A word about initialization: The GCodeParser firmware's init sequence consists of finding the zero position for each axis. It does this by moving slowly towards zero on one axis until it hits the limit switch. Then it steps backwards until the switch releases. This procedure is then repeated for the other axis. We're going to use this procedure to figure out if the limit switches are wired correctly.
  1. Manually move the carriage with the pen to the middle of the drawing area so when it starts to move there's plenty of time to react. The carriage should move fairly freely, if it doesn't then check that the power switch on the main board is off.
  1. Switch on the power on the main board.
  1. If nothing happens hit the Arduino's reset pushbutton on the side of the main board. If this still fails check that the Arduino flash succeeded then ask on the forums.
  1. One of the steppers will start to move and the carriage will move in a direction.
  1. Look at which limit switch it is moving towards hit the switch manually.
    *hint:* it should be the one in the corner of the frame near the stepper motor or the one on the carridge nearest the stepper side.
  1. If that stepper stops and the other one starts then that limit switch is wired correctly.
  1. If it keeps going in the same direction start to hit the other limit switches until it does stop. Remember which one stopped the motion.
  1. The carridge will now start to move in the other axis.
  1. Figure out which limit switch it will be going for *next* and hit it.
  1. If that stepper stops then that limit switch is wired correctly.
    The initialization procedure is now complete but only two limit switches have been tested
1. Fix the limit switch wiring - if necessary.
  1. From the above procedure there should be two pieces of information for each axis: the limit switch that should have stopped the motion and the one that did stop the motion.
  1. To fix the wiring, follow both of the connections all the way back to the main board and swap them.
  
    
###Brief Procedure

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

###How to DIY

If you want change the source code, you could find it in GRemotFull/source/GRemote.pde.

1. Download and install Processing-2.1.2. http://processing.org/
2. Install the Processing library, controlP5 -- copy the whole folder to C:\Users\xxx\Documents\Processing\libraries
3. Open the GRemote.pde by Processing, DIY the code and click the “run” button to test it.

[![alt text](images/XY Plotter 2.0.jpg "Makeblock XY Plotter 2.0")](http://www.makeblock.cc/xy-plotter-robot-kit-2-0/)
