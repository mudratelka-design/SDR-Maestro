//=============================================================================
// File: WebConfigServer.cpp
// Commit: 11
// Version: 0.3.0
//=============================================================================

#include "WebConfigServer.h"

#include <stdio.h>
#include <WiFi.h>

#include "ProfileManager.h"
#include "ActionCodec.h"
#include "Logger.h"
#include "Events.h"

WebConfigServer WebConfigServerInstance;

namespace
{
    const char* EVENT_FIELD_SUFFIX[4] = { "cw", "ccw", "sp", "lp" };

    EventType eventTypeForSlot(uint8_t slot)
    {
        switch (slot)
        {
            case 0: return EventType::EncoderClockwise;
            case 1: return EventType::EncoderCounterClockwise;
            case 2: return EventType::ButtonPressed;
            case 3: return EventType::ButtonLongPressed;
            default: return EventType::None;
        }
    }
}

void WebConfigServer::begin()
{
    WiFi.mode(WIFI_AP);
    WiFi.softAP(AP_SSID, AP_PASSWORD);

    server.on("/", HTTP_GET, [this]() { handleRoot(); });
    server.on("/activate", HTTP_POST, [this]() { handleActivate(); });
    server.on("/profile", HTTP_GET, [this]() { handleProfileGet(); });
    server.on("/profile", HTTP_POST, [this]() { handleProfileSave(); });
    server.onNotFound([this]() { handleNotFound(); });

    server.begin();

    apStartTime = millis();
    apActive = true;
    timeoutElapsed = false;

    char buf[96];
    snprintf(buf, sizeof(buf), "Config AP \"%s\" is up - connect and open http://%s/ to configure.",
              AP_SSID, WiFi.softAPIP().toString().c_str());
    LoggerInstance.info(buf);
}

void WebConfigServer::update()
{
    if (!apActive)
    {
        return;
    }

    server.handleClient();

    const uint32_t elapsed = millis() - apStartTime;

    if (!timeoutElapsed && elapsed >= AP_TIMEOUT_MS)
    {
        timeoutElapsed = true;
        LoggerInstance.info("Config AP timeout reached; will shut down once no client is connected.");
    }

    if (timeoutElapsed && WiFi.softAPgetStationNum() == 0)
    {
        shutdownAP();
    }
}

void WebConfigServer::shutdownAP()
{
    server.stop();
    WiFi.softAPdisconnect(true);
    WiFi.mode(WIFI_OFF);
    apActive = false;

    LoggerInstance.info("Config AP turned off.");
}

String WebConfigServer::pageHeader(const char* title) const
{
    String html = "<!DOCTYPE html><html><head><meta charset='utf-8'>"
                  "<meta name='viewport' content='width=device-width, initial-scale=1'>"
                  "<title>";
    html += title;
    html += "</title><style>"
            "body{font-family:sans-serif;max-width:720px;margin:20px auto;padding:0 12px;}"
            "table{border-collapse:collapse;width:100%;margin-bottom:12px;}"
            "th,td{border:1px solid #ccc;padding:6px;text-align:left;font-size:0.95em;}"
            "input[type=text]{width:100%;box-sizing:border-box;font-size:0.95em;}"
            "th{background:#eee;}"
            ".btn{display:inline-block;padding:8px 14px;margin:4px 4px 4px 0;background:#2b6cb0;"
            "color:#fff;text-decoration:none;border-radius:4px;border:none;font-size:1em;cursor:pointer;}"
            ".btn.grey{background:#718096;}"
            ".active{font-weight:bold;color:#2b6cb0;}"
            "code{background:#f0f0f0;padding:1px 4px;border-radius:3px;}"
            "</style></head><body><h2>";
    html += title;
    html += "</h2>";
    return html;
}

String WebConfigServer::pageFooter() const
{
    return "</body></html>";
}

int WebConfigServer::profileIndexFromRequest(bool& ok) const
{
    ok = false;

    if (!server.hasArg("profile"))
    {
        return 0;
    }

    const int p = server.arg("profile").toInt();

    if (p < 0 || p >= PROFILE_COUNT)
    {
        return 0;
    }

    ok = true;
    return p;
}

void WebConfigServer::handleRoot()
{
    String html = pageHeader("SDR Maestro Config");

    html += "<p>Active profile: <span class='active'>";
    html += ProfileManagerInstance.profileName(ProfileManagerInstance.activeProfileIndex());
    html += "</span></p>";

    html += "<table><tr><th>Profile</th><th>Status</th><th></th></tr>";

    for (uint8_t p = 0; p < PROFILE_COUNT; p++)
    {
        html += "<tr><td>";
        html += ProfileManagerInstance.profileName(p);
        html += "</td><td>";

        if (p == ProfileManagerInstance.activeProfileIndex())
        {
            html += "active now";
        }
        else
        {
            html += "<form method='POST' action='/activate' style='margin:0;'>";
            html += "<input type='hidden' name='profile' value='";
            html += String(p);
            html += "'><button class='btn' type='submit'>Activate</button></form>";
        }

        html += "</td><td><a class='btn grey' href='/profile?profile=";
        html += String(p);
        html += "'>Edit</a></td></tr>";
    }

    html += "</table>";
    html += "<p>Tip: short-press an encoder within 5 seconds of power-on to make "
            "that encoder's numbered profile active for that session, without using this page.</p>";
    html += pageFooter();

    server.send(200, "text/html", html);
}

void WebConfigServer::handleActivate()
{
    if (server.hasArg("profile"))
    {
        const int p = server.arg("profile").toInt();

        if (p >= 0 && p < PROFILE_COUNT)
        {
            ProfileManagerInstance.setActiveProfile(static_cast<uint8_t>(p));
        }
    }

    server.sendHeader("Location", "/");
    server.send(303, "text/plain", "");
}

void WebConfigServer::handleProfileGet()
{
    bool ok = false;
    const int profile = profileIndexFromRequest(ok);

    if (!ok)
    {
        server.sendHeader("Location", "/");
        server.send(303, "text/plain", "");
        return;
    }

    String html = pageHeader(ProfileManagerInstance.profileName(static_cast<uint8_t>(profile)));

    html += "<p>Format for each box: <code>NONE</code>, <code>KEY:UP_ARROW</code>, "
            "<code>KEY:TAB+SHIFT</code>, <code>CHAR:m</code>, or <code>MEDIA:VOLUME_UP</code>. "
            "Hex codes such as <code>KEY:0x29</code> also work. Leave blank for no action.</p>";

    html += "<form method='POST' action='/profile'>";
    html += "<input type='hidden' name='profile' value='";
    html += String(profile);
    html += "'>";

    html += "<table><tr><th>Encoder</th><th>Turn Right</th><th>Turn Left</th>"
            "<th>Short Press</th><th>Long Press</th></tr>";

    for (uint8_t e = 0; e < ENCODER_COUNT; e++)
    {
        html += "<tr><td>#";
        html += String(e + 1);
        html += "</td>";

        for (uint8_t slot = 0; slot < 4; slot++)
        {
            const KeyAction action = ProfileManagerInstance.getProfileAction(
                static_cast<uint8_t>(profile), e, eventTypeForSlot(slot));

            html += "<td><input type='text' name='e";
            html += String(e);
            html += "_";
            html += EVENT_FIELD_SUFFIX[slot];
            html += "' value='";
            html += ActionCodec::toString(action);
            html += "'></td>";
        }

        html += "</tr>";
    }

    html += "</table>";
    html += "<p><button class='btn' type='submit'>Save</button> "
            "<a class='btn grey' href='/'>Back</a></p>";
    html += "</form>";
    html += pageFooter();

    server.send(200, "text/html", html);
}

void WebConfigServer::handleProfileSave()
{
    bool ok = false;
    const int profile = profileIndexFromRequest(ok);

    if (!ok)
    {
        server.sendHeader("Location", "/");
        server.send(303, "text/plain", "");
        return;
    }

    KeyAction clockwise[ENCODER_COUNT];
    KeyAction counterClockwise[ENCODER_COUNT];
    KeyAction shortPress[ENCODER_COUNT];
    KeyAction longPress[ENCODER_COUNT];

    for (uint8_t e = 0; e < ENCODER_COUNT; e++)
    {
        const String fieldBase = String("e") + String(e) + String("_");

        clockwise[e]        = ActionCodec::parse(server.arg(fieldBase + "cw"));
        counterClockwise[e] = ActionCodec::parse(server.arg(fieldBase + "ccw"));
        shortPress[e]       = ActionCodec::parse(server.arg(fieldBase + "sp"));
        longPress[e]        = ActionCodec::parse(server.arg(fieldBase + "lp"));
    }

    ProfileManagerInstance.setProfileActions(
        static_cast<uint8_t>(profile), clockwise, counterClockwise, shortPress, longPress);

    server.sendHeader("Location", String("/profile?profile=") + String(profile));
    server.send(303, "text/plain", "");
}

void WebConfigServer::handleNotFound()
{
    server.send(404, "text/plain", "Not found");
}
