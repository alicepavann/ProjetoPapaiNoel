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
int previousMillis = 0;  // Tempo anterior para verificar o intervalo
int interval = 10000;  // Intervalo de verificação (10 segundos)
bool apModeEnabled = false;  // Flag para saber se o modo AP foi ativado

//Função para verificar a conexão wifi e entrar no modo AP
void checkWiFiAndEnterAP() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Conexão Wi-Fi perdida. Tentando reconectar...");

    // Desconectar e tentar reconectar
    WiFi.disconnect();
    WiFi.begin();  // Tenta reconectar com as credenciais já salvas

    long startAttemptTime = millis();
    bool reconnectSuccess = false;

    // Tentar reconectar por até 10 segundos
    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
      delay(500);
      Serial.print(".");
      if (WiFi.status() == WL_CONNECTED) {
        reconnectSuccess = true;
        break;
      }
    }

    if (reconnectSuccess) {
      Serial.println("Reconectado com sucesso ao Wi-Fi.");
    } else {
      Serial.println("Falha na reconexão. Entrando no modo AP...");

      // Reinicia o modo AP para nova configuração
      BlynkState::set(MODE_WAIT_CONFIG);  // Entra no modo AP de configuração

      // Fica no modo AP até que o usuário configure a nova rede
      while (BlynkState::get() != MODE_RUNNING) {
        BlynkEdgent.run();  // Executa a configuração do Blynk
        delay(100);
      }

      // Após a configuração, tenta reconectar novamente
      if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Reconexão após o modo AP bem-sucedida.");
      } else {
        Serial.println("Ainda não conectado após o modo AP.");
      }
    }
  } else {
    Serial.println("Conexão Wi-Fi estável.");
  }
}

void myTimerEvent() {
  // Envia dados ao Blynk
  Blynk.virtualWrite(V4, 20.0 + random(-111, 111) / 9.9);
}
bool ledState = HIGH;  

// Função chamada quando o botão virtual no Blynk (V1) é pressionado
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

void setup() {
  Serial.begin(115200);
  delay(100);

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

  // Alterna o estado do LED para indicar o status da conexão Wi-Fi
  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(LED_PIN, HIGH);  // LED aceso se estiver conectado
  } else {
    digitalWrite(LED_PIN, LOW);  // LED apagado se não estiver conectado
  }

  // Atualiza o endereço IP e envia valores para o Blynk
  localIP_Address = WiFi.localIP().toString();
  long count = millis() % 9999;
  Blynk.virtualWrite(V2, count);

  // Exibe o endereço IP do ESP32
  Serial.print("Endereço IP do ESP32: ");
  Serial.println(WiFi.localIP());
  delay(1000); 
}
//testando versinamento com git