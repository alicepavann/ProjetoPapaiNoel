
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
  Serial.print("Endereço IP do ESP32: ");
  Serial.println(WiFi.localIP());
  }
}