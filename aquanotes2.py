import serial
import time
import requests

# Konfigurasi koneksi serial dengan Arduino
ser = serial.Serial('/dev/ttyACM1', 115200)  # Ganti '/dev/ttyACM0' sesuai dengan port Arduino
time_delay = 300  # 5 menit dalam detik

def send_sensor_data(data):
    url = "http://localhost/aquanotes/store_data.php"
    response = requests.get(url, params=data)
    if response.status_code == 200:
        print("Data berhasil dikirim ke database")
    else:
        print("Gagal mengirim data ke database")

try:
    while True:
        arduino_data = ser.readline().decode().strip()
        if arduino_data:
            data_list = arduino_data.split(',')
            if len(data_list) == 6:
                water_temp = data_list[0]
                do_value = data_list[1]
                tds_value = data_list[2]
                air_temp = data_list[3]
                ph_value = data_list[4]
                ammonia_value = data_list[5]
                
                data_to_send = {
                    "water_temperature": water_temp,
                    "do": do_value,
                    "tds": tds_value,
                    "air_temperature": air_temp,
                    "ph": ph_value,
                    "amonia": ammonia_value
                }
                
                send_sensor_data(data_to_send)
        time.sleep(time_delay)

except KeyboardInterrupt:
    print("Program dihentikan oleh pengguna")
    ser.close()
