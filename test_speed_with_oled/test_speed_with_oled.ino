#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>


const char* ssid      = "Fiki Fahrizal";
const char* password  = "16091996";
const char* host      = "192.168.100.8";// localhost 

const char* remote_host = "www.google.com";

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7);

String avg_time_ms;
String max_time_ms;
String min_time_ms;
int i,r,s;

void setup() {
  Serial.begin(115200);
  delay(10);
  lcd.begin (20,4); 
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  
  Serial.println();
  Serial.println("Connecting to WiFi");
  //Serial.println(ESP.getCpuFreqMHz());
  lcd.setCursor ( 0, 0 );
  lcd.print("Connecting to Wifi"); 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("WiFi connected with ip ");  // Just for troubleshot purpose.
  lcd.setCursor (0,1);
  lcd.print(WiFi.SSID());
  Serial.println(WiFi.localIP());
//  Serial.println(WiFi.RSSI(network));
  lcd.setCursor(0,2);
  lcd.print(WiFi.localIP());
  Serial.print("Pinging host ");
  Serial.println(remote_host);
  
}

void loop() {
    long rssi = WiFi.RSSI();
    lcd.noDisplay();
    delay(200);
    lcd.display();
    delay(200);
    lcd.clear();


    Serial.print("connecting to ");
    Serial.println(host);
  
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
    }


    
    if(Ping.ping(remote_host)) 
    {
    Ping.ping(remote_host, 10);  //10 time ping to google, You can change value to higher or lower
    i= Ping.averageTime();
    avg_time_ms = Ping.averageTime(); // reading string and Int for easy display integration.
    r=Ping.maxTime();
    max_time_ms= Ping.maxTime();
    s=Ping.minTime();
    min_time_ms=Ping.minTime();
    Serial.println(i);
    Serial.println(r);
    Serial.println(s);

  if (i < 99)
 {
  Serial.println("GOOD");
  lcd.setCursor(0,0);
  lcd.print("pingtime");
  lcd.setCursor(10,0);
  lcd.print(rssi);
  lcd.setCursor(0,1);
  lcd.print(avg_time_ms+"ms");
  lcd.setCursor(0,2);
  lcd.print("Internet condition");
  lcd.setCursor(0,3);
  lcd.print("Good");
 }
  if (i > 100 && i < 199)
 {
  Serial.println("bad"); 
  lcd.setCursor(0,0);
  lcd.print("pingtime");
  lcd.setCursor(0,1);
  lcd.print(avg_time_ms+"ms");
  lcd.setCursor(0,2);
  lcd.print("Internet condition");
  lcd.setCursor(0,3);
  lcd.print("Bad");
 }
    } 
    
    else 
    {
    Serial.println("Error :(");
    lcd.setCursor(0,1);
    lcd.print("Internet condition");
    lcd.setCursor(0,2);
    lcd.print("Offline");
    }

  
 
  String url = "/wifi/add.php?";
  url += "pingtime=";
  url +=i ;
 
  Serial.print("Requesting URL: ");
  Serial.println(url);
 
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
 
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
 
  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    if (line.indexOf("sukses gaes") != -1) {
      Serial.println("Yes, data masuk");
    } else if (line.indexOf("gagal gaes") != -1) {
      Serial.println("Maaf, data gagal masuk");
      
    }
  }
  Serial.println("closing connection");
  
  delay(10000);  // Every minutes
  lcd.clear();
}
