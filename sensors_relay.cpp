#include "globals.h"

/**
 * @brief (Internal) Parses Tasmota JSON for relay status.
 * Expects payload from "Status 0" or "Status 11".
 * @return true if ON, false if OFF.
 */
static bool parseTasmotaRelayStatus(const String& payload) {
  DynamicJsonDocument doc(1024); // Smaller doc for Status 0
  DeserializationError err = deserializeJson(doc, payload);
  if (err) {
    Serial.printf("❌ [RELAY] JSON parse error: %s\n", err.c_str());
    return false; // Failsafe
  }
  const char* powerSTS = doc["StatusSTS"]["POWER"];
  if (powerSTS) {
    return (strcmp(powerSTS, "ON") == 0);
  }
  const char* powerStatus = doc["Status"]["POWER"];
  if (powerStatus) {
    return (strcmp(powerStatus, "ON") == 0);
  }
  const char* powerRoot = doc["POWER"];
  if (powerRoot) {
    return (strcmp(powerRoot, "ON") == 0);
  }
  Serial.println("❌ [RELAY] Could not find 'POWER' key in JSON response.");
  return false;
}

/**
 * @brief (Internal) Actively queries the Tasmota device for its relay status.
 * @return true if relay is ON, false if OFF or error.
 */
static bool getRelayStatus() {
  if (WiFi.status() != WL_CONNECTED) {
    return false; 
  }
  HTTPClient http;
  http.setTimeout(2000);
  http.setReuse(false);
  String url = String(remoteHost) + "/cm?cmnd=Status%200";
  
  if (http.begin(url)) {
    int code = http.GET();
    if (code == 200) {
      bool status = parseTasmotaRelayStatus(http.getString()); 
      http.end();
      return status;
    }
    Serial.printf("❌ [RELAY] Status check failed, HTTP %d\n", code);
    http.end();
  }
  return false; 
}

/**
 * @brief Sets the relay state with verification (Closed-Loop).
 */
void setRelay(bool on) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("❌ [RELAY] No WiFi. Command skipped.");
    return; 
  }
  
  HTTPClient http;
  http.setTimeout(2500);
  http.setReuse(false);
  String url = String(remoteHost) + (on ? relayOn : relayOff);
  Serial.println(String("📡 [RELAY] CMD: ") + (on ? "ON" : "OFF") + " → " + url);

  if (http.begin(url)) {
    int code = http.GET();
    Serial.printf("📤 [RELAY] HTTP %d\n", code);
    
    if (code == 200) {
      Serial.println("🔍 [RELAY] Command OK. Verifying status...");
      delay(500); 
      bool actualState = getRelayStatus();
      Serial.printf("👀 [RELAY] Verified state: %s\n", actualState ? "ON" : "OFF");
      if (actualState == on) {
        Serial.println("✅ [RELAY] SUCCESS. State matches command.");
        heating = on; 
      } else {
        Serial.println("❌ [RELAY] ERROR! State MISMATCH. Retrying next cycle.");
      }
    } else {
      Serial.println("❌ [RELAY] HTTP error. State unchanged. Retrying next cycle.");
    }
    http.end();
  } else {
    Serial.println("❌ [RELAY] http.begin() failed. State unchanged. Retrying next cycle.");
  }
}

/**
 * @brief (Internal) Parses Tasmota JSON for temperature sensor.
 */
static float parseTasmotaPayloadForTemp(const String& payload) {
  DynamicJsonDocument doc(4096);
  DeserializationError err = deserializeJson(doc, payload);
  if (err) {
    Serial.printf("❌ [TEMP] JSON parse error: %s\n", err.c_str());
    return NAN;
  }
  if (doc["StatusSNS"]["DS18B20"]["Temperature"])        return doc["StatusSNS"]["DS18B20"]["Temperature"].as<float>();
  if (doc["StatusSNS"]["DS18B20-1"]["Temperature"])      return doc["StatusSNS"]["DS18B20-1"]["Temperature"].as<float>();
  if (doc["DS18B20"]["Temperature"])                     return doc["DS18B20"]["Temperature"].as<float>();
  if (doc["StatusSNS"].is<JsonObject>()) {
    for (JsonPair kv : doc["StatusSNS"].as<JsonObject>()) {
      if (kv.value().is<JsonObject>() && kv.value()["Temperature"])
        return kv.value()["Temperature"].as<float>();
    }
  }
  return NAN;
}

/**
 * @brief Fetches temperature from the remote Tasmota device.
 */
float getRemoteTemp() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("🌡️❌ [TEMP] No WiFi. Read skipped.");
    return NAN; 
  }
  
  HTTPClient http;
  http.setTimeout(2500);
  http.setReuse(false);
  float temp = NAN;
  
  String url1 = String(remoteHost) + "/cm?cmnd=Status%208";
  Serial.println("🌡️ [TEMP] GET " + url1);
  if (http.begin(url1)) {
    int code = http.GET();
    if (code == 200) temp = parseTasmotaPayloadForTemp(http.getString());
    http.end();
  }
  
  if (isnan(temp)) {
    String url2 = String(remoteHost) + "/cm?cmnd=Sensor";
    Serial.println("🌡️ [TEMP] GET " + url2);
    if (http.begin(url2)) {
      int code = http.GET();
      if (code == 200) temp = parseTasmotaPayloadForTemp(http.getString());
      http.end();
    }
  }
  
  return temp;
}

/**
 * @brief NEW: Sends a "Restart 1" command to the Tasmota device.
 * This is a "fire and forget" command for emergency watchdog use.
 */
void rebootTasmota() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("❌ [WATCHDOG] No WiFi. Cannot send reboot command.");
    return; 
  }

  HTTPClient http;
  http.setTimeout(1500); 
  http.setReuse(false);
  String url = String(remoteHost) + "/cm?cmnd=Restart%201";
  Serial.println("📡 [WATCHDOG] CMD: RESTART → " + url);

  if (http.begin(url)) {
    http.GET(); 
    http.end();
  } else {
    Serial.println("❌ [WATCHDOG] http.begin() failed for reboot command.");
  }
}


// ----------------- WEATHER (MODIFIED for 5-Day/3-Hour Forecast) -----------------
/**
 * @brief Fetches weather forecast from OpenWeatherMap API.
 * This now uses the /forecast endpoint to get predictive data.
 */
bool fetchOpenWeather() {
  if (owApiKey.length() < 5 || owCity.length() < 2) {
    Serial.println("🌦️ [WEATHER] Missing API key or city");
    return false;
  }
  
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("🌦️❌ [WEATHER] No WiFi. Fetch skipped.");
    return false;
  }
  
  WiFiClientSecure client;
  client.setInsecure(); 
  client.setTimeout(3000);
  HTTPClient http;
  http.setTimeout(2500);
  http.setReuse(false);

  // --- MODIFIED: Use /forecast endpoint, cnt=2 asks for 2 time blocks (now, +3h)
  String url = "https://api.openweathermap.org/data/2.5/forecast?q=" + owCity + "&units=" + owUnits + "&lang=" + (lang == "hu" ? "hu" : "en") + "&appid=" + owApiKey + "&cnt=2";
  
  Serial.println("🌦️ [WEATHER] GET (Forecast) " + url);
  if (!http.begin(client, url)) {
    Serial.println("🌦️❌ [WEATHER] http.begin() failed");
    return false;
  }
  
  int code = http.GET();
  if (code != 200) {
    Serial.printf("🌦️❌ [WEATHER] HTTP %d\n", code);
    // --- FALLBACK ---
    owTemp = 10.0f; 
    owTemp_3h_forecast = 10.0f; // Fallback
    owPop_3h_forecast = 0.0f; // Fallback
    owDesc = "API Error";
    owIcon = "01d";
    http.end();
    return false;
  }
  String payload = http.getString();
  http.end();
  
  DynamicJsonDocument doc(8192); // Needs to be larger for forecast
  if (deserializeJson(doc, payload)) {
    Serial.println("🌦️❌ [WEATHER] JSON error");
    // --- FALLBACK ---
    owTemp = 10.0f; 
    owTemp_3h_forecast = 10.0f; 
    owPop_3h_forecast = 0.0f;
    owDesc = "JSON Error";
    owIcon = "01d";
    return false;
  }

  // --- MODIFIED: Parse the new forecast structure ---
  if (!doc["list"] || doc["list"].size() < 2) {
    Serial.println("🌦️❌ [WEATHER] JSON structure invalid (missing 'list')");
    // --- FALLBACK ---
    owTemp = 10.0f; 
    owTemp_3h_forecast = 10.0f; 
    owPop_3h_forecast = 0.0f;
    owDesc = "JSON Error";
    owIcon = "01d";
    return false;
  }

  // Get data for "NOW" (list[0])
  JsonVariant list0 = doc["list"][0];
  // Get data for "IN 3 HOURS" (list[1])
  JsonVariant list1 = doc["list"][1];
  
  // Update all global weather variables from list[0]
  owTemp  = list0["main"]["temp"]       | 10.0f; 
  owFeelsLike = list0["main"]["feels_like"] | owTemp;
  owTempMin = list0["main"]["temp_min"] | owTemp;
  owTempMax = list0["main"]["temp_max"] | owTemp;
  owHum   = list0["main"]["humidity"]   | 50.0f;
  owPress = list0["main"]["pressure"]   | 1013.0f;
  owWind  = list0["wind"]["speed"]      | 0.0f;
  
  // --- NEW: Get Forecast data ---
  owPop_3h_forecast = list0["pop"] | 0.0f; // Probability of precipitation (0-1)
  owTemp_3h_forecast = list1["main"]["temp"] | owTemp; // 3h forecast, fallback to current
  // ---

  // Get shared data (city, sunrise/sunset)
  owSunrise = doc["city"]["sunrise"] | 0;
  owSunset = doc["city"]["sunset"] | 0;
  
  const char* icon_val = list0["weather"][0]["icon"];
  owIcon = String(icon_val ? icon_val : "01d");
  
  const char* desc_val = list0["weather"][0]["description"];
  owDesc = String(desc_val ? desc_val : "Weather OK");
  // --- END MODIFICATION ---
  
  lastWeatherFetch = millis();
  
  Serial.printf("🌦️✅ Now: %.1f°C (Feels: %.1f°C), 3h Fcast: %.1f°C, Precip: %.0f%%\n",
    owTemp, owFeelsLike, owTemp_3h_forecast, (owPop_3h_forecast * 100.0f));
  Serial.printf("🌦️✅ %s (%s)\n", owDesc.c_str(), owIcon.c_str());
  return true;
}