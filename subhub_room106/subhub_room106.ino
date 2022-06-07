#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN D6

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(64, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

  
// ce_pin  (RST): default 4
// sck_pin (CLK): default 5
// io_pin  (DAT): default 6
// DS1302 rtc(ce_pin, sck_pin, io_pin);
DS1302 rtc(D2, D5, D4);

char *schedule[][3] = {  {"", "", ""}, //Sunday
                         {"106. IDEATION AND CPS. Ms Anmol","106. RESPONSIVE WEB. Mr Basit","106. EXPERIENCE DESIGN. Mr Iftikhar"}, //Monday
                         {"106. TOMORROW'S WEB. Mr Basit","106. CREATIVE INCUBATOR. Ms Arshiya","106. RESPONSIVE WEB. Mr Basit"}, //Tuesday
                         {"106. WEB DEVELOPMENT. Ms Zainab","106. EXPERIENCE DESIGN. Mr Iftikhar","106. CREATIVE INCUBATOR. Ms Arshiya"}, //Wednesday
                         {"Vacant","106. EMERGING TECHNOLOGIES. Dr Brohi","106. IDEATION AND CPS. Ms Anmol"},//Thursday
                         {"", "", ""}, //Friday
                         {"", "", ""}, //Sunday
                       }; 
                         
void setup() {
  Serial.begin(115200);
//  Serial.println("hello");
  
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(matrix.Color(255, 255, 255)); //setting text color to white
 
  Serial.println("matrix done");
  Wire.begin();
  rtc.begin();
  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(__DATE__, __TIME__));
  }
  Serial.println("rtc done");
}

// DISPLAY THE FULL TEXT
char *subject = "VACANT";
int  pixelPerChar = 6;
int  maxDisplacement;

int x = matrix.width();
void changeSub(int current_day, int current_hour, int current_minute){
//  int current_hour, int current_minute, int current_second
  int session = 0;
 //check every hour then check if between minute 0-30 or 31-59
  if(current_day == 1 || current_day == 2 || current_day == 3 || current_day == 4){
    if(current_hour == 9){
      if(current_minute >= 0 && current_minute <= 30) subject = "Good Morning, have fun at school! <3 Love you!"; 
      else if(current_minute >= 31 && current_minute <= 59) subject = schedule[current_day][0];
    }
    else if(current_hour == 10){
      if(current_minute >= 0 && current_minute <= 30) subject = schedule[current_day][0];
      else if(current_minute >= 31 && current_minute <= 59) subject = schedule[current_day][0];
    }
    else if(current_hour == 11){
      if(current_minute >= 0 && current_minute <= 30) subject = schedule[current_day][1];
      else if(current_minute >= 31 && current_minute <= 59) subject = schedule[current_day][1];
    }
    else if(current_hour == 12){
      if(current_minute >= 0 && current_minute <= 30) subject = schedule[current_day][1];
      else if(current_minute >= 31 && current_minute <= 59) subject = schedule[current_day][2];
    }
    else if(current_hour == 13){
      if(current_minute >= 0 && current_minute <= 30) subject = schedule[current_day][2];
      else if(current_minute >= 31 && current_minute <= 59) subject = schedule[current_day][2];
    }
    else if (current_hour >= 14) subject = "Call me when you're home <3"; 
    
  } 
  else if(current_day == 0 || current_day == 5 || current_day == 6){ //the following if statements are for the weekends (sunday, friday, saturday)
    if(current_hour >= 9 && current_hour <= 20){
      subject = "Creative Computing @ Bath Spa University! Learn WebDesign, GamesDevelopment, PhoneApps, MachineLearning, AR-VR…..& lots more! Visit www.bathspa.ae";
    }
  }

  maxDisplacement = strlen(subject) * pixelPerChar;
}

void loop() {
  DateTime now = rtc.now();
  changeSub(now.dayOfWeek(), now.hour(), now.minute());
//  changeSub(now.dayOfWeek(), now.hour(), now.minute(), now.second());
  matrix.fillScreen(0);
  matrix.setCursor(x, 0);
  matrix.print(subject);
  if(--x < -maxDisplacement) {
    x = matrix.width();
  }
  matrix.show();
  delay(80);
}
