#define LED_1 19
#define LED_2 0
#define LED_3 2
#define LED_4 1

#define BUTTON_1 46
#define BUTTON_2 16

#define LDR 3

#define BUZZER 10

#include <vector>

using namespace std; 

int button_state = LOW;

int o = 0;

vector< int > vlrs;

void setup() {
  Serial.begin(9600);

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);

  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);

  pinMode(LDR, INPUT);

  pinMode(BUZZER, OUTPUT);

}

void loop() {

  if (digitalRead(BUTTON_1) == HIGH) {
    delay(500);

    converteSensor();

    delay(1000);
  }

  if(digitalRead(BUTTON_2) == HIGH) {
    delay(500);

    ALL_VALUES();

    delay(1000);
  }

}

void converteSensor() { 
  
  int bis[4];

  int div = (4095 - 500)/16;

  int vlr = analogRead(LDR);

  int bi = vlr/div, bi2 = vlr/div;

  Serial.println(vlr);   
  Serial.println(bi);   
   
  for(int i = 0; i < 4 ; i++)    
  {    
    bis[i] = bi % 2; 
    bi = bi/2;   

    Serial.println(bis[i]);
    vlrs.push_back(bis[i]);
  }
  
  vlrs.push_back(bi2);
  Serial.println(vlrs[4+o]);
  LED_BUZZER_ACTION(o);
} 

void ALL_VALUES() {

  int k = 0;

  Serial.println("Segue valores guardados: ");

  delay(500);

  for (int j = 0; j < vlrs.size()/4 ; j++){

    LED_BUZZER_ACTION(k);

    Serial.println("Próximo no vetor: ");

    delay(1500);

    k += 5;

  }

  vlrs.clear();
  o = 0;
  Serial.println("Vetor esvaziado!");
}

void LED_BUZZER_ACTION (int count) {

  int Tones[15] = {650,800, 1666, 4186, 4435, 4699, 4978, 5274, 5588, 5920, 6272, 6645, 7040, 7459, 7902};

  if(vlrs[0 + count] == 1) {
    digitalWrite(LED_1, HIGH); 
  }

  if(vlrs[1 + count] == 1) {
    digitalWrite(LED_2, HIGH);
  }
  
  if(vlrs[2 + count] == 1) {
    digitalWrite(LED_3, HIGH);
  }

  if(vlrs[3 + count] == 1) {
    digitalWrite(LED_4, HIGH);  
  }

  tone(BUZZER,Tones[vlrs[4 + count]],1000);

  delay(1000);

  digitalWrite(LED_1 ,LOW);
  digitalWrite(LED_2 ,LOW);
  digitalWrite(LED_3 ,LOW);
  digitalWrite(LED_4 ,LOW);

  o += 5;
  
}
