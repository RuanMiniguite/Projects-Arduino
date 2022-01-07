#include<Keypad.h>
#include<Servo.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd (A0, A1, A2, A3, A4, A5);

const byte ROWS = 4;
const byte COLS = 4;

//Teclado
char keys[ROWS][COLS] = {
  {'1', '2', '3', '+'},
  {'4', '5', '6', '-'},
  {'7', '8', '9', '*'},
  {'l', '0', '=', '/'}
};
byte rowPins[ROWS] = {11, 10, 9, 8}; 
byte colPins[COLS] = {7, 6, 5, 4};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


char number[10] = {'1','2','3','4','5','6','7','8','9','0'};

String valor[10][1];	//Log de entrada
int pos_valor = 0;		//qtd_caracter digitado
String buf;

int i;			//contador
int j;			//Verificar se é numero
int k = 0;		//Verificar se é primeiro


void setup(){
  Serial.begin(9600);
  lcd.begin(16,2);

  lcd.setCursor(0,0);
  lcd.print("INICIANDO...");
  delay(2000); 
  lcd.clear();
  lcd.setCursor(0,0);
}

void loop(){
	
  char key = keypad.getKey();
  	
  if(key != NO_KEY){

    i = 0;
    j = 0;

    while(i < 11){
      if(key == number[i]){
        j = 1;
        k = 1;
      }
      i++;
    }

    if(k == 0 && j == 0){
      lcd.print("ERRO!");
      delay(5000);
      lcd.clear();	
    
    }else if(k == 1 && j == 1){
      lcd.print(key);
      buf += key;
   
    }else if(k == 1 && j == 0){
      valor[pos_valor][0] = buf;
      valor[pos_valor][1] = "1";		//add numero
      pos_valor++;
      buf = "";
     
      if(key != '='){
        lcd.print(key);
        valor[pos_valor][0] = key;
        valor[pos_valor][1] = "0";		//add operação
        pos_valor++;
     
      }else{
        calc();				//chama a operação
      }
    }

    if(key == 'l'){
      lcd.clear();
      k = 0;
      buf = "";
      lcd.setCursor(0,0);
      pos_valor = 0;

      for(i = 0; i < pos_valor; i++){
        valor[i][0]= "";
        valor[i][1]= "";
      }
    }	   
  }
}


void calc(){
	
  double aux, aux2;
  String opr;

  lcd.setCursor(0,1);
  lcd.print("Resp: ");

  if(pos_valor < 2){
    for(i = 0; i < pos_valor; i++){
      lcd.print(valor[i][0]);
    }
  
  }else{
    i = 0;

    while(i < pos_valor){	
      if(i < 1){
        aux = valor[i][0].toInt();
        i++;
        opr = valor[i][0];
        i++;
        aux2 = valor[i][0].toInt();
      }else{
        opr = valor[i][0];
        i++;
        aux2 = valor[i][0].toInt();
      }

      if(opr == "+"){
        aux += aux2;
      }else if(opr == "-"){
        aux -= aux2;
      }else if(opr == "*"){
        aux *= aux2;
      }else if(opr == "/"){
        aux /= aux2;
      }

      i++;
    }
    lcd.print(aux);
  }
}
