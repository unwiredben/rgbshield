RGB LED Shield for Arduino
==========================

The various folders are Arduino sketches that work with the RGB LED Shield.

In order to build them, you need to unpack the TLC5490_r014_2.zip file
from this repo into your Arduino libraries folder.  Also, change the tlc_config.h
file to list NUM_TLCS as 3 instead of 1 or you'll get a blue/green color splash.

That ZIP comes from <http://code.google.com/p/tlc5940arduino/>.

All source files are under [the MIT License](http://www.opensource.org/licenses/MIT).  

Board design files are under
[Creative Commons-SA 3.0 US license](http://creativecommons.org/licenses/by-sa/3.0/us/).