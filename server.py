from python_artnet import python_artnet as Artnet
import serial
import traceback
import struct

port = serial.Serial("COM4",153600)
#port = serial.Serial("/dev/ttyUSB0",153600)

artNet = Artnet.Artnet("0.0.0.0")

while True:
    try:
        #Getdata
        artNetBuffer = artNet.readBuffer()
        if artNetBuffer is not None:
            #Get universe 0
            artNetPacket = artNetBuffer[0]
            if artNetPacket.data is not None:
                dmxPacket = artNetPacket.data
                sequenceNo = artNetPacket.sequence
                port.write(bytearray([0xAA,0x69]))
                sum = 0
                port.write(struct.pack("<512H",*dmxPacket))
                for i in dmxPacket:
                #    port.write(bytearray(i))
                    sum+=i
                port.write(bytearray([sum&0xFF]))
    except KeyboardInterrupt:
        break
    except :
        print("Eroor")
        print(traceback.format_exc())
        