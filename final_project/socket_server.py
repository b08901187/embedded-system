#!/usr/bin/env python3
import socket
import json
import time
import random


HOST = '192.168.43.158' # Standard loopback interface address 
PORT = 7080 # Port to listen on (use ports > 1023)
print(socket.gethostbyname(socket.gethostname()))
path = 'save.txt'


while (True):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((HOST, PORT))
    s.listen()

    print("The Auto tea maker server is running..")
    conn, addr = s.accept()

    for i in range(2):

        print('Connected by', addr)
        
        message = conn.recv(1024).decode('utf-8')
        print(message)

        temp = input()
        conn.send(temp.encode('utf-8'))

        
