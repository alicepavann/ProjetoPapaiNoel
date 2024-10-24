const int ledPin = 2;  // Pino do LED (ajuste conforme necessário)
const int pinoAutomatico = 23; // Pino D23 do ESP32 para ativar o modo automático

void controle(bool &autom, bool acionaA, bool acionaB, bool limiteA, bool limiteB, 
              long tempoManobra, bool &alarmeA, bool &alarmeB, bool reset, 
              int numeroDeX, bool &recomecar, bool &concluido)
{
    int direcao = 0;               // 1: direita, -1: esquerda, 0: centro
    int cicloAtual = 0;            // Contador de ciclos automáticos
    long tempoInicio = 0;           // Tempo de início de cada manobra
    bool motorLigado = false;      // Controle do motor (ligado/desligado)
    bool cicloIniciado = false;    // Verifica se o ciclo foi iniciado
    bool primeiraVez = true;       // Primeira vez após reinício

    // Verifica se o pino 23 foi acionado para definir o modo automático
    autom = digitalRead(pinoAutomatico);

    if (reset) {
        // Resetando todas as variáveis
        Serial.println("Resetando sistema.");
        alarmeA = false;
        alarmeB = false;
        cicloAtual = 0;
        motorLigado = false;
        cicloIniciado = false;
        concluido = false;
        direcao = 0; // Volta para o centro
        primeiraVez = true;
        digitalWrite(ledPin, LOW);  // Apaga o LED durante o reset
        return;
    }

    // Modo automático acende o LED
    if (autom) {
        digitalWrite(ledPin, HIGH);  // Acender o LED para indicar modo automático
        if (primeiraVez) {
            Serial.println("Modo automático iniciado.");
            primeiraVez = false;
            cicloIniciado = true;
            tempoInicio = millis();  // Inicia temporizador para tempo de manobra
        }

        if (cicloIniciado) {
            // Controle do motor de acordo com a direção
            if (direcao == 0) {
                Serial.println("Movendo para a direita.");
                direcao = 1;  // Mover para a direita
            } else if (direcao == 1 && !limiteA) {
                Serial.println("Movendo para a direita até limite A.");
                motorLigado = true;  // Motor ligado
            } else if (direcao == 1 && limiteA) {
                Serial.println("Limite A atingido, movendo para o centro.");
                direcao = 0;  // Volta para o centro
                motorLigado = false;  // Motor desligado
            } else if (direcao == 0 && !limiteB) {
                Serial.println("Movendo para a esquerda.");
                direcao = -1;  // Mover para a esquerda
            } else if (direcao == -1 && limiteB) {
                Serial.println("Limite B atingido, movendo para o centro.");
                direcao = 0;  // Volta para o centro
                motorLigado = false;  // Motor desligado
            }

            // Verificação de tempo para alarme
            if (millis() - tempoInicio > tempoManobra) {
                if (direcao == 1) {
                    alarmeA = true;  // Ativar alarme A
                    Serial.println("Alarme A! Tempo excedido.");
                } else if (direcao == -1) {
                    alarmeB = true;  // Ativar alarme B
                    Serial.println("Alarme B! Tempo excedido.");
                }
                motorLigado = false;  // Parar o motor
                cicloIniciado = false; // Fim do ciclo
            }

            // Verifica se o ciclo foi concluído e incrementa o contador
            if (!motorLigado && direcao == 0) {
                cicloAtual++;
                Serial.print("Ciclo ");
                Serial.print(cicloAtual);
                Serial.println(" concluído.");
                if (cicloAtual >= numeroDeX) {
                    concluido = true;
                    cicloIniciado = false;
                    Serial.println("Todos os ciclos automáticos concluídos.");
                } else {
                    tempoInicio = millis();  // Reinicia o temporizador para o próximo ciclo
                }
            }
        }
    } else {
        // Se o modo automático estiver desligado, o LED será apagado
        digitalWrite(ledPin, LOW);  // Apaga o LED quando não está no modo automático
    }
}

void setup_controle() {
  pinMode(ledPin, OUTPUT);       // Define o pino do LED como saída
  pinMode(pinoAutom, INPUT);     // Define o pino 23 como entrada
  Serial.begin(115200);        
}

void loop_controle() {

  
  delay(100); 
}


