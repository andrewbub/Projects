#!/afs/nd.edu/user14/csesoft/2017-fall/anaconda3/bin/python3.6
# -*- coding: UTF-8 -*-
# Andrew Bub, Molly Pierce
# Python 
# PORT NUMBER = 60800

import sys
import zmq
import time

port = "60800"
studentMachine = "student00.cse.nd.edu"
if len(sys.argv) > 1:
	studentMachine = sys.argv[1]
print ("Attempting to connect to ", studentMachine, " on port ", port, "...")
context = zmq.Context();
socket = context.socket(zmq.REQ) # set up socket as req
socket.connect("tcp://localhost:%s" % port)
print ("Connected.")
print("")
print("Welcome to irish.")

while True:
	# run first command
	command = sys.stdin.readline().strip(); 
	socket.send_string(command);
	# get the reply
	message = socket.recv()
	message = message.decode("utf-8") #for output
	print (message); 
	time.sleep(3);
