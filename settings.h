// WiFi settings
const char* ssid = "SSID";
const char* password = "Password";

// Spotify settings
String clientId = "Spotify ClientID";
String clientSecret = "Spotify Secret Key";
// These next two lines have to match. A client clientSpotifierHostName makes the
// node listen on http://esp32.local. Spotify needs an exact match of the redirect url
String espotifierNodeName = "esp32";
String redirectUri = "http%3A%2F%2F" + espotifierNodeName + ".local%2Fcallback%2F";

