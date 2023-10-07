import serial

ser = serial.Serial(
    port="COM3",
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=0
)

# Open the output file in write mode
with open("output.csv", "w") as f:
    header = "Canal0,Canal1,Canal2,Canal3\n"
    f.write(header)

    print("Connected to: " + ser.portstr)

    # This will store the line
    line = []

    try:
        while True:
            for c in ser.read():
                c = chr(c)
                line.append(c)
                if c == "\n":
                    print("Line: " + "".join(line))
                    data_str = "".join(line)
                    f.write(data_str)
                    f.flush()  # Flush the data to the file
                    line = []
    except KeyboardInterrupt:
        print("KeyboardInterrupt: Exiting the program.")

# Close the serial port when done
ser.close()
