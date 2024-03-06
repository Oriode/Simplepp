#pragma once

#include "../String.h"
#include "../ParamContainer.h"
#include "Url.h"
#include "Network.h"
#include "HTTPQuery.h"
#include "../Log.h"

namespace Network {

	template<typename T>
	class HTTPResponseT : public HTTPQueryT<T> {
	public:
		HTTPResponseT();
		template<typename EndFunc = StringASCII::IsEndIterator>
		HTTPResponseT( const StringASCII::ElemType** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL, int verbose = 0 );

		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parseQuery( const StringASCII::ElemType** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL, int verbose = 0 );

		StringASCII formatQuery() const;
		void formatQuery( StringASCII* outputStr ) const;

		template<typename EndFunc = StringASCII::IsEndIterator>
		bool parseQueryTitle( const StringASCII::ElemType** itP, const EndFunc& endFunc = StringASCII::IS_END_SENTINEL, int verbose = 0 );

		void formatQueryTitle( StringASCII* outputStr ) const;

		void setStatusCode( Size statusCode );
		void setStatusMessage( const StringASCII& statusMessage );

		const Size getStatusCode() const;
		const StringASCII& getStatusMessage() const;

	protected:
		Size statusCode;
		StringASCII statusMessage;

	private:
	};

	using HTTPResponse = HTTPResponseT<int>;

}

#include "HTTPResponse.hpp"