# NFCDoorLock

# PARTS : 
	ARDUINO UNO R3
	RFID-RC522	
	SOLENOID DOOR LOCK
	PASSIVE BUZZER
	LCD L2C
	
# LIBRARY  :
	RFID.h
	LiquidCrystal_I2C.h
	Wire.h
	
 
           |   MFRC522     | Arduino       
           |   Reader/PCD  | Uno/101        
  Signal   |   Pin         | Pin           	 
  ---------|---------------|------------
  RST/Reset|   RST         | 9             
  SPI SS   |   SDA(SS)     | 10            
  SPI MOSI |   MOSI        | 11 / ICSP-4   			 
  SPI MISO |   MISO        | 12 / ICSP-1   
  SPI SCK  |   SCK         | 13 / ICSP-3   
