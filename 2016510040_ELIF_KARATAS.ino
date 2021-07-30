#include<LiquidCrystal.h>

#define button 9
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

int buttonState = 0; // button controls

int TIME_SCREEN_CLOCK = 2000;
int TIME_SCREEN_INFO = 1000;
String TIME_STRING = "2021.05.20 - 02:10:56"; // DATE AND TIME

int year = TIME_STRING.substring(0,4).toInt();
int month = TIME_STRING.substring(5,7).toInt();
int day = TIME_STRING.substring(8,10).toInt();
int hour1 = TIME_STRING.substring(13,15).toInt(); // hour1 for both of english and turkish screen calculating
int minute = TIME_STRING.substring(16,18).toInt();
int second = TIME_STRING.substring(19,21).toInt();

int count = 0; // counter for 2 seconds time screen clock

long hour2; // hour2 for english screen
int weekday; // day of weeks

String date_eng; // day of weeks in english
String date_turk; // day of weeks in turkish

void setup()
{
  Serial.begin(19200);
  lcd.begin(16, 2); 
  pinMode(button,INPUT); 
}

void timeEnglish(int day, int month, int year){
      hour2 = hour1 % 12; // mod12 for english screen
        lcd.setCursor(0,0);
        lcd.print("0");
        lcd.setCursor(1,0);
        second++;
      count++; // counter for 2 seconds time screen clock
        lcd.print(hour2);
        lcd.print(":");
        if(minute<10){
          lcd.setCursor(3,0);
          lcd.print("0");
        }
        lcd.print(minute);
        lcd.print(":");
      if(second<10){
          lcd.setCursor(6,0);
          lcd.print("0");
        }
        lcd.print(second);
      if(hour1 < 12){
           lcd.setCursor(9,0);
           lcd.print(" AM");
        }
        else{
           lcd.setCursor(9,0);
           lcd.print(" PM");
        }
        if(hour1 > 12){
           hour2 = hour2 % 12;
        }
        lcd.setCursor(13,0);
        lcd.print("ENG");
  
         if(second==59){ // if second is 59, it will update to 0
          second = 0;
          lcd.setCursor(6,0);
          minute++;
        }
        if(minute == 60){ // if minute is 60, it will update to 0
          minute = 0;
          lcd.setCursor(3,0);
          hour1++;
        }
      if(hour1 == 24){ // if hour1 is 24, it will update to 0
          hour1 = 0;
          lcd.setCursor(0,0);
          day++;
        }
        if(day>30){ // if day is more than 30, than increase the month
          month++;
        }
        if(month>12){ // if month is more than 12, than increase the year
          year++;
        }
}

void timeTurkish(int day, int month, int year){
      lcd.setCursor(0,0);
        second++; // second increase
      count++; // counter for 2 seconds time screen clock 
      if(hour1<10){ // if hour1 is less than 10, than add 0 to start cursor
          lcd.setCursor(0,0);
          lcd.print("0");
        }
        lcd.print(hour1);
        lcd.print(":");
        if(minute<10){
          lcd.setCursor(3,0);
          lcd.print("0");
        }
        lcd.print(minute);
        lcd.print(":");
      if(second<10){
          lcd.setCursor(6,0);
          lcd.print("0");
        }
        lcd.print(second);      
        lcd.setCursor(13,0);
        lcd.print("TUR");
  
        if(second==59){
          second = 0;
          lcd.setCursor(6,0);
          minute++;
        }
        if(minute == 60){
          minute = 0;
          lcd.setCursor(3,0);
          hour1++;
        }
      if(hour1 == 24){
          hour1 = 0;
          lcd.setCursor(0,0);
          day++;
        }
        if(day>30){
          month++;
        }
        if(month>12){
          year++;
        }
}

int dayofweek(int day, int month, int year)  
{  
  // it is calculating day of weeks
  // 0 represents sunday
   weekday  = (day += month < 3 ? year-- : year - 2, 23*month/9 + day + 4 + year/4- year/100 + year/400)%7;
}

void date(int day, int month, int year){
  // it prints date with day, month, year
  if(day<10){
    lcd.setCursor(0,1);
    lcd.print("0");
    lcd.setCursor(1,1);
    lcd.print(day);
  }
  else{
    lcd.setCursor(0,1);
    lcd.print(day);
  }
  lcd.setCursor(2,1);
  lcd.print(":");
  if(month<10){
    lcd.setCursor(3,1);
    lcd.print("0");
    lcd.setCursor(4,1);
    lcd.print(month);
  }
  else{
    lcd.setCursor(3,1);
    lcd.print(month);
  }
  lcd.setCursor(5,1);
  lcd.print(":");
  lcd.setCursor(6,1);
  lcd.print(year);
}

int dayofTurkish(int weekday)  
{  
  // days with turkish names
  if(weekday == 0){
      date_turk = "PAZ";
  }
  if(weekday == 1){
        date_turk = "PZT";
  }
  if(weekday == 2){
        date_turk = "SAL";
  }
  if(weekday == 3){
        date_turk = "CAR";
  }
  if(weekday == 4){
        date_turk = "PER";
  }
  if(weekday == 5){
        date_turk = "CUM";
  }
  if(weekday == 6){
        date_turk = "CMT";
  }
  lcd.setCursor(13,1);
  lcd.print(date_turk);
}

int dayofEnglish(int weekday)  
{  
  // days with english names
  if(weekday == 0){
        date_eng = "SUN";
  }
  if(weekday == 1){
          date_eng = "MON";
  }
  if(weekday == 2){
          date_eng = "TUE";
  }
  if(weekday == 3){
          date_eng = "WED";
  }
  if(weekday == 4){
          date_eng = "THU";
  }
  if(weekday == 5){
          date_eng = "FRI";
  }
  if(weekday == 6){
          date_eng = "SAT";
  }
  lcd.setCursor(13,1);
  lcd.print(date_eng);
}

void loop()
{
  // if button is pressed, than turn into turkish screen
  if(digitalRead(button) && buttonState == 0){ // if the button is pressed in starting of the program (button state is 0)
    buttonState=1; // beginning of the first operation, buton state is 1
    while(buttonState == 1){ // contiunity...
      lcd.clear();
      dayofweek(day,month,year);
      dayofTurkish(weekday); 
      timeTurkish(day,month,year);  
      date(day,month,year);
      delay(TIME_SCREEN_CLOCK);   
      if(count>=2 && count%2 == 0){ // 2 seconds waiting
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("SA:DA:SN 24H DIL");
        lcd.setCursor(0,1);
        lcd.print("GG:AA:YYYY   GUN");
      }
      delay(TIME_SCREEN_INFO);
      if(digitalRead(button)&& buttonState == 1){ // if the button is pressed and program is in first operation
          buttonState = 0; // button state is 0
          break; // leave the first operation, break from while
      }
    }
  }
  // if button is pressed, than turn into english screen
  else
    lcd.clear();
    dayofweek(day,month,year);
    dayofEnglish(weekday); 
    timeEnglish(day,month,year);  
    date(day,month,year);
    delay(TIME_SCREEN_CLOCK);   
    if(count>=2 && count%2 == 0){ // 2 seconds waiting
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("HH:MM:SS 12H LNG");
      lcd.setCursor(0,1);
      lcd.print("DD:MM:YYYY   DOW");
    }
    delay(TIME_SCREEN_INFO);
}

// references: https://stackoverflow.com/questions/7910339/how-to-convert-int-to-string-on-arduino
