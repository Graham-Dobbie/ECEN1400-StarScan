from contextlib import aclosing
import os
import serial
import sys
import time

ser = serial.Serial()

ser.timeout=1
ser.port='COM7'
ser.baudrate=115200
ser.open()

def send_handshake():
    ack_code = ser.read(1)

    while(ack_code != b'S'):
        # print(ack_code)
        ack_code = ser.read(1)

    # print( ack_code)
    print("Sending Handshake ...")
    ser.write(b'O')
    time.sleep(.01)
    ser.write(b'K')
    time.sleep(0.01)

    while((ack_code != b'T') and (ack_code != b'F')):
        # print(ack_code)
        ack_code = ser.read(1)

    print( "Acknowledged Handshake")
    print()

def send_packet(packet, timeout):
    pass


time.sleep(1);

ser.flushOutput()
ser.flushInput()

time.sleep(1);

#  Handshake





# path = input("Please input the .wav file you would like upload: ")
# dst = input("Now input the name of the file")

path = "tada.wav"


wav_file = open(path, 'rb')

raw_data = wav_file.read()

data_len = len(raw_data)





print()
    



