#include <ArduinoJson.h>
#include <ArduinoJson.hpp>



#include <Arduino.h>

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <WiFi.h>
#include <SpotifyEsp32.h>
#include <SPI.h>

// LCD pins
#define TFT_CS 1
#define TFT_RST 2
#define TFT_DC 3
#define TFT_SCLK 4
#define TFT_MOSI 5

// Encoder pins
#define ENC_CLK 9
#define ENC_DT  10

// Button pins
#define BTN_REWIND 6
#define BTN_PLAY   7
#define BTN_SKIP   8

// Encoder volume
int volume = 50;          // starting volume
int lastCLK;

// Button states
bool lastRewindState = HIGH;
bool lastPlayState = HIGH;
bool lastSkipState = HIGH;

char* SSID = "YOUR WIFI SSID";
const char* PASSWORD = "YOUR WIFI PASSWORD";
const char* CLIENT_ID = "5987d8be69064b48a204fdb42516316b";
const char* CLIENT_SECRET = "d90cbfab4ef645629a9aa3538cef210c";

String lastArtist;
String lastTrackname;

Spotify sp(CLIENT_ID, CLIENT_SECRET);
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

    tft.initR(INITR_BLACKTAB); // the type of screen
    tft.setRotation(1); // this makes the screen landscape! remove this line for portrait
    Serial.println("TFT Initialized!");
    tft.fillScreen(ST77XX_BLACK); // make sure there is nothing in the buffer

    WiFi.begin(SSID, PASSWORD);
    Serial.print("Connecting to WiFi...");
    while(WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
    }
    Serial.printf("\nConnected!\n");

    tft.setCursor(0,0); // make the cursor at the top left
    tft.write(WiFi.localIP().toString().c_str()); // print out IP on the screen

    sp.begin();
    while(!sp.is_auth()){
        sp.handle_client();
    }
    Serial.println("Authenticated");

    pinMode(ENC_CLK, INPUT_PULLUP);
pinMode(ENC_DT, INPUT_PULLUP);

lastCLK = digitalRead(ENC_CLK);

pinMode(BTN_REWIND, INPUT_PULLUP);
pinMode(BTN_PLAY, INPUT_PULLUP);
pinMode(BTN_SKIP, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  String currentArtist = sp.current_artist_names();
    String currentTrackname = sp.current_track_name();

    if (lastArtist != currentArtist && currentArtist != "Something went wrong" && !currentArtist.isEmpty()) {
        tft.fillScreen(ST77XX_BLACK);
        lastArtist = currentArtist;
        Serial.println("Artist: " + lastArtist);
        tft.setCursor(10,10);
        tft.write(lastArtist.c_str());
    }

    if (lastTrackname != currentTrackname && currentTrackname != "Something went wrong" && currentTrackname != "null") {
        lastTrackname = currentTrackname;
        Serial.println("Track: " + lastTrackname);
        tft.setCursor(10,40);
        tft.write(lastTrackname.c_str());
    }

// Encoder
    int currentCLK = digitalRead(ENC_CLK);

if (currentCLK != lastCLK) {

    if (digitalRead(ENC_DT) != currentCLK) {
        volume += 2;     // clockwise
    } else {
        volume -= 2;     // counter clockwise
    }

    volume = constrain(volume, 0, 100);

    sp.set_volume(volume);

    Serial.print("Volume: ");
    Serial.println(volume);

    lastCLK = currentCLK;
    
}
tft.fillRect(0, 70, 160, 20, ST77XX_BLACK);
tft.setCursor(10,70);
tft.print("Volume: ");
tft.print(volume);

// Buttons
bool rewindState = digitalRead(BTN_REWIND);
bool playState = digitalRead(BTN_PLAY);
bool skipState = digitalRead(BTN_SKIP);

// REWIND (previous track / restart)
if (rewindState == LOW && lastRewindState == HIGH) {
    Serial.println("Previous Track");
    sp.previous();
}

// PLAY / PAUSE
if (playState == LOW && lastPlayState == HIGH) {
    Serial.println("Play/Pause");
    
   sp.start_resume_playback();
}

// SKIP
if (skipState == LOW && lastSkipState == HIGH) {
    Serial.println("Next Track");
 sp.skip(); 
}

lastRewindState = rewindState;
lastPlayState = playState;
lastSkipState = skipState;
    delay(500);
}
