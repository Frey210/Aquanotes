import serial
import time
import requests
import csv
import os

# Konfigurasi koneksi serial dengan Arduino
ser = serial.Serial('/dev/ttyACM1', 115200)  # Ganti '/dev/ttyACM0' sesuai dengan port Arduino
time_delay = 300  # 5 menit dalam detik
csv_filename = "sensor_data.csv"

def send_sensor_data(data):
    url = "http://kedaireka.simnasfikpunhas.com/device_1/store_data.php"
    response = requests.get(url, params=data)
    if response.status_code == 200:
        print("Data berhasil dikirim ke database")
        return True
    else:
        print("Gagal mengirim data ke database")
        return False

def save_to_csv(data):
    if not os.path.exists(csv_filename):
        with open(csv_filename, 'w', newline='') as csvfile:
            csv_writer = csv.DictWriter(csvfile, fieldnames=data.keys())
            csv_writer.writeheader()
    with open(csv_filename, 'a', newline='') as csvfile:
        csv_writer = csv.DictWriter(csvfile, fieldnames=data.keys())
        csv_writer.writerow(data)
        print("Data disimpan dalam file CSV")

try:
    while True:
        arduino_data = ser.readline().decode().strip()
        if arduino_data:
            data_list = arduino_data.split(',')
            if len(data_list) == 6:
                water_temp = data_list[0]
                do_value = data_list[1]
                tds_value = data_list[2]
                ph_value = data_list[3]
                air_temp = data_list[4]
                ammonia_value = data_list[5]
                
                data_to_send = {
                    "water_temperature": water_temp,
                    "do": do_value,
                    "tds": tds_value,
                    "air_temperature": air_temp,
                    "ph": ph_value,
                    "amonia": ammonia_value
                }
                
                if not send_sensor_data(data_to_send):
                    save_to_csv(data_to_send)
        time.sleep(time_delay)

except KeyboardInterrupt:
    print("Program dihentikan oleh pengguna")
    ser.close()
