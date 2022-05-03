#include "HTTPClient.h"
namespace Network {

	template<typename T>
	inline HTTPQueryT<T>::HTTPQueryT() :
		bHeaderNeedFormat(false) {}

	template<typename T>
	inline HTTPQueryT<T>::~HTTPQueryT() {

	}

	template<typename T>
	inline void HTTPQueryT<T>::formatQueryContent(StringASCII* outputStr) const {
		StringASCII& str(*outputStr);

		str << this->contentStr;
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
		if ( content.getSize() != this->contentStr.getSize() ) {
			// Header need to be recomputed as the Content-Size has changed.
			this->bHeaderNeedFormat = true;
		}

		this->contentStr = content;
	}

	template<typename T>
	inline void HTTPQueryT<T>::clearContent() {
		if ( this->contentStr.getSize() ) {
			this->contentStr.clear();

			// Header need to be recomputed as the Content-Size has changed.
			this->bHeaderNeedFormat = true;
		}
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
		if ( !parseQueryContent(itP, endFunc) ) {
			return false;
		}

		return true;
	}

	template<typename T>
	inline void HTTPQueryT<T>::formatQuery(StringASCII* outputStr) const {
		StringASCII& str(*outputStr);

		const_cast< HTTPQueryT<T>* >( this )->formatQueryHeader();

		str << this->headerStr;
		formatQueryContent(outputStr);
	}

	template<typename T>
	inline void HTTPQueryT<T>::formatHeaderParam(StringASCII* outputStr, const ParamT<StringASCII, StringASCII>& param) const {
		StringASCII& str(*outputStr);

		str << param.getName();
		str << StringASCII::ElemType(':');
		str << StringASCII::ElemType(' ');
		str << param.getValue();
		str << StringASCII::ElemType('\r');
		str << StringASCII::ElemType('\n');
	}

	template<typename T>
	inline void HTTPQueryT<T>::formatQueryHeader() {
		if ( this->bHeaderNeedFormat ) {

			this->headerStr.clear();

			for ( typename Vector<HTTPParam*>::Iterator it(this->paramVector.getBegin()); it != this->paramVector.getEnd(); this->paramVector.iterate(&it) ) {
				const HTTPParam* param(this->paramVector.getValueIt(it));

				formatHeaderParam(&this->headerStr, *param);
			}

			if ( this->contentStr.getSize() ) {
				static const ParamT<StringASCII, StringASCII> contentTypeParam(StringASCII("Content-Type"), StringASCII("application/x-www-form-urlencoded"));
				static const StringASCII contentLengthParamName("Content-Length");

				formatHeaderParam(&this->headerStr, contentTypeParam);
				formatHeaderParam(&this->headerStr, ParamT<StringASCII, StringASCII>(contentLengthParamName, StringASCII::toString(this->contentStr.getSize())));
			}

			this->headerStr << StringASCII::ElemType('\r');
			this->headerStr << StringASCII::ElemType('\n');

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

		FunctorNewLine functorNewLine(endFunc);
		FunctorParamName functorParamName(endFunc);
		FunctorSpace functorSpace(endFunc);

		clearParams();

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

			addParam(newParam);

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
	template<typename EndFunc>
	inline bool HTTPQueryT<T>::parseQueryContent(const StringASCII::ElemType** itP, const EndFunc& endFunc) {
		const StringASCII::ElemType*& it(*itP);
		for ( ; ( *it == StringASCII::ElemType('\n') || *it == StringASCII::ElemType('\r') ) && !endFunc(it); it++ );

		const StringASCII::ElemType* contentStrBeginIt(it);
		for ( ; !endFunc(it); it++ );
		this->contentStr = StringASCII(contentStrBeginIt, Size(it - contentStrBeginIt));

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

		FunctorNewLine functorNewLine(endFunc);
		FunctorWord functorWord(endFunc);
		FunctorSpace functorSpace(endFunc);

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
		for ( ; !functorNewLine(it); it++ );
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
	const StringASCII HTTPRequestT<T>::methodStrTable[] = { StringASCII("GET"), StringASCII("POST"), StringASCII("DELETE") };

	template<typename T>
	inline HTTPRequestT<T>::HTTPRequestT() :
		method(Method::Unknown)
	{
		HTTPParam* hostParam(new HTTPParam(StringASCII("Host")));
		addParam(hostParam);

		this->hostParam = hostParam;
	}

	template<typename T>
	inline HTTPRequestT<T>::HTTPRequestT(typename UrlT<T>::Type type, const StringASCII& hostname) :
		url(type, hostname)
	{
		HTTPParam* hostParam(new HTTPParam(StringASCII("Host"), hostname));
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
		if ( !parseQueryHeader(itP, endFunc) ) {
			return false;
		}
		if ( !parseQueryContent(itP, endFunc) ) {
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

		FunctorNewLine functorNewLine(endFunc);
		FunctorWord functorWord(endFunc);
		FunctorSpace functorSpace(endFunc);

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

		StringASCII methodStr(methodStrBeginIt, Size(methodStrEndIt - methodStrBeginIt));
		typename HTTPRequestT<T>::Method method(HTTPRequestT<T>::getMethod(methodStr));

		if ( method == Method::Unknown ) {
			error("HTTP request syntax error : Unkown method.");
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

		StringASCII protocolStr(protocolStrBeginIt, Size(protocolStrEndIt - protocolStrBeginIt));

		this->method = method;
		this->protocolStr = protocolStr;

		return true;
	}

	template<typename T>
	template<typename EndFunc>
	inline bool HTTPRequestT<T>::parseQueryContent(const StringASCII::ElemType** itP, const EndFunc& endFunc) {
		if ( !this->url.parseParams(itP, endFunc) ) {
			return false;
		}
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

		if ( this->method == Method::POST ) {
			StringASCII paramStr;
			this->url.formatParams(&paramStr);
			const_cast<HTTPRequestT<T> *>(this)->setContent(paramStr);
		} else {
			const_cast< HTTPRequestT<T>* >( this )->clearContent();
		}

		HTTPQueryT<T>::formatQuery(outputStr);
	}

	template<typename T>
	inline void HTTPRequestT<T>::setMethod(typename HTTPRequestT<T>::Method method) {
		this->method = method;
	}

	template<typename T>
	inline void HTTPRequestT<T>::setEndPoint(const UrlT<T>& url) {
		this->url = url;

		updateHostParamValue();
	}

	template<typename T>
	inline void HTTPRequestT<T>::setEndPoint(const StringASCII& endPointStr, const Vector<HTTPParam>& paramVector) {
		this->url.setEndPoint(endPointStr);
		this->url.setParams(paramVector);
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
	inline typename HTTPRequestT<T>::Method HTTPRequestT<T>::getMethod() const {
		return this->method;
	}

	template<typename T>
	inline const UrlT<T>& HTTPRequestT<T>::getEndPoint() const {
		return this->url;
	}

	template<typename T>
	inline const StringASCII& HTTPRequestT<T>::getMethodString(typename HTTPRequestT<T>::Method method) {
		unsigned char methodIndex(static_cast< unsigned char >( method ));
		if ( methodIndex < sizeof(HTTPRequestT<T>::methodStrTable) ) {
			return HTTPRequestT<T>::methodStrTable[ methodIndex ];
		} else {
			return StringASCII::null;
		}
	}

	template<typename T>
	inline typename HTTPRequestT<T>::Method HTTPRequestT<T>::getMethod(const StringASCII& methodStr) {
		constexpr Size enumSize(sizeof(HTTPRequestT<T>::methodStrTable));
		for ( Size i(0); i < enumSize; i++ ) {
			if ( methodStr == HTTPRequestT<T>::methodStrTable[ i ] ) {
				return static_cast< typename HTTPRequestT<T>::Method >( i );
			}
		}
		return HTTPRequestT<T>::Method::Unknown;
	}

	template<typename T>
	inline void HTTPRequestT<T>::formatQueryTitle(StringASCII* outputStr) const {
		StringASCII& str(*outputStr);

		str << HTTPRequestT<T>::getMethodString(this->method);
		str << StringASCII::ElemType(' ');
		if ( this->method == Method::POST ) {
			this->url.formatEndPointWOParams(&str);
		} else {
			this->url.formatEndPoint(&str);
		}
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
	inline HTTPClientT<T>::HTTPClientT(typename UrlT<T>::Type type, const StringASCII& hostname) :
		request(type, hostname)
	{
		this->request.setProtocol(StringASCII("HTTP/1.1"));

		// this->request.setHeaderParam(StringASCII("Accept"), StringASCII("*/*"));
		this->request.setHeaderParam(StringASCII("Connection"), StringASCII("Keep-Alive"));
	}

	template<typename T>
	inline HTTPParam* HTTPClientT<T>::setHeaderParam(const StringASCII& paramName, const StringASCII& paramValue) {
		return this->request.setHeaderParam(paramName, paramValue);
	}

	template<typename T>
	inline HTTPResponseT<T>* HTTPClientT<T>::query(typename HTTPRequestT<T>::Method method, const StringASCII& endPointStr, const Vector<HTTPParam>& urlParams) {
		this->request.setMethod(method);
		this->request.setEndPoint(endPointStr, urlParams);

		if ( this->request.getEndPoint().getType() == UrlT<T>::Type::HTTPS ) {

			this->sendBuffer.clear();
			this->request.formatQuery(&this->sendBuffer);

			// Try sending directly as we are in keep alive.
			if ( !this->connection.isConnected() || !connection.send(this->sendBuffer.toCString(), int(this->sendBuffer.getSize())) ) {
				if ( !connection.connect(this->request.getEndPoint().getHostname(), unsigned short(443), Network::SockType::TCP) ) {
					return NULL;
				}
				if ( !connection.send(this->sendBuffer.toCString(), int(this->sendBuffer.getSize())) ) {
					return NULL;
				}
			}

			int maxSizeReceive(sizeof(this->receiveBuffer));
			const StringASCII::ElemType* parseIt(this->receiveBuffer);
			int totalReceivedLength(connection.receive(this->receiveBuffer, maxSizeReceive));

			if ( totalReceivedLength <= int(0) ) {
				return NULL;
			}

			// We receive something, let's try parse the title and the header.
			if ( !this->response.parseQueryTitle(&parseIt, StringASCII::IsEndIterator(this->receiveBuffer + totalReceivedLength)) ) {
				return NULL;
			}
			if ( !this->response.parseQueryHeader(&parseIt, StringASCII::IsEndIterator(this->receiveBuffer + totalReceivedLength)) ) {
				return NULL;
			}

			// Now we have the title and the header. Let's check for the Content-Length.
			HTTPParam* contentSizeParam(this->response.getHeaderParam(StringASCII("Content-Length")));

			int contentLength;
			if ( contentSizeParam ) {
				contentLength = contentSizeParam->getValue().toULongLong();
			} else {
				contentLength = Size(0);
			}

			maxSizeReceive = contentLength + ( parseIt - this->receiveBuffer );

			while ( totalReceivedLength < maxSizeReceive ) {
				int receivedLength(connection.receive(this->receiveBuffer + totalReceivedLength, maxSizeReceive - totalReceivedLength));

				if ( receivedLength <= int(0) ) {
					return NULL;
				}

				totalReceivedLength += receivedLength;
			}

			debug(*( this->receiveBuffer + totalReceivedLength ) = StringASCII::ElemType('\n'));

			if ( !this->response.parseQueryContent(&parseIt, StringASCII::IsEndIterator(this->receiveBuffer + totalReceivedLength)) ) {
				return NULL;
			}

			return &this->response;
		} else {
			error(String::format("Unsuported query type %.", UrlT<T>::getTypeString(this->request.getEndPoint().getType())));
			return NULL;
		}

		return NULL;
	}

	template<typename T>
	inline HTTPResponseT<T>* HTTPClientT<T>::getLastResponse() {
		return &this->response;
	}

}