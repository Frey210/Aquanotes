import serial
import time
import requests

# Konfigurasi serial
arduino_port = 'COM3'  # Sesuaikan dengan port Arduino Anda
baud_rate = 115200
thing_speak_api_key = 'EBYNQ6ISU6MF2IYP'  # API Key untuk menulis data ke ThingSpeak
thing_speak_url = 'https://api.thingspeak.com/update'

# Inisialisasi komunikasi serial
try:
    arduino = serial.Serial(arduino_port, baud_rate, timeout=2)
    print("Koneksi serial dengan Arduino berhasil!")
except Exception as e:
    print(f"Gagal menghubungkan ke port {arduino_port}: {e}")
    exit()

# Fungsi untuk mengirim data ke ThingSpeak
def send_to_thingspeak(data):
    try:
        response = requests.post(thing_speak_url, params=data)
        if response.status_code == 200:
            print("Data berhasil dikirim ke ThingSpeak.")
        else:
            print(f"Gagal mengirim data. Status kode: {response.status_code}")
    except Exception as e:
        print(f"Kesalahan saat mengirim data: {e}")

# Loop untuk membaca data dari Arduino
try:
    while True:
        if arduino.in_waiting > 0:
            line = arduino.readline().decode('utf-8').strip()
            print(f"Data dari Arduino: {line}")
            
            # Pecah data berdasarkan koma
            try:
                dall_temp, dissolved_oxygen, tds, ph, lm35_temp, mq137_ppm = line.split(',')
                
                # Siapkan payload untuk ThingSpeak
                payload = {
                    'api_key': thing_speak_api_key,
                    'field1': dall_temp,
                    'field2': dissolved_oxygen,
                    'field3': tds,
                    'field4': ph,
                    'field5': lm35_temp,
                    'field6': mq137_ppm,
                }
                
                # Kirim data ke ThingSpeak
                send_to_thingspeak(payload)
                
            except ValueError as e:
                print(f"Kesalahan parsing data: {e}")
        
        time.sleep(1)

except KeyboardInterrupt:
    print("Program dihentikan oleh pengguna.")
finally:
    arduino.close()
    print("Koneksi serial ditutup.")
