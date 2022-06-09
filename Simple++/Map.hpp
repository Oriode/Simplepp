#include "Map.h"

template<typename T>
RBNode<T>::RBNode( ctor ) {
	// Empty
}

template<typename T>
RBNode<T>::RBNode( RBNode<T> * parent, const T & value ) :
	parent( parent ),
	value( value ),
	left( NULL ),
	right( NULL ),
	color( Color::Red ) {


}

template<typename T>
RBNode<T>::RBNode( RBNode<T> * parent ) :
	parent( parent ),
	left( NULL ),
	right( NULL ),
	color( Color::Red ) {


}

template<typename T>
RBNode<T>::RBNode() :
	parent( NULL ),
	left( NULL ),
	right( NULL ) {

}


template<typename T>
RBNode<T>::RBNode( RBNode<T> && node ) :
	value( Utility::toRValue( node.value ) ),
	parent( Utility::toRValue( node.parent ) ),
	left( Utility::toRValue( node.left ) ),
	right( Utility::toRValue( node.right ) ),
	color( Utility::toRValue( node.color ) ) {

	node.left = NULL;
	node.right = NULL;

	// Set the parent to be linked to this node instead of the old one
	if ( this -> parent ) {
		if ( this -> parent -> getLeft() == &node ) {
			this -> parent -> setLeft( this );
		} else {
			this -> parent -> setRight( this );
		}
	}
}

template<typename T>
RBNode<T>::RBNode( const RBNode<T> & node ) :
	parent( NULL ) {

	// Using an explicit stack for high performances and be sure to never crash with a stack overflow exception
	struct Stack {
	public:
		Stack() {}
		Stack( RBNode<T> * nodeDst, const RBNode<T> & nodeSrc ) : nodeDst( nodeDst ), nodeSrc( &nodeSrc ) {}
		const RBNode<T> * nodeSrc;
		RBNode<T> * nodeDst;
	};

	Vector<Stack> stack;
	stack.reserve( 10 );
	stack.push( Stack( this, node ) );

	while ( stack.getSize() ) {
		Stack e( stack.pop() );
		const RBNode<T> & nodeSrc( *( e.nodeSrc ) );
		RBNode<T> * nodeDst( e.nodeDst );

		nodeDst -> color = nodeSrc.color;
		nodeDst -> value = nodeSrc.value;

		if ( nodeSrc.getRight() ) {
			nodeDst -> right = new RBNode<T>( ctor::null );
			nodeDst -> right -> setParent( nodeDst );

			stack.push( Stack( nodeDst -> right, *( nodeSrc.getRight() ) ) );
		} else {
			nodeDst -> right = NULL;
		}
		if ( nodeSrc.getLeft() ) {
			nodeDst -> left = new RBNode<T>( ctor::null );
			nodeDst -> left -> setParent( nodeDst );

			stack.push( Stack( nodeDst -> left, *( nodeSrc.getLeft() ) ) );
		} else {
			nodeDst -> left = NULL;
		}
	}



	/*
		if ( node.getLeft() ) {
			RBNode<T> * leftCopy( new RBNode<T>( *( node.getLeft() ) ) );
			leftCopy -> setParent( this );
			this -> left = leftCopy;
		} else {
			this -> left = NULL;
		}
		if ( node.getRight() ) {
			RBNode<T> * rightCopy( new RBNode<T>( *( node.getRight() ) ) );
			rightCopy -> setParent( this );
			this -> right = rightCopy;
		} else {
			this -> right = NULL;
		}*/
}

template<typename T>
RBNode<T> & RBNode<T>::operator=( RBNode<T> && node ) {
	_unload();

	this -> parent = Utility::toRValue( node.parent );
	this -> color = Utility::toRValue( node.color );
	this -> value = Utility::toRValue( node.value );
	this -> left = Utility::toRValue( node.left );
	this -> right = Utility::toRValue( node.right );

	node.left = NULL;
	node.right = NULL;

	// Set the parent to be linked to this node instead of the old one
	if ( this -> parent ) {
		if ( this -> parent -> getLeft() == &node ) {
			this -> parent -> setLeft( this );
		} else {
			this -> parent -> setRight( this );
		}
	}
	return *this;
}

template<typename T>
RBNode<T> & RBNode<T>::operator=( const RBNode<T> & node ) {
	// Using an explicit stack for high performances and be sure to never crash with a stack overflow exception
	struct Stack {
	public:
		Stack() {}
		Stack( RBNode<T> * nodeDst, const RBNode<T> & nodeSrc ) : nodeDst( nodeDst ), nodeSrc( &nodeSrc ) {}
		const RBNode<T> * nodeSrc;
		RBNode<T> * nodeDst;
	};

	Vector<Stack> stack;
	stack.reserve( 10 );
	stack.push( Stack( this, node ) );

	_clear();

	while ( stack.getSize() ) {
		Stack e( stack.pop() );
		const RBNode<T> & nodeSrc( *( e.nodeSrc ) );
		RBNode<T> * nodeDst( e.nodeDst );

		nodeDst -> color = nodeSrc.color;
		nodeDst -> value = nodeSrc.value;

		if ( nodeSrc.getRight() ) {
			nodeDst -> right = new RBNode<T>( ctor::null );
			nodeDst -> right -> setParent( nodeDst );

			stack.push( Stack( nodeDst -> right, *( nodeSrc.getRight() ) ) );
		} else {
			nodeDst -> right = NULL;
		}
		if ( nodeSrc.getLeft() ) {
			nodeDst -> left = new RBNode<T>( ctor::null );
			nodeDst -> left -> setParent( nodeDst );

			stack.push( Stack( nodeDst -> left, *( nodeSrc.getLeft() ) ) );
		} else {
			nodeDst -> left = NULL;
		}
	}



	/*_unload();

	this -> parent = NULL;
	this -> color = node.color;
	this -> value = node.value;

	if ( node.getLeft() ) {
		RBNode<T> * leftCopy( new RBNode<T>( *( node.getLeft() ) ) );
		leftCopy -> setParent( this );
		this -> left = leftCopy;
	} else {
		this -> left = NULL;
	}
	if ( node.getRight() ) {
		RBNode<T> * rightCopy( new RBNode<T>( *( node.getRight() ) ) );
		rightCopy -> setParent( this );
		this -> right = rightCopy;
	} else {
		this -> right = NULL;
	}*/
	return *this;
}

template<typename T>
RBNode<T>::~RBNode() {
	_unload();
}

template<typename T>
void RBNode<T>::_unload() {
	delete this -> left;
	delete this -> right;
}

template<typename T>
void RBNode<T>::_clear() {
	_unload();
	this -> left = NULL;
	this -> right = NULL;
	this -> parent = NULL;
}



template<typename T>
template<typename Stream>
bool RBNode<T>::write( Stream * stream ) const {
	// Using an explicit stack for high performances and be sure to never crash with a stack overflow exception
	Vector<const RBNode<T> *> stack;
	stack.reserve( 10 );
	stack.push( this );

	while ( stack.getSize() ) {
		const RBNode<T> * node( stack.pop() );

		if ( !IO::write( stream, &node -> value ) )
			return false;
		if ( !IO::write( stream, &node -> color ) )
			return false;
		bool isLeft( node -> left != NULL ), isRight( node -> right != NULL );
		if ( !IO::write( stream, &isRight ) )
			return false;
		if ( isRight )
			stack.push( node -> right );
		if ( !IO::write( stream, &isLeft ) )
			return false;
		if ( isLeft )
			stack.push( node -> left );
	}




	/*if ( !IO::write( stream, &this -> value ) )
		return false;
	bool isLeft( this -> left ), isRight( this -> right );
	if ( !IO::write( stream, &isLeft ) )
		return false;
	if ( isLeft ) {
		if ( !IO::write( stream, this -> left ) )
			return false;
	}
	if ( !IO::write( stream, &isRight ) )
		return false;
	if ( isRight ) {
		if ( !IO::write( stream, this -> right ) )
			return false;
	}*/
	return true;
}

template<typename T>
template<typename Stream>
bool RBNode<T>::read( Stream * stream ) {
	// Using an explicit stack for high performances and be sure to never crash with a stack overflow exception
	Vector<RBNode<T> *> stack;
	stack.reserve( 10 );
	stack.push( this );

	_clear();

	while ( stack.getSize() ) {
		RBNode<T> * node( stack.pop() );

		if ( !IO::read( stream, &node -> value ) ) {
			_clear();
			return false;
		}
		if ( !IO::read( stream, &node -> color ) ) {
			_clear();
			return false;
		}

		bool isLeft, isRight;

		if ( !IO::read( stream, &isRight ) ) {
			_clear();
			return false;
		}
		if ( isRight ) {
			node -> right = new RBNode<T>( ctor::null );
			node -> right -> setParent( node );
			stack.push( node -> right );
		} else {
			node -> right = NULL;
		}

		if ( !IO::read( stream, &isLeft ) ) {
			_clear();
			return false;
		}
		if ( isLeft ) {
			node -> left = new RBNode<T>( ctor::null );
			node -> left -> setParent( node );
			stack.push( node -> left );
		} else {
			node -> left = NULL;
		}
	}
	return true;
}


template<typename T>
const T & RBNode<T>::getValue() const {
	return this -> value;
}

template<typename T>
T & RBNode<T>::getValue() {
	return this -> value;
}

template<typename T>
void RBNode<T>::setValue( const T & value ) {
	this -> value = value;
}

template<typename T>
RBNode<T> * RBNode<T>::getRight() {
	return this -> right;
}

template<typename T>
const RBNode<T> * RBNode<T>::getRight() const {
	return this -> right;
}

template<typename T>
void RBNode<T>::setRight( RBNode<T> * right ) {
	this -> right = right;
}

template<typename T>
const RBNode<T> * RBNode<T>::getLeft() const {
	return this -> left;
}

template<typename T>
RBNode<T> * RBNode<T>::getLeft() {
	return this -> left;
}

template<typename T>
void RBNode<T>::setLeft( RBNode<T> * left ) {
	this -> left = left;
}

template<typename T>
const RBNode<T> * RBNode<T>::getParent() const {
	return this -> parent;
}

template<typename T>
RBNode<T> * RBNode<T>::getParent() {
	return this -> parent;
}

template<typename T>
void RBNode<T>::setParent( RBNode<T> * parent ) {
	this -> parent = parent;
}

template<typename T>
typename RBNode<T>::Color RBNode<T>::getColor() const {
	return this -> color;
}

template<typename T>
void RBNode<T>::setColor( typename RBNode<T>::Color color ) {
	this -> color = color;
}

template<typename T>
void RBNode<T>::swapColor() {
	this -> color = Color( !bool( this -> color ) );
}

template<typename T>
RBNode<T> * RBNode<T>::getGrandParent( const RBNode<T> & n ) {
	if ( n.getParent() -> parent )
		return n.getParent() -> getParent();
	else
		return NULL;
}

template<typename T>
RBNode<T> * RBNode<T>::getUncle( const RBNode<T> & n ) {
	auto grandParent( RBNode<T>::getGrandParent( n ) );
	if ( grandParent ) {
		if ( n.getParent() == grandParent -> getLeft() )
			return grandParent -> getRight();
		else
			return grandParent -> getLeft();
	} else
		return NULL;
}


template<typename T>
void RBNode<T>::insertNodeLeft( RBNode<T> * parentNode, RBNode<T> * node, RBNode<T> ** root ) {
	assert( parentNode -> getLeft() == NULL );
	parentNode -> setLeft( node );
	RBNode<T>::insertNode( node, root );
}

template<typename T>
void RBNode<T>::insertNodeRight( RBNode<T> * parentNode, RBNode<T> * node, RBNode<T> ** root ) {
	assert( parentNode -> getRight() == NULL );
	parentNode -> setRight( node );
	RBNode<T>::insertNode( node, root );
}


template<typename T>
void RBNode<T>::insertNode( RBNode<T> * node, RBNode<T> ** root ) {

	while ( true ) {
		RBNode<T> * P( node -> getParent() );

		if ( !P ) {
			// Case 1 : We are the root

			node -> setColor( Color::Black );
			( *root ) = node;
		} else {
			// Case 2 : We are not the root

			// Note : In the following cases it can be assumed that N has a grandparent node G, because its parent P is red, and if it were the root, it would be black. Thus, N also has an uncle node U, although it may be a leaf in cases 4 and 5.
			if ( P -> getColor() == Color::Red ) {
				RBNode<T> * G( P -> getParent() );
				RBNode<T> * U;

				bool uncleLeft;
				if ( node -> getParent() == G -> getLeft() ) {
					uncleLeft = false;
					U = G -> getRight();
				} else {
					uncleLeft = true;
					U = G -> getLeft();
				}

				if ( U && U -> getColor() == Color::Red ) {
					// Case 3 : Parent and Uncle are Red

					P -> setColor( Color::Black );
					U -> setColor( Color::Black );
					G -> setColor( Color::Red );
					node = G;
					continue;

				} else {
					// Case 4 :
					if ( !uncleLeft ) {
						if ( node == P -> getRight() ) {
							// Tree Rotation Left
							RBNode<T> * L( node -> getLeft() );

							G -> setLeft( node );
							node -> setParent( G );
							node -> setLeft( P );
							P -> setParent( node );
							P -> setRight( L );
							if ( L ) L -> setParent( P );


							P = node;
							node = node -> getLeft();
						}
					} else {
						if ( node == P -> getLeft() ) {
							// Tree rotation Right
							RBNode<T> * R( node -> getRight() );

							G -> setRight( node );
							node -> setParent( G );
							node -> setRight( P );
							P -> setParent( node );
							P -> setLeft( R );
							if ( R ) R -> setParent( P );

							P = node;
							node = node -> getRight();
						}
					}



					P -> setColor( Color::Black );
					G -> setColor( Color::Red );

					if ( node == P -> getLeft() ) {
						// Tree rotation Right
						RBNode<T> * _P( G );
						RBNode<T> * _G( _P -> getParent() );
						RBNode<T> * _N( P );
						RBNode<T> * _R( _N -> getRight() );


						_N -> setRight( _P );
						_P -> setParent( _N );
						_P -> setLeft( _R );
						if ( _R ) _R -> setParent( _P );

						if ( _G ) {
							if ( _G -> getLeft() == _P )
								_G -> setLeft( _N );
							else
								_G -> setRight( _N );
							_N -> setParent( _G );
						} else {
							_N -> setParent( NULL );
							( *root ) = _N;
						}
					} else {
						// Tree rotation Left
						RBNode<T> * _P( G );
						RBNode<T> * _G( _P -> getParent() );
						RBNode<T> * _N( P );
						RBNode<T> * _L( _N -> getLeft() );


						_N -> setLeft( _P );
						_P -> setParent( _N );
						_P -> setRight( _L );
						if ( _L ) _L -> setParent( _P );

						if ( _G ) {
							if ( _G -> getLeft() == _P )
								_G -> setLeft( _N );
							else
								_G -> setRight( _N );
							_N -> setParent( _G );
						} else {
							_N -> setParent( NULL );
							( *root ) = _N;
						}
					}

				}
			}
		}
		break;
	}

}


template<typename T>
void RBNode<T>::deleteNode( RBNode<T> * node, RBNode<T> ** root ) {
	RBNode<T> * P( node -> getParent() );


	if ( node -> getRight() && node -> getLeft() ) {
		// If node has two child, 

		RBNode<T> * successor( node -> getRight() );
		while ( successor -> getLeft() ) {
			successor = successor -> getLeft();
		}


		// Successor's Child
		RBNode<T> * C( successor -> getRight() );

		// Successor's Parent
		RBNode<T> * sP( successor -> getParent() );

		bool successorIsLeft;


		successor -> setLeft( node -> getLeft() );
		node -> getLeft() -> setParent( successor );


		if ( node -> getRight() != successor ) {
			successor -> setRight( node -> getRight() );
			node -> getRight() -> setParent( successor );

			if ( C ) C -> setParent( sP );
			sP -> setLeft( C );
			successorIsLeft = true;

		} else {
			sP = successor;
			successorIsLeft = false;
		}


		// Now swap the successor with the node itself
		successor -> setParent( P );
		Color sColor( successor -> getColor() );
		successor -> setColor( node -> getColor() );

		if ( P ) {
			if ( P -> getLeft() == node )
				P -> setLeft( successor );
			else
				P -> setRight( successor );
		} else {
			( *root ) = successor;
		}

		if ( sColor == Color::Black )
			_deleteFixUp( C, root, sP, successorIsLeft );
	} else {


		RBNode<T> * child;
		Color childColor;

		if ( node -> getRight() ) {
			child = node -> getRight();
			childColor = child -> getColor();
		} else if ( node -> getLeft() ) {
			child = node -> getLeft();
			childColor = child -> getColor();
		} else {
			child = NULL;
			childColor = Color::Black;
		}


		// replace(node, child)
		bool NisLeft;
		if ( P ) {
			if ( P -> getLeft() == node ) {
				P -> setLeft( child );
				NisLeft = true;
			} else {
				P -> setRight( child );
				NisLeft = false;
			}
		} else {
			( *root ) = child;
		}
		if ( child ) {
			child -> setParent( P );
		}

		if ( node -> getColor() == Color::Black ) {
			if ( child && child -> getColor() == Color::Red ) {
				child -> setColor( Color::Black );
			} else {
				// At this stage we have Color(child) == Black && Color(node) == Black => S -> Left != NULL && S -> Right != NULL
				if ( P ) {
					_deleteFixUp( child, root, P, NisLeft );
				}
			}
		}
	}
	node -> setLeft( NULL );
	node -> setRight( NULL );
	delete node;
}




template<typename T>
void RBNode<T>::_deleteFixUp( RBNode<T> * N, RBNode<T> ** root, RBNode<T> * P, bool NisLeft ) {
	while ( true ) {
		RBNode<T> * S;
		if ( NisLeft ) {
			S = P -> getRight();
		} else {
			S = P -> getLeft();
		}

		//TMP
		//if ( !S ) return;

		// Case 2
		// S is not null because N had a child
		if ( S -> getColor() == Color::Red ) {
			P -> setColor( Color::Red );
			S -> setColor( Color::Black );

			if ( NisLeft ) {
				//assert( S -> getLeft() );

				// Rotate Left on P
				RBNode<T> * _P( P );
				RBNode<T> * _G( _P -> getParent() );
				RBNode<T> * _N( S );
				RBNode<T> * _L( _N -> getLeft() );


				_N -> setLeft( _P );
				_P -> setParent( _N );
				_P -> setRight( _L );
				if ( _L ) _L -> setParent( _P );

				if ( _G ) {
					if ( _G -> getLeft() == _P )
						_G -> setLeft( _N );
					else
						_G -> setRight( _N );
					_N -> setParent( _G );
				} else {
					_N -> setParent( NULL );
					( *root ) = _N;
				}


				// Relabel S
				S = _L;

			} else {
				//assert( S -> getRight() );
				// Rotate Right on P
				RBNode<T> * _P( P );
				RBNode<T> * _G( _P -> getParent() );
				RBNode<T> * _N( S );
				RBNode<T> * _R( _N -> getRight() );


				_N -> setRight( _P );
				_P -> setParent( _N );
				_P -> setLeft( _R );
				if ( _R ) _R -> setParent( _P );

				if ( _G ) {
					if ( _G -> getLeft() == _P )
						_G -> setLeft( _N );
					else
						_G -> setRight( _N );
					_N -> setParent( _G );
				} else {
					_N -> setParent( NULL );
					( *root ) = _N;
				}

				// Relabel S
				S = _R;

			}
		}
		// Case 3

		//if ( !S ) return;

		if ( P -> getColor() == Color::Black &&
			 S -> getColor() == Color::Black &&
			 ( !S -> getLeft() || S -> getLeft() -> getColor() == Color::Black ) &&
			 ( !S -> getRight() || S -> getRight() -> getColor() == Color::Black ) ) {

			S -> setColor( Color::Red );
			N = P;
			P = P -> getParent();
			if ( P ) {
				NisLeft = ( P -> getLeft() == N );
				continue;
			}
		} else {
			if ( P -> getColor() == Color::Red &&
				 S -> getColor() == Color::Black &&
				 ( !S -> getLeft() || S -> getLeft() -> getColor() == Color::Black ) &&
				 ( !S -> getRight() || S -> getRight() -> getColor() == Color::Black ) ) {
				// Case 4

				S -> setColor( Color::Red );
				P -> setColor( Color::Black );
			} else {
				// Case 5

				assert( S -> getColor() == Color::Black );

				// TMP
				// N is Left && Color(S.right) ==  Black && Color(S.left) == Red 
				if ( NisLeft && ( !S -> getRight() || S -> getRight() -> getColor() == Color::Black ) && S -> getLeft() && S -> getLeft() -> getColor() == Color::Red ) {

					assert( S -> getLeft() -> getColor() == Color::Red ); // Trivial due to case 2-4

					S -> setColor( Color::Red );
					S -> getLeft() -> setColor( Color::Black );

					// Rotate Right on S

					RBNode<T> * _P( S );
					RBNode<T> * _G( P );
					RBNode<T> * _N( S -> getLeft() );
					RBNode<T> * _R( _N -> getRight() );


					_N -> setRight( _P );
					_P -> setParent( _N );
					_P -> setLeft( _R );
					if ( _R ) _R -> setParent( _P );

					_G -> setRight( _N );
					_N -> setParent( _G );

					// Update S
					S = _N;

					// N is right && Color(S.left) == Black && Color(S.right) == Red 
				} else if ( !NisLeft && ( !S -> getLeft() || S -> getLeft() -> getColor() == Color::Black ) && S -> getRight() && S -> getRight() -> getColor() == Color::Red ) {

					assert( S -> getRight() -> getColor() == Color::Red ); // Trivial due to case 2-4


					S -> setColor( Color::Red );
					S -> getRight() -> setColor( Color::Black );

					//Rotate Left on S 
					RBNode<T> * _P( S );
					RBNode<T> * _G( P );
					RBNode<T> * _N( S -> getRight() );
					RBNode<T> * _L( _N -> getLeft() );


					_N -> setLeft( _P );
					_P -> setParent( _N );
					_P -> setRight( _L );
					if ( _L ) _L -> setParent( _P );

					_G -> setLeft( _N );
					_N -> setParent( _G );

					// Update S
					S = _N;
				}
				// Case 6	

				assert( S );
				assert( S && S -> getColor() == Color::Black );

				S -> setColor( P -> getColor() );
				P -> setColor( Color::Black );

				if ( NisLeft ) {
					assert( S -> getRight() -> getColor() == Color::Red );
					S -> getRight() -> setColor( Color::Black );

					// Rotate Left on P
					RBNode<T> * _P( P );
					RBNode<T> * _G( _P -> getParent() );
					RBNode<T> * _N( S );
					RBNode<T> * _L( _N -> getLeft() );


					_N -> setLeft( _P );
					_P -> setParent( _N );
					_P -> setRight( _L );
					if ( _L ) _L -> setParent( _P );

					if ( _G ) {
						if ( _G -> getLeft() == _P )
							_G -> setLeft( _N );
						else
							_G -> setRight( _N );
						_N -> setParent( _G );
					} else {
						_N -> setParent( NULL );
						( *root ) = _N;
					}

				} else {
					assert( S -> getLeft() -> getColor() == Color::Red );
					S -> getLeft() -> setColor( Color::Black );


					// Rotate Right on P
					RBNode<T> * _P( P );
					RBNode<T> * _G( _P -> getParent() );
					RBNode<T> * _N( S );
					RBNode<T> * _R( _N -> getRight() );


					_N -> setRight( _P );
					_P -> setParent( _N );
					_P -> setLeft( _R );
					if ( _R ) _R -> setParent( _P );

					if ( _G ) {
						if ( _G -> getLeft() == _P )
							_G -> setLeft( _N );
						else
							_G -> setRight( _N );
						_N -> setParent( _G );
					} else {
						_N -> setParent( NULL );
						( *root ) = _N;
					}
				}
			}
		}
		break;
	}
}
















template<typename T>
template<typename S>
S RBNode<T>::toString() const {
	return RBNode<T>::toString<S>( this );
}


template<typename T>
template<typename S>
S RBNode<T>::toString( RBNode<T> * root ) {
	if ( !root ) return S();

	struct Stack {
	public:
		Stack() {}
		Stack( RBNode<T> * node, unsigned int tabs ) : node( node ), tabs( tabs ) {}
		RBNode<T> * node;
		unsigned int tabs;
	};

	Vector<Stack> stack;
	stack.reserve( 10 );
	stack.push( Stack( root, 0 ) );


	S string;
	string.reserve( 100 );


	while ( stack.getSize() ) {
		auto last( stack.pop() );
		unsigned int tabs( last.tabs );
		RBNode<T> * node( last.node );


		for ( unsigned int i( 0 ); i < tabs; i++ )
			string << S::ElemType( '\t' );
		if ( node -> getColor() == Color::Black )
			string << S::ElemType( 'B' );
		else
			string << S::ElemType( 'R' );
		string << S( node -> getValue() ) << S::ElemType( '\n' );


		if ( node -> getRight() )
			stack.push( Stack( node -> getRight(), tabs + 1 ) );
		if ( node -> getLeft() )
			stack.push( Stack( node -> getLeft(), tabs + 1 ) );

	}

	return string;
}



template<typename T>
unsigned int RBNode<T>::_checkNbBlackNode( RBNode<T> * node, unsigned int nbBlackNodes ) {

	if ( node ) {
		if ( node -> getColor() == Color::Red ) {
			// Tree has a Red node with red child :/
			assert( ( !node -> getLeft() || node -> getLeft() -> getColor() == Color::Black ) && ( !node -> getRight() || node -> getRight() -> getColor() == Color::Black ) );
		}

		if ( node -> getColor() == Color::Black )
			nbBlackNodes++;

		unsigned int nbBlacksLeft( _checkNbBlackNode( node -> getLeft(), nbBlackNodes ) );
		unsigned int nbBlacksRight( _checkNbBlackNode( node -> getRight(), nbBlackNodes ) );
		// Tree has not the same number of black nodes for every path :/
		assert( nbBlacksLeft == nbBlacksRight );


		return nbBlacksLeft;
	} else {
		return nbBlackNodes + 1;
	}
}



/************************************************************************/
/* Tree                                                                 */
/************************************************************************/

template<typename I, typename T, typename Compare>
RBTree<I, T, Compare>::RBTree( const Compare & compareFunc ) :
	compareFunc( compareFunc ),
	rootNode( NULL ) {
	static_assert( Utility::isBase<Math::Compare::Template, Compare>::value, "Functor should inherite from Math::Compare::Template" );

}

template<typename I, typename T, typename Compare>
RBTree<I, T, Compare>::RBTree( const RBTree<I, T, Compare> & tree ) :
	compareFunc( tree.compareFunc ) {

	if ( tree.rootNode ) {
		this -> rootNode = new RBNode<MapObject<I, T>>( *( tree.rootNode ) );
	} else {
		this -> rootNode = NULL;
	}
}

template<typename I, typename T, typename Compare>
RBTree<I, T, Compare>::RBTree( RBTree<I, T, Compare> && tree ) :
	compareFunc( Utility::toRValue( tree.compareFunc ) ),
	rootNode( Utility::toRValue( tree.rootNode ) ) {
	tree.rootNode = NULL;
}

template<typename I, typename T, typename Compare>
RBTree<I, T, Compare>::~RBTree() {
	delete this -> rootNode;
}

template<typename I, typename T, typename Compare>
RBTree<I, T, Compare> & RBTree<I, T, Compare>::operator=( const RBTree<I, T, Compare> & tree ) {
	_unload();

	this -> compareFunc = tree.compareFunc;
	if ( tree.rootNode ) {
		this -> rootNode = new RBNode<MapObject<I, T>>( *( tree.rootNode ) );
	} else {
		this -> rootNode = NULL;
	}
	return *this;
}


template<typename I, typename T, typename Compare>
RBTree<I, T, Compare> & RBTree<I, T, Compare>::operator=( RBTree<I, T, Compare> && tree ) {
	_unload();
	this -> compareFunc = Utility::toRValue( tree.compareFunc );
	this -> rootNode = Utility::toRValue( tree.rootNode );

	tree.rootNode = NULL;
	return *this;
}


template<typename I, typename T, typename Compare>
void RBTree<I, T, Compare>::_unload() {
	delete this -> rootNode;
}

template<typename I, typename T, typename Compare>
void RBTree<I, T, Compare>::_clear() {
	_unload();
	this -> rootNode = NULL;
}

template<typename I, typename T, typename Compare>
template<typename C>
inline RBTree<I, T, Compare>::operator BasicString<C>() const {
	return toString<BasicString<C>>();
}

template<typename I, typename T, typename Compare>
template<typename S>
S RBTree<I, T, Compare>::toString() const {
	return RBNode< MapObject<I, T> >::toString<S>( this -> rootNode );
}

template<typename I, typename T, typename Compare>
RBNode< MapObject< I, T > > * RBTree<I, T, Compare>::_insert( const I & index, const T & value ) {

	RBNode< MapObject< I, T > > * node( this -> rootNode );
	if ( node == NULL ) {
		RBNode< MapObject< I, T > > * newNode( new RBNode< MapObject< I, T > >( NULL, MapObject< I, T >( index, value ) ) );
		RBNode< MapObject< I, T > >::insertNode( newNode, &this -> rootNode );
		return newNode;
	} else {
		while ( true ) {
			Math::Compare::Value compareResult( this -> compareFunc( index, node -> getValue().getIndex() ) );
			if ( compareResult == Math::Compare::Value::Equal ) {
				return NULL;
			} else if ( compareResult == Math::Compare::Value::Less ) {
				if ( node -> getLeft() ) {
					node = node -> getLeft();
					continue;
				} else {
					RBNode< MapObject< I, T > > * newNode( new RBNode< MapObject< I, T > >( node, MapObject< I, T >( index, value ) ) );
					RBNode< MapObject< I, T > >::insertNodeLeft( node, newNode, &this -> rootNode );

					#ifdef DEBUG
					RBTree<I, T, Compare>::_checkTree( this -> rootNode, this -> compareFunc );
					#endif
					return newNode;
				}
			} else {
				if ( node -> getRight() ) {
					node = node -> getRight();
					continue;
				} else {
					RBNode< MapObject< I, T > > * newNode( new RBNode< MapObject< I, T > >( node, MapObject< I, T >( index, value ) ) );
					RBNode< MapObject< I, T > >::insertNodeRight( node, newNode, &this -> rootNode );

					#ifdef DEBUG
					RBTree<I, T, Compare>::_checkTree( this -> rootNode, this -> compareFunc );
					#endif
					return newNode;
				}
			}
		}
	}
	return NULL;
}

template<typename I, typename T, typename Compare>
T * RBTree<I, T, Compare>::insert( const I & index, const T & value ) {
	auto newNode( _insert( index, value ) );
	return ( newNode != NULL ) ? const_cast< T * >( &( newNode -> getValue().getValue() ) ) : NULL;
}

template<typename I, typename T, typename Compare>
RBNode< MapObject< I, T > > * RBTree<I, T, Compare>::insertNode( const I & index, const T & value ) {
	return _insert( index, value );
}

template<typename I, typename T, typename Compare>
const T * RBTree<I, T, Compare>::operator[]( const I & index ) const {
	return getValueI( index );
}

template<typename I, typename T, typename Compare>
T * RBTree<I, T, Compare>::operator[]( const I & index ) {
	return getValueI( index );
}

template<typename I, typename T, typename Compare>
const RBNode< MapObject<I, T> > * RBTree<I, T, Compare>::getNodeI( const I & index ) const {
	return const_cast< RBTree<I, T, Compare> * >( this ) -> getNodeI( index );
}

template<typename I, typename T, typename Compare>
RBNode< MapObject<I, T> > * RBTree<I, T, Compare>::getNodeI( const I & index ) {
	if ( this -> rootNode ) {
		RBNode< MapObject< I, T > > * node( this -> rootNode );
		while ( true ) {
			Math::Compare::Value compareResult( this -> compareFunc( index, node -> getValue().getIndex() ) );

			if ( compareResult == Math::Compare::Value::Equal ) {
				return node;
			} else if ( compareResult == Math::Compare::Value::Less ) {
				node = node -> getLeft();
				if ( !node )
					return NULL;
			} else {
				node = node -> getRight();
				if ( !node )
					return NULL;
			}
		}
	} else {
		return NULL;
	}
}


template<typename I, typename T, typename Compare>
const RBNode< MapObject<I, T> > * RBTree<I, T, Compare>::getNearestNodeLessI( const I & index ) const {
	return const_cast< RBTree<I, T, Compare> * >( this ) -> getNearestNodeI( index );
}

template<typename I, typename T, typename Compare>
RBNode< MapObject<I, T> > * RBTree<I, T, Compare>::getNearestNodeLessI( const I & index ) {
	if ( this -> rootNode ) {
		RBNode< MapObject< I, T > > * node( this -> rootNode );
		while ( true ) {
			Math::Compare::Value compareResult( this -> compareFunc( index, node -> getValue().getIndex() ) );

			if ( compareResult == Math::Compare::Value::Equal ) {
				return node;
			} else if ( compareResult == Math::Compare::Value::Less ) {
				if ( !node -> getLeft() )
					return node;
				else
					node = node -> getLeft();
			} else {
				if ( !node -> getRight() )
					return node;
				else
					node = node -> getRight();
			}
		}
	} else {
		return NULL;
	}
}



template<typename I, typename T, typename Compare>
T * RBTree<I, T, Compare>::getValueI( const I & index ) {
	RBNode< MapObject<I, T> > * nodeFounded( getNodeI( index ) );
	if ( nodeFounded ) {
		return &( nodeFounded -> getValue().getValue() );
	} else {
		return NULL;
	}
}

template<typename I, typename T, typename Compare>
const T * RBTree<I, T, Compare>::getValueI( const I & index ) const {
	return const_cast< RBTree<I, T, Compare> * >( this ) -> getValueI( index );
}

template<typename I, typename T, typename Compare>
void RBTree<I, T, Compare>::setValueI( const I & index, const T & v ) {
	*( getValueI( index ) ) = v;
}

template<typename I, typename T, typename Compare>
bool RBTree<I, T, Compare>::eraseI( const I & index ) {
	if ( this -> rootNode ) {
		RBNode< MapObject< I, T > > * node( this -> rootNode );
		while ( true ) {
			Math::Compare::Value compareResult( this -> compareFunc( index, node -> getValue().getIndex() ) );

			if ( compareResult == Math::Compare::Value::Equal ) {
				RBNode< MapObject< I, T > >::deleteNode( node, &this -> rootNode );

				// DEBUG
				#ifdef DEBUG
				RBTree<I, T, Compare>::_checkTree( this -> rootNode, this -> compareFunc );
				#endif

				return true;
			} else if ( compareResult == Math::Compare::Value::Less ) {
				node = node -> getLeft();
				if ( !node )
					return false;
			} else {
				node = node -> getRight();
				if ( !node )
					return false;
			}
		}
	} else {
		return false;
	}
}

template<typename I, typename T, typename Compare>
bool RBTree<I, T, Compare>::eraseNode( RBNode< MapObject<I, T> > * node ) {
	RBNode< MapObject< I, T > >::deleteNode( node, &this -> rootNode );
	return true;
}


template<typename I, typename T, typename Compare>
void RBTree<I, T, Compare>::_checkTree( RBNode<MapObject<I, T>> * root, Compare & func ) {
	RBNode<MapObject<I, T>>::_checkNbBlackNode( root, 1 );
	RBTree<I, T, Compare>::_checkTreeSorted( root, func );
}


template<typename I, typename T, typename Compare>
void RBTree<I, T, Compare>::_checkTreeSorted( RBNode< MapObject<I, T> > * node, Compare & func ) {
	if ( node ) {
		const MapObject<I, T> & v( node -> getValue() );
		if ( node -> getLeft() ) {
			Math::Compare::Value compareValue( func( node -> getLeft() -> getValue().getIndex(), v.getIndex() ) );
			assert( compareValue == Math::Compare::Value::Less );
			_checkTree( node -> getLeft(), func );
		}
		if ( node -> getRight() ) {
			Math::Compare::Value compareValue( func( node -> getRight() -> getValue().getIndex(), v.getIndex() ) );
			assert( compareValue == Math::Compare::Value::Greater );
			_checkTree( node -> getRight(), func );
		}
	}
}




template<typename I, typename T, typename Compare>
template<typename Stream>
bool RBTree<I, T, Compare>::read(Stream* stream ) {
	_clear();

	if ( !IO::read( stream, &this -> compareFunc ) ) {
		_clear();
		return false;
	}

	bool isRootNode;
	if ( !IO::read( stream, &isRootNode ) ) {
		_clear();
		return false;
	}
	if ( isRootNode ) {
		this -> rootNode = new RBNode<MapObject<I, T>>();

		if ( !IO::read( stream, this -> rootNode ) ) {
			_clear();
			return false;
		}
	}


	return true;
}




template<typename I, typename T, typename Compare>
template<typename Stream>
bool RBTree<I, T, Compare>::write(Stream* stream ) const {
	if ( !IO::write( stream, &this -> compareFunc ) )
		return false;

	bool isRootNode( this -> rootNode != NULL );
	if ( !IO::write( stream, &isRootNode ) )
		return false;

	if ( this -> rootNode ) {
		if ( !IO::write( stream, this -> rootNode ) )
			return false;
	}

	return true;
}


template<typename I, typename T, typename Compare>
void RBTree<I, T, Compare>::clear() {
	delete this -> rootNode;
	this -> rootNode = NULL;
}


template<typename I, typename T, typename Compare>
bool RBTree<I, T, Compare>::iterate( typename RBTree<I, T, Compare>::Iterator * it ) const {
	auto node( ( *it ) );

	if ( node -> getLeft() ) {
		// If we can go left, just do it !
		( *it ) = node -> getLeft();
		return true;
	} else if ( node -> getRight() ) {
		// If we can go right, just do it !
		( *it ) = node -> getRight();
		return true;
	} else {
		// We are in a leaf, we have to roll back
		while ( node -> getParent() ) {
			if ( node -> getParent() -> getRight() == node ) {
				node = node -> getParent();
			} else {
				node = node -> getParent();
				if ( node -> getRight() ) {
					( *it ) = node -> getRight();
					return true;
				}
			}
		}
	}
	( *it ) = NULL;
	return false;
}

template<typename I, typename T, typename Compare>
bool RBTree<I, T, Compare>::iterate( typename RBTree<I, T, Compare>::Iterator * it, I ** i, T ** v ) const {
	auto node( ( *it ) );
	if ( node == NULL )
		return false;

	( *i ) = &( node -> getValue() -> getIndex() );
	( *v ) = &( node -> getValue() -> getValue() );

	iterate( it );
	return true;
}

template<typename I, typename T, typename Compare>
template<typename TestFunctor>
bool RBTree<I, T, Compare>::iterate( typename RBTree<I, T, Compare>::Iterator * it, I ** i, T ** v, TestFunctor & testFunctor ) const {
	auto node( ( *it ) );
	if ( node == NULL )
		return false;

	( *i ) = &( node -> getValue() -> getIndex() );
	( *v ) = &( node -> getValue() -> getValue() );

	if ( testFunctor( ( *v ) ) ) {
		iterate( it );
		return true;
	} else {
		return false;
	}
}

template<typename I, typename T, typename Compare>
bool RBTree<I, T, Compare>::iterateAscending( typename RBTree<I, T, Compare>::Iterator * it ) const {
	auto node( ( *it ) );

	// While there is still data bigger, go to it.
	if (node->getRight()) {
		node = node->getRight();
		while (node->getLeft()) {
			node = node->getLeft();
		}
		(*it) = node;
		return true;

	}
	else {
		// Ok, no more greater at this stage, let's go back.
		while (node->getParent()) {
			// Check if the current node come from left or right.
			if (node == node->getParent()->getLeft()) {
				// We came from left. This mean the parent this greater, fine !
				(*it) = node->getParent();
				return true;
			}
			else {
				// We came from right. This mean the parent is smaller, go back one more time.
				node = node->getParent();
			}

		}

		// No parent, look's like we finished here.
		(*it) = NULL;
		return false;
	}
	// Should never access here.
	return false;
}

template<typename I, typename T, typename Compare>
bool RBTree<I, T, Compare>::iterateAscending(typename RBTree<I, T, Compare>::Iterator* it, I** i, T** v) const {
	auto node((*it));
	if (node == NULL)
		return false;

	(*i) = &(node->getValue()->getIndex());
	(*v) = &(node->getValue()->getValue());

	iterateAscending(it);
	return true;
}

template<typename I, typename T, typename Compare>
template<typename TestFunctor>
bool RBTree<I, T, Compare>::iterateAscending(typename RBTree<I, T, Compare>::Iterator* it, I** i, T** v, TestFunctor& testFunctor) const {
	auto node((*it));
	if (node == NULL)
		return false;

	(*i) = &(node->getValue()->getIndex());
	(*v) = &(node->getValue()->getValue());

	if (testFunctor((*v))) {
		iterateAscending(it);
		return true;
	}
	else {
		return false;
	}
}

template<typename I, typename T, typename Compare>
typename RBTree<I, T, Compare>::Iterator RBTree<I, T, Compare>::getBegin() const {
	return this -> rootNode;
}

template<typename I, typename T, typename Compare>
typename RBTree<I, T, Compare>::Iterator RBTree<I, T, Compare>::begin() const {
	return getBegin();
}

template<typename I, typename T, typename Compare>
typename RBTree<I, T, Compare>::Iterator RBTree<I, T, Compare>::getEnd() const {
	return NULL;
}

template<typename I, typename T, typename Compare>
typename RBTree<I, T, Compare>::Iterator RBTree<I, T, Compare>::end() const {
	return NULL;
}

template<typename I, typename T, typename Compare>
typename RBTree<I, T, Compare>::Iterator RBTree<I, T, Compare>::getSmallest() const {
	auto node(this->rootNode);

	// Go Left until we can't anymore.
	while (node->getLeft())
		node = node->getLeft();

	return node;
}

template<typename I, typename T, typename Compare>
const T & RBTree<I, T, Compare>::getValueIt( typename RBTree<I, T, Compare>::Iterator it ) const {
	return it -> getValue().getValue();
}

template<typename I, typename T, typename Compare>
T & RBTree<I, T, Compare>::getValueIt( typename RBTree<I, T, Compare>::Iterator it ) {
	return it -> getValue().getValue();
}

template<typename I, typename T, typename Compare>
const I & RBTree<I, T, Compare>::getIndexIt( typename RBTree<I, T, Compare>::Iterator it ) const {
	return it -> getValue().getIndex();
}

template<typename I, typename T, typename Compare>
I & RBTree<I, T, Compare>::getIndexIt( typename RBTree<I, T, Compare>::Iterator it ) {
	return it -> getValue().getIndex();
}

template<typename I, typename T, typename Compare>
void RBTree<I, T, Compare>::setValueIt( typename RBTree<I, T, Compare>::Iterator it, const T & v ) {
	return it -> getValue().setValue( v );
}

template<typename I, typename T, typename Compare>
void RBTree<I, T, Compare>::setIndexIt( typename RBTree<I, T, Compare>::Iterator it, const I & v ) {
	return it -> getValue().setIndex( v );
}

template<typename I, typename T, typename Compare /*= Math::Logical::Less*/>
bool RBTree<I, T, Compare>::isEmpty() const {
	return ( rootNode == NULL );
}


/************************************************************************/
/* MAP                                                                  */
/************************************************************************/

/*

template<typename I, typename T, typename Compare>
Map<I, T, Compare>::Map( const Compare & compareFunc ) : RBTree<I, T, Compare>(compareFunc) {

}

template<typename I, typename T, typename Compare>
Map<I, T, Compare>::Map( const Map<I, T, Compare> & map ) : Vector< MapObject<I, T> *>( map ), RBTree<I, T, Compare>( map ) {

}

template<typename I, typename T, typename Compare>
Map<I, T, Compare>::Map( Map<I, T, Compare> && map ) :
	Vector< MapObject<I, T> *>( Utility::toRValue( map ) ),
	RBTree<I, T, Compare>( Utility::toRValue( map ) )
{

}

template<typename I, typename T, typename Compare>
template<typename C>
BasicString<C> Map<I, T, Compare>::toString() const {
	return RBTree<I, T, Compare>::toString();
}

template<typename I, typename T, typename Compare>
template<typename C>
Map<I, T, Compare>::operator BasicString<C>() const {
	return toString<C>();
}

template<typename I, typename T, typename Compare>
Map<I, T, Compare> & Map<I, T, Compare>::operator=( const Map & tree ) {
	Vector< MapObject<I, T> * >::operator=( tree );
	RBTree<I, T, Compare>::operator=( tree );
	return *this;
}

template<typename I, typename T, typename Compare>
Map<I, T, Compare> & Map<I, T, Compare>::operator=( Map && tree ) {
	Vector< MapObject<I, T> * >::operator=( Utility::toRValue( tree ) );
	RBTree<I, T, Compare>::operator=( Utility::toRValue( tree ) );
	return *this;
}

template<typename I, typename T, typename Compare>
bool Map<I, T, Compare>::write( IO::SimpleFileStream * stream ) const {
	if ( !RBTree<I, T, Compare>::write( stream ) )
		return false;
	return true;
}

template<typename I, typename T, typename Compare>
void Map<I, T, Compare>::_clear() {
	Vector< MapObject<I, T> *>::_clear();
	RBTree<I, T, Compare>::_clear();
}

template<typename I, typename T, typename Compare>
T * Map<I, T, Compare>::insert( const I & index, const T & value ) {
	auto newNode( RBTree<I, T, Compare>::_insert( index, value ) );
	if ( newNode ) {
		Vector< MapObject<I, T> *>::push( const_cast< MapObject<I, T> * >( &( newNode -> getValue() ) ) );
		return const_cast<T *>(&(newNode -> getValue().getValue()));
	}
	return NULL;
}

template<typename I, typename T, typename Compare>
bool Map<I, T, Compare>::read( IO::SimpleFileStream * stream ) {
	if ( !RBTree<I, T, Compare>::read( stream ) ) {
		_clear();
		return false;
	}
	Vector< MapObject<I, T> *>::clear();

	if ( RBTree<I, T, Compare>::rootNode == NULL )
		return true;

	Vector< MapObject<I, T> *>::reserve( 10 );
	Vector < RBNode<MapObject<I, T> > *> stack;
	stack.reserve( 10 );
	stack.push( RBTree<I, T, Compare>::rootNode );

	while ( stack.getSize() ) {
		RBNode< MapObject<I, T> > * node = stack.pop();
		Vector< MapObject<I, T> *>::push( const_cast< MapObject<I, T> * >( &( node -> getValue() ) ) );

		if ( node -> getRight() )
			stack.push( node -> getRight() );
		if ( node -> getLeft() )
			stack.push( node -> getLeft() );
	}

	return true;
}


template<typename I, typename T, typename Compare>
const T & Map<I, T, Compare>::getValueIt( typename Map<I, T, Compare>::Iterator it ) const {
	return Vector< MapObject< I, T > * >::getValueIt( it ) -> getValue();
}

template<typename I, typename T, typename Compare>
T & Map<I, T, Compare>::getValueIt( typename Map<I, T, Compare>::Iterator it ) {
	return Vector< MapObject< I, T > * >::getValueIt( it ) -> getValue();
}

template<typename I, typename T, typename Compare>
const I & Map<I, T, Compare>::getIndexIt( typename Map<I, T, Compare>::Iterator it ) const {
	return Vector< MapObject< I, T > * >::getValueIt( it ) -> getIndex();
}

template<typename I, typename T, typename Compare>
I & Map<I, T, Compare>::getIndexIt( typename Map<I, T, Compare>::Iterator it ) {
	return Vector< MapObject< I, T > * >::getValueIt( it ) -> getIndex();
}

template<typename I, typename T, typename Compare>
const T & Map<I, T, Compare>::getValueI( typename Map<I, T, Compare>::Size i ) const {
	return Vector< MapObject< I, T > * >::getValueI( i ) -> getValue();
}

template<typename I, typename T, typename Compare>
T & Map<I, T, Compare>::getValueI( typename Map<I, T, Compare>::Size i ) {
	return Vector< MapObject< I, T > * >::getValueI( i ) -> getValue();
}

template<typename I, typename T, typename Compare>
const I & Map<I, T, Compare>::getIndexI( typename Map<I, T, Compare>::Size i ) const {
	return Vector< MapObject< I, T > * >::getValueI( i ) -> getIndex();
}

template<typename I, typename T, typename Compare>
I & Map<I, T, Compare>::getIndexI( typename Map<I, T, Compare>::Size i ) {
	return Vector< MapObject< I, T > * >::getValueI( i ) -> getIndex();
}

template<typename I, typename T, typename Compare>
void Map<I, T, Compare>::setValueIt( typename Map<I, T, Compare>::Iterator it, const T & v ) {
	return Vector< MapObject< I, T > * >::getValueIt( it ) -> setValue( v );
}

template<typename I, typename T, typename Compare>
void Map<I, T, Compare>::setIndexIt( typename Map<I, T, Compare>::Iterator it, const I & v ) {
	return Vector< MapObject< I, T > * >::getValueIt( it ) -> setIndex( v );
}

template<typename I, typename T, typename Compare>
void Map<I, T, Compare>::setValueI( typename Map<I, T, Compare>::Size i, const T & v ) {
	return Vector< MapObject< I, T > * >::getValueI( i ) -> setValue( v );
}

template<typename I, typename T, typename Compare>
void Map<I, T, Compare>::setIndexI( typename Map<I, T, Compare>::Size i, const I & v ) {
	return Vector< MapObject< I, T > * >::getValueI( i ) -> setIndex( v );
}



template<typename I, typename T, typename Compare>
bool Map<I, T, Compare>::iterate( typename Map<I, T, Compare>::Iterator * it ) const {
	( *it )++;
	return !( *it == getEnd() );
}

template<typename I, typename T, typename Compare>
bool Map<I, T, Compare>::iterate( typename Map<I, T, Compare>::Iterator * it, I ** i, T ** v ) const {
	if ( *it == getEnd() )
		return false;
	*i = ( *it ) -> getIndex();
	*v = ( *it ) -> getValue();
	( *it )++;
	return true;
}

template<typename I, typename T, typename Compare>
template<typename TestFunctor>
bool Map<I, T, Compare>::iterate( typename Map<I, T, Compare>::Iterator * it, I ** i, T ** v, TestFunctor & testFunctor ) const {
	if ( *it == getEnd() )
		return false;
	*i = ( *it ) -> getIndex();
	*v = ( *it ) -> getValue();
	if ( testFunctor( *v ) ) {
		( *it )++;
		return true;
	}
	return false;
}

template<typename I, typename T, typename Compare>
void Map<I, T, Compare>::isEmpty() {
	return RBTree<I, T, Compare>::isEmpty();
}

template<typename I, typename T, typename Compare>
void Map<I, T, Compare>::clear() {
	Vector< MapObject< I, T > * >::clear();
	RBTree<I, T, Compare>::clear();
}*/
