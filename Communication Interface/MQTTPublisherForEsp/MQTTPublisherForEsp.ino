#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <WiFiEspUdp.h>
#include "SoftwareSerial.h"
#include <PubSubClient.h>

#define ESP_SSID                                      "twguest"
#define ESP_PASS                                      "crimson trout rewrite trustable ivy"

#define mqtt_server                                   "10.71.124.85"
#define mqtt_port                                     1883
#define mqtt_client_id                                "ESP"
#define mqtt_client_topic_send_status                 "mqtt/arduino/status"
#define mqtt_client_topic_send_message                "mqtt/arduino/send/message"
#define mqtt_client_topic_receive_led                 "users/L"
#define birthMsg                                      "Arduino Client connected"
#define willMsg                                       "Arduino Client disconnected"

#define LEDpin 13

String messageStr; 
char message[50];

long lastMsg = 0;
long lastLoop = 0;

int status = WL_IDLE_STATUS; // the Wifi radio's status

WiFiEspClient espClient;

//print any message received for subscribed topic
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  if((char)payload[0] == '1') {
    Serial.println("LED is on");
    digitalWrite(LEDpin, HIGH);
  } else if ((char)payload[0] == '0'){
    Serial.println("LED is off");
    digitalWrite(LEDpin, LOW);
  }
}

PubSubClient client(mqtt_server, mqtt_port, callback, espClient);

SoftwareSerial soft(6, 7); // RX, TX

void setup() {
  // initialize serial for debugging
  Serial.begin(9600);
  // initialize serial for ESP module
  soft.begin(9600);
  // initialize ESP module
  WiFi.init(&soft);

  pinMode(LEDpin, OUTPUT);
 
  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ESP_SSID);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ESP_SSID, ESP_PASS);
  }

  // you're connected now, so print out the data
  Serial.println("You're connected to the network"); 
}

void sendData() {
  messageStr = "Hola"; 
  messageStr.toCharArray(message, messageStr.length() + 1); 
  Serial.print("Sending Message: ");
  Serial.println(message);
  
  client.publish(mqtt_client_topic_send_message, message);
}

void loop() {

  long now = millis(); 

  if (now - lastMsg > 15000) {
    lastMsg = now;
    sendData();
  } 
 
  if (now - lastLoop > 200) {
    lastLoop = now;
    if (!client.connected()) {
      reconnect();
    }
    client.loop();
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect, just a name to identify the client
    if (client.connect(mqtt_client_id, mqtt_client_topic_send_status, 1, 1, willMsg)) {
      Serial.println("connected");
      client.publish(mqtt_client_topic_send_status, birthMsg);
      Serial.println(client.subscribe(mqtt_client_topic_receive_led));
 
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
