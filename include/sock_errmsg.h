#ifndef _SSOCK_ERRMSG_
#define _SSOCK_ERRMSG_
#include "sock_libs.h"

_SEWEEX_BEGIN

static constexpr char GET_ADDR_INFO_FAILED[]	= "failed to get addrinfo";
static constexpr char CREATION_SOCKET_FAILED[]	= "failed to create a socket";
static constexpr char CLOSING_SOCKET_FAILED[]	= "failed to close a socket";
static constexpr char BINDING_SOCKET_FAILED[]	= "failed to bind a socket";
static constexpr char LISTENING_SOCKET_FAILED[]	= "failed to listen a socket";
static constexpr char CONNECTING_SOCKET_FAILED[]	= "failed to listen a socket";
static constexpr char CREATION_WSADATA_FAILED[]	= "failed to create a wsadata";
static constexpr char CLOSING_WSADATA_FAILED[]	= "failed to close a wsadata";
static constexpr char RECEIVE_SOCKET_ERROR[]	= "failed to recv msg from a socket";
static constexpr char SEND_SOCKET_ERROR[]		= "failed to send msg to the socket";
static constexpr char TRYING_TO_GET_SO_MANY_BYTES[] = "so many bytes want to get";
static constexpr char GETTING_HOST_IP_ERROR[] = "failed to get host ip";
static constexpr char MAKING_ZERO_SIZE_ARRAY[] = "cannot make zero size array";

_SEWEEX_END
#endif