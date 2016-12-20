#pragma once

#include "Mutex.h"

class BasicLoadable {
public:
	///@brief Empty constructor initialized at NOT loaded and NOT loading.
	BasicLoadable();


	///@brief copy constructor
	///@param loadable Another loadable object to be copied.
	BasicLoadable( const BasicLoadable & loadable );

	virtual ~BasicLoadable();

	///@brief load the object (this function may not be overloaded)
	///@return True if the object has been loaded successfully, False otherwise
	bool load();

	///@brief unload this object (this function may not be overloaded)
	///@return True if the object has been unloaded successfully, False otherwise
	bool unload();

	///@brief if the current object is loaded, unload it and then call load again, if not, this do nothing.
	///@return True if the object has been unloaded and loaded again successfully, False otherwise
	bool reload();

	///@brief get if the current object is loaded or not
	///@return Boolean to know if the current object is loaded or not.
	bool isLoaded() const;

	///@brief get if the current object is currently loading
	///@return Boolean to know if the current object is loading actually
	bool isLoading() const;

	///@brief lock the current object to ensure no parallelization of the loading state. (Locking an already locked object will trigger a crash)
	void lock();

	///@brief unlock the current object to permit parallelization of the loading state. (unlocking an non locked object will trigger a crash)
	void unlock();


	///@brief copy operator
	///@param loadable another object to be copied.
	///@return reference to this object
	BasicLoadable & operator = ( const BasicLoadable & loadable );

protected:
	///@brief set if the current object is loaded or not. (use with caution)
	///@param loaded Boolean to set if the current object is loaded or not.
	void setLoaded( bool loaded );

	///@brief set if the current object is currently loading (use with caution)
	///@param isLoading if the current object is loading or not.
	void setLoading( bool isLoading );

	///@brief function to be overloaded to add action during the loading process.
	///@return True if the loading has succeeded, False otherwise
	virtual bool onLoad();

	///@brief function to be overloaded to add action during the unloading process.
	///@return True if the unloading has succeeded, False otherwise
	virtual bool onUnload();

private:
	bool mIsloaded;
	bool bIsLoading;
	Mutex mutex;
};

