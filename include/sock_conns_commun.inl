#if defined(_SSOCK_CONNS_) and !defined(_SSOCK_CONNS_COMMUN_)
#define _SSOCK_CONNS_COMMUN_

template<typename _ConnTag, typename _ProtTag>
template<typename _CharTy>
inline _STD basic_string<_CharTy> _SEWEEX Connection<_ConnTag, _ProtTag>::Receive()
{
	using _Str_type = _STD basic_string<_CharTy>;

	_Str_type Result;
	_Str_type Buff;

	do
		Result += Buff = Receive<_CharTy>(DEFAULT_BUFFER_SIZE);
	while (!Buff.empty());

	return Result;
}

template<typename _ConnTag, typename _ProtTag>
template<typename _CharTy>
inline _STD basic_string<_CharTy> _SEWEEX Connection<_ConnTag, _ProtTag>::Receive(size_t _CharsNum)
{
	using _Str_type			= _STD basic_string<_CharTy>;
	size_t BytesToReceive	= _CharsNum * sizeof(_CharTy);
	int BytesReceived		= SOCKET_ERROR;

	_STD memset(_BufferPtr, 0, DEFAULT_BUFFER_SIZE);

	if (BytesToReceive > DEFAULT_BUFFER_SIZE) 
	{
		if (BytesReceived = recv(_Socket, _BufferPtr, DEFAULT_BUFFER_SIZE, 0) == SOCKET_ERROR)
			_STD _Xruntime_error(RECEIVE_SOCKET_ERROR);

		return _Str_type((_CharTy*)_BufferPtr, BytesReceived) + Receive<_CharTy>(_CharsNum - DEFAULT_BUFFER_SIZE);
	}
	else {
		if (BytesReceived = recv(_Socket, _BufferPtr, _CharsNum, 0) == SOCKET_ERROR)
			_STD _Xruntime_error(RECEIVE_SOCKET_ERROR);

		return _Str_type(_BufferPtr, BytesReceived);
	}
}

template<typename _ConnTag, typename _ProtTag>
template<typename _CharTy>
inline void _SEWEEX Connection<_ConnTag, _ProtTag>::Send(const _STD basic_string<_CharTy>& _Msg)
{
	int BytesSended = send(_Socket, (const char*)_Msg.c_str(),
		min((_Msg.size() + 1) * sizeof(_CharTy), DEFAULT_BUFFER_SIZE), 0);

	if (BytesSended == SOCKET_ERROR)
		_STD _Xruntime_error(SEND_SOCKET_ERROR);
}

#endif