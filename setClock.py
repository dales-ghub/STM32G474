from datetime import datetime
import argparse, serial, time

def out(ser, string):
    if(args.v):
        print(string)
    string = string + "\n"
    ser.write(string.encode())

parser=argparse.ArgumentParser()
parser.add_argument('-p',dest='port', default='/dev/ttyACM0')
parser.add_argument('-v',dest='v', action='store_true')

args=parser.parse_args()
ser = serial.Serial(args.port, 115200, timeout=.1)

now = datetime.now()

string = "STime %d:%d:%d" % (now.hour, now.minute, now.second)
out(ser, string)
print(ser.readline().strip())

time.sleep(1)
string = "SetDate %02d-%02d-%02d" % (now.year%100, now.month, now.day)
out(ser, string)
print(ser.readline().strip())


