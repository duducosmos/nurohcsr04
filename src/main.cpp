#include <Arduino.h>
#include "model_data.h"
#include "NeuralNetwork.h"

NeuralNetwork *nn;

const int trigPin = 4; //D4
const int echoPin = 2; //D3

long duration;

void neuralf();
void gen_data();
int get_duration();

void setup()
{
  Serial.begin(9600);
  nn = new NeuralNetwork(hcsr04_1_tflite);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{
  neuralf();
}

int get_duration()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  return duration;
}

void gen_data()
{
  Serial.println(get_duration());
  delay(500);
}

void neuralf()
{

  int duration = get_duration();


  nn->getInputBuffer()[0] = duration;

  float predicted = nn->predict();

  float dist = duration * 0.343 / 2;

  Serial.printf("Pred %.2f Calculated %.2f \n", predicted, dist);

  delay(1000);
}