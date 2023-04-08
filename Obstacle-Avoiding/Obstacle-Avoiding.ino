// Define os pinos dos motores
#define LEFT_MOTOR_BACKWARD 10
#define LEFT_MOTOR_FORWARD 11
#define RIGHT_MOTOR_BACKWARD 12
#define RIGHT_MOTOR_FORWARD 13

// Define os pinos do sensor ultrassônico
//O módulo HC-SR04 requer um sinal PWM para disparar o pulso ultrassônico e medir a distância.
//No Arduino Nano, as portas analógicas que suportam PWM são: A0, A1, A2, A3, A4, A5. Essas portas podem ser utilizadas para controlar o HC-SR04.
#define TRIGGER_PIN A4
#define ECHO_PIN A5
// Define a distância mínima para o robô desviar de obstáculos (em centímetros)
const int MIN_DISTANCE = 15;

void setup() {
  // Define os pinos como saída
  pinMode(LEFT_MOTOR_FORWARD, OUTPUT
  );
  pinMode(LEFT_MOTOR_BACKWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_BACKWARD, OUTPUT);

  // Define os pinos do sensor ultrassônico como entrada
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Inicializa a comunicação serial
  Serial.begin(9600);
}

void loop() {
  // Mede a distância do objeto mais próximo
  long distance = measureDistance();

  // Verifica se há obstáculos próximos
  if (distance < MIN_DISTANCE) {
    // Desvia do obstáculo
    moveBackward();
    delay(300);
    turnRight();
    delay(250);

  } else {
    // Move para frente
    moveForward2();
  }

  // Imprime a distância medida no monitor serial
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}


void moveForward2() {
  moveForward();
  delay(10);
  stopMotors();
  delay(1);
}

void stopMotors() {
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
}

void moveForward() {
  digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
}

void moveBackward() {
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(LEFT_MOTOR_BACKWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, HIGH);
}

void turnLeft() {
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(LEFT_MOTOR_BACKWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
}

void turnRight() {
  digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, HIGH);
}


/*
O número 58 usado no cálculo da distância é uma constante que representa a velocidade do som em centímetros por microssegundo. O som viaja a uma velocidade aproximada de 343 metros por segundo (m/s) a uma temperatura de 20 graus Celsius. Isso equivale a cerca de 0,0343 centímetros por microssegundo.

Como o sensor HC-SR04 mede o tempo de ida e volta do som, precisamos dividir esse tempo por dois para obter o tempo de ida apenas. Depois disso, basta multiplicar o tempo de ida por 0,0343 para obter a distância em centímetros. No entanto, como o sensor não é perfeito e há outros fatores que podem afetar a velocidade do som, um fator de conversão comumente usado é de 58, que é aproximadamente 0,0343 multiplicado por 2.

Então, para converter o tempo de viagem do som em centímetros, dividimos o tempo por 58. Por exemplo, se o tempo de viagem do som for de 580 microssegundos, a distância seria calculada como 580 / 58 = 10 cm.

É importante lembrar que a velocidade do som varia de acordo com a temperatura e a umidade, portanto, esse fator de conversão pode não ser preciso em todas as condições ambientais. Em aplicações que exigem maior precisão, é necessário ajustar o fator de conversão com base nas condições específicas do ambiente.
*/


long measureDistance() {
  long duration, distance;
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration / 58;
  return distance;
}





