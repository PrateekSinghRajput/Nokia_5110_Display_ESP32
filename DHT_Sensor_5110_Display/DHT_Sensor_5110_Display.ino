

#include <SPI.h>               
#include <Adafruit_GFX.h>     
#include <Adafruit_PCD8544.h>  
#include <DHT.h>          

Adafruit_PCD8544 display = Adafruit_PCD8544(18, 23, 19, 2, 15);

#define DHTPIN  26          
#define DHTTYPE DHT22        
DHT dht22(DHTPIN, DHTTYPE); 

void setup() {


  display.begin();
  dht22.begin();

  display.setContrast(50);
  display.clearDisplay();   
  display.drawFastHLine(0, 23, display.width(), BLACK);

  display.setTextSize(1);
  display.setTextColor(BLACK, WHITE);
  display.setCursor(6, 0);
  display.print("TEMPERATURE:");
  display.setCursor(15, 28);
  display.print("HUMIDITY:");
  display.display();

}

void loop() {

  int Humi = dht22.readHumidity() * 10;
  int Temp = dht22.readTemperature() * 10;

  display.setCursor(18, 12);
  if(Temp < 0)  
    display.printf("-%02u.%1u C", (abs(Temp)/10)%100, abs(Temp) % 10);
  else          
    display.printf(" %02u.%1u C", (Temp/10)%100, Temp % 10);
  display.drawRect(50, 12, 3, 3, BLACK);
  display.setCursor(24, 40);
  display.printf("%02u.%1u %%", (Humi/10)%100, Humi % 10);

  display.display();

  delay(1000);
}
