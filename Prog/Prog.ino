// --- Programme Arduino --- 
// Trame de code générée par le générateur de code Arduino
// du site www.mon-club-elec.fr 

// Auteur du Programme : X. HINAULT - Tous droits réservés 
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
 /* Reveil */ 

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

// --- Déclaration des constantes des broches analogiques ---


// --- Déclaration des variables globales ---



// --- Déclaration des objets utiles pour les fonctionnalités utilisées ---

//------------ Création d'un objet afficheur LCD alphanumérique ---- 
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);// initialisation LCD en mode 4 bits


// ////////////////////////// 2. FONCTION SETUP = Code d'initialisation ////////////////////////// 
// La fonction setup() est exécutée en premier et 1 seule fois, au démarrage du programme

void setup()   { // debut de la fonction setup()

// --- ici instructions à exécuter 1 seule fois au démarrage du programme --- 

// ------- Initialisation fonctionnalités utilisées -------  
//Initialisation de Time
timeSet();
Alarm.timerRepeat(1500, timeSet); 
// Initialisation de l'afficheur LCD 
lcd.begin(20,4); // Initialise le LCD avec 20 colonnes x 4 lignes
delay(10); // pause rapide pour laisser temps initialisation

// ------- Broches en sorties numériques -------  
 pinMode (7,OUTPUT); // Broche 7 configurée en sortie
 
// ------- Broches en entrées numériques -------  
 pinMode (2,INPUT); // Broche 2 configurée en entrée
 pinMode (3,INPUT); // Broche 3 configurée en entrée
 pinMode (4,INPUT); // Broche 4 configurée en entrée
 pinMode (5,INPUT); // Broche 5 configurée en entrée
 pinMode (6,INPUT); // Broche 6 configurée en entrée

// ------- Activation si besoin du rappel au + (pullup) des broches en entrées numériques -------  
 digitalWrite (2,HIGH); // Rappel au + activé sur la broche 2 configurée en entrée
 digitalWrite (3,HIGH); // Rappel au + activé sur la broche 3 configurée en entrée
 digitalWrite (4,HIGH); // Rappel au + activé sur la broche 4 configurée en entrée
 digitalWrite (5,HIGH); // Rappel au + activé sur la broche 5 configurée en entrée
 digitalWrite (6,HIGH); // Rappel au + activé sur la broche 6 configurée en entrée

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

  printDigit(hour());
  lcd.print(hour());
  lcd.print(":");
  printDigit(minute());
  lcd.print(minute());
  lcd.print(":");
  printDigit(second());
  lcd.print(second());
  lcd.setCursor(0,2);
  printDigit(day());
  lcd.print(day());
  lcd.print("/");
  printDigit(month());
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

void timeSet(){
  Wire.beginTransmission(DS1307_I2C_ADDRESS);   // Open I2C line in write mode
  Wire.write((byte)0x00);                              // Set the register pointer to (0x00)
  Wire.endTransmission();                       // End Write Transmission
  Wire.requestFrom(DS1307_I2C_ADDRESS, 7);      // Open the I2C line in send mode
  seconds     = bcdToDec(Wire.read() & 0x7f); // Read seven bytes of data
  minutes     = bcdToDec(Wire.read());
  hours       = bcdToDec(Wire.read() & 0x3f);  
  days = bcdToDec(Wire.read());
  months      = bcdToDec(Wire.read());
  years       = bcdToDec(Wire.read());
  setTime(hours, minutes, seconds, days, months, years); 
}

// ////////////////////////// Fin du programme //////////////////// 


// ////////////////////////// Mémo instructions //////////////////// 
// ////////////////////////// Fin Mémo instructions //////////////////// 


