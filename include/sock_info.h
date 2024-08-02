#ifndef _SSOCK_INFO_
#define _SSOCK_INFO_
#include "sock_libs.h"
#include "sock_errmsg.h"

_SEWEEX_BEGIN

typedef unsigned short Port;

class IPv4
{
public:

	static constexpr	size_t NUMBER_OF_FIELDS = 4;
	static const		IPv4 LOCALHOST_ADDR;
	static const		IPv4 ANY_ADDR;
	static const		IPv4 ERR_ADDR;

private:

	using field_type = unsigned char;
	using ip_t = _STD array<field_type, NUMBER_OF_FIELDS>;

public:

	IPv4(const _STD string& _HostName) 
		: IPv4(ERR_ADDR) 
	{
		addrinfo* result{};

		if (getaddrinfo(_HostName.c_str(), 0, 0, &result) != 0)
			_STD _Xruntime_error(GETTING_HOST_IP_ERROR);
		
		for (size_t i{}; i < 4; i++)
			_Data[i] = ((BYTE*)(&result->ai_addr->sa_data))[i + 2];
	}

	constexpr IPv4(ip_t&& _Ip)
		: _Data{ _Ip }
	{}

	constexpr IPv4(const ip_t& _Ip)
		: _Data{ _Ip }
	{}

	constexpr IPv4(field_type _b0, field_type _b1, field_type _b2, field_type _b3)
		: _Data{ _b0, _b1, _b2, _b3 }
	{}

	constexpr IPv4(const IPv4&) = default;
	constexpr IPv4(IPv4&&) = default;

	_STD string str() {
		_STD string _Result;

		_Result += _STD to_string(int(_Data[0]));
		_Result += ".";
		_Result += _STD to_string(int(_Data[1]));
		_Result += ".";
		_Result += _STD to_string(int(_Data[2]));
		_Result += ".";
		_Result += _STD to_string(int(_Data[3]));

		return _Result;
	}

private:

	ip_t _Data;
};

constexpr IPv4 IPv4::ERR_ADDR		= { 255,255,255,255 };
constexpr IPv4 IPv4::ANY_ADDR		= { 0,0,0,0 };
constexpr IPv4 IPv4::LOCALHOST_ADDR = { 127,0,0,1 };

class SocketInfo
{
	const IPv4 _Ip;
	const Port _Port;

public:

	constexpr SocketInfo(const IPv4& _IP, Port _PORT)
		: _Ip{ _IP }, _Port{ _PORT }
	{}

	constexpr SocketInfo(IPv4&& _IP, Port _PORT)
		: _Ip{ _IP }, _Port{ _PORT }
	{}

	IPv4 GetIP() const noexcept {
		return _Ip;
	}

	Port GetPort() const noexcept {
		return _Port;
	}
};

_SEWEEX_END
#endif