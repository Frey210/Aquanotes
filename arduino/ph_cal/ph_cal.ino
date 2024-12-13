// Variabel untuk menyimpan nilai analog dan tegangan
int pH_Value; 
float Voltage;
float pH; 

// Koefisien kalibrasi (dihitung berdasarkan pembacaan pada buffer pH 4 dan pH 7)
float slope; // Kemiringan linier
float intercept; // Titik potong sumbu-Y

void setup() 
{ 
  Serial.begin(9600);
  pinMode(A2, INPUT); 
  
  // Tentukan titik kalibrasi berdasarkan pembacaan tegangan sensor
  float voltage_pH4 = 4.6; // Tegangan saat buffer pH 4
  float voltage_pH7 = 4.18; // Tegangan saat buffer pH 7
  float pH4 = 4.0; 
  float pH7 = 7.0;
  
  // Hitung slope dan intercept
  slope = (pH7 - pH4) / (voltage_pH7 - voltage_pH4);
  intercept = pH4 - slope * voltage_pH4;
}

void loop() 
{ 
  // Baca nilai analog dari sensor
  pH_Value = analogRead(A2); 
  
  // Konversi nilai analog menjadi tegangan
  Voltage = pH_Value * (5.0 / 1023.0); 
  
  // Hitung nilai pH berdasarkan hasil kalibrasi
  pH = slope * Voltage + intercept;
  
  // Tampilkan tegangan dan nilai pH
  Serial.print("Voltage: ");
  Serial.print(Voltage);
  Serial.print(" V, pH: ");
  Serial.println(pH);
  
  delay(500); 
}
