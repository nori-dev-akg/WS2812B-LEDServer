#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <uri/UriBraces.h>
#include <uri/UriRegex.h>
#include "TwinkleFox.h"

#define WIFI_SSID "(your ssid)"          // change your setting
#define WIFI_PASSWORD "(ssid password)"  // change your setting

const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;

ESP8266WebServer server(80);

const IPAddress ip = IPAddress(192, 168, 0, 213); // change your setting
const IPAddress gw = IPAddress(192, 168, 0, 1);   // change your setting
const IPAddress sm = IPAddress(255, 255, 255, 0); // change your setting

static const char xyz[] PROGMEM =
    "<!DOCTYPE html>"
    "<html>"
    "<head>"
    "<meta charset=\"UTF-8\">"
    "<title>TwinkleFOX Web</title>"
    "<meta name=\"viewport\" content=\"width=device-width,initial-scale=1\">"
    "</head>"
    "<body>"
    "<form method=\"get\" action=\"./\">"
    "<p>Power</p>"
    "<input type=\"submit\" name=\"pw\" value=\"On\">"
    "<input type=\"submit\" name=\"pw\" value=\"Off\">"
    "<p>Custom</p>"
    "<input type=\"submit\" name=\"pt\" value=\"Halloween\">"
    "<input type=\"submit\" name=\"pt\" value=\"Christmas\">"
    "<input type=\"submit\" name=\"pt\" value=\"Sakura\"><br>"
    "<input type=\"submit\" name=\"pt\" value=\"Autumn\"><br>"
    "<p>TwinkleFox</p>"
    "<input type=\"submit\" name=\"pt\" value=\"RetroC9\">"
    "<input type=\"submit\" name=\"pt\" value=\"BlueWhite\">"
    "<input type=\"submit\" name=\"pt\" value=\"RainbowColors\">"
    "<input type=\"submit\" name=\"pt\" value=\"FairyLight\">"
    "<input type=\"submit\" name=\"pt\" value=\"RedGreenWhite\">"
    "<input type=\"submit\" name=\"pt\" value=\"PartyColors\">"
    "<input type=\"submit\" name=\"pt\" value=\"RedWhite\">"
    "<input type=\"submit\" name=\"pt\" value=\"Snow\">"
    "<input type=\"submit\" name=\"pt\" value=\"Holly\">"
    "<input type=\"submit\" name=\"pt\" value=\"Ice\">"
    "</form>"
    " </body>"
    "</html>";

bool power = true;

void handleRoot()
{
  String pw = server.arg("pw");
  if (pw == "On") { power = true; }
  if (pw == "Off") { power = false; powerOff(); }

  String pt = server.arg("pt");
  if (pt == "RetroC9") { chooseColorPalette(RetroC9_p); }
  else if (pt == "BlueWhite") { chooseColorPalette(BlueWhite_p); }
  else if (pt == "RedGreenWhite") { chooseColorPalette(RedGreenWhite_p); }
  else if (pt == "RainbowColors") { chooseColorPalette(RainbowColors_p); }
  else if (pt == "FairyLight") { chooseColorPalette(FairyLight_p); }
  else if (pt == "RedGreenWhite") { chooseColorPalette(RedGreenWhite_p); }
  else if (pt == "PartyColors") { chooseColorPalette(PartyColors_p); }
  else if (pt == "RedWhite") { chooseColorPalette(RedWhite_p); }
  else if (pt == "Snow") { chooseColorPalette(Snow_p); }
  else if (pt == "Holly") { chooseColorPalette(Holly_p); }
  else if (pt == "Ice") { chooseColorPalette(Ice_p); }
  else if (pt == "Halloween") { chooseColorPalette(Halloween_p); }
  else if (pt == "Christmas") { chooseColorPalette(Christmas_p); }
  else if (pt == "Sakura") { chooseColorPalette(Sakura_p); }
  else if (pt == "Autumn") { chooseColorPalette(Autumn_p); }

  server.send(200, "text/html", FPSTR(xyz));
}

void setup(void)
{
  Serial.begin(115200);
  WiFi.config(ip, gw, sm);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266"))
  {
    Serial.println("MDNS responder started");
  }

  server.on(UriRegex("^\\/(.*)$"), handleRoot);

  server.begin();
  Serial.println("HTTP server started");

  setup_TinkleFox();
}

void loop(void)
{
  server.handleClient();
  MDNS.update();

  if (power)
  {
    loop_TinkleFox();
  }
}
