// CONNECTIONS:
// DS1302 CLK/SCLK --> 5
// DS1302 DAT/IO --> 4
// RTc Module Wiring:
// DS1302 RST/CE --> 2
// DS1302 VCC --> 3.3v - 5v
// DS1302 GND --> GND

// Stepper Motor Driver Wiring:
// Pin 8 to IN1 on the ULN2003 driver
// Pin 9 to IN2 on the ULN2003 driver
// Pin 10 to IN3 on the ULN2003 driver
// Pin 11 to IN4 on the ULN2003 driver

// Stepper Library
#include <Stepper.h>

// RTC Library
#include <ThreeWire.h>  
#include <RtcDS1302.h>

// Define number of steps per rotation:
const int stepsPerRevolution = 64;

ThreeWire myWire(4,5,2); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);

int current_pos = 0; 
int steps = 0;
float stepsPerAngle = 5.625;

void setup () 
{

    // Begin Serial communication at a baud rate of 9600:
    Serial.begin(9600);

    Serial.print("compiled: ");
    Serial.print(__DATE__);
    Serial.println(__TIME__);

    Rtc.Begin();
    
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    printDateTime(compiled);
    Serial.println();

    
    // Set the speed to 5 rpm:
    myStepper.setSpeed(60);
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
    if (!now.IsValid())
    {
        // Common Causes:
        //    1) the battery on the device is low or even missing and the power line was disconnected
        Serial.println("RTC lost confidence in the DateTime!");
    }

    delay(1000);
}

#define countof(a) (sizeof(a) / sizeof(a[0]))

//only for 
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
  int schedule[4][3] = {{0,36,108}, //monday
                       {72,144,0}, //tuesday
                       {252,180,144}, //wednesday
                       {324,0,216}}; //thursday
                 
//  String schedule[4][3] = {{"Responsive Web","Physical Computing","Tomorrow's Web"}, //monday
//                           {"Physical Computing","Physical Computing","Vacant"}, //tuesday
//                           {"Emerging Technologies","Creative Industries","Tomorrow's Web"}, //wednesday
//                           {"Physical Computing","Creative Incubator","Creative Industries"}}; //thursday
  
  if(current_day == 1){ //monday
    switch(current_time){
      case 10:
        rotate(schedule[0][0]);
        Serial.print(schedule[0][0]);
        Serial.println("MONDAY, SESSION 1");
        break;
      case 20:
        rotate(schedule[0][1]);
        Serial.print(schedule[0][1]);
        Serial.println("MONDAY, SESSION 2"); 
        break;
      case 30:
        rotate(schedule[0][2]);
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
        rotate(schedule[1][0]);
        Serial.print(schedule[1][0]);
        Serial.println("TUESDAY, SESSION 1");
        break;
      case 20:
        rotate(schedule[1][1]);
        Serial.print(schedule[1][1]);
        Serial.println("TUESDAY, SESSION 2"); 
        break;
      case 30:
        rotate(schedule[1][2]);
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
        rotate(schedule[2][0]);
        Serial.print(schedule[2][0]); 
        Serial.println("WEDNESDAY, SESSION 1");
        break;
      case 20:
        rotate(schedule[2][1]);
        Serial.print(schedule[2][1]); 
        Serial.println("WEDNESDAY, SESSION 2"); 
        break;
      case 30:
        rotate(schedule[2][2]);
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
        rotate(schedule[3][0]);
        Serial.print(schedule[3][0]);  
        Serial.println("THURSDAY, SESSION 1");
        break;
      case 20:
        rotate(schedule[3][1]);
        Serial.print(schedule[3][1]);
        Serial.println("THURSDAY, SESSION 2"); 
        break;
      case 30:
        rotate(schedule[3][2]);
        Serial.print(schedule[3][2]); 
        Serial.println("THURSDAY, SESSION 3");
        break;
      default:
        break;
    }
  }
}

void rotate(int next_pos){
  int n;
  if(current_pos != next_pos){
    Serial.print(current_pos);
    if(current_pos < next_pos){
      n = next_pos - current_pos;
      steps = n / stepsPerAngle;
      myStepper.step(steps);
      Serial.print(steps);
      Serial.println();
      delay(5000);
    }
    else if(current_pos > next_pos){
      n = current_pos - next_pos;
      steps = n / stepsPerAngle;
      if(next_pos == 0){
        n = current_pos;
      }
      myStepper.step(-steps);
      Serial.print(steps);
      Serial.println();
      delay(5000);
    }
    current_pos = next_pos;
  }
  delay(500);
}
