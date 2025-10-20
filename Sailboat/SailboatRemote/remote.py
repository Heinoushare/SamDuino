import serial
import keyboard

PORT = "/dev/cu.usbserial-A800cGri"
BAUD = 9600




xbee = serial.Serial(PORT, BAUD, timeout=1)
print("Connected. Type messages and press Enter. Ctrl+C to quit.\n")

try:
    lastSend = ""
    while True:
        send = "-"
        # print(keyboard.read_key())
        if keyboard.is_pressed(13):
            send = "S"
        elif keyboard.is_pressed(1):
            send = "s"
        elif keyboard.is_pressed(12):
            send = "r"
        elif keyboard.is_pressed(2):
            send = "R"
        elif keyboard.is_pressed('space'):
            send = "e"

        if send != lastSend:
            xbee.write(send.encode())
            print("Sent:", send)
            lastSend = send

        # keyboard.wait('q', suppress=False)
        if xbee.in_waiting:
            data = xbee.read(xbee.in_waiting).decode(errors="ignore")
            print("Received:", data.strip())
except KeyboardInterrupt:
    pass
finally:
    xbee.close()