#include<Keypad.h>
#include<Servo.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd (A0, A1, A2, A3, A4, A5);

int ledAmarelo = 3;

const byte ROWS = 4;
const byte COLS = 3;

char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {11, 10, 9, 8}; 
byte colPins[COLS] = {7, 6, 5};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String buf;
int intensity = 0;

void setup(){

  Serial.begin(9600);
  pinMode(ledAmarelo, OUTPUT);

  lcd.begin(16,2);
  visor();
}

void loop(){
	
  char key = keypad.getKey();
  
  if(key != NO_KEY){
	if(key == '*'){
      limpar();
    }else{
      value(key);
    }
  }
}

void value(char key){
  if(key == '#'){
   	intensity = buf.toInt();
    potenc_led(intensity); 
  }else{
    lcd.print(key);
  	buf += key;
  }
}

void potenc_led(int x){
 
  float luminosity;
  
  if(x >= 0 && x <= 100){
 
    luminosity = (x * 255)/ 100;

    visor();
    analogWrite(ledAmarelo, luminosity);
  	buf = "";
    
  }else{
  	lcd.print(" ERRO!");
    delay(3000);
    limpar();
    
  }
}

void limpar(){
  buf = "";
  intensity = 0;
  analogWrite(ledAmarelo, intensity);
  visor();
}

void visor(){
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("BRILHO: ");
  lcd.print(intensity);
  lcd.print("/100");
  lcd.setCursor(0,0);
  lcd.print("VALOR: ");

}