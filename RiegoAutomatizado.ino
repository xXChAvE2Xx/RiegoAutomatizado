#include "DHT.h"
#define DHTTYPE DHT11
#include <SPI.h>
#define humedadSueloPin A0
#define ldr_pin A5

const int DHTPIN = 6;
int luzIntencidad = 0;
int motorRiego_pin = 3;
int motorRiego_velocidad = 255;//Entre 0 y 255.

DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(9600);
  Serial.println("DHT11 Prueba!");
  dht.begin(); //Inicializamos el dht  
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int HumedadSuelo = map(analogRead(humedadSueloPin), 365, 1020, 100, 0);
  int luzIntencidad = map(analogRead(ldr_pin), 0, 1023, 100, 0);
  
  // Humedad relativa y temperatura
  Serial.println("*******************************");
  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.println(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println(" *C ");
   
  //Intencidad de la Luz
  Serial.print("Luz: ");
  Serial.print(luzIntencidad);
  Serial.println("%");

  //Humedad del suelo
  Serial.print("Humedad del suelo: ");
  Serial.print(HumedadSuelo);
  Serial.println(" %\t");
  Serial.println("*******************************");

//**************************************************************
// Datos
// ETO= Dato de conagua
// Etc= Eto*Kc*FT(0.8)
// Kc= Coeficiente del cultivo
// FT= Factor de Tanque
// L.R.= Etc/Eficiencia del sistema de riego
//Datos mini bomba.
//Voltaje de funcionamiento: 3-6v DC.
//Consumo de corriente a 5VDC: 0.40A
//Altura bombeo máx.: 40-110cm.
//Caudal bombeo máx.: 80-120 l/h (Aprox 1.625 l/m).
//Tiempo continuo de trabajo de 500 horas.
//**************************************************************


 if( HumedadSuelo <= 60) {
   digitalWrite(motorRiego_pin, HIGH);
   Serial.println("Riego activado");
   analogWrite(motorRiego_pin, motorRiego_velocidad);
 }else{
   digitalWrite(motorRiego_pin, LOW);
   Serial.println("Riego detenido");
 }
 
 delay (6000);//Tiempo de espera 6s para la siguiente muestra
}
