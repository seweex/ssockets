#ifndef _SSOCK_TAGS_
#define _SSOCK_TAGS_
#include "sock_libs.h"

_SEWEEX_BEGIN

struct NullTag {};

struct ClientTag {};
struct ServerTag {};
typedef ClientTag Client;
typedef ServerTag Server;

struct TCPTag {};
struct UDPTag {};
typedef TCPTag TCP;
typedef UDPTag UDP;

struct NonCopyTag {
	NonCopyTag() = default;
	NonCopyTag(const NonCopyTag&) = delete;
	NonCopyTag& operator=(const NonCopyTag&) = delete;
};

_SEWEEX_END
#endif