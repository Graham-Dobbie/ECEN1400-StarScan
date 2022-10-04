import os
import serial
import sys
import time

ser = serial.Serial()

ser.timeout=1
ser.port='COM6'
ser.baudrate=115200
ser.open()
ser.flushOutput()
ser.flushInput()

time.sleep(1);

ser.flushOutput()
ser.flushInput()

time.sleep(1);

#  Handshake

ser.write(b'O')
time.sleep(.1);
ser.write(b'K')
time.sleep(.1);

ack_code = ser.read(1)

while(len(ack_code) <= 0):
    ack_code = ser.read(1)

print( ack_code)
    



