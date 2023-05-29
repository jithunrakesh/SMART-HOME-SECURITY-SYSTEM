// Libraries for ESP32-CAM and sensors

#define BLYNK_PRINT Serial

#include <WiFi.h>

#include <WiFiClient.h>

#include <BlynkSimpleEsp32.h>

#define trigPin 5

#define echoPin 18

#define pirPin 2

#define buzzerPin 4

char auth[] = "AUTH-TOKEN";

char ssid[] = "RIT";

char pass[] = "";

BlynkTimer timer;

void setup()

{

  pinMode(trigPin, OUTPUT);

  pinMode(echoPin, INPUT);

  pinMode(pirPin, INPUT);

  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  timer.setInterval(1000L, sendSensor);

}

void loop()

{

  Blynk.run();

  timer.run();

}

void sendSensor()

{

  digitalWrite(trigPin, LOW);

  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  int distance = duration * 0.034 / 2;

  Serial.print("Distance = ");

  Serial.println(distance);

  if (distance <= 5)

  {

    Blynk.virtualWrite(V0, 1); // Set V0 to 1 to indicate the presence of an intruder

    if (digitalRead(pirPin) == HIGH) {

      Serial.println("Intruder detected!");

      digitalWrite(buzzerPin, HIGH); // Turn on buzzer

    } else {

      digitalWrite(buzzerPin, LOW); // Turn off buzzer

    }

  }

  else

  {

    Blynk.virtualWrite(V0, 0); // Set V0 to 0 if no intruder is detected

  }

}
