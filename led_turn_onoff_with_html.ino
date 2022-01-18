#include <ESP8266WiFi.h>

 

const char* ssid = "Zain";    //  Your Wi-Fi Name

const char* password = "12345678";   // Wi-Fi Password

 


int pinF = D0;
int pinB = D1;
int pinR = D2;
int pinL = D3;
char command;
WiFiServer server(80);

// Set your Static IP address
IPAddress local_IP(192, 168, 10, 17);
// Set your Gateway IP address
IPAddress gateway(192, 168, 1, 1);

IPAddress subnet(255, 255, 0, 0);

void setup()

{

  Serial.begin(9600); //Default Baudrate

  pinMode(pinF, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinR, OUTPUT);
  pinMode(pinL, OUTPUT);
  
  digitalWrite(pinF,LOW);
  digitalWrite(pinB,LOW);
  digitalWrite(pinR,LOW);
  digitalWrite(pinL,LOW);
  
  digitalWrite(LED_BUILTIN,HIGH);  
  Serial.print("Connecting to the Newtork");

   WiFi.softAP(ssid, password); //begin WiFi access point
  Serial.println("");

 // while (WiFi.status() != WL_CONNECTED)

  //{

    //delay(500);

    //Serial.print(".");

  //}

  Serial.println("WiFi connected"); 

  server.begin();  // Starts the Server

  Serial.println("Server started");

 

  Serial.print("IP Address of network: "); // will IP address on Serial Monitor

  Serial.println(WiFi.softAPIP());

  Serial.print("Copy and paste the following URL: https://"); // Will print IP address in URL format

  Serial.print(WiFi.localIP());

  Serial.println("/");

}

 

void loop()

{

  WiFiClient client = server.available();

  if (!client)

  {

    return;

  }

  Serial.println("Waiting for new client");

  while(!client.available())

  {

    delay(1);

  }
  // check out what request the client has made
  String request = client.readStringUntil('\r');

  Serial.println(request);

  client.flush();

 

  
  
  if(request.indexOf("/FORWARD") != -1)

  {
     digitalWrite(pinF, HIGH);
     command = 1;
    

  }

  else if(request.indexOf("/BACKWARD") != -1)

  {
     digitalWrite(pinB, HIGH);
     command = 2;
    //value = HIGH;

  }

  else if(request.indexOf("/RIGHT") != -1)

  {
     digitalWrite(pinR, HIGH);
     delay(150);
     digitalWrite(pinR, LOW);
     command = 3;
    //value = HIGH;

  }

  else if(request.indexOf("/LEFT") != -1)

  {
     digitalWrite(pinL, HIGH);
     delay(150);
     digitalWrite(pinL, LOW);
     command = 4;
    //value = HIGH;

  }
  
  else if(request.indexOf("/STOP") != -1)

  {
     digitalWrite(pinR, LOW);
     digitalWrite(pinL, LOW);
     digitalWrite(pinB, LOW);
     digitalWrite(pinF, LOW);
     command = 5;
  }

//*------------------HTML Page Code---------------------*//

 

  client.println("HTTP/1.1 200 OK"); //

  client.println("Content-Type: text/html");

  client.println("");

  client.println("<!DOCTYPE HTML>");

  client.println("<html>");

 

  client.print(" CONTROLLING COMMAND: ");

 

  if(command == 1)

  {

    client.print("MOVE FORWARD");

  }

  else if(command == 2)

  {

    client.print("MOVE BACKWARD");

  }
  else if(command == 3)
  {

    client.print("MOVE RIGHT");

  }
  else if(command == 4)
  {

    client.print("MOVE LEFT");

  }
  else if(command == 5)
  {

    client.print("STOP");

  }

  client.println("<br><br>");

  client.println("<center><a href=\"/FORWARD\"\"><h1>MOVE FORWARD</h1></center></a><br><br>");

  client.println("<center><a href=\"/BACKWARD\"\"><h1>MOVE BACKWARD</h1></a></center><br><br>");
  
  client.println("<center><a href=\"/RIGHT\"\"><h1>TURN RIGHT</h1></a></center><br><br>");

  client.println("<center><a href=\"/LEFT\"\"><h1>TURN LEFT</h1></a></center><br><br>");

   client.println("<center><a href=\"/STOP\"\"><h1>STOP</h1></a></center><br><br>");

  client.println("</html>");

 

  delay(2);

  Serial.println("Client disonnected");

  Serial.println("");

}
