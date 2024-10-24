#define BLYNK_TEMPLATE_ID "TMPL2FIys0Pd9"
#define BLYNK_TEMPLATE_NAME "LED ESP32"
#define BLYNK_FIRMWARE_VERSION "0.1.0"
#define BLYNK_PRINT Serial
#define APP_DEBUG
#define USE_ESP32_DEV_MODULE
#define LED_PIN 2  // Pino do LED

#include "BlynkEdgent.h"

// Variáveis globais e objetos
String localIP_Address = "192.168.0.1";  // Endereço IP local
BlynkTimer timer;  // Timer do Blynk
unsigned long previousMillis = 0;  // Tempo anterior para verificar o intervalo
int interval = 10000;  // Intervalo de verificação (10 segundos)
bool apModeEnabled = false;  // Flag para saber se o modo AP foi ativado
const int pinoAutom = 23;

 // Variáveis fictícias para simulação
  bool autom = false;
  bool acionaA = false;
  bool acionaB = false;
  bool limiteA = false;
  bool limiteB = false;
  long tempoManobra = 5000;  // 5 segundos de tempo de manobra
  bool alarmeA = false;
  bool alarmeB = false;
  bool reset = false;
  int numeroDeX = 3;  // Realizar 3 ciclos automáticos
  bool recomecar = false;
  bool concluido = false;





void myTimerEvent() {
  // Envia dados ao Blynk
  Blynk.virtualWrite(V4, 20.0 + random(-111, 111) / 9.9);
}
bool ledState = HIGH;  

// Função chamada quando o botão virtual no Blynk (V0) é pressionado
BLYNK_WRITE(V0) {
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

BLYNK_WRITE(V7) {
  ledState = param.asInt();  // Obtém o estado do botão (0 ou 1)

  // Atualiza o estado do LED
  digitalWrite(LED_PIN, ledState);
  
  // Exibe o estado atual do LED no monitor serial
  if (ledState == 1 || digitalRead(pinoAutom) == HIGH) {
    Serial.println("entrou no if");
    autom = true;
    recomecar = true;
      // Chama a função controle
    controle(autom, acionaA, acionaB, limiteA, limiteB, tempoManobra, alarmeA, alarmeB, reset, numeroDeX, recomecar, concluido);
  } else {
    autom = false;
  }
}
  

void setup() {
  Serial.begin(115200);
  delay(100);
  pinMode(pinoAutom, INPUT);
  pinMode(LED_PIN, OUTPUT);  // Define o pino do LED como saída
  digitalWrite(LED_PIN, ledState);
  BlynkEdgent.begin();  // Inicia o Blynk e a configuração Wi-Fi
  timer.setInterval(10000, myTimerEvent);  // Executa a função a cada 10 segundos
}

void loop() {
  BlynkEdgent.run();  // Mantém o Blynk ativo
  timer.run();  // Executa o temporizador do Blynk

  long currentMillis = millis();

  // Verifica a cada 10 segundos se ainda está conectado ao Wi-Fi
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    checkWiFiAndEnterAP();  // Se a conexão Wi-Fi for perdida, entra no modo AP
  }
  
  // Atualiza o endereço IP e envia valores para o Blynk
  localIP_Address = WiFi.localIP().toString();
  long count = millis() % 9999;
  Blynk.virtualWrite(V2, count);

}