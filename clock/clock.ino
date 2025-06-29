#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

Adafruit_PCD8544 display = Adafruit_PCD8544(18, 23, 19, 2, 15);

const char* ssid     = "Prateek";
const char* password = "justdoelectronics@#12345";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 19800, 60000); 

int currentDay, currentMonth, currentYear;

void setup() {
  
  Serial.begin(115200);

  display.begin();
  display.setContrast(50);
  display.clearDisplay();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");

  timeClient.begin();

  display.setTextSize(1);
  display.setTextColor(BLACK, WHITE);
  display.clearDisplay();
  display.setCursor(24, 0);
  display.print("CLOCK");
  display.display();
}

void loop() {
  timeClient.update();

  unsigned long epochTime = timeClient.getEpochTime();
  convertEpochToDate(epochTime);

  int h = timeClient.getHours();
  int m = timeClient.getMinutes();
  int s = timeClient.getSeconds();

 
  display.fillRect(0, 25, display.width(), display.height() - 25, WHITE);

  display.setTextSize(1);
  const char* timeFormat = "%02d:%02d:%02d";
  char timeStr[9];
  snprintf(timeStr, sizeof(timeStr), timeFormat, h, m, s);
  int16_t x1, y1;
  uint16_t w, hgt;
  display.getTextBounds(timeStr, 0, 0, &x1, &y1, &w, &hgt);
  display.setCursor((display.width() - w) / 2, 15);
  display.print(timeStr);

  display.setTextSize(1);
  const char* dateFormat = "%02d-%02d-%04d";
  char dateStr[15];
  snprintf(dateStr, sizeof(dateStr), dateFormat, currentDay, currentMonth, currentYear);
  display.getTextBounds(dateStr, 0, 0, &x1, &y1, &w, &hgt);
  display.setCursor((display.width() - w) / 2, 30);
  display.print(dateStr);

  display.display();

  delay(1000);
}

void convertEpochToDate(unsigned long epoch) {
  unsigned long days = epoch / 86400L;
  int year = 1970;
  while (true) {
    bool leap = isLeapYear(year);
    int daysInYear = leap ? 366 : 365;
    if (days >= daysInYear) {
      days -= daysInYear;
      year++;
    } else {
      break;
    }
  }
  int month = 1;
  int monthDays[] = {31,28,31,30,31,30,31,31,30,31,30,31};
  if (isLeapYear(year)) monthDays[1] = 29;
  while (days >= monthDays[month - 1]) {
    days -= monthDays[month - 1];
    month++;
  }
  int day = days + 1;

  currentYear = year;
  currentMonth = month;
  currentDay = day;
}

bool isLeapYear(int year) {
  return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}
