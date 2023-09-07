#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>


char wifi_name[] = "Sarang";                      
char password[] = "45678910";  


const int trigPin = 2;
const int echoPin = 3;

float time, space;

WiFiClient customer;
MqttClient mqttClient(customer);

const char dealer[] = "mqtt-dashboard.com";
int port = 1883;
const char subject[] = "SIT210/waves";

const long interval = 1000;
unsigned long old_mills = 0;

int count = 0;

void setup() {

  Serial.begin(9600);
  while (!Serial) {
 
  }

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // waiting for wifi connections
  Serial.print("Attempting to connect to WPA wifi_name: ");
  Serial.println(wifi_name);
  while (WiFi.begin(wifi_name, password) != WL_CONNECTED) {
    // failed, retrying
    Serial.print(".");
    delay(5000);
  }

  Serial.println("You're connected to the network");
  Serial.println();

  Serial.print("Connection in progress: ");
  Serial.println(dealer);

  if (!mqttClient.connect(dealer, port)) {
    Serial.print("Can't connect to MQTT broker: Error code = ");
    Serial.println(mqttClient.connectError());

    while (1)
      ;
  }

  Serial.println("Connection with MQTT dealer secured!");
  Serial.println();
}

void loop() {
  mqttClient.poll();
  unsigned long mills = millis();

  if (mills - old_mills >= interval) {

    old_mills = mills;

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    time = pulseIn(echoPin, HIGH);
    space = (time * .0343) / 2;
    Serial.print("space: ");
    Serial.println(space);
    if (space < 20) {
      
      mqttClient.beginMessage(subject);
      mqttClient.print("space is: ");
      mqttClient.print(space);
      mqttClient.endMessage();
      delay(1000);
    }

    Serial.println();
  }
}