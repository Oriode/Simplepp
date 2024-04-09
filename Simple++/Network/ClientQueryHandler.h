#pragma once

#include "Simple++/Network/HTTPMessage.h"

namespace Network {

	template<typename T>
	class HTTPHandler {
	public:
		virtual ~HTTPHandler() = default;
		///@brief	Event called when a query got an answer.
		///@param	queryMessage	HTTPQuery that triggered this answer.
		///@param	responseMessage	Response,  can be NULL if corrupted or unexpected.
		///@param	error	Error state if any. 
		virtual void onAnswer( const HTTPMessage* queryMessage, const HTTPMessage* responseMessage, HTTPError error ) { };

		///@brief	Called when the handler has finished it's job and can be deleted.
		virtual void onDelete() { };
	};

	using ClientQueryHandler = HTTPHandler<int>;

}