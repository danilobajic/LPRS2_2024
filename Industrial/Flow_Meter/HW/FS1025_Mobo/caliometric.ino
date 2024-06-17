
#define PIN_Q A1
#define PIN_HE A2
#define PIN_T A3

#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  lcd.begin(16, 2);
  Serial.begin(115200);
  pinMode(PIN_HE, OUTPUT);
  digitalWrite(PIN_HE, 1);
}


float calculateFlowRate(float voltage) {
  // Formula za izračunavanje protoka na osnovu napona
  return 0.2 * voltage * voltage + 0.3 * voltage + 0.5;
}

float calculateTemperature(float voltage) {
  // Linearna interpolacija za temperaturu
  return (80.0 - 5.0) / (1.0 - 4.25) * (voltage - 4.25) + 5.0;
}

void loop() {

  int smpl_Q = analogRead(PIN_Q);  // Čitamo sirovu vrednost
  float V_Q = smpl_Q * (5.0 / 1024.0);  // Pravilno skaliranje za napon

  int smpl_T = analogRead(PIN_T);  // Čitamo sirovu vrednost
  float V_T = smpl_T * (5.0 / 1024.0);  // Pravilno skaliranje za napon
  
  // Napon prema protoku
  float Q = calculateFlowRate(V_Q);
  float T = calculateTemperature(V_T);

  static int i;
  
  if(i == 0){
    Serial.print("V_Q"); Serial.print('\t'); Serial.print("V_T"); Serial.print('\t'); Serial.print("Q"); Serial.print('\t'); Serial.print("T"); Serial.println();
  }
  Serial.print(V_Q); Serial.print('\t'); Serial.print(V_T); Serial.print('\t'); Serial.print(Q); Serial.print('\t'); Serial.print(T); Serial.println();
  
  i++;
  if(i == 10){
    i = 0;
  }
  

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Q="); lcd.print(Q); lcd.print("L/min");
  lcd.setCursor(0, 1);
  lcd.print("T="); lcd.print(T); lcd.print("*C");

  delay(250);
 
}

