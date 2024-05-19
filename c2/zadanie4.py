import serial
import time
import threading

# Initialize serial connection
ser = serial.Serial("/dev/ttyUSB0", 9600)
ser.timeout = 1


def read_serial():
    while True:
        if ser.in_waiting > 0:
            data = ser.readline().decode("utf-8").strip()
            if data:
                print(data)


def continuous_read(command):
    while True:
        ser.write(command.encode())
        time.sleep(1)
        if stop_event.is_set():
            break


stop_event = threading.Event()


def handle_command(command):
    if command in ["H", "T", "L", "P", "A"]:
        ser.write(command.encode())
    elif command in ["h", "t", "l", "p", "a"]:
        stop_event.clear()
        continuous_thread = threading.Thread(
            target=continuous_read, args=(command.upper(),)
        )
        continuous_thread.start()
        input("Press Enter to stop...")
        stop_event.set()


if __name__ == "__main__":
    read_thread = threading.Thread(target=read_serial)
    read_thread.start()

    try:
        while True:
            command = input("Enter command (H, T, L, P, A, h, t, l, p, a): ")
            handle_command(command)
    except KeyboardInterrupt:
        ser.close()
        print("Program terminated.")
