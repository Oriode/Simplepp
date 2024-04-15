#pragma once

#include "../String.h"
#include "../ParamContainer.h"
#include "../Map.h"

#include "Url.h"
#include "Network.h"

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
			Xml,
			Png
		};

		HTTPQueryT();

		~HTTPQueryT();

		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parseQuery( const StringASCII::ElemType** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL, int verbose = 0 );

		void formatQuery( StringASCII* outputStr ) const;
		void formatHeaderParam( StringASCII* outputStr, const ParamT<StringASCII, StringASCII>& param ) const;

		///@brief Parse the query String and update the header params Vector.
		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parseQueryHeader( const StringASCII::ElemType** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL, int verbose = 0 );

		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parseQueryContent( const StringASCII::ElemType** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL, int verbose = 0 );

		void formatQueryContent( StringASCII* outputStr ) const;

		HTTPParam* setHeaderParam( const StringASCII& paramName, const StringASCII& paramValue );

		const HTTPParam* getHeaderParam( const StringASCII& paramName ) const;
		HTTPParam* getHeaderParam( const StringASCII& paramName );

		void setProtocol( const StringASCII& protocol );
		void setContent( const StringASCII& content );
		void clearContent();

		typename HTTPQueryT<T>::ContentType getContentType() const;
		void setContentType( typename HTTPQueryT<T>::ContentType contentType );

		const StringASCII& getProtocol() const;
		const StringASCII& getContent() const;

		static const StringASCII& getContentTypeString( typename ContentType contentType );
		static typename ContentType getContentType( const StringASCII& contentTypeStr );

		static const StringASCII contentTypeStrTable[7];

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

}


#include "HTTPQuery.hpp"