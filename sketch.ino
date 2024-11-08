// Pievienojam vajadzīgās bibliotēkas - tās mums palīdz strādāt ar WiFi un LCD ekrānu
#include <WiFi.h>            
#include <Wire.h>            
#include <LiquidCrystal_I2C.h> 

// Izveidojam LCD ekrāna objektu - tas kontrolēs mūsu ekrānu
// 0x27 - ekrāna adrese, 16 - kolonnu skaits, 2 - rindu skaits
LiquidCrystal_I2C LCD(0x27, 16, 2);

// WiFi tīkla iestatījumi
const char* wifi_nosaukums = "Wokwi-GUEST";  // Tīkla nosaukums
const char* wifi_parole = "";                // Tīkla parole

// Laika iestatījumi - izmantojam Latvijas laiku (UTC+2)
#define LAIKA_ZONA 7200  // Latvijas laiks sekundēs (2 stundas * 3600)

// Programmas sākums - šī daļa izpildās tikai vienu reizi
void setup() {
  // Ieslēdzam LCD ekrānu
  LCD.init();
  LCD.backlight();
  
  // Parādam ziņojumu, ka mēģinām pieslēgties internetam
  LCD.setCursor(0, 0);
  LCD.print("Pievienos WiFi");
  
  // Pieslēdzamies WiFi tīklam
  WiFi.begin(wifi_nosaukums, wifi_parole);
  
  // Gaidām, kamēr pieslēgsies internetam
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    LCD.print(".");
  }
  
  // Kad pieslēdzāmies, parādam to ekrānā
  LCD.clear();
  LCD.print("WiFi OK!");
  delay(1000);
  
  // Iestatām pareizo laiku
  configTime(LAIKA_ZONA, 0, "pool.ntp.org");
}

// Funkcija laika parādīšanai - šī funkcija rāda laiku ekrānā
void raditLaiku() {
  struct tm laiks;
  
  // Mēģinām iegūt laiku
  if (!getLocalTime(&laiks)) {
    LCD.setCursor(0, 0);
    LCD.print("Kluda!");
    return;
  }
  
  // Notīram ekrānu
  LCD.clear();
  
  // Parādam pulksteni
  LCD.setCursor(0, 0);
  LCD.printf("%02d:%02d:%02d", 
    laiks.tm_hour,    // Stundas
    laiks.tm_min,     // Minūtes
    laiks.tm_sec      // Sekundes
  );
  
  // Parādam datumu
  LCD.setCursor(0, 1);
  LCD.printf("%02d.%02d.%04d", 
    laiks.tm_mday,          // Diena
    laiks.tm_mon + 1,       // Mēnesis (+1, jo sākas no 0)
    laiks.tm_year + 1900    // Gads (+1900, jo sākas no 1900)
  );
}

// Programmas galvenā cilpa - šī daļa atkārtojas bezgalīgi
void loop() {
  raditLaiku();  // Parādam laiku
  delay(1000);   // Pagaidām 1 sekundi
}
