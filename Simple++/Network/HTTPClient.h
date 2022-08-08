#pragma once

#include "../ParamContainer.h"
#include "Url.h"
#include "TLSConnection.h"

namespace Network {

	template<typename T>
	class HTTPQueryT : protected ParamContainerT<StringASCII, StringASCII> {
	public:

		enum class ContentType : unsigned char {
			None,
			Text,
			Html,
			Params,
			Json,
			Xml
		};

		HTTPQueryT();

		~HTTPQueryT();

		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parseQuery(const StringASCII::ElemType** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		void formatQuery(StringASCII* outputStr) const;
		void formatHeaderParam(StringASCII* outputStr, const ParamT<StringASCII, StringASCII>& param) const;

		///@brief Parse the query String and update the header params Vector.
		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parseQueryHeader(const StringASCII::ElemType** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parseQueryContent(const StringASCII::ElemType** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		void formatQueryContent(StringASCII* outputStr) const;

		HTTPParam* setHeaderParam(const StringASCII& paramName, const StringASCII& paramValue);

		const HTTPParam* getHeaderParam(const StringASCII& paramName) const;
		HTTPParam* getHeaderParam(const StringASCII& paramName);

		void setProtocol(const StringASCII& protocol);
		void setContent(const StringASCII& content);
		void clearContent();

		typename HTTPQueryT<T>::ContentType getContentType() const;
		void setContentType(typename HTTPQueryT<T>::ContentType contentType);

		const StringASCII& getProtocol() const;
		const StringASCII& getContent() const;

		static const StringASCII& getContentTypeString(typename ContentType contentType);
		static typename ContentType getContentType(const StringASCII& contentTypeStr);

		static const StringASCII contentTypeStrTable[];

	protected:
		ContentType contentType;
		StringASCII protocolStr;

	private:
		///@brief Format the query header using the specified params.
		void formatQueryHeader();

		bool bHeaderNeedFormat;

		StringASCII headerStr;
		StringASCII contentStr;
	};

	using HTTPQuery = HTTPQueryT<int>;

	template<typename T>
	class HTTPResponseT : public HTTPQueryT<T> {
	public:
		HTTPResponseT();
		template<typename EndFunc = StringASCII::IsEndIterator>
		HTTPResponseT(const StringASCII::ElemType ** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parseQuery(const StringASCII::ElemType ** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		StringASCII formatQuery() const;
		void formatQuery(StringASCII* outputStr) const;

		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parseQueryTitle(const StringASCII::ElemType** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		void formatQueryTitle(StringASCII* outputStr) const;

		void setStatusCode(Size statusCode);
		void setStatusMessage(const StringASCII& statusMessage);

		const Size getStatusCode() const;
		const StringASCII& getStatusMessage() const;

	protected:
		Size statusCode;
		StringASCII statusMessage;

	private:
	};

	using HTTPResponse = HTTPResponseT<int>;

	template<typename T>
	class HTTPRequestT : public HTTPQueryT<T> {
	public:
		typedef typename UrlT<T>::Type Type;

		enum class Method : unsigned char {
			GET,
			POST,
			DEL,
			Unknown
		};

		HTTPRequestT();
		HTTPRequestT(typename UrlT<T>::Type type, const StringASCII& hostname);
		template<typename EndFunc = StringASCII::IsEndIterator>
		HTTPRequestT(const StringASCII::ElemType ** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parseQuery(const StringASCII::ElemType ** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		StringASCII formatQuery() const;
		void formatQuery(StringASCII* outputStr) const;

		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parseQueryTitle(const StringASCII::ElemType** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		void formatQueryTitle(StringASCII* outputStr) const;

		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parseQueryContent(const StringASCII::ElemType** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		void setMethod(typename HTTPRequestT<T>::Method method);
		void setEndPoint(const UrlT<T>& url);
		void setEndPoint(const StringASCII& endPointStr, const Vector<HTTPParam>& paramVector);
		void setEndPoint(typename UrlT<T>::Type type, const StringASCII& hostname, const StringASCII& endPointStr, const Vector<HTTPParam>& paramVector);
		bool setEndPoint(const StringASCII& url);

		typename HTTPRequestT<T>::Method getMethod() const;
		const UrlT<T> & getEndPoint() const;

		static const StringASCII& getMethodString(typename HTTPRequestT<T>::Method method);
		static typename HTTPRequestT<T>::Method getMethod(const StringASCII& methodStr);

		static const StringASCII methodStrTable[];

	protected:
		void updateHostParamValue();

		using HTTPQueryT<T>::setContent;
		using HTTPQueryT<T>::getContent;

		Method method;
		UrlT<T> url;

		HTTPParam* hostParam;
	};

	using HTTPRequest = HTTPRequestT<int>;

	template<typename T>
	class HTTPClientT {
	public:
		HTTPClientT(typename UrlT<T>::Type type, const StringASCII& hostname);

		HTTPParam* setHeaderParam(const StringASCII& paramName, const StringASCII& paramValue);

		HTTPResponseT<T> * query(typename HTTPRequestT<T>::Method method, const StringASCII& endPointStr, const Vector<HTTPParam>& urlParams);
		HTTPResponseT<T> * query(typename HTTPRequestT<T> * request);

		const HTTPResponseT<T>* getLastResponse() const;

	private:
		HTTPResponseT<T>* _query(const typename HTTPRequestT<T>& request);

		HTTPRequestT<T> request;
		HTTPResponseT<T> response;

		TLSConnectionT<T> connection;
		bool bWasConnected;

		StringASCII sendBuffer;
		char receiveBuffer[ 1000000 ];
	};

	using HTTPClient = HTTPClientT<int>;

}

#include "HTTPClient.hpp"