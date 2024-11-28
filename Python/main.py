import time
import serial.tools.list_ports
import json

port = list(serial.tools.list_ports.comports())
device= None
for p in port:
    if "CP2104 USB to UART Bridge Controller - CP2104 USB to UART Bridge Controller" in p.description:
        device = p.device

ser = serial.Serial(device, 115200, timeout=3)

time.sleep(3)
ser.reset_input_buffer()
print('Serial OK')

increase = 0


while True:
    try:
        time.sleep(0.01)
        if increase < 255:
            increase+= 1
        else:
            increase-= 1
        print('Sedn data to ESP32')
        print(increase)
        
        json_on = {'name': 'Led 21', 'action': 'on', 'intensity': increase}
        json_off = {'name': 'Led 21', 'action': 'off', 'intensity': increase}
        ser.write(json.dumps(json_on).encode('utf-8'))
        time.sleep(1)
        ser.write(json.dumps(json_off).encode('utf-8'))
        ser.write('Led On 22\n'.encode('utf-8'))
        time.sleep(1)
        ser.write('Led Off 22\n'.encode('utf-8'))
        # if ser.in_waiting >= 0:
             # data = ser.readline().decode('utf-8')
            # print(data)
    except KeyboardInterrupt:
        print('Close serial communication')
        ser.close()
        break