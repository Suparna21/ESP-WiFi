#include <WiFi.h>

void esp_ap(void);
void wifi_mode(void);

unsigned long wifi_connect_time = millis();

void setup(){
  Serial.begin(9600);

  WiFi.persistent(false);        // Do NOT allow automatic WiFi NVS writes
  WiFi.disconnect(true, true);   // Clear old saved WiFi data
  
  esp_ap();
  wifi_mode();

  delay(10000);

  esp_sta();
  wifi_mode();
}


void loop(){
  

}


//This function helps to set ESP as access point
void esp_sta(){
  const char* ssid = "SSID";
  const char* password = "password";

  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED && (millis() - wifi_connect_time < 5000)){
    Serial.print(".");
    delay(500);
  }
  if(WiFi.status() == WL_CONNECTED){
    Serial.println("Connected to wifi");
  }
  else if(WiFi.status() != WL_CONNECTED){
    Serial.println("Not connected to wifi");
  }
}


//This function helps to set ESP as access point
void esp_ap(){
  IPAddress ESP_IP;                   //IPAddress is a data type (class) used to store/represent IP addresses
  const char* ssid = "ESP32";
  const char* password = "12345678"; 

  WiFi.softAP(ssid, password);
  ESP_IP = WiFi.softAPIP();
  Serial.print("Local access point IP adress: ");
  Serial.println(ESP_IP);
  delay(1000);
}


//This function helps to check the wifi status of ESP32
void wifi_mode(){
  wifi_mode_t mode = WiFi.getMode();

  switch (mode) {
    case WIFI_OFF:    Serial.println("WIFI_OFF"); break;
    case WIFI_STA:    Serial.println("WIFI_STA"); break;
    case WIFI_AP:     Serial.println("WIFI_AP"); break;
    case WIFI_AP_STA: Serial.println("WIFI_AP_STA"); break;
    default:          Serial.println("UNKNOWN"); break;
  }
}


