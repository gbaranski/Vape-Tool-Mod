#ifndef ARDUINO_H
#define ARDUINO_H
#include <Arduino.h>
#endif

#ifndef OUTPUT_H
#define OUTPUT_H
#include "output.h"
#endif

#include <ArduinoJson.h>

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

const char *ssid = "Nigeria";
const char *password = "hondamsx125";

const char *PARAM_MESSAGE = "message";

void handleNotFound(AsyncWebServerRequest *request)
{
    request->send(404, "text/plain", "Not found");
}

void setupWifiAndServer()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Serial.printf("WiFi Failed!\n");
        return;
    }

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", String(getPwm()));
    });

    server.on("/getData", HTTP_GET, [](AsyncWebServerRequest *request) {
        StaticJsonDocument<200> data;
        String serializedData;
        data["pwmValue"] = getPwm();
        serializeJsonPretty(data, serializedData);

        request->send(200, "application/json", serializedData);
    });

    server.on("/setPWM", HTTP_GET, [](AsyncWebServerRequest *request) {
        String newPWM;
        if (request->hasParam("pwm"))
        {

            newPWM = request->getParam("pwm")->value();
            setPwm(uint32_t(newPWM.toInt()));
            request->send(200, "text/plain", "SET TO");
        }
        else
        {
            request->send(400, "text/plain", "NO PWM PARAM");
        }
    });

    server.onNotFound(handleNotFound);

    server.begin();
}