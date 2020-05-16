///@file BasicGlLoadable.h
///@brief Base of every object loadable on the GPU
///@author Clement Gerber
///@date 01/12/16 (DMY)

#pragma once

#include "../BuildConfig.h"
#include "../Mutex.h"
#ifdef _UI



namespace GL {
	class BasicGlLoadable {
	public:
		BasicGlLoadable();
		
		///@brief Copy Constructor
		///@param glLoadable Object to be loaded
		BasicGlLoadable( const BasicGlLoadable & glLoadable );

		///@brief This object can freely be deleted using a reference or pointer to a BasicGlLoadable if inherited
		virtual ~BasicGlLoadable();

		///@brief Copy operator
		///@param glLoadable Object to be copied
		///@return reference to THIS
		BasicGlLoadable & operator=( const BasicGlLoadable & glLoadable );
		
		///@brief Load this object to the GPU
		///@return True if the loading has succeeded, False otherwise
		bool glLoad();

		///@brief Unload this object from the GPU
		///@return True if the unloading has succeeded, False otherwise
		bool glUnload();

		///@brief Unload and Load again this object (only if already loaded)
		///@return True if the object has been unloaded and loaded again successfully, False otherwise
		bool glReload();

		///@brief If the object is already loaded or not
		///@return Boolean true if this object is loaded
		bool isGlLoaded() const;

		///@brief If the object is already loading to the GPU
		///@return Boolean true if the object is currently loading, false otherwise.
		bool isGlLoading() const;
	protected:
		///@brief Set the active state if loaded or not (use with caution)
		///@param If the object is loaded or not
		void setGlLoaded( bool bIsGlLoaded );

		///@brief Virtual function to be overloaded, defining the action to do when the object is loading
		///@return True if the loading to the GPU has succeeded. False otherwise
		virtual bool onGlLoad();

		///@brief Virtual function to be overloaded, defining the action to do when the object is unloaded
		///@return True if the unloading from the GPU has succeeded. False otherwise
		virtual bool onGlUnload();

	private:
		bool bIsGlLoaded;
		bool bIsGlLoading;
		Mutex glLoadingMutex;
	};

}
#endif


