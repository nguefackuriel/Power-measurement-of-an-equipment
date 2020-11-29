//Ce programme affiche la valeur de la consommation energetique au moyen d'un capteur de courant, 
//le niveau de l'eclairage et l'etat du relais

// definition des librairies
#define <Wire.h>
#include <LiquidCrystal_I2C.h>

#define relay=8; // relais au pin 8
boolean etat_relais=false;

// Instanciation de la LCD 20*4
LiquidCrystal_I2C lcd(0x27,20,4);

//Definition des variables
float amplitude_courant;
float valeur_effective;
float tension_effective = 230;
float puissance_effective;
float sensor;



void setup() {
    // initialisation de la liaison serie
Serial.begin(9600);

// Initialisation de la lcd
lcd.init();

//Afichage d'un message de bienvenu
lcd.backlight();
lcd.setCursor(1,0);
lcd.print("Bienvenue");


//configuration relais
pinMode(relay,OUTPUT);

//Calibration du capteur
sensor=getSensorValue(A1);

// Effacement de la LCD
lcd.clear();

}

void loop() {
 // Mesure de la lumiere
 float value=analogRead(A0);
 float light=(value/1024.0)*100.0;

 //Mesure de la puissance

 float sensor_value=getSensorValue(A1);

 //Conversion en courant
 amplitude_courant=(float)(sensor_value-sensor)/1024*5/185*1000000;
 valeur_effective=amplitude_courant/1.414;
 puissance_effective=abs(valeur_effective*tension_effective/1000);


 // Controle du relais
 // On eteind si le taux de lumiere >75%
 if(light>75)
 {
  digitalWrite(relay,LOW);
  etat_relais=false;
 }
 else if(light<50)
 {
  digitalWrite(relay,HIGH);
  etat_relais=true;
 }

 //Affichage de l'etat
 lcd.setCursor(1,0);
 lcd.print("Relais: ");
 if(etat_relais)
 {
  lcd.print("Allumee");
 }
 else
 {
  lcd.print("Eteind");
 }

//Affichage de la consommation
lcd.setCursor(1,1);
lcd.print("Puissance: ");
lcd.print("puissance_effective");
lcd.print("W");


    //Affichage du niveau de luminosite
lcd.setCursor(1,2);
lcd.print("Light:");
lcd.print(light);
lcd.println("%");

delay(500);

}

// Obtenir la lecture du capteur
float getSensorValue(int pin)
{
  int sensorValue;
  float avgSensor=0;
  int nbre_mesure=100;
  for(int i=0; i<nbre_mesure; i++)
  {
    sensorValue = analogRead(pin);
    avgSensor = avgSensor + float(sensorValue);
  }
  avgSensor = avgSensor/float(nbre_mesure);
  return avgSensor;
  
}
