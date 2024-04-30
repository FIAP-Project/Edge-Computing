#include <LiquidCrystal.h>
#include <DHT.h>

#define DHT_PIN 6 // Pino para o DHT22
#define DHT_TYPE DHT11

const int photoResistorPin = A0;
const int numReads = 5;

LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(9600);
  
  pinMode(photoResistorPin, INPUT);
  
  lcd.begin(16, 2);
  dht.begin();
}

void loop() {
  float photoResistorValues[numReads];
  float humidityValues[numReads];
  float temperatureValues[numReads];
  
  for (int i = 0; i < numReads; i++) {
    int photoResistorValue = analogRead(photoResistorPin);
    int humidityValue = dht.readHumidity();
    int temperatureValue = dht.readTemperature();
    
    photoResistorValues[i] = photoResistorValue;
    humidityValues[i] = humidityValue;
    temperatureValues[i] = temperatureValue;
    delay(1000);
  }
  
  float photoResistorMedia = media(photoResistorValues, numReads);
  float humidityMedia = media(humidityValues, numReads);
  float temperatureMedia = media(temperatureValues, numReads);
  
  lcd.clear();
  
  if (temperatureMedia < 10)
    lcd.print("Temp. BAIXA");
  
  else if (temperatureMedia > 15)
    lcd.print("Temp. ALTA");
    
  else
    lcd.print("Temp. OK");
  
  lcd.setCursor(0, 1);
  lcd.print("Temp. = ");
  lcd.print(temperatureMedia);
  lcd.print("C");
  
  delay(5000);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  
  if (humidityMedia < 50)
    lcd.print("Umidade BAIXA");
  
  else if (humidityMedia > 70)
    lcd.print("Umidade ALTA");
  
  else 
    lcd.print("Umidade OK");
    
  lcd.setCursor(0, 1);
  lcd.print("Umidade = ");
  lcd.print((int)humidityMedia);
  lcd.print("%");
  
  delay(5000);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  
  if (photoResistorMedia < 300)
    lcd.print("Luz ambiente OK");
  
  else if (photoResistorMedia > 600)
    lcd.print("Muito CLARO");
    
  else
    lcd.print("Meia luz");
}

float media(float valores[], int length) {
  int soma = 0;
  for (int i = 0; i < length; i++)
    soma += valores[i];
  
  return (float) soma / length;
}
