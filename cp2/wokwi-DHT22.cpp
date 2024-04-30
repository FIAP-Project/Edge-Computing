#include <DHT.h>

#define DHT_PIN 2 // Pino para o DHT22
#define DHT_TYPE DHT22

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(9600);

  dht.begin();
}

void loop() {
  float humidity = dht.readHumidity();
  float temp = dht.readTemperature();

  Serial.print("Humidity: ");
  Serial.println(humidity);

  Serial.print("Temp: ");
  Serial.println(temp);  

  delay(3000);
}
