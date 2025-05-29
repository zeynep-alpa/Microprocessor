// 4 basamaklı 7 segment display için segment (a-h) ve digit pinleri tanımlanıyor
int segmentPins[] = {2, 3, 4, 5, 6, 7, 8, 13};  // a, b, c, d, e, f, g, dp (13. pin decimal point)
int digitPins[] = {9, 10, 11, 12};             // DIG1–DIG4 (common anode girişleri)

// Görüntülenecek karakterleri tutan 4 basamaklı buffer (başlangıçta boş)
char displayBuffer[4] = {' ', ' ', ' ', ' '};  

// ASCII karakterden 7 segment için hex karşılığı üreten fonksiyon
byte decodeASCII(char c) {
  switch (c) {
    case '0': return 0b11000000;
    case '1': return 0b11111001;
    case '2': return 0b10100100;
    case '3': return 0b10110000;
    case '4': return 0b10011001;
    case '5': return 0b10010010;
    case '6': return 0b10000010;
    case '7': return 0b11111000;
    case '8': return 0b10000000;
    case '9': return 0b10010000;
    default:  return 0xFF; // tanımsız karakterler için tüm segmentleri kapat
  }
}

void setup() {
  Serial.begin(9600);  // Bilgisayarla seri haberleşme başlatılır

  // Tüm segment pinleri çıkış olarak ayarlanır
  for (int i = 0; i < 8; i++)
    pinMode(segmentPins[i], OUTPUT);

  // Tüm digit pinleri çıkış olarak ayarlanır
  for (int i = 0; i < 4; i++)
    pinMode(digitPins[i], OUTPUT);
}

void loop() {
  // Eğer seri porttan bir karakter geldiyse
  if (Serial.available() > 0) {
    char c = Serial.read(); // Karakteri oku
    // Display buffer’ı sola kaydır
    for (int i = 0; i < 3; i++)
      displayBuffer[i] = displayBuffer[i+1];
    // Gelen karakter en sağdaki digit'e eklenir
    displayBuffer[3] = c;
  }

  // Dinamik tarama yöntemi: her basamak sırayla aktif edilerek görüntülenir
  for (int i = 0; i < 4; i++) {
    digitalWrite(digitPins[i], LOW); // İlgili digit aktif edilir (common anode mantığı)

    // Aktif digit'e ait karakterin segment karşılığı alınır
    byte segments = decodeASCII(displayBuffer[i]);
    
    // a–g–dp segmentleri sırayla yazılır
    for (int j = 0; j < 8; j++)
      digitalWrite(segmentPins[j], !((segments >> j) & 0x01)); // LOW → LED yanar (ters mantık)

    delay(5);  // Gözün algılayabileceği süre kadar basamak açık kalır
    digitalWrite(digitPins[i], HIGH); // Basamak kapatılır, diğerine geçilir
  }
}
