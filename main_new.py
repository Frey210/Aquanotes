import tkinter as tk
from tkinter import ttk, filedialog, messagebox
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import pandas as pd
import serial
import threading
import time  # Mengimport waktu untuk timestamp

# === Konfigurasi Serial ===
SERIAL_PORT = 'COM14'  # Ganti sesuai port Arduino Anda
BAUD_RATE = 9600

# === Data Global ===
data_history = []

# === Fungsi untuk Menyimpan Data ke Excel ===
def save_to_excel():
    if not data_history:
        return
    # Menyimpan data dengan timestamp lengkap (tanggal-bulan-tahun jam-menit-detik)
    timestamp = time.strftime("%d-%m-%Y %H-%M-%S")
    file_path = filedialog.asksaveasfilename(defaultextension=".xlsx",
                                             filetypes=[("Excel files", "*.xlsx")])
    if file_path:
        df = pd.DataFrame(data_history, columns=["Timestamp", "Temperature", "DO", "TDS", "pH"])
        df['Timestamp'] = [x[0] for x in data_history]  # Menambahkan kolom timestamp
        df.to_excel(file_path, index=False)
        messagebox.showinfo("Success", f"Data saved to {file_path}")

# === Fungsi untuk Memperbarui Grafik ===
def update_graph():
    if not data_history:
        return
    temp_data, do_data, tds_data, ph_data = zip(*[x[1:] for x in data_history])  # Mengambil data tanpa timestamp
    temp_line.set_ydata(temp_data)
    temp_line.set_xdata(range(len(temp_data)))
    ax.relim()
    ax.autoscale_view()
    canvas.draw()

# === Fungsi untuk Membaca Data Serial ===
def read_serial():
    global data_history
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE)
    while True:
        try:
            line = ser.readline().decode().strip()
            values = list(map(float, line.split(',')))
            if len(values) == 4:
                # Menambahkan timestamp saat data diterima
                timestamp = time.strftime("%d-%m-%Y %H-%M-%S")
                data_history.append([timestamp] + values)
                if len(data_history) > 50:  # Batasi jumlah data dalam grafik
                    data_history.pop(0)
                # Update Grafik
                update_graph()
                # Update Gauge Bar
                temp_var.set(f"{values[0]:.2f} °C")
                do_var.set(f"{values[1]:.2f} mg/L")
                tds_var.set(f"{values[2]:.2f} ppm")
                ph_var.set(f"{values[3]:.2f}")
        except Exception as e:
            print(f"Error: {e}")

# === GUI ===
root = tk.Tk()
root.title("Sensor Monitoring")
root.geometry("800x600")

# Frame Visualisasi
frame_graph = tk.Frame(root)
frame_graph.pack(side=tk.TOP, fill=tk.BOTH, expand=True)

# Frame Gauge
frame_gauge = tk.Frame(root)
frame_gauge.pack(side=tk.TOP, fill=tk.X, padx=10, pady=10)

# Gauge Variables
temp_var = tk.StringVar(value="0.00 °C")
do_var = tk.StringVar(value="0.00 mg/L")
tds_var = tk.StringVar(value="0.00 ppm")
ph_var = tk.StringVar(value="0.00")

# Gauge Bar
for label, var in [("Temperature", temp_var), ("DO", do_var), ("TDS", tds_var), ("pH", ph_var)]:
    frame = tk.Frame(frame_gauge)
    frame.pack(side=tk.LEFT, fill=tk.BOTH, expand=True, padx=5)
    tk.Label(frame, text=label, font=("Arial", 12)).pack()
    ttk.Progressbar(frame, orient="vertical", maximum=100, value=0, length=200).pack()
    tk.Label(frame, textvariable=var, font=("Arial", 12)).pack()

# Grafik
fig = Figure(figsize=(6, 4), dpi=100)
ax = fig.add_subplot(111)
temp_line, = ax.plot([], [], label="Temperature (°C)", color="red")
ax.set_title("Real-time Data")
ax.set_xlabel("Time")
ax.set_ylabel("Values")
ax.legend()

canvas = FigureCanvasTkAgg(fig, frame_graph)
canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=True)

# Tombol Simpan Riwayat
btn_save = tk.Button(root, text="Save History to Excel", command=save_to_excel)
btn_save.pack(side=tk.BOTTOM, pady=10)

# Jalankan Serial Reader di Thread Terpisah
thread = threading.Thread(target=read_serial, daemon=True)
thread.start()

root.mainloop()
