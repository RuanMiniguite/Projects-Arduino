#define	keypad_pin  	A0
#define	par1			3	
#define	par2			5
#define	par3			6
#define	par4			9
#define	par5			10

int vet[5] = {0, 0, 0, 0, 0};
int vet_lum[5] = {0, 0, 0, 0, 0};
int brilho, aux;
int valor;
float luminosity;

void setup(){
  pinMode(par1, OUTPUT);
  pinMode(par2, OUTPUT);
  pinMode(par3, OUTPUT);
  pinMode(par4, OUTPUT);
  pinMode(par5, OUTPUT);
  Serial.begin(9600);
}

void loop(){  
  
  delay(100);					//evitar lag
  
  if(Serial.available()){
    aux = Serial.read();
    if(aux == 150){
      Select();
    }else{
      brilho = aux;
      potenc_led(brilho);
      Serial.print(brilho);
    }
  }
  
  valor = analogRead(keypad_pin);
   
  if(valor < 1023){
  	acender_led(valor);
  }
}

void potenc_led(int x){
  luminosity = (x * 255)/ 100;
}

void acender_led(int led){

  if(led <= 124){
  	//par1
    analogWrite(par1, luminosity);
    delay(200);
	led_on(0);
    
  }else if(led > 124 && led <= 254){
  	//par2
    analogWrite(par2, luminosity);
    delay(200);
    led_on(1);
    
  }else if(led > 254 && led <= 512){
  	//par3
    analogWrite(par3, luminosity);
    delay(200);
    led_on(2);
    
  }else if(led > 512 && led <= 682){
  	//par4
    analogWrite(par4, luminosity);
    delay(200);
    led_on(3);
    
  }else if(led > 682 && led <= 861){
    //par5
    analogWrite(par5, luminosity);
    delay(200);
    led_on(4);
    
  }
}

void led_on(int led){

  int qtd = 0;
  
  if(luminosity != 0){
    vet[led] = 1;
    vet_lum[led] = brilho;
  }else{
  	 vet[led] = 0;
     vet_lum[led] = 0;
  }
  
  for(int i = 0; i < 5; i++){
    if(vet[i] == 1){
      qtd++;
    }
  }
  
  Serial.write(qtd);
}


void Select(){
  for(int i = 0; i < 5; i++){
    Serial.write(vet_lum[i]);
    delay(1000);
  }
}