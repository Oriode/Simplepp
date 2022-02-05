#pragma once

#include "../ParamContainer.h"
#include "Url.h"
#include "TLSConnection.h"

namespace Network {

	template<typename T>
	class HTTPQueryT : protected ParamContainerT<StringASCII, StringASCII> {
	public:
		HTTPQueryT();

		~HTTPQueryT();

		HTTPParam* setHeaderParam(const StringASCII& paramName, const StringASCII& paramValue);

		const HTTPParam* getHeaderParam(const StringASCII& paramName) const;
		HTTPParam* getHeaderParam(const StringASCII& paramName);

		void setProtocol(const StringASCII& protocol);
		void setContent(const StringASCII& content);

		const StringASCII& getProtocol() const;
		const StringASCII& getContent() const;

	protected:
		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parseQuery(const StringASCII::ElemType** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		void formatQuery(StringASCII* outputStr) const;

		StringASCII protocolStr;

	private:
		///@brief Format the query header using the specified params.
		void formatQueryHeader();

		///@brief Parse the query String and update the header params Vector.
		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parseQueryHeader(const StringASCII::ElemType ** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

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

		void setStatusCode(Size statusCode);
		void setStatusMessage(const StringASCII& statusMessage);

		const Size getStatusCode() const;
		const StringASCII& getStatusMessage() const;

	protected:
		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parseQueryTitle(const StringASCII::ElemType ** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		void formatQueryTitle(StringASCII* outputStr) const;

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
		template<typename EndFunc = StringASCII::IsEndIterator>
		HTTPRequestT(const StringASCII::ElemType ** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parseQuery(const StringASCII::ElemType ** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		StringASCII formatQuery() const;
		void formatQuery(StringASCII* outputStr) const;

		void setMethod(typename HTTPRequestT<T>::Method method);
		void setEndPoint(const UrlT<T>& url);
		void setEndPoint(typename UrlT<T>::Type type, const StringASCII& hostname, const StringASCII& endPointStr, const Vector<HTTPParam *>& paramVector);
		bool setEndPoint(const StringASCII& url);

		typename HTTPRequestT<T>::Method getMethod() const;
		const UrlT<T> & getEndPoint() const;

		static const StringASCII& getMethodString(typename HTTPRequestT<T>::Method method);
		static typename HTTPRequestT<T>::Method getMethod(const StringASCII& methodStr);

	protected:
		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parseQueryTitle(const StringASCII::ElemType ** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL);

		void formatQueryTitle(StringASCII* outputStr) const;

		void updateHostParamValue();

		Method method;
		UrlT<T> url;

		HTTPParam* hostParam;
	};

	using HTTPRequest = HTTPRequestT<int>;

	template<typename T>
	class HTTPClientT {
	public:
		HTTPClientT();

		HTTPParam* setHeaderParam(const StringASCII& paramName, const StringASCII& paramValue);

		HTTPResponseT<T> * query(typename HTTPRequestT<T>::Method method, typename UrlT<T>::Type type, const StringASCII& hostname, const StringASCII& endPointStr, const Vector<HTTPParam *>& urlParams);
		HTTPResponseT<T> * query(typename HTTPRequestT<T>::Method method, const UrlT<T> & url);

	private:
		HTTPRequestT<T> request;
		HTTPResponseT<T> response;
	};

	using HTTPClient = HTTPClientT<int>;

}

#include "HTTPClient.hpp"