    /* 
Modified on Nov 25, 2020
Modified by MehranMaleki from Arduino Examples
Home
*/


// CONNECTIONS:
// DS1302 CLK/SCLK --> 5
// DS1302 DAT/IO --> 4
// DS1302 RST/CE --> 2
// DS1302 VCC --> 3.3v - 5v
// DS1302 GND --> GND

#include <ThreeWire.h>  
#include <RtcDS1302.h>

ThreeWire myWire(4,5,2); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

void setup () 
{
    Serial.begin(9600);

    Serial.print("compiled: ");
    Serial.print(__DATE__);
    Serial.println(__TIME__);

    Rtc.Begin();
    
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    printDateTime(compiled);
    Serial.println();
}

void loop () 
{
    RtcDateTime now = Rtc.GetDateTime();
    
    printDateTime(now);
    Serial.println();

    int current_time = now.Second();
    int current_dow = now.DayOfWeek();
    
    if(current_time == 10 || current_time == 20 || current_time == 30){
      declarePosition(current_time, current_dow);
    }
//    if (!now.IsValid())
//    {
//        // Common Causes:
//        //    1) the battery on the device is low or even missing and the power line was disconnected
//        Serial.println("RTC lost confidence in the DateTime!");
//    }

    delay(1000);
}

#define countof(a) (sizeof(a) / sizeof(a[0]))

//will act as rotate()
void printDateTime(const RtcDateTime& dt)
{
    
    char datestring[20];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    Serial.print(datestring);
}

void declarePosition(int current_time, int current_day){
  //schedule for room 107
  //row format : {9:30 session, 11:00 session, 12:30 session}
//  int schedule[7][3] = {{0,4,2}, //monday
//                       {2,5,6}, //tuesday
//                       {9,1,3}, //wednesday
//                       {7,0,8}}; //thursday
                 
  String schedule[4][3] = {{"Responsive Web","Physical Computing","Tomorrow's Web"}, //monday
                           {"Physical Computing","Physical Computing","Vacant"}, //tuesday
                           {"Emerging Technologies","Creative Industries","Tomorrow's Web"}, //wednesday
                           {"Physical Computing","Creative Incubator","Creative Industries"}}; //thursday
  
  if(current_day == 1){ //monday
    switch(current_time){
      case 10:
        Serial.print(schedule[0][0]);
        Serial.println("MONDAY, SESSION 1");
        break;
      case 20:
        Serial.print(schedule[0][1]);
        Serial.println("MONDAY, SESSION 2"); 
        break;
      case 30:
        Serial.print(schedule[0][2]);
        Serial.println("MONDAY, SESSION 3");
        break;
      default:
        break;
      }
  }
  else if(current_day == 2){ //tuesday
    switch(current_time){
      case 10: 
        Serial.print(schedule[1][0]);
        Serial.println("TUESDAY, SESSION 1");
        break;
      case 20:
        Serial.print(schedule[1][1]);
        Serial.println("TUESDAY, SESSION 2"); 
        break;
      case 30:
        Serial.print(schedule[1][2]);
        Serial.println("TUESDAY, SESSION 3");
        break;
      default:
        break;
    }
  }
  else if(current_day == 3){ //wednesday
    switch(current_time){
      case 10:
        Serial.print(schedule[2][0]); 
        Serial.println("WEDNESDAY, SESSION 1");
        break;
      case 20:
        Serial.print(schedule[2][1]); 
        Serial.println("WEDNESDAY, SESSION 2"); 
        break;
      case 30:
        Serial.print(schedule[2][2]); 
        Serial.println("WEDNESDAY, SESSION 3");
        break;
      default:
        break;
    }
  }
  else if(current_day == 4){ //thursday
    switch(current_time){
      case 10:
        Serial.print(schedule[3][0]);  
        Serial.println("THURSDAY, SESSION 1");
        break;
      case 20:
        Serial.print(schedule[3][1]);
        Serial.println("THURSDAY, SESSION 2"); 
        break;
      case 30:
        Serial.print(schedule[3][2]);
        Serial.println("THURSDAY, SESSION 3");
        break;
      default:
        break;
    }
  }
}
