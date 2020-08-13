int RELE2=6;
int RELE1=5;
int BTN2=3;
int BTN1=11;
int VALBTN1=0;
int ANTBTN1=0;
int ESTADORELE=0;
int VALBTN2=0;
int ANTBTN2=0;
int ESTADORELE2=0;


void setup() {
  pinMode(RELE2,OUTPUT);
  pinMode(RELE1,OUTPUT);
  pinMode(BTN1, INPUT);
  pinMode(BTN2, INPUT);
  
}

void loop() {

/////////////////////////////////////////////////////RELE1///////////////////////////////////
  
  VALBTN1=digitalRead(BTN1);
  
  if((VALBTN1==HIGH) && (ANTBTN1==LOW)){ ///////Despues del primer if el valor de ESTADORELE ES 1
    ESTADORELE=1-ESTADORELE;             ///////y cuando vuelve a correr el bucle es 1-1
  }
    ANTBTN1 = VALBTN1;
    
  if(ESTADORELE==1){
    digitalWrite(RELE1,HIGH);
  }else{
    digitalWrite(RELE1,LOW);
  }
  
//////////////////////////////////////////////////////////RELE2/////////////////////////////////////////

  VALBTN2=digitalRead(BTN2);
  
  if((VALBTN2==HIGH) && (ANTBTN2==LOW)){ ///////Despues del primer if el valor de ESTADORELE ES 1
    ESTADORELE2=1-ESTADORELE2;             ///////y cuando vuelve a correr el bucle es 1-1
  }
    ANTBTN2 = VALBTN2;
    
  if(ESTADORELE2==1){
    digitalWrite(RELE2,HIGH);
  }else{
    digitalWrite(RELE2,LOW);
  }
}
