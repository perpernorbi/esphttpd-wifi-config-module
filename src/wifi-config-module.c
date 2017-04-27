#include <esp8266.h>
#include "httpd.h"
#include "httpdespfs.h"
#include "cgiwifi.h"
#include "cgiflash.h"
#include "auth.h"
#include "espfs.h"
#include "captdns.h"
#include "webpages-espfs.h"
#include "cgiwebsocket.h"
#include "json.h"


int ICACHE_FLASH_ATTR wifi_module_cgiWiFiStatus (HttpdConnData *connData)
{
    httpdStartResponse(connData, 200);
    httpdHeader(connData, "Content-Type", "text/json");
    httpdEndHeaders(connData);

    char buff[1024];
    buff[0] = 0;
    JSONBeginObject(buff);
    switch (wifi_get_opmode()) {
    case 1:
        JSONAddKeyValuePairStr(buff, "WiFiMode", "Client");
        break;
    case 2:
        JSONAddKeyValuePairStr(buff, "WiFiMode", "SoftAP");
        break;
    case 3:
        JSONAddKeyValuePairStr(buff, "WiFiMode", "STA+AP");
        break;
    }

    struct station_config stconf;
    wifi_station_get_config(&stconf);

    JSONAddKeyValuePairStr(buff, "currSsid", (const char*)stconf.ssid);

    struct ip_info info;
    wifi_get_ip_info(0, &info);
    JSONAddKey(buff, "network");
    JSONBeginObject(buff);
    JSONAddKeyValuePairIpAddr(buff, "ip", info.ip);
    JSONAddKeyValuePairIpAddr(buff, "gw", info.gw);
    JSONAddKeyValuePairIpAddr(buff, "netmask", info.netmask);
    JSONEndObject(buff);

    httpdSend(connData, buff, -1);
    return HTTPD_CGI_DONE;
}

HttpdBuiltInUrl wifi_module_builtInUrls[]={
    {"/wifi", cgiRedirect, "/wifi/wifi.tpl"},
    {"/wifi/", cgiRedirect, "/wifi/wifi.tpl"},
    {"/wifi/wifiscan.cgi", cgiWiFiScan, NULL},
    {"/wifi/wifi.tpl", cgiEspFsTemplate, tplWlan},
    {"/wifi/connect.cgi", cgiWiFiConnect, NULL},
    {"/wifi/connstatus.cgi", cgiWiFiConnStatus, NULL},
    {"/wifi/wifistatus.cgi", wifi_module_cgiWiFiStatus, NULL},
    {"/wifi/setmode.cgi", cgiWiFiSetMode, NULL},
    {NULL, NULL, NULL}
};
