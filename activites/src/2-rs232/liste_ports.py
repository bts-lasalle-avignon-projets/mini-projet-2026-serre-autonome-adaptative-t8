import serial.tools.list_ports

ports = serial.tools.list_ports.comports()
for port in ports:
    if port.description != "n/a":
        print(f"{port.device}: {port.description}")
