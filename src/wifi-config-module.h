#ifndef WIFICONFIGMODULE_H
#define WIFICONFIGMODULE_H
#include "httpd.h"
#include "cgiwifi.h"
#include "httpdespfs.h"
#include <c_types.h>

int ICACHE_FLASH_ATTR wifi_module_cgiWiFiStatus (HttpdConnData *connData);

extern const HttpdBuiltInUrl wifi_module_builtInUrls[];
#endif // WIFICONFIGMODULE_H
