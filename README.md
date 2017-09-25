# SDLJoyPad
![alt tag](http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/Demos/JoyPad.png)

This demo requires SDL 2.0 and a wireless xbox controller. Under the mac you can install this driver. Under linux you may have to install the xpad kernel driver

So far it has not been tested under windows and the button mappings may be different.

Note that this .pro file contains the calls to add the output of sdl2-config to the build using

`QMAKE_CXXFLAGS+=$$system(sdl2-config  --cflags)`

`message(output from sdl2-config --cflags added to CXXFLAGS= $$QMAKE_CXXFLAGS)`

`LIBS+=$$system(sdl2-config  --libs)`

`message(output from sdl2-config --libs added to LIB=$$LIBS)`

This is different from the Qt versions of the .pro file
