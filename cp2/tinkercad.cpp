#include <LiquidCrystal.h>

const int photoResistorPin = A0;
const int potenciometerPin = A1;
const int temperaturePin = A2;

const int numReads = 5;

LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  
  pinMode(photoResistorPin, INPUT);
  pinMode(potenciometerPin, INPUT);
  pinMode(temperaturePin, INPUT);
  
  lcd.begin(16, 2);
}

void loop() {
  float photoResistorValues[numReads];
  float potenciometerValues[numReads];
  float temperatureValues[numReads];
  
  for (int i = 0; i < numReads; i++) {
    int photoResistorValue = analogRead(photoResistorPin);
    int potenciometerValue = analogRead(potenciometerPin);
    int temperatureValue   = analogRead(temperaturePin);
    float tmpCelsius = map(((temperatureValue - 20) * 3.04), 0, 1023, -40, 125);
    
    photoResistorValues[i] = photoResistorValue;
    potenciometerValues[i] = potenciometerValue;
    temperatureValues[i]   = tmpCelsius;
    delay(1000);
  }
  
  float photoResistorMedia = media(photoResistorValues, numReads);
  float potenciometerMedia = media(potenciometerValues, numReads);
  float temperatureMedia   = media(temperatureValues, numReads);
  
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
  
  float pontenciometerValuePercentage = map(potenciometerMedia, 0, 1022, 0, 100);
  if (pontenciometerValuePercentage < 50)
    lcd.print("Umidade BAIXA");
  
  else if (pontenciometerValuePercentage > 70)
    lcd.print("Umidade ALTA");
  
  else 
    lcd.print("Umidade OK");
    
  lcd.setCursor(0, 1);
  lcd.print("Umidade = ");
  lcd.print((int)pontenciometerValuePercentage);
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
