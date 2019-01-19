/*
Displays album artwork of currently playing song from your Spotify account.

By: Wes Furuya and Andrew England
SparkFun Electronics
Date: January 7th, 2019

License: This code is public domain but you buy me a beer if you use this and we meet
someday (Beerware license).

This code sets up your ESP32 as a webpage server and loads a 64x64 pixel image from the
Spotify Client API. The ESP32 then decodes the jpg image into an 8-bit color array that
gets displayed on the matrix panel.

This code is written for the SparkFun ESP32 Thing and the 64x64 RGB LED Matrix Panel.
SparkFun sells these at its website: www.sparkfun.com Do you like this library? Help
support SparkFun. Buy a board and panel!
    https://www.sparkfun.com/products/13907
    https://www.sparkfun.com/products/14824

This code is based off the ESP8266 Spotify Remote, written by Thing Pulse:
    https://github.com/ThingPulse/esp8266-spotify-remote/

This code requires several libraries to run:
JPEGDecoder-   https://github.com/Bodmer/JPEGDecoder
PxMatrix-      https://github.com/2dom/PxMatrix
FastLED-       https://github.com/FastLED/FastLED
Adafruit GFX-  https://github.com/adafruit/Adafruit-GFX-Library

Development environment specifics: Arduino IDE 1.8.5

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details. You should have received a copy of
the GNU General Public License along with this program.  If not, see
<http://www.gnu.org/licenses/>.

*/

// Libraries
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <FS.h>
#include <SPIFFS.h>
#include <JPEGDecoder.h>
#include <ESPmDNS.h>
#include "SpotifyClient.h"
#include "settings.h"
#include <FastLED.h>
#include <PxMatrix.h>

// Define Tasks for Cores
TaskHandle_t Task1;
TaskHandle_t Task2;

// Define Output Pins For Matrix Display
#define CLOCK_PIN 14
#define DATA_PIN 13
#define P_LAT 22
#define P_A 19
#define P_B 23
#define P_C 18
#define P_D 5
#define P_E 15
#define P_OE 2
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

// Variables For XY Matrix
const uint16_t kMatrixWidth = 64;
const uint16_t kMatrixHeight = 64;
const bool    kMatrixSerpentineLayout = false;
uint16_t XY(uint16_t x, uint16_t y);

#define double_buffer
PxMATRIX display(64, 64, P_LAT, P_OE, P_A, P_B, P_C, P_D, P_E);

// Variables For FastLED
const uint16_t NUM_LEDS = 4156;
CRGB clockLight[NUM_LEDS];


#define Stringize( L )     #L
#define MakeString( M, L ) M(L)
#define $Line MakeString( Stringize, __LINE__ )
#define Reminder __FILE__ "(" $Line ") : Reminder: "

const char* host = "api.spotify.com";
const int httpsPort = 443;
String currentImageUrl = "";
uint32_t lastDrawingUpdate = 0;
uint16_t counter = 0;
long lastUpdate = 0;
boolean isDownloadingCover = false;
void saveRefreshToken(String refreshToken);
String loadRefreshToken();

uint16_t responseCode = 200;

SpotifyClient client(clientId, clientSecret, redirectUri);
SpotifyData data;
SpotifyAuth auth;


void drawJPEGFromSpiffs(String filename, int xpos, int ypos, DrawingCallback *drawingCallback);



void setup() {
  Serial.begin(115200);
  delay(2000);
  boolean mounted = SPIFFS.begin();

  display.begin(32);
  display.setBrightness(255);

  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(clockLight, NUM_LEDS);

  if (!mounted) {
    SPIFFS.format();
    SPIFFS.begin();
  }

  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  if (!MDNS.begin("esp32")) {             // Start the mDNS responder for esp8266.local
    Serial.println("Error setting up MDNS responder!");
  }
  Serial.println("mDNS responder started");

  String code = "";
  String grantType = "";
  String refreshToken = loadRefreshToken();
  if (refreshToken == "") {
    code = client.startConfigPortal();
    grantType = "authorization_code";
  } else {
    code = refreshToken;
    grantType = "refresh_token";
  }

  client.getToken(&auth, grantType, code);
  Serial.printf("Refresh token: %s\nAccess Token: %s\n", auth.refreshToken.c_str(), auth.accessToken.c_str());
  if (auth.refreshToken != "") {
    saveRefreshToken(auth.refreshToken);
  }

xTaskCreatePinnedToCore(
             Task1code, /* Task function. */
             "Task1",   /* name of task. */
             10000,     /* Stack size of task */
             NULL,      /* parameter of the task */
             0,         /* priority of the task */
             &Task1,    /* Task handle to keep track of created task */
             0);        /* pin task to core 0 */

}

void loop() {
  display.display(15);
}

uint16_t XY( uint16_t x, uint16_t y)
{
  uint16_t i;
  uint16_t reverseX = (kMatrixWidth - 1) - x;
  i = (y * kMatrixWidth) + 7 - (x % kMatrixWidth);
  return i;
}



void saveRefreshToken(String refreshToken) {

  File f = SPIFFS.open("/refreshToken.txt", "w+");
  if (!f) {
    Serial.println("Failed to open config file");
    return;
  }
  f.println(refreshToken);
  f.close();
}

String loadRefreshToken() {
  Serial.println("Loading config");
  File f = SPIFFS.open("/refreshToken.txt", "r");
  if (!f) {
    Serial.println("Failed to open config file");
    return "";
  }
  while (f.available()) {
    //Lets read line by line from the file
    String token = f.readStringUntil('\r');
    Serial.printf("Refresh Token: %s\n", token.c_str());
    f.close();
    return token;
  }
  return "";
}

void drawJPEGFromSpiffs(String filename, int xpos, int ypos) {
  char buffer[filename.length() + 1];
  filename.toCharArray(buffer, filename.length() + 1);
  JpegDec.decodeFsFile(buffer);
  uint16_t mcu_w = JpegDec.MCUWidth;
  uint16_t mcu_h = JpegDec.MCUHeight;
  
  Serial.println("Generating Image...");
  
  while ( JpegDec.read() == 1) {
    uint16_t *pImg;
    pImg = JpegDec.pImage;
    int mcu_x = JpegDec.MCUx * mcu_w;
    int mcu_y = JpegDec.MCUy * mcu_h;
    for (uint16_t y = mcu_y; y < mcu_y + mcu_h; y++) {
      for (uint16_t x = mcu_x; x < mcu_x + mcu_w; x++) {
        uint8_t red = (uint8_t)((((*pImg & 0xF800) >> 11) / 32.0) * 255);
        uint8_t green = (uint8_t)((((*pImg & 0x7E0) >> 6) / 32.0) * 255);
        uint8_t blue = (uint8_t)((((*pImg & 0x1F) / 32.0) * 255));
        
        display.drawPixelRGB888(x, y, red, blue, green);
        *pImg++;
      }
    }
  }
  SPIFFS.remove("/cover.jpg");
}

void Task1code( void * pvParameters ){
  for(;;){
    if (millis() - lastUpdate > 2000) {
      responseCode = client.update(&data, &auth);
      Serial.printf("HREF: %s\n", data.image64Href.c_str());
      lastUpdate = millis();
      if (responseCode == 401) {
        client.getToken(&auth, "refresh_token", auth.refreshToken);
        if (auth.refreshToken != "") {
          saveRefreshToken(auth.refreshToken);
        }
      }
      else if (responseCode == 200) {
        String selectedImageHref = data.image64Href;
        if (selectedImageHref != currentImageUrl) {
          Serial.println("New Image. Downloading it");
          isDownloadingCover = true;
          client.downloadFile(selectedImageHref, "/cover.jpg");
          isDownloadingCover = false;
          currentImageUrl = selectedImageHref;
          drawJPEGFromSpiffs("/cover.jpg", 0, 0);
        }
      }
    }
  }
}
