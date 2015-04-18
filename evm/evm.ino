#include <LiquidCrystal.h>
#include <Keypad.h>


#define LCD_LIGHT_PIN 11
#define party1  31
#define party2  33
#define party3  35
#define party4  37

#define p_lcd1  52
#define p_lcd2  53
#define p_lcd3  47
#define p_lcd4  46

#define l1 38
#define l2 44
#define l3 45
#define l4 49
const int buttonPin = 22;// the number of the pushbutton pin
const int buttonPin_end = 42;
const int ledPin =  24;      // the number of the LED pin
// variables will change:

unsigned int currentLcdLightOnTime = 0;
// For calculating the lcd light on time.
unsigned long lcdLightOn_StartMillis;

boolean isLcdLightOn;               // For checking push-button state.

int buttonState = 0;                // variable for reading the pushbutton status
int buttonState1 = 0;
int p;
int i;
LiquidCrystal lcd(50, 48, 36, 34, 32, 30);
/*
LCD key map **** for reference
pin 1 is GND *************** connected to GND
pin 2 is VDD or 5v ********* connected to 5v
pin 3 is VEE *************** connected to d5 or any adjustable voltage
pin 4 is RS **************** connected to 50
pin 5 is R/W *************** conneeted to GND
pin 6 is Enb *************** connected to 48
pin 7 is DB0 *************** connected to GND
pin 8 is DB1 *************** connected to GND
pin 9 is DB2 *************** connected to GND
pin 10 is DB3 ************** connected to GND
pin 11 is DB4 ************** connected to 36
pin 12 is DB5 ************** connected to 34
pin 13 is DB6 ************** connected to 32
pin 14 is DB7 ************** connected to 30
pin 15 is LED+ ************* connected to 4
pin 16 is LED- ************* connected to GND

*/
const byte ROWS = 4;                //four rows
const byte COLS = 4;                //fou columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int voterID[] = {93, 17, 106, 91, 25};
String voterName [] = {"Ifty", "Nandita", "Sayed", "Pritom", "Prioty"};
int vote_Cast [] = { 0, 0, 0, 0, 0};
int vote_counter[] = { 0, 0, 0, 0, 0};






int id_entry()
{
  Serial.println("id entry begin");
  //delay(1000);
  char key = 'e';
  int idNumber = 0;
  int temp = 0;

  while (1)
  { //http://www.arduino-hacks.com/converting-integer-to-character-vice-versa/

    Serial.println("loop begins");
    delay(10);

    key = keypad.getKey();
    if (key == 'D')
    {
      break;
    }
    if (key)
    {
      temp = key - 48; //char to int === does it really work? maisun.

      idNumber = idNumber * 10 + temp;
    }

    lcd.setCursor(0, 1);
    lcd.print(idNumber);
    //lcd.display();
  }
  Serial.print("ID Number  ");
  Serial.println(idNumber);
  return idNumber;

}









void id_check (int p)
{
  int  fake = 1;
  int q = p;
  i = 0;
  while (i <= 4)
  {
    if (q == voterID[i])
    { // voter name..... print korbe
      fake = 0;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(voterName[i]);
      lcd.setCursor(0, 1);
      lcd.print("is found");
      //lcd.display();
      delay(5000);
      Serial.println(vote_Cast[i]);
      if (vote_Cast[i] == 0)
      {
        vote_Cast[i] = 1;
        give_Vote();
        Serial.println(vote_Cast[i]);        // voteing option to p1,p2,....
        break;
      }
      else {//(vote_Cast[i] == 1) {

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Vote against this ID");
        lcd.setCursor(0, 1);
        lcd.print("has been casted");
        delay(4000);
        lcd.clear();
        break;
      }

    }


    i++;
  }
  if (fake)
  {
    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.print("you are not recognised");
    delay(5000);
    lcd.clear();
  }
  //  lcd.clear();
  // lcd.setCursor(0, 0);
  // lcd.print("Invalid ID");  //it might show to everyone. maisun
  // lcd.display();            // contact to rabbi
}







void give_Vote() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("press any party");//and hold any one of given option"); // too long string
  lcd.setCursor(0, 1);
  //lcd.print("until you see any further message:");
  //delay(5000); // for humans to catch

  // button initialize holo
  //  p1 = digitalRead(party1);
  //  p2 = digitalRead(party2);
  //  p3 = digitalRead(party3);
  //  p4 = digitalRead(party4);

  digitalWrite(p_lcd1, 0);
  digitalWrite(p_lcd2, 0);
  digitalWrite(p_lcd3, 0);
  digitalWrite(p_lcd4, 0);
  i = 1;
  while (i)
  {
    if (digitalRead(party1) == HIGH )
    {
      vote_counter[1] = vote_counter[1] + 1; //vote count korbe...
      //count_vote();
      digitalWrite(p_lcd1, HIGH);
      i = 0;
    }
    else if (digitalRead(party2) == HIGH)
    {
      vote_counter[2] = vote_counter[2] + 1;
      // count_vote();
      digitalWrite(p_lcd2, HIGH);
      i = 0;
    }
    else if (digitalRead(party3) == HIGH)
    {
      vote_counter[3] = vote_counter[3] + 1;
      digitalWrite(p_lcd3, HIGH);
      i = 0;
    }
    else if (digitalRead(party4) == HIGH)
    {
      vote_counter[4] = vote_counter[4] + 1;
      digitalWrite(p_lcd4, HIGH);
      i = 0;
    }
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Thank You.");
  lcd.setCursor(0, 1);
  lcd.print(vote_counter[1]);
  lcd.setCursor(4, 1);
  lcd.print(vote_counter[2]);
  lcd.setCursor(8, 1);
  lcd.print(vote_counter[3]);
  lcd.setCursor(12, 1);
  lcd.print(vote_counter[4]);
  delay(5000);

  //*****************************************************************************************************
  //digitalWrite(LCD_LIGHT_PIN, LOW);
  //*****************************************************************************************************
  digitalWrite(p_lcd1, 0);
  digitalWrite(p_lcd2, 0);
  digitalWrite(p_lcd3, 0);
  digitalWrite(p_lcd4, 0);
  lcd.clear();
  //break;
}






void count_vote() {
  //  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("p1");

  lcd.setCursor(4, 0);
  lcd.print("p2");

  lcd.setCursor(8, 0);
  lcd.print("p3");

  lcd.setCursor(12, 0);
  lcd.print("P4");

  lcd.setCursor(0, 1);
  lcd.print(vote_counter[1]);

  lcd.setCursor(4, 1);
  lcd.print(vote_counter[2]);

  lcd.setCursor(8, 1);
  lcd.print(vote_counter[3]);

  lcd.setCursor(12, 1);
  lcd.print(vote_counter[4]);
}

//function always above void setup()





void setup() {


  Serial.begin(9600);
  // initialize the LED pin as an output:
  lcd.begin(16, 2);
  lcd.clear();


  pinMode(ledPin, OUTPUT);     // initialize the pushbutton pin as an input:
  pinMode(LCD_LIGHT_PIN, OUTPUT);

  pinMode(p_lcd1, OUTPUT);
  pinMode(p_lcd2, OUTPUT);
  pinMode(p_lcd3, OUTPUT);
  pinMode(p_lcd4, OUTPUT);

  pinMode(buttonPin, INPUT);
  pinMode(10, OUTPUT);
  analogWrite(10, 20);
  pinMode(LCD_LIGHT_PIN, OUTPUT);


  //  pinMode(buttonPin_end, INPUT);
  //pinMode(6, OUTPUT);//************* check*****************


  digitalWrite(LCD_LIGHT_PIN, HIGH);
  isLcdLightOn = false;


  pinMode(party1, INPUT);
  pinMode(party2, INPUT);
  pinMode(party3, INPUT);
  pinMode(party4, INPUT);


  lcd.print("initialization done");
  delay(2000);
  digitalWrite(LCD_LIGHT_PIN, LOW);

}






void loop() {

  Serial.print("loop begun");
  // lcd.setCursor(0, 0);
  //lcd.clear();
  //lcd.print("Waiting for input");
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  //  buttonState1 = digitalRead(buttonPin_end);
  //u check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:

  if (digitalRead(buttonPin) == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    digitalWrite(LCD_LIGHT_PIN, HIGH);
    lcd.setCursor(0, 0);
    lcd.clear();  // First row.
    lcd.print("Welcome");
    lcd.setCursor(0, 1);
    lcd.print("to EVM");
    delay(1000);
    //lcd.display();
    delay(1000);
    isLcdLightOn = true;



    lcd.clear();
    lcd.setCursor(0, 0);  // First row.
    lcd.print("Enter Your ID:");
    //delay(1000);
    p = id_entry(); //****************check
    Serial.println(p);
    id_check(p);



  }

  // if (buttonState1 == HIGH) {
  count_vote();
  //}
  //    else{
  //
  //    lcd.clear();
  //    lcd.setCursor(0, 0);  // First row.
  //    lcd.print("Thank You");
  //    delay(5000);
  //    digitalWrite(ledPin,LOW);
  //    digitalWrite(LCD_LIGHT_PIN, LOW);
  //
  //}
}
