#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>

//wifi credentials  
char wifi_name[] = "Sarang";    //  network wifi_name (name)
char password[] = "45678910";    //  network password 

int Led = 13;

WiFiClient customer;
MqttClient mqttClient(customer);

const char dealer[] = "mqtt-dashboard.com";
int        port     = 1883;
const char subject[]  = "SIT210/waves";

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  pinMode(Led, OUTPUT);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // attempt to connect to WiFi network:
  Serial.print("Attempting to connect to WPA wifi_name: ");
  Serial.println(wifi_name);
  while (WiFi.begin(wifi_name, password) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

  Serial.println("You're connected to the network");
  Serial.println();

  

  Serial.print("Attempting to connect to the MQTT dealer: ");
  Serial.println(dealer);

  if (!mqttClient.connect(dealer, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT dealer!");
  Serial.println();

  Serial.print("Subscribing to subject: ");
  Serial.println(subject);
  Serial.println();

  // subscribe to a subject
  mqttClient.subscribe(subject);

  // subjects can be unsubscribed using:
  // mqttClient.unsubscribe(subject);

  Serial.print("Waiting for messages on subject: ");
  Serial.println(subject);
  Serial.println();
}

void loop() {
  int Msize = mqttClient.parseMessage();
  if (Msize) {
    // we received a message, print out the subject and contents
    Serial.print("Received a message with subject '");
    Serial.print(mqttClient.messageTopic());
    Serial.print("', length ");
    Serial.print(Msize);
    Serial.println(" bytes:");

    // use the Stream interface to print the contents
    while (mqttClient.available()) {
      Serial.print((char)mqttClient.read());
    }
    Serial.println();
    digitalWrite(Led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(200);                       // wait for a second
    digitalWrite(Led, LOW);    // turn the LED off by making the voltage LOW
    delay(200);
    digitalWrite(Led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(200);                       // wait for a second
    digitalWrite(Led, LOW);    // turn the LED off by making the voltage LOW
    delay(200);
    digitalWrite(Led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(200);                       // wait for a second
    digitalWrite(Led, LOW);    // turn the LED off by making the voltage LOW
    delay(200);

    Serial.println();
  }
}