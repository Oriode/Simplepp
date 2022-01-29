namespace Network {

	template<typename T>
	inline HTTPQueryT<T>::HTTPQueryT() :
		bHeaderNeedFormat(false) {}

	template<typename T>
	inline HTTPQueryT<T>::~HTTPQueryT() {

	}

	template<typename T>
	inline HTTPParam* HTTPQueryT<T>::setHeaderParam(const StringASCII& paramName, const StringASCII& paramValue) {
		this->bHeaderNeedFormat = true;
		return ParamContainerT<StringASCII, StringASCII>::setParam(paramName, paramValue);
	}

	template<typename T>
	inline const HTTPParam* HTTPQueryT<T>::getHeaderParam(const StringASCII& paramName) const {
		return ParamContainerT<StringASCII, StringASCII>::getParam(paramName);
	}

	template<typename T>
	inline HTTPParam* HTTPQueryT<T>::getHeaderParam(const StringASCII& paramName) {
		return ParamContainerT<StringASCII, StringASCII>::getParam(paramName);
	}

	template<typename T>
	inline void HTTPQueryT<T>::setProtocol(const StringASCII& protocol) {
		this->protocolStr = protocol;
	}

	template<typename T>
	inline void HTTPQueryT<T>::setContent(const StringASCII& content) {
		this->contentStr = content;
	}

	template<typename T>
	inline const StringASCII& HTTPQueryT<T>::getProtocol() const {
		return this->protocolStr;
	}

	template<typename T>
	inline const StringASCII& HTTPQueryT<T>::getContent() const {
		return this->contentStr;
	}

	template<typename T>
	template<typename EndFunc>
	inline bool HTTPQueryT<T>::parseQuery(const StringASCII::ElemType** itP, const EndFunc& endFunc) {
		if ( !parseQueryHeader(itP, endFunc) ) {
			return false;
		}

		const StringASCII::ElemType*& it(*itP);
		for ( ; ( *it == StringASCII::ElemType('\n') || *it == StringASCII::ElemType('\r') ) && !endFunc(it); it++ );

		const StringASCII::ElemType* contentStrBeginIt(it);
		for ( ; !endFunc(it); it++ );
		this->contentStr = StringASCII(contentStrBeginIt, Size(it - contentStrBeginIt));

		return true;
	}

	template<typename T>
	inline void HTTPQueryT<T>::formatQuery(StringASCII* outputStr) const {
		StringASCII& str(*outputStr);

		const_cast< HTTPQueryT<T>* >( this )->formatQueryHeader();

		str << this->headerStr;
		str << StringASCII::ElemType('\r');
		str << StringASCII::ElemType('\n');
		str << this->contentStr;
	}

	template<typename T>
	inline void HTTPQueryT<T>::formatQueryHeader() {
		if ( this->bHeaderNeedFormat ) {

			this->headerStr.clear();

			for ( typename Vector<HTTPParam*>::Iterator it(this->paramVector.getBegin()); it != this->paramVector.getEnd(); this->paramVector.iterate(&it) ) {
				const HTTPParam* param(this->paramVector.getValueIt(it));

				this->headerStr << param->getName();
				this->headerStr << StringASCII::ElemType(':');
				this->headerStr << StringASCII::ElemType(' ');
				this->headerStr << param->getValue();
				this->headerStr << StringASCII::ElemType('\r');
				this->headerStr << StringASCII::ElemType('\n');
			}

			this->bHeaderNeedFormat = false;
		}
	}

	template<typename T>
	template<typename EndFunc>
	inline bool HTTPQueryT<T>::parseQueryHeader(const StringASCII::ElemType** itP, const EndFunc& endFunc) {
		struct FunctorNewLine {
			FunctorNewLine(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::ElemType* it) const { return *it == StringASCII::ElemType('\r') || *it == StringASCII::ElemType('\n') || endFunc(it); }

			const EndFunc& endFunc;
		};
		struct FunctorParamName {
			FunctorParamName(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::ElemType* it) const { return *it == StringASCII::ElemType(':') || *it == StringASCII::ElemType(' ') || *it == StringASCII::ElemType('\r') || *it == StringASCII::ElemType('\n') || endFunc(it); }

			const EndFunc& endFunc;
		};
		struct FunctorSpace {
			FunctorSpace(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::ElemType* it) const { return *it != StringASCII::ElemType(' ') || *it == StringASCII::ElemType('\r') || *it == StringASCII::ElemType('\n') || endFunc(it); }

			const EndFunc& endFunc;
		};

		static FunctorNewLine functorNewLine(endFunc);
		static FunctorParamName functorParamName(endFunc);
		static FunctorSpace functorSpace(endFunc);

		const StringASCII::ElemType*& it(*itP);
		while ( true ) {
			// Skip spaces.
			for ( ; !functorSpace(it); it++ );

			const StringASCII::ElemType* paramNameBeginIt(it);
			for ( ; !functorParamName(it); it++ );
			const StringASCII::ElemType* paramNameEndIt(it);

			if ( *it == StringASCII::ElemType(':') ) {
				it++;
			}

			// Skip spaces.
			for ( ; !functorSpace(it); it++ );

			const StringASCII::ElemType* paramValueBeginIt(it);
			for ( ; !functorNewLine(it); it++ );
			const StringASCII::ElemType* paramValueEndIt(it);

			if ( paramNameBeginIt == paramNameEndIt || paramValueBeginIt == paramValueEndIt ) {
				error("HTTP header syntax error.");
				return false;
			}

			StringASCII newParamName(paramNameBeginIt, Size(paramNameEndIt - paramNameBeginIt));
			StringASCII newParamValue(paramValueBeginIt, Size(paramValueEndIt - paramValueBeginIt));

			HTTPParam* newParam(new HTTPParam(newParamName, newParamValue));

			this->paramVector.push(newParam);

			// End condition.
			if ( *it == StringASCII::ElemType('\r') && !endFunc(it) ) {
				it++;
				if ( *it == StringASCII::ElemType('\n') && !endFunc(it) ) {
					it++;
				}
				if ( *it == StringASCII::ElemType('\r') && !endFunc(it) ) {
					it++;
					if ( *it == StringASCII::ElemType('\n') && !endFunc(it) ) {
						it++;
					}
					break;
				}
				continue;
			}

			break;
		}

		return true;
	}

	template<typename T>
	inline HTTPResponseT<T>::HTTPResponseT() {}

	template<typename T>
	template<typename EndFunc>
	inline HTTPResponseT<T>::HTTPResponseT(const StringASCII::ElemType** itP, const EndFunc& endFunc) {
		parseQuery(itP, endFunc);
	}

	template<typename T>
	template<typename EndFunc>
	inline bool HTTPResponseT<T>::parseQuery(const StringASCII::ElemType** itP, const EndFunc& endFunc) {
		if ( !parseQueryTitle(itP, endFunc) ) {
			return false;
		}
		if ( !HTTPQueryT<T>::parseQuery(itP, endFunc) ) {
			return false;
		}
		return true;
	}

	template<typename T>
	inline StringASCII HTTPResponseT<T>::formatQuery() const {
		StringASCII outputStr;
		outputStr.reserve(10000);

		formatQuery(&outputStr);
	}

	template<typename T>
	inline void HTTPResponseT<T>::formatQuery(StringASCII* outputStr) const {
		formatQueryTitle(outputStr);
		HTTPQueryT<T>::formatQuery(outputStr);
	}

	template<typename T>
	inline void HTTPResponseT<T>::setStatusCode(Size statusCode) {
		this->statusCode = statusCode;
	}

	template<typename T>
	inline void HTTPResponseT<T>::setStatusMessage(const StringASCII& statusMessage) {
		this->statusMessage = statusMessage;
	}

	template<typename T>
	inline const Size HTTPResponseT<T>::getStatusCode() const {
		return this->statusCode;
	}

	template<typename T>
	inline const StringASCII& HTTPResponseT<T>::getStatusMessage() const {
		return this->statusMessage;
	}

	template<typename T>
	template<typename EndFunc>
	inline bool HTTPResponseT<T>::parseQueryTitle(const StringASCII::ElemType** itP, const EndFunc& endFunc) {
		struct FunctorNewLine {
			FunctorNewLine(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::ElemType* it) const { return *it == StringASCII::ElemType('\r') || *it == StringASCII::ElemType('\n') || endFunc(it); }

			const EndFunc& endFunc;
		};
		struct FunctorWord {
			FunctorWord(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::ElemType* it) const { return *it == StringASCII::ElemType(' ') || *it == StringASCII::ElemType('\r') || *it == StringASCII::ElemType('\n') || endFunc(it); }

			const EndFunc& endFunc;
		};
		struct FunctorSpace {
			FunctorSpace(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::ElemType* it) const { return *it != StringASCII::ElemType(' ') || *it == StringASCII::ElemType('\r') || *it == StringASCII::ElemType('\n') || endFunc(it); }

			const EndFunc& endFunc;
		};

		static FunctorNewLine functorNewLine(endFunc);
		static FunctorWord functorWord(endFunc);
		static FunctorSpace functorSpace(endFunc);

		const StringASCII::ElemType*& it(*itP);
		// Skip spaces.
		for ( ; !functorSpace(it); it++ );

		const StringASCII::ElemType* protocolStrBeginIt(it);
		for ( ; !functorWord(it); it++ );
		const StringASCII::ElemType* protocolStrEndIt(it);

		// Skip spaces.
		for ( ; !functorSpace(it); it++ );

		Size statusCode(StringASCII::toULongLong(&it, 10, functorWord));

		// Skip spaces.
		for ( ; !functorSpace(it); it++ );

		const StringASCII::ElemType* statusMessageBeginIt(it);
		for ( ; !functorWord(it); it++ );
		const StringASCII::ElemType* statusMessageEndIt(it);

		// Skip up to end line.
		for ( ; !functorNewLine(it); it++ );

		// End condition.
		if ( *it == StringASCII::ElemType('\r') && !endFunc(it) ) {
			it++;
			if ( *it == StringASCII::ElemType('\n') && !endFunc(it) ) {
				it++;
			}
		}

		if ( protocolStrBeginIt == protocolStrEndIt ) {
			error("HTTP response syntax error.");
			return false;
		}

		StringASCII protocolStr(protocolStrBeginIt, Size(protocolStrEndIt - protocolStrBeginIt));
		StringASCII statusMessage(statusMessageBeginIt, Size(statusMessageEndIt - statusMessageBeginIt));

		this->protocolStr = protocolStr;
		this->statusCode = statusCode;
		this->statusMessage = statusMessage;

		return true;
	}

	template<typename T>
	inline void HTTPResponseT<T>::formatQueryTitle(StringASCII* outputStr) const {
		StringASCII& str(*outputStr);

		str << this->protocolStr;
		str << StringASCII::ElemType(' ');
		str << this->statusCode;
		str << StringASCII::ElemType(' ');
		str << this->statusMessage;
		str << StringASCII::ElemType('\r');
		str << StringASCII::ElemType('\n');
	}

	template<typename T>
	inline HTTPRequestT<T>::HTTPRequestT() {
		HTTPParam* hostParam(new HTTPParam(StringASCII("Host")));
		addParam(hostParam);

		this->hostParam = hostParam;
	}

	template<typename T>
	template<typename EndFunc>
	inline HTTPRequestT<T>::HTTPRequestT(const StringASCII::ElemType** itP, const EndFunc& endFunc) :
		hostParam(NULL)
	{
		parseQuery(itP, endFunc);
	}

	template<typename T>
	template<typename EndFunc>
	inline bool HTTPRequestT<T>::parseQuery(const StringASCII::ElemType** itP, const EndFunc& endFunc) {
		if ( !parseQueryTitle(itP, endFunc) ) {
			return false;
		}
		if ( !HTTPQueryT<T>::parseQuery(itP, endFunc) ) {
			return false;
		}
		return true;
	}

	template<typename T>
	template<typename EndFunc>
	inline bool HTTPRequestT<T>::parseQueryTitle(const StringASCII::ElemType** itP, const EndFunc& endFunc) {
		struct FunctorNewLine {
			FunctorNewLine(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::ElemType* it) const { return *it == StringASCII::ElemType('\r') || *it == StringASCII::ElemType('\n') || endFunc(it); }

			const EndFunc& endFunc;
		};
		struct FunctorWord {
			FunctorWord(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::ElemType* it) const { return *it == StringASCII::ElemType(' ') || *it == StringASCII::ElemType('\r') || *it == StringASCII::ElemType('\n') || endFunc(it); }

			const EndFunc& endFunc;
		};
		struct FunctorSpace {
			FunctorSpace(const EndFunc& endFunc) :
				endFunc(endFunc) {}
			bool operator()(const typename StringASCII::ElemType* it) const { return *it != StringASCII::ElemType(' ') || *it == StringASCII::ElemType('\r') || *it == StringASCII::ElemType('\n') || endFunc(it); }

			const EndFunc& endFunc;
		};

		static FunctorNewLine functorNewLine(endFunc);
		static FunctorWord functorWord(endFunc);
		static FunctorSpace functorSpace(endFunc);

		const StringASCII::ElemType*& it(*itP);

		// Skip spaces.
		for ( ; !functorSpace(it); it++ );

		const StringASCII::ElemType* methodStrBeginIt(it);
		for ( ; !functorWord(it); it++ );
		const StringASCII::ElemType* methodStrEndIt(it);

		if ( methodStrBeginIt == methodStrEndIt ) {
			error("HTTP request syntax error : no method.");
			return false;
		}

		// Skip spaces.
		for ( ; !functorSpace(it); it++ );

		if ( !this->url.parse(&it, functorWord) ) {
			return false;
		}

		// Skip spaces.
		for ( ; !functorSpace(it); it++ );

		const StringASCII::ElemType* protocolStrBeginIt(it);
		for ( ; !functorWord(it); it++ );
		const StringASCII::ElemType* protocolStrEndIt(it);

		if ( protocolStrBeginIt == protocolStrEndIt ) {
			error("HTTP request syntax error : no protocol.");
			return false;
		}

		// Skip up to end line.
		for ( ; !functorNewLine(it); it++ );

		// End condition.
		if ( *it == StringASCII::ElemType('\r') && !endFunc(it) ) {
			it++;
			if ( *it == StringASCII::ElemType('\n') && !endFunc(it) ) {
				it++;
			}
		}

		StringASCII methodStr(methodStrBeginIt, Size(methodStrEndIt - methodStrBeginIt));
		StringASCII protocolStr(protocolStrBeginIt, Size(protocolStrEndIt - protocolStrBeginIt));

		this->methodStr = methodStr;
		this->protocolStr = protocolStr;

		return true;
	}

	template<typename T>
	inline StringASCII HTTPRequestT<T>::formatQuery() const {
		StringASCII outputStr;
		outputStr.reserve(10000);

		formatQuery(&outputStr);
	}

	template<typename T>
	inline void HTTPRequestT<T>::formatQuery(StringASCII* outputStr) const {
		formatQueryTitle(outputStr);
		HTTPQueryT<T>::formatQuery(outputStr);
	}

	template<typename T>
	inline void HTTPRequestT<T>::setMethod(const StringASCII& method) {
		this->methodStr = method;
	}

	template<typename T>
	inline void HTTPRequestT<T>::setEndPoint(const UrlT<T>& url) {
		this->url = url;

		updateHostParamValue();
	}

	template<typename T>
	inline void HTTPRequestT<T>::setEndPoint(typename UrlT<T>::Type type, const StringASCII& hostname, const StringASCII& endPointStr, const Vector<HTTPParam>& paramVector) {
		this->url.setType(type);
		this->url.setHostname(hostname);
		this->url.setEndPoint(endPointStr);
		this->url.setParams(paramVector);

		updateHostParamValue();
	}

	template<typename T>
	inline bool HTTPRequestT<T>::setEndPoint(const StringASCII& url) {
		if ( !this->url.parse(url) ) {
			return false;
		}

		updateHostParamValue();

		return true;
	}

	template<typename T>
	inline const StringASCII& HTTPRequestT<T>::getMethod() const {
		return this->methodStr;
	}

	template<typename T>
	inline const UrlT<T>& HTTPRequestT<T>::getEndPoint() const {
		return this->url;
	}

	template<typename T>
	inline void HTTPRequestT<T>::formatQueryTitle(StringASCII* outputStr) const {
		StringASCII& str(*outputStr);

		str << this->methodStr;
		str << StringASCII::ElemType(' ');
		this->url.format(&str);
		// str << this->endPoint.getEndPoint();
		str << StringASCII::ElemType(' ');
		str << this->protocolStr;
		str << StringASCII::ElemType('\r');
		str << StringASCII::ElemType('\n');
	}

	template<typename T>
	inline void HTTPRequestT<T>::updateHostParamValue() {
		if ( this->hostParam ) {
			this->hostParam->setValue(this->url.getHostname());
		} else {
			this->hostParam = setHeaderParam(StringASCII("Host"), this->url.getHostname());
		}
	}

	template<typename T>
	inline HTTPClientT<T>::HTTPClientT() {
		this->request.setMethod(StringASCII("GET"));
		this->request.setProtocol(StringASCII("HTTP/1.1"));

		this->request.setHeaderParam(StringASCII("Accept"), StringASCII("*/*"));
		this->request.setHeaderParam(StringASCII("Connection"), StringASCII("close"));
	}

	template<typename T>
	inline HTTPParam* HTTPClientT<T>::setHeaderParam(const StringASCII& paramName, const StringASCII& paramValue) {
		return this->request.setHeaderParam(paramName, paramValue);
	}

	template<typename T>
	inline HTTPResponseT<T>* HTTPClientT<T>::query(typename UrlT<T>::Type type, const StringASCII& hostname, const StringASCII& endPointStr, const Vector<Param>& urlParams) {
		this->request.setEndPoint(type, hostname, endPointStr, urlParams);

		static StringASCII sendBuffer;
		static char receiveBuffer[ 1000000 ];

		TLSConnectionT<T> connection;

		if ( type == UrlT<T>::Type::HTTPS ) {
			if ( connection.connect(hostname, unsigned short(443), Network::SockType::TCP) ) {

				this->request.formatQuery(&sendBuffer);

				if ( !connection.send(sendBuffer.toCString(), int(sendBuffer.getSize())) ) {
					return NULL;
				}

				int totalReceivedLength(0);
				while ( true ) {
					int receivedLength(connection.receive(receiveBuffer + totalReceivedLength, sizeof(receiveBuffer) - totalReceivedLength));

					if ( receivedLength <= int(0) ) {
						break;
					}

					totalReceivedLength += receivedLength;
				}

				const StringASCII::ElemType* parseIt(receiveBuffer);
				StringASCII::IsEndIterator endFunc(receiveBuffer + totalReceivedLength);
				if ( !this->response.parseQuery(&parseIt, endFunc) ) {
					return NULL;
				}

				return &this->response;
			}
		} else {
			error(String::format("Unsuported query type %.", UrlT<T>::getTypeString(type)));
			return NULL;
		}

		return NULL;
	}

}