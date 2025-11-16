#pragma once

/* ===============================================================
 * GLOBALS.H (v6.6 - Forecast Upgrade)
 * =============================================================== */

// --- Libraries ---
#include <WiFi.h>
#include <WebServer.h>
#include <WiFiManager.h>
#include <ESPmDNS.h>
#include <Preferences.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>
#include <time.h>
#include <math.h>
#include <ArduinoOTA.h>
#include <SPIFFS.h>
#include "config.h"
#include <ESPping.h> 

// --- Program Info Structs ---
struct TargetInfo {
  float target;
  String programName;
};
struct ScheduleEvent {
  time_t epochTime;
  float targetTemp;
  String programName;
};

// --- NEW: Advanced Schedule Struct ---
#define MAX_SCHEDULE_POINTS 21 
struct SchedulePoint {
  uint8_t day;     
  uint16_t time;   
  float target;    
  bool enabled;    
};

// --- Global Variable (Extern Declaration) ---
extern WebServer server;
extern Preferences prefs;
extern float currentTemp;
extern float filtTemp;
extern float hyst;
extern bool heating;
extern bool manualMode;
extern float manualTarget;
extern bool boostActive;
extern uint32_t boostUntil;
extern bool ecoEnabled;
extern bool preHeatActive; 
extern const float ecoDelta;
extern String lang;

// Simple Schedule (Fallback)
extern String wdMorningTime, wdEveningTime, weMorningTime, weEveningTime;
extern float wdTargetMorning, wdTargetEvening, weTargetMorning, weTargetEvening;

// Advanced Learning
extern bool learnMode;
extern bool learnActive;
extern float learnGainRate;
extern float learnLossCoeff;

// Advanced Schedule Globals
extern bool advancedSchedulingEnabled;
extern int advancedScheduleCount;
extern SchedulePoint advancedSchedule[MAX_SCHEDULE_POINTS];

// --- Presence Detection (Away Mode) ---
extern bool awayMode;
extern float awayTargetTemp;
extern String presenceIPs; 
extern int awayTimeoutMins;
extern unsigned long lastPresenceMs; 
extern unsigned long lastPingCheck;  

// --- Calendar Integration ---
extern bool calendarMode;     
extern float calendarTarget;  
extern unsigned long lastCalendarFetch; 

// Timers
extern unsigned long lastTempFetch, lastControl, lastLog, lastGas, lastWeatherFetch, lastSwitchMs;
extern unsigned long lastWifiCheck; 
extern unsigned long cpuBusyMicros;
extern unsigned long cpuWindowStartMs;
extern int cpuLoadPctCached;

// Remote Relay
extern String remoteHost, relayOn, relayOff;
extern int tasmotaFailureCount; 

// Gas
extern int lastGasDay;
extern float gasMJ_today, gasCost_today;
extern unsigned long onMillis_today;
extern float gasEnergyPerM3, gasPricePerMJ;

// Weather
extern String owApiKey, owCity, owUnits;
extern float owTemp, owFeelsLike, owTempMin, owTempMax, owHum, owPress, owWind;
extern uint32_t owSunrise, owSunset;
extern String owIcon, owDesc;
// --- NEW: Forecast Globals ---
extern float owTemp_3h_forecast;  // Temperature in 3 hours
extern float owPop_3h_forecast;   // Probability of Precipitation (0-1)

// Log
extern LogPoint logBuf[LOG_CAP];
extern int logCount;
extern int logHead;


// --- Function Prototypes ---

// main .ino
void setup_wifi_manager();
void setup_mdns();
void setup_ota();
void setup_time();
void checkWiFiConnection(); 

// time_utils.cpp
time_t getEpochNow();
String getTimeString();
bool isWeekendNow();
bool isNightNow();
int toMinutes(const String& hhmm);

// schedule.cpp
ScheduleEvent getNextScheduleEvent();
TargetInfo getActiveProgramInfo();

// control.cpp
void controlHeating();
void updateLearning(float prevT, float nowT, float outdoorT, unsigned long dtMs);
void updateGasEstimation();
void update_cpu_load();
void checkPresence(); 
void updateAwayStatus(); 

// sensors_relay.cpp
void setRelay(bool on);
float getRemoteTemp();
bool fetchOpenWeather();
void rebootTasmota(); 

// storage.cpp
void saveSettings();
void loadSettings();
void saveLogToNVS();
void loadLogFromNVS();
void appendLog(time_t ep, float t);
void logToGoogleSheet(String params); 
void fetchCalendarTarget(); 

// web_server.cpp
void setup_web_server();
void loop_web_server();
void handleStatus();
void handleToggle();
void handleManualHeat();
void handleSave();
void handleSaveLang();
void handleSaveSched();
void handleProSet();
void handleBoost();
void handleEco();
void handleSchedJson();
void handleSettingsJson();
void handleDevInfo();
void handleGasSave();
void handleWeatherSave();
void handleLogJson();
void handleDownloadCSV();
void handleClearLog();
void handleWifiReset();
void handleEnergyJson();
void handleDiagJson();
void handleReboot();
void handleWeatherJson();

// Advanced Schedule Handlers
void handleAdvSchedJson();
void handleAdvSchedSave();
void handleAdvSchedEnable();
void handleAdvSchedDelete(); 

// Presence API
void handlePresenceSave();

// --- NEW: Calendar API ---
void handleCalendarSave();

// V55 Module
void V55_afterSetupRegisterRoutes();
void V55_loopTick();
namespace V55 { bool getTPIAdvice(); }