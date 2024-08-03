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

_SEWEEX_BEGIN

#if defined(_SSOCK_USE_WSAPI_VER_MJ) and defined(_SSOCK_USE_WSAPI_VER_MN)
	constexpr WORD _WinSockVer = MAKEWORD(_SSOCK_USE_WSAPI_VER_MJ, _SSOCK_USE_WSAPI_VER_MN);
#elif defined(_SSOCK_USE_WSAPI_VER_MJ) != defined(_SSOCK_USE_WSAPI_VER_MN)
	#error "incorrect definition of the wsapi version "
#else
	constexpr WORD _WinSockVer = MAKEWORD(2, 2);
#endif

_SEWEEX_END

#endif