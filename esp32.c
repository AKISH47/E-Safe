// Load Wi-Fi & Temperature sensor library
#include <WiFi.h>
#include <stdlib.h>
#include "DHT.h"
#define DHTPIN 4  //what pin we're connected to
#define DHTTYPE DHT11  // DHT 11 Temperature Sensor
#define ANALOG_IN_PIN 36
DHT dht(DHTPIN, DHTTYPE);// Initialize DHT sensor for normal 16mhz Arduino
int relay_pin = 22;
float adc_voltage = 0.0;// Floats for ADC voltage & Input voltage
float in_voltage = 0.0;
float R1 = 2200.0;// Floats for resistor values in divider (in ohms) - voltage sensor
float R2 = 750000.0;
float ref_voltage = 3.3;// Float for Reference Voltage
int adc_value = 0;// Integer for ADC value
float temp_threshold = 25;//Variables for Temp Sensor and Volt Sensor
float voltage_threshold = 60;
const char* ssid = "abcd"; //Wifi Name & Password
const char* password = "1234567890";
IPAddress local_ip(192, 168, 7, 1);
IPAddress gateway(192, 168, 7, 1);
IPAddress subnet(255, 255, 255, 0);
WiFiServer server(80);// Set web server port number to 80
String header;// Variable to store the HTTP request
String relayState = "off"; // Auxiliar variables to store the current output state
const int relay = 16; // Assign output variables to GPIO pins
const int blue_led = 23;
unsigned long currentTime = millis(); // Current time
unsigned long previousTime = 0;// Previous time
const long timeoutTime = 2000; // Define timeout time in milliseconds 
(example: 2000ms = 2s)
String tempString = "c";

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  Serial.print("Setting AP (Access Point)…");
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  server.begin();
  pinMode(relay, OUTPUT);   
    pinMode(blue_led, OUTPUT);
  digitalWrite(relay, LOW);   // Set outputs to LOW
  digitalWrite(blue_led, LOW);   // Set outputs to LOW
  dht.begin();   //initialize Temp Sensor
}
void webpageLoop() {
  WiFiClient client = server.available();  // Listen for incoming clients
  if (client) {  // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");                                        // print a message out in the serial port
    String currentLine = "";                                 // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {  // if there's bytes to read from the client,
        char c = client.read();  // read a byte, then
        Serial.write(c);         // print it out the serial monitor
        header += c;
        if (c == '\n') {  // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
  if (header.indexOf("GET /relay/on") >= 0) {             // turns the GPIOs on and off
              turnOnRelay();
            } else if (header.indexOf("GET /relay/off") >= 0) {
              turnOffRelay();
            }
            // Display the HTML web page
            client.println("<!DOCTYPE html>");
            client.println("<html><head><meta><link><style>");
            client.println(" html {text-align: center;}");
            client.println(".relayControl { border: none; color: white; padding: 4%; float:middle;margin: 8%;
            width:500px;length:500px}");
            client.println("</style></head>");
            client.println("<body><h1><p style=\"font-size: 200%\">E-Safe</p></h1> ");
            client.println("<hr>");
            client.println("<p style = \"font-size: 50px;\">  Current Temperature is 22.75 </p>");
            client.println("<p style = \"font-size: 50px;\">  Battery is currently charging </p>");
            if (relayState == "off") {
              client.println("  <p><a href=\"/relay/on\"><button  style=\"background-color:green;font-size:500%\"; 
            class=\"relayControl\">TurnRelayON</button></a></p>");
            } else {
              client.println("  <p><a href=\"/relay/off\"><button style=\"background-color: red;font-size:500%\";
            class=\"relayControl\">Turn RelayOFF</button></a></p>");
            }
            client.println("</body></html>");
            client.println();             // The HTTP response ends with another blank line
            break;             // Break out of the while loop
            } else {  // if you got a newline, then clear currentLine
            currentLine = "";
            }
            } else if (c != '\r') {  // if you got anything else but a carriage return character,
            currentLine += c;      // add it to the end of the currentLine
            }
            }
            }

}
    header = ""; // Clear the header variable
    client.stop();// Close the connection
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
void turnOffRelay() {
  digitalWrite(relay,LOW);
  relayState = "off";
  Serial.println("Relay is off");
}
void turnOnRelay() {
  digitalWrite(relay,HIGH);
  relayState = "on";
    Serial.println("Relay is on");
}
void tempLoop() {
  adc_value = analogRead(ANALOG_IN_PIN);
  Serial.println("Analog Reading is");
  Serial.println(adc_value);
  adc_voltage = (adc_value * ref_voltage) / 4096.0;// Determine voltage at ADC input
  in_voltage = adc_voltage / (R2 / (R1 + R2)); // Calculate voltage at divider input
  Serial.print("Input Voltage = ");// Print results to Serial Monitor to 2 decimal places
  Serial.println(in_voltage, 2);
  delay(500);// Short delay
  float t = dht.readTemperature();// Read temperature as Celsius
  float c = dht.readTemperature(true);
  float value = dht.computeHeatIndex(c);// Compute heat index
  Serial.println(t);
  delay(100);
  // if temp is greater than 30c and if voltage is greater than 25 turn off the circuit
  // we are testing with smaller 7.2v battery right now
  if (in_voltage >= voltage_threshold || t >= temp_threshold) {
    turnOffRelay();
  }

void loop() {
  webpageLoop();
  tempLoop();
}

