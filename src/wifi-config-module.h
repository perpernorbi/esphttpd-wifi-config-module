#ifndef WIFICONFIGMODULE_H
#define WIFICONFIGMODULE_H
#include "httpd.h"
#include "cgiwifi.h"
#include "httpdespfs.h"
#include <c_types.h>

int ICACHE_FLASH_ATTR wifi_module_cgiWiFiStatus (HttpdConnData *connData);

extern HttpdBuiltInUrl wifi_module_builtInUrls[];
extern const size_t wifi_module_builtInUrlsSize;
#endif // WIFICONFIGMODULE_H
