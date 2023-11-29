#include <DHT.h>

#define tdsSensorPin A0
#define phSensorPin A1
#define dhtSensorPin 8

#define DHTTYPE DHT11

DHT dht(dhtSensorPin, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float tdsValue = readTDS();
  float pHValue = readpH();
  float humidityValue = readHumidity();
  float airTemperatureValue = readAirTemperature();

  Serial.print(tdsValue);
  Serial.print(",");
  Serial.print(pHValue);
  Serial.print(",");
  Serial.print(humidityValue);
  Serial.print(",");
  Serial.print(airTemperatureValue);
  Serial.println("");

  delay(1000);
}

float readTDS() {
  int tdsSensorValue = analogRead(tdsSensorPin);
  float voltage = tdsSensorValue * (5.0 / 1024.0);
  float tdsValue = voltage * 1000;
  return tdsValue;
}

float readpH() {
  int sensorValue = analogRead(phSensorPin);
  float pHValue = map(sensorValue, 0, 1023, 0, 14);
  return pHValue;
}

float readHumidity() {
  float humidity = dht.readHumidity();
  if (isnan(humidity)) {
    return 0;
  }

  return humidity;
}

float readAirTemperature() {
  float airTemperature = dht.readTemperature();
  if (isnan(airTemperature)) {
    return 0;
  }

  return airTemperature;
}
