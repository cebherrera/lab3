#include <PCD8544.h>

// Instancia de Pantalla
static PCD8544 lcd;

// Leds para indicar cuandos se esta midiendo un voltaje mayor a 20 v
int led0 = 0;
int led1 = 1;
int led2 = 2;
int led3 = 8; 

// Switches
int serialcontroler = 13;
int switchAC_DC = 12;

// Entradas Analogicas
float voltage0;
int entrada0 = 0;

float voltage1;
int entrada1 = 1;

float voltage2;
int entrada2 = 2;

float voltage3;
int entrada3 = 3;


// Entrada de Signo Analogicas
float valorsigno0;
int signo0 = 5;

float valorsigno1;
int signo1 = 5;

// Entrada de Signo Digitales
int signo2 = 9;
int valsigno2;
int signo3 = 10;
int valsigno3;

void setup() {
  // Configuracion de Pantalla
  lcd.begin() ; // default resolution is 84x48

  // Se establecen los pines con LEDs como salida
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  // Switches del circuito
  pinMode(serialcontroler, INPUT);
  pinMode(switchAC_DC, INPUT);

  // Se inicia la comunicacion serial para debbuging
  Serial.begin(9600);
}

void loop() {
  // Si modoAC_DC es un 1 es modo AC, si es un 0 es modo DC
  int modoAC_DC = digitalRead(switchAC_DC);

  // Procesamiento de Entradas Analogicas
  float valortemp0 = analogRead(entrada0); // Leemos el valor analogico el cual por el ADC es un valor entero de 0 a 1023
  voltage0 = valortemp0 * (24.0 / 1023.0); // Se convierte el valor leido a un rango de 0v-5v
  if (voltage0>=20){ // Se revisa si el voltaje medido es +-20v o mas para enceder el LED de precuacion
    digitalWrite(led0, HIGH); 
  } else {
    digitalWrite(led0, LOW);  
  }

  float valortemp1 = analogRead(entrada1); // Leemos el valor analogico el cual por el ADC es un valor entero de 0 a 1023
  voltage1 = valortemp1 * (24.0 / 1023.0); // Se convierte el valor leido a un rango de 0v-5v
  if (voltage1>=20){ // Se revisa si el voltaje medido es +-20v o mas para enceder el LED de precuacion
    digitalWrite(led1, HIGH); 
  } else {
    digitalWrite(led1, LOW);  
  }

  float valortemp2 = analogRead(entrada2); // Leemos el valor analogico el cual por el ADC es un valor entero de 0 a 1023
  voltage2 = valortemp2 * (24.0 / 1023.0); // Se convierte el valor leido a un rango de 0v-5v
  if (voltage2>=20){ // Se revisa si el voltaje medido es +-20v o mas para enceder el LED de precuacion
    digitalWrite(led2, HIGH); 
  } else {
    digitalWrite(led2, LOW);  
  }

  float valortemp3 = analogRead(entrada3); // Leemos el valor analogico el cual por el ADC es un valor entero de 0 a 1023
  voltage3 = valortemp3 * (24.0 / 1023.0); // Se convierte el valor leido a un rango de 0v-5v
  if (voltage3>=20){ // Se revisa si el voltaje medido es +-20v o mas para enceder el LED de precuacion
    digitalWrite(led3, HIGH); 
  } else {
    digitalWrite(led3, LOW);  
  }

  // Se verifica si el valor medidio es AC o DC para procesamiento adicional
  if (modoAC_DC==1){ // Si modoAC_DC es un 1 es modo AC, si es un 0 es modo DC
    voltage0=voltage0*0.7071;
    voltage1=voltage1*0.7071;
    voltage2=voltage2*0.7071;
    voltage3=voltage3*0.7071;
  } else {
    // Se lee el signo que se encuentra en la entrada analogica
    float signotemp0 = analogRead(signo0); // Leemos el valor analogico el cual por el ADC es un valor entero de 0 a 1023
    valorsigno0 = signotemp0 * (5.0 / 1023.0); // Se convierte el valor leido a un rango de 0v-5v
    float signotemp1 = analogRead(signo1); // Leemos el valor analogico el cual por el ADC es un valor entero de 0 a 1023
    valorsigno1 = signotemp1 * (5.0 / 1023.0); // Se convierte el valor leido a un rango de 0v-5v

    // Se lee el signo que se encuentra en la entrada digital
    valsigno2 = digitalRead(signo2);
    valsigno3 = digitalRead(signo3);

    // Habiendo leido el signo se decide como modificar cada voltaje medido
    if(valorsigno0 == 0){voltage0 = -voltage0;}
    if(valorsigno1 == 0){voltage1 = -voltage1;}
    if(valsigno2 == 0){voltage2 = -voltage2;}
    if(valsigno3 == 0){voltage3 = -voltage3;}
  }

  // Se limpia pantalla
  lcd.clear();

  // Se escribe en la pantalla los valores medidos
  lcd.setCursor(0, 0);
  lcd.print("Voltaje0:" + String(voltage0));

  lcd.setCursor(0, 1);
  lcd.print("Voltaje1:" + String(voltage1));

  lcd.setCursor(0, 2);
  lcd.print("Voltaje2:" + String(voltage2));

  lcd.setCursor(0, 3);
  lcd.print("Voltaje3:" + String(voltage3));

  delay(200);

  int valserial = digitalRead(serialcontroler);
  if (valserial==1){
    // Se autoriza comunicacion serial
    Serial.println(String(voltage0) +","+ String(voltage1) + "," + String(voltage2) +","+ String(voltage3));
  } 
  /*
  // Se imprime el estado de los switches para debbuging
  Serial.print("valserail: ");
  Serial.println(valserial);
  Serial.print("modoAC_DC: ");
  Serial.println(modoAC_DC);
  
  // Se imprime el voltage para debbuging
  Serial.print("Voltage0: ");
  Serial.println(voltage0);
  Serial.print("Voltage1: ");
  Serial.println(voltage1);
  Serial.print("Voltage2: ");
  Serial.println(voltage2);
  Serial.print("Voltage3: ");
  Serial.println(voltage3);

  // Se imprime el signo leido para debbuging 
  Serial.print("valorsigno0: ");
  Serial.println(valorsigno0);
  Serial.print("valorsigno1: ");
  Serial.println(valorsigno1);
  Serial.print("valsigno2: ");
  Serial.println(valsigno2);
  Serial.print("valsigno3: ");
  Serial.println(valsigno3);
  */
  
}
