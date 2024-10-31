#include "Definicoes.h"

/* PARAMETROS DE ENTRADA
P0 = ENTRADA MODO DE OPERAÇÃO
P1 = LIMITE A = SENSOR DE FIM DE CURSO LADO A
P2 = LIMITE B = SENSOR DE FIM DE CURSO LADO B
P3 = MANEUVERTIME = TEMPO DE MANOBRA MILISEGUNDOS -> BLYNK
P4 = JOYSTICK = POSIÇÃO DO JOYSTICK
P5 = numberOfCycles = NUMERO DE CICLOS DA COREOGRAFIA
P6 = RESET = ORDEM EXTERNA PARA RESET DE FALHAS
P7 = RESTART = ORDEM EXTERNA PARA REINICIAR MODO AUTOMATICO (NOVA COREOGRAFIA)

PARAMETROS DE SAIDA
P8 = ALARMA = FALHA NO ACIONAMENTO LADO A
P9 = ALARMB = FALHA NO ACIONAMENTO LADO B
P10 = COMPLETED = CICLO CONCLUIDO
P11 = OUT A = ACIONA MOTOR LADO A 
P12 = OUT B = ACIONA MOTOR LADO B
*/

void control(bool autoMode, bool limitA, bool limitB, 
             long maneuverTime, int joystickX, int joystickY, int numberOfCycles, 
             bool reset, bool &restart, bool &alarmA, bool &alarmB,  
             bool &completed, bool &outA, bool &outB) {

    int direction = 0;                // 1: direita, -1: esquerda, 0: centro
    int currentCycle = 0;             // Contador de ciclos automáticos
    long startTime = 0;               // Tempo de início de cada manobra
    bool cycleStarted = false;        // Verifica se o ciclo foi iniciado
    bool firstTime = true;            // Primeira vez após reinício
    bool motorOn = false;             // Status do motor


    // Modo Automático
    if (autoMode) {
        if (!cycleStarted) {
            if (!limitA && currentCycle < numberOfCycles) {
                direction = -1;
                cycleStarted = true;
                firstTime = true;
                completed = false;
            } else if (!limitB) {
                direction = 1;
                cycleStarted = true;
                firstTime = true;
                completed = false;
            }
        } else {
            // Verificação de tempo para alarme
            if (millis() - startTime > maneuverTime) {
                if (direction == 1) alarmA = true;
                else if (direction == -1) alarmB = true;
                motorOn = false;
                cycleStarted = false;
            }

            // Verifica se o ciclo foi concluído
            if (!motorOn && direction == 0) {
                currentCycle++;
                if (currentCycle >= numberOfCycles) {
                    completed = true;
                    cycleStarted = false;
                } else {
                    startTime = millis();
                }
            }
        }
    } 

    // Modo Manual
    else {
        // Verifica direção baseada no eixo X
        if (joystickX > 230 && !limitA) {
            direction = 1;
            outA = true;
            outB = false;
        } else if (joystickX < 20 && !limitB) {
            direction = -1;
            outA = false;
            outB = true;
        } else {
            direction = 0;  // Parado
            outA = false;
            outB = false;
        }

        // Verifica direção baseada no eixo Y
        if (joystickY > 230 && !limitA) {
            outA = true;
            outB = false;
        } else if (joystickY < 20 && limitB) {
            outA = false;
            outB = true;
        }
    }

    // Reset de falhas
    if (reset) {
        autoMode = false;
        outA = false;
        outB = false;
        limitA = false;
        limitB = false;
        alarmA = false;
        alarmB = false;
        currentCycle = 0;
        completed = false;
    }

    // Restart do modo automático
    if (restart) {
        if (!limitA) {
            direction = -1;
            cycleStarted = true;
            firstTime = true;
            completed = false;
            autoMode = true;
        } else if (!limitB) {
            direction = 1;
            cycleStarted = true;
            firstTime = true;
            completed = false;
            autoMode = true;
        } else {
            Serial.println("Falha no restart");
            restart = false;
        }
    }

    // Verificação de alarmes
    if (alarmA || alarmB) {
        motorOn = false;
        Serial.println("Sensor atingido");
        direction = 0;
    }
}
