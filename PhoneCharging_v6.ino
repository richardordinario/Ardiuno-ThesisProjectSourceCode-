#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <Wire.h>
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <Keypad.h>

SoftwareSerial mySerial(11, 12);
LiquidCrystal_I2C lcd(0x27, 20, 4);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'}, 
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {3, 4, 5, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 8, 9, 10}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

#define COIN_PIN 2
int d1_penalty = 0;
int menu = 0;
int n = 0, i = 0;
int inputCol = 15;
int inputCol2 = 7;
int perminute = 0;
//-----------------------------------------------------------
int a = 0;    //---------------------------------           //
int b = 0;    //----------------------------------          //
int c = 0;    //-----------variable sa total income ng machine
int d = 0;    //--------------------------------            //
uint8_t n1 = 21;//-----------------------                   //
uint8_t n2 = 22;                                            //
//-----------------------------------------------------------

int d1A=0,d1B=0,d1C=0,d1D=0;
uint8_t d1n1=27; 
uint8_t d1n2=28;

int code1 = 0;
int code2 = 0;
int code3 = 0;
int code4 = 0;
uint8_t code_add1 = 23;
uint8_t code_add2 = 24;
uint8_t code_add3 = 25;
uint8_t code_add4 = 26; 

int buzz = 52;
int insertCoin = 0;
int money = 0;
int dnum = 0;
int tempo_add;
int fingerprint_status = 0;
volatile int pulses = 0;
volatile long timeLastPulse = 0;
const int coinInt = 0;

uint8_t id = 0;

int d1_chargingState = 0;
int d2_chargingState = 0;       // State ng bawat door
int d3_chargingState = 0;       // na may charging time
int d4_chargingState = 0;
int d5_chargingState = 0;
int d6_chargingState = 0;
int d7_chargingState = 0;
int d8_chargingState = 0;
int d9_chargingState = 0;
int d10_chargingState = 0;

int d1_timerSeconds = 0;
int d2_timerSeconds = 0;
int d3_timerSeconds = 0;        // total timer ng bawat door
int d4_timerSeconds = 0;        // kung saan pwedeng madagdagan at mabawasan
int d5_timerSeconds = 0;
int d6_timerSeconds = 0;
int d7_timerSeconds = 0;
int d8_timerSeconds = 0;
int d9_timerSeconds = 0;
int d10_timerSeconds = 0;



//---------------------------------------TIMER PENALTY VAR NG BAWAT DOOR-------------------//
int sec_d1,minu_d1,hr_d1 = 0;
int sec_d2,minu_d2,hr_d2 = 0;
int sec_d3,minu_d3,hr_d3 = 0;
int sec_d4,minu_d4,hr_d4 = 0;
int sec_d5,minu_d5,hr_d5 = 0;
int sec_d6,minu_d6,hr_d6 = 0;
int sec_d7,minu_d7,hr_d7 = 0;
int sec_d8,minu_d8,hr_d8 = 0;
int sec_d9,minu_d9,hr_d9 = 0;
int sec_d10,minu_d10,hr_d10 = 0;

int sub6sec1=0,sub6sec2=0,count_6=0,penalty_6=0;
int sub7sec1=0,sub7sec2=0,count_7=0,penalty_7=0;
int sub8sec1=0,sub8sec2=0,count_8=0,penalty_8=0;
int sub9sec1=0,sub9sec2=0,count_9=0,penalty_9=0;
int sub10sec1=0,sub10sec2=0,count_10=0,penalty_10=0;

int sub1sec1=0,sub1sec2=0,count_1=0,penalty_1=0;
int sub2sec1=0,sub2sec2=0,count_2=0,penalty_2=0;
int sub3sec1=0,sub3sec2=0,count_3=0,penalty_3=0;
int sub4sec1=0,sub4sec2=0,count_4=0,penalty_4=0;
int sub5sec1=0,sub5sec2=0,count_5=0,penalty_5=0;

//---------------------------------------------------------------------------------//
unsigned long d1_time_now = 0;
unsigned long d2_time_now = 0;
unsigned long d3_time_now = 0;
unsigned long d4_time_now = 0;             //kasama sa timer ng bawat door
unsigned long d5_time_now = 0;             // para magfunction
unsigned long d6_time_now = 0;
unsigned long d7_time_now = 0;
unsigned long d8_time_now = 0;
unsigned long d9_time_now = 0;
unsigned long d10_time_now = 0;


int display_door1 = 0;
int display_door2 = 0;
int display_door3 = 0;
int display_door4 = 0;              //display ng timer ng every door
int display_door5 = 0;              //
int display_door6 = 0;
int display_door7 = 0;
int display_door8 = 0;
int display_door9 = 0;
int display_door10 = 0;

uint8_t door1_id_add = 11;         //address ng bawat door nasinisave sa eeprom
uint8_t door2_id_add = 12;
uint8_t door3_id_add = 13;
uint8_t door4_id_add = 14;
uint8_t door5_id_add = 15;
uint8_t door6_id_add = 16;
uint8_t door7_id_add = 17;
uint8_t door8_id_add = 18;
uint8_t door9_id_add = 19;
uint8_t door10_id_add = 20;

int current_d1 = 32;              // pin number ng relay charger-----------------
int current_d2 = 33;              // for power---------------------------
int current_d3 = 34;            
int current_d4 = 35;
int current_d5 = 36;
int current_d6 = 37;
int current_d7 = 38;
int current_d8 = 39;
int current_d9 = 40;
int current_d10 = 41;

int led1 = 42;                    //pin ng led for charging indicator-------
int led2 = 43;
int led3 = 44;
int led4 = 45;                    //--------------------------------------
int led5 = 46;
int led6 = 47;
int led7 = 48;
int led8 = 49;
int led9 = 50;
int led10 = 51;

int ledState1 = LOW;
int ledState2 = LOW;
int ledState3 = LOW;
int ledState4 = LOW;
int ledState5 = LOW;
int ledState6 = LOW;
int ledState7 = LOW;
int ledState8 = LOW;
int ledState9 = LOW;
int ledState10 = LOW;


int door1state = A1;        //pin ng lightsensor
int door2state = A2;
int door3state = A3;
int door4state = A4;
int door5state = A5;
int door6state = A6;
int door7state = A7;
int door8state = A8;
int door9state = A9;
int door10state = A10;

int d1state = 0;            //sa lightsensor
int d2state = 0;
int d3state = 0;
int d4state = 0;
int d5state = 0;
int d6state = 0;
int d7state = 0;
int d8state = 0;
int d9state = 0;
int d10state = 0;

int state1 = 0;            // sa condition ng lightsensor
int state2 = 0;
int state3 = 0;
int state4 = 0;
int state5 = 0;
int state6 = 0;
int state7 = 0;
int state8 = 0;
int state9 = 0;
int state10 = 0;

int insert_state = 0;

int door_locker1 = 22;            // locker pin ng bawat door
int door_locker2 = 23;            // ng relay
int door_locker3 = 24;
int door_locker4 = 25;
int door_locker5 = 26;
int door_locker6 = 27;
int door_locker7 = 28;
int door_locker8 = 29;
int door_locker9 = 30;
int door_locker10 = 31;

char input[2];
char input_passcode[3];

void coinISR()
{
  pulses++;
  timeLastPulse = millis();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  startPage();
  
  tone(buzz,1000,500);
  
  pinMode(current_d1, OUTPUT);
  pinMode(current_d2, OUTPUT);
  pinMode(current_d3, OUTPUT);
  pinMode(current_d4, OUTPUT);
  pinMode(current_d5, OUTPUT);
  pinMode(current_d6, OUTPUT);
  pinMode(current_d7, OUTPUT);
  pinMode(current_d8, OUTPUT);
  pinMode(current_d9, OUTPUT);
  pinMode(current_d10, OUTPUT);
  
  digitalWrite(current_d1, HIGH);
  digitalWrite(current_d2, HIGH);
  digitalWrite(current_d3, HIGH);
  digitalWrite(current_d4, HIGH);
  digitalWrite(current_d5, HIGH);
  digitalWrite(current_d6, HIGH);
  digitalWrite(current_d7, HIGH);
  digitalWrite(current_d8, HIGH);
  digitalWrite(current_d9, HIGH);
  digitalWrite(current_d10, HIGH);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(led8, OUTPUT);
  pinMode(led9, OUTPUT);
  pinMode(led10, OUTPUT);

  pinMode(door_locker1, OUTPUT);
  pinMode(door_locker2, OUTPUT);
  pinMode(door_locker3, OUTPUT);
  pinMode(door_locker4, OUTPUT);
  pinMode(door_locker5, OUTPUT);
  pinMode(door_locker6, OUTPUT);
  pinMode(door_locker7, OUTPUT);
  pinMode(door_locker8, OUTPUT);
  pinMode(door_locker9, OUTPUT);
  pinMode(door_locker10, OUTPUT);
  
  digitalWrite(door_locker1, HIGH);
  digitalWrite(door_locker2, HIGH);
  digitalWrite(door_locker3, HIGH);
  digitalWrite(door_locker4, HIGH); 
  digitalWrite(door_locker5, HIGH);
  digitalWrite(door_locker6, HIGH);
  digitalWrite(door_locker7, HIGH);
  digitalWrite(door_locker8, HIGH);
  digitalWrite(door_locker9, HIGH);
  digitalWrite(door_locker10, HIGH);

  pinMode (COIN_PIN, INPUT_PULLUP);
  attachInterrupt(coinInt, coinISR, RISING);  // COIN wire connected to D2;


  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  Serial.println("\n\nAdafruit Fingerprint sensor enrollment");

  // set the data rate for the sensor serial port
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) {
      delay(1);
    }
  }

  finger.getTemplateCount();
  Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  //EEPROM.write(door6_id_add, 0);
  //EEPROM.write(door5_id_add, 0);
  //EEPROM.write(door4_id_add, 0);
  //EEPROM.write(door3_id_add, 0);
  //EEPROM.write(door2_id_add, 0);
  //EEPROM.write(door1_id_add, 0);
  //EEPROM.write(n1,0);
  //EEPROM.write(n2,0);
  //EEPROM.write(code_add1,0);
  //EEPROM.write(code_add2,0);
  //EEPROM.write(code_add3,0);
  //EEPROM.write(code_add4,0);
  //EEPROM.write(d1n1,0);
  //EEPROM.write(d1n2,0);
}

void loop() {
  // put your main code here, to run repeatedly:
  //EEPROM.write(door1_id_add,0);

  chargingDoor();
  readKey();
  coinAcceptor();
  doorstat();
}
//-----------------------------------------------------------------------------------------------------------------------
// ------------------------------------------- Dito start lahat ng function ---------------------------------------------
void readKey()
{
  char key = keypad.getKey();
  if (key)
  {
    switch (key)
    {
      case '0':
        if (menu == 1) {
          lcd.setCursor(inputCol = inputCol + 1, 1);
          lcd.print('0');
          if (n > 1) {
            lcd.clear();
            countInput();
          } else {
            input[n] = '0';
            n = n + 1;
          }
        } else if (menu == 4) {
          lcd.setCursor(inputCol = inputCol + 1, 1);
          lcd.print('0');
          if (n > 1) {
            lcd.clear();
            countInput();
          } else {
            input[n] = '0';
            n = n + 1;
          }
        }else if (menu== 13) {
          lcd.setCursor(inputCol = inputCol + 1, 1);
          lcd.print('0');
          if (n > 1) {
            lcd.clear();
            countInput2();
          } else {
            input[n] = '0';
            n = n + 1;
          }
        }
        else if(menu == 7){
          lcd.setCursor(inputCol2 = inputCol2 + 1, 2);
          lcd.print('*');
          if (n > 3) {
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    INVALID INPUT   ");
            delay(1000);
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    PLEASE WAIT...  ");
            delay(1000);
            reset();
          } else {
            input_passcode[n] = '0';
            n = n + 1;
          }
        }else if(menu == 9){
          lcd.setCursor(inputCol2 = inputCol2 + 1, 2);
          lcd.print('*');
          if (n > 3) {
            n=0;
            inputCol2 = 7;
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    INVALID INPUT   ");
            delay(1000);
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    PLEASE WAIT...  ");
            delay(1000);
            lcd.clear();
            change_pass();
          } else {
            input_passcode[n] = '0';
            n = n + 1;
          }
        }
        break;
      case '1':
        if (menu == 1) {
          lcd.setCursor(inputCol = inputCol + 1, 1);
          lcd.print('1');
          if (n > 1) {
            lcd.clear();
            countInput();
          } else {
            input[n] = '1';
            n = n + 1;
          }
        } else if (menu == 4) {
          lcd.setCursor(inputCol = inputCol + 1, 1);
          lcd.print('1');
          if (n > 1) {
            lcd.clear();
            countInput();
          } else {
            input[n] = '1';
            n = n + 1;
          }
        }else if (menu== 13) {
          lcd.setCursor(inputCol = inputCol + 1, 1);
          lcd.print('1');
          if (n > 1) {
            lcd.clear();
            countInput2();
          } else {
            input[n] = '1';
            n = n + 1;
          }
        }
        else if(menu == 7){
          lcd.setCursor(inputCol2 = inputCol2 + 1, 2);
          lcd.print('*');
          if (n > 3) {
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    INVALID INPUT   ");
            delay(1000);
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    PLEASE WAIT...  ");
            delay(1000);
            reset();
          } else {
            input_passcode[n] = '1';
            n = n + 1;
          }
        }else if(menu == 9){
          lcd.setCursor(inputCol2 = inputCol2 + 1, 2);
          lcd.print('*');
          if (n > 3) {
            n=0;
            inputCol2=7;
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    INVALID INPUT   ");
            delay(1000);
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    PLEASE WAIT...  ");
            delay(1000);
            lcd.clear();
            change_pass();
          } else {
            input_passcode[n] = '1';
            n = n + 1;
          }
        }
        break;
      case '2':
        if (menu == 1) {
          lcd.setCursor(inputCol = inputCol + 1, 1);
          lcd.print('2');
          if (n > 1) {
            lcd.clear();
            countInput();
          } else {
            input[n] = '2';
            n = n + 1;
          }
        } else if (menu == 4) {
          lcd.setCursor(inputCol = inputCol + 1, 1);
          lcd.print('2');
          if (n > 1) {
            lcd.clear();
            countInput();
          } else {
            input[n] = '2';
            n = n + 1;
          }
        }else if (menu== 13) {
          lcd.setCursor(inputCol = inputCol + 1, 1);
          lcd.print('2');
          if (n > 1) {
            lcd.clear();
            countInput2();
          } else {
            input[n] = '2';
            n = n + 1;
          }
        }
        else if(menu == 7){
          lcd.setCursor(inputCol2 = inputCol2 + 1, 2);
          lcd.print('*');
          if (n > 3) {
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    INVALID INPUT   ");
            delay(1000);
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    PLEASE WAIT...  ");
            delay(1000);
            reset();
          } else {
            input_passcode[n] = '2';
            n = n + 1;
          }
        }else if(menu == 9){
          lcd.setCursor(inputCol2 = inputCol2 + 1, 2);
          lcd.print('*');
          if (n > 3) {
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    INVALID INPUT   ");
            delay(1000);
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    PLEASE WAIT...  ");
            delay(1000);
            lcd.clear();
            n=0;
            inputCol2=7;
            change_pass();
          } else {
            input_passcode[n] = '2';
            n = n + 1;
          }
        }
        break;
        case '3':
        if (menu == 1) {
          lcd.setCursor(inputCol = inputCol + 1, 1);
          lcd.print('3');
          if (n > 1) {
            lcd.clear();
            countInput();
          } else {
            input[n] = '3';
            n = n + 1;
          }
        } else if (menu == 4) {
          lcd.setCursor(inputCol = inputCol + 1, 1);
          lcd.print('3');
          if (n > 1) {
            lcd.clear();
            countInput();
          } else {
            input[n] = '3';
            n = n + 1;
          }
        } else if (menu== 13) {
          lcd.setCursor(inputCol = inputCol + 1, 1);
          lcd.print('3');
          if (n > 1) {
            lcd.clear();
            countInput2();
          } else {
            input[n] = '3';
            n = n + 1;
          }
        }
        else if(menu == 7){
          lcd.setCursor(inputCol2 = inputCol2 + 1, 2);
          lcd.print('*');
          if (n > 3) {
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    INVALID INPUT   ");
            delay(1000);
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    PLEASE WAIT...  ");
            delay(1000);
            reset();
          } else {
            input_passcode[n] = '3';
            n = n + 1;
          }
        }else if(menu == 9){
          lcd.setCursor(inputCol2 = inputCol2 + 1, 2);
          lcd.print('*');
          if (n > 3) {
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    INVALID INPUT   ");
            delay(1000);
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    PLEASE WAIT...  ");
            delay(1000);
            lcd.clear();
            n=0;
            inputCol2=7;
            change_pass();
          } else {
            input_passcode[n] = '3';
            n = n + 1;
          }
        }
        break;
        case '4':
        if (menu == 1) {
          lcd.setCursor(inputCol = inputCol + 1, 1);
          lcd.print('4');
          if (n > 1) {
            lcd.clear();
            countInput();
          } else {
            input[n] = '4';
            n = n + 1;
          }
        } else if (menu == 4) {
          lcd.setCursor(inputCol = inputCol + 1, 1);
          lcd.print('4');
          if (n > 1) {
            lcd.clear();
            countInput();
          } else {
            input[n] = '4';
            n = n + 1;
          }
        } else if (menu== 13) {
          lcd.setCursor(inputCol = inputCol + 1, 1);
          lcd.print('4');
          if (n > 1) {
            lcd.clear();
            countInput2();
          } else {
            input[n] = '4';
            n = n + 1;
          }
        }
        else if(menu == 7){
          lcd.setCursor(inputCol2 = inputCol2 + 1, 2);
          lcd.print('*');
          if (n > 3) {
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    INVALID INPUT   ");
            delay(1000);
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    PLEASE WAIT...  ");
            delay(1000);
            reset();
          } else {
            input_passcode[n] = '4';
            n = n + 1;
          }
        }else if(menu == 9){
          lcd.setCursor(inputCol2 = inputCol2 + 1, 2);
          lcd.print('*');
          if (n > 3) {
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    INVALID INPUT   ");
            delay(1000);
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    PLEASE WAIT...  ");
            delay(1000);
            lcd.clear();
            n=0;
            inputCol2=7;
            change_pass();
          } else {
            input_passcode[n] = '4';
            n = n + 1;
          }
        }
        break;
        case '5':
        if (menu == 1) {
          lcd.setCursor(inputCol = inputCol + 1, 1);
          lcd.print('5');
          if (n > 1) {
            lcd.clear();
            countInput();
          } else {
            input[n] = '5';
            n = n + 1;
          }
        } else if (menu == 4) {
          lcd.setCursor(inputCol = inputCol + 1, 1);
          lcd.print('5');
          if (n > 1) {
            lcd.clear();
            countInput();
          } else {
            input[n] = '5';
            n = n + 1;
          }
        }else if (menu== 13) {
          lcd.setCursor(inputCol = inputCol + 1, 1);
          lcd.print('5');
          if (n > 1) {
            lcd.clear();
            countInput2();
          } else {
            input[n] = '5';
            n = n + 1;
          }
        }
        else if(menu == 7){
          lcd.setCursor(inputCol2 = inputCol2 + 1, 2);
          lcd.print('*');
          if (n > 3) {
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    INVALID INPUT   ");
            delay(1000);
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    PLEASE WAIT...  ");
            delay(1000);
            reset();
          } else {
            input_passcode[n] = '5';
            n = n + 1;
          }
        }else if(menu == 9){
          lcd.setCursor(inputCol2 = inputCol2 + 1, 2);
          lcd.print('*');
          if (n > 3) {
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    INVALID INPUT   ");
            delay(1000);
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    PLEASE WAIT...  ");
            delay(1000);
            lcd.clear();
            n=0;
            inputCol2=7;
            change_pass();
          } else {
            input_passcode[n] = '5';
            n = n + 1;
          }
        }
        break;
        case '6':
        if (menu == 1) {
          lcd.setCursor(inputCol = inputCol + 1, 1);
          lcd.print('6');
          if (n > 1) {
            lcd.clear();
            countInput();
          } else {
            input[n] = '6';
            n = n + 1;
          }
        } else if (menu == 4) {
          lcd.setCursor(inputCol = inputCol + 1, 1);
          lcd.print('6');
          if (n > 1) {
            lcd.clear();
            countInput();
          } else {
            input[n] = '6';
            n = n + 1;
          }
        }else if (menu== 13) {
          lcd.setCursor(inputCol = inputCol + 1, 1);
          lcd.print('6');
          if (n > 1) {
            lcd.clear();
            countInput2();
          } else {
            input[n] = '6';
            n = n + 1;
          }
        }
        else if(menu == 7){
          lcd.setCursor(inputCol2 = inputCol2 + 1, 2);
          lcd.print('*');
          if (n > 3) {
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    INVALID INPUT   ");
            delay(1000);
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    PLEASE WAIT...  ");
            delay(1000);
            reset();
          } else {
            input_passcode[n] = '6';
            n = n + 1;
          }
        }else if(menu == 9){
          lcd.setCursor(inputCol2 = inputCol2 + 1, 2);
          lcd.print('*');
          if (n > 3) {
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    INVALID INPUT   ");
            delay(1000);
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    PLEASE WAIT...  ");
            delay(1000);
            lcd.clear();
            n=0;
            inputCol2=7;
            change_pass();
          } else {
            input_passcode[n] = '6';
            n = n + 1;
          }
        }
        break;
        case '7':
        if (menu == 1) {
          lcd.setCursor(inputCol = inputCol + 1, 1);
          lcd.print('7');
          if (n > 1) {
            lcd.clear();
            countInput();
          } else {
            input[n] = '7';
            n = n + 1;
          }
        } else if (menu == 4) {
          lcd.setCursor(inputCol = inputCol + 1, 1);
          lcd.print('7');
          if (n > 1) {
            lcd.clear();
            countInput();
          } else {
            input[n] = '7';
            n = n + 1;
          }
        }else if (menu== 13) {
          lcd.setCursor(inputCol = inputCol + 1, 1);
          lcd.print('7');
          if (n > 1) {
            lcd.clear();
            countInput2();
          } else {
            input[n] = '7';
            n = n + 1;
          }
        }
        else if(menu == 7){
          lcd.setCursor(inputCol2 = inputCol2 + 1, 2);
          lcd.print('*');
          if (n > 3) {
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    INVALID INPUT   ");
            delay(1000);
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    PLEASE WAIT...  ");
            delay(1000);
            reset();
          } else {
            input_passcode[n] = '7';
            n = n + 1;
          }
        }else if(menu == 9){
          lcd.setCursor(inputCol2 = inputCol2 + 1, 2);
          lcd.print('*');
          if (n > 3) {
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    INVALID INPUT   ");
            delay(1000);
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    PLEASE WAIT...  ");
            delay(1000);
            lcd.clear();
            n=0;
            inputCol2=7;
            change_pass();
          } else {
            input_passcode[n] = '7';
            n = n + 1;
          }
        }
        break;
        case '8':
        if (menu == 1) {
          lcd.setCursor(inputCol = inputCol + 1, 1);
          lcd.print('8');
          if (n > 1) {
            lcd.clear();
            countInput();
          } else {
            input[n] = '8';
            n = n + 1;
          }
        } else if (menu == 4) {
          lcd.setCursor(inputCol = inputCol + 1, 1);
          lcd.print('8');
          if (n > 1) {
            lcd.clear();
            countInput();
          } else {
            input[n] = '8';
            n = n + 1;
          }
        }else if (menu== 13) {
          lcd.setCursor(inputCol = inputCol + 1, 1);
          lcd.print('8');
          if (n > 1) {
            lcd.clear();
            countInput2();
          } else {
            input[n] = '8';
            n = n + 1;
          }
        }        
        else if(menu == 7){
          lcd.setCursor(inputCol2 = inputCol2 + 1, 2);
          lcd.print('*');
          if (n > 3) {
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    INVALID INPUT   ");
            delay(1000);
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    PLEASE WAIT...  ");
            delay(1000);
            reset();
          } else {
            input_passcode[n] = '8';
            n = n + 1;
          }
        }else if(menu == 9){
          lcd.setCursor(inputCol2 = inputCol2 + 1, 2);
          lcd.print('*');
          if (n > 3) {
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    INVALID INPUT   ");
            delay(1000);
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    PLEASE WAIT...  ");
            delay(1000);
            lcd.clear();
            n=0;
            inputCol2=7;
            change_pass();
          } else {
            input_passcode[n] = '8';
            n = n + 1;
          }
        }
        break;
        case '9':
        if (menu == 1) {
          lcd.setCursor(inputCol = inputCol + 1, 1);
          lcd.print('9');
          if (n > 1) {
            lcd.clear();
            countInput();
          } else {
            input[n] = '9';
            n = n + 1;
          }
        } else if (menu == 4) {
          lcd.setCursor(inputCol = inputCol + 1, 1);
          lcd.print('9');
          if (n > 1) {
            lcd.clear();
            countInput();
          } else {
            input[n] = '9';
            n = n + 1;
          }
        }else if (menu== 13) {
          lcd.setCursor(inputCol = inputCol + 1, 1);
          lcd.print('9');
          if (n > 1) {
            lcd.clear();
            countInput2();
          } else {
            input[n] = '9';
            n = n + 1;
          }
        }
        else if(menu == 7){
          lcd.setCursor(inputCol2 = inputCol2 + 1, 2);
          lcd.print('*');
          if (n > 3) {
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    INVALID INPUT   ");
            delay(1000);
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    PLEASE WAIT...  ");
            delay(1000);
            reset();
          } else {
            input_passcode[n] = '9';
            n = n + 1;
          }
        }else if(menu == 9){
          lcd.setCursor(inputCol2 = inputCol2 + 1, 2);
          lcd.print('*');
          if (n > 3) {
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    INVALID INPUT   ");
            delay(1000);
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("    PLEASE WAIT...  ");
            delay(1000);
            lcd.clear();
            n=0;
            inputCol2=7;
            change_pass();
          } else {
            input_passcode[n] = '9';
            n = n + 1;
          }
        }
        break;
                //--------------------------------------------------------------------------------------------------------------------------
      case 'B': ///------------------------------------------------------------------LETTER B-----------------------------------------------
        if ((menu == 1) or (menu == 4)) { //------------------------------------------------------------------------------------------------
          lcd.clear();
          startPage();
          state1 = 0;
          state2 = 0;
          state3 = 0;
          state4 = 0;
          state5 = 0;
          state6 = 0;
          state7 = 0;
          state8 = 0;
          state9 = 0;
          state10 = 0;
          reset();
        } else if ((menu == 2) or (menu == 12)) {
          lcd.clear();
          lcd.setCursor(0, 1);
          lcd.print("    BACK TO MAIN    ");
          lcd.setCursor(0, 2);
          lcd.print("    PLEASE WAIT...  ");
          state1 = 0;
          state2 = 0;
          state3 = 0;
          state4 = 0;
          state5 = 0;
          state6 = 0;
          state7 = 0;
          state8 = 0;
          state9 = 0;
          state10 = 0;
          switch (dnum) {
            case 1:
              tone(buzz,500,500);
              digitalWrite(door_locker1, LOW);
              delay(1000);
              digitalWrite(door_locker1, HIGH);
              break;
            case 2:
              tone(buzz,500,500);
              digitalWrite(door_locker2, LOW);
              delay(1000);
              digitalWrite(door_locker2, HIGH);
              break;
            case 3:
              tone(buzz,500,500);
              digitalWrite(door_locker3, LOW);
              delay(1000);
              digitalWrite(door_locker3, HIGH);
              break;
            case 4:
              tone(buzz,500,500);
              digitalWrite(door_locker4, LOW);
              delay(1000);
              digitalWrite(door_locker4, HIGH);
              break;
            case 5:
              tone(buzz,500,500);
              digitalWrite(door_locker5, LOW);
              delay(1000);
              digitalWrite(door_locker5, HIGH);
              break;
            case 6:
              tone(buzz,500,500);
              digitalWrite(door_locker6, LOW);
              delay(1000);
              digitalWrite(door_locker6, HIGH);
              break;
            case 7:
              tone(buzz,500,500);
              digitalWrite(door_locker7, LOW);
              delay(1000);
              digitalWrite(door_locker7, HIGH);
              break;
            case 8:
              tone(buzz,500,500);
              digitalWrite(door_locker8, LOW);
              delay(1000);
              digitalWrite(door_locker8, HIGH);
              break;
            case 9:
              tone(buzz,500,500);
              digitalWrite(door_locker9, LOW);
              delay(1000);
              digitalWrite(door_locker9, HIGH);
              break;
            case 10:
              tone(buzz,500,500);
              digitalWrite(door_locker10, LOW);
              delay(1000);
              digitalWrite(door_locker10, HIGH);
              break;
          }
          lcd.clear();
          reset();
        } else if ((menu == 3) or (menu == 5)){
          lcd.clear();
          lcd.setCursor(0, 1);
          lcd.print("    BACK TO MAIN    ");
          lcd.setCursor(0, 2);
          lcd.print("    PLEASE WAIT...  ");
          delay(1000);
          lcd.clear();
          reset();
        }else if(menu==10){
          switch (dnum) {
            case 1:
                EEPROM.write(door1_id_add, 0);
            break;
            case 2:
                EEPROM.write(door2_id_add, 0);
            break;
            case 3:
                EEPROM.write(door3_id_add, 0);
            break;
            case 4:
                EEPROM.write(door4_id_add, 0);
            break;
            case 5:
                EEPROM.write(door5_id_add, 0);
            break;
            case 6:
                EEPROM.write(door6_id_add, 0);
            break;
            case 7:
                EEPROM.write(door7_id_add, 0);
            break;
            case 8:
                EEPROM.write(door8_id_add, 0);
            break;
            case 9:
                EEPROM.write(door9_id_add, 0);
            break;
            case 10:
                EEPROM.write(door10_id_add, 0);
            break;
            }
              lcd.clear();
              lcd.setCursor(0, 1);
              lcd.print("    BACK TO MAIN    ");
              lcd.setCursor(0, 2);
              lcd.print("    PLEASE WAIT...  ");
              delay(1000);
              lcd.clear();
              reset();
          }
         
         else if (menu == 6) {
          lcd.clear();
          lcd.setCursor(0, 1);
          lcd.print("    BACK TO MAIN    ");
          lcd.setCursor(0, 2);
          lcd.print("    PLEASE WAIT...  ");
          delay(1000);
          menu = 5;
          state1 = 0;
          state2 = 0;
          state3 = 0;
          state4 = 0;
          state5 = 0;
          state6 = 0;
          state7 = 0;
          state8 = 0;
          state9 = 0;
          state10 = 0;
          money = 0;
          insertCoin = 0;
          insert_state = 0;
          display_door1 = 2;
          display_door2 = 2;
          display_door3 = 2;
          display_door4 = 2;
          display_door5 = 2;
          display_door6 = 2;
          display_door7 = 2;
          display_door8 = 2;
          display_door9 = 2;
          display_door10 = 2;
          door1_chargingStatus();
          door2_chargingStatus();
          door3_chargingStatus();
          door4_chargingStatus();
          door5_chargingStatus();
          door6_chargingStatus();
          door7_chargingStatus();
          door8_chargingStatus();
          door9_chargingStatus();
          door10_chargingStatus();
        } else if((menu == 7)||(menu == 8)){
          lcd.clear();
          lcd.setCursor(0, 1);
          lcd.print("    BACK TO MAIN    ");
          lcd.setCursor(0, 2);
          lcd.print("    PLEASE WAIT...  ");
          delay(1000);
          lcd.clear(); 
          reset();
        } else if((menu == 9)||(menu==13)){
          lcd.clear();
          lcd.setCursor(0, 1);
          lcd.print("  CANCEL OPERATION  ");
          delay(1000);
          lcd.clear(); 
          a = 0;
          b = 0;
          c = 0;
          d = 0;
          adminView();
          n=0;
          inputCol2 = 7;
          menu=8;
        }
        break;
      case 'A'://-------------------------------------------------------------------------LETTER A-------------------------------------------------------------------------------
        if (menu == 0) {
          lcd.clear();
          askForAccessDoor();
          menu = 4;
        } else if (menu == 3) {
          lcd.clear();
          display_door1 = 0;
          display_door2 = 0;
          display_door3 = 0;
          display_door4 = 0;
          display_door5 = 0;
          display_door6 = 0;
          display_door7 = 0;
          display_door8 = 0;
          display_door9 = 0;
          display_door10 = 0;
          enrollFunction();
          menu=10;

        } else if(menu==10){
          switch (dnum) {
            case 1:
              tempo_add = EEPROM.read(door1_id_add);
              if (tempo_add == 1) {}
              else {
                EEPROM.write(door1_id_add, dnum);
                tempo_add = 0;
              }
              break;
             case 2:
              tempo_add = EEPROM.read(door2_id_add);
              if (tempo_add == 2) {}
              else {
                EEPROM.write(door2_id_add, dnum);
                tempo_add = 0;
              }
              break;
             case 3:
              tempo_add = EEPROM.read(door3_id_add);
              if (tempo_add == 3) {}
              else {
                EEPROM.write(door3_id_add, dnum);
                tempo_add = 0;
              }
             break;
             case 4:
              tempo_add = EEPROM.read(door4_id_add);
              if (tempo_add == 4) {}
              else {
                EEPROM.write(door4_id_add, dnum);
                tempo_add = 0;
              }
             break;
             case 5:
              tempo_add = EEPROM.read(door5_id_add);
              if (tempo_add == 5) {}
              else {
                EEPROM.write(door5_id_add, dnum);
                tempo_add = 0;
              }
             break;
             case 6:
              tempo_add = EEPROM.read(door6_id_add);
              if (tempo_add == 6) {}
              else {
                EEPROM.write(door6_id_add, dnum);
                tempo_add = 0;
              }
             break;
             case 7:
              tempo_add = EEPROM.read(door7_id_add);
              if (tempo_add == 7) {}
              else {
                EEPROM.write(door7_id_add, dnum);
                tempo_add = 0;
              }
             break;
             case 8:
              tempo_add = EEPROM.read(door8_id_add);
              if (tempo_add == 8) {}
              else {
                EEPROM.write(door8_id_add, dnum);
                tempo_add = 0;
              }
             break;
             case 9:
              tempo_add = EEPROM.read(door9_id_add);
              if (tempo_add == 9) {}
              else {
                EEPROM.write(door9_id_add, dnum);
                tempo_add = 0;
              }
             break;
             case 10:
              tempo_add = EEPROM.read(door10_id_add);
              if (tempo_add == 10) {}
              else {
                EEPROM.write(door10_id_add, dnum);
                tempo_add = 0;
              }
             break;
          }
          lcd.clear();
          id=dnum;
          fingerprint_status = 1;
          enrollFunction();
        } else if(menu==8){
          lcd.clear();
          change_pass();
          menu = 9;
        } else if(menu==9){
          if((n<4)||(n!=4)){
              lcd.clear();
              lcd.setCursor(0, 1);
              lcd.print("  INVALID PASSCODE  ");
              delay(1000);
              lcd.clear();
              n=0;
              inputCol2 = 7;
              change_pass();
          }else {
            checkpass();
            int c1 = code1;
            int c2 = code2;
            int c3 = code3;
            int c4 = code4;

            EEPROM.write(code_add1,c1);
            EEPROM.write(code_add2,c2);
            EEPROM.write(code_add3,c3);
            EEPROM.write(code_add4,c4);

            lcd.clear();
            lcd.setCursor(0,1);
            lcd.print("  PASSWORD UPDATE!  ");
            delay(1000); 
            adminView();
            menu = 7;
          }
        }
        break;                             //---------------------------------------------------------------------------------------------------
      case 'C':                            //-------------------------------------------LETTER C------------------------------------------------
        if (menu == 0) {                   //---------------------------------------------------------------------------------------------------
          lcd.clear();
          askForChargingDoor();
          menu = menu + 1;
        } else if (menu == 2) {
          switch (dnum) {
            case 1:
              if (money == 0) {
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("    INSUFFICIENT    ");
                lcd.setCursor(0, 2);
                lcd.print("      CREDITS !");
                delay(1000);
                lcd.clear();
                dnum = 1;
                coinInput();
              } else {
                d1_timerSeconds = d1_timerSeconds + (perminute) * 60;
                incomeCount();
                perminute = 0;
                lcd.clear();
                insert_state = 0;
                d1_chargingState = 1;
                door1_chargingStatus();
                display_door1 = 1;
                menu = menu + 1;
                money = 0;
                perminute=0;
                state1 = 0;
              }
              break;
            case 2:
              if (money == 0) {
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("    INSUFFICIENT    ");
                lcd.setCursor(0, 2);
                lcd.print("      CREDITS !");
                delay(1000);
                lcd.clear();
                dnum = 2;
                coinInput();
              } else {
                d2_timerSeconds = d2_timerSeconds + (perminute) * 60;
                incomeCount();
                perminute=0;
                lcd.clear();
                insert_state = 0;
                d2_chargingState = 1;
                display_door2 = 1;
                door2_chargingStatus();
                menu = menu + 1;
                money = 0;
                state2 = 0;
              }
            break;
            case 3:
              if (money == 0) {
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("    INSUFFICIENT    ");
                lcd.setCursor(0, 2);
                lcd.print("      CREDITS !");
                delay(1000);
                lcd.clear();
                dnum = 3;
                coinInput();
              } else {
                d3_timerSeconds = d3_timerSeconds + (perminute) * 60;
                incomeCount();
                perminute = 0;
                lcd.clear();
                insert_state = 0;
                d3_chargingState = 1;
                display_door3 = 1;
                door3_chargingStatus();
                menu = menu + 1;
                money = 0;
                state3 = 0;
              }
            break;
            case 4:
              if (money == 0) {
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("    INSUFFICIENT    ");
                lcd.setCursor(0, 2);
                lcd.print("      CREDITS !");
                delay(1000);
                lcd.clear();
                dnum = 4;
                coinInput();
              } else {
                
                d4_timerSeconds = d4_timerSeconds + (perminute) * 60;
                incomeCount();
                perminute = 0;
                lcd.clear();
                insert_state = 0;
                d4_chargingState = 1;
                display_door4 = 1;
                door4_chargingStatus();
                menu = menu + 1;
                money = 0;
                state4 = 0;
              }
            break;
            case 5:
              if (money == 0) {
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("    INSUFFICIENT    ");
                lcd.setCursor(0, 2);
                lcd.print("      CREDITS !");
                delay(1000);
                lcd.clear();
                dnum = 5;
                coinInput();
              } else {
                d5_timerSeconds = d5_timerSeconds + (perminute) * 60;
                incomeCount();
                perminute = 0;
                lcd.clear();
                insert_state = 0;
                d5_chargingState = 1;
                display_door5 = 1;
                door5_chargingStatus();
                menu = menu + 1;
                money = 0;
                state5 = 0;
              }
            break;
            case 6:
              if (money == 0) {
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("    INSUFFICIENT    ");
                lcd.setCursor(0, 2);
                lcd.print("      CREDITS !");
                delay(1000);
                lcd.clear();
                dnum = 6;
                coinInput();
              } else {
                d6_timerSeconds = d6_timerSeconds + (perminute) * 60;
                incomeCount();
                perminute = 0;
                lcd.clear();
                insert_state = 0;
                d6_chargingState = 1;
                display_door6 = 1;
                door6_chargingStatus();
                menu = menu + 1;
                money = 0;
                state6 = 0;
              }
            break;
            case 7:
              if (money == 0) {
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("    INSUFFICIENT    ");
                lcd.setCursor(0, 2);
                lcd.print("      CREDITS !");
                delay(1000);
                lcd.clear();
                dnum = 7;
                coinInput();
              } else {
                d7_timerSeconds = d7_timerSeconds + (perminute) * 60;
                incomeCount();
                perminute = 0;
                lcd.clear();
                insert_state = 0;
                d7_chargingState = 1;
                display_door7 = 1;
                door7_chargingStatus();
                menu = menu + 1;
                money = 0;
                state7 = 0;
              }
            break;
            case 8:
              if (money == 0) {
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("    INSUFFICIENT    ");
                lcd.setCursor(0, 2);
                lcd.print("      CREDITS !");
                delay(1000);
                lcd.clear();
                dnum = 8;
                coinInput();
              } else {
                d8_timerSeconds = d8_timerSeconds + (perminute) * 60;
                incomeCount();
                perminute = 0;
                lcd.clear();
                insert_state = 0;
                d8_chargingState = 1;
                display_door8 = 1;
                door8_chargingStatus();
                menu = menu + 1;
                money = 0;
                state8 = 0;
              }
            break;

            case 9:
              if (money == 0) {
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("    INSUFFICIENT    ");
                lcd.setCursor(0, 2);
                lcd.print("      CREDITS !");
                delay(1000);
                lcd.clear();
                dnum = 9;
                coinInput();
              } else {
                d9_timerSeconds = d9_timerSeconds + (perminute) * 60;
                incomeCount();
                perminute = 0;
                lcd.clear();
                insert_state = 0;
                d9_chargingState = 1;
                display_door9 = 1;
                door9_chargingStatus();
                menu = menu + 1;
                money = 0;
                state9 = 0;
              }
            break;

            case 10:
              if (money == 0) {
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("    INSUFFICIENT    ");
                lcd.setCursor(0, 2);
                lcd.print("      CREDITS !");
                delay(1000);
                lcd.clear();
                dnum = 10;
                coinInput();
              } else {
                d10_timerSeconds = d10_timerSeconds + (perminute) * 60;
                incomeCount();
                perminute = 0;
                lcd.clear();
                insert_state = 0;
                d10_chargingState = 1;
                display_door10 = 1;
                door10_chargingStatus();
                menu = menu + 1;
                money = 0;
                state10 = 0;
              }
            break;
             
          }                     //---------------------------------------------------------------------------------------------------------------------------
        } else if (menu == 8) { //---------------------------------------------ADMIN INCOME FUNCTION---------------------------------------------------------
          lcd.clear();          //-----------------------------------------------------------------------------------------------------------------------------
          incomeFunc();
          c = EEPROM.read(n1);
          d = EEPROM.read(n2);
          int totalEEPROM = c * 256 + d;
          lcd.setCursor(10,1);
          lcd.print(totalEEPROM);
          menu = 9;          
        }else if(menu==9) {
          EEPROM.write(n1,0);
          EEPROM.write(n2,0);
          lcd.clear();
          lcd.setCursor(0,1);
          lcd.print("    INCOME RESET    ");
          delay(2000);
          lcd.clear();
          incomeFunc();           //------------------------------------------------------------------------------------------------------------------------
        }else if(menu==11){       //----------------------------------------------LETTER C PAY PENALTY------------------------------------------------------
                                  //------------------------------------------------------------------------------------------------------------------------
          switch(tempo_add){
            case 1:
              if(money < penalty_1){
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("    INSUFFICIENT    ");
                lcd.setCursor(0, 2);
                lcd.print("      CREDITS !");
                delay(1000);
                lcd.clear();
                menu=11;
                insertCoin = 2;
                display_door1 = 4;
                door1_chargingStatus();
              }else {
                incomeCount();
                digitalWrite(led1, LOW);
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("      THANK YOU      ");
                lcd.setCursor(0, 2);
                lcd.print("    CHARGED AGAIN    ");
                EEPROM.write(door1_id_add, 0);
                tone(buzz,500,500);
                digitalWrite(door_locker1, LOW);
                delay(1000);
                digitalWrite(door_locker1, HIGH);
                lcd.clear();
                id = 1;
                deleteFingerprint(id);
                money=0;
                display_door1 = 0;
                d1_chargingState = 0;
                sec_d1 = 0;
                minu_d1 = 0;
                hr_d1 = 0;
                sub1sec1=0;
                sub1sec2=0;
                count_1=0;
                penalty_1=0;
                reset(); 
              }
            break;
            case 2:
              if(money < penalty_2){
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("    INSUFFICIENT    ");
                lcd.setCursor(0, 2);
                lcd.print("      CREDITS !");
                delay(1000);
                lcd.clear();
                menu=11;
                insertCoin = 2;
                display_door2 = 4;
                door2_chargingStatus();
              }else {
                incomeCount();
                lcd.clear();
                digitalWrite(led2, LOW);
                EEPROM.write(door2_id_add, 0);
                lcd.setCursor(0, 1);
                lcd.print("      THANK YOU      ");
                lcd.setCursor(0, 2);
                lcd.print("    CHARGED AGAIN    ");
                tone(buzz,500,500);
                digitalWrite(door_locker2, LOW);
                delay(1000);
                digitalWrite(door_locker2, HIGH);
                lcd.clear();
                id = 2;
                deleteFingerprint(id);
                money=0;
                display_door2 = 0;
                d2_chargingState = 0;
                sec_d2 = 0;
                minu_d2 = 0;
                hr_d2 = 0;
                sub2sec1=0;
                sub2sec2=0;
                count_2=0;
                penalty_2 =0;
                reset(); 
              }
            break;
            case 3:
              if(money < penalty_3){
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("    INSUFFICIENT    ");
                lcd.setCursor(0, 2);
                lcd.print("      CREDITS !");
                delay(1000);
                lcd.clear();
                menu=11;
                insertCoin = 2;
                display_door3 = 4;
                door3_chargingStatus();
              }else {
                incomeCount();
                lcd.clear();
                digitalWrite(led3, LOW);
                EEPROM.write(door3_id_add, 0);
                lcd.setCursor(0, 1);
                lcd.print("      THANK YOU      ");
                lcd.setCursor(0, 2);
                lcd.print("    CHARGED AGAIN    ");
                tone(buzz,500,500);
                digitalWrite(door_locker3, LOW);
                delay(1000);
                digitalWrite(door_locker3, HIGH);
                lcd.clear();
                id = 3;
                deleteFingerprint(id);
                money=0;
                display_door3 = 0;
                d3_chargingState = 0;
                sec_d3 = 0;
                minu_d3 = 0;
                hr_d3 = 0;
                sub3sec1=0;
                sub3sec2=0;
                count_3=0;
                penalty_3 =0;
                reset(); 
              }
            break;
            case 4:
              if(money < penalty_4){
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("    INSUFFICIENT    ");
                lcd.setCursor(0, 2);
                lcd.print("      CREDITS !");
                delay(1000);
                lcd.clear();
                menu=11;
                insertCoin = 2;
                display_door4 = 4;
                door4_chargingStatus();
              }else {
                incomeCount();
                lcd.clear();
                digitalWrite(led4, LOW);
                EEPROM.write(door4_id_add, 0);
                lcd.setCursor(0, 1);
                lcd.print("      THANK YOU      ");
                lcd.setCursor(0, 2);
                lcd.print("    CHARGED AGAIN    ");
                tone(buzz,500,500);
                digitalWrite(door_locker4, LOW);
                delay(1000);
                digitalWrite(door_locker4, HIGH);
                lcd.clear();
                id = 4;
                deleteFingerprint(id);
                money=0;
                display_door4 = 0;
                d4_chargingState = 0;
                sec_d4 = 0;
                minu_d4 = 0;
                hr_d4 = 0;
                sub4sec1=0;
                sub4sec2=0;
                count_4=0;
                penalty_4 =0;
                reset(); 
              }
            break;
            
            case 5:
              if(money < penalty_5){
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("    INSUFFICIENT    ");
                lcd.setCursor(0, 2);
                lcd.print("      CREDITS !");
                delay(1000);
                lcd.clear();
                menu=11;
                insertCoin = 2;
                display_door5 = 4;
                door5_chargingStatus();
              }else {
                incomeCount();
                lcd.clear();
                digitalWrite(led5, LOW);
                EEPROM.write(door5_id_add, 0);
                lcd.setCursor(0, 1);
                lcd.print("      THANK YOU      ");
                lcd.setCursor(0, 2);
                lcd.print("    CHARGED AGAIN    ");
                tone(buzz,500,500);
                digitalWrite(door_locker5, LOW);
                delay(1000);
                digitalWrite(door_locker5, HIGH);
                lcd.clear();
                id = 5;
                deleteFingerprint(id);
                money=0;
                display_door5 = 0;
                d5_chargingState = 0;
                sec_d5 = 0;
                minu_d5 = 0;
                hr_d5 = 0;
                sub5sec1=0;
                sub5sec2=0;
                count_5=0;
                penalty_5=0;
                reset(); 
              }
            break;
            
            case 6:
              if(money < penalty_6){
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("    INSUFFICIENT    ");
                lcd.setCursor(0, 2);
                lcd.print("      CREDITS !");
                delay(1000);
                lcd.clear();
                menu=11;
                insertCoin = 2;
                display_door6 = 4;
                door6_chargingStatus();
              }else {
                incomeCount();
                lcd.clear();
                digitalWrite(led6, LOW);
                EEPROM.write(door6_id_add, 0);
                lcd.setCursor(0, 1);
                lcd.print("      THANK YOU      ");
                lcd.setCursor(0, 2);
                lcd.print("    CHARGED AGAIN    ");
                tone(buzz,500,500);
                digitalWrite(door_locker6, LOW);
                delay(1000);
                digitalWrite(door_locker6, HIGH);
                lcd.clear();
                id = 6;
                deleteFingerprint(id);
                money=0;
                display_door6 = 0;
                d6_chargingState = 0;
                sec_d6 = 0;
                minu_d6 = 0;
                hr_d6 = 0;
                sub6sec1=0;
                sub6sec2=0;
                count_6=0;
                penalty_6=0;
                reset(); 
              }
            break;

            case 7:
              if(money < penalty_7){
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("    INSUFFICIENT    ");
                lcd.setCursor(0, 2);
                lcd.print("      CREDITS !");
                delay(1000);
                lcd.clear();
                menu=11;
                insertCoin = 2;
                display_door7 = 4;
                door7_chargingStatus();
              }else {
                incomeCount();
                lcd.clear();
                digitalWrite(led7, LOW);
                EEPROM.write(door7_id_add, 0);
                lcd.setCursor(0, 1);
                lcd.print("      THANK YOU      ");
                lcd.setCursor(0, 2);
                lcd.print("    CHARGED AGAIN    ");
                tone(buzz,500,500);
                digitalWrite(door_locker7, LOW);
                delay(1000);
                digitalWrite(door_locker7, HIGH);
                lcd.clear();
                id = 7;
                deleteFingerprint(id);
                money=0;
                display_door7 = 0;
                d7_chargingState = 0;
                sec_d7 = 0;
                minu_d7 = 0;
                hr_d7 = 0;
                sub7sec1=0;
                sub7sec2=0;
                count_7=0;
                penalty_7=0;
                reset(); 
              }
            break;

            case 8:
              if(money < penalty_8){
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("    INSUFFICIENT    ");
                lcd.setCursor(0, 2);
                lcd.print("      CREDITS !");
                delay(1000);
                lcd.clear();
                menu=11;
                insertCoin = 2;
                display_door8 = 4;
                door8_chargingStatus();
              }else {
                incomeCount();
                lcd.clear();
                digitalWrite(led8, LOW);
                EEPROM.write(door8_id_add, 0);
                lcd.setCursor(0, 1);
                lcd.print("      THANK YOU      ");
                lcd.setCursor(0, 2);
                lcd.print("    CHARGED AGAIN    ");
                tone(buzz,500,500);
                digitalWrite(door_locker8, LOW);
                delay(1000);
                digitalWrite(door_locker8, HIGH);
                lcd.clear();
                id = 8;
                deleteFingerprint(id);
                money=0;
                display_door8 = 0;
                d8_chargingState = 0;
                sec_d8 = 0;
                minu_d8 = 0;
                hr_d8 = 0;
                sub8sec1=0;
                sub8sec2=0;
                count_8=0;
                penalty_8=0;
                reset(); 
              }
            break;

            case 9:
              if(money < penalty_9){
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("    INSUFFICIENT    ");
                lcd.setCursor(0, 2);
                lcd.print("      CREDITS !");
                delay(1000);
                lcd.clear();
                menu=11;
                insertCoin = 2;
                display_door9 = 4;
                door9_chargingStatus();
              }else {
                incomeCount();
                lcd.clear();
                digitalWrite(led9, LOW);
                EEPROM.write(door9_id_add, 0);
                lcd.setCursor(0, 1);
                lcd.print("      THANK YOU      ");
                lcd.setCursor(0, 2);
                lcd.print("    CHARGED AGAIN    ");
                tone(buzz,500,500);
                digitalWrite(door_locker9, LOW);
                delay(1000);
                digitalWrite(door_locker9, HIGH);
                lcd.clear();
                id = 9;
                deleteFingerprint(id);
                money=0;
                display_door9 = 0;
                d9_chargingState = 0;
                sec_d9 = 0;
                minu_d9 = 0;
                hr_d9 = 0;
                sub9sec1=0;
                sub9sec2=0;
                count_9=0;
                penalty_9=0;
                reset(); 
              }
            break;

            case 10:
              if(money < penalty_10){
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("    INSUFFICIENT    ");
                lcd.setCursor(0, 2);
                lcd.print("      CREDITS !");
                delay(1000);
                lcd.clear();
                menu=11;
                insertCoin = 2;
                display_door10 = 4;
                door10_chargingStatus();
              }else {
                incomeCount();
                lcd.clear();
                digitalWrite(led10, LOW);
                EEPROM.write(door10_id_add, 0);
                lcd.setCursor(0, 1);
                lcd.print("      THANK YOU      ");
                lcd.setCursor(0, 2);
                lcd.print("    CHARGED AGAIN    ");
                tone(buzz,500,500);
                digitalWrite(door_locker10, LOW);
                delay(1000);
                digitalWrite(door_locker10, HIGH);
                lcd.clear();
                id = 10;
                deleteFingerprint(id);
                money=0;
                display_door10 = 0;
                d10_chargingState = 0;
                sec_d10 = 0;
                minu_d10 = 0;
                hr_d10 = 0;
                sub10sec1=0;
                sub10sec2=0;
                count_10=0;
                penalty_10=0;
                reset(); 
              }
            break;
          }
        }
        break;
        
            //----------------------------------------------------------------------------------------------------------------------------------------
      case '*':   //---------------------------------------------------------------PROCEED BUTTON------------------------------------------------------------
        if (menu == 1) { //----------------------------------------------------------------------------------------------------------------------------------
            if ((input[0] == '1') and (input[1] == '0')) {
              if (d10_chargingState != 0) {
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("  THE DOOR IS USED  ");
                delay(1000);
                lcd.clear();
                startPage();
                n = 0;
                menu = 0;
                inputReset();
              } else {
                digitalWrite(door_locker10, LOW);
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("  LOCKER 10 IS OPEN ");
                tone(buzz,500,500);
                delay(1000);
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print(" PLEASE  CLOSED THE ");
                lcd.setCursor(0, 1);
                lcd.print(" LOCKER TO PROCEED..");
                lcd.setCursor(0, 2);
                lcd.print("                    ");
                lcd.setCursor(0, 3);
                lcd.print("B-> CANCEL");
                digitalWrite(door_locker10, HIGH);
                dnum = 10;
                state10 = 1;
                menu = 12;
                doorstat();
                  if (state10 == 3) {
                    lcd.clear();
                    doorstat();
                  } 
                }
            } else if ((n == 1) and (input[0] == '1')) { //-------------------------LOCKER 1-----------------------
              if (d1_chargingState != 0) {
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("  THE DOOR IS USED  ");
                delay(1000);
                lcd.clear();
                startPage();
                n = 0;
                menu = 0;
                inputReset();
              } else {
                digitalWrite(door_locker1, LOW);
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("  LOCKER 1 IS OPEN  ");
                tone(buzz,500,300);
                delay(1000);
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print(" PLEASE  CLOSED THE ");
                lcd.setCursor(0, 1);
                lcd.print(" LOCKER TO PROCEED..");
                lcd.setCursor(0, 2);
                lcd.print("                    ");
                lcd.setCursor(0, 3);
                lcd.print("B-> CANCEL");
                digitalWrite(door_locker1, HIGH);
                dnum = 1;
                state1 = 1;
                menu = 12;
                doorstat();
                  if (state1 == 3) {
                    lcd.clear();
                    doorstat();
                  } 
                }
                  
          } else if ((n == 1) and (input[0] == '2')) {
            if (d2_chargingState == 1) {
              lcd.clear();
              lcd.setCursor(0, 1);
              lcd.print("  THE DOOR IS USED  ");
              delay(1000);
              lcd.clear();
              startPage();
              n = 0;
              menu = 0;
              inputReset();
            } else {
              digitalWrite(door_locker2, LOW);
              lcd.clear();
              lcd.setCursor(0, 1);
              lcd.print("  LOCKER 2 IS OPEN  ");
              tone(buzz,500,300);
              delay(1000);
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print(" PLEASE  CLOSED THE ");
              lcd.setCursor(0, 1);
              lcd.print(" LOCKER TO PROCEED..");
              lcd.setCursor(0, 2);
              lcd.print("                    ");
              lcd.setCursor(0, 3);
              lcd.print("B-> CANCEL");
              digitalWrite(door_locker2, HIGH);
              dnum = 2;
              menu = 12;
              state2 = 1;
              doorstat();
              if (state2 == 3) {
                lcd.clear();
                doorstat();
              }
              
            }
          } else if ((n == 1) and (input[0] == '3')) {
            if (d3_chargingState == 1) {
              lcd.clear();
              lcd.setCursor(0, 1);
              lcd.print("  THE DOOR IS USED  ");
              delay(1000);
              lcd.clear();
              startPage();
              n = 0;
              menu = 0;
              inputReset();
            } else {
              digitalWrite(door_locker3, LOW);
              lcd.clear();
              lcd.setCursor(0, 1);
              lcd.print("  LOCKER 3 IS OPEN  ");
              tone(buzz,500,300);
              delay(1000);
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print(" PLEASE  CLOSED THE ");
              lcd.setCursor(0, 1);
              lcd.print(" LOCKER TO PROCEED..");
              lcd.setCursor(0, 2);
              lcd.print("                    ");
              lcd.setCursor(0, 3);
              lcd.print("B-> CANCEL");
              digitalWrite(door_locker3, HIGH);
              dnum = 3;
              menu = 12;
              state3 = 1;
              doorstat();
              if (state3 == 3) {
                lcd.clear();
                doorstat();
              }
              
            }
          } else if ((n == 1) and (input[0] == '4')) {
            if (d4_chargingState == 1) {
              lcd.clear();
              lcd.setCursor(0, 1);
              lcd.print("  THE DOOR IS USED  ");
              delay(1000);
              lcd.clear();
              startPage();
              n = 0;
              menu = 0;
              inputReset();
            } else {
              digitalWrite(door_locker4, LOW);
              lcd.clear();
              lcd.setCursor(0, 1);
              lcd.print("  LOCKER 4 IS OPEN  ");
              tone(buzz,500,300);
              delay(1000);
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print(" PLEASE  CLOSED THE ");
              lcd.setCursor(0, 1);
              lcd.print(" LOCKER TO PROCEED..");
              lcd.setCursor(0, 2);
              lcd.print("                    ");
              lcd.setCursor(0, 3);
              lcd.print("B-> CANCEL");
              digitalWrite(door_locker4, HIGH);
              dnum = 4;
              menu = 12;
              state4 = 1;
              doorstat();
              if (state4 == 3) {
                lcd.clear();
                doorstat();
              }
            }
          } else if ((n == 1) and (input[0] == '5')) {
            if (d5_chargingState == 1) {
              lcd.clear();
              lcd.setCursor(0, 1);
              lcd.print("  THE DOOR IS USED  ");
              delay(1000);
              lcd.clear();
              startPage();
              n = 0;
              menu = 0;
              inputReset();
            } else {
              digitalWrite(door_locker5, LOW);
              lcd.clear();
              lcd.setCursor(0, 1);
              lcd.print("  LOCKER 5 IS OPEN  ");
              tone(buzz,500,300);
              delay(1000);
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print(" PLEASE  CLOSED THE ");
              lcd.setCursor(0, 1);
              lcd.print(" LOCKER TO PROCEED..");
              lcd.setCursor(0, 2);
              lcd.print("                    ");
              lcd.setCursor(0, 3);
              lcd.print("B-> CANCEL");
              digitalWrite(door_locker5, HIGH);
              dnum = 5;
              menu = 12;
              state5 = 1;
              doorstat();
              if (state5 == 3) {
                lcd.clear();
                doorstat();
              }
            }
          } else if ((n == 1) and (input[0] == '6')) {
            if (d6_chargingState == 1) {
              lcd.clear();
              lcd.setCursor(0, 1);
              lcd.print("  THE DOOR IS USED  ");
              delay(1000);
              lcd.clear();
              startPage();
              n = 0;
              menu = 0;
              inputReset();
            } else {
              digitalWrite(door_locker6, LOW);
              lcd.clear();
              lcd.setCursor(0, 1);
              lcd.print("  LOCKER 6 IS OPEN  ");
              tone(buzz,500,300);
              delay(1000);
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print(" PLEASE  CLOSED THE ");
              lcd.setCursor(0, 1);
              lcd.print(" LOCKER TO PROCEED..");
              lcd.setCursor(0, 2);
              lcd.print("                    ");
              lcd.setCursor(0, 3);
              lcd.print("B-> CANCEL");
              digitalWrite(door_locker6, HIGH);
              dnum = 6;
              menu = 12;
              state6 = 1;
              doorstat();
              if (state6 == 3) {
                lcd.clear();
                doorstat();
              }
            }
          }else if ((n == 1) and (input[0] == '7')) {
            if (d7_chargingState == 1) {
              lcd.clear();
              lcd.setCursor(0, 1);
              lcd.print("  THE DOOR IS USED  ");
              delay(1000);
              lcd.clear();
              startPage();
              n = 0;
              menu = 0;
              inputReset();
            } else {
              digitalWrite(door_locker7, LOW);
              lcd.clear();
              lcd.setCursor(0, 1);
              lcd.print("  LOCKER 7 IS OPEN  ");
              tone(buzz,500,300);
              delay(1000);
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print(" PLEASE  CLOSED THE ");
              lcd.setCursor(0, 1);
              lcd.print(" LOCKER TO PROCEED..");
              lcd.setCursor(0, 2);
              lcd.print("                    ");
              lcd.setCursor(0, 3);
              lcd.print("B-> CANCEL");
              digitalWrite(door_locker7, HIGH);
              dnum = 7;
              menu = 12;
              state7 = 1;
              doorstat();
              if (state7 == 3) {
                lcd.clear();
                doorstat();
              }
            }
          }else if ((n == 1) and (input[0] == '8')) {
            if (d8_chargingState == 1) {
              lcd.clear();
              lcd.setCursor(0, 1);
              lcd.print("  THE DOOR IS USED  ");
              delay(1000);
              lcd.clear();
              startPage();
              n = 0;
              menu = 0;
              inputReset();
            } else {
              digitalWrite(door_locker8, LOW);
              lcd.clear();
              lcd.setCursor(0, 1);
              lcd.print("  LOCKER 8 IS OPEN  ");
              tone(buzz,500,300);
              delay(1000);
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print(" PLEASE  CLOSED THE ");
              lcd.setCursor(0, 1);
              lcd.print(" LOCKER TO PROCEED..");
              lcd.setCursor(0, 2);
              lcd.print("                    ");
              lcd.setCursor(0, 3);
              lcd.print("B-> CANCEL");
              digitalWrite(door_locker8, HIGH);
              dnum = 8;
              menu = 12;
              state8 = 1;
              doorstat();
              if (state8 == 3) {
                lcd.clear();
                doorstat();
              }
            }
          }else if ((n == 1) and (input[0] == '9')) {
            if (d9_chargingState == 1) {
              lcd.clear();
              lcd.setCursor(0, 1);
              lcd.print("  THE DOOR IS USED  ");
              delay(1000);
              lcd.clear();
              startPage();
              n = 0;
              menu = 0;
              inputReset();
            } else {
              digitalWrite(door_locker9, LOW);
              lcd.clear();
              lcd.setCursor(0, 1);
              lcd.print("  LOCKER 9 IS OPEN  ");
              tone(buzz,500,300);
              delay(1000);
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print(" PLEASE  CLOSED THE ");
              lcd.setCursor(0, 1);
              lcd.print(" LOCKER TO PROCEED..");
              lcd.setCursor(0, 2);
              lcd.print("                    ");
              lcd.setCursor(0, 3);
              lcd.print("B-> CANCEL");
              digitalWrite(door_locker9, HIGH);
              dnum = 9;
              menu = 12;
              state9 = 1;
              doorstat();
              if (state9 == 3) {
                lcd.clear();
                doorstat();
              }
            }
          } else {       
            lcd.clear();
            lcd.setCursor(0,1);
            lcd.print("    INVALID INPUT   ");
            lcd.setCursor(0,2);
            lcd.print("     BACK TO MAIN   ");
            delay(1000);
            lcd.clear();
            reset();
          }
                                                    //----------------------------------------------------------------------------------------------------------------------------------
        } else if (menu == 4) {                     //------------------------------------------------------Acceess Page naman----------------------------------------------------------
          if ((n == 1) and (input[0] == '1')) {     //----------------------------------------------------------------------------------------------------------------------------------
            if (d1_chargingState == 1) {
              lcd.clear();
              dnum = 1;
              insertCoin = 1;
              display_door1 = 2;
              door1_chargingStatus();                 
              menu = 5;
            } else if (d1_chargingState == 2) {
              lcd.clear();
              dnum = 1;
              display_door1 = 3;
              door1_chargingStatus();
              menu = 5;
            } else {
              lcd.clear();
              lcd.setCursor(0, 1);
              lcd.print("  DOOR 1 IS UNUSED  ");
              delay(1000);
              lcd.clear();
              reset();
            }
          } else if ((n == 1) and (input[0] == '2')) { // ------------------------------door 2 ----------------------------------------
            if (d2_chargingState == 1) {
              lcd.clear();
              dnum = 2;
              insertCoin = 1;
              display_door2 = 2;
              door2_chargingStatus();                 
              menu = 5;
             
            } else if (d2_chargingState == 2) {
              lcd.clear();
              dnum = 2;
              display_door2 = 3;
              door2_chargingStatus();
              menu = 5;
            } else {
              lcd.clear();
              lcd.setCursor(0, 1);
              lcd.print("  DOOR 2 IS UNUSED  ");
              delay(1000);
              lcd.clear();
              reset();
            }
          } else if ((n == 1) and (input[0] == '3')) { // --------------------------- Door 3 --------------------------------------------
            if (d3_chargingState == 1) {
              lcd.clear();
              dnum = 3;
              insertCoin = 1;
              display_door3 = 2;
              door3_chargingStatus();                 
              menu = 5;
            } else if (d3_chargingState == 2) {
              lcd.clear();
              dnum = 3;
              display_door3 = 3;
              door3_chargingStatus();
              menu = 5;
            } else {
              lcd.clear();
              lcd.setCursor(0, 1);
              lcd.print("  DOOR 3 IS UNUSED  ");
              delay(1000);
              lcd.clear();
              reset();
            }
          } else if ((n == 1) and (input[0] == '4')) { // --------------------------- Door 4 --------------------------------------------
            if (d4_chargingState == 1) {
              lcd.clear();
              dnum = 4;
              insertCoin = 1;
              display_door4 = 2;
              door4_chargingStatus();                 
              menu = 5;
            } else if (d4_chargingState == 2) {
              lcd.clear();
              dnum = 4;
              display_door4 = 3;
              door4_chargingStatus();
              menu = 5;
            } else {
              lcd.clear();
              lcd.setCursor(0, 1);
              lcd.print("  DOOR 4 IS UNUSED  ");
              delay(1000);
              lcd.clear();
              reset();
            }
          }  else if ((n == 1) and (input[0] == '5')) { // --------------------------- Door 5 --------------------------------------------
            if (d5_chargingState == 1) {
              lcd.clear();
              dnum = 5;
              insertCoin = 1;
              display_door5 = 2;
              door5_chargingStatus();                 
              menu = 5;
            } else if (d5_chargingState == 2) {
              lcd.clear();
              dnum = 5;
              menu = 5;
              display_door5 = 3;
              door5_chargingStatus();
            } else {
              lcd.clear();
              lcd.setCursor(0, 1);
              lcd.print("  DOOR 5 IS UNUSED  ");
              delay(1000);
              lcd.clear();
              reset();
            }
          }  else if ((n == 1) and (input[0] == '6')) { // --------------------------- Door 6 --------------------------------------------
            if (d6_chargingState == 1) {
              lcd.clear();
              dnum = 6;
              insertCoin = 1;
              display_door6 = 2;
              door6_chargingStatus();                 
              menu = 5;
            } else if (d6_chargingState == 2) {
              
              lcd.clear();
              dnum = 6;
              display_door6 = 3;
              menu = 5;
              door6_chargingStatus();
            } else {
              lcd.clear();
              lcd.setCursor(0, 1);
              lcd.print("  DOOR 6 IS UNUSED  ");
              delay(1000);
              lcd.clear();
              reset();
            }
          } else if ((n == 1) and (input[0] == '7')) { // --------------------------- Door 7 --------------------------------------------
            if (d7_chargingState == 1) {
              lcd.clear();
              dnum = 7;
              insertCoin = 1;
              display_door7 = 2;
              door7_chargingStatus();                 
              menu = 5;
            } else if (d7_chargingState == 2) {
              lcd.clear();
              dnum = 7;
              display_door7 = 3;
              door7_chargingStatus();
              menu = 5;
            } else {
              lcd.clear();
              lcd.setCursor(0, 1);
              lcd.print("  DOOR 7 IS UNUSED  ");
              delay(1000);
              lcd.clear();
              reset();
            }
          } else if ((n == 1) and (input[0] == '8')) { // --------------------------- Door 8 --------------------------------------------
            if (d8_chargingState == 1) {
              lcd.clear();
              dnum = 8;
              insertCoin = 1;
              display_door8 = 2;
              door8_chargingStatus();                 
              menu = 5;
            } else if (d8_chargingState == 2) {
              lcd.clear();
              dnum = 8;
              display_door8 = 3;
              door8_chargingStatus();
              menu = 5;
            } else {
              lcd.clear();
              lcd.setCursor(0, 1);
              lcd.print("  DOOR 8 IS UNUSED  ");
              delay(1000);
              lcd.clear();
              reset();
            }
          } else if ((n == 1) and (input[0] == '9')) { // --------------------------- Door 9 --------------------------------------------
            if (d9_chargingState == 1) {
              lcd.clear();
              dnum = 9;
              insertCoin = 1;
              display_door9 = 2;
              door9_chargingStatus();                 
              menu = 5;
            } else if (d9_chargingState == 2) {
              lcd.clear();
              dnum = 9;
              display_door9 = 3;
              door9_chargingStatus();
              menu = 5;
            } else {
              lcd.clear();
              lcd.setCursor(0, 1);
              lcd.print("  DOOR 9 IS UNUSED  ");
              delay(1000);
              lcd.clear();
              reset();
            }
          } else if ((input[0] == '1') and (input[1] == '0')) { // --------------------------- Door 10 --------------------------------------------
            if (d10_chargingState == 1) {
              lcd.clear();
              dnum = 10;
              insertCoin = 1;
              display_door10 = 2;
              door10_chargingStatus();                 
              menu = 5;
            } else if (d10_chargingState == 2) {
              lcd.clear();
              dnum = 10;
              display_door10 = 3;
              door10_chargingStatus();
              menu = 5;
            } else {
              lcd.clear();
              lcd.setCursor(0, 1);
              lcd.print("  DOOR 10 IS UNUSED ");
              delay(1000);
              lcd.clear();
              reset();
            }
          }
          
          else {
            lcd.clear();
            lcd.setCursor(0,1);
            lcd.print("    INVALID INPUT   ");
            lcd.setCursor(0,2);
            lcd.print("     BACK TO MAIN   ");
            delay(1000);
            lcd.clear();
            reset();
          }                   //-------------------------------------------------------------------------------------------------------------------------------------------------
        }else if(menu == 7){  //-----------------------------------------------------------------ADMIN SIDE FUNCTION-------------------------------------------------------------
          int c1 = EEPROM.read(code_add1);
          int c2 = EEPROM.read(code_add2);
          int c3 = EEPROM.read(code_add3);
          int c4 = EEPROM.read(code_add4);

          if((n!=4)||(n<4)){
              lcd.clear();
              lcd.setCursor(0, 1);
              lcd.print("  INVALID PASSCODE  ");
              lcd.setCursor(0, 2);
              lcd.print("    BACK TO MAIN    ");
              delay(1000);
              lcd.clear();
              reset();
          }else {
              checkpass();
              if((code1 == c1)&&(code2 == c2)&&(code3 == c3)&&(code4 == c4)){
                lcd.clear();
                lcd.setCursor(0, 1);
                tone(buzz,500,500);
                lcd.print("   ACCESS GRANTED!  ");
                lcd.setCursor(0, 2);
                lcd.print("     ADMIN PANEL    ");
                delay(1000);
                lcd.clear();
                menu = 8;
                n=0;
                inputCol2 = 7;
                adminView();
              }else {
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("  INVALID PASSCODE  ");
                lcd.setCursor(0, 2);
                lcd.print("    BACK TO MAIN    ");
                delay(1000);
                lcd.clear();
                reset();
              }
          }
        }else if(menu==13) { //-----------------------------------------------------ADMIN OPEN LOCKER FUNCTION----------------------------
          if ((n == 1) and (input[0] == '1')) {
            id = 1;
            deleteFingerprint(id);
            EEPROM.write(door1_id_add, 0);
            id= 0 ;
            display_door1 = 0;
            d1_timerSeconds=0;
            d1_chargingState = 0;
            sec_d1 = 0;
            minu_d1 = 0;
            hr_d1 = 0;
            sub1sec1=0;
            sub1sec2=0;
            count_1=0;
            penalty_1=0;
            menu = 8;
            lcd.clear();
            tone(buzz,1000,500);
            digitalWrite(led1, LOW);
            lcd.setCursor(0, 1);
            lcd.print("    LOCKER 1 OPEN   ");
            digitalWrite(door_locker1, LOW);
            delay(1000);
            digitalWrite(door_locker1, HIGH);
            lcd.clear();
            adminView();
          }else if ((n == 1) and (input[0] == '2')) {
            id = 2;
            deleteFingerprint(id);
            EEPROM.write(door2_id_add, 0);
            id = 0;
            display_door2 = 0;
            d2_timerSeconds=0;
            d2_chargingState = 0;
            sec_d2 = 0;
            minu_d2 = 0;
            hr_d2 = 0;
            sub2sec1=0;
            sub2sec2=0;
            count_2=0;
            penalty_2=0;
            menu = 8;
            lcd.clear();
            tone(buzz,1000,500);
            digitalWrite(led2, LOW);
            lcd.setCursor(0, 1);
            lcd.print("    LOCKER 2 OPEN   ");
            digitalWrite(door_locker2, LOW);
            delay(1000);
            digitalWrite(door_locker2, HIGH);
            lcd.clear();
            adminView();
            
          }else if ((n == 1) and (input[0] == '3')) {
            id = 3;
            deleteFingerprint(id);
            EEPROM.write(door3_id_add, 0);
            id = 0;
            display_door3 = 0;
            d3_timerSeconds=0;
            d3_chargingState = 0;
            sec_d3 = 0;
            minu_d3 = 0;
            hr_d3 = 0;
            sub3sec1=0;
            sub3sec2=0;
            count_3=0;
            penalty_3=0;
            menu = 8;
            lcd.clear();
            tone(buzz,1000,500);
            digitalWrite(led3, LOW);
            lcd.setCursor(0, 1);
            lcd.print("    LOCKER 3 OPEN   ");
            digitalWrite(door_locker3, LOW);
            delay(1000);
            digitalWrite(door_locker3, HIGH);
            lcd.clear();
            adminView();
            
          }else if ((n == 1) and (input[0] == '4')) {
            id = 4;
            deleteFingerprint(id);
            EEPROM.write(door4_id_add, 0);
            id = 0;
            display_door4 = 0;
            d4_timerSeconds=0;
            d4_chargingState = 0;
            sec_d4 = 0;
            minu_d4 = 0;
            hr_d4 = 0;
            sub4sec1=0;
            sub4sec2=0;
            count_4=0;
            penalty_4=0;
            menu = 8;
            lcd.clear();
            tone(buzz,1000,500);
            digitalWrite(led4, LOW);
            lcd.setCursor(0, 1);
            lcd.print("    LOCKER 4 OPEN   ");
            digitalWrite(door_locker4, LOW);
            delay(1000);
            digitalWrite(door_locker4, HIGH);
            lcd.clear();
            adminView();
            
          }else if ((n == 1) and (input[0] == '5')) {
            id = 5;
            deleteFingerprint(id);
            EEPROM.write(door5_id_add, 0);
            id = 0;
            display_door5 = 0;
            d5_timerSeconds=0;
            d5_chargingState = 0;
            sec_d5 = 0;
            minu_d5 = 0;
            hr_d5 = 0;
            sub5sec1=0;
            sub5sec2=0;
            count_5=0;
            penalty_5=0;
            menu = 8;
            lcd.clear();
            tone(buzz,1000,500);
            digitalWrite(led5, LOW);
            lcd.setCursor(0, 1);
            lcd.print("    LOCKER 5 OPEN   ");
            digitalWrite(door_locker5, LOW);
            delay(1000);
            digitalWrite(door_locker5, HIGH);
            lcd.clear();
            adminView();
          
          }else if ((n == 1) and (input[0] == '6')) {
            id = 6;
            deleteFingerprint(id);
            EEPROM.write(door6_id_add, 0);
            id = 0;
            display_door6 = 0;
            d6_timerSeconds=0;
            d6_chargingState = 0;
            sec_d6 = 0;
            minu_d6 = 0;
            hr_d6 = 0;
            sub6sec1=0;
            sub6sec2=0;
            count_6=0;
            penalty_6=0;
            menu = 8;
            lcd.clear();
            tone(buzz,1000,500);
            digitalWrite(led6, LOW);
            lcd.setCursor(0, 1);
            lcd.print("    LOCKER 6 OPEN   ");
            digitalWrite(door_locker6, LOW);
            delay(1000);
            digitalWrite(door_locker6, HIGH);
            lcd.clear();
            adminView();
            
          }else if ((n == 1) and (input[0] == '7')) {
            id = 7;
            deleteFingerprint(id);
            EEPROM.write(door7_id_add, 0);
            id = 0;
            display_door7 = 0;
            d7_timerSeconds=0;
            d7_chargingState = 0;
            sec_d7 = 0;
            minu_d7 = 0;
            hr_d7 = 0;
            sub7sec1=0;
            sub7sec2=0;
            count_7=0;
            penalty_7=0;
            menu = 8;
            lcd.clear();
            tone(buzz,1000,500);
            digitalWrite(led7, LOW);
            lcd.setCursor(0, 1);
            lcd.print("    LOCKER 7 OPEN   ");
            digitalWrite(door_locker7, LOW);
            delay(1000);
            digitalWrite(door_locker7, HIGH);
            lcd.clear();
            adminView();
          
          }else if ((n == 1) and (input[0] == '8')) {
            id = 8;
            deleteFingerprint(id);
            EEPROM.write(door8_id_add, 0);
            id = 0;
            display_door8 = 0;
            d8_timerSeconds=0;
            d8_chargingState = 0;
            sec_d8 = 0;
            minu_d8 = 0;
            hr_d8 = 0;
            sub8sec1=0;
            sub8sec2=0;
            count_8=0;
            penalty_8=0;
            menu = 8;
            lcd.clear();
            tone(buzz,1000,500);
            digitalWrite(led8, LOW);
            lcd.setCursor(0, 1);
            lcd.print("    LOCKER 8 OPEN   ");
            digitalWrite(door_locker8, LOW);
            delay(1000);
            digitalWrite(door_locker8, HIGH);
            lcd.clear();
            adminView();
          }else if ((n == 1) and (input[0] == '9')) {
            id = 9;
            deleteFingerprint(id);
            EEPROM.write(door9_id_add, 0);
            id = 0;
            display_door9 = 0;
            d9_timerSeconds=0;
            d9_chargingState = 0;
            sec_d9 = 0;
            minu_d9 = 0;
            hr_d9 = 0;
            sub9sec1=0;
            sub9sec2=0;
            count_9=0;
            penalty_9=0;
            menu = 8;
            lcd.clear();
            tone(buzz,1000,500);
            digitalWrite(led9, LOW);
            lcd.setCursor(0, 1);
            lcd.print("    LOCKER 9 OPEN   ");
            digitalWrite(door_locker9, LOW);
            delay(1000);
            digitalWrite(door_locker9, HIGH);
            lcd.clear(); 
            adminView();
          
          }else if ((input[0] == '1') and (input[1] == '0')) {
            id = 10;
            deleteFingerprint(id);
            EEPROM.write(door10_id_add, 0);
            id = 0;
            display_door10 = 0;
            d10_timerSeconds=0;
            d10_chargingState = 0;
            sec_d10 = 0;
            minu_d10 = 0;
            hr_d10 = 0;
            sub10sec1=0;
            sub10sec2=0;
            count_10=0;
            penalty_10=0;
            menu = 8;
            lcd.clear();
            tone(buzz,1000,500);
            digitalWrite(led10, LOW);
            lcd.setCursor(0, 1);
            lcd.print("   LOCKER 10 OPEN   ");
            digitalWrite(door_locker10, LOW);
            delay(1000);
            digitalWrite(door_locker10, HIGH);
            lcd.clear();
            adminView();
          }
        }
      break;                       //----------------------------------------------------------------------------------------------------------------------------------
      case 'D':                     //------------------------------------LETTER D------------------------------------------------------------------------------------
        if (menu == 5) {
          switch (dnum) {
            case 1:
              tempo_add = EEPROM.read(door1_id_add);
              if (tempo_add == 1) {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("    ACCESS DOOR 1   ");
                lcd.setCursor(0, 2);
                lcd.print("  PUT YOUR FINGER!  ");
                fingerprint_status = 1;
                while (fingerprint_status == 1) {
                  getFingerprintID();
                  delay(50);
                }
              }
              else {
                lcd.clear();
                tone(buzz,1000,500);
                lcd.setCursor(0, 1);
                lcd.print("    LOCKER 1 OPEN   ");
                insertCoin = 0;
                digitalWrite(door_locker1, LOW);
                delay(1000);
                digitalWrite(door_locker1, HIGH);
                lcd.clear();
              }
              break;
            case 2:
              tempo_add = EEPROM.read(door2_id_add);
              if (tempo_add == 2) {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("    ACCESS DOOR 2   ");
                lcd.setCursor(0, 2);
                lcd.print("  PUT YOUR FINGER!  ");
                fingerprint_status = 1;
                while (fingerprint_status == 1) {
                  getFingerprintID();
                  delay(50);
                }
              }
              else {
                lcd.clear();
                tone(buzz,1000,500);
                lcd.setCursor(0, 1);
                lcd.print("    LOCKER 2 OPEN   ");
                insertCoin = 0;
                digitalWrite(door_locker2, LOW);
                delay(1000);
                digitalWrite(door_locker2, HIGH);
                lcd.clear();
              }
            break;
            case 3:
              tempo_add = EEPROM.read(door3_id_add);
              if (tempo_add == 3) {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("    ACCESS DOOR 3   ");
                lcd.setCursor(0, 2);
                lcd.print("  PUT YOUR FINGER!  ");
                fingerprint_status = 1;
                while (fingerprint_status == 1) {
                  getFingerprintID();
                  delay(50);
                }
              }
              else {
                lcd.clear();
                tone(buzz,1000,500);
                lcd.setCursor(0, 1);
                lcd.print("    LOCKER 3 OPEN   ");
                insertCoin = 0;
                digitalWrite(door_locker3, LOW);
                delay(1000);
                digitalWrite(door_locker3, HIGH);
                lcd.clear();
              }
            break;

            case 4:
              tempo_add = EEPROM.read(door4_id_add);
              if (tempo_add == 4) {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("    ACCESS DOOR 4   ");
                lcd.setCursor(0, 2);
                lcd.print("  PUT YOUR FINGER!  ");
                fingerprint_status = 1;
                while (fingerprint_status == 1) {
                  getFingerprintID();
                  delay(50);
                }
              }
              else {
                lcd.clear();
                tone(buzz,1000,500);
                lcd.setCursor(0, 1);
                lcd.print("    LOCKER 4 OPEN   ");
                insertCoin = 0;
                digitalWrite(door_locker4, LOW);
                delay(1000);
                digitalWrite(door_locker4, HIGH);
                lcd.clear();
              }
            break;

            case 5:
              tempo_add = EEPROM.read(door5_id_add);
              if (tempo_add == 5) {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("    ACCESS DOOR 5   ");
                lcd.setCursor(0, 2);
                lcd.print("  PUT YOUR FINGER!  ");
                fingerprint_status = 1;
                while (fingerprint_status == 1) {
                  getFingerprintID();
                  delay(50);
                }
              }
              else {
                lcd.clear();
                tone(buzz,1000,500);
                lcd.setCursor(0, 1);
                lcd.print("    LOCKER 5 OPEN   ");
                insertCoin = 0;
                digitalWrite(door_locker5, LOW);
                delay(1000);
                digitalWrite(door_locker5, HIGH);
                lcd.clear();
              }
            break;

            case 6:
              tempo_add = EEPROM.read(door6_id_add);
              if (tempo_add == 6) {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("    ACCESS DOOR 6   ");
                lcd.setCursor(0, 2);
                lcd.print("  PUT YOUR FINGER!  ");
                fingerprint_status = 1;
                while (fingerprint_status == 1) {
                  getFingerprintID();
                  delay(50);
                }
              }
              else {
                lcd.clear();
                tone(buzz,1000,500);
                lcd.setCursor(0, 1);
                lcd.print("    LOCKER 6 OPEN   ");
                insertCoin = 0;
                digitalWrite(door_locker6, LOW);
                delay(1000);
                digitalWrite(door_locker6, HIGH);
                lcd.clear();
              }
            break;

            case 7:
              tempo_add = EEPROM.read(door7_id_add);
              if (tempo_add == 7) {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("    ACCESS DOOR 7   ");
                lcd.setCursor(0, 2);
                lcd.print("  PUT YOUR FINGER!  ");
                fingerprint_status = 1;
                while (fingerprint_status == 1) {
                  getFingerprintID();
                  delay(50);
                }
              }
              else {
                lcd.clear();
                tone(buzz,1000,500);
                lcd.setCursor(0, 1);
                lcd.print("    LOCKER 7 OPEN   ");
                insertCoin = 0;
                digitalWrite(door_locker7, LOW);
                delay(1000);
                digitalWrite(door_locker7, HIGH);
                lcd.clear();
              }
            break;

            case 8:
              tempo_add = EEPROM.read(door8_id_add);
              if (tempo_add == 8) {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("    ACCESS DOOR 8   ");
                lcd.setCursor(0, 2);
                lcd.print("  PUT YOUR FINGER!  ");
                fingerprint_status = 1;
                while (fingerprint_status == 1) {
                  getFingerprintID();
                  delay(50);
                }
              }
              else {
                lcd.clear();
                tone(buzz,1000,500);
                lcd.setCursor(0, 1);
                lcd.print("    LOCKER 8 OPEN   ");
                insertCoin = 0;
                digitalWrite(door_locker8, LOW);
                delay(1000);
                digitalWrite(door_locker8, HIGH);
                lcd.clear();
              }
            break;

            case 9:
              tempo_add = EEPROM.read(door9_id_add);
              if (tempo_add == 9) {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("    ACCESS DOOR 9   ");
                lcd.setCursor(0, 2);
                lcd.print("  PUT YOUR FINGER!  ");
                fingerprint_status = 1;
                while (fingerprint_status == 1) {
                  getFingerprintID();
                  delay(50);
                }
              }
              else {
                lcd.clear();
                tone(buzz,1000,500);
                lcd.setCursor(0, 1);
                lcd.print("    LOCKER 9 OPEN   ");
                insertCoin = 0;
                digitalWrite(door_locker9, LOW);
                delay(1000);
                digitalWrite(door_locker9, HIGH);
                lcd.clear();
              }
            break;

            case 10:
              tempo_add = EEPROM.read(door10_id_add);
              if (tempo_add == 10) {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("   ACCESS DOOR 10   ");
                lcd.setCursor(0, 2);
                lcd.print("  PUT YOUR FINGER!  ");
                fingerprint_status = 1;
                while (fingerprint_status == 1) {
                  getFingerprintID();
                  delay(50);
                }
              }
              else {
                lcd.clear();
                tone(buzz,1000,500);
                lcd.setCursor(0, 1);
                lcd.print("   LOCKER 10 OPEN   ");
                insertCoin = 0;
                digitalWrite(door_locker10, LOW);
                delay(1000);
                digitalWrite(door_locker10, HIGH);
                lcd.clear();
              }
            break;
          }
        }else if(menu == 0){
          lcd.clear();
          adminMode();
          menu = 7;
        }else if(menu == 8) {
          inputReset();
          menu=13;
          n=0;
          lcd.clear();
          adminSel();
        }
       break;
    }
  }
}
void startPage()
{
  lcd.setCursor(0, 0);
  lcd.print("   PHONE CHARGING   ");
  lcd.setCursor(0, 1);
  lcd.print("     WITH LOCKER    ");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("C->CHARGE  A->ACCESS");
}
void askForChargingDoor()
{
  lcd.setCursor(0, 0);
  lcd.print("     CHARGE MODE    ");
  lcd.setCursor(0, 1);
  lcd.print("   SELECT DOOR:");
  lcd.print(input);
  lcd.setCursor(0, 2);
  //lcd.print("#->CLEAR ");
  lcd.setCursor(0, 3);
  lcd.print("*->PROCEED   B->BACK");
}
void askForAccessDoor()
{
  lcd.setCursor(0, 0);
  lcd.print("     ACCESS MODE    ");
  lcd.setCursor(0, 1);
  lcd.print("   SELECT DOOR:");
  lcd.print(input);
  lcd.setCursor(0, 2);
  //lcd.print("#->CLEAR ");
  lcd.setCursor(0, 3);
  lcd.print("*->PROCEED   B->BACK");
}
void inputReset() {
  int p;
  inputCol = 15;
  for (p = 0; p < 2; p++) {
    input[p] = ' ';
  }
  n = 0;
}
  void countInput() {                  //----------------------------------------------BInibilang lahat ng character na ininput ni user sa pagpili ng locker number--------------------------
  int c;
  inputCol = 15;
  for (c = 0; c < 2; c++) {
    input[c] = ' ';
  }
  n = 0;
  lcd.setCursor(0, 1);
  lcd.print("    INVALID INPUT   ");
  delay(2000);
  lcd.clear();
  reset();
}
void countInput2() {                  //----------------------------------------------BInibilang lahat ng character na ininput ni Admin sa pagpili ng locker number--------------------------
  int c;
  inputCol = 15;
  for (c = 0; c < 2; c++) {
    input[c] = ' ';
  }
  n = 0;
  lcd.setCursor(0, 1);
  lcd.print("    INVALID INPUT   ");
  delay(2000);
  lcd.clear();
  adminSel();
}

void coinInput() {
  if (insert_state == 1) {
    lcd.setCursor(0, 0);
    lcd.print(" CHARGE IN DOOR - ");
    lcd.print(dnum);
    lcd.setCursor(0, 1);
    lcd.print(" PLEASE INSERT COIN");
    lcd.setCursor(0, 2);
    lcd.print(" CREDITS: ");
    lcd.print(money);
    lcd.setCursor(0, 3);
    lcd.print("C->CHARGE  B->CANCEL");
  } else if (insert_state == 2) {
    switch (dnum) {
      case 1:
        door1_chargingStatus();
        break;
      case 2:
        door2_chargingStatus();
        break;
      case 3:
        door3_chargingStatus();
        break;
      case 4:
        door4_chargingStatus();
        break;
      case 5:
        door5_chargingStatus();
        break;
      case 6:
        door6_chargingStatus();
        break;
      case 7:
        door7_chargingStatus();
        break;
      case 8:
        door8_chargingStatus();
        break;
      case 9:
        door9_chargingStatus();
        break;
      case 10:
        door10_chargingStatus();
        break;
    }
  }

  else if(insert_state == 3){
     lcd.setCursor(15,2);
     lcd.print(money);
  }

}

void door1_chargingStatus() {                                         //  Charging status ng Door 1
  if (display_door1 == 1) {                                           //  Nandito na lahat Access
    lcd.setCursor(0, 0);                                                //  And ADD ng time
    lcd.print("DOOR-> 1 LOCK DOOR ?");
    lcd.setCursor(0, 1);
    lcd.print("  TIME -> ");
    char d1_timest[6];
    sprintf(d1_timest, "%.2d:%.2d:%.2d", ((d1_timerSeconds/60)/60),((d1_timerSeconds/60) %60), (d1_timerSeconds - ((d1_timerSeconds / 60) * 60)));
    lcd.print(d1_timest);
    lcd.setCursor(0, 3);
    lcd.print(" A->YES       B->NO ");
  } else if (display_door1 == 2) {
    tempo_add = EEPROM.read(door1_id_add);
    if (d1_timerSeconds != 0) {
      lcd.setCursor(0, 0);
      lcd.print("   ACCESS DOOR 1");
      lcd.setCursor(0, 1);
      lcd.print("  TIME-> ");
      char d1_timest[6];
      sprintf(d1_timest, "%.2d:%.2d:%.2d", ((d1_timerSeconds/60)/60),((d1_timerSeconds/60) %60), (d1_timerSeconds - ((d1_timerSeconds / 60) * 60)));
      lcd.print(d1_timest);
      lcd.setCursor(0, 2);
      lcd.print(" PLEASE INSERT COIN ");
      insertCoin = 1;
      d1_timerSeconds = d1_timerSeconds + (perminute) * 60;
      incomeCount();
      money = 0;
      perminute=0;
      lcd.setCursor(0, 3);
      lcd.print("B->BACK");
      if (tempo_add == 1) {
        lcd.print("    D->LEAVED");
      } else {
        lcd.setCursor(12, 3);
        lcd.print(" D->OPEN");
      }
  } else {
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("   DOOR 1 TIMES UP");
    delay(2000);
    lcd.clear();
    reset();
  }
  
} 

  else if (display_door1 == 3) {
    lcd.setCursor(0, 0);
    lcd.print("   ACCESS DOOR 1");
    lcd.setCursor(0, 1);
    lcd.print("  TIME->");
    //rem_countd1();
    char timer[6];
    sprintf(timer,"%.2d:%.2d:%.2d", hr_d1,minu_d1,sec_d1);
    lcd.setCursor(10,1);
    lcd.print(timer);
    lcd.setCursor(0, 2);
    lcd.print("PENALTY: ");
    lcd.print(penalty_1);
    lcd.setCursor(0, 3);
    lcd.print("B->BACK");
    tempo_add = EEPROM.read(door1_id_add);
    lcd.print("    D->LEAVED");
  }

  else if(display_door1 == 4){
    lcd.setCursor(0, 0);
    lcd.print("      LOCKER 1      ");
    lcd.setCursor(0, 1);
    lcd.print("    PENALTY: ");
    lcd.print(penalty_1);
    lcd.setCursor(0, 2);
    lcd.print("COIN INSERTED: ");
    coinInput();
    lcd.setCursor(0,3);
    lcd.print("C->PAY       B->BACK");  
  }
}
void door2_chargingStatus() {                                         //  Charging status ng Door 2
  if (display_door2 == 1) {                                           //  Nandito na lahat Access
    lcd.setCursor(0, 0);                                                //  And ADD ng time
    lcd.print("DOOR-> 2 LOCK DOOR ?");
    lcd.setCursor(0, 1);
    lcd.print("  TIME -> ");
    char d2_timest[6];
    sprintf(d2_timest, "%.2d:%.2d:%.2d", ((d2_timerSeconds/60)/60),((d2_timerSeconds/60) %60), (d2_timerSeconds - ((d2_timerSeconds / 60) * 60)));
    lcd.print(d2_timest);
    lcd.setCursor(0, 3);
    lcd.print(" A->YES       B->NO ");
  } else if (display_door2 == 2) {
    
    if(d2_timerSeconds != 0){
      lcd.setCursor(0, 0);
      lcd.print("   ACCESS DOOR 2");
      lcd.setCursor(0, 1);
      lcd.print("  TIME-> ");
      char d2_timest[6];
      sprintf(d2_timest, "%.2d:%.2d:%.2d", ((d2_timerSeconds/60)/60),((d2_timerSeconds/60) %60), (d2_timerSeconds - ((d2_timerSeconds / 60) * 60)));
      lcd.print(d2_timest);
      lcd.setCursor(0, 2);
      lcd.print(" PLEASE INSERT COIN ");
      insertCoin = 1;
      d2_timerSeconds = d2_timerSeconds + (perminute) * 60;
      incomeCount();
      money = 0;
      perminute=0;
      lcd.setCursor(0, 3);
      lcd.print("B->BACK");
      tempo_add = EEPROM.read(door2_id_add);
      if (tempo_add == 2) {
        lcd.print("    D->LEAVED");
      } else {
        lcd.setCursor(12, 3);
        lcd.print(" D->OPEN");
      }  
    }else {
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("   DOOR 2 TIMES UP");
      delay(2000);
      lcd.clear();
      reset();
    }
    
 } else if (display_door2 == 3) {
    lcd.setCursor(0, 0);
    lcd.print("   ACCESS DOOR 2");
    lcd.setCursor(0, 1);
    lcd.print("    TIME->");
    //rem_countd2();
    char d2_rem_timest[6];
    sprintf(d2_rem_timest,"%.2d:%.2d:%.2d", hr_d2,minu_d2,sec_d2);
    lcd.setCursor(10, 1);
    lcd.print(d2_rem_timest);
    lcd.setCursor(0, 2);
    lcd.print("PENALTY: ");
    lcd.print(penalty_2);
    lcd.setCursor(0, 3);
    lcd.print("B->BACK");
    tempo_add = EEPROM.read(door2_id_add);
    lcd.print("    D->LEAVED");
  }

  else if(display_door2 == 4){
    lcd.setCursor(0, 0);
    lcd.print("      LOCKER 2      ");
    lcd.setCursor(0, 1);
    lcd.print("    PENALTY: ");
    lcd.print(penalty_2);
    lcd.setCursor(0, 2);
    lcd.print("COIN INSERTED: ");
    coinInput();
    lcd.setCursor(0,3);
    lcd.print("C->PAY       B->BACK");  
  }
}
void door3_chargingStatus() {                                         //  Charging status ng Door 3
  if (display_door3 == 1) {                                           //  Nandito na lahat Access
    lcd.setCursor(0, 0);                                                //  And ADD ng time
    lcd.print("DOOR-> 3 LOCK DOOR ?");
    lcd.setCursor(0, 1);
    lcd.print("  TIME -> ");
    char d3_timest[6];
    sprintf(d3_timest, "%.2d:%.2d:%.2d", ((d3_timerSeconds/60)/60),((d3_timerSeconds/60) %60), (d3_timerSeconds - ((d3_timerSeconds / 60) * 60)));
    lcd.print(d3_timest);
    lcd.setCursor(0, 3);
    lcd.print(" A->YES       B->NO ");
  } else if (display_door3 == 2) {
    if(d3_timerSeconds != 0){
      lcd.setCursor(0, 0);
      lcd.print("   ACCESS DOOR 3");
      lcd.setCursor(0, 1);
      lcd.print("  TIME-> ");
      char d3_timest[6];
      sprintf(d3_timest, "%.2d:%.2d:%.2d", ((d3_timerSeconds/60)/60),((d3_timerSeconds/60) %60), (d3_timerSeconds - ((d3_timerSeconds / 60) * 60)));
      lcd.print(d3_timest);
      lcd.setCursor(0, 2);
      lcd.print(" PLEASE INSERT COIN ");
      insertCoin = 1;
      d3_timerSeconds = d3_timerSeconds + (money * 1) * 60;
      incomeCount();
      money = 0;
      perminute=0;
      lcd.setCursor(0, 3);
      lcd.print("B->BACK");
      tempo_add = EEPROM.read(door3_id_add);
      if (tempo_add == 3) {
        lcd.print("    D->LEAVED");
      } else {
        lcd.setCursor(12, 3);
        lcd.print(" D->OPEN");
      }
    } else {
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("   DOOR 3 TIMES UP");
      delay(2000);
      lcd.clear();
      reset();
    }
      
 } else if (display_door3 == 3) {
    lcd.setCursor(0, 0);
    lcd.print("   ACCESS DOOR 3");
    lcd.setCursor(0, 1);
    lcd.print("    TIME->");
    //rem_countd3();
    char d3_rem_timest[6];
    sprintf(d3_rem_timest,"%.2d:%.2d:%.2d", hr_d3,minu_d3,sec_d3);
    lcd.setCursor(10, 1);
    lcd.print(d3_rem_timest);
    lcd.setCursor(0, 2);
    lcd.print("PENALTY: ");
    lcd.print(penalty_3);
    lcd.setCursor(0, 3);
    lcd.print("B->BACK");
    tempo_add = EEPROM.read(door3_id_add);
    lcd.print("    D->LEAVED");
  }

  else if(display_door3 == 4){
    lcd.setCursor(0, 0);
    lcd.print("      LOCKER 3      ");
    lcd.setCursor(0, 1);
    lcd.print("    PENALTY: ");
    lcd.print(penalty_3);
    lcd.setCursor(0, 2);
    lcd.print("COIN INSERTED: ");
    coinInput();
    lcd.setCursor(0,3);
    lcd.print("C->PAY       B->BACK");  
  }
}

void door4_chargingStatus() {                                         //  Charging status ng Door 4
  if (display_door4 == 1) {                                           //  Nandito na lahat Access
    lcd.setCursor(0, 0);                                                //  And ADD ng time
    lcd.print("DOOR-> 4 LOCK DOOR ?");
    lcd.setCursor(0, 1);
    lcd.print(" TIME -> ");
    char d4_timest[6];
    sprintf(d4_timest, "%.2d:%.2d:%.2d", ((d4_timerSeconds/60)/60),((d4_timerSeconds/60) %60), (d4_timerSeconds - ((d4_timerSeconds / 60) * 60)));
    lcd.print(d4_timest);
    lcd.setCursor(0, 3);
    lcd.print(" A->YES       B->NO ");
  } else if (display_door4 == 2) {
    if(d4_timerSeconds != 0) {
      lcd.setCursor(0, 0);
      lcd.print("   ACCESS DOOR 4");
      lcd.setCursor(0, 1);
      lcd.print("  TIME-> ");
      char d4_timest[6];
      sprintf(d4_timest, "%.2d:%.2d:%.2d", ((d4_timerSeconds/60)/60),((d4_timerSeconds/60) %60), (d4_timerSeconds - ((d4_timerSeconds / 60) * 60)));
      lcd.print(d4_timest);
      lcd.setCursor(0, 2);
      lcd.print(" PLEASE INSERT COIN ");
      insertCoin = 1;
      d4_timerSeconds = d4_timerSeconds + (perminute) * 60;
      incomeCount();
      money = 0;
      perminute=0;
      lcd.setCursor(0, 3);
      lcd.print("B->BACK");
      tempo_add = EEPROM.read(door4_id_add);
      if (tempo_add == 4) {
        lcd.print("    D->LEAVED");
      } else {
        lcd.setCursor(12, 3);
        lcd.print(" D->OPEN");
      }
    } else {
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("   DOOR 4 TIMES UP");
      delay(1000);
      lcd.clear();
      reset();
    }
      
  } else if (display_door4 == 3) {
    lcd.setCursor(0, 0);
    lcd.print("   ACCESS DOOR 4");
    lcd.setCursor(0, 1);
    lcd.print("  TIME->");
    //rem_countd4();
    char d4_rem_timest[6];
    sprintf(d4_rem_timest,"%.2d:%.2d:%.2d", hr_d4,minu_d4,sec_d4);
    lcd.setCursor(10, 1);
    lcd.print(d4_rem_timest);
    lcd.setCursor(0, 2);
    lcd.print("PENALTY: ");
    lcd.print(penalty_4);
    lcd.setCursor(0, 3);
    lcd.print("B->BACK");
    tempo_add = EEPROM.read(door4_id_add);
    lcd.print("    D->LEAVED");
  }

  else if(display_door4 == 4){
    lcd.setCursor(0, 0);
    lcd.print("      LOCKER 4      ");
    lcd.setCursor(0, 1);
    lcd.print("    PENALTY: ");
    lcd.print(penalty_4);
    lcd.setCursor(0, 2);
    lcd.print("COIN INSERTED: ");
    coinInput();
    lcd.setCursor(0,3);
    lcd.print("C->PAY       B->BACK");  
  }
}

void door5_chargingStatus() {                                         //  Charging status ng Door 5
  if (display_door5 == 1) {                                           //  Nandito na lahat Access
    lcd.setCursor(0, 0);                                                //  And ADD ng time
    lcd.print("DOOR-> 5 LOCK DOOR ?");
    lcd.setCursor(0, 1);
    lcd.print(" TIME -> ");
    char d5_timest[6];
    sprintf(d5_timest, "%.2d:%.2d:%.2d", ((d5_timerSeconds/60)/60),((d5_timerSeconds/60) %60), (d5_timerSeconds - ((d5_timerSeconds / 60) * 60)));
    lcd.print(d5_timest);
    lcd.setCursor(0, 3);
    lcd.print(" A->YES       B->NO ");
  } else if (display_door5 == 2) {
    if(d5_timerSeconds!=0) {
      lcd.setCursor(0, 0);
      lcd.print("   ACCESS DOOR 5");
      lcd.setCursor(0, 1);
      lcd.print("    TIME->");
      char d5_timest[6];
      sprintf(d5_timest, "%.2d:%.2d:%.2d", ((d5_timerSeconds/60)/60),((d5_timerSeconds/60) %60), (d5_timerSeconds - ((d5_timerSeconds / 60) * 60)));
      lcd.print(d5_timest);
      lcd.setCursor(0, 2);
      lcd.print(" PLEASE INSERT COIN ");
      insertCoin = 1;
      incomeCount();
      d5_timerSeconds = d5_timerSeconds + (perminute) * 60;
      money = 0;
      perminute=0;
      lcd.setCursor(0, 3);
      lcd.print("B->BACK");
      tempo_add = EEPROM.read(door5_id_add);
        if (tempo_add == 5) {
          lcd.print("    D->LEAVED");
        } else {
          lcd.setCursor(12, 3);
          lcd.print(" D->OPEN");
        }
    } else {
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("   DOOR 5 TIMES UP");
      delay(1000);
      lcd.clear();
      reset();
    }
  } else if (display_door5 == 3) {
    lcd.setCursor(0, 0);
    lcd.print("   ACCESS DOOR 5");
    lcd.setCursor(0, 1);
    lcd.print("  TIME->");
    //rem_countd5();
    char d5_rem_timest[6];
    sprintf(d5_rem_timest,"%.2d:%.2d:%.2d", hr_d5,minu_d5,sec_d5);
    lcd.setCursor(10, 1);
    lcd.print(d5_rem_timest);
    lcd.setCursor(0, 2);
    lcd.print("PENALTY: ");
    lcd.print(penalty_5);
    lcd.setCursor(0, 3);
    lcd.print("B->BACK");
    tempo_add = EEPROM.read(door5_id_add);
    lcd.print("    D->LEAVED");
  }
  else if(display_door5 == 4){
    lcd.setCursor(0, 0);
    lcd.print("      LOCKER 5      ");
    lcd.setCursor(0, 1);
    lcd.print("    PENALTY: ");
    lcd.print(penalty_5);
    lcd.setCursor(0, 2);
    lcd.print("COIN INSERTED: ");
    coinInput();
    lcd.setCursor(0,3);
    lcd.print("C->PAY       B->BACK");  
  }
}

void door6_chargingStatus() {                                         //  Charging status ng Door 6
  if (display_door6 == 1) {                                           //  Nandito na lahat Access
    lcd.setCursor(0, 0);                                                //  And ADD ng time
    lcd.print("DOOR-> 6 LOCK DOOR ?");
    lcd.setCursor(0, 1);
    lcd.print(" TIME -> ");
    char d6_timest[6];
    sprintf(d6_timest, "%.2d:%.2d:%.2d", ((d6_timerSeconds/60)/60),((d6_timerSeconds/60) %60), (d6_timerSeconds - ((d6_timerSeconds / 60) * 60)));
    lcd.print(d6_timest);
    lcd.setCursor(0, 3);
    lcd.print(" A->YES       B->NO ");
  } else if (display_door6 == 2) {
    tempo_add = EEPROM.read(door6_id_add);
    if (d6_timerSeconds != 0) {
      lcd.setCursor(0, 0);
      lcd.print("   ACCESS DOOR 6");
      lcd.setCursor(0, 1);
      lcd.print("    TIME->");
      char d6_timest[6];
      sprintf(d6_timest, "%.2d:%.2d:%.2d", ((d6_timerSeconds/60)/60),((d6_timerSeconds/60) %60), (d6_timerSeconds - ((d6_timerSeconds / 60) * 60)));
      lcd.print(d6_timest);
      lcd.setCursor(0, 2);
      lcd.print(" PLEASE INSERT COIN ");
      insertCoin = 1;
      incomeCount();
      d6_timerSeconds = d6_timerSeconds + (perminute) * 60;
      money = 0;
      perminute=0;
      lcd.setCursor(0, 3);
      lcd.print("B->BACK");
      if (tempo_add == 6) {
        lcd.print("    D->LEAVED");
      } else {
        lcd.setCursor(12, 3);
        lcd.print(" D->OPEN");
      }
  } else {
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("   DOOR 6 TIMES UP");
    delay(1000);
    lcd.clear();
    reset();
  }
  
} else if (display_door6 == 3) {
  
    lcd.setCursor(0, 0);
    lcd.print("   ACCESS DOOR 6");
    lcd.setCursor(0, 1);
    lcd.print("  TIME->");
    //rem_countd6();
    char d6_rem_timest[6];
    sprintf(d6_rem_timest,"%.2d:%.2d:%.2d", hr_d6,minu_d6,sec_d6);
    lcd.setCursor(10,1);
    lcd.print(d6_rem_timest);
    lcd.setCursor(0, 2);
    lcd.print("PENALTY: ");
    lcd.print(penalty_6);
    lcd.setCursor(0, 3);
    lcd.print("B->BACK");
    tempo_add = EEPROM.read(door6_id_add);
    lcd.print("    D->LEAVED");
  }

  else if (display_door6 == 4){
    lcd.setCursor(0, 0);
    lcd.print("      LOCKER 6      ");
    lcd.setCursor(0, 1);
    lcd.print("    PENALTY: ");
    lcd.print(penalty_6);
    lcd.setCursor(0, 2);
    lcd.print("COIN INSERTED: ");
    coinInput();
    lcd.setCursor(0,3);
    lcd.print("C->PAY       B->BACK");  
  }
}

void door7_chargingStatus() {                                         //  Charging status ng Door 7
  if (display_door7 == 1) {                                           //  Nandito na lahat Access
    lcd.setCursor(0, 0);                                                //  And ADD ng time
    lcd.print("DOOR-> 7 LOCK DOOR ?");
    lcd.setCursor(0, 1);
    lcd.print(" TIME -> ");
    char d7_timest[6];
    sprintf(d7_timest, "%.2d:%.2d:%.2d", ((d7_timerSeconds/60)/60),((d7_timerSeconds/60) %60), (d7_timerSeconds - ((d7_timerSeconds / 60) * 60)));
    lcd.print(d7_timest);
    lcd.setCursor(0, 3);
    lcd.print(" A->YES       B->NO ");
  } else if (display_door7 == 2) {
    tempo_add = EEPROM.read(door7_id_add);
    if (d7_timerSeconds != 0) {
      lcd.setCursor(0, 0);
      lcd.print("   ACCESS DOOR 7");
      lcd.setCursor(0, 1);
      lcd.print("  TIME-> ");
      char d7_timest[6];
      sprintf(d7_timest, "%.2d:%.2d:%.2d", ((d7_timerSeconds/60)/60),((d7_timerSeconds/60) %60), (d7_timerSeconds - ((d7_timerSeconds / 60) * 60)));
      lcd.print(d7_timest);
      lcd.setCursor(0, 2);
      lcd.print(" PLEASE INSERT COIN ");
      insertCoin = 1;
      incomeCount();
      d7_timerSeconds = d7_timerSeconds + (perminute) * 60;
      money = 0;
      perminute=0;
      lcd.setCursor(0, 3);
      lcd.print("B->BACK");
      if (tempo_add == 7) {
        lcd.print("    D->LEAVED");
      } else {
        lcd.setCursor(12, 3);
        lcd.print(" D->OPEN");
      }
  } else {
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("   DOOR 7 TIMES UP");
    delay(2000);
    lcd.clear();
    reset();
  }
  
}  else if (display_door7 == 3) {
  
    lcd.setCursor(0, 0);
    lcd.print("   ACCESS DOOR 7");
    lcd.setCursor(0, 1);
    lcd.print("  TIME->");
    char d7_rem_timest[6];
    sprintf(d7_rem_timest,"%.2d:%.2d:%.2d", hr_d7,minu_d7,sec_d7);
    lcd.setCursor(10,1);
    lcd.print(d7_rem_timest);
    lcd.setCursor(0, 2);
    lcd.print("PENALTY: ");
    lcd.print(penalty_7);
    lcd.setCursor(0, 3);
    lcd.print("B->BACK");
    tempo_add = EEPROM.read(door7_id_add);
    lcd.print("    D->LEAVED");
  }

  else if (display_door7 == 4){
    lcd.setCursor(0, 0);
    lcd.print("      LOCKER 7      ");
    lcd.setCursor(0, 1);
    lcd.print("    PENALTY: ");
    lcd.print(penalty_7);
    lcd.setCursor(0, 2);
    lcd.print("COIN INSERTED: ");
    coinInput();
    lcd.setCursor(0,3);
    lcd.print("C->PAY       B->BACK");  
  }
      
}


void door8_chargingStatus() {                                         //  Charging status ng Door 8
  if (display_door8 == 1) {                                           //  Nandito na lahat Access
    lcd.setCursor(0, 0);                                                //  And ADD ng time
    lcd.print("DOOR-> 8 LOCK DOOR ?");
    lcd.setCursor(0, 1);
    lcd.print("  TIME -> ");
    char d8_timest[6];
    sprintf(d8_timest, "%.2d:%.2d:%.2d", ((d8_timerSeconds/60)/60),((d8_timerSeconds/60) %60), (d8_timerSeconds - ((d8_timerSeconds / 60) * 60)));
    lcd.print(d8_timest);
    lcd.setCursor(0, 3);
    lcd.print(" A->YES       B->NO ");
  } else if (display_door8 == 2) {
    tempo_add = EEPROM.read(door8_id_add);
    if (d8_timerSeconds != 0) {
      lcd.setCursor(0, 0);
      lcd.print("   ACCESS DOOR 8");
      lcd.setCursor(0, 1);
      lcd.print("  TIME-> ");
      char d8_timest[6];
      sprintf(d8_timest, "%.2d:%.2d:%.2d", ((d8_timerSeconds/60)/60),((d8_timerSeconds/60) %60), (d8_timerSeconds - ((d8_timerSeconds / 60) * 60)));
      lcd.print(d8_timest);
      lcd.setCursor(0, 2);
      lcd.print(" PLEASE INSERT COIN ");
      insertCoin = 1;
      incomeCount();
      d8_timerSeconds = d8_timerSeconds + (perminute) * 60;
      money = 0;
      perminute=0;
      lcd.setCursor(0, 3);
      lcd.print("B->BACK");
      if (tempo_add == 8) {
        lcd.print("    D->LEAVED");
      } else {
        lcd.setCursor(12, 3);
        lcd.print(" D->OPEN");
      }
  } else {
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("   DOOR 8 TIMES UP");
    delay(1000);
    lcd.clear();
    reset();
  }
  
} else if (display_door8 == 3) {
  
    lcd.setCursor(0, 0);
    lcd.print("   ACCESS DOOR 8");
    lcd.setCursor(0, 1);
    lcd.print("  TIME->");
    char d8_rem_timest[6];
    sprintf(d8_rem_timest,"%.2d:%.2d:%.2d", hr_d8,minu_d8,sec_d8);
    lcd.setCursor(10,1);
    lcd.print(d8_rem_timest);
    lcd.setCursor(0, 2);
    lcd.print("PENALTY: ");
    lcd.print(penalty_8);
    lcd.setCursor(0, 3);
    lcd.print("B->BACK");
    tempo_add = EEPROM.read(door8_id_add);
    lcd.print("    D->LEAVED");
  }

  else if (display_door8 == 4){
    lcd.setCursor(0, 0);
    lcd.print("      LOCKER 8      ");
    lcd.setCursor(0, 1);
    lcd.print("    PENALTY: ");
    lcd.print(penalty_8);
    lcd.setCursor(0, 2);
    lcd.print("COIN INSERTED: ");
    coinInput();
    lcd.setCursor(0,3);
    lcd.print("C->PAY       B->BACK");  
  }
      
}

void door9_chargingStatus() {                                         //  Charging status ng Door 9
  if (display_door9 == 1) {                                           //  Nandito na lahat Access
    lcd.setCursor(0, 0);                                                //  And ADD ng time
    lcd.print("DOOR-> 9 LOCK DOOR ?");
    lcd.setCursor(0, 1);
    lcd.print("  TIME -> ");
    char d9_timest[6];
    sprintf(d9_timest, "%.2d:%.2d:%.2d", ((d9_timerSeconds/60)/60),((d9_timerSeconds/60) %60), (d9_timerSeconds - ((d9_timerSeconds / 60) * 60)));
    lcd.print(d9_timest);
    lcd.setCursor(0, 3);
    lcd.print(" A->YES       B->NO ");
  } else if (display_door9 == 2) {
    tempo_add = EEPROM.read(door9_id_add);
    if (d9_timerSeconds != 0) {
      lcd.setCursor(0, 0);
      lcd.print("   ACCESS DOOR 9");
      lcd.setCursor(0, 1);
      lcd.print("  TIME-> ");
      char d9_timest[6];
      sprintf(d9_timest, "%.2d:%.2d:%.2d", ((d9_timerSeconds/60)/60),((d9_timerSeconds/60) %60), (d9_timerSeconds - ((d9_timerSeconds / 60) * 60)));
      lcd.print(d9_timest);
      lcd.setCursor(0, 2);
      lcd.print(" PLEASE INSERT COIN ");
      insertCoin = 1;
      d9_timerSeconds = d9_timerSeconds + (perminute) * 60;
      incomeCount();
      money = 0;
      perminute=0;
      lcd.setCursor(0, 3);
      lcd.print("B->BACK");
      if (tempo_add == 9) {
        lcd.print("    D->LEAVED");
      } else {
        lcd.setCursor(12, 3);
        lcd.print(" D->OPEN");
      }
  } else {
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("   DOOR 9 TIMES UP");
    delay(2000);
    lcd.clear();
    reset();
  }
  
} else if (display_door9 == 3) {
  
    lcd.setCursor(0, 0);
    lcd.print("   ACCESS DOOR 9");
    lcd.setCursor(0, 1);
    lcd.print("  TIME->");
    char d9_rem_timest[6];
    sprintf(d9_rem_timest,"%.2d:%.2d:%.2d", hr_d9,minu_d9,sec_d9);
    lcd.setCursor(10,1);
    lcd.print(d9_rem_timest);
    lcd.setCursor(0, 2);
    lcd.print("PENALTY: ");
    lcd.print(penalty_9);
    lcd.setCursor(0, 3);
    lcd.print("B->BACK");
    tempo_add = EEPROM.read(door9_id_add);
    lcd.print("    D->LEAVED");
  }

  else if (display_door9 == 4){
    
    lcd.setCursor(0, 0);
    lcd.print("      LOCKER 9      ");
    lcd.setCursor(0, 1);
    lcd.print("    PENALTY: ");
    lcd.print(penalty_9);
    lcd.setCursor(0, 2);
    lcd.print("COIN INSERTED: ");
    coinInput();
    lcd.setCursor(0,3);
    lcd.print("C->PAY       B->BACK");  
  }

}

void door10_chargingStatus() {                                         //  Charging status ng Door 10
  if (display_door10 == 1) {                                           //  Nandito na lahat Access
    lcd.setCursor(0, 0);                                                //  And ADD ng time
    lcd.print("DOOR- 10 LOCK DOOR?");
    lcd.setCursor(0, 1);
    lcd.print("  TIME -> ");
    char d10_timest[6];
    sprintf(d10_timest, "%.2d:%.2d:%.2d", ((d10_timerSeconds/60)/60),((d10_timerSeconds/60) %60), (d10_timerSeconds - ((d10_timerSeconds / 60) * 60)));
    lcd.print(d10_timest);
    lcd.setCursor(0, 3);
    lcd.print(" A->YES       B->NO ");
  } else if (display_door10 == 2) {
    tempo_add = EEPROM.read(door10_id_add);
    if (d10_timerSeconds != 0) {
      lcd.setCursor(0, 0);
      lcd.print("  ACCESS DOOR 10");
      lcd.setCursor(0, 1);
      lcd.print("  TIME-> ");
      char d10_timest[6];
      sprintf(d10_timest, "%.2d:%.2d:%.2d", ((d10_timerSeconds/60)/60),((d10_timerSeconds/60) %60), (d10_timerSeconds - ((d10_timerSeconds / 60) * 60)));
      lcd.print(d10_timest);
      lcd.setCursor(0, 2);
      lcd.print(" PLEASE INSERT COIN ");
      insertCoin = 1;
      d10_timerSeconds = d10_timerSeconds + (perminute) * 60;
      incomeCount();
      money = 0;
      perminute=0;
      lcd.setCursor(0, 3);
      lcd.print("B->BACK");
      if (tempo_add == 10) {
        lcd.print("    D->LEAVED");
      } else {
        lcd.setCursor(12, 3);
        lcd.print(" D->OPEN");
      }
  } else {
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("  DOOR 10 TIMES UP");
    delay(1000);
    lcd.clear();
    reset();
  }
  
} else if (display_door10 == 3) {
  
    lcd.setCursor(0, 0);
    lcd.print("  ACCESS DOOR 10");
    lcd.setCursor(0, 1);
    lcd.print("  TIME->");
    char d10_rem_timest[6];
    sprintf(d10_rem_timest,"%.2d:%.2d:%.2d", hr_d10,minu_d10,sec_d10);
    lcd.setCursor(10,1);
    lcd.print(d10_rem_timest);
    lcd.setCursor(0, 2);
    lcd.print("PENALTY: ");
    lcd.print(penalty_10);
    lcd.setCursor(0, 3);
    lcd.print("B->BACK");
    tempo_add = EEPROM.read(door10_id_add);
    lcd.print("    D->LEAVED");
  }

  else if (display_door10 == 4){
    
    lcd.setCursor(0, 0);
    lcd.print("     LOCKER 10      ");
    lcd.setCursor(0, 1);
    lcd.print("    PENALTY: ");
    lcd.print(penalty_10);
    lcd.setCursor(0, 2);
    lcd.print("COIN INSERTED: ");
    coinInput();
    lcd.setCursor(0,3);
    lcd.print("C->PAY       B->BACK");  
  }
      
}                      //-------------------------------------------------------------------------------------------------
void coinAcceptor() {  //------------------------------------------------coin acceptor function---------------------------
  long timeFromLastPulse = millis() - timeLastPulse;
  if (pulses > 0 && timeFromLastPulse > 500) {
    // sequence of pulses stopped; determine the coin type;
    if (pulses == 1) {
      if (insertCoin == 1) {
        money += 1;
        coinInput();
        perminute = perminute + 1; 
      }else if(insertCoin == 2) {
        money += 1;
        coinInput();
       }else {}
    } else if (pulses == 5) {
      if (insertCoin == 1) {
        for (i = 0 ; i < pulses ; i++ ) {
          money += 1;
          coinInput();
        }
        perminute = perminute + 10;
      }else if(insertCoin==2){
        for (i = 0 ; i < pulses ; i++ ) {
          money += 1;
          coinInput();
        } 
      } else {}
    } else if (pulses == 10) {
      if (insertCoin == 1) {
        for (i = 0 ; i < pulses ; i++ ) {
          money += 1;
          coinInput();
        }
        perminute = perminute + 25;
      }else if(insertCoin==2) {
         for (i = 0 ; i < pulses ; i++ ) {
          money += 1;
          coinInput();
        }
      } else {}
    } else {
      pulses = 0;
    }
    pulses = 0;
  }
}                                                 //--------------------------------------------------------------------------------------------------------------------------
void chargingDoor() {                             //----------------------Running time ng lahat ng door-----------------------------------------------------------------------
  if (d1_chargingState == 1) {                    //--------------------------------------------------------------------------------------------------------------------------
    if (millis() > d1_time_now + 1000) {
      d1_time_now = millis();
      --d1_timerSeconds;
      door1_chargingStatus();
      if (d1_timerSeconds <= 0) {
        d1_chargingState = 0;
        digitalWrite(current_d1, HIGH);
        digitalWrite(led1, LOW);
        tempo_add = EEPROM.read(door1_id_add);
        if (tempo_add == 1) {
          //kapag nakalock mag run 2min to leave door1 //-------------------------------------------------------------------
          d1_chargingState = 2;
          tone(buzz,1000,1000);
          //reset();
        } else {;
          tone(buzz,500,500);
          digitalWrite(door_locker1, LOW);
          delay(1000);
          digitalWrite(door_locker1, HIGH);
          state1 = 2;
          d1state = 0;
          //lcd.clear();
          //reset();
        }
      } else {
        digitalWrite(current_d1, LOW);
        digitalWrite(led1, HIGH);
      }
    }
  } else if (d1_chargingState == 2) {
    if (millis() > d1_time_now + 1000) {
      d1_time_now = millis();
      if(sec_d1==59){
        ++minu_d1;
        sec_d1=0;
          if(count_1==0) {
            sub1sec1 =sub1sec1 + 1;
          }else if(count_1==1){
            sub1sec2 = sub1sec2 + 1;
          }
        if(minu_d1 == 60){
          ++hr_d1;
          minu_d1 = 0;     
        }
      }else {
        ++sec_d1;
       }
       if(sub1sec1==2){
        penalty_1 = penalty_1 + 10;
        sub1sec1 = 0;
        count_1 = 1;
       }else if(sub1sec2==30){
        penalty_1 = penalty_1 + 10;
        sub1sec2 = 0;
        count_1 = 1;
       }
      door1_chargingStatus();

      if(ledState1 == LOW) {
        ledState1 = HIGH;
      }else {
        ledState1 = LOW;
      }
      digitalWrite(led1,ledState1);
    }
  }
  if (d2_chargingState == 1) { // -------------------------------door 2 running time -----------------------
    if (millis() > d2_time_now + 1000) {
      d2_time_now = millis();
      --d2_timerSeconds;
      door2_chargingStatus();
      if (d2_timerSeconds <= 0) {
        d2_chargingState = 0;
        digitalWrite(current_d2, HIGH);
        digitalWrite(led2, LOW);
        tempo_add = EEPROM.read(door2_id_add);
        if (tempo_add == 2) {
          d2_chargingState = 2;
          tone(buzz,1000,1000);
          //reset();
        } else {
          tone(buzz,500,500);
          digitalWrite(door_locker2, LOW);
          delay(1000);
          digitalWrite(door_locker2, HIGH);
          state2 = 2;
          d2state = 0;
          //lcd.clear();
          //reset();
        }
      } else {
        digitalWrite(current_d2, LOW);
        digitalWrite(led2, HIGH);
      }
    }
  }else if (d2_chargingState == 2) {
    if (millis() > d2_time_now + 1000) {
      d2_time_now = millis();
      if(sec_d2==59){
        ++minu_d2;
        sec_d2=0;
          if(count_2==0) {
            sub2sec1 =sub2sec1 + 1;
          }else if(count_2==1){
            sub2sec2 = sub2sec2 + 1;
          }
        if(minu_d2 == 60){
          ++hr_d2;
          minu_d2 = 0;     
        }
      }else {
        ++sec_d2;
       }
       if(sub2sec1==2){
        penalty_2 = penalty_2 + 10;
        sub2sec1 = 0;
        count_2 = 1;
       }else if(sub2sec2==30){
        penalty_2 = penalty_2 + 10;
        sub2sec2 = 0;
        count_2 = 1;
       }
      door2_chargingStatus();
      
      if(ledState2 == LOW) {
        ledState2 = HIGH;
      }else {
        ledState2 = LOW;
      }
      digitalWrite(led2,ledState2);
    }
  }

  if (d3_chargingState == 1) { // -------------------------------door 3 running time -----------------------
    if (millis() > d3_time_now + 1000) {
      d3_time_now = millis();
      --d3_timerSeconds;
      door3_chargingStatus();
      if (d3_timerSeconds <= 0) {
        d3_chargingState = 0;
        digitalWrite(led3, LOW);
        digitalWrite(current_d3, HIGH);
        tempo_add = EEPROM.read(door3_id_add);
        if (tempo_add == 3) {
          d3_chargingState = 2;
          tone(buzz,1000,1000);
          
        } else {
          tone(buzz,500,500);
          digitalWrite(door_locker3, LOW);
          delay(1000);
          digitalWrite(door_locker3, HIGH);
          state3 = 2;
          d3state = 0;
        }
      } else {
        digitalWrite(current_d3, LOW);
        digitalWrite(led3, HIGH);
      }
    }
  }else if (d3_chargingState == 2) {
    if (millis() > d3_time_now + 1000) {
      d3_time_now = millis();
      if(sec_d3==59){
        ++minu_d3;
        sec_d3=0;
          if(count_3==0) {
            sub3sec1 =sub3sec1 + 1;
          }else if(count_3==1){
            sub3sec2 = sub3sec2 + 1;
          }
        if(minu_d3 == 60){
          ++hr_d3;
          minu_d3 = 0;     
        }
      }else {
        ++sec_d3;
       }
       if(sub3sec1==2){
        penalty_3 = penalty_3 + 10;
        sub3sec1 = 0;
        count_3 = 1;
       }else if(sub3sec2==30){
        penalty_3 = penalty_3 + 10;
        sub3sec2 = 0;
        count_3 = 1;
       }
      door3_chargingStatus();
      
      if(ledState3 == LOW) {
        ledState3 = HIGH;
      }else {
        ledState3 = LOW;
      }
      digitalWrite(led3,ledState3);
    }
  }

  
  if (d4_chargingState == 1) { // -------------------------------door 4 running time -----------------------
    if (millis() > d4_time_now + 1000) {
      d4_time_now = millis();
      --d4_timerSeconds;
      door4_chargingStatus();
      if (d4_timerSeconds <= 0) {
        d4_chargingState = 0;
        digitalWrite(led4, LOW);
        digitalWrite(current_d4, HIGH);
        tempo_add = EEPROM.read(door4_id_add);
        if (tempo_add == 4) {
          d4_chargingState = 2;
          tone(buzz,1000,1000);
        } else {
          tone(buzz,500,500);
          digitalWrite(door_locker4, LOW);
          delay(1000);
          digitalWrite(door_locker4, HIGH);
          state4 = 2;
          d4state = 0;
        }
      } else {
        digitalWrite(led4, HIGH);
        digitalWrite(current_d4, LOW);
      }
    }
  }else if (d4_chargingState == 2) {
    if (millis() > d4_time_now + 1000) {
      d4_time_now = millis();
      if(sec_d4==59){
        ++minu_d4;
        sec_d4=0;
          if(count_4==0) {
            sub4sec1 =sub4sec1 + 1;
          }else if(count_4==1){
            sub4sec2 = sub4sec2 + 1;
          }
        if(minu_d4 == 60){
          ++hr_d4;
          minu_d4 = 0;     
        }
      }else {
        ++sec_d4;
       }
       if(sub4sec1==2){
        penalty_4 = penalty_4 + 10;
        sub4sec1 = 0;
        count_4 = 1;
       }else if(sub4sec2==30){
        penalty_4 = penalty_4 + 10;
        sub4sec2 = 0;
        count_4 = 1;
       }
      door4_chargingStatus();
      
      if(ledState4 == LOW) {
        ledState4 = HIGH;
      }else {
        ledState4 = LOW;
      }
      digitalWrite(led4,ledState4);
    }
  }

  if (d5_chargingState == 1) { // -------------------------------door 5 running time -----------------------
    if (millis() > d5_time_now + 1000) {
      d5_time_now = millis();
      --d5_timerSeconds;
      door5_chargingStatus();
      if (d5_timerSeconds <= 0) {
        d5_chargingState = 0;
        digitalWrite(led5, LOW);
        digitalWrite(current_d5, HIGH);
        tempo_add = EEPROM.read(door5_id_add);
        if (tempo_add == 5) {
          d5_chargingState = 2;
          tone(buzz,1000,1000);
        } else {
          tone(buzz,1000,1000);
          digitalWrite(door_locker5, LOW);
          delay(1000);
          digitalWrite(door_locker5, HIGH);
          state5 = 2;
          d5state = 0;
        }
      } else {
        digitalWrite(led5, HIGH);
        digitalWrite(current_d5, LOW);
      }
    }
  } else if (d5_chargingState == 2) {
    if (millis() > d5_time_now + 1000) {
      d5_time_now = millis();
      if(sec_d5==59){
        ++minu_d5;
        sec_d5=0;
          if(count_5==0) {
            sub5sec1 =sub5sec1 + 1;
          }else if(count_5==1){
            sub5sec2 = sub5sec2 + 1;
          }
        if(minu_d5 == 60){
          ++hr_d5;
          minu_d5 = 0;     
        }
      }else {
        ++sec_d5;
       }
       if(sub5sec1==2){
        penalty_5 = penalty_5 + 10;
        sub5sec1 = 0;
        count_5 = 1;
       }else if(sub5sec2==30){
        penalty_5 = penalty_5 + 10;
        sub5sec2 = 0;
        count_5 = 1;
       }
      door5_chargingStatus();
      
      if(ledState5 == LOW) {
        ledState5 = HIGH;
      }else {
        ledState5 = LOW;
      }
      digitalWrite(led5,ledState5);
    }
  }

  if (d6_chargingState == 1) { //---------------------------------Door 6 running time---------------------------------------------------
    if (millis() > d6_time_now + 1000) {
      d6_time_now = millis();
      --d6_timerSeconds;
      door6_chargingStatus();
      if (d6_timerSeconds <= 0) {
        d6_chargingState = 0;
        digitalWrite(led6, LOW);
        digitalWrite(current_d6, HIGH);
        tempo_add = EEPROM.read(door6_id_add);
        if (tempo_add == 6) {                            
          d6_chargingState = 2;
          tone(buzz,1000,1000);
        } else {
          tone(buzz,500,500);
          digitalWrite(door_locker6, LOW);
          delay(1000);
          digitalWrite(door_locker6, HIGH);
          state6 = 2;
          d6state = 0;
        }
      } else {
        digitalWrite(led6, HIGH);
        digitalWrite(current_d6, LOW);
      }
    }
  }else if (d6_chargingState == 2) {
    if (millis() > d6_time_now + 1000) {
      d6_time_now = millis();
      if(sec_d6==59){
        ++minu_d6;
        sec_d6=0;
          if(count_6==0) {
            sub6sec1 =sub6sec1 + 1;
          }else if(count_6==1){
            sub6sec2 = sub6sec2 + 1;
          }
        if(minu_d6 == 60){
          ++hr_d6;
          minu_d6 = 0;     
        }
      }else {
        ++sec_d6;
       }
       if(sub6sec1==2){
        penalty_6 = penalty_6 + 10;
        sub6sec1 = 0;
        count_6 = 1;
       }else if(sub6sec2==30){
        
        penalty_6 = penalty_6 + 10;
        sub6sec2 = 0;
        count_6 = 1;
       }
       
      door6_chargingStatus();
      
      if(ledState6 == LOW) {
        ledState6 = HIGH;
      }else {
        ledState6 = LOW;
      }
      digitalWrite(led6,ledState6);
    }
  }
  if (d7_chargingState == 1) { //---------------------------------Door 7 running time---------------------------------------------------
    if (millis() > d7_time_now + 1000) {
      d7_time_now = millis();
      --d7_timerSeconds;
      door7_chargingStatus();
      if (d7_timerSeconds <= 0) {
        d7_chargingState = 0;
        digitalWrite(led7, LOW);
        digitalWrite(current_d7, HIGH);
        tempo_add = EEPROM.read(door7_id_add);
        if (tempo_add == 7) {                                                   
          d7_chargingState = 2;
          tone(buzz,1000,1000);
         
        } else {
          tone(buzz,500,500);
          digitalWrite(door_locker7, LOW);
          delay(1000);
          digitalWrite(door_locker7, HIGH);
          state7 = 2;
          d7state = 0;
        }
      } else {
        digitalWrite(led7, HIGH);
        digitalWrite(current_d7, LOW);
      }
    }
  } else if (d7_chargingState == 2) {
    if (millis() > d7_time_now + 1000) {
      d7_time_now = millis();
      if(sec_d7==59){
        ++minu_d7;
        sec_d7=0;
          if(count_7==0) {
            sub7sec1 =sub7sec1 + 1;
          }else if(count_7==1){
            sub7sec2 = sub7sec2 + 1;
          }
        if(minu_d7 == 60){
          ++hr_d7;
          minu_d7 = 0;     
        }
      }else {
        ++sec_d7;
       }
       if(sub7sec1==2){
        penalty_7 = penalty_7 + 10;
        sub7sec1 = 0;
        count_7 = 1;
       }else if(sub7sec2==30){
        penalty_7 = penalty_7 + 10;
        sub7sec2 = 0;
        count_7 = 1;
       }
       
      door7_chargingStatus();
      
      if(ledState7 == LOW) {
        ledState7 = HIGH;
      }else {
        ledState7 = LOW;
      }
      digitalWrite(led7,ledState7);
    }
  }

  if (d8_chargingState == 1) { //---------------------------------Door 8 running time---------------------------------------------------
    if (millis() > d8_time_now + 1000) {
      d8_time_now = millis();
      --d8_timerSeconds;
      door8_chargingStatus();
      if (d8_timerSeconds <= 0) {
        d8_chargingState = 0;
        digitalWrite(led8, LOW);
        digitalWrite(current_d8, HIGH);
        tempo_add = EEPROM.read(door8_id_add);
        if (tempo_add == 8) {
                              
          d8_chargingState = 2;
          tone(buzz,1000,1000);
        
        } else {;
          tone(buzz,500,500);
          digitalWrite(door_locker8, LOW);
          delay(1000);
          digitalWrite(door_locker8, HIGH);
          state8 = 2;
          d8state = 0;
        }
      } else {
        digitalWrite(led8, HIGH);
        digitalWrite(current_d8, LOW);
      }
    }
  } else if (d8_chargingState == 2) {
    if (millis() > d8_time_now + 1000) {
      d8_time_now = millis();
      if(sec_d8==59){
        ++minu_d8;
        sec_d8=0;
          if(count_8==0) {
            sub8sec1 =sub8sec1 + 1;
          }else if(count_8==1){
            sub8sec2 = sub8sec2 + 1;
          }
        if(minu_d8 == 60){
          ++hr_d8;
          minu_d8 = 0;     
        }
      }else {
        ++sec_d8;
       }
       if(sub8sec1==2){
        penalty_8 = penalty_8 + 10;
        sub8sec1 = 0;
        count_8 = 1;
       }else if(sub8sec2==30){
        penalty_8 = penalty_8 + 10;
        sub8sec2 = 0;
        count_8 = 1;
       }
       
      door8_chargingStatus();
      
      if(ledState8 == LOW) {
        ledState8 = HIGH;
      }else {
        ledState8 = LOW;
      }
      digitalWrite(led8,ledState8);
    }
  }
   if (d9_chargingState == 1) { //---------------------------------Door 9 running time---------------------------------------------------
    if (millis() > d9_time_now + 1000) {
      d9_time_now = millis();
      --d9_timerSeconds;
      door9_chargingStatus();
      if (d9_timerSeconds <= 0) {
        d9_chargingState = 0;
        digitalWrite(led9, LOW);
        digitalWrite(current_d9, HIGH);
        tempo_add = EEPROM.read(door9_id_add);
        if (tempo_add == 9) {
                                
          d9_chargingState = 2;
          tone(buzz,1000,1000);
          
        } else {;
          tone(buzz,500,500);
          digitalWrite(door_locker9, LOW);
          delay(1000);
          digitalWrite(door_locker9, HIGH);
          state9 = 2;
          d9state = 0;
        }
      } else {
        digitalWrite(led9, HIGH);
        digitalWrite(current_d9, LOW);
      }
    }
  } else if (d9_chargingState == 2) {
    if (millis() > d9_time_now + 1000) {
      d9_time_now = millis();
      if(sec_d9==59){
        ++minu_d9;
        sec_d9=0;
          if(count_9==0) {
            sub9sec1 =sub9sec1 + 1;
          }else if(count_9==1){
            sub9sec2 = sub9sec2 + 1;
          }
        if(minu_d9 == 60){
          ++hr_d9;
          minu_d9 = 0;     
        }
      }else {
        ++sec_d9;
       }
       if(sub9sec1==2){
        penalty_9 = penalty_9 + 10;
        sub9sec1 = 0;
        count_9 = 1;
       }else if(sub9sec2==30){
        penalty_9 = penalty_9 + 10;
        sub9sec2 = 0;
        count_9 = 1;
       }
       
      door9_chargingStatus();
      
      if(ledState9 == LOW) {
        ledState9 = HIGH;
      }else {
        ledState9 = LOW;
      }
      digitalWrite(led9,ledState9);
    }
  }

  if (d10_chargingState == 1) { //---------------------------------Door 10 running time---------------------------------------------------
    if (millis() > d10_time_now + 1000) {
      d10_time_now = millis();
      --d10_timerSeconds;
      door10_chargingStatus();
      if (d10_timerSeconds <= 0) {
        d10_chargingState = 0;
        digitalWrite(led10, LOW);
        digitalWrite(current_d10, HIGH);
        tempo_add = EEPROM.read(door10_id_add);
        if (tempo_add == 10) {
                                
          d10_chargingState = 2;
          tone(buzz,1000,1000);
          
        } else {;
          tone(buzz,500,500);
          digitalWrite(door_locker10, LOW);
          delay(1000);
          digitalWrite(door_locker10, HIGH);
          state10 = 2;
          d10state = 0;
        }
      } else {
        digitalWrite(led10, HIGH);
        digitalWrite(current_d10, LOW);
      }
    }
  } else if (d10_chargingState == 2) {
    if (millis() > d10_time_now + 1000) {
      d10_time_now = millis();
      if(sec_d10==59){
        ++minu_d10;
        sec_d10=0;
          if(count_10==0) {
            sub10sec1 =sub10sec1 + 1;
          }else if(count_10==1){
            sub10sec2 = sub10sec2 + 1;
          }
        if(minu_d10 == 60){
          ++hr_d10;
          minu_d10 = 0;     
        }
      }else {
        ++sec_d10;
       }
       if(sub10sec1==2){
        penalty_10 = penalty_10 + 10;
        sub10sec1 = 0;
        count_10 = 1;
       }else if(sub10sec2==30){
        penalty_10 = penalty_10 + 10;
        sub10sec2 = 0;
        count_10 = 1;
       }
       
      door10_chargingStatus();
      
      if(ledState10 == LOW) {
        ledState10 = HIGH;
      }else {
        ledState10 = LOW;
      }
      digitalWrite(led10,ledState10);
    }
  }
}                      //-----------------------------------------------------------------------
void enrollFunction() {//------------------------------ENROLL FUNCTION--------------------------
  if(id == 0) {        //----------------------------------------------------------------------
    lcd.setCursor(0, 1);
    lcd.print("    ARE YOU SURE ?  ");
    lcd.setCursor(0, 3);
    lcd.print("A->YES     B->CANCEL");    
  }else {
    lcd.setCursor(0, 0);
    lcd.print("   LOCKED LOCKER ");
    lcd.print(id);
    lcd.setCursor(0, 2);
    lcd.print("   PUT YOUR FINGER  "); 
    while (fingerprint_status == 1) {
      getFingerprintEnroll();
    }
  }
  
}
uint8_t getFingerprintEnroll() {
  int p = -1;
  Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Image taken");
        break;
      case FINGERPRINT_NOFINGER:
        Serial.println(".");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Imaging error");
        break;
      default:
        Serial.println("Unknown error");
        break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  Serial.println("Remove finger");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("    ENROLL MODE !   ");
  lcd.setCursor(0, 2);
  lcd.print(" REMOVE YOUR FINGER");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Place same finger again");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("    ENROLL MODE !   ");
  lcd.setCursor(0, 2);
  lcd.print(" PLACE SAME FINGER! ");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Image taken");
        break;
      case FINGERPRINT_NOFINGER:
        Serial.print(".");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Imaging error");
        break;
      default:
        Serial.println("Unknown error");
        break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  Serial.print("Creating model for #");  Serial.println(id);

  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("    ENROLL MODE !   ");
    lcd.setCursor(0, 2);
    lcd.print("      TRY AGAIN     ");
    delay(1000);
    id=0;
    menu=10;
    fingerprint_status = 0;
    lcd.clear();
    enrollFunction();
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("       LOCKER       ");
    lcd.setCursor(0, 2);
    lcd.print(" SUCCESSFULY LOCKED!");
    delay(2000);
    lcd.clear();
    reset();

  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }
}
void reset() {  //------------------------------------------------------------------------------RESET FUNCTION---------------------------------------------------------------

  startPage();
  menu = 0;
  //money = 0;
  n = 0;
  id = 0;
  d1state = 0;
  d2state = 0;
  d3state = 0;
  d4state = 0;
  d5state = 0;
  d6state = 0;
  d7state = 0;
  d8state = 0;
  d9state = 0;
  d10state = 0;
  dnum = 0;
  inputCol2 = 7;
  tempo_add = 0;
  insertCoin = 0;
  insert_state = 0;
  inputReset();
  fingerprint_status = 0;
  display_door1 = 0;
  display_door2 = 0;
  display_door3 = 0;
  display_door4 = 0;
  display_door5 = 0;
  display_door6 = 0;
  display_door7 = 0;
  display_door8 = 0;
  display_door9 = 0;
  display_door10 = 0;
}                  //-----------------------------------------------------------------------------------------------------------------------------------------------------------
void doorstat() { //------------------------------------------------------DOOR STATUSN NG SENSOR--------------------------------------------------------------------------------
  d1state = analogRead(door1state);
  if (d1state < 5) {
    if (state1 == 1) {
      //delay(1000);
      lcd.clear();
      insertCoin = 1;
      insert_state = 1;
      lcd.setCursor(0,1);
      lcd.print("     PLEASE WAIT..  ");
      delay(1000);
      lcd.clear();
      coinInput();
      menu = 2;
      state1 = 3;
    } else if (state1 == 2) {
      state1 = 0;
    }
  } else { }

  d2state = analogRead(door2state);
  if (d2state < 5) {
    if (state2 == 1) {
      lcd.clear();
      insertCoin = 1;
      insert_state = 1;
      lcd.setCursor(0,1);
      lcd.print("     PLEASE WAIT..  ");
      delay(1000);
      lcd.clear();
      coinInput();
      menu = 2;
      state2 = 3;
    } else if (state2 == 2) {
      state2 = 0;
    }
  } else { }

  d3state = analogRead(door3state);
  if (d3state < 5) {
    if (state3 == 1) {
      lcd.clear();
      insertCoin = 1;
      insert_state = 1;
      lcd.setCursor(0,1);
      lcd.print("     PLEASE WAIT..  ");
      delay(1000);
      lcd.clear();
      coinInput();
      menu = 2;
      state3 = 3;
    } else if (state3 == 2) {
      state3 = 0;
    }
  } else { }

  d4state = analogRead(door4state);
  if (d4state < 5) {
    if (state4 == 1) {
      lcd.clear();
      insertCoin = 1;
      insert_state = 1;
      lcd.setCursor(0,1);
      lcd.print("     PLEASE WAIT..  ");
      delay(1000);
      lcd.clear();
      coinInput();
      menu = 2;
      state4 = 3;
    } else if (state4 == 2) {
      state4 = 0;
    }
  } else { }

  d5state = analogRead(door5state);
  if (d5state == 1) {
    if (state5 == 1) {
      lcd.clear();
      insertCoin = 1;
      insert_state = 1;
      lcd.setCursor(0,1);
      lcd.print("     PLEASE WAIT..  ");
      delay(1000);
      lcd.clear();
      coinInput();
      menu = 2;
      state5 = 3;
    } else if (state5 == 2) {
      state5 = 0;
    }
  } else { }

  d6state = analogRead(door6state);
  if (d6state < 5) {
    if (state6 == 1) {
     lcd.clear();
      insertCoin = 1;
      insert_state = 1;
      lcd.setCursor(0,1);
      lcd.print("     PLEASE WAIT..  ");
      delay(1000);
      lcd.clear();
      coinInput();
      menu = 2;
      state6 = 3;
    } else if (state6 == 2) {
      state6 = 0;
    }
  } else { }

  d7state = analogRead(door7state);
  if (d7state < 5) {
    if (state7 == 1) {
      lcd.clear();
      insertCoin = 1;
      insert_state = 1;
      lcd.setCursor(0,1);
      lcd.print("     PLEASE WAIT..  ");
      delay(1000);
      lcd.clear();
      coinInput();
      menu = 2;
      state7 = 3;
    } else if (state7 == 2) {
      state7 = 0;
    }
  } else { }

  d8state = analogRead(door8state);
  if (d8state < 5) {
    if (state8 == 1) {
      lcd.clear();
      insertCoin = 1;
      insert_state = 1;
      lcd.setCursor(0,1);
      lcd.print("     PLEASE WAIT..  ");
      delay(1000);
      lcd.clear();
      coinInput();
      menu = 2;
      state8 = 3;
    } else if (state8 == 2) {
      state8 = 0;
    }
  } else { }
  
  d9state = analogRead(door9state);
  if (d9state < 5) {
    if (state9 == 1) {
      lcd.clear();
      insertCoin = 1;
      insert_state = 1;
      lcd.setCursor(0,1);
      lcd.print("     PLEASE WAIT..  ");
      delay(1000);
      lcd.clear();
      coinInput();
      menu = 2;
      state9 = 3;
    } else if (state9 == 2) {
      state9 = 0;
    }
  } else { }

  d10state = analogRead(door10state);
  if (d10state < 5) {
    if (state10 == 1) {
      lcd.clear();
      insertCoin = 1;
      insert_state = 1;
      lcd.setCursor(0,1);
      lcd.print("     PLEASE WAIT..  ");
      delay(1000);
      lcd.clear();
      coinInput();
      menu = 2;
      state10 = 3;
    } else if (state10 == 2) {
      state10 = 0;
    }
  } else { }
  
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("     FINGERPRINT    ");
    lcd.setCursor(0, 2);
    lcd.print(" IS NOT REGISTERED! ");
    delay(1000);
    reset();
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  // found a match!                                           //-------------------------------------------------------------------------------------------------------------------
  Serial.print("Found ID #"); Serial.print(finger.fingerID);  //--------------------------------------------------------VERIFY FINGERPRINT-----------------------------------------
  Serial.print(" with confidence of "); Serial.println(finger.confidence);//-------------------------------------------------------------------------------------------------------
  if (tempo_add == finger.fingerID) {
    switch (tempo_add) {
      case 1:
        if(penalty_1 != 0){
          lcd.clear();
          menu=11;
          insertCoin = 2;
          insert_state=3;
          fingerprint_status=0;
          display_door1 = 4;
          door1_chargingStatus();           
        }
        else 
        {
          d1_chargingState = 0;
          d1_timerSeconds = 0;
          digitalWrite(led1, LOW);
          digitalWrite(current_d1, HIGH);
          state1 = 2;
          lcd.clear();
          EEPROM.write(door1_id_add, 0);
          lcd.setCursor(0, 1);
          lcd.print("      THANK YOU    ");
          lcd.setCursor(0, 2);
          lcd.print("    CHARGE AGAIN!  ");
          digitalWrite(door_locker1, LOW);
          delay(1000);
          digitalWrite(door_locker1, HIGH);
          lcd.clear();
          id = 1;
          deleteFingerprint(id);
          return finger.fingerID;
          reset(); 
        }
     break;
     case 2:
        if(penalty_2 != 0){
          lcd.clear();
          menu=11;
          insertCoin = 2;
          insert_state = 3;
          fingerprint_status=0;
          display_door2 = 4;
          door2_chargingStatus();        
        }
        else
        {
          d2_chargingState = 0;
          d2_timerSeconds = 0;
          digitalWrite(led2, LOW);
          digitalWrite(current_d2, HIGH);
          state2 = 2;
          lcd.clear();
          EEPROM.write(door2_id_add, 0);
          lcd.setCursor(0, 1);
          lcd.print("      THANK YOU    ");
          lcd.setCursor(0, 2);
          lcd.print("    CHARGE AGAIN   ");
          digitalWrite(door_locker2, LOW);
          delay(1000);
          digitalWrite(door_locker2, HIGH);
          lcd.clear();
          id = 2;
          deleteFingerprint(id);
          return finger.fingerID;
          reset();
        }
     break;
     case 3:
        if(penalty_3 != 0){
          lcd.clear();
          menu=11;
          insertCoin = 2;
          insert_state = 3;
          fingerprint_status=0;
          display_door3 = 4;
          door3_chargingStatus();        
        }
        else
        {
          d3_chargingState = 0;
          d3_timerSeconds = 0;
          digitalWrite(led3, LOW);
          digitalWrite(current_d3, HIGH);
          state3 = 2;
          lcd.clear();
          EEPROM.write(door3_id_add, 0);
          lcd.setCursor(0, 1);
          lcd.print("      THANK YOU    ");
          lcd.setCursor(0, 2);
          lcd.print("    CHARGE AGAIN   ");
          digitalWrite(door_locker3, LOW);
          delay(1000);
          digitalWrite(door_locker3, HIGH);
          lcd.clear();
          id = 3;
          deleteFingerprint(id);
          return finger.fingerID;
          reset();
        }
     break;
     case 4:
        if(penalty_4 != 0){
          lcd.clear();
          menu=11;
          insertCoin = 2;
          insert_state = 3;
          fingerprint_status=0;
          display_door4 = 4;
          door4_chargingStatus();        
        }
        else
        {
          d4_chargingState = 0;
          d4_timerSeconds = 0;
          digitalWrite(led4, LOW);
          digitalWrite(current_d4, HIGH);
          state4 = 2;
          lcd.clear();
          EEPROM.write(door4_id_add, 0);
          lcd.setCursor(0, 1);
          lcd.print("      THANK YOU    ");
          lcd.setCursor(0, 2);
          lcd.print("    CHARGE AGAIN   ");
          digitalWrite(door_locker4, LOW);
          delay(1000);
          digitalWrite(door_locker4, HIGH);
          lcd.clear();
          id = 4;
          deleteFingerprint(id);
          return finger.fingerID;
          reset();
        }
     break;
     case 5:
        if(penalty_5 != 0){
          lcd.clear();
          menu=11;
          insertCoin = 2;
          insert_state = 3;
          fingerprint_status=0;
          display_door5 = 4;
          door5_chargingStatus();        
        }
        else
        {
          d5_chargingState = 0;
          d5_timerSeconds = 0;
          digitalWrite(led5, LOW);
          digitalWrite(current_d3, HIGH);
          state5 = 2;
          lcd.clear();
          EEPROM.write(door5_id_add, 0);
          lcd.setCursor(0, 1);
          lcd.print("      THANK YOU    ");
          lcd.setCursor(0, 2);
          lcd.print("    CHARGE AGAIN   ");
          digitalWrite(door_locker5, LOW);
          delay(1000);
          digitalWrite(door_locker5, HIGH);
          lcd.clear();
          id = 5;
          deleteFingerprint(id);
          return finger.fingerID;
          reset();
        }
     break;
     case 6:
        if(penalty_6 != 0){
          lcd.clear();
          menu=11;
          insertCoin = 2;
          insert_state = 3;
          fingerprint_status=0;
          display_door6 = 4;
          door6_chargingStatus();        
        }
        else
        {
          d6_chargingState = 0;
          d6_timerSeconds = 0;
          digitalWrite(led6, LOW);
          digitalWrite(current_d6, HIGH);
          state6 = 2;
          lcd.clear();
          EEPROM.write(door6_id_add, 0);
          lcd.setCursor(0, 1);
          lcd.print("      THANK YOU    ");
          lcd.setCursor(0, 2);
          lcd.print("    CHARGE AGAIN   ");
          digitalWrite(door_locker6, LOW);
          delay(1000);
          digitalWrite(door_locker6, HIGH);
          lcd.clear();
          id = 6;
          deleteFingerprint(id);
          return finger.fingerID;
          reset();
        }
     break;
     case 7:
        if(penalty_7 != 0){
          lcd.clear();
          menu=11;
          insertCoin = 2;
          insert_state = 3;
          fingerprint_status=0;
          display_door7 = 4;
          door7_chargingStatus();        
        }
        else
        {
          d7_chargingState = 0;
          d7_timerSeconds = 0;
          digitalWrite(led7, LOW);
          digitalWrite(current_d7, HIGH);
          state7 = 2;
          lcd.clear();
          EEPROM.write(door7_id_add, 0);
          lcd.setCursor(0, 1);
          lcd.print("      THANK YOU    ");
          lcd.setCursor(0, 2);
          lcd.print("    CHARGE AGAIN   ");
          digitalWrite(door_locker7, LOW);
          delay(1000);
          digitalWrite(door_locker7, HIGH);
          lcd.clear();
          id = 7;
          deleteFingerprint(id);
          return finger.fingerID;
          reset();
        }
     break;
     case 8:
        if(penalty_8 != 0){
          lcd.clear();
          menu=11;
          insertCoin = 2;
          insert_state = 3;
          fingerprint_status=0;
          display_door8 = 4;
          door8_chargingStatus();        
        }
        else
        {
          d8_chargingState = 0;
          d8_timerSeconds = 0;
          digitalWrite(led8, LOW);
          digitalWrite(current_d8, HIGH);
          state8 = 2;
          lcd.clear();
          EEPROM.write(door8_id_add, 0);
          lcd.setCursor(0, 1);
          lcd.print("      THANK YOU    ");
          lcd.setCursor(0, 2);
          lcd.print("    CHARGE AGAIN   ");
          digitalWrite(door_locker8, LOW);
          delay(1000);
          digitalWrite(door_locker8, HIGH);
          lcd.clear();
          id = 8;
          deleteFingerprint(id);
          return finger.fingerID;
          reset();
        }
     break;
     case 9:
        if(penalty_9 != 0){
          lcd.clear();
          menu=11;
          insertCoin = 2;
          insert_state = 3;
          fingerprint_status=0;
          display_door9 = 4;
          door9_chargingStatus();        
        }
        else
        {
          d9_chargingState = 0;
          d9_timerSeconds = 0;
          digitalWrite(led9, LOW);
          digitalWrite(current_d9, HIGH);
          state9 = 2;
          lcd.clear();
          EEPROM.write(door9_id_add, 0);
          lcd.setCursor(0, 1);
          lcd.print("      THANK YOU    ");
          lcd.setCursor(0, 2);
          lcd.print("    CHARGE AGAIN   ");
          digitalWrite(door_locker9, LOW);
          delay(1000);
          digitalWrite(door_locker9, HIGH);
          lcd.clear();
          id = 9;
          deleteFingerprint(id);
          return finger.fingerID;
          reset();
        }
     break;

     case 10:
        if(penalty_10 != 0){
          lcd.clear();
          menu=11;
          insertCoin = 2;
          insert_state = 3;
          fingerprint_status=0;
          display_door10 = 4;
          door10_chargingStatus();        
        }
        else
        {
          d10_chargingState = 0;
          d10_timerSeconds = 0;
          digitalWrite(led10, LOW);
          digitalWrite(current_d10, HIGH);
          state10 = 2;
          lcd.clear();
          EEPROM.write(door10_id_add, 0);
          lcd.setCursor(0, 1);
          lcd.print("      THANK YOU    ");
          lcd.setCursor(0, 2);
          lcd.print("    CHARGE AGAIN   ");
          digitalWrite(door_locker10, LOW);
          delay(1000);
          digitalWrite(door_locker10, HIGH);
          lcd.clear();
          id = 10;
          deleteFingerprint(id);
          return finger.fingerID;
          reset();
        }
     break;
    }
  } else {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(" THE SELECTED DOOR  ");
    lcd.setCursor(0, 2);
    lcd.print("    IS INVALID..    ");
    delay(1000);
    lcd.clear();
    reset();
  }
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID;
}
uint8_t deleteFingerprint(uint8_t id) {
  uint8_t p = -1;

  p = finger.deleteModel(id);

  if (p == FINGERPRINT_OK) {
    Serial.println("Deleted!");
    reset();
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not delete in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.print("Unknown error: 0x"); Serial.println(p, HEX);
    return p;
  }
}

void adminMode() {
  lcd.setCursor(0,0);
  lcd.print("     ADMIN MODE     ");
  lcd.setCursor(0,1);
  lcd.print("   ENTER PASSCODE   ");  
  lcd.setCursor(0,3);
  lcd.print("*->PROCEED   B->BACK");
}
void adminView() {
  lcd.setCursor(0,0);
  lcd.print("     ADMIN PANEL    ");
  lcd.setCursor(0,1);
  lcd.print("D->OPEN LOCKER      "); 
  lcd.setCursor(0,2);
  lcd.print("A->CHANGE PASSCODE  ");  
  lcd.setCursor(0,3);
  lcd.print("C->INCOME    B->BACK");
}
void change_pass() {
  lcd.setCursor(0,0);
  lcd.print("     ADMIN PANEL    ");
  lcd.setCursor(0,1);
  lcd.print(" ENTER NEW PASSCODE ");   
  lcd.setCursor(0,3);
  lcd.print("A->SAVE      B->BACK");
}
void checkpass() {
  switch(input_passcode[0]){
              case '0':
                code1 = 0;
              break;
              case '1':
                code1 = 1;
              break;
              case '2':
                code1 = 2;
              break;
              case '3':
                code1 = 3;
              break;
              case '4':
                code1 = 4;
              break;
              case '5':
                code1 = 5;
              break;
              case '6':
                code1 = 6;
              break;
              case '7':
                code1 = 7;
              break;
              case '8':
                code1 = 8;
              break;
              case '9':
                code1 = 9;
              break;
            }
            switch(input_passcode[1]){
              case '0':
                code2 = 0;
              break;
              case '1':
                code2 = 1;
              break;
              case '2':
                code2 = 2;
              break;
              case '3':
                code2 = 3;
              break;
              case '4':
                code2 = 4;
              break;
              case '5':
                code2 = 5;
              break;
              case '6':
                code2 = 6;
              break;
              case '7':
                code2 = 7;
              break;
              case '8':
                code2 = 8;
              break;
              case '9':
                code2 = 9;
              break;
            }
            switch(input_passcode[2]){
             case '0':
                code3 = 0;
              break;
              case '1':
                code3 = 1;
              break;
              case '2':
                code3 = 2;
              break;
              case '3':
                code3 = 3;
              break;
              case '4':
                code3 = 4;
              break;
              case '5':
                code3 = 5;
              break;
              case '6':
                code3 = 6;
              break;
              case '7':
                code3 = 7;
              break;
              case '8':
                code3 = 8;
              break;
              case '9':
                code3 = 9;
              break;
            }
            switch(input_passcode[3]){
             case '0':
                code4 = 0;
              break;
              case '1':
                code4 = 1;
              break;
              case '2':
                code4 = 2;
              break;
              case '3':
                code4 = 3;
              break;
              case '4':
                code4 = 4;
              break;
              case '5':
                code4 = 5;
              break;
              case '6':
                code4 = 6;
              break;
              case '7':
                code4 = 7;
              break;
              case '8':
                code4 = 8;
              break;
              case '9':
                code4 = 9;
              break;
            }
}
void incomeCount() {
  c = EEPROM.read(n1);  
  d = EEPROM.read(n2);
  
  int totalEEPROM = c * 256 + d;
  money = money + totalEEPROM;

  a = money / 256;
  b = money % 256;

  EEPROM.write(n1,a);
  EEPROM.write(n2,b); 
}
void incomeFunc() {
  lcd.setCursor(0,0);
  lcd.print("     ADMIN PANEL    ");
  lcd.setCursor(0,1);
  lcd.print("  INCOME: ");  
  lcd.setCursor(0,3);
  lcd.print("C->COINS OUT B->BACK"); 
}
void adminSel() {
  lcd.setCursor(0,0);
  lcd.print("     ADMIN PANEL    ");
  lcd.setCursor(0, 1);
  lcd.print("   SELECT DOOR:");
  lcd.print(input);
  lcd.setCursor(0, 3);
  lcd.print("*->OPEN     B-> BACK");
}
