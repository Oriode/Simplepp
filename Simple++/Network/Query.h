#pragma once

#include "Simple++/Mutex.h"
#include "Simple++/Time/TimePoint.h"
#include "ClientQueryHandler.h"
#include "Simple++/Network/HTTPMessage.h"
#include "Simple++/Notify.h"

#include "BasicQuery.h"

namespace Network {
	

	///@brief	Override of the BasicQuery Class with template specific Request/Response types for easiest use.
	template<typename QueryType, typename ResponseType>
	class QueryT : public BasicQuery {
	public:
		///@brief	Constructor using a queryMessage.
		///@param	queryMessage	Message used to be sent, has to be dynamically allocated but not deleted.
		///@param	responseMessage	Message used to be received, has to be dynamically allocated but not deleted.
		QueryT( const QueryType* queryMessage, ResponseType* responseMessage, ClientQueryHandler* handler = NULL );

		///@brief	Get the Query Message.
		const QueryType* getQueryMessage() const;

		///@brief	Get the Response Message.
		const ResponseType* getResponseMessage() const;
		ResponseType* getResponseMessage();

	private:

	};

	template<typename QueryType, typename ResponseType>
	QueryT<QueryType, ResponseType>::QueryT( const QueryType* queryMessage, ResponseType* responseMessage, ClientQueryHandler* handler ) :
		BasicQuery( queryMessage, responseMessage, handler ) { }

	template<typename QueryType, typename ResponseType>
	const QueryType* Network::QueryT<QueryType, ResponseType>::getQueryMessage() const {
		return reinterpret_cast< const QueryType* >( BasicQuery::getQueryMessage() );
	}

	template<typename QueryType, typename ResponseType>
	inline const ResponseType* QueryT<QueryType, ResponseType>::getResponseMessage() const {
		return reinterpret_cast< ResponseType* >( BasicQuery::getResponseMessage() );
	}

	template<typename QueryType, typename ResponseType>
	inline ResponseType* QueryT<QueryType, ResponseType>::getResponseMessage() {
		return reinterpret_cast< ResponseType* >( BasicQuery::getResponseMessage() );
	}


}