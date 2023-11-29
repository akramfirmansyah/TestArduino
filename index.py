import serial
import time
from datetime import datetime
import csv

ser = serial.Serial("COM3", 9600)
time.sleep(2)

csvPath = "data/data.csv"

try:
    with open(csvPath, mode="w", newline="") as csvFile:
        fieldNames = ["datetime", "ppm", "pH", "humidity", "air_temperature"]
        writer = csv.DictWriter(csvFile, fieldnames=fieldNames)

        writer.writeheader()

        # while True:
        i = 0
        while i < 20:
            i += 1

            data = ser.readline().decode("utf-8").strip()
            print(data)

            tds, ph, humidity, airTemperature = map(float, data.split(","))

            currentDatetime = datetime.now().strftime("%d-%m-%Y %H:%M:%S")

            writer.writerow(
                {
                    "datetime": currentDatetime,
                    "ppm": tds,
                    "pH": ph,
                    "humidity": humidity,
                    "air_temperature": airTemperature,
                }
            )
except KeyboardInterrupt:
    ser.close()
