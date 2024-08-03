#ifndef _SSOCK_CONNS_
#define _SSOCK_CONNS_

#include "sock_libs.h"
#include "sock_errmsg.h"
#include "sock_traits.h"
#include "sock_info.h"

_SEWEEX_BEGIN

class _Connection_base abstract 
	: public NonCopyTag {
protected:

	static WSADATA*				WSAPI_DATA;
	static unsigned short		NUM_OF_SOCKETS;
	static constexpr size_t		DEFAULT_BUFFER_SIZE = 512;

	SOCKET _Socket;
	char * _BufferPtr;
	size_t _BufferSize;

	bool isBadSocket() const noexcept {
		return _Socket == INVALID_SOCKET;
	}

	void AllocBuffer(size_t _Size) {
		_BufferPtr = new char[_BufferSize = _Size] {};
	}

	void ReleaseBuffer() {
		delete[] _BufferPtr;
	}

public:

	size_t BufferSize() {
		return _BufferSize;
	}

	size_t ResizeBuffer(size_t _NewSize) {
		if (_NewSize == 0)
			_STD _Xinvalid_argument(MAKING_ZERO_SIZE_ARRAY);

		ReleaseBuffer();
		AllocBuffer(_NewSize);
	}

	static void WSAInit() {
		WSAPI_DATA = new WSADATA;

		if (WSAStartup(MAKEWORD(2,2), WSAPI_DATA) != 0)
			_STD _Xruntime_error(CREATION_WSADATA_FAILED);
	}

	static void WSATerminate() {
		if (WSACleanup() != 0)
			_STD _Xruntime_error(CLOSING_WSADATA_FAILED);

		delete WSAPI_DATA;
	}
};

WSADATA*		_Connection_base::WSAPI_DATA = nullptr;
unsigned short	_Connection_base::NUM_OF_SOCKETS = 0;

template<typename _ConnTag, typename _ProtTag>
class Connection : public _Connection_base
{
	static_assert(is_tag_v<_ConnTag>, "bad '_ConnTag'");
	static_assert(is_tag_v<_ProtTag>, "bad '_ProtTag'");

	using _Conn_traits = _Connection_traits<_ConnTag, _ProtTag>;

public:

	Connection(const SocketInfo& _Info) {
		if (NUM_OF_SOCKETS == 0)
			WSAInit();

		AllocBuffer(DEFAULT_BUFFER_SIZE);

		_Socket = _Conn_traits::MakeSocket(
			_Info.GetIP().str().c_str(),
			_STD to_string(_Info.GetPort()).c_str()
		);

		if (isBadSocket()) 
			_STD _Xruntime_error(CREATION_SOCKET_FAILED);

		NUM_OF_SOCKETS++;
	}

	~Connection() {
		_Conn_traits::CloseSocket(_Socket);

		if (--NUM_OF_SOCKETS == 0)
			WSATerminate();

		ReleaseBuffer();
	}

	template<typename _CharTy> _STD basic_string<_CharTy> Receive();
	template<typename _CharTy> _STD basic_string<_CharTy> Receive(size_t _CharsNum);
	template<typename _CharTy> void Send(const _STD basic_string<_CharTy>& _Msg);
};

#include "sock_conns_commun.inl"

using ClientTCP = Connection<ClientTag, TCPTag>;
using ServerTCP = Connection<ServerTag, TCPTag>;

using ClientUDP = Connection<ClientTag, UDPTag>;
using ServerUDP = Connection<ServerTag, UDPTag>;

_SEWEEX_END
#endif