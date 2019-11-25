
#include "Arduino.h"
#include "TemperatureSensor.h"
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "List.h"

const char * ssid = "CROCS_NETWORK";
const char * pass = "NOTAVLAD";

List<TemperatureSensor*> sensors = List<TemperatureSensor*>();

String header;
AsyncWebServer server(80);

void storeSensorValue(String mac, float temp)
{
    TemperatureSensor * sensor = nullptr;
    for(int i = 0; i < sensors.size(); i++)
    {
        if(sensors[i]->getMAC() == mac)
        {
            sensor = sensors[i];
        }
    }

    if(sensor == nullptr)
    {
        sensor = new TemperatureSensor(mac);
        sensors.add(sensor);
    }

    if(sensor != nullptr)
    {
        sensor->setTemp(temp);
    }
}

void setup()
{
    Serial.begin(115200);
    
    Serial.println("STARTED");
    Serial.println("Setting AP...");
    WiFi.softAP(ssid, pass);
    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP: ");
    Serial.println(IP);

    server.on("/sendtemp", HTTP_GET, [](AsyncWebServerRequest * request)
    {
        storeSensorValue(request->getParam(0)->value(), request->getParam(1)->value().toFloat());
        Serial.println("/sendtemp");
        request->send(200, "text/plain", "message received");
    });
    server.on("/", HTTP_GET, [](AsyncWebServerRequest * request)
    {
        String data = "<html><head><script> function getData() { var xmlHttp = new XMLHttpRequest(); xmlHttp.open(\"GET\", \"http://192.168.4.1/getdata\", false); xmlHttp.send(null); return xmlHttp.responseText; }</script></head><body><button onclick=alert(getData())>Get Data</button></body></html>";
        request->send(200, "text/html", data);
    });

    server.on("/getdata",HTTP_GET, [](AsyncWebServerRequest * request)
    {
        String data = "Current data:\r\n";
        for(int i = 0; i < sensors.size(); i++)
        {
            if(sensors[i] != nullptr)
            {
                data += sensors[i]->getMAC();
                data += ": ";
                data += sensors[i]->getTemp();
                data += "\r\n";
            }
        }
        request->send(200, "text/plain", data);
    });

    server.begin();
}

void loop()
{
    
    /*WiFiClient client = server.available();
    if(client)
    {
        Serial.println("New client");
        String currentLine = "";
        
        while (client.connected()) {            // loop while the client's connected
        if (client.available())
        {             // if there's bytes to read from the client,
            char c = client.read();             // read a byte, then
            Serial.write(c);                    // print it out the serial monitor
            header += c;
            if (c == '\n') 
            {                    // if the byte is a newline character
                // if the current line is blank, you got two newline characters in a row.
                // that's the end of the client HTTP request, so send a response:
                if (currentLine.length() == 0) {
                    // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
                    // and a content-type so the client knows what's coming, then a blank line:
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-type:text/html");
                    client.println("Connection: close");
                    client.println();
                    client.println("OK");   
                    // The HTTP response ends with another blank line
                    client.println();
                    // Break out of the while loop
                    break;
                } 
                else
                { // if you got a newline, then clear currentLine
                    currentLine = "";
                }
            }
            else if (c != '\r')
            {  // if you got anything else but a carriage return character,
                currentLine += c;      // add it to the end of the currentLine
            }
        }
        }
        // Clear the header variable
        header = "";
        // Close the connection
        client.stop();
        Serial.println("Client disconnected.");
        Serial.println("");
    }*/
}