#include <Wire.h>      // libreria de comunicacion por I2C
#include <LCD.h>      // libreria para funciones de LCD
#include <LiquidCrystal_I2C.h>    // libreria para LCD por I2C
#include <virtuabotixRTC.h>

/////////////////////////////Definir conexiones y direccion de pantalla LCD////////////////////////////////

LiquidCrystal_I2C lcd (0x27, 2, 1, 0, 4, 5, 6, 7); // DIR, E, RW, RS, D4, D5, D6, D7

///////////////////////////////////////Definir Variables Tipo Byte///////////////////////////////////////////////////
int RELE = 6;
//***** variarables para H Inicio
uint8_t r = 0;
uint8_t rd = 0;
//***** variarables para H Final
uint8_t al = 0; ///****
uint8_t gm = 0; ///****
//***** variarables para Min Inicio
uint8_t Min = 0; ///****
uint8_t Mind = 0; ///****
//***** variarables para Min Final
uint8_t MinL = 0; ///****
uint8_t MinD = 0; ///****

////////////////////////////Definicio de las variables para la funcion Switch()////////////////////////////

#define S_HOME 0
#define S_SET_L 1
#define S_SET_M 2
#define S_SET_HR 3
#define S_SET_HRLUN 4
#define S_SET_HRMAR 5

uint8_t estado = S_HOME;//Inicio//Del Menu//

////////////////////////////////////////Estado de los Botones//////////////////////////////////////////////

#define BTN_MENU 0
#define BTN_EXIT 1
#define BTN_ARRIBA 2
#define BTN_HR 3 

/////////////////////////////////////////Pines de los botones//////////////////////////////////////////////

uint8_t button[4] = {
  8,
  9,
  10,
  3, 
};

uint8_t button_state[4];//Arreglo String de los botones//

///////////////////////////Inicializacion de variables y los estados de los botones////////////////////////


virtuabotixRTC myRTC(5, 4, 2);


void setup() {
  pinMode(RELE, OUTPUT);
  Serial.begin(9600);
  lcd.clear();
  lcd.begin(16,2);
  lcd.setBacklightPin(3,POSITIVE);  // puerto P3 de PCF8574 como positivo
  lcd.setBacklight(HIGH);   // habilita iluminacion posterior de LCD
         
  printHOME();//Mensaje de Inicio//
  // segundos, minutos, horas, dia de la semana, dia del mes, mes, año//dia de la semana Domingo=0, Lunes=1, Martes=2; Miercoles=3; Jueves=4; Vienres=5; Sabado=6
  myRTC.setDS1302Time(23, 51, 23, 1, 03, 8, 2020);
  pinMode(button[BTN_MENU], INPUT_PULLUP); //INPUT_PULLUP es la conexion para los pulsadores
  pinMode(button[BTN_EXIT], INPUT_PULLUP);
  pinMode(button[BTN_ARRIBA], INPUT_PULLUP);
  pinMode(button[BTN_HR], INPUT_PULLUP);

  button_state [0] = HIGH;
  button_state [1] = HIGH;
  button_state [2] = HIGH;
  button_state [3] = HIGH;
}


////////if(flancoSubida(button[BTN_MENU]))<--otra forma de verlo/////////////////
///////Si se detecta un flanco de subida en el boton MENU algo se va a ejecutar////////////////////////////

  uint8_t flancoSubida (int btn){
  uint8_t valor_nuevo = digitalRead(button[btn]);
  uint8_t result =  button_state[btn]!=valor_nuevo && valor_nuevo == 1;
  button_state[btn] = valor_nuevo;
  return result;
}

//////////////////////////Lo que se imprimira por dia//Lo que se Imprime En Home///////////////////////////

void printHOME(){
 lcd.clear();
 int a = map (myRTC.dayofweek,0,6,0,6); 
 lcd.setCursor(1,0);
 lcd.print("[MENU]"); 
 lcd.setCursor(8,0);
 myRTC.updateTime();
 lcd.print(myRTC.dayofmonth);
 lcd.print("/");
 lcd.print(myRTC.month);
 lcd.print("/");
 lcd.print(myRTC.year);
 lcd.setCursor(0,1);
 lcd.print("Dia:");
 lcd.setCursor(8,1);
 lcd.print(myRTC.hours);
 lcd.print(":");
 lcd.print(myRTC.minutes);
 lcd.print(":");
 lcd.print(myRTC.seconds);
 
 if(a == 1 ){
  lcd.setCursor(4,1);
  lcd.print("Lun.");
 }
 if(a == 2 ){
  lcd.setCursor(4,1);
  lcd.print("Mar.");
 }
 if(a == 3 ){
  lcd.setCursor(4,1);
  lcd.print("Mie.");
 }
 if(a == 4 ){
  lcd.setCursor(4,1);
  lcd.print("Jue.");
 }
 if(a == 5 ){
  lcd.setCursor(4,1);
  lcd.print("Vie.");
 }
 if(a == 6 ){
  lcd.setCursor(4,1);
  lcd.print("Sab.");
 }
 if(a == 0 ){
  lcd.setCursor(4,1);
  lcd.print("Dom.");
 }
  delay(1000);
}

/////////////////////////////////////////////////LUNES////////////////////////////////////////////////////
void printLUNES(){
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Set Lun.");
 lcd.setCursor(9,0);
 lcd.print("Inicio");
 lcd.setCursor(9,1);
 lcd.print(">");
 lcd.setCursor(10,1);
 lcd.print(r,DEC);
 lcd.setCursor(12,1);
 lcd.print(":");
 lcd.setCursor(13,1);
 lcd.print(Min, DEC);
}

void printLunF(){
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Set Lun.");
 lcd.setCursor(9,0);
 lcd.print("Final");
 lcd.setCursor(9,1);
 lcd.print(">");
 lcd.setCursor(10,1);
 lcd.print(al,DEC);
 lcd.setCursor(12,1);
 lcd.print(":");
 lcd.setCursor(13,1);
 lcd.print(MinL, DEC);
}
/////////////////////////////////////////////////DOMINGO///////////////////////////////////////////////////
void printMARTES(){
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Set Mar.");
 lcd.setCursor(9,0);
 lcd.print("Inicio");
 lcd.setCursor(9,1);
 lcd.print(">");
 lcd.setCursor(10,1);
 lcd.print(rd,DEC);
 lcd.setCursor(12,1);
 lcd.print(":");
 lcd.setCursor(13,1);
 lcd.print(Mind, DEC); 
}

void printMarF(){
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Set Mar.");
 lcd.setCursor(9,0);
 lcd.print("Final");
 lcd.setCursor(9,1);
 lcd.print(">");
 lcd.setCursor(10,1);
 lcd.print(gm,DEC);
 lcd.setCursor(12,1);
 lcd.print(":");
 lcd.setCursor(13,1);
 lcd.print(MinD, DEC);
}

//////////////////////////////////////Configuracion de las Horas///////////////////////////////////////////


//////Horas INICIO Y FIN Lunes
//*****Hora Inicio
void printHoraLun() {
  lcd.setCursor(0,1);
  lcd.print("H:");
  lcd.print(r, DEC);
}

void printMin() {
  lcd.setCursor(5,1);
  lcd.print("M:");
  lcd.print(Min, DEC);
}
//*****Hora Final
void printHoraLunF() {
  lcd.setCursor(0,1);
  lcd.print("H:");
  lcd.print(al, DEC);
}

void printMinLunF() {
  lcd.setCursor(5,1);
  lcd.print("M:");
  lcd.print(MinL, DEC);
}
//////Horas INICIO Y FIN Domingo
//*****Hora Inicio
void printHoraMar() {
  lcd.setCursor(0,1);
  lcd.print("H:");
  lcd.print(rd, DEC);
}

void printMinMar() {
  lcd.setCursor(5,1);
  lcd.print("M:");
  lcd.print(Mind, DEC);
}
//*****Hora Final
void printHoraMarF() {
  lcd.setCursor(0,1);
  lcd.print("H:");
  lcd.print(gm, DEC);
}

void printMinMarF() {
  lcd.setCursor(5,1);
  lcd.print("M:");
  lcd.print(MinD, DEC);
}
//////////////////////////////////Aqui inicia el programa de horario programable/////////////////////////////////////

void loop() {
  switch(estado){
    case S_HOME: //inicio home
      if (flancoSubida(BTN_MENU)){
       estado = S_SET_L;
       printLUNES();//podrias imrprimir lunes 00:00:00
       break;   
      }
       printHOME();
 
      break; 
     
//////////////////////////////////////////////////////[LUNES]////////////////////////////////////////////////////////  
    case S_SET_L: /*** INICIO ESTADO S_SET_R ***/
      if(flancoSubida(BTN_MENU)) { // Transición BTN_MENU
        estado = S_SET_HRLUN;
        printLunF();
        break;
      }   
//////////////////////////////////////////////Hora Inicio Dia Lun/////////////////////////////////////////////////////  
      if(flancoSubida(BTN_ARRIBA)){ //TRANSICION AL BOTON Horas
      if(r<24){
        r++;
      }
      else{
        lcd.setCursor(3,1);
        lcd.print(" ");
        r = 0;
      }
       printHoraLun();
       break;
      }
/////////////////////////////////////////////////Min de Hora Inicio///////////////////////////////////////////////////   
      if (flancoSubida(BTN_HR)){
      if(Min<60){
        Min++;
      }
      else{
        lcd.setCursor(8,1);
        lcd.print(" ");
        Min = 0;
      }
       printMin();
       break;
       break;
      }  
////////////////////////////////////////////Bucle Final Hora Final Dia Lun////////////////////////////////////////////
      if(flancoSubida(BTN_EXIT)){ //TRANSICION AL BOTON MENU
        estado = S_HOME;
        //printHOME();
        break;
      }
     break;//fin lunes*/      
///////////////////////////////////Hora Inicio DE Hora Final Dia Lun/////////////////////////////////////////////////
case S_SET_HRLUN: 
      if(flancoSubida(BTN_MENU)) { // Transición BTN_MENU
        estado = S_SET_M;
        printMARTES();
        break;
      } 
      if(flancoSubida(BTN_ARRIBA)){ //TRANSICION AL BOTON Horas
      if(al<24){
        al++;
      }
      else{
        lcd.setCursor(3,1);
        lcd.print(" ");
        al = 0;
      }
       printHoraLunF();//aqui pones que se imprima hora 00:00
       break;
      }
/////////////////////////////////////////Min de Hora FINAL Dia Lun///////////////////////////////////////////////////   
      if (flancoSubida(BTN_HR)){
      if(MinL<60){
        MinL++;
      }
      else{
        lcd.setCursor(8,1);
        lcd.print(" ");
        MinL = 0;
      }
       printMinLunF();//aqui pones que se impriman los minutos 00:00
       break;
       break;
      }    
////////////////////////////////////////////Bucle Final Hora Final Dia Lun////////////////////////////////////////////
      if(flancoSubida(BTN_EXIT)){ //TRANSICION AL BOTON MENU
        estado = S_HOME;
      //  printHOME();
        break;
      }
     break;//fin lunes*/
    


 //////////////////////////////////////////////////[MARTES]/////////////////////////////////////////////////////////
    
    case S_SET_M: //inicio Martes
     if(flancoSubida(BTN_MENU)) { // Transición BTN_MENU
        estado = S_SET_HRMAR;
        printMarF();
        break;
      }
/////////////////////////////////////Hora Inicio Dia Mar//////////////////////////////////////////////////////////////  
      if(flancoSubida(BTN_ARRIBA)){ //TRANSICION AL BOTON Horas
      if(rd<24){
        rd++;
      }
      else{
        lcd.setCursor(3,1);
        lcd.print(" ");
        rd = 0;
      }
       printHoraMar();
       break;
      }
//////////////////////////////////////////////////Min de Hora Inicio/////////////////////////////////////////////////   
      if (flancoSubida(BTN_HR)){
      if(Mind<60){
        Mind++;
      }
      else{
        lcd.setCursor(8,1);
        lcd.print(" ");
        Mind = 0;
      }
       printMinMar();
       break;
       break;
      }  
///////////////////////////////////////Bucle Final dia Martes///////////////////////////////////////////////////////          
      if(flancoSubida(BTN_EXIT)){ //TRANSICION AL BOTON MENU
        estado = S_HOME;
      //  printHOME();
        break;
      }
     break;
//////////////////////////////////////Hora Inicio DE Hora Final Dia Mar//////////////////////////////////////////////
case S_SET_HRMAR: 
      if(flancoSubida(BTN_MENU)) { // Transición BTN_MENU
        estado = S_SET_L;
        printLUNES();
        break;
      } 
      if(flancoSubida(BTN_ARRIBA)){ //TRANSICION AL BOTON Horas
      if(gm<24){
        gm++;
      }
      else{
        lcd.setCursor(3,1);
        lcd.print(" ");
        gm = 0;
      }
       printHoraMarF();
       break;
      }
///////////////////////////////////////////Min de Hora FINAL Dia Mar/////////////////////////////////////////////////   
      if (flancoSubida(BTN_HR)){
      if(MinD<60){
        MinD++;
      }
      else{
        lcd.setCursor(8,1);
        lcd.print(" ");
        MinD = 0;
      }
       printMinMarF();
       break;
       break;
      }     
     
////////////////////////////////////////////Bucle Final Hora Final Dia Mar////////////////////////////////////////////
      if(flancoSubida(BTN_EXIT)){ //TRANSICION AL BOTON MENU
        estado = S_HOME;
      //  printHOME();
        break;
      }
     break;//fin Martes*/
  }
int a = map (myRTC.dayofweek,0,6,0,6); 
int b = map (myRTC.dayofweek,0,6,0,6); 

////////////////////////////////////////////////////////////Rele Lunes///////////////////////////////////////
 if(a==1 && r==myRTC.hours && Min==myRTC.minutes){
  digitalWrite(RELE,HIGH);
 }
 if(a==1 && al==myRTC.hours && MinL==myRTC.minutes){
  digitalWrite(RELE,LOW);
 }
////////////////////////////////////////////////////////////Rele Martes///////////////////////////////////////
 if(b==2 && rd==myRTC.hours && Mind==myRTC.minutes){
  digitalWrite(RELE,HIGH);
 }
 if(b==2 && gm==myRTC.hours && MinD==myRTC.minutes){
  digitalWrite(RELE,LOW);
 }

}
