#define INTERFACE_INTERVAL 200

int interface_input = 0;
long long interface_last_read = 0;

void interface_setup() {
  
}

void interface_loop() {
  int v = analogRead(A0);

  if(v != interface_input) {
    if(millis() - INTERFACE_INTERVAL > interface_last_read) {
      interface_input = v;
      interface_last_read = millis();

      if(config_publish) {
        mqtt_client.publish(config_publish_topic, String(v));
        display_touch_a();
      }
    }
  }
}
