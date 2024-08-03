#ifndef _SSOCK_TAGS_
#define _SSOCK_TAGS_
#include "sock_libs.h"

_SEWEEX_BEGIN

#define _TAG : public _Tag_base

struct _Tag_base {};

struct NullTag _TAG {};

struct ClientTag _TAG {};
struct ServerTag _TAG {};
typedef ClientTag Client;
typedef ServerTag Server;

struct TCPTag _TAG {};
struct UDPTag _TAG {};
typedef TCPTag TCP;
typedef UDPTag UDP;

struct NonCopyTag _TAG {
	NonCopyTag() = default;
	NonCopyTag(const NonCopyTag&) = delete;
	NonCopyTag& operator=(const NonCopyTag&) = delete;
};

template<typename _Ty> 
constexpr bool is_tag_v = _STD is_base_of<_Tag_base, _Ty>::value;

_SEWEEX_END
#endif