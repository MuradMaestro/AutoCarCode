#include <Servo.h>

Servo steeringServo; // Ön təkərlər üçün servo
int motorPin1 = 5;   // Motor sürücüsü pinləri
int motorPin2 = 6;
int motorPin3 = 9;
int motorPin4 = 10;
int servoPin = 3;

void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  steeringServo.attach(servoPin); // Servo idarəetmə pini
  steeringServo.write(90);  // Servonu başlanğıc mövqeyə gətir (90° - düz hərəkət)

  Serial.begin(115200); // ESP32-CAM ilə əlaqə üçün
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readString(); // ESP32-CAM-dən məlumatı oxu
    
    if (data == "LEFT") {
      // Sol dönmə
      steeringServo.write(45);  // Sol dönmə üçün servo açısını dəyiş
    } else if (data == "RIGHT") {
      // Sağ dönmə
      steeringServo.write(135); // Sağ dönmə üçün servo açısını dəyiş
    } else if (data == "FORWARD") {
      // İrəli hərəkət
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, HIGH);
      digitalWrite(motorPin4, LOW);
      steeringServo.write(90); // Düz hərəkət üçün
    } else if (data == "STOP") {
      // Dayan
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, LOW);
      digitalWrite(motorPin4, LOW);
    }
  }
}
