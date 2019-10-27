#include <RFID.h>
#include <Wire.h>  // Conection Library
#include <LiquidCrystal_I2C.h>  // i2C LCD Library
LiquidCrystal_I2C lcd(0x3F, 16, 2);
/*
PINOUT
* MOSI: Pin 11
* MISO: Pin 12
* SCK : Pin 13
* SS/SDA: Pin 10
* RST: Pin 9
* RQ: Tidak digunakan
*/
#include <SPI.h>

#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN,RST_PIN);

const int buzzer = 7;   //Passive buzzer ke Pin D7 dan GND
const int doorLock = 8; //Driver Selenoid Door Lock/Relay input ke pin D8
int serNum[5];          //Variable buffer Scan Card

int cards[][5] = {      //ID Kartu yang diperbolehkan masuk
  {240,49,119,24,174
}
  
};

bool access = false;

int alarm = 0;
uint8_t alarmStat = 0;
uint8_t maxError = 5;

void setup(){
    Serial.begin(9600);
    lcd.begin();
    SPI.begin();
    rfid.init();

    pinMode(doorLock, OUTPUT);
    digitalWrite(doorLock, HIGH);

  
  lcd.setCursor (0,0);
  lcd.print(F("  NFC DOOR LOCK   "));
  lcd.setCursor (0,1);
  lcd.print(F(" SMAN 1 TEGAL "));
  delay (2000);
  lcd.clear();
  noTone (buzzer);
}

void loop(){
  if (alarm >= maxError){
    alarmStat = 1;    }
  
  if (alarmStat == 0){ //belum di tempel kartu
  lcd.setCursor (0,0);
  lcd.setCursor (0,1);
  lcd.print(F(" tempel kartu "));

    if(rfid.isCard()){ //kartu ditempel
    
        if(rfid.readCardSerial()){ //baca serial & print
            Serial.print(rfid.serNum[0]);  //blok 0
            Serial.print(" ");
            Serial.print(rfid.serNum[1]);  //block 1
            Serial.print(" ");
            Serial.print(rfid.serNum[2]);  //block 2
            Serial.print(" ");
            Serial.print(rfid.serNum[3]);  //block 3
            Serial.print(" ");
            Serial.print(rfid.serNum[4]);  //block 4
            Serial.println("");
            
            for(int x = 0; x < sizeof(cards); x++){ //loop read serial
              for(int i = 0; i < sizeof(rfid.serNum); i++ ){ //loop compare serial
                  if(rfid.serNum[i] != cards[x][i]) {
                      access = false;
                      break;
                  } else {
                      access = true;
                  }
              }
              if(access) break;
            }   
        }
        
       if(access){
          Serial.println("buka");
          lcd.setCursor (0,0);
          lcd.print(F(" Silahkan Masuk "));
          lcd.setCursor (0,1);
          lcd.print("ID:");
          lcd.print(rfid.serNum[0]); lcd.print(rfid.serNum[1]);
          lcd.print(rfid.serNum[2]); lcd.print(rfid.serNum[3]);
          lcd.print(rfid.serNum[4]);
           digitalWrite(doorLock, LOW);
           tone (buzzer,900);
           delay(100);
           tone (buzzer,1200);
           delay(100);
           tone (buzzer,1800);
           delay(200);
           noTone(buzzer);  
           delay(600);
           lcd.setCursor (0,0);
           lcd.print(F(" Silahkan Masuk "));
           lcd.setCursor (0,1);
           lcd.print(F("AutoLock after "));
           for(int i=5; i>0; i--){
            lcd.setCursor (15,1); lcd.print(i);
            delay (1000);
           }
           digitalWrite(doorLock, HIGH);
           lcd.clear();
      } else {
           alarm = alarm+1;
           Serial.println("tutup"); 
           lcd.setCursor (0,0);
           lcd.print(F(" anda tidak diizinkan  "));
           lcd.setCursor (0,1);
           lcd.print("ID:");
           lcd.print(rfid.serNum[0]); lcd.print(rfid.serNum[1]);
           lcd.print(rfid.serNum[2]); lcd.print(rfid.serNum[3]);
           lcd.print(rfid.serNum[4]);
           tone (buzzer,900);
           delay(200);
           noTone(buzzer);
           delay(200);
           tone (buzzer,900);
           delay(200);
           noTone (buzzer);  
           delay(500);
           lcd.clear();      
       }        
    }
    rfid.halt();
}
else {
  lcd.setCursor (0,0);
  lcd.print(F(".....TERKUNCI..... "));
  lcd.setCursor (0,1);
  lcd.print(F(" TUNGGU!!! "));
for(int i=60; i>0; i--){
tone (buzzer,1800);
lcd.setCursor (13,1); lcd.print(i);
lcd.print(F("  "));delay (1000);}
noTone (buzzer);
alarmStat = 0;
alarm = 0;
  }
}
