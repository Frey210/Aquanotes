const float minValue = 27.0;   // Nilai minimum
const float maxValue = 32.0;   // Nilai maksimum
const float changeThreshold = 0.5;  // Ambang batas perubahan
const unsigned long changeInterval = 5000;  // Interval perubahan (dalam milidetik)

float currentValue = 27.0;  // Nilai awal
unsigned long lastChangeTime = 0;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A0));
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastChangeTime >= changeInterval) {
    float randomValue = random(minValue * 10, maxValue * 10 + 1) / 10.0;  // Menghasilkan nilai acak dengan satu angka di belakang koma
    float diff = abs(randomValue - currentValue);

    if (diff <= changeThreshold) {
      currentValue = randomValue;
      lastChangeTime = currentTime;

      Serial.print("Nilai baru: ");
      Serial.println(currentValue, 1);  // Mencetak dengan 1 desimal
    }
  }
}
