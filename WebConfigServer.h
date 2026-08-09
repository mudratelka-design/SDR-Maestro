//=============================================================================
// File: WebConfigServer.h
// Commit: 11
// Version: 0.3.0
//=============================================================================

#ifndef WEB_CONFIG_SERVER_H
#define WEB_CONFIG_SERVER_H

#include <Arduino.h>
#include <WebServer.h>

#include "Config.h"

// Hosts a small WiFi access point (SSID/password from Config.h) and a web
// page for defining what each encoder's 4 events send, per profile, and
// for switching which profile is active - all without re-flashing the
// sketch. See ActionCodec.h for the small text format used in each field.
//
// The AP shuts itself off AP_TIMEOUT_MS after boot, provided nobody is
// connected at that point; if a browser is still connected, the AP stays
// up until that client disconnects, then shuts down.
class WebConfigServer
{
public:
    void begin();
    void update();

private:
    WebServer server{80};

    uint32_t apStartTime = 0;
    bool apActive = false;
    bool timeoutElapsed = false;

    void handleRoot();
    void handleActivate();
    void handleProfileGet();
    void handleProfileSave();
    void handleNotFound();

    void shutdownAP();

    String pageHeader(const char* title) const;
    String pageFooter() const;

    // Reads/validates the "profile" query or form argument. Sets ok=false
    // (and returns 0) if it's missing or out of range.
    int profileIndexFromRequest(bool& ok) const;
};

extern WebConfigServer WebConfigServerInstance;

#endif
