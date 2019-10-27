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
	
   
   PIN     |   RFID-RC522  | Arduino Uno R3	 
  ---------|---------------|----------------
  RST/Reset|   RST         | 9             
  SPI SS   |   SDA(SS)     | 10            
  SPI MOSI |   MOSI        | 11 / ICSP-4   			 
  SPI MISO |   MISO        | 12 / ICSP-1   
  SPI SCK  |   SCK         | 13 / ICSP-3   
