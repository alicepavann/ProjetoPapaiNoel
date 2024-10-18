//FUNÇÃO MOVER CINTURA

#define MOTOR_CINTURA_PIN 5  // Pino do motor que move a cintura
#define SENSOR_ESQ_PIN 6  // Pino do sensor de limite à esquerda
#define SENSOR_DIR_PIN 7  // Pino do sensor de limite à direita

int motorVeloc = 255;  // Velocidade máxima do motor (0-255)
int motorDirecao= 1;  // 1 para direita, -1 para esquerda

void setup() {
  Serial.begin(115200);
  pinMode(MOTOR_CINTURA_PIN, OUTPUT);
  pinMode(SENSOR_ESQ_PIN, INPUT);
  pinMode(SENSOR_DIR_PIN, INPUT);
  ///////////////////////////////
  pinMode(MOTOR_BRACO_PIN, OUTPUT);
  pinMode(SENSOR_MAX_PIN, INPUT);
  pinMode(SENSOR_MIN_PIN, INPUT);
  ///////////////////////////////
  pinMode(MOTOR_CABECA_PIN, OUTPUT);
  pinMode(SENSOR_CESQ_PIN, INPUT);
  pinMode(SENSOR_CDIR_PIN, INPUT);
  ////////////////////////////////

}
void loop(){
  Movimento_Cintura();
  Movimento_Braco();
  Movimento_Cabeca();
}
void Movimento_Cintura() {
  // Verifica se o sensor esquerdo foi acionado
  if (digitalRead(SENSOR_ESQ_PIN) == HIGH) {
    Serial.println("Sensor Esquerdo acionado. Girando para a direita.");
    motorDirecao = 1;  // Muda a direção para a direita
  }

  // Verifica se o sensor direito foi acionado
  if (digitalRead(SENSOR_DIR_PIN) == HIGH) {
    Serial.println("Sensor Direito acionado. Parando no centro.");
    motorDirecao = 0;  // Para o motor (centro)
  }

  // Controle do motor
  if (motorDirecao == 1) {
    analogWrite(MOTOR_PIN, motorVeloc);  // Gira para a direita
  } else if (motorDirecao == -1) {
    analogWrite(MOTOR_PIN, -motorVeloc);  // Gira para a esquerda
  } else {
    analogWrite(MOTOR_PIN, 0);  // Para o motor
  }

  delay(100);  // Pequeno atraso para estabilidade
}

//FUNÇÃO MOVIMENTAÇÃO DO BRAÇO
#define MOTOR_BRACO_PIN 8  // Pino do motor que move o braço
#define SENSOR_MAX_PIN 9  // Pino do sensor de limite altura máxima
#define SENSOR_MIN_PIN 10  // Pino do sensor de limite altura mínima

int motorVeloc1 = 255;  // Velocidade máxima do motor (0-255)
int motorDirecao1= 1;  // 1 para cima, -1 para baixo

void Movimento_Braco(){

  if (digitalRead(SENSOR_MAX_PIN) == HIGH) {
    Serial.println("Sensor altura máxima acionado. Descendo braço.");
    motorDirecao = 1;  // Muda a direção para baixo
  }

  // Verifica se o sensor altura minima foi acionado
  if (digitalRead(SENSOR_MIN_PIN) == HIGH) {
    Serial.println("Sensor altura minima acionado. Parando no centro.");
    motorDirecao = 0;  // Para o motor (centro)
  }

  // Controle do motor
  if (motorDirecao == 1) {
    analogWrite(MOTOR_PIN, motorVeloc1);  // Eleva até altura máxima
  } else if (motorDirecao == -1) {
    analogWrite(MOTOR_PIN, -motorVeloc1);  // Abaixa ao máximo
  } else {
    analogWrite(MOTOR_PIN, 0);  // Para o motor
  }

  delay(100);  // Pequeno atraso para estabilidade
}



int motorVeloc2 = 150;  // Velocidade máxima do motor (0-255)
int motorDirecao2= 1;  // 1 para cima, -1 para baixo

void Movimento_Cabeca() {
  // Verifica se o sensor esquerdo foi acionado
  if (digitalRead(SENSOR_CESQ_PIN) == HIGH) {
    Serial.println("Sensor Esquerdo acionado. Girando para a direita.");
    motorDirecao2 = 1;  // Muda a direção para a direita
  }

  // Verifica se o sensor direito foi acionado
  if (digitalRead(SENSOR_CDIR_PIN) == HIGH) {
    Serial.println("Sensor Direito acionado. Parando no centro.");
    motorDirecao2 = 0;  // Para o motor (centro)
  }

  // Controle do motor
  if (motorDirecao2 == 1) {
    analogWrite(MOTOR_CABECA_PIN, motorVeloc2);  // Gira para a direita
  } else if (motorDirecao2 == -1) {
    analogWrite(MOTOR_CABECA_PIN, -motorVeloc2);  // Gira para a esquerda
  } else {
    analogWrite(MOTOR_CABECA_PIN, 0);  // Para o motor
  }

  delay(100);  // Pequeno atraso para estabilidade
}




