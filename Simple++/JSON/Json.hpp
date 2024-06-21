#include "Json.h"
namespace JSON {

	template<typename S, typename C, typename EndFunc>
	NodeT<S>* parseT( const C** buffer, const EndFunc& endFunc ) {
		struct FunctorSpace {
			bool operator()( const C& c ) { return c == C( '\n' ) || c == C( '\r' ) || c == C( '\t' ) || c == C( ' ' ); }
		};
		static FunctorSpace functorSpace;

		const C*& it( *buffer );

		while ( functorSpace( *it ) ) it++;

		if ( ( *it ) == C( '{' ) ) {
			NodeMapT<S>* newNode( new NodeMapT<S>() );

			if ( !newNode -> readJSON( &it, endFunc ) ) {
				return NULL;
			} else {
				return newNode;
			}
		} else if ( ( *it ) == C( '[' ) ) {
			NodeArrayT<S>* newNode( new NodeArrayT<S>() );

			if ( !newNode -> readJSON( &it, endFunc ) ) {
				return NULL;
			} else {
				return newNode;
			}
		} else {
			NodeValueT<S>* newNode( new NodeValueT<S>() );

			if ( !newNode -> readJSON( &it, endFunc ) ) {
				return NULL;
			} else {
				return newNode;
			}
		}

		return NULL;
	}

	template<typename S, typename C, typename EndFunc>
	NodeT<S>* parseT( const C* buffer, const EndFunc& endFunc ) {
		return parseT<S, C, EndFunc>( &buffer, endFunc );
	}

	template<typename S>
	NodeT<S>* parseT( const S& str ) {
		const typename S::ElemType* buffer( str.toCString() );
		return parse<S, S::ElemType>( buffer );
	}

	template<typename S, typename C>
	bool fromJSON( const NodeT<S>* node, const S& childName, C* outValue, int verbose ) {
		const JSON::NodeT<S>* childNode( node->getChild( childName ) );
		if ( !childNode ) {
			if ( verbose > 0 ) { Log::displayError( String::format( "Missing node : %.", childName ) ); }
			return false;
		}

		if ( !fromJSON( childNode, outValue, verbose ) ) {
			return false;
		}

		return true;
	}

	template<typename S, typename C>
	bool fromJSON( const NodeT<S>* node, const S& childName, Optional<C>* outValue, int verbose ) {
		const JSON::NodeT<S>* childNode( node->getChild( childName ) );

		if ( !fromJSON( childNode, outValue, verbose ) ) {
			return false;
		}

		return true;
	}

	template<typename S, typename C>
	bool fromJSON( const NodeT<S>* node, C* v, int verbose ) {
		return _fromJSON<S>( node, v, verbose, reinterpret_cast< C* >( NULL ) );
	}

	template<typename S, typename C>
	bool fromJSON( const NodeT<S>* node, Optional<C>* v, int verbose ) {
		if ( !node || node -> getType() == JSON::NodeT<S>::Type::Null ) {
			v -> unset();
			return true;
		}

		// Set a new value using the default constructor.
		v -> setValue( C() );

		if ( !fromJSON( node, &v->getValue(), verbose ) ) {
			return false;
		}

		return true;
	}

	template<typename S, typename C>
	bool fromJSON( const NodeT<S>* node, Table<C>* t, int verbose ) {
		if ( node->getType() != JSON::NodeT<S>::Type::Array ) {
			if ( verbose > 0 ) { Log::displayError( __func__, String::format( "Node \"%\" is not a array one.", node->getName() ) ); }
			return false;
		}

		Size minSize( Math::min( node->getNbChildren(), t->getSize() ) );
		for ( Size i( 0 ); i < minSize; i++ ) {
			const JSON::NodeT<S>* nodeChild( node->getChild( i ) );
			if ( !JSON::fromJSON<S>( nodeChild, &t->getValueI( i ), verbose - 1 ) ) {
				return false;
			}
		}

		return true;
	}

	template<typename S, typename C, Size N>
	bool fromJSON( const NodeT<S>* node, StaticTable<C, N>* t, int verbose ) {
		if ( node->getType() != JSON::NodeT<S>::Type::Array ) {
			if ( verbose > 0 ) { Log::displayError( __func__, String::format( "Node \"%\" is not a array one.", node->getName() ) ); }
			return false;
		}

		Size minSize( Math::min( node->getNbChildren(), t->getSize() ) );
		for ( Size i( 0 ); i < minSize; i++ ) {
			const JSON::NodeT<S>* nodeChild( node->getChild( i ) );
			if ( !JSON::fromJSON<S>( nodeChild, &t->getValueI( i ), verbose - 1 ) ) {
				return false;
			}
		}

		return true;
	}

	template<typename S, typename C>
	bool fromJSON( const NodeT<S>* node, BasicVector<C>* v, int verbose ) {
		// If the node is a null one.
		if ( node->getType() == JSON::NodeT<S>::Type::Null ) {
			if ( verbose > 0 ) { Log::displayWarning( __func__, String::format( "Node \"%\" is null.", node->getName() ) ); }
			v -> clear();
			return false;
		}

		if ( node->getType() != JSON::NodeT<S>::Type::Array ) {
			if ( verbose > 0 ) { Log::displayError( __func__, String::format( "Node \"%\" is not a array one.", node->getName() ) ); }
			return false;
		}

		// Resize the BasicVector to the right size.
		v->resizeNoCopy( node->getNbChildren() );

		for ( Size i( 0 ); i < node->getNbChildren(); i++ ) {
			const JSON::NodeT<S>* nodeChild( node->getChild( i ) );
			if ( !JSON::fromJSON( nodeChild, &v->getValueI( i ), verbose - 1 ) ) {
				return false;
			}
		}

		return true;
	}

	template<typename S, typename C>
	bool fromJSON( const NodeT<S>* node, Vector<C>* v, int verbose ) {
		// If the node is a null one.
		if ( node->getType() == JSON::NodeT<S>::Type::Null ) {
			if ( verbose > 0 ) { Log::displayWarning( __func__, String::format( "Node \"%\" is null.", node->getName() ) ); }
			v -> clear();
			return false;
		}

		if ( node->getType() != JSON::NodeT<S>::Type::Array ) {
			if ( verbose > 0 ) { Log::displayError( __func__, String::format( "Node \"%\" is not a array one.", node->getName() ) ); }
			return false;
		}

		// Resize the Vector to the right size.
		v->resizeNoCopy( node->getNbChildren() );

		for ( Size i( 0 ); i < node->getNbChildren(); i++ ) {
			const JSON::NodeT<S>* nodeChild( node->getChild( i ) );
			if ( !JSON::fromJSON( nodeChild, &v->getValueI( i ), verbose - 1 ) ) {
				return false;
			}
		}

		return true;
	}

	template<typename S, typename Ratio>
	bool fromJSON( const NodeT<S>* node, Time::TimePoint<Ratio>* t, int verbose ) {
		// If the node is a null one.
		if ( node->getType() == JSON::NodeT<S>::Type::Null ) {
			if ( verbose > 0 ) { Log::displayWarning( __func__, String::format( "Node \"%\" is null.", node->getName() ) ); }
			t -> setValue( Time::TimeT( 0 ) );
			return false;
		}

		if ( node->getType() != JSON::NodeT<S>::Type::Value ) {
			if ( verbose > 0 ) { Log::displayError( __func__, String::format( "Node \"%\" is not a value one.", node->getName() ) ); }
			return false;
		}

		Time::Date d( Time::Date::parse( node->getValue() ) );
		(*t) = d.toTimePoint();

		return true;
	}

	template<typename S, typename C>
	bool _fromJSON( const NodeT<S>* node, C* v, int verbose, const Jsonable* ) {
		return v->fromJSON<S>( node, verbose );
	}

	template<typename S, typename C>
	bool _fromJSON( const NodeT<S>* node, C* v, int verbose, ... ) {
		// If the node is a null one.
		if ( node->getType() == JSON::NodeT<S>::Type::Null ) {
			if ( verbose > 0 ) { Log::displayWarning( __func__, String::format( "Node \"%\" is null.", node->getName() ) ); }
			return false;
		}

		if ( node->getType() != NodeT<S>::Type::Value ) {
			if ( verbose > 0 ) { Log::displayError( __func__, String::format( "Node \"%\" is not a value one.", node->getName() ) ); }
			return false;
		}
		( *v ) = node->getValue().fromString<C>();
		return true;
	}

	template<typename S>
	NodeT<S>* toJSON() {
		return new JSON::NodeValueT<S>();
	}

	template<typename S, typename C>
	NodeT<S>* toJSON( const C& v ) {
		return _toJSON<S>( v, reinterpret_cast< const C* >( NULL ) );
	}

	template<typename S, typename C>
	NodeT<S>* toJSON( const Optional<C>& v ) {
		if ( !v.isSet() ) {
			return NULL;
		}

		return toJSON<S, C>( v.getValue() );
	}

	template<typename S, typename C>
	NodeArrayT<S>* toJSON( const Table<C>& t ) {
		JSON::NodeArrayT<S>* nodeArray( new JSON::NodeArrayT<S>() );

		for ( Size i( 0 ); i < t.getSize(); i++ ) {
			JSON::NodeT<S>* nodeValue( toJSON<S>( t[ i ] ) );
			nodeArray->addChild( nodeValue );
		}

		return nodeArray;
	}

	template<typename S, typename C, Size N>
	NodeArrayT<S>* toJSON( const StaticTable<C, N>& t ) {
		JSON::NodeArrayT<S>* nodeArray( new JSON::NodeArrayT<S>() );

		for ( Size i( 0 ); i < t.getSize(); i++ ) {
			JSON::NodeT<S>* nodeValue( toJSON<S>( t[ i ] ) );
			nodeArray->addChild( nodeValue );
		}

		return nodeArray;
	}

	template<typename S, typename C>
	NodeArrayT<S>* toJSON( const BasicVector<C>& v ) {
		return toJSON<S>( *reinterpret_cast< const Table<C> * >( &v ) );
	}

	template<typename S, typename C>
	NodeArrayT<S>* toJSON( const Vector<C>& v ) {
		return toJSON<S>( *reinterpret_cast< const Table<C> * >( &v ) );
	}

	template<typename S, typename C>
	NodeT<S>* _toJSON( const C& v, const Jsonable* ) {
		return v.toJSON<S>();
	}

	template<typename S, typename C>
	NodeT<S>* _toJSON( const C& v, ... ) {
		return new NodeValueT<S>( S::toString( v ) );
	}

	template<typename S, typename C>
	bool write( const OS::Path& filePath, const C* object, int verbose ) {
		if ( verbose > 0 ) { Log::startStep( __func__, String::format( "Writting a JSON file \"%\"...", filePath ) ); }

		JSON::NodeT<S>* rootNode( toJSON<S, C>( *object ) );
		if ( !rootNode ) {
			if ( verbose > 0 ) { Log::endStepFailure( __func__, String::format( "Failed to create the JSON::Node \"%\".", filePath ) ); }
			return false;
		}

		if ( !rootNode -> writeFileJSON( filePath ) ) {
			if ( verbose > 0 ) { Log::endStepFailure( __func__, String::format( "Failed to write the file \"%\".", filePath ) ); }
			delete rootNode;
			return false;
		}

		// The Json node is not more usefull.
		delete rootNode;

		if ( verbose > 0 ) { Log::endStepSuccess( __func__, String::format( "Success.", filePath ) ); }

		return true;
	}

	template<typename S, typename C>
	bool read( const OS::Path& filePath, C* object, int verbose ) {

		if ( verbose > 0 ) { Log::startStep( __func__, String::format( "Reading a JSON objet." ) ); }

		JSON::NodeMapT<S> rootNode;
		if ( !rootNode.readFileJSON( filePath, verbose - 1 ) ) {
			if ( verbose > 0 ) { Log::endStepFailure( __func__, String::format( "Failed to read the file \"%\".", filePath ) ); }
			return false;
		}

		if ( !fromJSON( &rootNode, object, verbose - 1 ) ) {
			if ( verbose > 0 ) { Log::endStepFailure( __func__, String::format( "Failed to read the JSON::Node \"%\".", filePath ) ); }
			return false;
		}

		if ( verbose > 0 ) { Log::endStepSuccess( __func__, String::format( "Success.", filePath ) ); }

		return true;
	}

	template<typename S>
	inline bool Jsonable::fromJSON( const JSON::NodeT<S>* node, int verbose ) {
		ERROR_SPP( "Jsonable not overloaded the fromJSON method." );
		return false;
	}

	template<typename S>
	inline JSON::NodeT<S>* Jsonable::toJSON() const {
		ERROR_SPP( "Jsonable not overloaded the toJSON method." );
		return NULL;
	}

}