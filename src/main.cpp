// C++ code
//
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <PubSubClient.h>

int sensorState = 0;
int sensorPin = 5;
int ledPin = 4;
char ssid[] = "ONEPLUS_co_apkqta"; //  le nom du reseau WIFI
char password[] = "12345678";      // le mot de passe WIFI
//mqtt server
char mqtt_server[] = "192.168.97.166"; //adresse IP serveur
#define MQTT_USER ""
#define MQTT_PASS ""

WiFiClient espClient;
PubSubClient MQTTclient(espClient);

//Fonctions mqtt
void MQTTsend(String ans)
{
  static int cpt = 0;
  cpt++;
  String reponse = ans + (String)cpt + "ème fois";
  MQTTclient.publish("/epsi-demo/mon-capteur/temperature", reponse.c_str());
}

void MQTTconnect()
{

  while (!MQTTclient.connected())
  {
    Serial.print("Attente  MQTT connection...");
    String clientId = "TestClient-";
    clientId += String(random(0xffff), HEX);

    // test connexion
    if (MQTTclient.connect(clientId.c_str(), "", ""))
    {
      Serial.println("connected");
    }
    else
    { // si echec affichage erreur
      Serial.print("ECHEC, rc=");
      Serial.print(MQTTclient.state());
      Serial.println(" nouvelle tentative dans 5 secondes");
      delay(5000);
    }
  }
}

void MQTTcallback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message MQTT [");
  Serial.print(topic);
  Serial.print("] ");

  payload[length] = '\0';
  String s = String((char *)payload);

  Serial.println("message reçu : " + s);
}

void setup()
{
  WiFi.begin(ssid, password);
  Serial.println("");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");
  MQTTclient.setServer(mqtt_server, 1883);

  MQTTclient.setCallback(MQTTcallback);

  pinMode(sensorPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(4<, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  // read the state of the sensor/digital input
  static uint32_t lastTimeMqtt = 0;
  String str = "MOUVEMENT DETECTE POUR LA ";
  if (!MQTTclient.connected())
  {
    MQTTconnect();
  }
  MQTTclient.loop();
  sensorState = digitalRead(sensorPin);
  // check if sensor pin is HIGH. if it is, set the
  // LED on.
  // Serial.println(sensorState);
  if (sensorState == HIGH)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    MQTTsend(str);
    // Serial.println("Sensor activated!");
    digitalWrite(ledPin, HIGH);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(ledPin, LOW);
  }
  delay(5000); // Delay a little bit to improve simulation performance
  // connect serveur MQTT
}