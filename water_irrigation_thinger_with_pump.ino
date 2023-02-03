#define THINGER_SERIAL_DEBUG
#include "DHTStable.h"
#include <ThingerESP8266.h>
#include "arduino_secrets.h"
const int AirValue = 859;
const int WaterValue = 470;
const int pump = 5; //D1
#define DHT11_PIN       4 // D2
int soilMoistureValue = 0;
int soilmoisturepercent = 0;
ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);
DHTStable DHT;

void setup() {
  // open serial for monitoring
  Serial.begin(115200);

  // set builtin led as output
  pinMode(pump, OUTPUT);

  // add WiFi credentials
  thing.add_wifi(SSID, SSID_PASSWORD);

  // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  // thing["led"] << digitalPin(LED_BUILTIN);

  //thing["LUX"] >> outputValue(analogRead(A0));
  thing["Moisture in % "] >> outputValue(soilmoisturepercent);
  thing["Moisture in Atmosphere % "] >> outputValue(DHT.getHumidity());
  thing["Temperature in Atmosphere % Celcius "] >> outputValue(DHT.getTemperature());
}

void loop() {
 thing.handle();
  int chk = DHT.read11(DHT11_PIN);
  // DISPLAY DATA
  Serial.print("Atmosphere Humidity is = ");
  Serial.print(DHT.getHumidity(), 1);
  Serial.print(" %");
  Serial.println("Atmosphere Temperature is = ");
  Serial.print(DHT.getTemperature(), 1);
  Serial.print(" % Celcius");
  soilMoistureValue = analogRead(A0);
  Serial.println(soilMoistureValue);
  soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
  if (soilmoisturepercent >= 100)
  {
    Serial.println("100 %");
  }
  else if (soilmoisturepercent <= 0)
  {
    Serial.println("0 %");
  }
  else if (soilmoisturepercent > 0 && soilmoisturepercent < 100)
  {
    Serial.print(soilmoisturepercent);
    Serial.println("%");
  }
  if (soilmoisturepercent <= 50)
  {
    digitalWrite(pump, LOW);
    Serial.println("Pump is ON");
    thing["Pump Status"] >> outputValue("Solenoid valve is ON");
  }
  else
  {
     digitalWrite(pump, HIGH);
     Serial.println("Solenoid valve is OFF");
     thing["Pump Status"] >> outputValue("Pump is OFF");
  }
  delay(2000);
}
