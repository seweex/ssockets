#ifndef _SSOCK_TRAITS_
#define _SSOCK_TRAITS_
#include "sock_libs.h"
#include "sock_errmsg.h"
#include "sock_tags.h"

_SEWEEX_BEGIN

template<typename, typename>
class Connection;

template<typename _ConnTag, typename _ProtTag>
class _Connection_traits;

template<typename _ProtTag>
class _Protocol_traits;

template<typename _ProtTag>
class _Connection_traits<Client, _ProtTag>
{
	static SOCKET MakeSocket(LPCSTR _Ip, LPCSTR _Port)
	{
		addrinfo	hints;
		addrinfo	* result{};

		_STD memset(&hints, 0, sizeof hints);

		hints.ai_family		= AF_INET;
		hints.ai_socktype	= _Protocol_traits<_ProtTag>::SockType;
		hints.ai_protocol	= _Protocol_traits<_ProtTag>::Protocol;

		if (getaddrinfo(_Ip, _Port, &hints, &result) != 0)
			_STD _Xruntime_error(GET_ADDR_INFO_FAILED);

		SOCKET _Sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

		if (_Sock == INVALID_SOCKET)
			_STD _Xruntime_error(CREATION_SOCKET_FAILED);

		if (connect(_Sock, result->ai_addr, (int)result->ai_addrlen) != 0)
			_STD _Xruntime_error(CONNECTING_SOCKET_FAILED);

		freeaddrinfo(result);
		return _Sock;
	}

	static void CloseSocket(SOCKET _Sock) {
		closesocket(_Sock);
	}

public: 

	friend Connection<Client, _ProtTag>;
};

template<typename _ProtTag>
class _Connection_traits<Server, _ProtTag>
{
	static SOCKET MakeSocket(LPCSTR _Ip, LPCSTR _Port)
	{
		addrinfo	hints;
		addrinfo	* result{};

		_STD memset(&hints, 0, sizeof hints);

		hints.ai_family = AF_INET;
		hints.ai_socktype = _Protocol_traits<_ProtTag>::SockType;
		hints.ai_protocol = _Protocol_traits<_ProtTag>::Protocol;
		hints.ai_flags = AI_PASSIVE;

		if (getaddrinfo(0, _Port, &hints, &result) != 0)
			_STD _Xruntime_error(GET_ADDR_INFO_FAILED);

		SOCKET _Sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

		if (_Sock == INVALID_SOCKET)
			_STD _Xruntime_error(CREATION_SOCKET_FAILED);

		if (bind(_Sock, result->ai_addr, (int)result->ai_addrlen) != 0)
			_STD _Xruntime_error(BINDING_SOCKET_FAILED);

		if (listen(_Sock, SOMAXCONN) != 0)
			_STD _Xruntime_error(LISTENING_SOCKET_FAILED);

		SOCKET _ClientSock = accept(_Sock, 0, 0);
		closesocket(_Sock);
		freeaddrinfo(result);
		return _ClientSock;
	}

	static void CloseSocket(SOCKET _Sock) {
		shutdown(_Sock, SD_SEND);
	}

public:

	friend Connection<Server, _ProtTag>;
};

template<> class _Protocol_traits<TCP> 
{
	static constexpr int SockType = SOCK_STREAM;
	static constexpr int Protocol = IPPROTO_TCP;
	
public:

	friend _Connection_traits<Server, TCP>;
	friend _Connection_traits<Client, TCP>;
};

template<> class _Protocol_traits<UDP>
{
	static constexpr int SockType = SOCK_STREAM;
	static constexpr int Protocol = IPPROTO_UDP;

public:

	friend _Connection_traits<Server, UDP>;
	friend _Connection_traits<Client, UDP>;
};

_SEWEEX_END
#endif