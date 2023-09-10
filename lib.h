class Motor {
private:
  int pin1; // Пин для подключения клемы 1 мотора
  int pin2; // Пин для подключения клемы 2 мотора
public:
  // Конструктор класса
  Motor(int pin1, int pin2) {
    this->pin1 = pin1;
    this->pin2 = pin2;
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
  }

  // Метод для движения мотора вперед
void forward(int speed) {
    analogWrite(pin1, speed); // Устанавливаем скорость на пине pin1
    digitalWrite(pin2, LOW);  // Устанавливаем другой пин в LOW
}


  // Метод для движения мотора назад
  void backward(int speed) {
    digitalWrite(pin1, LOW);
    analogWrite(pin2, speed);
  }
  // Метод для остановки мотора
  void stop() {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
  }
}


// для ультра соника
class Ultrasonic {
private:
  int triggerPin; // Пин для отправки ультразвукового сигнала (TRIG)
  int echoPin;    // Пин для приёма отражённого сигнала (ECHO)

public:
  // Конструктор класса
  Ultrasonic(int triggerPin, int echoPin) {
    this->triggerPin = triggerPin;
    this->echoPin = echoPin;
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
  }

  // Метод для измерения расстояния
  float getDistance() {
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    unsigned long duration = pulseIn(echoPin, HIGH);
    // Скорость звука приближенно 343 м/с в воздухе
    // Расстояние = (Время * Скорость) / 2
    float distance = (duration * 0.0343) / 2;
    return distance; // в cm
  }
};



