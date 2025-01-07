void ConnectToWifi() {
  Serial.begin(9600);
  Serial.println();

  WiFi.hostname(wifiHostname);
  WiFi.begin("Lackawaxen", "vpgm1941");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}
