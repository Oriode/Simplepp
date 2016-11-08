///@file Node.h
///@brief File containing the Node Class, an XML Node
///@author Clement Gerber
///@date 20/10/16
#pragma once

#include "../UTF8String.h"
#include "../IO/IO.h"
#include "../Vector.h"
#include "../Map.h"





namespace XML {


	class Param : public BasicIO {
	public:
		///@brief Empty constructor
		Param();


		///brief Constructor from a name and a value
		///@param name Name of this param
		///@param value Value of this param
		Param( const UTF8String & name, const UTF8String & value );


		///@brief get the name of this param
		///@return Name of the param
		const UTF8String & getName() const;

		///@brief Set the name of this param
		///@param name Name of this param
		void setName( const UTF8String & name );

		///@brief get the value of this param
		///@return value of the param
		const UTF8String & getValue() const;

		///@brief Set the value of this param
		///@param value Value of this param
		void setValue( const UTF8String & value );


		///@brief read from a file stream
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		bool read( std::fstream * fileStream );

		///@brief write this object as binary into a file stream
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		bool write( std::fstream * fileStream ) const;
	private:
		void _clear();
		
		UTF8String name;
		UTF8String value;



	};







	class Node : public BasicIO {
	public:
		///@brief Empty constructor
		Node();

		///@brief create node
		///@param name Name of the node
		Node( const UTF8String & name );

		///@brief set the name of this node
		///@param name Name of this node
		void setName( const UTF8String & name );

		///@brief get the name of this node
		///@return name of this node
		const UTF8String & getName() const;


		///@brief set the content of this node
		///@param content Content of the node
		void setContent( const UTF8String & content );

		///@brief Get the content of this node
		///@return Content of this node
		const UTF8String & getContent() const;

		///@brief Add a param to this node
		///@param param Param to add to this node
		void addParam( const Param & param );

		///@brief Add a param to this node
		///@param param Pointer to the Param to add (Has to be allocated but NOT deallocated)
		void addParam( Param * param );

		///brief Add a param to this node
		///@param name Name of the param to add
		///@param value Value of the param to add
		void addParam( const UTF8String & name, const UTF8String & value );

		///@brief get a param from his name
		///@param Name of the param to retrieve
		///@return Pointer to the founded param or NULL of nothing has bee founded
		const Param * getParam( const UTF8String & name ) const;
		Param * getParam( const UTF8String & name );

		///@brief Add a child to this node
		///@param child Pointer to the child to add (Has to be allocated but NOT deallocated)
		void addChild( Node * child );



		///@brief read from a file stream
		///@param fileStream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		bool read( std::fstream * fileStream );

		///@brief write this object as binary into a file stream
		///@param fileStream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		bool write( std::fstream * fileStream ) const;
	private:
		void _clear();
		void _unload();

		UTF8String name;
		UTF8String content;

		Map< UTF8String, Param > params;
		Vector< Node * > childs;


	};


}
