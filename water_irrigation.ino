
//calibration for percentage value
const int calib_value_air = 859;
const int calib_value_water = 470;

int moisture_in_analog = 0;
int moisture_in_100percentage = 0;

void setup()
{
  Serial.begin(115200);
}
void loop()
{
  moisture_in_analog = analogRead(A0);  // Getting RAW value from SM Sensor
  Serial.println(moisture_in_analog);   // Print RAW value on Serial monitor

  moisture_in_100percentage = map(moisture_in_analog, calib_value_air, calib_value_water, 0, 100); // Mapping 0-100 from RAW value
  if (moisture_in_100percentage >= 100)
  {
    Serial.println("100 %");            // Print 100% if map value is greater than 100
  }
  else if (moisture_in_100percentage <= 0)
  {
    Serial.println("0 %");              // Print 0% if map value is less than 0
  }
  else if (moisture_in_100percentage > 0 && moisture_in_100percentage < 100)
  {
    Serial.print(moisture_in_100percentage);  // Print actual percentage
    Serial.println("%");
  }
  delay(250);   // Give some time to get next value
}
