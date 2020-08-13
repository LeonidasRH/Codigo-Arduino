#include<LiquidCrystal.h>
LiquidCrystal lcd(7,6,5,4,3,2);

int TRIG = 10;   
int ECO = 9;
int LED = 8;
int DURACION;
float DISTANCIA;
float voltage;


void setup() {
  lcd.begin(16,2);
  Serial.begin(9600);
  Serial.println("DISTANCIA,voltage");

  pinMode(TRIG, OUTPUT); 
  pinMode(ECO, INPUT);  
  pinMode(LED, OUTPUT);
  pinMode(12,INPUT);
}

void loop() {

digitalWrite(TRIG, HIGH);
delay(1);
digitalWrite(TRIG, LOW);

DURACION=pulseIn(ECO,HIGH);

  lcd.clear();
    
  lcd.setCursor(0,0);
  DISTANCIA=((0.034*DURACION)/2);
  
  Serial.print(DISTANCIA);
  Serial.print(",");
  lcd.print("Dist.:");
  lcd.print(DISTANCIA,1);
  lcd.print("cm");
  

  voltage=(DISTANCIA*(132));
  Serial.println(voltage);
  lcd.setCursor(0,1);
  lcd.print("Volt.:");
  lcd.print(voltage,0);
  lcd.setCursor(11,1);
  lcd.print("P:");
  lcd.print(voltage/DISTANCIA,0);

 if(digitalRead(11)==HIGH){
    delay(200);
  }else{
  delay(500);
  }

  if(DISTANCIA<=40&&DISTANCIA>=0){
    digitalWrite(LED, HIGH);
  }else if(DISTANCIA>40){
    digitalWrite(LED, LOW);
  }
}
