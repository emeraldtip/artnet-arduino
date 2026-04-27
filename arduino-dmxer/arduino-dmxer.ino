#include <DmxSimple.h>

uint8_t buffer[1024]; //raw data

bool synced = false;
uint16_t index = 0;
uint8_t prevByte = 0;

void setup() {
    pinMode(13,OUTPUT);
    DmxSimple.usePin(3);
    DmxSimple.maxChannel(512); 
    Serial.begin(153600);
    Serial.println("Booting");
    digitalWrite(13,HIGH);
    delay(500);
    digitalWrite(13,LOW);
}

void loop() {
    while (Serial.available() > 0) {
        uint8_t b = Serial.read();

        //syncer
        if (!synced) {
            if (prevByte == 0xAA && b == 0x69) {
                synced = true;
                index = 0;
                digitalWrite(13,LOW);
            }
            prevByte = b;
            continue;
        }

        //dumper
        if (index < 1024) {
            buffer[index++] = b;
            continue;
        }

        //checksum
        uint8_t receivedChecksum = b;

        if (checkChecksum(buffer, 1024, receivedChecksum)) {
            onPacketReceived();
        } 

        synced = false;
        index = 0;
    }
}

bool checkChecksum(uint8_t *buf, uint16_t len, uint8_t checksum) {
    uint8_t sum = 0;
    for (uint16_t i = 0; i < len; i++) {
        sum += buf[i];
    }
    if (sum == checksum) {
        digitalWrite(13,HIGH);
    }
    return sum == checksum;
}


void onPacketReceived() {
    digitalWrite(13,LOW);
    analogWrite(13,buffer[0]);
	for (int i = 0; i<512; i++)
    {
	    DmxSimple.write(i+1,buffer[i*2]);
    }
}