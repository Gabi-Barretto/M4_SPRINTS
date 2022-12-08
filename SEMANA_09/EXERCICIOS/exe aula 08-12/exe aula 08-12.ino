#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <iostream>
using namespace std;

const char* ssid = "Inteli-COLLEGE";
const char* password = "QazWsx@123";
#define I2C_SDA 4
#define I2C_SCL 5

#define RGB_BRIGHTNESS 64 

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

bool cadastrou = false;
// set LCD address, number of columns and rows

// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);


void setup() {
  Serial.begin(115200);

  Wire.begin(I2C_SDA, I2C_SCL);

  lcd.init();

  lcd.backlight();

  lcd.setCursor(0, 0);


}

char nova_senha;

void loop() {

  if (!cadastrou) {
    Senha();
  }


  delay(5000);
}

void Senha( ) {

  Serial.println("qual a nova senha?");
  while (Serial.available() == 0) {}     //wait for data available
  String nvsenha = Serial.readString();  //read until timeout           
  Serial.print(nvsenha);
  if(nvsenha.length() != 5) {
    Serial.println("A senha precisa de 4 dígitos!");
    return;
  }
  delay(3000);
  cadastrou = true;
  if (nvsenha) {
    Serial.println("Confirme a senha");
    while (Serial.available() == 0) {}
    String senha = Serial.readString();

    delay(3000);

    if(senha == nvsenha){
      Serial.println("Printando no LCD - AU");
      neopixelWrite(RGB_BUILTIN,0,RGB_BRIGHTNESS,0); // Green
      lcd.print("Autorizado!");
      delay(1000);
      //lcd.clear(); 
    }
    else {
      Serial.println("Printando no LCD - NG");
      neopixelWrite(RGB_BUILTIN,RGB_BRIGHTNESS,0,0); // Red
      lcd.print("NEGADO!");
      delay(1000);
      //lcd.clear(); 
    }
  }
}