void controle(bool autom, bool acionaA, bool acionaB, bool limiteA, bool limiteB, 
              long tempoManobra, bool &alarmeA, bool &alarmeB, bool reset, 
              int numeroDeX, bool &recomecar, bool &concluido)
{
    static int direcao = 0;               // 1: direita, -1: esquerda, 0: centro
    static int cicloAtual = 0;            // Contador de ciclos automáticos
    static unsigned long tempoInicio = 0; // Tempo de início de cada manobra
    static bool motorLigado = false;      // Controle do motor (ligado/desligado)
    static bool cicloIniciado = false;    // Verifica se o ciclo foi iniciado
    static bool primeiraVez = true;       // Primeira vez após reinício

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
        return;
    }

    // Lógica para modo automático
    if (autom) {
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
        // Lógica para modo manual
        if (acionaA && !limiteA) {
            Serial.println("Movendo para a direita (manual).");
            direcao = 1;  // Movimentação para a direita
            motorLigado = true;
        } else if (acionaB && !limiteB) {
            Serial.println("Movendo para a esquerda (manual).");
            direcao = -1;  // Movimentação para a esquerda
            motorLigado = true;
        }

        // Verifica limites e para o motor
        if ((limiteA && direcao == 1) || (limiteB && direcao == -1)) {
            Serial.println("Limite atingido, voltando ao centro (manual).");
            direcao = 0;  // Retorna ao centro
            motorLigado = false;  // Para o motor
        }
    }
}
