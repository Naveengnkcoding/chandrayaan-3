#include <WiFi.h>
///#include <ESP8266WebServer.h>
#include <ESP32Servo.h>

const char* ssid = "ROVER";
const char* password = "hello123";

/* Put IP Address details */
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

bool red = true;
String gps = "Receiving Temperature";
Servo servo;

#ifdef __cplusplus
extern "C" {
#endif
uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif
uint8_t temprature_sens_read();

WiFiServer server(80);

void handleRoot() {
  Serial.println("Root page called");
  server.send(200, "text/html", SendHTML(red));
}
void handleRight() {
  Serial.println("DOOR ON");
  servo.write(100);
  server.send(200, "text/html", SendHTML(red));

void handleLeft() {
  Serial.println("Door Close");
  servo.write(95);
  server.send(200, "text/html", SendHTML(red));
}
void handleStop() {
  Serial.println("LED ON");
  digitalWrite(33, HIGH);
  server.send(200, "text/html", SendHTML(red));
}

void handleres(){
  Serial.println("LED OFF");
  digitalWrite(33, LOW);
}
  server.send(200, "text/html", SendHTML(red));
}
void setup() {
  Serial.begin(115200);
  servo.attach(36);

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
  
  pinMode(33, OUTPUT);
  pinMode(36, OUTPUT)
  digitalWrite(33, LOW);
  digitalWrite(36 LOW);

  server.on("/", handleRoot);
  server.on("/left", handleLeft);
  server.on("/right", handleRight);
  server.on("/stop", handleStop);
  server.on("/res", handleres);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  Serial.print((temprature_sens_read() - 32) / 1.8);
  gps = (temprature_sens_read() - 32) / 1.8;
  server.handleClient(); 
}

String SendHTML(uint8_t color){
  String ptr ="<!DOCTYPE html><html>\n";
  ptr +="<head><meta name=\'viewport\' content=\'width=device-width, initial-scale=1.0, user-scalable=no\'><meta http-equiv='refresh' content='0.5'>\n";
  ptr +="<title>ROVER CONTROL</title>\n";
  ptr +="<style>*{margin: 0;padding: 0;box-sizing: border-box;font-family: 'Courier New', Courier, monospace;}\n";
  ptr +="a{text-decoration: none;width: 7vw;height: 7vw;display: flex;justify-content: center;align-items: center;background: #111;border-radius: 50%;text-align: center;font-size: 28px;font-weight: 700;color: #fff;}\n";
  ptr +=".t{width: 50%;margin:auto;height: 20vh;padding-top: 5vh;border-radius: 13px;color: #fff;}\n";
  ptr +=".l{margin:2vw;font-weight:none;font-size:18px;text-decoration: underline;height:auto;background: none; color:black;}";
  ptr +="</style></head><body>\n";
  ptr +="<div style='display:inline-flex;width:100%;height: 20vh; text-align: center; float: center;margin-top: 10vh;'><a class='l' href='/sol'>Solar</a>\n";
  ptr +="<div class='t' style='background:orange;'><h2>Chandrayaan 3(Vikram)</h2>"+gps+"</div>\n";
  ptr +="<a class='l' href='/res'>Reset</a></div><div style='display: flex;justify-content: space-around;align-items: center;height: 70vh;'>\n";
  ptr +="<div style='display: flex;gap: 10px;text-align: center;align-items: center;'>\n";
  ptr +="<a href='/left'>&#9664;</a><a href='/stop' id='r'>  &#9632;</a><a href='/right'>&#9654;</a></div>\n";
  ptr +="</div></body></html>\n";
  return ptr;
}
