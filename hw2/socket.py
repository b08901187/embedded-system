#!/usr/bin/env python3
import socket

import json
import time
import random

import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt

HOST = '192.168.109.158' # Standard loopback interface address 
PORT = 5420 # Port to listen on (use ports > 1023)
#print(socket.gethostbyname(socket.gethostname()))
path = 'save.txt'

data_num = 20
MAGNETO_x = np.ones(data_num)
MAGNETO_y = np.ones(data_num)
MAGNETO_z = np.ones(data_num)
GYRO_x = np.ones(data_num)
GYRO_y = np.ones(data_num)
GYRO_z = np.ones(data_num)
ACCELERO_x = np.ones(data_num)
ACCELERO_y = np.ones(data_num)
ACCELERO_z = np.ones(data_num)
num = np.ones(data_num)

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    conn, addr = s.accept()
    with conn:
        print('Connected by', addr)
        count = 0
        with open(path,'w',encoding='utf-8') as f:
           while count<60 :
              count += 1
              data = conn.recv(1024).decode('utf-8')
              f.write(data)
              f.write("\n")
              print('Received from socket server : ', data)



with open(path, 'r', encoding='utf-8') as shown:
    lines = shown.readlines()
    index = 0
    count = 0
    for i in lines:
        line = json.loads(i)

        if count == 0:
           MAGNETO_x[index] = line['MAGNETO_x']
           MAGNETO_y[index] = line['MAGNETO_y']
           MAGNETO_z[index] = line['MAGNETO_z']
           count = 1

        elif count == 1:
           GYRO_x[index] = line['GYRO_x']
           GYRO_y[index] = line['GYRO_y']
           GYRO_z[index] = line['GYRO_z']
           count = 2


        elif count == 2:
           ACCELERO_x[index] = line['ACCELERO_x']
           ACCELERO_y[index] = line['ACCELERO_y']
           ACCELERO_z[index] = line['ACCELERO_z']
           count = 0
           num[index] = line['s']
           index += 1

print(num)


fig1 = plt.figure()
ax = plt.axes()
ax.set_xlabel('time')
ax.set_ylabel('magneto')
plt.plot(num, MAGNETO_x)
plt.plot(num, MAGNETO_y)
plt.plot(num, MAGNETO_z)

fig1 = plt.figure()
ax = plt.axes()
ax.set_xlabel('time')
ax.set_ylabel('gyro')
plt.plot(num, GYRO_x)
plt.plot(num, GYRO_y)
plt.plot(num, GYRO_z)

fig1 = plt.figure()
ax = plt.axes()
ax.set_xlabel('time')
ax.set_ylabel('acceleration')
plt.plot(num, ACCELERO_x)
plt.plot(num, ACCELERO_y)
plt.plot(num, ACCELERO_z)

plt.show()


        
