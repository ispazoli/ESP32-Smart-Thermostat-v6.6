<<<<<<< HEAD
[Magyar (HU)](https://www.google.com/search?q=%23magyar-verzi%C3%B3) | [English (EN)](https://www.google.com/search?q=%23english-version)
=======
Magyar (HU) | English (EN)ESP32 Smart Thermostat Pro (v6.6+)Ez egy fejlett, hálózatra kapcsolt okostermosztát firmware, amely egy ESP32-es mikrokontrolleren fut. Egy különálló, Tasmota-alapú (ESP8266/ESP32) relé- és szenzoregységet vezérel HTTP-n keresztül.A projekt célja egy kereskedelmi forgalomban kapható okostermosztátok tudásával vetekedő, proaktív okostermosztát biztosítása. A rendszer nemcsak a ház hőveszteségét tanulja meg, hanem a várható időjárás-előrejelzést (/forecast API [cite: sensors_relay.cpp (v6.6 - Teljes, Javított):sensors_relay.cpp]) is felhasználja, hogy intelligensebben indítsa a fűtést.Mindezt helyi hálózaton futtatva, de képes felhő-szolgáltatások (Google Naptár, Google Sheets) integrálására is.<a id="magyar-verzió"></a>Magyar Verzió (HU)📸 Galéria / Működés közbenA webes felület három beépített témát tartalmaz [cite: style.css], valamint reszponzív, funkcionális képernyőket biztosít a beállításokhoz.Választható TémákApple Téma (Alapértelmezett)Siemens TémaNest TémaFunkcionális KépernyőkIdőjárás (v6.6 Prognózis)Rendszer (Okos Funkciók)Diagnosztika (Mérőórák)🌟 Főbb Funkciók (v6.6)A rendszer lelke egy ESP32, amely egy központi "agyként" funkcionál. Minden vezérlési logika, ütemezés és a webes felület itt fut.Proaktív "Optimális Indítás" (Smart Learning v6.6): A rendszer már nemcsak a jelenlegi külső hőmérsékletet (owTemp), hanem a 3 órás előrejelzést (owTemp_3h_forecast [cite: globals.h]) is felhasználja. Kiszámítja a várható hőveszteséget, és előre gondolkodva, intelligensebben indítja a fűtést, hogy az pont az ütemezett időpontra érje el a célhőfokot [cite: schedule.cpp].Modern Webes Felület: Teljesen reszponzív, témázható (Apple, Siemens, Nest stílusú) mobilbarát weboldal [cite: index.html (v6.6 - Prognózis):index.html, app.js (v6.6 - Teljes, Javított):app.js].Időjárás-előrejelzés: A /forecast API [cite: sensors_relay.cpp (v6.6 - Teljes, Javított):sensors_relay.cpp] használatával kijelzi a várható 3 órás hőmérsékletet és a csapadék esélyét [cite: index.html (v6.6 - Prognózis):index.html].Zárt láncú Tasmota vezérlés: HTTP parancsokkal vezérel egy távoli Tasmota relét. A parancs kiadása után ellenőrzi a relé tényleges állapotát a setRelay funkcióban [cite: sensors_relay.cpp (v6.6 - Teljes, Javított):sensors_relay.cpp].Fejlett TPI Vezérlés: "Time-Proportional Integral" (TPI) algoritmust használ a fűtés precíz, impulzusszélesség-moduláción alapuló vezérléséhez (a V55 modul alapján) [cite: v55_module.cpp].Jelenlét Érzékelés (Away Mode): Figyeli a helyi hálózaton lévő eszközöket (pl. telefonok) PING segítségével. Ha senki sincs otthon, "Távollét" módba kapcsol [cite: control.cpp].Google Naptár Integráció: Képes beolvasni egy Google Naptárból az eseményeket, és felülbírálni a fűtési ütemtervet (pl. "Home Office" vagy "Nyaralás" események alapján) [cite: storage.cpp (v6.6 - Tanúsítvány javítva):storage.cpp].Google Sheets Naplózás: Automatikusan naplózza a hőmérsékleti adatokat és a gázfogyasztást egy privát Google Sheets táblázatba [cite: storage.cpp (v6.6 - Tanúsítvány javítva):storage.cpp].Stabilitási Funkciók (Watchdog):Tasmota Watchdog: Figyeli a Tasmota egység válaszait. Ha a Tasmota lefagy, a termosztát biztonsági okokból lekapcsolja a fűtést, és újraindítási parancsot küld a Tasmotának (rebootTasmota() [cite: sensors_relay.cpp (v6.6 - Teljes, Javított):sensors_relay.cpp]).Wi-Fi Öngyógyítás: Automatikusan megpróbál újracsatlakozni a Wi-Fi hálózatra, ha a kapcsolat megszakad [cite: ESP_Thermostat_Pro_v6_5_1_Calendar_Backend.ino].⚙️ Működés (Soros Monitor)A serial log.txt [cite: serial log.txt] tartalma tökéletesen mutatja a rendszer működését. A termosztát 10 másodpercenként lekéri a Tasmota hőfokát, és közben futtatja a többi okos funkciót.// A Tasmota egység folyamatos lekérdezése
13:23:37.602 -> 🌡️ [TEMP] GET [http://192.168.1.](http://192.168.1.x)/cm?cmnd=Status%208
13:23:47.574 -> 🌡️ [TEMP] GET [http://192.168.1.](http://192.168.1.x)/cm?cmnd=Status%208
>>>>>>> parent of 5fe4621 (Enhance README with detailed feature descriptions)

# **ESP32 Smart Thermostat Pro (v6.6+)**

Ez egy fejlett, hálózatra kapcsolt okostermosztát firmware, amely egy ESP32-es mikrokontrolleren fut. Egy különálló, Tasmota-alapú (ESP8266/ESP32) relé- és szenzoregységet vezérel HTTP-n keresztül.

A projekt célja egy kereskedelmi forgalomban kapható okostermosztátok tudásával vetekedő, **proaktív** okostermosztát biztosítása. A rendszer nemcsak a ház hőveszteségét tanulja meg, hanem a **várható időjárás-előrejelzést** (/forecast API

$$cite: \`sensors\_relay.cpp (v6.6 \- Teljes, Javított):sensors\_relay.cpp\`$$  
) is felhasználja, hogy intelligensebben indítsa a fűtést.

Mindezt helyi hálózaton futtatva, de képes felhő-szolgáltatások (Google Naptár, Google Sheets) integrálására is.

# **Magyar Verzió (HU)**

## **📸 Galéria / Működés közben**

A webes felület három beépített témát tartalmaz

$$cite: \`style.css\`$$  
, valamint reszponzív, funkcionális képernyőket biztosít a beállításokhoz.

### **Választható Témák**

|

| Apple Téma (Alapértelmezett) | Siemens Téma | Nest Téma |  
| | | |

### **Funkcionális Képernyők**

| Időjárás (v6.6 Prognózis) | Rendszer (Okos Funkciók) | Diagnosztika (Mérőórák) |  
| | | |

## **🌟 Főbb Funkciók (v6.6)**

A rendszer lelke egy ESP32, amely egy központi "agyként" funkcionál. Minden vezérlési logika, ütemezés és a webes felület itt fut.

* **Proaktív "Optimális Indítás" (Smart Learning v6.6):** A rendszer már nemcsak a *jelenlegi* külső hőmérsékletet (owTemp), hanem a **3 órás előrejelzést** (owTemp\_3h\_forecast$$cite: \`globals.h\`$$  
  ) is felhasználja. Kiszámítja a várható hőveszteséget, és *előre gondolkodva*, intelligensebben indítja a fűtést, hogy az pont az ütemezett időpontra érje el a célhőfokot$$cite: \`schedule.cpp\`$$  
  .  
* **Modern Webes Felület:** Teljesen reszponzív, témázható (Apple, Siemens, Nest stílusú) mobilbarát weboldal$$cite: \`index.html (v6.6 \- Prognózis):index.html\`, \`app.js (v6.6 \- Teljes, Javított):app.js\`$$  
  .  
* **Időjárás-előrejelzés:** A /forecast API$$cite: \`sensors\_relay.cpp (v6.6 \- Teljes, Javított):sensors\_relay.cpp\`$$  
  használatával kijelzi a várható 3 órás hőmérsékletet és a csapadék esélyét$$cite: \`index.html (v6.6 \- Prognózis):index.html\`$$  
  .  
* **Zárt láncú Tasmota vezérlés:** HTTP parancsokkal vezérel egy távoli Tasmota relét. A parancs kiadása után ellenőrzi a relé tényleges állapotát a setRelay funkcióban$$cite: \`sensors\_relay.cpp (v6.6 \- Teljes, Javított):sensors\_relay.cpp\`$$  
  .  
* **Fejlett TPI Vezérlés:** "Time-Proportional Integral" (TPI) algoritmust használ a fűtés precíz, impulzusszélesség-moduláción alapuló vezérléséhez (a V55 modul alapján)$$cite: \`v55\_module.cpp\`$$  
  .  
* **Jelenlét Érzékelés (Away Mode):** Figyeli a helyi hálózaton lévő eszközöket (pl. telefonok) PING segítségével. Ha senki sincs otthon, "Távollét" módba kapcsol$$cite: \`control.cpp\`$$  
  .  
* **Google Naptár Integráció:** Képes beolvasni egy Google Naptárból az eseményeket, és felülbírálni a fűtési ütemtervet (pl. "Home Office" vagy "Nyaralás" események alapján)$$cite: \`storage.cpp (v6.6 \- Tanúsítvány javítva):storage.cpp\`$$  
  .  
* **Google Sheets Naplózás:** Automatikusan naplózza a hőmérsékleti adatokat és a gázfogyasztást egy privát Google Sheets táblázatba$$cite: \`storage.cpp (v6.6 \- Tanúsítvány javítva):storage.cpp\`$$  
  .  
* **Stabilitási Funkciók (Watchdog):**  
  * **Tasmota Watchdog:** Figyeli a Tasmota egység válaszait. Ha a Tasmota lefagy, a termosztát biztonsági okokból lekapcsolja a fűtést, és újraindítási parancsot küld a Tasmotának (rebootTasmota()$$cite: \`sensors\_relay.cpp (v6.6 \- Teljes, Javított):sensors\_relay.cpp\`$$  
    ).  
  * **Wi-Fi Öngyógyítás:** Automatikusan megpróbál újracsatlakozni a Wi-Fi hálózatra, ha a kapcsolat megszakad$$cite: \`ESP\_Thermostat\_Pro\_v6\_5\_1\_Calendar\_Backend.ino\`$$  
    .

## **⚙️ Működés (Soros Monitor)**

A serial log.txt

$$cite: \`serial log.txt\`$$  
tartalma tökéletesen mutatja a rendszer működését. A termosztát 10 másodpercenként lekéri a Tasmota hőfokát, és közben futtatja a többi okos funkciót.

// A Tasmota egység folyamatos lekérdezése  
13:23:37.602 \-\> 🌡️ \[TEMP\] GET \[http://192.168.1.\](http://192.168.1.)x/cm?cmnd=Status%208  
13:23:47.574 \-\> 🌡️ \[TEMP\] GET \[http://192.168.1.\](http://192.168.1.)x/cm?cmnd=Status%208

// A "Smart Learning" folyamatosan tanulja a ház hűlési sebességét  
13:23:48.714 \-\> 🧠📉 \[LEARN\] COOLING: Net=-0.87°C/h, T\_Delta=6.61°C \-\> NewCoeff=0.1318, AvgCoeff=0.0942  
13:23:57.609 \-\> 🌡️ \[TEMP\] GET \[http://192.168.1.\](http://192.168.1.)x/cm?cmnd=Status%208

// 15 percenként elmenti az adatot a Google Sheets-be  
13:24:01.623 \-\> 📝 \[LOG\] Saving 15-minute log...  
13:24:01.623 \-\> 📤 \[GSheet\] Sending data to URL: \[https://script.google.com/macros/s/xxxx\](https://script.google.com/macros/s/xxxx)...  
13:24:07.703 \-\> 📬 \[GSheet\] HTTP Code: 200  
13:24:07.703 \-\> 📬 \[GSheet\] Response: OK: Data logged successfully.

// Percenként fut a Jelenlét-érzékelés (PING)  
13:24:07.703 \-\> Pinging... 192.168.1.x  
13:24:08.617 \-\> 🏠 \[PRESENCE\] Success\! 192.168.1.x is reachable.  
13:24:08.617 \-\> 🌡️ \[TEMP\] GET \[http://192.168.1.\](http://192.168.1.)x/cm?cmnd=Status%208

// ... (később, a v6.6-os kód futtatása)

// A 10 percenkénti időjárás-lekérdezés már a "/forecast" API-t használja  
16:51:02.004 \-\> 🌦️ \[WEATHER\] GET (Forecast) \[https://api.openweathermap.org/data/2.5/forecast?q=\](https://api.openweathermap.org/data/2.5/forecast?q=)...  
// Sikerült a 3 órás előrejelzés lekérése\!  
16:51:02.417 \-\> 🌦️✅ Now: 12.2°C (Feels: 11.2°C), 3h Fcast: 10.9°C, Precip: 0%  
16:51:02.464 \-\> 🌦️✅ overcast clouds (04n)  
16:51:02.776 \-\> 🌡️ \[TEMP\] GET \[http://192.168.1.\](http://192.168.1.)x/cm?cmnd=Status%208

// A tanulási algoritmus folyamatosan fut  
16:51:03.050 \-\> 🧠📉 \[LEARN\] COOLING: Net=-4.05°C/h, T\_Delta=8.83°C \-\> NewCoeff=0.4585, AvgCoeff=0.1504

## **🛠️ Hardverkövetelmények**

1. **Központi Egység (Agy):** 1 db ESP32 (pl. ESP32 WROOM 32).  
2. **Relé/Szenzor Egység:** 1 db ESP8266 (pl. Wemos D1 Mini) vagy ESP32, amely Tasmota firmware-t futtat.  
3. **Szenzor:** 1 db DS18B20 hőmérséklet-érzékelő, amely a Tasmota egységre van kötve.  
4. **Kapcsolás:** 1 db 5V-os relé modul, amelyet a Tasmota egység vezérel.

## **⚙️ Szoftveres Beüzemelés**

A rendszer három fő komponensből áll, amelyeket be kell állítani.

### **1\. Lépés: Tasmota Relé/Szenzor Egység**

Ez az egység felel a fizikai mérésért és kapcsolásért.

1. Telepítsd a Tasmota firmware-t az ESP8266/ESP32 eszközre.  
2. Állítsd be a Tasmota felületén a DS18B20 szenzort.  
3. Állítsd be a relét.  
4. Győződj meg róla, hogy az egység fix IP címet kap a routereden.  
5. Ellenőrizd, hogy a http://\<IP\>/cm?cmnd=Status%208 parancsra JSON választ kapsz, ami tartalmazza a hőmérsékleti adatot.  
6. Ellenőrizd, hogy a http://\<IP\>/cm?cmnd=Power%20On és Power%20Off parancsokkal tudod kapcsolni a relét.

### **2\. Lépés: Google Script (Kombinált)**

A Google Naptár és a Google Sheets naplózás funkciókhoz egyetlen Google Apps Scriptre van szükség

$$cite: \`ESP\_Thermostat\_Script.gs\`$$  
.

1. Hozz létre egy új Google Sheets táblázatot (pl. Termosztát Adatok).  
2. Hozd létre a lapokat (pl. Sheet1 vagy Napló). Állítsd be a fejléceket (Dátum, Hőmérséklet (°C), Gáz Fogyasztás (MJ), Gáz Költség (Ft)).  
3. Menj az Eszközök \> Parancsfájl-szerkesztő menübe.  
4. Illeszd be a Thermostat\_Combined\_Script.gs$$cite: \`ESP\_Thermostat\_Script.gs\`$$  
   teljes tartalmát.  
5. **Állítsd be a konfigurációs részt** a szkript tetején (a SHEET\_ID-t, CALENDAR\_ID-t stb.).  
6. **Telepítsd a szkriptet:**  
   * Telepítés \> Új telepítés.  
   * Típus: Internetes alkalmazás.  
   * Hozzáférés: Bárki (Anyone).  
   * Engedélyezd a futtatást (A Google kérni fogja a hozzáférést a Sheets-hez és a Naptárhoz).  
7. Másold ki a kapott "Internetes alkalmazás URL-címét".

### **3\. Lépés: ESP32 Termosztát Firmware**

Ez a projekt fő firmware-e.

1. **Könyvtárak:** Telepítsd az összes szükséges könyvtárat az Arduino IDE-ben (a globals.h alapján)$$cite: \`globals.h\`$$  
   .  
2. **Konfiguráció:**  
   * **config.h:** Illeszd be a 2\. Lépésben kapott Google Script URL-t a G\_SCRIPT\_URL makróba$$cite: \`config.h\`$$  
     .  
   * **ESP\_Thermostat\_Pro...ino:** A globális változók között állítsd be a Tasmota egységed IP címét (remoteHost)$$cite: \`ESP\_Thermostat\_Pro\_v6\_5\_1\_Calendar\_Backend.ino\`$$  
     .  
3. **SPIFFS Fájlrendszer feltöltése:**  
   * Hozd létre a data mappát a projekt gyökerében.  
   * Másold bele a 3 webes fájlt: index.html$$cite: \`index.html (v6.6 \- Prognózis):index.html\`$$  
     , style.css$$cite: \`style.css\`$$  
     , app.js$$cite: \`app.js (v6.6 \- Teljes, Javított):app.js\`$$  
     .  
   * Az Arduino IDE Tools (Eszközök) menüjéből válaszd az "ESP32 Sketch Data Upload" opciót.  
4. **Fordítás és Feltöltés:** Fordítsd le és töltsd fel a programot az ESP32-re.

### **4\. Lépés: Első Indítás (WiFiManager)**

1. Első indításkor az ESP32 létrehoz egy ESP\_Thermostat\_Setup nevű Wi-Fi hálózatot$$cite: \`helpers.cpp\`$$  
   .  
2. Csatlakozz ehhez a hálózathoz a telefonoddal. Egy felugró portál fogad.  
3. Add meg az otthoni Wi-Fi hálózatod adatait.  
4. Az ESP32 elmenti a beállításokat, és újraindul. Keresd meg http://esp32thermostat.local$$cite: \`helpers.cpp\`$$  
   címen.

## **📖 Felhasználói Útmutató (Webes Felület)**

Nyisd meg a termosztát IP címét (vagy a http://esp32thermostat.local címet) egy böngészőben.

### **Főoldal (Thermostat)**

(Lásd: Thermostat.png)

* **Fő kijelző:** Itt láthatod az aktuális hőmérsékletet, a célhőfokot és az aktív programot (pl. "Hétköznap reggel", "Naptár", "Távollét").  
* **Jelvények (Badges):**  
  * TÁVOLLÉT (Away): Akkor jelenik meg, ha a jelenlét-érzékelés aktív.  
  * ELŐFŰTÉS (Pre-Heat): Akkor jelenik meg, ha az "Optimális Indítás" (Smart Learning) aktív, és a rendszer épp fűt az ütemezés *előtt*.  
  * BOOST: Manuális fűtés \+1°C-kal 30 percre.  
  * ECO: Éjszakai (22:00-06:00) hőmérséklet-csökkentés aktív.  
* **Hőmérséklet Napló:** Az elmúlt 48 óra hőmérsékleti grafikonja.

### **Ütemterv (Schedule)**

* Ez a fül csak akkor látható, ha a "Haladó Ütemterv" be van kapcsolva a Rendszer fülön.  
* Itt vehetsz fel új, időponthoz és naphoz kötött fűtési pontokat (max. 21 db).

### **Rendszer & Statisztika (System)**

(Lásd: System.png)

* **Szabályozás (Control):**  
  * Tanuló mód: Az "Optimális Indítás" be/kikapcsolása.  
  * Haladó ütemterv: Váltás az egyszerű és a 7 napos ütemező között.  
* **Gáz (Gas):** Add meg a gáz fűtőértékét és árát a becsült fogyasztás és költség kiszámításához.  
* **Okos Funkciók (Smart Features):**  
  * **Jelenlét Érzékelés:** Itt add meg a figyelt telefonok IP címeit, a türelmi időt (pl. 30 perc), és a "Távollét" hőfokot (pl. 16°C).  
* **Naptár Integráció:** Engedélyezi a Google Naptár felülbírálást. A Google Scriptben (ESP\_Thermostat\_Script.gs$$cite: \`ESP\_Thermostat\_Script.gs\`$$  
  ) beállított KEYWORD (pl. futes:22.5) beírásával működik az esemény leírásában.

### **Időjárás (Weather)**

(Lásd: Weather.png)

* A termosztát az OpenWeatherMap 5 Day / 3 Hour Forecast API-ját használja$$cite: \`sensors\_relay.cpp (v6.6 \- Teljes, Javított):sensors\_relay.cpp\`$$  
  .  
* Itt kell megadnod az ingyenes OWM API kulcsodat és a városodat.  
* **Új (v6.6):** A felület már nemcsak a jelenlegi hőfokot, hanem a **Csapadék (3ó)** esélyét (pop$$cite: \`sensors\_relay.cpp (v6.6 \- Teljes, Javított):sensors\_relay.cpp\`$$  
  ) és a **3 órás előrejelzés** hőfokát (temp\_3h$$cite: \`app.js (v6.6 \- Teljes, Javított):app.js\`$$  
  ) is kijelzi.

### **Diagnosztika (Diagnostics)**

(Lásd: Diag.png)

* A rendszer belső állapotjelzője, hibakereséshez.  
* Presence Ping: **(Élő adat)** Azt mutatja, mikor látta utoljára a rendszer a figyelt IP címek valamelyikét. Segít a Jelenlét Érzékelés tesztelésében$$cite: \`app.js (v6.6 \- Teljes, Javított):app.js\`$$  
  .  
* **Okos Tanulás Diagnosztika:**  
  * Kazán Felfűtési Sebesség: A tanult érték, °C/óra.  
  * Épület Hatékonysága: A tanult hővesztési együttható (minél alacsonyabb, annál jobb).

# **English Version (EN)**

## **📸 Gallery / In Action**

The web interface features three built-in themes

$$cite: \`style.css\`$$  
and provides responsive, functional screens for configuration.

### **Selectable Themes**

| Apple Theme (Default) | Siemens Theme | Nest Theme |  
| | | |

### **Functional Screens**

| Weather (v6.6 Forecast) | System (Smart Features) | Diagnostics (Gauges) |  
| | | |

## **🌟 Core Features (v6.6)**

The system's "brain" is an ESP32, which runs all control logic, scheduling, and the web interface.

* **Proactive "Optimal Start" (Smart Learning v6.6):** The system no longer uses just the *current* outdoor temperature (owTemp), but also the **3-hour forecast** (owTemp\_3h\_forecast$$cite: \`globals.h\`$$  
  ). It calculates the *expected* heat loss and starts the heating more intelligently, thinking ahead to reach the target temperature exactly on time$$cite: \`schedule.cpp\`$$  
  .  
* **Modern Web UI:** A fully responsive, theme-able (Apple, Siemens, Nest styles) mobile-friendly web interface$$cite: \`index.html (v6.6 \- Prognózis):index.html\`, \`app.js (v6.6 \- Teljes, Javított):app.js\`$$  
  .  
* **Weather Forecast:** Uses the /forecast API$$cite: \`sensors\_relay.cpp (v6.6 \- Teljes, Javított):sensors\_relay.cpp\`$$  
  to display the 3-hour temperature forecast and the probability of precipitation$$cite: \`index.html (v6.6 \- Prognózis):index.html\`$$  
  .  
* **Closed-Loop Tasmota Control:** Manages a remote Tasmota relay via HTTP, verifying the relay's actual state after sending a command using the setRelay function$$cite: \`sensors\_relay.cpp (v6.6 \- Teljes, Javított):sensors\_relay.cpp\`$$  
  .  
* **Advanced TPI Control:** Uses a Time-Proportional Integral (TPI) algorithm for precise, pulse-width-modulated heating control (based on the V55 module)$$cite: \`v55\_module.cpp\`$$  
  .  
* **Presence Detection (Away Mode):** Monitors devices on the local network (e.g., phones) via PING. If no one is home, it switches to "Away Mode"$$cite: \`control.cpp\`$$  
  .  
* **Google Calendar Integration:** Can read events from a Google Calendar to override the heating schedule (e.g., for "Home Office" or "Vacation" events)$$cite: \`storage.cpp (v6.6 \- Tanúsítvány javítva):storage.cpp\`$$  
  .  
* **Google Sheets Logging:** Automatically logs temperature data and gas consumption metrics to a private Google Sheet$$cite: \`storage.cpp (v6.6 \- Tanúsítvány javítva):storage.cpp\`$$  
  .  
* **Stability Features (Watchdog):**  
  * **Tasmota Watchdog:** Monitors Tasmota unit responses. If the Tasmota unit freezes, the thermostat performs a failsafe (turns heating OFF) and sends a reboot command (rebootTasmota()$$cite: \`sensors\_relay.cpp (v6.6 \- Teljes, Javított):sensors\_relay.cpp\`$$  
    ).  
  * **Wi-Fi Self-Healing:** Automatically attempts to reconnect to the Wi-Fi network if the connection is lost$$cite: \`ESP\_Thermostat\_Pro\_v6\_5\_1\_Calendar\_Backend.ino\`$$  
    .

## **⚙️ How it Works (Serial Log)**

The provided serial log.txt

$$cite: \`serial log.txt\`$$  
perfectly demonstrates the system in action. The thermostat polls the Tasmota for temperature every 10 seconds while running its smart features in parallel.

// Continuous polling of the Tasmota unit  
13:23:37.602 \-\> 🌡️ \[TEMP\] GET \[http://192.168.1.\](http://192.168.1.)x/cm?cmnd=Status%208  
13:23:47.574 \-\> 🌡️ \[TEMP\] GET \[http://192.168.1.\](http://192.168.1.)x/cm?cmnd=Status%208

// "Smart Learning" is constantly learning the building's heat loss  
13:23:48.714 \-\> 🧠📉 \[LEARN\] COOLING: Net=-0.87°C/h, T\_Delta=6.61°C \-\> NewCoeff=0.1318, AvgCoeff=0.0942  
13:23:57.609 \-\> 🌡️ \[TEMP\] GET \[http://192.168.1.\](http://192.168.1.)x/cm?cmnd=Status%208

// Every 15 minutes, it logs data to Google Sheets  
13:24:01.623 \-\> 📝 \[LOG\] Saving 15-minute log...  
13:24:01.623 \-\> 📤 \[GSheet\] Sending data to URL: \[https://script.google.com/macros/s/xxxx\](https://script.google.com/macros/s/xxxx)...  
13:24:07.703 \-\> 📬 \[GSheet\] HTTP Code: 200  
13:24:07.703 \-\> 📬 \[GSheet\] Response: OK: Data logged successfully.

// Every minute, Presence Detection (PING) is running  
13:24:07.703 \-\> Pinging... 192.168.1.x  
13:24:08.617 \-\> 🏠 \[PRESENCE\] Success\! 192.168.1.x is reachable.  
13:24:08.617 \-\> 🌡️ \[TEMP\] GET \[http://192.168.1.\](http://192.168.1.)x/cm?cmnd=Status%208

// ... (later, running v6.6 code)

// The 10-minute weather fetch now uses the "/forecast" API  
16:51:02.004 \-\> 🌦️ \[WEATHER\] GET (Forecast) \[https://api.openweathermap.org/data/2.5/forecast?q=\](https://api.openweathermap.org/data/2.5/forecast?q=)...  
// Success\! 3-hour forecast data was received\!  
16:51:02.417 \-\> 🌦️✅ Now: 12.2°C (Feels: 11.2°C), 3h Fcast: 10.9°C, Precip: 0%  
16:51:02.464 \-\> 🌦️✅ overcast clouds (04n)  
16:51:02.776 \-\> 🌡️ \[TEMP\] GET \[http://192.168.1.\](http://192.168.1.)x/cm?cmnd=Status%208

<<<<<<< HEAD
// The learning algorithm continues to run  
16:51:03.050 \-\> 🧠📉 \[LEARN\] COOLING: Net=-4.05°C/h, T\_Delta=8.83°C \-\> NewCoeff=0.4585, AvgCoeff=0.1504

## **🛠️ Hardware Requirements**

1. **Central Unit (Brain):** 1x ESP32 (e.g., ESP32 WROOM 32).  
2. **Relé/Szenzor Egység:** 1x ESP8266 (e.g., Wemos D1 Mini) or ESP32, running Tasmota.  
3. **Szenzor:** 1x DS18B20 temperature sensor, connected to the Tasmota unit.  
4. **Switching:** 1x 5V Relay Module, controlled by the Tasmota unit.

## **⚙️ Software Setup**

The system consists of three main components that must be configured.

### **Step 1: Tasmota Relay/Sensor Unit**

1. Flash Tasmota firmware onto your ESP8266/ESP32.  
2. Configure the DS18B20 sensor and Relay in the Tasmota UI.  
3. Assign a static IP address to this unit on your router.  
4. Verify that http://\<IP\>/cm?cmnd=Status%208 (for sensor) and http://\<IP\>/cm?cmnd=Power%20On (for relay) work.

### **Step 2: Google Script (Combined)**

A single Google Apps Script is needed for Calendar and Sheets logging

$$cite: \`ESP\_Thermostat\_Script.gs\`$$  
.

1. Create a new Google Sheet (e.g., Thermostat Data).  
2. Create your log sheets (e.g., Sheet1) and set up the headers (Dátum, Hőmérséklet (°C), etc.).  
3. Go to Extensions \> Apps Script.  
4. Paste the entire content of Thermostat\_Combined\_Script.gs$$cite: \`ESP\_Thermostat\_Script.gs\`$$  
   .  
5. **Configure the script** at the top (set SHEET\_ID, CALENDAR\_ID, etc.).  
6. **Deploy the script:**  
   * Deploy \> New deployment.  
   * Type: Web app.  
   * Who has access: Anyone.  
   * Authorize the script (it will ask for permission to access your Sheets and Calendar).  
7. Copy the resulting "Web app URL".

### **Step 3: ESP32 Thermostat Firmware**

1. **Libraries:** Install all required libraries in the Arduino IDE (see globals.h)$$cite: \`globals.h\`$$  
   .  
2. **Configuration:**  
   * **config.h:** Paste your Google Script URL from Step 2 into the G\_SCRIPT\_URL macro$$cite: \`config.h\`$$  
     .  
   * **ESP\_Thermostat\_Pro...ino:** Set your Tasmota's IP address in the remoteHost variable$$cite: \`ESP\_Thermostat\_Pro\_v6\_5\_1\_Calendar\_Backend.ino\`$$  
     .  
3. **Upload SPIFFS Filesystem:**  
   * Create a data folder in the project sketch directory.  
   * Place index.html$$cite: \`index.html (v6.6 \- Prognózis):index.html\`$$  
     , style.css$$cite: \`style.css\`$$  
     , and app.js$$cite: \`app.js (v6.6 \- Teljes, Javított):app.js\`$$  
     into this folder.  
   * Use the "ESP32 Sketch Data Upload" tool in the Arduino IDE Tools menu.  
4. **Compile and Upload:** Compile and upload the main .ino sketch to your ESP32.

### **Step 4: First Boot (WiFiManager)**

1. On first boot, the ESP32 creates a Wi-Fi network named ESP\_Thermostat\_Setup$$cite: \`helpers.cpp\`$$  
   .  
2. Connect to it with your phone; a captive portal will appear.  
3. Enter your home Wi-Fi credentials.  
4. The ESP32 will reboot and connect. You can find it at http://esp32thermostat.local$$cite: \`helpers.cpp\`$$  
   .

## **📖 User Guide (Web Interface)**

Open the thermostat's IP address (or http://esp32thermostat.local) in a browser.

### **Main Tab (Thermostat)**

(See: Thermostat.png)

* **Main Display:** Shows current temp, target temp, and active program (e.g., "Weekday morning", "Calendar", "Away Mode").  
* **Badges:**  
  * AWAY: Appears when Presence Detection is active.  
  * PRE-HEAT: Appears when "Optimal Start" (Smart Learning) is active and heating *before* a schedule.  
  * BOOST: Manual heating \+1°C for 30 minutes.  
  * ECO: Nighttime (22:00-06:00) temperature setback is active.  
* **Temperature Log:** A 48-hour chart of your temperature history.

### **Schedule Tab**

* Only visible if "Advanced Schedule" is enabled on the System tab.  
* Lets you add, edit, and delete up to 21 day/time-specific setpoints.

### **System & Stats Tab**

(See: System.png)

* **Control:**  
  * Smart learning: Toggles the "Optimal Start" feature.  
  * Advanced Schedule: Toggles between the Simple and 7-day schedulers.  
* **Gas:** Configure your gas heating value and cost for consumption estimates.  
* **Smart Features:**  
  * **Smart Presence:** Configure monitored IPs, timeout (e.g., 30 min), and "Away" temperature (e.g., 16°C).  
* **Calendar Integration:** Enables Google Calendar override. Works by adding the KEYWORD (e.g., futes:22.5) set in your Google Script$$cite: \`ESP\_Thermostat\_Script.gs\`$$  
  to an event's description.

### **Weather Tab**

(See: Weather.png)

* Uses the OpenWeatherMap 5 Day / 3 Hour Forecast API$$cite: \`sensors\_relay.cpp (v6.6 \- Teljes, Javított):sensors\_relay.cpp\`$$  
  .  
* You must enter your free OWM API key and city name.  
* **New (v6.6):** The UI now displays **Precipitation (3h)** (pop$$cite: \`sensors\_relay.cpp (v6.6 \- Teljes, Javított):sensors\_relay.cpp\`$$  
  ) and the **3-Hour Forecast** temperature (temp\_3h$$cite: \`app.js (v6.6 \- Teljes, Javított):app.js\`$$  
  ).

### **Diagnostics Tab**

(See: Diag.png)

* The internal health dashboard, useful for debugging.  
* Presence Ping: **(Live Data)** Shows how long ago the system last saw a monitored IP. Helps you test the Presence Detection setup$$cite: \`app.js (v6.6 \- Teljes, Javított):app.js\`$$  
  .  
* **Smart Learning Diagnostics:**  
  * Boiler Heat-Up Rate: The learned value in °C/hour.  
  * Building Efficiency: The learned heat-loss coefficient (lower is better).

## **⚖️ Licenc (License)**

Ez a projekt az MIT Licenc alatt van közzétéve. / This project is licensed under the MIT License.

## **🙏 Elismerések (Acknowledgements)**

* Köszönet a projekt eredeti ötletgazdájának, **Ispa**\-nak.  
* A firmware-t és a dokumentációt az **Ispa** és a **Google AI** (Gemini) közösen fejlesztette.
=======
// The learning algorithm continues to run
16:51:03.050 -> 🧠📉 [LEARN] COOLING: Net=-4.05°C/h, T_Delta=8.83°C -> NewCoeff=0.4585, AvgCoeff=0.1504
🛠️ Hardware RequirementsCentral Unit (Brain): 1x ESP32 (e.g., ESP32 WROOM 32).Relé/Szenzor Egység: 1x ESP8266 (e.g., Wemos D1 Mini) or ESP32, running Tasmota.Szenzor: 1x DS18B20 temperature sensor, connected to the Tasmota unit.Switching: 1x 5V Relay Module, controlled by the Tasmota unit.⚙️ Software SetupThe system consists of three main components that must be configured.Step 1: Tasmota Relay/Sensor UnitFlash Tasmota firmware onto your ESP8266/ESP32.Configure the DS18B20 sensor and Relay in the Tasmota UI.Assign a static IP address to this unit on your router.Verify that http://<IP>/cm?cmnd=Status%208 (for sensor) and http://<IP>/cm?cmnd=Power%20On (for relay) work.Step 2: Google Script (Combined)A single Google Apps Script is needed for Calendar and Sheets logging [cite: ESP_Thermostat_Script.gs].Create a new Google Sheet (e.g., Thermostat Data).Create your log sheets (e.g., Sheet1) and set up the headers (Dátum, Hőmérséklet (°C), etc.).Go to Extensions > Apps Script.Paste the entire content of Thermostat_Combined_Script.gs [cite: ESP_Thermostat_Script.gs].Configure the script at the top (set SHEET_ID, CALENDAR_ID, etc.).Deploy the script:Deploy > New deployment.Type: Web app.Who has access: Anyone.Authorize the script (it will ask for permission to access your Sheets and Calendar).Copy the resulting "Web app URL".Step 3: ESP32 Thermostat FirmwareLibraries: Install all required libraries in the Arduino IDE (see globals.h) [cite: globals.h].Configuration:config.h: Paste your Google Script URL from Step 2 into the G_SCRIPT_URL macro [cite: config.h].ESP_Thermostat_Pro...ino: Set your Tasmota's IP address in the remoteHost variable [cite: ESP_Thermostat_Pro_v6_5_1_Calendar_Backend.ino].Upload SPIFFS Filesystem:Create a data folder in the project sketch directory.Place index.html [cite: index.html (v6.6 - Prognózis):index.html], style.css [cite: style.css], and app.js [cite: app.js (v6.6 - Teljes, Javított):app.js] into this folder.Use the "ESP32 Sketch Data Upload" tool in the Arduino IDE Tools menu.Compile and Upload: Compile and upload the main .ino sketch to your ESP32.Step 4: First Boot (WiFiManager)On first boot, the ESP32 creates a Wi-Fi network named ESP_Thermostat_Setup [cite: helpers.cpp].Connect to it with your phone; a captive portal will appear.Enter your home Wi-Fi credentials.The ESP32 will reboot and connect. You can find it at http://esp32thermostat.local [cite: helpers.cpp].📖 User Guide (Web Interface)Open the thermostat's IP address (or http://esp32thermostat.local) in a browser.Main Tab (Thermostat)(See: Thermostat.png)Main Display: Shows current temp, target temp, and active program (e.g., "Weekday morning", "Calendar", "Away Mode").Badges:AWAY: Appears when Presence Detection is active.PRE-HEAT: Appears when "Optimal Start" (Smart Learning) is active and heating before a schedule.BOOST: Manual heating +1°C for 30 minutes.ECO: Nighttime (22:00-06:00) temperature setback is active.Temperature Log: A 48-hour chart of your temperature history.Schedule TabOnly visible if "Advanced Schedule" is enabled on the System tab.Lets you add, edit, and delete up to 21 day/time-specific setpoints.System & Stats Tab(See: System.png)Control:Smart learning: Toggles the "Optimal Start" feature.Advanced Schedule: Toggles between the Simple and 7-day schedulers.Gas: Configure your gas heating value and cost for consumption estimates.Smart Features:Smart Presence: Configure monitored IPs, timeout (e.g., 30 min), and "Away" temperature (e.g., 16°C).Calendar Integration: Enables Google Calendar override. Works by adding the KEYWORD (e.g., futes:22.5) set in your Google Script [cite: ESP_Thermostat_Script.gs] to an event's description.Weather Tab(See: Weather.png)Uses the OpenWeatherMap 5 Day / 3 Hour Forecast API [cite: sensors_relay.cpp (v6.6 - Teljes, Javított):sensors_relay.cpp].You must enter your free OWM API key and city name.New (v6.6): The UI now displays Precipitation (3h) (pop [cite: sensors_relay.cpp (v6.6 - Teljes, Javított):sensors_relay.cpp]) and the 3-Hour Forecast temperature (temp_3h [cite: app.js (v6.6 - Teljes, Javított):app.js]).Diagnostics Tab(See: Diag.png)The internal health dashboard, useful for debugging.Presence Ping: (Live Data) Shows how long ago the system last saw a monitored IP. Helps you test the Presence Detection setup [cite: app.js (v6.6 - Teljes, Javított):app.js].Smart Learning Diagnostics:Boiler Heat-Up Rate: The learned value in °C/hour.Building Efficiency: The learned heat-loss coefficient (lower is better).⚖️ Licenc (License)Ez a projekt az MIT Licenc alatt van közzétéve. / This project is licensed under the MIT License.🙏 Elismerések (Acknowledgements)Köszönet a projekt eredeti ötletgazdájának, Ispa-nak.A firmware-t és a dokumentációt az Ispa és a Google AI (Gemini) közösen fejlesztette.
>>>>>>> parent of 5fe4621 (Enhance README with detailed feature descriptions)
