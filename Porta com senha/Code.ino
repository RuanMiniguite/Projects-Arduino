#include<Keypad.h>
#include<Servo.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd (A0, A1, A2, A3, A4, A5);

String senha = "12345";
String buf = "";

Servo s;
int pinoServo = 13;
int i = 0;
int ledVerde = 2;
int ledVermelho = 1;
int buzzer = 12;
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
	{'1', '2', '3', 'A'},
	{'4', '5', '6', 'B'},
	{'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {11, 10, 9, 8}; 
byte colPins[COLS] = {7, 6, 5, 4};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup(){

	Serial.begin(9600);
	s.attach(pinoServo);
  	s.write(0);
 	pinMode(ledVerde, OUTPUT);
  	pinMode(ledVermelho, OUTPUT);
  	pinMode(buzzer, OUTPUT);
  	lcd.begin(16,2);
  	
  	lcd.setCursor(0,0);
  	lcd.print("INICIANDO...");
  	delay(2000);
  	lcd.setCursor(0,0);
  	lcd.print("Pressione *"); 
  
}

void loop(){
	
  char key = keypad.getKey();
  
  if(key != NO_KEY){
    if(key == '*'){
    	i = 0;
   	 	lcd.clear();
    	buf = "";
    	password();
    }
  }
}

void password(){
	while(i < 8){
    	lcd.setCursor(0,0);
      	lcd.print("SENHA: ");
      
      	char key = keypad.getKey();
      	
        if(key != NO_KEY){
			buf += key;
         	lcd.print(buf);
          	i++;
        }
    }
	
    if(buf == senha){
		lcd.setCursor(0,1);
      	lcd.print("SENHA OK");
      	digitalWrite(ledVermelho, LOW);
     	digitalWrite(ledVerde, HIGH);
		s.write(90);
      	delay(5000);
      	digitalWrite(ledVerde, LOW);
        digitalWrite(ledVermelho, HIGH);  
      	s.write(0);
      	lcd.clear();
		lcd.setCursor(0,0);
      	lcd.print("Pressione *"); 
   
    }else{
    	lcd.setCursor(0,0);
     	lcd.print("Pressione *"); 
      	lcd.setCursor(0,1);
      	lcd.print("SENHA INCORRETA ");
      	alarm();
      	analogWrite(buzzer, 0);
      	digitalWrite(ledVermelho, HIGH);
      	delay(500);
      	digitalWrite(ledVermelho, LOW); 
    }
}


void alarm(){	
  for(int j = 0; j < 3; j++){
  	tone(buzzer, 5); 
	delay(500);
	noTone(buzzer);
    delay(500);  
  }
}