import serial
import time
import requests
import csv
import os
from datetime import datetime, timedelta

def send_sensor_data(data):
    url = "http://aquanotes.id/device_1/store_data.php"
    try:
        response = requests.get(url, params=data)
        response.raise_for_status()
        print("Data berhasil dikirim ke database")
        return True
    except requests.exceptions.RequestException as e:
        print("Gagal mengirim data ke database:", e)
        return False

def save_to_csv(data):
    file_exists = os.path.exists(csv_filename)
    with open(csv_filename, 'a', newline='') as csvfile:
        csv_writer = csv.DictWriter(csvfile, fieldnames=csv_headers)
        if not file_exists:
            csv_writer.writeheader()
        csv_writer.writerow(data)
        print("Data disimpan dalam file CSV")

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM1', 115200, timeout=1)
    ser.reset_input_buffer()

    # buffer_reset_interval = 300  # Reset buffer setiap 5 menit
    # last_buffer_reset_time = datetime.now()
    
    csv_filename = "sensor_data.csv"
    csv_headers = ["water_temperature", "do", "tds", "ph", "air_temperature", "amonia"]

    try:
        while True:
            if ser.in_waiting > 0:
                arduino_data = ser.readline().decode().strip()
                current_time = datetime.now()

                # # Reset buffer secara berkala
                # if (current_time - last_buffer_reset_time) > timedelta(seconds=buffer_reset_interval):
                #     ser.reset_input_buffer()  # Reset buffer input
                #     last_buffer_reset_time = current_time

                if arduino_data:
                    print("Data dari Arduino:", arduino_data)
                    data_list = arduino_data.split(',')
                    if len(data_list) == 6:
                        try:
                            water_temp = float(data_list[0])
                            do_value = float(data_list[1])
                            tds_value = float(data_list[2])
                            ph_value = float(data_list[3])
                            air_temp = float(data_list[4])
                            ammonia_value = float(data_list[5])

                            data_to_send = {
                                "water_temperature": water_temp,
                                "do": do_value,
                                "tds": tds_value,
                                "air_temperature": air_temp,
                                "ph": ph_value,
                                "amonia": ammonia_value
                            }

                            if current_time.minute % 5 == 0:
                                if send_sensor_data(data_to_send):
                                    print("Update berhasil pada:", datetime.now())
                                else:
                                    save_to_csv(data_to_send)
                        except ValueError:
                            print("Data dari Arduino tidak sesuai format")
                ser.reset_input_buffer()  # Reset buffer input
            time.sleep(60)  # Cek setiap 1 menit

    except KeyboardInterrupt:
        print("Program dihentikan oleh pengguna")
        ser.close()
