from python_artnet import python_artnet as Artnet
import serial

port = serial.Serial("COM4",115200)

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
artNet.close()