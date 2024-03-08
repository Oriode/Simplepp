///@file Text.h
///@brief File containing the Text Object 
///@date 17/10/16 (DMY)
///@author Clement Gerber
#pragma once


#include "Image.h"
#include "Font.h"

namespace Graphic {



	///@brief Text Object representing an Image of Type T automatically rendered and sized with the specified Text and Font.
	template<typename T>
	class Text : public ImageT<T> {
	public:

		///@brief Empty constructor
		///@brief format Format to be used for the image render
		Text( Format format = Format::RGBA );


		///@brief Constructor which render directly
		///@param font Font file used to render
		///@param str StringASCII to be rendered
		///@param centering How the text has to be centered in the image
		///@param format Format of the resulting image
		template<typename LoadingFunc>
		Text( const FontT<T, LoadingFunc> & font, const UTF8String & str, const Math::Vec2<bool> & centering = Math::Vec2<bool>(false), Format format = Format::RGBA );

		///@brief Copy Constructor
		///@param text Text to be copied
		Text( const Text & text );

		///@brief Move Constructor
		///@param text Text to be moved
		Text( Text && text );

		///@brief Copy Operator
		///@param text Text to be copied
		///@return reference to this
		Text & operator=( const Text & text );

		///@brief Move Operator
		///@param text Text to be moved
		///@return reference to this
		Text & operator=( Text && text );

		///@brief set the text to be rendered
		///@param font Font file used to render
		///@param str StringASCII to be rendered
		///@param centering How the text has to be centered in the image
		template<typename LoadingFunc>
		void setText( const FontT<T, LoadingFunc> & font, const UTF8String & str, const Math::Vec2<bool> & centering = Math::Vec2<bool>( false ) );

		///@brief Get the centering of this Text
		///@return Vec2<bool> where x is the centering horizontal and y vertical
		const Math::Vec2<bool> & getCentering() const;

		///@brief Get the Margins of this text
		///@return Rectangle representing the 4 margins (Left, Bottom, Right, Top)
		const Math::Rectangle<float> & getMargins() const;

		///@brief Get the Bias of this text (Used to draw it)
		///@return Bias of this text
		const Math::Vec2<float> & getBias() const;

		///@brief read from a file stream
		///@param stream stream used to read load this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool read( Stream * stream, int verbose = 0 );

		///@brief write this object as binary into a file stream
		///@param stream stream used to write this object
		///@return boolean to know if the operation is a success of not.
		template<typename Stream>
		bool write( Stream * stream ) const;
	private:
		template<typename LoadingFunc, typename Functor>
		void _setText( const FontT<T, LoadingFunc> & font, const UTF8String & str, const Math::Vec2<bool> & centering, Functor & func );
		void _clear();
		

		Math::Vec2<bool> centering;
		Math::Rectangle<float> margins;
		Math::Vec2<float> bias;
		UTF8String str;
	};

}



#include "Text.hpp"



