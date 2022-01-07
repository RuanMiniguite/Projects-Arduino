#include<Keypad.h>
#include<Servo.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd (A0, A1, A2, A3, A4, A5);

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
int led_on = 0;

void setup(){
  Serial.begin(9600);
  lcd.begin(16,2);
  visor();
}

void loop(){
  
  char key = keypad.getKey();
  
  if(Serial.available()){
    led_on = Serial.read();
  }
  
  
  if(key != NO_KEY){
	if(key == '*'){
      kwm();
    }else{
      value(key);
    }
  }
  delay(100);			//evitar lag
}

void value(char key){
  if(key == '#'){
   	intensity = buf.toInt();
    if(intensity >= 0 && intensity <= 100){
      visor();
      Serial.write(intensity);
      buf = "";
    }else{
      lcd.print(" ERRO!");
      delay(3000);
      limpar();
    }
  }else{
    lcd.print(key);
  	buf += key;
  }
}

void limpar(){
  buf = "";
  intensity = 0;
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

void kwm(){
  
  float total_kwh, total_rs;
  
  lcd.clear();
  lcd.setCursor(0,0);
  
  total_kwh = Query(); 
  total_rs =  total_kwh * 1;
  
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("Total kwh");
  
  lcd.setCursor(9,1);
  lcd.print(total_kwh, 5);
  delay(5000);
  
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("Total R$");
  lcd.setCursor(0,1);
  lcd.print(" 1h");
  
  lcd.setCursor(9,1);
  lcd.print(total_rs, 5); 
  
  delay(5000);
  
  total_rs =  total_kwh * 30;
  
  lcd.setCursor(0,1);
  lcd.print("30d");
  lcd.setCursor(9,1);
  lcd.print(total_rs, 5); 
  
  delay(5000);
  visor();
}


float Query(){

  int vet_brilho[5], i = 0;
  float total;
  
  Serial.write(150);
  lcd.print("Carregando");
  
  while(i < 5){
  	if(Serial.available()){
      vet_brilho[i] = Serial.read();
      Serial.print(vet_brilho[i] );
      lcd.print(".");
      i++;
    }
  }
  
  for(i = 0; i < 5; i++){
  	total += print_par_led(i, vet_brilho[i]);
    delay(5000);
  }
  
  return total;
  
}

float print_par_led(int par, int x){

  float volts, kwh;
  
  lcd.clear();
  
  volts = (x * 5) / 100;
  kwh = (volts * 0.020 * 2) / 1000;
  
  
  lcd.setCursor(0,0);
  lcd.print("Par de led ");
  lcd.print(par + 1);
  
  lcd.setCursor(0,1);
  lcd.print("kwh: ");
  lcd.setCursor(9,1);
  lcd.print(kwh, 5);
  
  return kwh;
}