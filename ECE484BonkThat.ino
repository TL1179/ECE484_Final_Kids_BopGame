
//LCD files and PINs
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

//Buzzer PIN
int buzzer = 11;

//Initialize Buttons and LED PINS
  //Red
const int ButtonPinRed = 3;
const int ledPinRed = 8;
  //Yellow
const int ButtonPinYellow = 7;
const int ledPinYellow = 9;
  //Green
const int ButtonPinGreen = 6;
const int ledPinGreen = 10;
  //Blue
const int ButtonPinBlue = 5;
const int ledPinBlue = 12;

//Reset PIN
int Reset = 4;

//Variables used
int count = 0;
int setting = 2000;
int StSt = 0;




void setup() {

  //Reset coding
  digitalWrite(Reset, HIGH);
  pinMode(Reset, OUTPUT);


  //Start the LCD up
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.print("Press button");
  lcd.setCursor(0, 1);
  lcd.print("to start");

  

  //Waits for one of the buttons to be pressed to continue through the game
  while(StSt == 0){
    if (millis()>30000) {
      digitalWrite(Reset,LOW);
    }
    
    int readingRed = digitalRead(ButtonPinRed);
    int readingYellow = digitalRead(ButtonPinYellow);
    int readingGreen = digitalRead(ButtonPinGreen);
    int readingBlue = digitalRead(ButtonPinBlue);
    if (readingRed == 1 || readingYellow == 1 || readingGreen == 1 || readingBlue == 1) {
      StSt = 1;
    }
  }

  
  lcd.clear();
  lcd.print("Bonk That!");
  lcd.setCursor(0, 1);
  lcd.print("Are you Ready!");
  delay(2000);

  //PIN assigns
    //Red button and led
  pinMode(ButtonPinRed, INPUT);
  pinMode(ledPinRed, OUTPUT);
    //Yellow button and led
  pinMode(ButtonPinYellow, INPUT);
  pinMode(ledPinYellow, OUTPUT);
    //Green button and led
  pinMode(ButtonPinGreen, INPUT);
  pinMode(ledPinGreen, OUTPUT);
    //Blue button and led
  pinMode(ButtonPinBlue, INPUT);
  pinMode(ledPinBlue, OUTPUT);
  
  lcd.clear();
  lcd.print("Score: ");
  lcd.print(count);
  lcd.setCursor(0, 1);
  lcd.print("G0!");
  delay(200);

  //RNG seed
  randomSeed(analogRead(0));
  
  //The indication of started game with 2 flashes
  digitalWrite(ledPinRed, HIGH);
  digitalWrite(ledPinYellow, HIGH);
  digitalWrite(ledPinGreen, HIGH);
  digitalWrite(ledPinBlue, HIGH);
  delay(100);
  digitalWrite(ledPinRed, LOW);
  digitalWrite(ledPinYellow, LOW);
  digitalWrite(ledPinGreen, LOW);
  digitalWrite(ledPinBlue, LOW);
  delay(100);
  digitalWrite(ledPinRed, HIGH);
  digitalWrite(ledPinYellow, HIGH);
  digitalWrite(ledPinGreen, HIGH);
  digitalWrite(ledPinBlue, HIGH);
  delay(100);
  digitalWrite(ledPinRed, LOW);
  digitalWrite(ledPinYellow, LOW);
  digitalWrite(ledPinGreen, LOW);
  digitalWrite(ledPinBlue, LOW);
  delay(500);

  //Serial.begin(9600);
  
  //count = 0;
  //setting = 2000;
}

void loop() {

  
  int readingRed = digitalRead(ButtonPinRed);
  int readingYellow = digitalRead(ButtonPinYellow);
  int readingGreen = digitalRead(ButtonPinGreen);
  int readingBlue = digitalRead(ButtonPinBlue);

  //determines which pseudo random number is picked out of the 4 options
  long randNum = random(1,400);
  int number = randNum%4;
  //Serial.println(number);
  //Serial.println(count);


    //increaseing difficlty 
    //when button pressed correct, then timer for next round decreases by 0.1 seconds
    if (count > 0) {
      setting = setting - 100;
    }
  


 
  switch (number) {
    case 0: {
      digitalWrite(ledPinRed, HIGH);
      tone (buzzer, 200);
      lcd.setCursor(0, 1);
      lcd.print("Bep It!");
      int testRed = 0;
      int buzzRed = millis();
      while (testRed != 1) {
        
        if (millis() - buzzRed > setting) {
          //Serial.println(millis());
          //Serial.println(buzzRed);
          noTone(buzzer);
          lcd.clear();
          lcd.print("Too slow, you");
          lcd.setCursor(0, 1);
          lcd.print("had ");
          float timer = setting/1000.0;
          //Serial.println(setting);
          //Serial.println(timer);
          lcd.print(timer, 1);
          lcd.print(" seconds!");
          delay(1000);
          digitalWrite(Reset,LOW);
        }
        
        readingRed = digitalRead(ButtonPinRed);
        readingYellow = digitalRead(ButtonPinYellow);
        readingGreen = digitalRead(ButtonPinGreen);
        readingBlue = digitalRead(ButtonPinBlue);
        //Serial.println(readingRed);
        if (readingRed == 1) {
          noTone(buzzer);
          //Serial.println("made it in if");
          while (millis() - buzzRed < setting) {
            readingRed = digitalRead(ButtonPinRed);
            readingYellow = digitalRead(ButtonPinYellow);
            readingGreen = digitalRead(ButtonPinGreen);
            readingBlue = digitalRead(ButtonPinBlue);
            //Serial.println("made it in while");
            if (readingYellow == 1 || readingGreen == 1 || readingBlue == 1) {
              lcd.clear();
              lcd.print("Extra Buttons!");
              delay(500);
              digitalWrite(Reset,LOW);
            }
          }
          
          //Serial.println("success red");
          testRed = 1;
          //Serial.println(millis());
          count = count + 1;
          lcd.clear();
          lcd.print("Score: ");
          lcd.print(count);
        }
        if (readingYellow == 1) {
          //Serial.println("fail yellow");
          lcd.clear();
          lcd.print("Wrong One!");
          delay(500);
          digitalWrite(Reset,LOW);
        }
        if (readingGreen == 1) {
          //Serial.println("fail green");
          lcd.clear();
          lcd.print("Wrong One!");
          delay(500);
          digitalWrite(Reset,LOW);
        }
        if (readingBlue == 1) {
          //Serial.println("fail blue");
          lcd.clear();
          lcd.print("Wrong One!");
          delay(500);
          digitalWrite(Reset,LOW);
        }
        
      }
      noTone(buzzer);
      if (millis() - buzzRed < setting) {
          delay(setting - (millis() - buzzRed));
      }
      digitalWrite(ledPinRed, LOW);
    } break;

    /////////////////////////////////////////////////
    
    case 1: {
      digitalWrite(ledPinYellow, HIGH);
      tone (buzzer, 400);
      lcd.setCursor(0, 1);
      lcd.print("Bim It!");
      int testYellow = 0;
      int buzzYellow = millis();
      while (testYellow != 1) {
        
        if (millis() - buzzYellow > setting) {
          //Serial.println(millis());
          //Serial.println(buzzYellow);
          noTone(buzzer);
          lcd.clear();
          lcd.print("Too slow, you");
          lcd.setCursor(0, 1);
          lcd.print("had ");
          float timer = setting/1000.0;
          //Serial.println(setting);
          //Serial.println(timer);
          lcd.print(timer, 1);
          lcd.print(" seconds!");
          delay(1000);
          digitalWrite(Reset,LOW);
        }
        
        readingRed = digitalRead(ButtonPinRed);
        readingYellow = digitalRead(ButtonPinYellow);
        readingGreen = digitalRead(ButtonPinGreen);
        readingBlue = digitalRead(ButtonPinBlue);
        //Serial.println(readingYellow);
        if (readingRed == 1) {
          //Serial.println("fail red");
          lcd.clear();
          lcd.print("Wrong One!");
          delay(500);
          digitalWrite(Reset,LOW);
        }
        if (readingYellow == 1) {
          //Serial.println("success yellow");
          noTone(buzzer);
          //Serial.println("made it in if");
          while (millis() - buzzYellow < setting) {
            readingRed = digitalRead(ButtonPinRed);
            readingYellow = digitalRead(ButtonPinYellow);
            readingGreen = digitalRead(ButtonPinGreen);
            readingBlue = digitalRead(ButtonPinBlue);
            //Serial.println("made it in while");
            if (readingRed == 1 || readingGreen == 1 || readingBlue == 1) {
              lcd.clear();
              lcd.print("Extra Buttons!");
              delay(500);
              digitalWrite(Reset,LOW);
            }
          }
          testYellow = 1;
          //Serial.println(millis());
          count = count + 1;
          lcd.clear();
          lcd.print("Score: ");
          lcd.print(count);
        }
        if (readingGreen == 1) {
          //Serial.println("fail green");
          lcd.clear();
          lcd.print("Wrong One!");
          delay(500);
          digitalWrite(Reset,LOW);
        }
        if (readingBlue == 1) {
          //Serial.println("fail blue");
          lcd.clear();
          lcd.print("Wrong One!");
          delay(500);
          digitalWrite(Reset,LOW);
        }
        
      }
      noTone(buzzer);
      if (millis() - buzzYellow < setting) {
          delay(setting - (millis() - buzzYellow));
      }
      digitalWrite(ledPinYellow, LOW);
    } break;

    /////////////////////////////////////////////////

    case 2: {
      digitalWrite(ledPinGreen, HIGH);
      tone (buzzer, 600);
      lcd.setCursor(0, 1);
      lcd.print("Bonk It!");
      int testGreen = 0;
      int buzzGreen = millis();
      while (testGreen != 1) {
        //Serial.println("into Green loop");

        if (millis() - buzzGreen > setting) {
          //Serial.println(millis());
          //Serial.println(buzzGreen);
          noTone(buzzer);
          lcd.clear();
          lcd.print("Too slow, you");
          lcd.setCursor(0, 1);
          lcd.print("had ");
          float timer = setting/1000.0;
          //Serial.println(setting);
          //Serial.println(timer);
          lcd.print(timer, 1);
          lcd.print(" seconds!");
          delay(1000);
          digitalWrite(Reset,LOW);
        }
        
        readingRed = digitalRead(ButtonPinRed);
        readingYellow = digitalRead(ButtonPinYellow);
        readingGreen = digitalRead(ButtonPinGreen);
        readingBlue = digitalRead(ButtonPinBlue);
        //Serial.println(readingGreen);
        if (readingRed == 1) {
          //Serial.println("fail red");
          lcd.clear();
          lcd.print("Wrong One!");
          delay(500);
          digitalWrite(Reset,LOW);
        }
        if (readingYellow == 1) {
          //Serial.println("fail yellow");
          lcd.clear();
          lcd.print("Wrong One!");
          delay(500);
          digitalWrite(Reset,LOW);
        }
        if (readingGreen == 1) {
          //Serial.println("success green");
          noTone(buzzer);
          //Serial.println("made it in if");
          while (millis() - buzzGreen < setting) {
            readingRed = digitalRead(ButtonPinRed);
            readingYellow = digitalRead(ButtonPinYellow);
            readingGreen = digitalRead(ButtonPinGreen);
            readingBlue = digitalRead(ButtonPinBlue);
            //Serial.println("made it in while");
            if (readingRed == 1 || readingYellow == 1 || readingBlue == 1) {
              lcd.clear();
              lcd.print("Extra Buttons!");
              delay(500);
              digitalWrite(Reset,LOW);
            }
          }
          testGreen = 1;
          //Serial.println(millis());
          count = count + 1;
          lcd.clear();
          lcd.print("Score: ");
          lcd.print(count);
          
        }
      }
      noTone(buzzer);

      if (millis() - buzzGreen < setting) {
          delay(setting - (millis() - buzzGreen));
      }
      digitalWrite(ledPinGreen, LOW);
      
    } break;

    ////////////////////////////////////////////////////

    case 3: {
      digitalWrite(ledPinBlue, HIGH);
      tone (buzzer, 800);
      lcd.setCursor(0, 1);
      lcd.print("Baf It!");
      int testBlue = 0;
      int buzzBlue = millis();
      while (testBlue != 1) {
        
        if (millis() - buzzBlue > setting) {
          //Serial.println(millis());
          //Serial.println(buzzBlue);
          noTone(buzzer);
          lcd.clear();
          lcd.print("Too slow, you");
          lcd.setCursor(0, 1);
          lcd.print("had ");
          float timer = setting/1000.0;
          //Serial.println(setting);
          //Serial.println(timer);
          lcd.print(timer, 1);
          lcd.print(" seconds!");
          delay(1000);
          digitalWrite(Reset,LOW);
        }
        
        readingRed = digitalRead(ButtonPinRed);
        readingYellow = digitalRead(ButtonPinYellow);
        readingGreen = digitalRead(ButtonPinGreen);
        readingBlue = digitalRead(ButtonPinBlue);
        //Serial.println(readingGreen);
        if (readingRed == 1) {
          //Serial.println("fail red");
          lcd.clear();
          lcd.print("Wrong One!");
          delay(500);
          digitalWrite(Reset,LOW);
        }
        if (readingYellow == 1) {
          //Serial.println("fail yellow");
          lcd.clear();
          lcd.print("Wrong One!");
          delay(500);
          digitalWrite(Reset,LOW);
        }
        if (readingGreen == 1) {
          //Serial.println("fail green");
          lcd.clear();
          lcd.print("Wrong One!");
          delay(500);
          digitalWrite(Reset,LOW);
        }
        if (readingBlue == 1) {
          //Serial.println("success blue");
          noTone(buzzer);
          //Serial.println("made it in if");
          while (millis() - buzzBlue < setting) {
            readingRed = digitalRead(ButtonPinRed);
            readingYellow = digitalRead(ButtonPinYellow);
            readingGreen = digitalRead(ButtonPinGreen);
            readingBlue = digitalRead(ButtonPinBlue);
            //Serial.println("made it in while");
            if (readingRed == 1 || readingYellow == 1 || readingGreen == 1) {
              lcd.clear();
              lcd.print("Extra Buttons!");
              delay(500);
              digitalWrite(Reset,LOW);
            }
          }
          testBlue = 1;
          //Serial.println(millis());
          count = count + 1;
          lcd.clear();
          lcd.print("Score: ");
          lcd.print(count);
        }
      }
      noTone(buzzer);
      if (millis() - buzzBlue < setting) {
          delay(setting - (millis() - buzzBlue));
      }
      digitalWrite(ledPinBlue, LOW);
      
    } break;
  }


  //delay(200);
  digitalWrite(ledPinRed, LOW);
  digitalWrite(ledPinYellow, LOW);
  digitalWrite(ledPinGreen, LOW);
  
}
