template<typename I, typename T, typename Compare>
MultiMap<I, T, Compare>::MultiMap( const Compare & compareFunc ) : Map<I, Vector<T>, Compare>( compareFunc ) {

}

template<typename I, typename T, typename Compare>
MultiMap<I, T, Compare>::MultiMap( const MultiMap<I, T, Compare> & map ) : Map<I, Vector<T>, Compare>( map ) {

}

template<typename I, typename T, typename Compare>
MultiMap<I, T, Compare>::MultiMap( MultiMap<I, T, Compare> && map ) : Map<I, Vector<T>, Compare>( Utility::toRValue( map ) ) {

}

template<typename I, typename T, typename Compare>
template<typename C>
MultiMap<I, T, Compare>::operator BasicString<C>() const {
	return toString<BasicString<C>>();
}

template<typename I, typename T, typename Compare>
MultiMap<I, T, Compare> & MultiMap<I, T, Compare>::operator=( const MultiMap<I, T, Compare> & map ) {
	Map<I, Vector<T>, Compare>::operator=( map );
	return *this;
}

template<typename I, typename T, typename Compare>
MultiMap<I, T, Compare> & MultiMap<I, T, Compare>::operator=( MultiMap<I, T, Compare> && map ) {
	Map<I, Vector<T>, Compare>::operator=( Utility::toRValue( map ) );
	return *this;
}

template<typename I, typename T, typename Compare>
T * MultiMap<I, T, Compare>::insert( const I & index, const T & value ) {
	return _insert( index, value );
}


template<typename I, typename T, typename Compare>
T * MultiMap<I, T, Compare>::_insert( const I & index, const T & value ) {
	RBNode< MapObject< I, Vector<T> > > * node( this -> rootNode );
	if ( node == NULL ) {
		RBNode< MapObject< I, Vector<T> > > * newNode( new RBNode< MapObject< I, Vector<T> > >( NULL, MapObject< I, Vector<T> >( index, Vector<T>() ) ) );
		T * valueP( newNode -> getValue().getValue().push( value ) );
		RBNode< MapObject< I, Vector<T> > >::insertNode( newNode, &this -> rootNode );
		return valueP;
	} else {
		while ( true ) {
			Math::Compare::Value compareResult( this -> compareFunc( index, node -> getValue().getIndex() ) );
			if ( compareResult == Math::Compare::Value::Equal ) {
				// We already have values for this index, not a problem, push the new one :)
				T * valueP( node -> getValue().getValue().push( value ) );
				return valueP;
			} else if ( compareResult == Math::Compare::Value::Less ) {
				if ( node -> getLeft() ) {
					node = node -> getLeft();
					continue;
				} else {
					RBNode< MapObject< I, Vector<T> > > * newNode( new RBNode< MapObject< I, Vector<T> > >( node, MapObject< I, Vector<T> >( index, Vector<T>() ) ) );
					RBNode< MapObject< I, Vector<T> > >::insertNodeLeft( node, newNode, &this -> rootNode );
					T * valueP( newNode -> getValue().getValue().push( value ) );

					#ifdef DEBUG
					RBTree<I, Vector<T>, Compare>::_checkTree( this -> rootNode, this -> compareFunc );
					#endif
					return valueP;
				}
			} else {
				if ( node -> getRight() ) {
					node = node -> getRight();
					continue;
				} else {
					RBNode< MapObject< I, Vector<T> > > * newNode( new RBNode< MapObject< I, Vector<T> > >( node, MapObject< I, Vector<T> >( index, Vector<T>() ) ) );
					RBNode< MapObject< I, Vector<T> > >::insertNodeRight( node, newNode, &this -> rootNode );
					T * valueP( newNode -> getValue().getValue().push( value ) );

					#ifdef DEBUG
					RBTree<I, Vector<T>, Compare>::_checkTree( this -> rootNode, this -> compareFunc );
					#endif
					return valueP;
				}
			}
		}
	}
	// Should never be accessed
	return NULL;
}



template<typename I, typename T, typename Compare>
bool MultiMap<I, T, Compare>::eraseFirst( const I & index, const T & value ) {
	if ( this -> rootNode ) {
		RBNode< MapObject< I, Vector<T> > > * node( this -> rootNode );
		while ( true ) {
			Math::Compare::Value compareResult( this -> compareFunc( index, node -> getValue().getIndex() ) );

			if ( compareResult == Math::Compare::Value::Equal ) {
				Vector<T> & vector( node -> getValue().getValue() );
				if ( vector.getSize() > 1 ) {
					return vector.eraseFirst( value );
				} else {
					if ( vector[0] == value ) {
						RBNode< MapObject< I, Vector<T> > >::deleteNode( node, &this -> rootNode );

						// DEBUG
						#ifdef DEBUG
						RBTree<I, Vector<T>, Compare>::_checkTree( this -> rootNode, this -> compareFunc );
						#endif
						return true;
					}
					return false;
				}
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
bool MultiMap<I, T, Compare>::eraseAll( const I & index, const T & value ) {
	if ( this -> rootNode ) {
		RBNode< MapObject< I, Vector<T> > > * node( this -> rootNode );
		while ( true ) {
			Math::Compare::Value compareResult( this -> compareFunc( index, node -> getValue().getIndex() ) );

			if ( compareResult == Math::Compare::Value::Equal ) {
				Vector<T> & vector( node -> getValue().getValue() );
				if ( vector.eraseAll( value ) ) {
					if ( !vector.getSize() ) {
						RBNode< MapObject< I, Vector<T> > >::deleteNode( node, &this -> rootNode );

						// DEBUG
						#ifdef DEBUG
						RBTree<I, Vector<T>, Compare>::_checkTree( this -> rootNode, this -> compareFunc );
						#endif
					}
					return true;
				}
				return false;
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
