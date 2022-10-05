from contextlib import aclosing
import os
import serial
import sys
import time

ser = serial.Serial()

ser.timeout=1
ser.port='COM4'
ser.baudrate=115200
ser.open()
ser.flushOutput()
ser.flushInput()

time.sleep(1);

ser.flushOutput()
ser.flushInput()

time.sleep(1);

#  Handshake



ack_code = ser.read(1)

while(ack_code != b'S'):
    print(ack_code)
    ack_code = ser.read(1)

print( ack_code)
print("hello")
ser.write(b'O')
time.sleep(.01)
ser.write(b'K')
time.sleep(0.01)

while((ack_code != b'T') and (ack_code != b'F')):
    print(ack_code)
    ack_code = ser.read(1)

print( ack_code)
    



