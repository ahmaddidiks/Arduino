import serial
import time
import struct

PORT = "COM4"
BAUDRATE = 115200
HEADER = 255

ser = serial.Serial(port=PORT, baudrate=BAUDRATE, timeout=0.1)

while True:
  if ser.in_waiting:
    data_raw = ser.read(1)
    header= struct.unpack('B', data_raw)
    print(data_raw, header[0])
    
    if header[0] == HEADER:
      data_raw = ser.read(36)
      '''
      struct data:
      {
        uint16_t posTarget[6];    --> 6 * 2 byte
        float sensorFeedback[6];  --> 6 * 4 byte
      }
      '''

      pos = []
      # posTarget
      # 01 , 23, 45, 67, 89, 1011
      sublists = [data_raw[i:i+2] for i in range(0, 12, 2)]
      for data_raw_sublist in sublists:
        data = struct.unpack('h', data_raw_sublist)
        pos.append(data[0])
      print(pos)

      pos = []
      # sensorFeedback
      # ( 12-15, 16-19, 20-23, 24-27, 28-, 33-36 ) - data_start
      # 0-3, 4-7, 8-11, 12-15, 16-19, 20-23 
      data_start = 5*2+2
      sublists = [data_raw[i:i+4] for i in range(data_start, 36, 4)]
      for data_raw_sublist in sublists:
        data = struct.unpack('f', data_raw_sublist)
        pos.append(data[0])
      print(pos)
    
      while ser.in_waiting:
        _ = ser.read(1)
    
    else:
      while ser.in_waiting:
        _ = ser.read(1)

