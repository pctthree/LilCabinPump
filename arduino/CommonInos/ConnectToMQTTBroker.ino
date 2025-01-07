void ConnectToMqttBroker() {
   Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);
  // mqttClient.setUsernamePassword("pi", "lilcabinpiNR");
  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();
}
