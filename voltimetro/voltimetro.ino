#include <PCD8544.h>

// Leds para indicar cuandos se esta midiendo un voltaje mayor a 20 v
int led0 = 0;
int led1 = 1;
int led2 = 2;
int led3 = 9;

// Switches
int serialcontroler = 1;
int switchAC_DC = 1;

// Entradas Analogicas
float voltage0;
int entrada0 = 0;

float voltage1;
int entrada1 = 1;

float voltage2;
int entrada2 = 2;

float voltage3;
int entrada3 = 3;

// Entrada Digital
int signo = 1; 

void setup() {
  // Se establecen los pines con LEDs como salida
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  // Se inicia la comunicacion serial para debbuging
  Serial.begin(9600);
}

void loop() {
  float valortemp0 = analogRead(entrada0); // Leemos el valor analogico el cual por el ADC es un valor entero de 0 a 1023
  voltage0 = valortemp0 * (5.0 / 1023.0); // Se convierte el valor leido a un rango de 0v-5v
  if (voltage0>=4){ // Se revisa si el voltaje medido es 20v o mas para enceder el LED de precuacion
    digitalWrite(led0, HIGH); 
  } else {
    digitalWrite(led0, LOW);  
  }
  float valortemp1 = analogRead(entrada1); // Leemos el valor analogico el cual por el ADC es un valor entero de 0 a 1023
  voltage1 = valortemp1 * (5.0 / 1023.0); // Se convierte el valor leido a un rango de 0v-5v
  if (voltage1>=4){ // Se revisa si el voltaje medido es 20v o mas para enceder el LED de precuacion
    digitalWrite(led1, HIGH); 
  } else {
    digitalWrite(led1, LOW);  
  }
  float valortemp2 = analogRead(entrada2); // Leemos el valor analogico el cual por el ADC es un valor entero de 0 a 1023
  voltage2 = valortemp2 * (5.0 / 1023.0); // Se convierte el valor leido a un rango de 0v-5v
  if (voltage2>=4){ // Se revisa si el voltaje medido es 20v o mas para enceder el LED de precuacion
    digitalWrite(led2, HIGH); 
  } else {
    digitalWrite(led2, LOW);  
  }
  float valortemp3 = analogRead(entrada3); // Leemos el valor analogico el cual por el ADC es un valor entero de 0 a 1023
  voltage3 = valortemp3 * (5.0 / 1023.0); // Se convierte el valor leido a un rango de 0v-5v
  if (voltage3>=4){ // Se revisa si el voltaje medido es 20v o mas para enceder el LED de precuacion
    digitalWrite(led3, HIGH); 
  } else {
    digitalWrite(led3, LOW);  
  }

  // Se imprime el voltage para debbuging
  Serial.print("Voltage0: ");
  Serial.println(voltage0);
  Serial.print("Voltage1: ");
  Serial.println(voltage1);
  Serial.print("Voltage2: ");
  Serial.println(voltage2);
  Serial.print("Voltage3: ");
  Serial.println(voltage3);
}
