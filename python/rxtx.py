#!/usr/bin/python

import serial
import time
import numpy as np
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(17,GPIO.OUT)


ser=serial.Serial(
    port="/dev/ttyAMA0",
    baudrate=1000000,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=0.005
    )
counter=0


#Move 0xFF,0xFF,0x2B,0x05,0x03,0x1E,0xFF,0x05


#byte1 = bytes([0xFF,0xFF,0x02,0x03,0x04,0x19,0x01,0xE0])

li=[0xFF,0xFF,0x2B,0x05,0x03,0x1E,0xC8,0x00]

li2=[0xFF,0xFF,0x2B,0x05,0x03,0x1E,0xFF,0x01]

crc = sum(li[2:])
low1=crc&255
chksum=255-low1
print(chksum)
li.append(chksum)


crc2 = sum(li2[2:])
low2=crc2&255
chksum2=255-low2
li2.append(chksum2)
print(chksum2)

byte2 = bytearray(li)
byte3 = bytearray(li2)
f = open("demo.txt", "a")
s = ''.join(map(chr , byte2))
f.write(s)
f.close()
while 1:
    print(byte2)
    GPIO.output(17,True)
    a = ser.write(byte2)
    print(a)
    GPIO.output(17,False)
    x=ser.readline()
    print (x)
    time.sleep(0.5)
    GPIO.output(17,True)
    a = ser.write(byte3)
    print(a)
    GPIO.output(17,False)
    x=ser.readline()
    print (x)
    time.sleep(0.5)

