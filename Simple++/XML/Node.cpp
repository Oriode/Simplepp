#include "Node.h"

namespace XML {

	Param::Param( const UTF8String & name, const UTF8String & value ) : name(name), value(value) {

	}

	Param::Param() {

	}

	const UTF8String & Param::getName() const {
		return this -> name;
	}

	void Param::setName( const UTF8String & name ) {
		this -> name = name;
	}

	const UTF8String & Param::getValue() const {
		return this -> value;
	}

	void Param::setValue( const UTF8String & value ) {
		this -> value = value;
	}

	bool Param::read( std::fstream * fileStream ) {
		if ( !IO::read( fileStream, &this -> name ) ) {
			_clear();
			return false;
		}
		if ( !IO::read( fileStream, &this -> value ) ) {
			_clear();
			return false;
		}
		return true;
	}


	bool Param::write( std::fstream * fileStream ) const {
		if ( !IO::write( fileStream, &this -> name ) )
			return false;
		if ( !IO::write( fileStream, &this -> value ) )
			return false;
		return true;
	}

	void Param::_clear() {
		this -> name.clear();
		this -> value.clear();
	}

















	Node::Node( const UTF8String & name ) : name( name ) {

	}


	Node::Node() {

	}

	void Node::setName( const UTF8String & name ) {
		this -> name = name;
	}

	const UTF8String & Node::getName() const {
		return this -> name;
	}

	void Node::setContent( const UTF8String & content ) {
		this -> content = content;
	}

	const UTF8String & Node::getContent() const {
		return this -> content;
	}

	void Node::addParam( const Param & param ) {
		this -> params.insert( param.getName(), param );
	}


	void Node::addParam( const UTF8String & name, const UTF8String & value ) {
		this -> params.insert( name, Param( name, value ) );
	}

	void Node::addParam( Param * param ) {
		this -> params.insert( param -> getName(), *param );
	}

	Param * Node::getParam( const UTF8String & name ) {
		auto paramP = this -> params[name];
		if ( paramP ) return paramP;
		else return NULL;
	}

	const Param * Node::getParam( const UTF8String & name ) const {
		auto paramP = this -> params[name];
		if ( paramP ) return paramP;
		else return NULL;
	}

	void Node::addChild( Node * child ) {
		this -> childs.push( child );
	}




	void Node::_clear() {
		_unload();

		this -> name.clear();
		this -> content.clear();

		this -> params.clear();
		this -> childs.clear();

		Map<UTF8String, Param*> params;
		Vector<Node*> childs;
	}


	void Node::_unload() {
		/*
		for ( auto it( this -> params.getBegin() ); it != this -> params.getEnd(); this -> params.iterate( &it ) ) {
			delete this -> params.getValueIt( it );
		}*/
		for ( auto it( this -> childs.getBegin() ); it != this -> childs.getEnd(); this -> childs.iterate( &it ) ) {
			delete this -> childs.getValueIt( it );
		}
	}

	bool Node::read( std::fstream * fileStream ) {
		_unload();
		this -> params.clear();
		this -> childs.clear();


		// TODO

		return true;
	}

}
