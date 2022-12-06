#include <WiFi.h>
#include <WebServer.h>

#define LED_1 21
#define LED_2 48

#define BUTTON_1 1
#define BUTTON_2 2

#define BUZZER 37

#define seed_value 1
#define offset 1
#define range 4

//Iniciando variáveis necessárias para a jogabilidade
int points = 0;
bool true_state;
bool button_state_1;
bool button_state_2;
bool end_game;

int Tones[5] = {400, 1666, 2920};

// SSID & Password
const char* ssid = "Inteli-COLLEGE";  // Enter your SSID here
const char* password = "QazWsx@123";  //Enter your Password here

WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)

void setup() {
  Serial.begin(115200);
  Serial.println("Try Connecting to ");
  Serial.println(ssid);

  // Connect to your wi-fi modem
  WiFi.begin(ssid, password);

  // Check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());  //Show ESP32 IP on serial

  server.on("/", handle_root);

  server.begin();
  Serial.println("HTTP server started");

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  
  pinMode(BUZZER, OUTPUT);

  pinMode(BUTTON_1, INPUT);

  pinMode(BUTTON_2, INPUT);
  
  srand(seed_value);

  delay(100); 

}

void loop() {
  server.handleClient();
  if (!end_game) {
    
    game();
    
  }
}

// HTML & CSS contents which display on web server
String HTML = "<!DOCTYPE html>\
<html>\
<body>\
<h3>Morto ou Vivo!</h3>\
</body>\
</html>";

String HTML2 = "<!DOCTYPE html>\
<html>\
<body>\
<h3>Fim de Jogo!</h3>\
</body>\
</html>";

// Handle root url (/)
void handle_root() {
  server.send(200, "text/html", HTML);
  if (end_game) {
    server.send(200, "text/html", HTML2);
  }
}

void checkState () {

  button_state_1 = digitalRead(BUTTON_1);
  button_state_2 = digitalRead(BUTTON_2);

  if (button_state_1 && button_state_2 && true_state) {

    
    Serial.println("Ponto vivo!");
    return;

  }
  else if (!button_state_1 && !button_state_2 && !true_state) {


    Serial.println("Ponto morto!");
    return;

  }
  else {

    end_game = true;
    Serial.println("Fim de jogo");

  }
}

void game() {

  int nmr = offset + (rand() % range);
  int nmr_2 = offset + (rand() % range);

  //Serial.println(nmr);
  Serial.println(nmr_2);

  for (int i = 0; i < nmr; i++)
  {
    tone(BUZZER,Tones[0],300);
    delay(1000);
  }

  if (nmr_2 % 2 == 0) {

    true_state = true;

    digitalWrite(LED_2, HIGH);
    tone(BUZZER,Tones[2],470);
  
    delay(400);
    checkState();

    digitalWrite(LED_2, LOW);
  }
  else {

    true_state = false;

    digitalWrite(LED_1, HIGH);
    tone(BUZZER,Tones[2],470);
  
    delay(400);

    checkState();

    digitalWrite(LED_1, LOW);
  }

  delay(1000);
}  