

// --- Programme Arduino --- 

// Auteur du Programme : Hugo.A - Tous droits réservés 
// Programme écrit le : 2/7/2015.

// ------- Licence du code de ce programme ----- 
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License,
//  or any later version.
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

// ////////////////////  PRESENTATION DU PROGRAMME //////////////////// 

// -------- Que fait ce programme ? ---------
 /*Un Reveil */ 

// --- Fonctionnalités utilisées --- 

// Utilise le stockage de données en mémoire Eeprom interne 
// Utilise un afficheur LCD alphanumérique en mode 4 bits 

// -------- Circuit à réaliser --------- 

// Connexion du LCD sur les broches de la carte Arduino :
// Connecter broche RS du LCD sur la broche 8
// Connecter broche E du LCD sur la broche 9
// Connecter broche D4 du LCD sur la broche 10
// Connecter broche D5 du LCD sur la broche 11
// Connecter broche D6 du LCD sur la broche 12
// Connecter broche D7 du LCD sur la broche 13


// /////////////////////////////// 1. Entête déclarative /////////////////////// 
// A ce niveau sont déclarées les librairies incluses, les constantes, les variables, les objets utiles...

// --- Déclaration des constantes ---

// --- Inclusion des librairies ---

#include <LiquidCrystal.h> // Inclusion de la librairie pour afficheur LCD 
#include <TimeAlarms.h>
#include <Time.h>
#include <Wire.h>
#include <EEPROM.h> // Librairie pour le stockage de données en mémoire Eeprom interne 

// --- Déclaration des constantes utiles ---

// --- Déclaration des constantes des broches E/S numériques ---

const int RS=8; // Constante pour la broche 8
const int E=9; // Constante pour la broche 9
const int D4=10; // Constante pour la broche 10
const int D5=11; // Constante pour la broche 11
const int D6=12; // Constante pour la broche 12
const int D7=13; // Constante pour la broche 13
const int buz=7;
const int select=14;
const int gauche=6;
const int droite=5;
const int haut=4;
const int bas=3;
const int lumierebut=2;
const int lumierepin = 15;
boolean ifLum=false;

// --- Déclaration des constantes des broches analogiques ---


// --- Déclaration des variables globales ---
byte alarmLogo[8] = {//Logo alarme
	0b00000,
	0b00000,
	0b01110,
	0b10011,
	0b10101,
	0b10001,
	0b01110,
	0b00000
};


// --- Déclaration des objets utiles pour les fonctionnalités utilisées ---

//------------ Création d'un objet afficheur LCD alphanumérique ---- 
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);// initialisation LCD en mode 4 bits


// ////////////////////////// 2. FONCTION SETUP = Code d'initialisation ////////////////////////// 
// La fonction setup() est exécutée en premier et 1 seule fois, au démarrage du programme

void setup()   { // debut de la fonction setup()

// --- ici instructions à exécuter 1 seule fois au démarrage du programme --- 

// ------- Initialisation fonctionnalités utilisées -------  


//Initialisation de Time
timeReglage();
Alarm.timerRepeat(500, timeReglage); 

//Inisialisation du rétroeclerage
attachInterrupt(0, lumiere, CHANGE);

// Initialisation de l'afficheur LCD 
lcd.begin(16,2); // Initialise le LCD avec 20 colonnes x 4 lignes
delay(10); // pause rapide pour laisser temps initialisation

// ------- Broches en sorties numériques -------  
 pinMode (7,OUTPUT); // Broche 7 configurée en sortie
 
// ------- Broches en entrées numériques -------  
 pinMode (2,INPUT); // Broche 2 configurée en entrée
 pinMode (3,INPUT); // Broche 3 configurée en entrée
 pinMode (4,INPUT); // Broche 4 configurée en entrée
 pinMode (5,INPUT); // Broche 5 configurée en entrée
 pinMode (6,INPUT); // Broche 6 configurée en entrée
 pinMode (14,INPUT); // Broche 14 Select configurée en entrée
 pinMode (15,OUTPUT); // Broche 15 Lumiere configurée en entrée

// ------- Activation si besoin du rappel au + (pullup) des broches en entrées numériques -------  
 digitalWrite (14,HIGH); // Rappel au + activé sur la broche 2 configurée en entrée
 digitalWrite (3,HIGH); // Rappel au + activé sur la broche 3 configurée en entrée
 digitalWrite (4,HIGH); // Rappel au + activé sur la broche 4 configurée en entrée
 digitalWrite (5,HIGH); // Rappel au + activé sur la broche 5 configurée en entrée
 digitalWrite (6,HIGH); // Rappel au + activé sur la broche 6 configurée en entrée

// ------- Activation des alarmes -------  
for(byte i = 1;i<=EEPROM.read(0);i=i+4){
  if(EEPROM.read(i)){
    Alarm.alarmRepeat(EEPROM.read(i+1),EEPROM.read(i+2),0,alarm1);
  }
}
/*
 * Gauche = 1
 * Droite = 2
 * Haut = 3
 * Bas = 4
 * Select = 5
 */

// ------- Initialisation des variables utilisées -------  

} // fin de la fonction setup()
// ********************************************************************************

////////////////////////////////// 3. FONCTION LOOP = Boucle sans fin = coeur du programme //////////////////
// la fonction loop() s'exécute sans fin en boucle aussi longtemps que l'Arduino est sous tension

void loop(){ // debut de la fonction loop()
// --- ici instructions à exécuter par le programme principal --- 


delay(1000);
lcdWrite();

// --- code type Lecture/ecriture Eeprom interne
// int adresse = 0; // adresses entre 0 et 1023 pour Arduino UNO - 1024 octets 
// byte valeur=0; // variable pour octets à stocker/lire en Eeprom

// valeur = EEPROM.read(adresse); // lit une valeur en mémoire Eeprom à l'adresse indiquée
// EEPROM.write(adresse, valeur); // écrit une valeur en mémoire Eeprom à l'adresse indiquée 

//while(1); // stop loop

} // fin de la fonction loop() - le programme recommence au début de la fonction loop sans fin
// ********************************************************************************


// ////////////////////////// FONCTIONS DE GESTION DES INTERRUPTIONS //////////////////// 


// ////////////////////////// AUTRES FONCTIONS DU PROGRAMME //////////////////// 

void lcdWrite(){// Affiche le temp sur l'ecran

  printDigits(hour());
  lcd.print(hour());
  lcd.print(":");
  printDigits(minute());
  lcd.print(minute());
  lcd.print(":");
  printDigits(second());
  lcd.print(second());
  lcd.setCursor(0,2);
  printDigits(day());
  lcd.print(day());
  lcd.print("/");
  printDigits(month());
  lcd.print(month());
  lcd.print("/");
  lcd.print(year());
}

void lcdClear(){
  lcd.home();
  lcd.clear();
}

int printDigits(int digits)
{
  if(digits < 10){
    lcd.print("0");
  }
}

void timeReglage(){
  //Wire.beginTransmission(DS1307_I2C_ADDRESS);   // Open I2C line in write mode
  Wire.write((byte)0x00);                              // Set the register pointer to (0x00)
  Wire.endTransmission();                       // End Write Transmission
//  Wire.requestFrom(DS1307_I2C_ADDRESS, 7);      // Open the I2C line in send mode
  int secon     = bcdToDec(Wire.read() & 0x7f); // Read seven bytes of data
  int minutes     = bcdToDec(Wire.read());
  int hours       = bcdToDec(Wire.read() & 0x3f);  
  int days = bcdToDec(Wire.read());
  int months      = bcdToDec(Wire.read());
  int years       = bcdToDec(Wire.read());
  setTime(hours, minutes, secon, days, months, years); 
}

// ////////////////////////// Alarme /////////////////////


void alarm1(){
  for(short i = 0;i<10;i++){
  digitalWrite(buz,HIGH);
  delay(200);
  digitalWrite(buz,LOW);
  delay(1000);
  }
}

void alarm2(int repeat,int freq){
  for(short i = 0;i<repeat;i++){
  tone(buz,500,500);
  delay(1500);
  }
}
void alarm3(int repeat){
  for(short i = 0;i<repeat;i++) {
  tone(buz,map(i,0,repeat,100,1000),500);
  delay(1500);
  }
}

int difftempS(int h,int m,int s,int hn,int mn,int sn){
    int sa = h*3600 + m*60 + s;
    int san = hn*3600 + mn*60 + sn;
    int difs = sa - san;
    difs = difs - difftempH(h,m,s,hn,mn,sn) *3600;
    difs = difs - difftempM(h,m,s,hn,mn,sn) *60;
    return difs;
}
int difftempH(int h,int m,int s,int hn,int mn,int sn){
    int sa = h*3600 + m*60 + s;
    int san = hn*3600 + mn*60 + sn;
    unsigned int difh = (sa - san)/3600;
    return difh;
}
int difftempM(int h,int m,int s,int hn,int mn,int sn){
    int sa = h*3600 + m*60 + s;
    int san = hn*3600 + mn*60 + sn;
    unsigned int difm = (sa - san) - difftempH(h,m,s,hn,mn,sn) *3600;;
    difm = difm/60;
    return difm;
}

void lumiere(){
  if(ifLum){
     digitalWrite(lumierepin,LOW);
     ifLum=false;
  }else{
      digitalWrite(lumierepin,HIGH);
     ifLum=true;
     Alarm.timerOnce(60, lumiere);
  }
}


int but(){
  if(digitalRead(select) == LOW){
    return 5;
  }else if(digitalRead(gauche) == LOW){
    return 1;
  }else if(digitalRead(droite) == LOW){
    return 2;
  }else if(digitalRead(haut) == LOW){
    return 3;
  }else if(digitalRead(bas) == LOW){
    return 4;
  }else{
    return 0;
  }
}



void newAlarm(byte h,byte m){
  byte i = EEPROM.read(0) + 1;
  EEPROM.write(0,i);
  i=i*4;
  i=i-4;
  EEPROM.write(i+2,h);
  EEPROM.write(i+3,m);
}
// ////////////////////////// Conversion Hexadécimal //////////////

byte decToBcd(byte val){
// Convert normal decimal numbers to binary coded decimal
  return ( (val/10*16) + (val%10) );
}

byte bcdToDec(byte val)  {
// Convert binary coded decimal to normal decimal numbers
  return ( (val/16*10) + (val%16) );
}
  
// ////////////////////////// Fin du programme //////////////////// 


// ////////////////////////// Mémo instructions ////////////////////
/*
 * Bouton:
 * Gauche = 1
 * Droite = 2
 * Haut = 3
 * Bas = 4
 * Select = 5
 *
 */
 // ////////////////////////// Fin Mémo instructions //////////////////// 


