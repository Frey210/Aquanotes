import serial
import time
import requests
import threading

ser = serial.Serial('/dev/ttyACM0', 9600)
time_delay = 300  # 5 menit dalam detik

data_lock = threading.Lock()
arduino_data = None
last_send_time = time.time() - time_delay

def receive_data():
    global arduino_data
    while True:
        raw_data = ser.readline().decode().strip()
        if raw_data:
            with data_lock:
                arduino_data = raw_data

def send_sensor_data(data):
    url = "http://localhost/aquanotes/store_data.php"
    response = requests.get(url, params=data)
    if response.status_code == 200:
        print("Data berhasil dikirim ke database")
    else:
        print("Gagal mengirim data ke database")

def main_loop():
    global arduino_data, last_send_time
    while True:
        current_time = time.time()
        if current_time - last_send_time >= time_delay:
            with data_lock:
                if arduino_data:
                    data_list = arduino_data.split(',')
                    if len(data_list) == 6:
                        water_temp, do_value, tds_value, air_temp, ph_value, ammonia_value = data_list

                        data_to_send = {
                            "water_temperature": water_temp,
                            "do": do_value,
                            "tds": tds_value,
                            "air_temperature": air_temp,
                            "ph": ph_value,
                            "amonia": ammonia_value
                        }

                        send_sensor_data(data_to_send)
            last_send_time = current_time
        time.sleep(1)

# Membuat dan memulai thread penerimaan data
receive_thread = threading.Thread(target=receive_data)
receive_thread.daemon = True
receive_thread.start()

# Memulai loop utama
try:
    main_loop()
except KeyboardInterrupt:
    print("Program dihentikan oleh pengguna")
    ser.close()
