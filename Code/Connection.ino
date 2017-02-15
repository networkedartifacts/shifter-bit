#include <ESP8266WiFi.h>
#include <MQTTClient.h>

WiFiClient wifi_client;
MQTTClient mqtt_client;

void wifi_setup() {
  Serial.print("Joining WiFi...");
  WiFi.begin(config_wifi_ssid, config_wifi_key);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("\nJoined with IP Address: ");  
  Serial.println(WiFi.localIP());
}

void mqtt_setup() {
  mqtt_client.begin(config_mqtt_broker, wifi_client);
  
  Serial.print("Connecting to shiftr.io...");
  while (!mqtt_client.connect(config_mqtt_client_id, config_mqtt_user, config_mqtt_password)) {
    Serial.print(".");
  }

  Serial.println("\nConnected!");

  if(config_subscribe) {
    mqtt_client.subscribe(config_subscribe_topic);
  }
}

void mqtt_loop() {
  mqtt_client.loop();
  delay(10);
}

// predefine function
void display_touch_out();
void output_set(int);

void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
  if(config_subscribe) {
    display_touch_out();
    output_set(payload.toInt());
  }
}