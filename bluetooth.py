import serial
import time
import os
import time 
from time import sleep
from datetime import datetime
port = serial.Serial("/dev/rfcomm0", baudrate=9600)

# reading and writing data from and to arduino serially.                                      
# rfcomm0 -> this could be different

while True:
	print "DIGITAL LOGIC -- > RECEIVED..."
	port.write(str(3))
	rcv = port.readline()
	dataAsString =(rcv)
	if rcv:
	   print(rcv)
	fb = open('/home/pi/test2','a')
	fb.write(dataAsString) 
	fb.write('\n')
fb.close()
	
