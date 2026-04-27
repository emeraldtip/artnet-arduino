# Artnet-Arduino
This project consists of 2 scripts, which allow you to grab all values from an artnet universe and shove em into an arduino to convert them to DMX
- server.py grabs the artnet data and turns it into serial data with 2 sync bytes, dmx data and a shrimple crc
- arduino-dmxer grabs all those values and uses dmxsimple to shove it through a MAX485 and into an XLR plug

Pretty simple and chill stuff, just wanted my crappy CH340 arduino knockoff to be able to do DMX.
Probably would be faster to just send straight DMX down the CH340 and wire it into the MAX485 but oh well.
