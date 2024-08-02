#ifndef _SSOCK_LIBS_
#define _SSOCK_LIBS_
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <string>
#include <array>

#pragma comment(lib, "ws2_32.lib")

#define _SEWEEX_BEGIN	namespace seweex {
#define _SEWEEX_END		}
#define _SEWEEX			seweex::

#endif