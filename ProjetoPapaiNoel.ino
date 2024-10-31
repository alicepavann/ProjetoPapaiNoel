#define BLYNK_TEMPLATE_ID "TMPL2FIys0Pd9"
#define BLYNK_TEMPLATE_NAME "LED ESP32"
#define BLYNK_FIRMWARE_VERSION "0.1.0"
#define BLYNK_PRINT Serial
#define APP_DEBUG
#define USE_ESP32_DEV_MODULE
#define LED_PIN 2  // Pino do LED
#include "Definicoes.h"
#include "BlynkEdgent.h"

// Variáveis globais e objetos
String localIP_Address = "192.168.0.1";  // Endereço IP local
BlynkTimer timer;                        // Timer do Blynk
long previousMillis = 0;                 // Tempo anterior para verificar o intervalo
int interval = 10000;                    // Intervalo de verificação (10 segundos)
bool apModeEnabled = false;              // Flag para saber se o modo AP foi ativado
const int pinAutom = 22;                 //pino de teste
///////////////variaveis para teste/////////////////////
bool autoMode = false, manualMode = false;
bool activateA = false, activateB = false;
bool limitA = false, limitB = false;
bool alarmA = false, alarmB = false;
int numberOfCycles = 0;
long maneuverTime = 5000;
bool reset = false, restart = false;
bool completed = false;
bool ledState = HIGH;
int joystick1 = 0;
int joystick2 = 0;
int joystick3 = 0;
int joystick4 = 0;
int veloc_hand = 0;


void myTimerEvent() {
  // Envia dados ao Blynk
  Blynk.virtualWrite(V4, 20.0 + random(-111, 111) / 9.9);
}

BLYNK_WRITE(V4) {                //JOYSTICK CONTROLE CINTURA E ELEVAÇÃO
  joystick1 = param[0].asInt();  // Valor do eixo X
  joystick2 = param[1].asInt();  // Valor do eixo Y

  Serial.print("Posição Joystick 1: ");  // imprimi valores para teste
  Serial.println(joystick1);
  Serial.print("Posição JoySstick 2: ");
  Serial.println(joystick2);
}

BLYNK_WRITE(V5) {                //JOYSTICK CONTROLE CABEÇA, ACENO E BRAÇO
  joystick3 = param[0].asInt();  // Valor do eixo X
  joystick4 = param[1].asInt();  // Valor do eixo Y

  Serial.print("Posição Joystick 3: ");  // imprimi valores para teste
  Serial.println(joystick3);
  Serial.print("Posição Joystick 4: ");
  Serial.println(joystick4);
}
// Função chamada quando o botão virtual no Blynk (V0) é pressionado
BLYNK_WRITE(V6) {
  ledState = param.asInt();  // Obtém o estado do botão (0 ou 1)

  // Atualiza o estado do LED
  digitalWrite(LED_PIN, ledState);

  // Exibe o estado atual do LED no monitor serial
  if (ledState) {
    Serial.println("LED ligado");
  } else {
    Serial.println("LED desligado");
  }
}

BLYNK_WRITE(V8)
{
  int numOfX = param.asInt();
  Serial.print("Numero de Vezes da manobra x: "); Serial.println(numOfX);
}
BLYNK_WRITE(V25) { //Velocidade do ACENO (DE 0 A 10 NO APLICATIVO)
    int sliderValue = param.asInt(); // Lê o valor do controle deslizante de 1 a 10
    sliderValue = constrain(sliderValue, 1, 10);
    int pwmValue = map(sliderValue, 1, 10, 0, 255); // Converte para a escala de 0 a 255
    Serial.print("velocidade aceno: "); // Envia o valor PWM para o motor
    Serial.println(pwmValue);
}

BLYNK_WRITE(V23) { //Velocidade da CABEÇA (DE 0 A 10 NO APLICATIVO)
    int sliderValueC = param.asInt(); // Lê o valor do controle deslizante de 1 a 10
    sliderValueC = constrain(sliderValueC, 1, 10);
    int pwmValueC = map(sliderValueC, 1, 10, 0, 255); // Converte para a escala de 0 a 255
    Serial.print("velocidade cabeca: "); 
    Serial.println(pwmValueC);
}

BLYNK_WRITE(V7) {
  ledState = param.asInt();  // Obtém o estado do botão (0 ou 1)
  if (ledState == 1 || digitalRead(pinAutom) == HIGH) {
    digitalWrite(LED_PIN, ledState);
    Serial.println("entrou no if");
    autoMode = true;
  } else {
    autoMode = false;
    manualMode = true;
  }
}

//////////////////SAIDAS///////////////////////
void atualizarSaidas() {
  digitalWrite(sdHead, axsdHead);
  digitalWrite(sdArmUp, axsdArmUp);
  digitalWrite(sdArmDown, axsdArmDown);
  digitalWrite(sdLegsUp, axsdLegsUp);
  digitalWrite(sdLegsDown, axsdLegsDown);
  digitalWrite(sdWaistLeft, axsdWaistLeft);
  digitalWrite(sdWaistRight, axsdWaistRight);
  // Atualizar outras saídas conforme necessário
}

void setup() {
  Serial.begin(115200);
  delay(100);
  pinMode(pinAutom, INPUT);
  pinMode(LED_PIN, OUTPUT);  // Define o pino do LED como saída
  digitalWrite(LED_PIN, ledState);
  BlynkEdgent.begin();                     // Inicia o Blynk e a configuração Wi-Fi
  timer.setInterval(10000, myTimerEvent);  // Executa a função a cada 10 segundos
}

void loop() {
  BlynkEdgent.run();  // Mantém o Blynk ativo
  timer.run();        // Executa o temporizador do Blynk

  ////////////////WIFI////////////////////////////////////
  long currentMillis = millis();
  // Verifica a cada 10 segundos se ainda está conectado ao Wi-Fi
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    checkWiFiAndEnterAP();  // Se a conexão Wi-Fi for perdida, entra no modo AP
  }
  localIP_Address = WiFi.localIP().toString();
  long count = millis() % 9999;
  Blynk.virtualWrite(V2, count);
  ///////////////////////////////////////////////////////////


  ///////////////// chamada das funções para cada eixo
  //chamada para acionar o eixo de elevação
  control(autoMode, axedLegsUp, axedLegsDown,
          maneuverTime, joystick1, joystick2, numberOfCycles, reset, restart,
          alarmA, alarmB, completed, axsdArmUp, axsdArmDown);



    ///////////////// digitalWrite (atualizar o mapa de saida)
    atualizarSaidas();
}