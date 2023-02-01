import serial
import struct
import time

ser = serial.Serial('/dev/ttyACM1', baudrate=9600, timeout=1)  # Open the serial port at 9600 baud

time.sleep(2)

HEADER = 0x23

class DataPacket(object):
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.checksum = HEADER+key+value

data_packet = DataPacket(0x08, 1)

packet = struct.pack("<BBBB", HEADER, data_packet.key, data_packet.value, data_packet.checksum)
ser.write(packet)
# pritn packet as hex 
print(packet.hex())

# Read the acknowledgement from the Arduino
ack = ser.read(1)
if ack == b'\x24':
    print("Received valid acknowledgement from Arduino")
    # print ack as hex
    print(ack.hex())
else:
  print("No data received from Arduino")

ser.close()  # Close the serial port