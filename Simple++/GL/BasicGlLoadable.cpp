#include "BasicGlLoadable.h"


#ifdef _UI


namespace GL {

	BasicGlLoadable::BasicGlLoadable( void ) : 
		bIsGlLoaded( false ),
		bIsGlLoading( false )
	{
	
	}

	BasicGlLoadable::BasicGlLoadable( const BasicGlLoadable & glLoadable ) {
		this -> glLoadingMutex.lock();

		this -> bIsGlLoaded = glLoadable.bIsGlLoaded;
		this -> bIsGlLoading = glLoadable.bIsGlLoading;

		this -> glLoadingMutex.unlock();
	}

	BasicGlLoadable::~BasicGlLoadable( void ) {
	}

	bool BasicGlLoadable::glLoad() {
		this -> glLoadingMutex.lock();

		if ( this -> bIsGlLoaded ) {
			// Object already loaded, nothing to do.
			this -> glLoadingMutex.unlock();
			return true;
		}

		this -> bIsGlLoading = true;
		if ( onGlLoad() ) {
			this -> bIsGlLoading = false;
			this -> bIsGlLoaded = true;
			this -> glLoadingMutex.unlock();
			return true;
		} else {
			this -> bIsGlLoading = false;
			this -> glLoadingMutex.unlock();
			return false;
		}
	}

	bool BasicGlLoadable::isGlLoaded() const {
		return this -> bIsGlLoaded;
	}

	bool BasicGlLoadable::isGlLoading() const {
		return this -> bIsGlLoading;
	}

	void BasicGlLoadable::setGlLoaded( bool bIsGlLoaded ) {
		this -> bIsGlLoaded = bIsGlLoaded;
	}

	bool BasicGlLoadable::glUnload() {
		this -> glLoadingMutex.lock();

		if ( !this -> bIsGlLoaded ) {
			// Object not loaded, nothing to do.
			this -> glLoadingMutex.unlock();
			return true;
		}

		if ( onGlUnload() ) {
			this -> bIsGlLoaded = false;
			this -> glLoadingMutex.unlock();
			return true;
		} else {
			this -> glLoadingMutex.unlock();
			return true;
		}
	}

	bool BasicGlLoadable::glReload() {
		if ( isGlLoaded() ) {
			if ( glUnload() && glLoad() )
				return true;
			else
				return false;
		} else {
			return true;
		}
		
	}

	bool BasicGlLoadable::onGlLoad() {
		return true;
	}

	bool BasicGlLoadable::onGlUnload() {
		return true;
	}


	BasicGlLoadable & BasicGlLoadable::operator=( const BasicGlLoadable & loadable ) {
		this -> glLoadingMutex.lock();
		this -> bIsGlLoaded = loadable.bIsGlLoaded;
		this -> bIsGlLoading = loadable.bIsGlLoading;
		this -> glLoadingMutex.unlock();

		return *this;
	}



}

#endif // _UI

