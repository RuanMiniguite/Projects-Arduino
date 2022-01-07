
const byte tab_bin[10][7] = {
  
   {1,1,1,1,1,1,0},	//0
   {0,1,1,0,0,0,0}, //1
   {1,1,0,1,1,0,1},	//2
   {1,1,1,1,0,0,1}, //3 
   {0,1,1,0,0,1,1},	//4
   {1,0,1,1,0,1,1},	//5
   {1,0,1,1,1,1,1}, //6
   {1,1,1,0,0,0,0},	//7
   {1,1,1,1,1,1,1}, //8
   {1,1,1,1,0,1,1}  //9  
  //A B C D E F G
};


//Tempo de ligado de cada lampada
void func_temp(byte led, byte t){

  digitalWrite(led, HIGH);
  while(t > 0){
  	print_display(t);
    t--;
    delay(1000);
  }
  digitalWrite(led, LOW);
}

//Imprime no display
void print_display(byte num){
  byte pino = 7;
 
  for(byte x = 0; x < 7; x++){
    digitalWrite(pino,tab_bin[num][x]);
    pino++;
  }
}


void setup(){
  pinMode(2, OUTPUT);  	//LED verde
  pinMode(3, OUTPUT);	  //LED amarelo
  pinMode(4, OUTPUT);	  //LED vermelho
  
  pinMode(7, OUTPUT);	  //Display A
  pinMode(8, OUTPUT);	  //Display B
  pinMode(9, OUTPUT);	  //Display C
  pinMode(10, OUTPUT);  //Display D
  pinMode(11, OUTPUT);	//Display E
  pinMode(12, OUTPUT);	//Display F
  pinMode(13, OUTPUT);	//Display G
}

void loop(){  
  
  //Passar o LED(pino) e tempo(s)
  
  func_temp(2, 9);	//Verde, 9s
  func_temp(3, 3);	//Amarela, 3s
  func_temp(4, 6);	//Vermelha, 6s
  
}