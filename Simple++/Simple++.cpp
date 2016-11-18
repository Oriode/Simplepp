///@file Simple++.cpp
///@brief Main file used for doing some test
///@author Clement Gerber
///@date 26/05/2016 (DMY) 


//#define SPEEDTEST_DRAWLINE
//#define SPEEDTEST_DRAWLINE_FLOAT
//#define SPEEDTEST_GRAPH
//#define SPEEDTEST_ROUNDEDRECTANGLE
//#define SPEEDTEST_DISK
//#define SPEEDTEST_POLYGON
//#define SPEEDTEST_STROKE
//#define SPEEDTEST_RESAMPLE
//#define SPEEDTEST_DRAWTEXT
//#define SPEEDTEST_FILTER
//#define SPEEDTEST_ARRAYACCESS
//#define SPEEDTEST_LOGICAL
//#define SPEEDTEST_BLENDING
//#define SPEEDTEST_DATE
//#define SPEEDTEST_STRING_CONCAT
//#define SPEEDTEST_STRING_CAST
//#define SPEEDTEST_REGEX
//#define SPEEDTEST_VECTOR
#define SPEEDTEST_MAP
//#define SPEEDTEST_NETWORK
//#define SPEEDTEST_CAST
//#define SPEEDTEST_ARITHMETIC


//#define DEBUG_GRAPHIC
#define DEBUG_XML
//#define DEBUG_MAP

#ifndef _LIB
#include <iostream>
#include <string>
#include <chrono>
#include <map>
#include <regex>
#include <functional>

#include "Network/Network.h"
#include "Math/Math.h"
#include "String.h"
#include "Log.h"
#include "UTF8String.h"
#include "Map.h"
#include "Application.h"
#include "FreeImage.h"
#include "Graphic.h"
#include "Utility.h"
#include "Regex.h"
#include "Time/Time.h"
#include "Test.h"
#include "XML/XMLDocument.h"


template<typename T>
class ImageFunctor {
public:
	ImageFunctor() {};
	ImageFunctor & operator()( const Math::Vec2<Graphic::Size> & p, Graphic::ColorR<T> & color ) { return *this; }
	ImageFunctor & operator()( const Math::Vec2<Graphic::Size> & p, Graphic::ColorRGB<T> & color ) {
		unsigned int len = Math::length( p );
		color.r += len;
		color.g -= len;
		color.b += color.r + color.g;
		return *this;
	}
	ImageFunctor & operator()( const Math::Vec2<Graphic::Size> & p, Graphic::ColorRGBA<T> & color ) { return *this; }
};






int main( int argc, char * argv[] ) {


	#ifdef DEBUG 
	/************************************************************************/
	/* DEBUG PART															*/
	/************************************************************************/

	//Application<char> app( argc, argv );



	/************************************************************************/
	/* MAPS                                                                 */
	/************************************************************************/
	/*{
		Map<unsigned long, unsigned long> mapMine;
		std::map<unsigned long, unsigned long> mapSTD;

		Log::startChrono();
		for ( unsigned long i = 0; i < 1000; i++ ) {
			mapSTD.insert( std::pair<unsigned long, unsigned long>( Math::random( 0, 100000 ), i ) );
		}
		Log::stopChrono();
		Log::displayChrono( "Map .insert(); STD" );

		Log::startChrono();
		for ( unsigned long i = 0; i < 1000; i++ ) {
			mapMine.insert( Math::random( 0, 100000 ), i );
		}
		Log::stopChrono();
		Log::displayChrono( String( "Map .insert(); Mine " ) );
		for ( auto it = mapMine.getBegin(); it != mapMine.getEnd(); it++ ) {
			Log::displayLog( String( mapMine.getIndexit(it) ) + " : " + mapMine.getValueIt(it) );
		}
	}*/




	/*Vector<int *> testVector;

	for ( size_t i( 0 ); i < 1000; i++ ) {
		testVector.push( new int( i ) );
	}*/


	/************************************************************************/
	/* XML PART																*/
	/************************************************************************/
	#ifdef DEBUG_XML
	{
		UTF8String testStr( "Hello world" );
		UTF8String testDocumentStr( "<?xml version=\"1.0\" encoding=\"UTF - 8\"?><class testParam=\"xD\">test</class>" );
		XML::Document testDocument( WString("test.xml") );

		assert( IO::write( WString( "testXML.cxml" ), &testDocument ) );
		assert( IO::read( WString( "testXML.cxml" ), &testDocument ) );

		testDocument.writeXML( WString( "testOut.xml" ) );

		auto nodeTest( testDocument.getElementsById( "test" ) );

		if ( nodeTest.getSize() ) {
			log( nodeTest[0] -> getValue() );
		}

		int test;

	}
	#endif

	#ifdef DEBUG_MAP
	{

		auto r = Math::Compare::compare( UTF8String( "Hello" ), UTF8String( "World" ) );

		Map<unsigned long, unsigned long> testMap;

		testMap.insert( 0, 0 );
		testMap.insert( 1, 1 );
		testMap.insert( 2, 2 );
		testMap.insert( 3, 3 );
		testMap.insert( 4, 4 );
		testMap.insert( 5, 5 );
		testMap.insert( 6, 6 );
		testMap.insert( 7, 7 );
		testMap.insert( 8, 8 );
		testMap.insert( 9, 9 );


		for ( auto it( testMap.getBegin() ); it != testMap.getEnd(); testMap.iterate( &it ) ) {
			log( testMap.getValueIt( it ) );


		}

		log( String( testMap ) );


		{
			// Testing IN/OUT
			assert( IO::write( WString( "myMap.font" ), &testMap ) );

			Map<unsigned long, unsigned long> mapLoaded;
			assert( IO::read( WString( "myMap.font" ), &mapLoaded ) );

			log( String( mapLoaded ) );
		}

		{
			// Testing Copy
			Map<unsigned long, unsigned long> mapCopied = testMap ;

			log( String( mapCopied ) );

		}

		for ( size_t j( 0 ); j < 100; j++ ) {
			Map<unsigned long, unsigned long> testMap;
			for ( size_t i( 0 ); i < 100; i++ ) {
				testMap.insert( i, i );
			}
			testMap.eraseIndex( j );
		}
	
		for ( size_t i( 0 ); i < 1000; i++ ) {
			testMap.insert( Math::random( 0, 1000 ), i );
		}


		for ( size_t i( 0 ); i < 1000; i++ ) {
			testMap.eraseIndex( Math::random( 0, 1000 ));
		}
		//log( String( testMap ) );
		

	}
	#endif





	#ifdef DEBUG_GRAPHIC
	/************************************************************************/
	/* GRAPHIC PART									                        */
	/************************************************************************/

	Graphic::ColorRGB<unsigned char> colorUC( 6, 0, 8 );
	Graphic::ColorRGB<float> colorF(0.33, 0.86, 0.96);

	log( String( colorF.HSLtoRGB() ) );


/*
	Graphic::FontLoadable<unsigned char> font( L"consola.ttf", 40 );
	font.load();
	font.loadGlyph( Graphic::Font<unsigned char>::Template::Ascii );
	font.writeToFile( L"consola.cfont" );


	Graphic::FontLoadable<unsigned char> font2( L"consola.cfont" );
	font2.load();

	font.writeToFile( L"consola2.cfont" );

	Graphic::FreeImage glyphFreeImage;
	glyphFreeImage.loadFromDatas( ( unsigned char * ) font2['A'] -> getDatas(), font2['A'] -> getSize(), Graphic::FreeImage::Format::R );
	glyphFreeImage.saveToFile( "glyph_A.png", Graphic::FreeImage::SavingFormat::PNG );
*/

	Graphic::FreeImage freeImage( "sanctum.png", Graphic::FreeImage::Format::RGB );
	freeImage.load();

	Graphic::TextureLoadable<unsigned char> texture;
	texture.setDatas( ( unsigned char * ) freeImage.getDatas(), freeImage.getSize(), Graphic::LoadingFormat::BGR );
	texture.generateMipmaps();
	texture.writeToFile( "sanctum.ctexture" );

	
	Graphic::TextureLoadable<unsigned char> texture2( WString( "sanctum.ctexture" ) );
	texture2.load();
	texture2.writeToFile( "sanctum2.ctexture" );

	/************************************************************************/
	/* DOING SOME TEST IN imageTest2                                        */
	/************************************************************************/

	Graphic::ColorRGBA<unsigned char> colorWhite( 255, 255, 255, 100 );
	Graphic::ColorRGBA<unsigned char> colorRed( 255, 0, 0, 255 );
	Graphic::ColorRGB<unsigned char> colorMagenta( 255, 0, 150 );
	Graphic::ColorRGBA<unsigned char> colorBlack( 0, 0, 0, 150 );
	Graphic::ColorRGBA<unsigned char> colorTransluscient( 0, 0, 0, 0 );

	
	Graphic::Gradient::Vertical<Graphic::ColorRGBA<unsigned char>, Math::InterpolationFunc::Linear> gradientVertical;
	gradientVertical.addPoint( 0.0f, Graphic::ColorRGBA<unsigned char>( 255, 255, 255, 255 ) );
	gradientVertical.addPoint( 1.0f, Graphic::ColorRGBA<unsigned char>( 100, 100, 100, 255 ) );



	Graphic::Gradient::Horizontal<Graphic::ColorRGBA<unsigned char>, Math::InterpolationFunc::Linear> gradientHorizontal;
	gradientHorizontal.addPoint( 0.0f, Graphic::ColorRGBA<unsigned char>( 0, 0, 0, 255 ) );
	gradientHorizontal.addPoint( 1.0f, Graphic::ColorRGBA<unsigned char>( 255, 255, 255, 255 ) );


	Graphic::Gradient::Linear<Graphic::ColorRGBA<unsigned char>, Math::InterpolationFunc::Cubic> gradientLinear( 45 );
	gradientLinear.addPoint( 0.0f, Graphic::ColorRGBA<unsigned char>( 0, 0, 0, 255 ) );
	gradientLinear.addPoint( 0.2f, Graphic::ColorRGBA<unsigned char>( 255, 0, 0, 255 ) );
	gradientLinear.addPoint( 0.4f, Graphic::ColorRGBA<unsigned char>( 0, 255, 0, 255 ) );
	gradientLinear.addPoint( 0.6f, Graphic::ColorRGBA<unsigned char>( 0, 0, 0, 0 ) );
	gradientLinear.addPoint( 0.8f, Graphic::ColorRGBA<unsigned char>( 0, 255, 255, 255 ) );
	gradientLinear.addPoint( 1.0f, Graphic::ColorRGBA<unsigned char>( 0, 255, 255, 255 ) );


	Graphic::Gradient::Radial<Graphic::ColorRGBA<unsigned char>, Math::InterpolationFunc::Cubic> gradientRadial( Math::Vec2<float>( 0.5, 0.5 ), Math::Vec2<float>( 0.5, 0.5 ) );
	gradientRadial.addPoint( 0.0f, Graphic::ColorRGBA<unsigned char>( 0, 0, 0, 255 ) );
	gradientRadial.addPoint( 0.2f, Graphic::ColorRGBA<unsigned char>( 255, 0, 0, 255 ) );
	gradientRadial.addPoint( 0.4f, Graphic::ColorRGBA<unsigned char>( 0, 255, 0, 255 ) );
	gradientRadial.addPoint( 0.6f, Graphic::ColorRGBA<unsigned char>( 0, 0, 0, 0 ) );
	gradientRadial.addPoint( 0.8f, Graphic::ColorRGBA<unsigned char>( 0, 255, 255, 255 ) );
	gradientRadial.addPoint( 1.0f, Graphic::ColorRGBA<unsigned char>( 0, 255, 255, 255 ) );

	Graphic::Image image( *( texture2[0] ) );


	/*{
		//////////////////////////////////////////////////////////////////////////
		// Fill Image										//
		image.fillImage( Graphic::ColorR<unsigned char>( 255 ) );
	}*/

	{
		//////////////////////////////////////////////////////////////////////////
		// Copy Image										//
		Graphic::Image imageCopy = image;
		image = imageCopy;
	}

	/*{
		Graphic::ImageT<float> imagef( image );
		Graphic::Image mipmap( *(imagef.createMipmap()) );
		image = imagef;
		image.drawImage( Graphic::Point( 0, 0 ), mipmap );
	}*/


	/*{
		//////////////////////////////////////////////////////////////////////////
		// Change Hue Saturation Lightness Image								//
		image.changeHueSaturationLightness( 360, 1.0, 1.0f );
	}*/

	/*{
		//////////////////////////////////////////////////////////////////////////
		// Apply Non symmetrical Filter Image									//

		image = image.applySobelFilter();


	}*/

	/*{
		//////////////////////////////////////////////////////////////////////////
		// Blur Image															//
		image = image.applyGaussianBlur( 5, Graphic::Image::ConvolutionMode::NormalSize, Graphic::ColorRGBA<unsigned char>( 0, 0, 0, 0 ) );
	}*/

	/*{
		//////////////////////////////////////////////////////////////////////////
		// Apply Functor														//
		image.setPixels(ImageFunctor<unsigned char>());
	}*/

	/*{
		//////////////////////////////////////////////////////////////////////////
		// Thresholding the image												//
		image.threshold( Graphic::ColorRGBA<unsigned char>( 255 ), Graphic::ColorRGBA<unsigned char>( 0 ), Graphic::ColorRGBA<unsigned char>( 128, 0, 0, 0 ) );
	}*/



	/*{
		//////////////////////////////////////////////////////////////////////////
		// Blur Image															//
		unsigned int mySuperKernel2[11];
		Graphic::computeGaussianKernel(mySuperKernel2);


		image = image.applyFilter(mySuperKernel2, Graphic::Image::ConvolutionMode::NormalSize, Graphic::ColorRGBA<unsigned char>(0, 0, 0, 0));

// 		float mySuperKernel2[11];
// 		Graphic::computeGaussianKernel( mySuperKernel2 );
// 		Graphic::_Image<float> imagef( image );
//
// 		image = imagef.applyFilter( mySuperKernel2, Graphic::_Image<float>::ConvolutionMode::NormalSize, Graphic::ColorRGBAf( 0, 0, 0, 0 ) );
	}*/

	/*{
		//////////////////////////////////////////////////////////////////////////
		// Stroke																//
		image.drawStrokeFunctor(Graphic::Point(0, 0), image, 2, Graphic::ColorFunc::SimpleColor<Graphic::ColorRGBA<unsigned char>>(Graphic::ColorRGBA<unsigned char>(0, 255, 0, 255)), Graphic::Image::StrokeType::Middle);
	}*/


	
		/*{
			//////////////////////////////////////////////////////////////////////////
			// Draw Line										//
			Graphic::ColorR<unsigned char> colorBlack(0);

			Graphic::ColorRGB<unsigned char> colorRed(255,0,0);

			image.drawLine(Graphic::LineF(250, 250, 500, 500), colorBlack, 5);
			image.drawLine(Graphic::LineF(250, 250, 500, 400), colorBlack, 5);
			image.drawLine(Graphic::LineF(250, 250, 500, 300), colorBlack, 5);
			image.drawLine(Graphic::LineF(250, 250, 500, 250), colorBlack, 5);
			image.drawLine(Graphic::LineF(250, 250, 500, 200), colorBlack, 5);
			image.drawLine(Graphic::LineF(250, 250, 500, 100), colorBlack, 5);
			image.drawLine(Graphic::LineF(250, 250, 500, 0), colorBlack, 5);

			image.drawLine(Graphic::LineF(250, 250, 0, 500), colorBlack, 5);
			image.drawLine(Graphic::LineF(250, 250, 0, 400), colorBlack, 5);
			image.drawLine(Graphic::LineF(250, 250, 0, 300), colorBlack, 5);
			image.drawLine(Graphic::LineF(250, 250, 0, 250), colorBlack, 5);
			image.drawLine(Graphic::LineF(250, 250, 0, 200), colorBlack, 5);
			image.drawLine(Graphic::LineF(250, 250, 0, 100), colorBlack, 5);
			image.drawLine(Graphic::LineF(250, 250, 0, 0), colorBlack, 5);

			image.drawLine(Graphic::LineF(250, 250, 0, 0), colorBlack, 5);
			image.drawLine(Graphic::LineF(250, 250, 100, 0), colorBlack, 5);
			image.drawLine(Graphic::LineF(250, 250, 200, 0), colorBlack, 5);
			image.drawLine(Graphic::LineF(250, 250, 250, 0), colorBlack, 5);
			image.drawLine(Graphic::LineF(250, 250, 300, 0), colorBlack, 5);
			image.drawLine(Graphic::LineF(250, 250, 400, 0), colorBlack, 5);
			image.drawLine(Graphic::LineF(250, 250, 500, 0), colorBlack, 5);

			image.drawLine(Graphic::LineF(250, 250, 100, 500), colorBlack, 5);
			image.drawLine(Graphic::LineF(250, 250, 200, 500), colorBlack, 5);
			image.drawLine(Graphic::LineF(250, 250, 250, 500), colorBlack, 5);
			image.drawLine(Graphic::LineF(250, 250, 300, 500), colorBlack, 5);
			image.drawLine(Graphic::LineF(250, 250, 400, 500), colorBlack, 5);
			image.drawLine(Graphic::LineF(250, 250, 500, 500), colorBlack, 5);

		}*/
		/*{
			//////////////////////////////////////////////////////////////////////////
			// Draw Bezier UChar									//


			Graphic::ColorRGBA<unsigned char> colorRed(255, 0, 0, 128);
			image.drawBezierCurve(Graphic::PointF(0, 0), Graphic::PointF(100, 400), Graphic::PointF(400, 100), Graphic::PointF(500, 500), 3, colorRed);
			image.drawBezierCurve(Graphic::PointF(0, 499), Graphic::PointF(100, 100), Graphic::PointF(400, 400), Graphic::PointF(500, 0), 3, colorRed);

		}*/


		/*{
			//////////////////////////////////////////////////////////////////////////
			// Draw Bezier float									//

			Graphic::_Image<float> imageF(image);

			Graphic::ColorRGBA<float> colorRed(1.0f, 0.0f, 0.0f, 0.5f);
			imageF.drawBezierCurve(Graphic::PointF(0, 0), Graphic::PointF(100, 400), Graphic::PointF(400, 100), Graphic::PointF(500, 500), 3, colorRed);
			imageF.drawBezierCurve(Graphic::PointF(0, 499), Graphic::PointF(100, 100), Graphic::PointF(400, 400), Graphic::PointF(500, 0), 3, colorRed);




			image = imageF;

		}*/






	{
		//////////////////////////////////////////////////////////////////////////
		// Draw Text Glyph									//
		//auto maskTest = font['A'];
		//image.drawImage(Graphic::Point(300, 300), colorRed, Graphic::Rectangle(maskTest  -> getSize()), *maskTest);
	}



	{
		//////////////////////////////////////////////////////////////////////////
		// Draw Rectangle RGBA									//
		//image.drawRectangle(Graphic::Rectangle(0, 0, 250, 250), Graphic::ColorRGBA<unsigned char>(0, 255, 255, 100));
	}

	/*{
		//////////////////////////////////////////////////////////////////////////
		// Draw Gradient as Functor								//
		Graphic::ColorFunc::Gradient::Vertical<Graphic::ColorRGBA<unsigned char>, Graphic::InterpolationFunc::Cubic> testFunctorGradient( gradientVertical );
		image.drawRectangleFunctor( Graphic::Rectangle( 0, 0, 500, 500 ), testFunctorGradient );
	}*/
/*
	{
		//////////////////////////////////////////////////////////////////////////
		// Draw Text Point									//
		image.fillImage( Graphic::ColorRGB<unsigned char>( 255 ) );

		Graphic::Image imageTxt( Math::Vec2<Graphic::Size>( 500, 500 ), Graphic::Format::R );
		imageTxt.fillImage( Graphic::ColorR<unsigned char>( 0 ) );
		UTF8String testStr( "Hello World" );
		Graphic::drawText( &imageTxt, font, Graphic::Point( 250, 250 ), testStr, Graphic::ColorR<unsigned char>( 255 ), Math::Vec2<bool>( true, true ) );

		image.drawImageShadow( Graphic::Point( 0, 0 ), 0, imageTxt, Graphic::ColorRGBA<unsigned char>( 0, 0, 0, 255 ) );

		Graphic::ColorFunc::Gradient::Radial<Graphic::ColorRGBA<unsigned char>, Math::InterpolationFunc::Cubic> testFunctorGradientRadial( gradientRadial );
		Graphic::ColorFunc::Gradient::Vertical<Graphic::ColorRGBA<unsigned char>, Math::InterpolationFunc::Cubic> testFunctorGradientVertical( gradientVertical );


		image.drawImageFunctor<Graphic::ColorFunc::Gradient::Radial<Graphic::ColorRGBA<unsigned char>, Math::InterpolationFunc::Cubic>>( Graphic::Point( 10, 10 ), testFunctorGradientRadial, Graphic::Rectangle( imageTxt.getSize() ), imageTxt );

		image.drawStrokeFunctor<Graphic::ColorFunc::Gradient::Vertical<Graphic::ColorRGBA<unsigned char>, Math::InterpolationFunc::Cubic>>( Graphic::Point( 10, 10 ), imageTxt, 1, testFunctorGradientVertical, Graphic::Image::StrokeType::Middle );

		Graphic::FreeImage freeImage;
		freeImage.loadFromDatas( ( unsigned char * ) imageTxt.getDatas(), imageTxt.getSize(), Graphic::FreeImage::Format::R );
		freeImage.saveToFile( "testHelloWorld.png", Graphic::FreeImage::SavingFormat::PNG );
	}*/



	{
		//////////////////////////////////////////////////////////////////////////
		// Draw Bufferized Font !!!!!!!!!!!!									//



		//image.fillImage( Graphic::ColorRGB<unsigned char>( 255 ) );
		UTF8String testStr( "Hello World\nThis Lib is Awesome !" );

		typedef Graphic::FontEffect<unsigned char, Graphic::ColorFunc::SimpleColor<Graphic::ColorRGBA<unsigned char>>, Graphic::ColorFunc::SimpleColor<Graphic::ColorRGBA<unsigned char>>> FontType;
		FontType myFont( L"consola.ttf", 30 );

		myFont.setOverlayColorFunc( Graphic::ColorFunc::SimpleColor<Graphic::ColorRGBA<unsigned char>>( Graphic::ColorRGBA<unsigned char>( 255, 255, 255, 255 ) ) );
		myFont.setShadowActivated( false );
		myFont.setShadowColorFunc( Graphic::ColorFunc::SimpleColor<Graphic::ColorRGBA<unsigned char>>( Graphic::ColorRGBA<unsigned char>( 0, 0, 0, 250 ) ) );
		myFont.setShadowRadius( 2 );
		myFont.setShadowBias( Math::Vec2<float>( 1, -1 ) );


		myFont.setStrokeActivated( true );
		myFont.setStrokeSize( 1.9 );
		myFont.setStrokeColorFunc( Graphic::ColorFunc::SimpleColor<Graphic::ColorRGBA<unsigned char>>( Graphic::ColorRGBA<unsigned char>( 0, 0, 0, 150 ) ) );

		FontType myFontCOPY = myFont;
		myFontCOPY.loadGlyph( Graphic::FontEffect<unsigned char>::Template::Ascii );

		assert( IO::write( WString( "myFontCustomdeOUF.font" ), &myFontCOPY ) );


		FontType myFontCp;
		

		assert( IO::read( WString( "myFontCustomdeOUF.font" ), &myFontCp ) );



		auto maskTest = myFontCp['A'];
		//image.drawImage(Graphic::Point(300, 300), *maskTest);

		Graphic::Text<unsigned char> myText;
		myText.setText( myFontCp, testStr, Math::Vec2<bool>(true, true) );

		//Graphic::drawText( &image, myFontCp, Graphic::Point(250,250), testStr,  Math::Vec2<bool>( true, true ) );

		assert( IO::write( WString( "myText.cimg" ), &myText ) );
		Graphic::Text<unsigned char> myTextCp;
		assert( IO::read( WString( "myText.cimg" ), &myTextCp ) );

		auto mipmap = myTextCp.resample(Math::Vec2<Graphic::Size>( myTextCp.getSize() / 2 ), Graphic::Image::ResamplingMode::Lanczos);
		image.drawImage( Graphic::Point( myTextCp.getBias() / 2.0f ) + Graphic::Point(250,250), mipmap );

	}


	{
		//////////////////////////////////////////////////////////////////////////
		// Draw Text Rectangle									//
		//Graphic::drawText(imageTest2[0], fontTest, Graphic::Rectangle(0,0, 250, 250), testStr, gradientVertical, Math::Vec2<bool>(true, true));
	}

	{
		//////////////////////////////////////////////////////////////////////////
		// Draw Gradient										//
		//imageTest2[0] -> drawRectangle(Graphic::Rectangle(0, -250, 500, 250), gradientVertical);					//Vertical
		//imageTest2[0] -> drawRectangle(Graphic::Rectangle(0, 0, 500, 500), gradientHorizontal);						//Horizontal
		//imageTest2[0] -> drawRectangle(Graphic::Rectangle(250, 0, 750, 500), gradientHorizontal);					//Horizontal
		//imageTest2[0] -> drawRectangle(Graphic::Rectangle(-250, 0, 250, 500), gradientHorizontal);					//Horizontal

		//imageTest2[0] -> fillImage(gradientVertical, Graphic::Rectangle(0, 0, 500, 500));						//Vertical
		//imageTest2[0] -> drawRectangle(Graphic::Rectangle(-250, 0, 250, 500), gradientLinear);					//Linear
		//imageTest2[0] -> drawRectangle(Graphic::Rectangle(-250, 0, 250, 500), gradientRadial);					//Radial
	}




	{
		//////////////////////////////////////////////////////////////////////////
		// Draw Line as Functor									//
		//Graphic::ColorFunc::Gradient::Horizontal<Graphic::ColorRGBA<unsigned char>, Graphic::InterpolationFunc::Cubic> testFunctorGradient42(gradientHorizontal);
		//image.drawLineFunctor(Graphic::LineF(0, 0, 500, 500), testFunctorGradient42, 5);
	}

	{
		//////////////////////////////////////////////////////////////////////////
		// Draw Bezier Curve									//
		//image.drawBezierCurve(Graphic::PointF(0, 0), Graphic::PointF(100, 400), Graphic::PointF(400, 100), Graphic::PointF(500, 500), 3, Graphic::ColorRGBA<unsigned char>(0,0,0,128));
	}





	/*{
		//////////////////////////////////////////////////////////////////////////
		// Draw Rounded Rectangle								//

		image.drawRectangleRounded( Graphic::Rectangle( 0, 0, 500, 500 ), 100, Graphic::ColorRGBA<unsigned char>( 0, 0, 128, 128 ) );

		image.drawRectangleRounded( Graphic::Rectangle( 50, 50, 450, 450 ), 45, Graphic::ColorRGBA<unsigned char>( 255, 0, 128, 128 ) );


		//image.drawRectangleRounded<Graphic::BlendingFunc::Erase>( Graphic::Rectangle( 50, 50, 450, 450 ), 60, Graphic::ColorR<unsigned char>( 255 ), Graphic::BlendingFunc::Erase( ) );


	}*/

/*
	{
		//////////////////////////////////////////////////////////////////////////
		// Draw Polygon															//
		{
			Math::Vec2<float> vertices[] = { Math::Vec2<float>( 0.0f, 0.2f ), Math::Vec2<float>( 0.2f, 0.5f ), Math::Vec2<float>( 0.0f, 0.8f ), Math::Vec2<float>( 1.0f, 0.5f ) };
			Graphic::ColorFunc::SimpleColor<Graphic::ColorRGBA<unsigned char>> colorFunc( Graphic::ColorRGBA<unsigned char>( 0, 0, 0, 128 ) );

			image.drawPolygonFunctor<Graphic::ColorFunc::SimpleColor<Graphic::ColorRGBA<unsigned char>>>( vertices, 4, Graphic::Rectangle( 150, 150, 250, 250 ), colorFunc );

		}
		{

			Math::Vec2<float> vertices[] = { Math::Vec2<float>( 0.0f, 0.5f ), Math::Vec2<float>( 1.0f, 0.2f ), Math::Vec2<float>( 0.8f, 0.5f ), Math::Vec2<float>( 1.0f, 0.8f ) };
			Graphic::ColorFunc::SimpleColor<Graphic::ColorRGBA<unsigned char>> colorFunc( Graphic::ColorRGBA<unsigned char>( 0, 0, 0, 128 ) );

			image.drawPolygonFunctor<Graphic::ColorFunc::SimpleColor<Graphic::ColorRGBA<unsigned char>>>( vertices, 4, Graphic::Rectangle( 150, 250, 250, 350 ), colorFunc );

		}
		{

			Math::Vec2<float> vertices[] = { Math::Vec2<float>( 0.5f, 0.0f ), Math::Vec2<float>( 0.2f, 1.0f ), Math::Vec2<float>( 0.5f, 0.8f ), Math::Vec2<float>( 0.8f, 1.0f ) };
			Graphic::ColorFunc::SimpleColor<Graphic::ColorRGBA<unsigned char>> colorFunc( Graphic::ColorRGBA<unsigned char>( 0, 0, 0, 128 ) );

			image.drawPolygonFunctor<Graphic::ColorFunc::SimpleColor<Graphic::ColorRGBA<unsigned char>>>( vertices, 4, Graphic::Rectangle( 250, 150, 350, 250 ), colorFunc );

		}

		{
			Math::Vec2<float> vertices[] = { Math::Vec2<float>( 0.2f, 0.0f ), Math::Vec2<float>( 0.5f, 0.2f ), Math::Vec2<float>( 0.8f, 0.0f ), Math::Vec2<float>( 0.5f, 1.0f ) };
			Graphic::ColorFunc::SimpleColor<Graphic::ColorRGBA<unsigned char>> colorFunc( Graphic::ColorRGBA<unsigned char>( 0, 0, 0, 128 ) );

			image.drawPolygonFunctor<Graphic::ColorFunc::SimpleColor<Graphic::ColorRGBA<unsigned char>>>( vertices, 4, Graphic::Rectangle( 250, 250, 350, 350 ), colorFunc );

		}
	}*/
	/*{
		//////////////////////////////////////////////////////////////////////////
		// Draw Disk															//
		Graphic::ColorFunc::SimpleColor<Graphic::ColorRGBA<unsigned char>> colorFunc( Graphic::ColorRGBA<unsigned char>( 0, 0, 0, 128 ) );
		image.drawDiskFunctor<Graphic::ColorFunc::SimpleColor<Graphic::ColorRGBA<unsigned char>>>( Graphic::Point( 250, 250 ), 250, colorFunc );
	}*/








	/*{
		//////////////////////////////////////////////////////////////////////////
		// re sampling															//

		Graphic::FreeImage freeImageOriginal( "sanctum.png", Graphic::FreeImage::Format::RGB );
		freeImageOriginal.load();
		freeImageOriginal.resize( Graphic::Point( 100, 500 ), Graphic::FreeImage::Filter::Lanczos3 );
		Graphic::ImageT<unsigned char> imageLanczos( freeImageOriginal.getDatas(), freeImageOriginal.getSize(), Graphic::LoadingFormat::BGR, false, freeImageOriginal.getStride() );

		Graphic::FreeImage freeImageLinearIn( "sanctum200linear.png", Graphic::FreeImage::Format::RGB );
		freeImageLinearIn.load();
		Graphic::ImageT<unsigned char> imageExampleLinear( freeImageLinearIn.getDatas(), freeImageLinearIn.getSize(), Graphic::LoadingFormat::BGR, false );

		Graphic::FreeImage freeImageBicubicIn( "sanctum200bicubic.png", Graphic::FreeImage::Format::RGB );
		freeImageBicubicIn.load();
		Graphic::ImageT<unsigned char> imageExampleBicubic( freeImageBicubicIn.getDatas(), freeImageBicubicIn.getSize(), Graphic::LoadingFormat::BGR, false );

		//image.drawImage( Graphic::Point( 0, 0 ), imageSmall.resample( Math::Vec2<Graphic::Size>( 500, 500 ), Graphic::Image::ResamplingMode::Linear ) );
		image.drawImage( Graphic::Point( 0, 0 ), texture2[0] -> resample( Math::Vec2<Graphic::Size>( 100, 500 ), Graphic::Image::ResamplingMode::Lanczos ) );
		image.drawImage( Graphic::Point( 200, 0 ), texture2[0] -> resample( Math::Vec2<Graphic::Size>( 100, 100 ), Graphic::Image::ResamplingMode::Lanczos ) );
		image.drawImage( Graphic::Point( 300, 0 ), texture2[0] -> resample( Math::Vec2<Graphic::Size>( 50, 50 ), Graphic::Image::ResamplingMode::Lanczos ) );
		image.drawImage( Graphic::Point( 350, 0 ), texture2[0] -> resample( Math::Vec2<Graphic::Size>( 25, 25 ), Graphic::Image::ResamplingMode::Lanczos ) );

		//image.drawImage( Graphic::Point( 200, 0 ), imageExampleLinear );
		//image.drawImage( Graphic::Point( 0, 200 ), imageExampleBicubic );
		image.drawImage( Graphic::Point( 100, 0 ), imageLanczos );


	}*/




					/*{
						//////////////////////////////////////////////////////////////////////////
						// Draw Graph Points									//
						Math::Vec2<float> vStatic[] = { Math::Vec2<float>(-2.0f, 0.0f), Math::Vec2<float>(0.25f, 0.2f), Math::Vec2<float>(0.5f, 0.1f), Math::Vec2<float>(0.6f, 0.8f), Math::Vec2<float>(0.7f, 0.1f), Math::Vec2<float>(1.0f, 0.8f) };
						Vector<Math::Vec2<float>> v(vStatic);
						image.drawGraphValuesFunctor(v, Graphic::Rectangle(0, 0, 500, 500), Graphic::ColorFunc::SimpleColor<Graphic::ColorRGBA<unsigned char>>(Graphic::ColorRGBA<unsigned char>(255, 0, 0, 128)));
					}*/


	*( texture2[0] ) = image;

	{
		//////////////////////////////////////////////////////////////////////////
		// Generate Mipmaps									//
		texture2.generateMipmaps();
	}


	{
		//////////////////////////////////////////////////////////////////////////
		// Draw Mipmaps										//
		for ( size_t i = 1; i < texture2.getNumMipmaps(); i++ ) {
			//imageTest2[0] -> drawImage(Graphic::Point(0, 0), *imageTest2[i]);
		}
	}


	//////////////////////////////////////////////////////////////////////////
	// Saving to file										//
	Graphic::FreeImage freeImage2;
	freeImage2.loadFromDatas( ( unsigned char * ) texture2.getDatas( 0 ), texture2.getSize( 0 ), Graphic::FreeImage::Format::RGB );
	freeImage2.saveToFile( "sanctum3.png", Graphic::FreeImage::SavingFormat::PNG );
	#endif


	#else		//DEBUG
constexpr unsigned long long G10( 10000000000 );
constexpr unsigned long long G1( 1000000000 );
constexpr unsigned long long M100( 100000000 );
constexpr unsigned long long M10( 10000000 );
constexpr unsigned long long M1( 1000000 );
constexpr unsigned long long K100( 100000 );
constexpr unsigned long long K10( 10000 );
constexpr unsigned long long K1( 1000 );

	#ifdef SPEEDTEST_DRAWLINE
	{
		//////////////////////////////////////////////////////////////////////////
		// SPEED TEST : Draw Lines								//

		Graphic::ImageT<unsigned char> image( Math::Vec2<Graphic::Size>( 500 ), Graphic::Format::R );

		Graphic::Gradient::Horizontal<Graphic::ColorRGBA<unsigned char>, Graphic::InterpolationFunc::Cubic> gradientHorizontal;
		gradientHorizontal.addPoint( 0.0f, Graphic::ColorRGBA<unsigned char>( 0, 0, 0, 255 ) );
		gradientHorizontal.addPoint( 1.0f, Graphic::ColorRGBA<unsigned char>( 255, 255, 255, 255 ) );
		Graphic::ColorFunc::Gradient::Horizontal<Graphic::ColorRGBA<unsigned char>, Graphic::InterpolationFunc::Cubic> colorFunctor( gradientHorizontal );



		Log::startChrono();
		for ( size_t i = 0; i < M1; i++ ) {
			//image.drawLine(Graphic::LineF(0, 20, 500, 480), Graphic::ColorR<unsigned char>(255), 5);
			image.drawLineFunctor( Graphic::LineF( 0, 20, 500, 480 ), Graphic::ColorFunc::SimpleColor<Graphic::ColorR<unsigned char>>( Graphic::ColorR<unsigned char>( 255 ) ), 1 );

			//image.drawLineFunctor(Graphic::LineF(0, 20, 500, 480), colorFunctor, 5);
		}
		Log::stopChrono();
		Log::displayChrono( "DRAW LINES R -> R (Last Result: 1.581s for M1)" );

		Graphic::FreeImage freeImage;
		freeImage.loadFromDatas( ( unsigned char * ) image.getDatas(), image.getSize(), Graphic::FreeImage::Format::R );
		freeImage.saveToFile( "drawline.png", Graphic::FreeImage::SavingFormat::PNG );
	}
	#endif

	#ifdef SPEEDTEST_DRAWLINE_FLOAT
	{
		//////////////////////////////////////////////////////////////////////////
		// SPEED TEST : Draw Lines								//

		Graphic::ImageT<float> image( Math::Vec2<Graphic::Size>( 500 ), Graphic::Format::R );

		Log::startChrono();
		for ( size_t i = 0; i < M1; i++ ) {
			image.drawLineFunctor( Graphic::LineF( 0, 20, 500, 480 ), Graphic::ColorFunc::SimpleColor<Graphic::ColorR<float>>( Graphic::ColorR<float>( 1 ) ), 1 );
		}
		Log::stopChrono();
		Log::displayChrono( "DRAW LINES R -> R (Last Result: 1.6s for M1)" );


		Graphic::ImageT<unsigned char> imageUC( image );
		Graphic::FreeImage freeImage;
		freeImage.loadFromDatas( ( unsigned char * ) imageUC.getDatas(), imageUC.getSize(), Graphic::FreeImage::Format::R );
		freeImage.saveToFile( "drawline_float.png", Graphic::FreeImage::SavingFormat::PNG );
	}

	#endif

	#ifdef SPEEDTEST_GRAPH
	{
		//////////////////////////////////////////////////////////////////////////
		// SPEED TEST : Graph									//

		Graphic::ImageT<unsigned char> image( Math::Vec2<Graphic::Size>( 500 ), Graphic::Format::R );


		Math::Vec2<float> vStatic[] = { Math::Vec2<float>( 0.0f, 0.2f ), Math::Vec2<float>( 0.25f, 0.2f ), Math::Vec2<float>( 0.5f, 0.1f ), Math::Vec2<float>( 0.6f, 0.8f ), Math::Vec2<float>( 0.7f, 0.1f ), Math::Vec2<float>( 1.0f, 0.8f ) };
		Vector<Math::Vec2<float>> v( vStatic );

		Log::startChrono();
		for ( size_t i = 0; i < K10; i++ ) {
			image.drawGraphValuesFunctor( v, Graphic::Rectangle( 0, 0, 500, 500 ), Graphic::ColorFunc::SimpleColor<Graphic::ColorR<unsigned char>>( Graphic::ColorR<unsigned char>( 128 ) ) );
		}
		Log::stopChrono();
		Log::displayChrono( "DRAW GRAPH R -> R (Last Result: 6.0s for K100)" );

		Graphic::FreeImage freeImage;
		freeImage.loadFromDatas( ( unsigned char * ) image.getDatas(), image.getSize(), Graphic::FreeImage::Format::R );
		freeImage.saveToFile( "graph.png", Graphic::FreeImage::SavingFormat::PNG );
	}
	#endif


	#ifdef SPEEDTEST_ROUNDEDRECTANGLE
	{
		//////////////////////////////////////////////////////////////////////////
		// SPEED TEST : Rounded Rectangle							//

		Graphic::ImageT<unsigned char> image( Math::Vec2<Graphic::Size>( 500 ), Graphic::Format::R );


		Log::startChrono();
		for ( size_t i = 0; i < K10; i++ ) {
			image.drawRectangleRounded( Graphic::Rectangle( 0, 0, 500, 500 ), 100, Graphic::ColorR<unsigned char>( 255 ) );

		}
		Log::stopChrono();
		Log::displayChrono( "DRAW ROUNDED RECTANGLE R -> R (Last Result: 0.883s for K10)" );

		Graphic::FreeImage freeImage;
		freeImage.loadFromDatas( ( unsigned char * ) image.getDatas(), image.getSize(), Graphic::FreeImage::Format::R );
		freeImage.saveToFile( "rectangleRounded.png", Graphic::FreeImage::SavingFormat::PNG );
	}
	#endif

	#ifdef SPEEDTEST_DISK
	{
		//////////////////////////////////////////////////////////////////////////
		// SPEED TEST : Rounded Rectangle							//

		Graphic::ImageT<unsigned char> image( Math::Vec2<Graphic::Size>( 500 ), Graphic::Format::R );

		Graphic::ColorFunc::SimpleColor<Graphic::ColorR<unsigned char>> colorFunc( Graphic::ColorR<unsigned char>( 255 ) );


		Log::startChrono();
		for ( size_t i = 0; i < K10; i++ ) {
			image.drawRectangleRounded( Graphic::Rectangle( 0, 0, 500, 500 ), 250, Graphic::ColorR<unsigned char>( 255 ) );

		}
		Log::stopChrono();
		Log::displayChrono( "DRAW ROUNDED RECTANGLE R -> R (Last Result: 0.779s for K10)" );

		Log::startChrono();
		for ( size_t i = 0; i < K10; i++ ) {
			image._drawDiskFunctor<Graphic::ColorFunc::SimpleColor<Graphic::ColorR<unsigned char>>, Graphic::BlendingFunc::Normal, Graphic::ColorR<unsigned char>>( Graphic::Point( 250, 250 ), 250, colorFunc );

		}
		Log::stopChrono();
		Log::displayChrono( "DRAW DISK RECTANGLE R -> R (Last Result: 0.778s for K10)" );

		Graphic::FreeImage freeImage;
		freeImage.loadFromDatas( ( unsigned char * ) image.getDatas(), image.getSize(), Graphic::FreeImage::Format::R );
		freeImage.saveToFile( "rectangleRounded.png", Graphic::FreeImage::SavingFormat::PNG );
	}
	#endif

	#ifdef SPEEDTEST_DRAWTEXT
	{
		//////////////////////////////////////////////////////////////////////////
		// SPEED TEST : Draw Text											//
		Graphic::FontLoadable<unsigned char> font( L"consola.ttf", 15 );
		font.load();
		font.loadGlyph( Graphic::Font<unsigned char>::Template::Ascii );

		Graphic::ImageT<unsigned char> image( Math::Vec2<Graphic::Size>( 500 ), Graphic::Format::RGB );

		UTF8String testStr( "Hello World" );

		Log::startChrono();
		for ( size_t i = 0; i < M1; i++ ) {
			Graphic::drawText( &image, font, Graphic::Rectangle( 0, 0, 250, 250 ), testStr, Graphic::ColorRGB<unsigned char>( 255, 100, 200 ), Math::Vec2<bool>( true, true ) );
		}
		Log::stopChrono();
		Log::displayChrono( "DRAW \"Hello World\" (Last Result: 1.629s for M1)" );


		Graphic::FreeImage freeImage;
		freeImage.loadFromDatas( ( unsigned char * ) image.getDatas(), image.getSize(), Graphic::FreeImage::Format::RGB );
		freeImage.saveToFile( "drawText.png", Graphic::FreeImage::SavingFormat::PNG );
	}
	#endif


	#ifdef SPEEDTEST_RESAMPLE
	{
		//////////////////////////////////////////////////////////////////////////
		// SPEED TEST : Re sample												//

		Graphic::FreeImage freeImageIn( "sanctum.png", Graphic::FreeImage::Format::RGB );
		Graphic::FreeImage freeImageOriginal( "sanctum.png", Graphic::FreeImage::Format::RGB );
		freeImageIn.load();
		freeImageOriginal.load();
		Graphic::ImageT<unsigned char> imageOriginal( freeImageIn.getDatas(), freeImageIn.getSize(), Graphic::LoadingFormat::BGR, false );
		Graphic::ImageT<unsigned char> image( imageOriginal );
		Graphic::ImageT<unsigned char> image2( imageOriginal.getSize(), Graphic::Format::RGB );

		Log::startChrono();
		for ( size_t i = 0; i < K10; i++ ) {
			image2 = image.resample( Math::Vec2<Graphic::Size>( 100, 400 ), Graphic::Image::ResamplingMode::Nearest );
			image = image2.resample( Math::Vec2<Graphic::Size>( 500, 100 ), Graphic::Image::ResamplingMode::Nearest );

			image2 = image;
			image = image2;

		}
		Log::stopChrono();
		Log::displayChrono( "RESAMPLE NEAREST RGB (Last Result: 8.1s for K10)" );

		Log::startChrono();
		for ( size_t i = 0; i < K1; i++ ) {
			image2 = image.resample( Math::Vec2<Graphic::Size>( 100, 400 ), Graphic::Image::ResamplingMode::Bilinear );
			image = image2.resample( Math::Vec2<Graphic::Size>( 500, 100 ), Graphic::Image::ResamplingMode::Bilinear );
		}

		Log::stopChrono();
		Log::displayChrono( "RESAMPLE LINEAR RGB (Last Result: 780ms for K1)" );

		Log::startChrono();
		for ( size_t i = 0; i < K1; i++ ) {
			image = imageOriginal;
			image = image.resample( Math::Vec2<Graphic::Size>( 200, 200 ), Graphic::Image::ResamplingMode::Lanczos );
			//image = image2.resample( Math::Vec2<Graphic::Size>( 500, 500 ), Graphic::Image::ResamplingMode::Linear );
		}

		Log::stopChrono();
		Log::displayChrono( "RESAMPLE LANCZOS RGB (Last Result: 3450ms for K1)" );

		Log::startChrono();
		for ( size_t i = 0; i < K1; i++ ) {
			freeImageIn.resize( Math::Vec2<Graphic::Size>( 100, 400 ), Graphic::FreeImage::Filter::Bilinear );
			freeImageIn.resize( Math::Vec2<Graphic::Size>( 500, 100 ), Graphic::FreeImage::Filter::Bilinear );

		}
		Log::stopChrono();
		Log::displayChrono( "RESAMPLE FreeImage LINEAR RGB (Last Result: 1900ms for K1)" );


		Graphic::FreeImage freeImageOut;
		freeImageOut.loadFromDatas( ( unsigned char * ) image.getDatas(), image.getSize(), Graphic::FreeImage::Format::RGB );
		freeImageOut.saveToFile( "resample.png", Graphic::FreeImage::SavingFormat::PNG );

	}
	#endif


	#ifdef SPEEDTEST_POLYGON
	{
		//////////////////////////////////////////////////////////////////////////
		// SPEED TEST : Polygon									//

		Graphic::ImageT<unsigned char> image( Math::Vec2<Graphic::Size>( 500 ), Graphic::Format::R );

		Math::Vec2<float> vertices[] = { Math::Vec2<float>( 0.0f, 0.2f ), Math::Vec2<float>( 0.2f, 0.5f ), Math::Vec2<float>( 0.0f, 0.8f ), Math::Vec2<float>( 1.0f, 0.5f ) };
		Graphic::ColorFunc::SimpleColor<Graphic::ColorR<unsigned char>> colorFunc( Graphic::ColorR<unsigned char>( 128 ) );

		Log::startChrono();
		for ( size_t i = 0; i < K100; i++ ) {
			image.drawPolygonFunctor<Graphic::ColorFunc::SimpleColor<Graphic::ColorR<unsigned char>>>( vertices, 4, Graphic::Rectangle( 100, 100, 400, 400 ), colorFunc );

		}
		Log::stopChrono();
		Log::displayChrono( "DRAW POLYGON R -> R (Last Result: 1.4s for K100)" );

		Graphic::FreeImage freeImage;
		freeImage.loadFromDatas( ( unsigned char * ) image.getDatas(), image.getSize(), Graphic::FreeImage::Format::R );
		freeImage.saveToFile( "polygon.png", Graphic::FreeImage::SavingFormat::PNG );
	}
	#endif

	#ifdef SPEEDTEST_FILTER
	{
		//////////////////////////////////////////////////////////////////////////
		// Filter											//
		Graphic::FreeImage freeImageIn( "sanctum.png", Graphic::FreeImage::Format::RGB );
		freeImageIn.load();
		Graphic::ImageT<unsigned char> image( freeImageIn.getDatas(), Math::Vec2<Graphic::Size>( 500 ), Graphic::LoadingFormat::BGR, false );
		Graphic::ImageT<float> imagef( image );




		Log::startChrono();
		for ( size_t i = 0; i < K1; i++ ) {
			image = image.applyGaussianBlur( 5, Graphic::Image::ConvolutionMode::NormalSize, Graphic::ColorRGBA<unsigned char>( 0, 0, 0, 0 ) );
		}
		Log::stopChrono();
		Log::displayChrono( "FILTER RGB UCHAR (Last Result: 9.5s for K1)" );


		Log::startChrono();
		for ( size_t i = 0; i < K1; i++ ) {
			imagef = imagef.applyGaussianBlur( 5, Graphic::ImageT<float>::ConvolutionMode::NormalSize, Graphic::ColorRGBA<float>( 0, 0, 0, 0 ) );
		}
		Log::stopChrono();
		Log::displayChrono( "FILTER RGB FLOAT (Last Result: 15.1s for K1)" );


		Graphic::FreeImage freeImageOut;
		freeImageOut.loadFromDatas( ( unsigned char * ) image.getDatas(), image.getSize(), Graphic::FreeImage::Format::RGB );
		freeImageOut.saveToFile( "filterUCHAR.png", Graphic::FreeImage::SavingFormat::PNG );


		image = imagef;
		freeImageOut.loadFromDatas( ( unsigned char * ) image.getDatas(), image.getSize(), Graphic::FreeImage::Format::RGB );
		freeImageOut.saveToFile( "filterFLOAT.png", Graphic::FreeImage::SavingFormat::PNG );
	}
	#endif


	#ifdef SPEEDTEST_STROKE
	{
		//////////////////////////////////////////////////////////////////////////
		// Stroke											//
		Graphic::FreeImage freeImageIn( "sanctum.png", Graphic::FreeImage::Format::RGB );
		freeImageIn.load();
		Graphic::ImageT<unsigned char> image( freeImageIn.getDatas(), freeImageIn.getSize(), Graphic::LoadingFormat::RGB, false );
		image.threshold( Graphic::ColorRGBA<unsigned char>( 255 ), Graphic::ColorRGBA<unsigned char>( 0 ), Graphic::ColorRGBA<unsigned char>( 128, 0, 0, 0 ) );

		Log::startChrono();
		for ( size_t i = 0; i < K1; i++ ) {
			image.drawStrokeFunctor( Graphic::Point( 0, 0 ), image, 2, Graphic::ColorFunc::SimpleColor<Graphic::ColorRGB<unsigned char>>( Graphic::ColorRGB<unsigned char>( 0, 255, 0 ) ), Graphic::Image::StrokeType::Outside );
		}
		Log::stopChrono();
		Log::displayChrono( "STROKE THICKNESS 2 RGB UCHAR (Last Result: 11000ms for K1)" );

		Graphic::FreeImage freeImageOut;
		freeImageOut.loadFromDatas( ( unsigned char * ) image.getDatas(), image.getSize(), Graphic::FreeImage::Format::RGB );
		freeImageOut.saveToFile( "stroke.png", Graphic::FreeImage::SavingFormat::PNG );
	}
	#endif


	#ifdef SPEEDTEST_LOGICAL
	//////////////////////////////////////////////////////////////////////////
	// SPEED TEST : Logicals								//
	{
		size_t sum = 0;
		Log::startChrono();
		for ( size_t i = 0; i < G10; i++ ) {
			sum += ( i < i + 2 ) ? 1 : 0;
		}
		Log::stopChrono();
		Log::displayChrono( String( "LOGICAL < (Last : 5914ms) " ) + sum );

		sum = 0;
		Log::startChrono();
		for ( size_t i = 0; i < G10; i++ ) {
			sum += ( i <= i + 2 ) ? 1 : 0;
		}
		Log::stopChrono();
		Log::displayChrono( String( "LOGICAL <= (Last : 8281ms) " ) + sum );
	}
	#endif

	#ifdef SPEEDTEST_ARRAYACCESS
	//////////////////////////////////////////////////////////////////////////
	// SPEED TEST : INT VS UINT Array access times.					//
	{
		int * testArray = new int[10000000];
		int sum = 0;
		int iteratorInt;
		int iteratorAdd = Math::random( 0, 100 );
		size_t j;
		Log::startChrono();
		for ( j = 0; j < M10; j++ ) {
			for ( iteratorInt = 0; iteratorInt < 1000; iteratorInt++ ) {
				sum += *( testArray + iteratorInt * iteratorAdd );
			}
		}
		Log::stopChrono();
		Log::displayChrono( "INT ARRAY ACCESS" + sum );

		sum = 0;
		unsigned int iteratorUInt;
		Log::startChrono();
		for ( j = 0; j < M10; j++ ) {
			for ( iteratorUInt = 0; iteratorUInt < 1000; iteratorUInt++ ) {
				sum += *( testArray + iteratorUInt * iteratorAdd );
			}
		}
		Log::stopChrono();
		Log::displayChrono( "UINT ARRAY ACCESS" + sum );

		sum = 0;
		size_t iteratorSizeT;
		Log::startChrono();
		for ( j = 0; j < M10; j++ ) {
			for ( iteratorSizeT = 0; iteratorSizeT < 1000; iteratorSizeT++ ) {
				sum += *( testArray + iteratorSizeT * iteratorAdd );
			}
		}
		Log::stopChrono();
		Log::displayChrono( "SIZE_T ARRAY ACCESS" + sum );

		//RESULT : UINT is the faster nearly followed by SIZET, INT is a bit slower.
		delete[] testArray;
	}
	#endif

	#ifdef SPEEDTEST_BLENDING
	//////////////////////////////////////////////////////////////////////////
	// Speed Test : Testing RGBA Blending times float VS unsigned char	//
	{
		Graphic::ColorRGBA<unsigned char> colorWhite( 255, 255, 255, 10 );
		Graphic::ColorRGBA<unsigned char> colorRed( 255, 0, 0, 10 );

		Graphic::Image testBlendRGBA1( Math::Vec2<Graphic::Size>( 200, 200 ), Graphic::Format::RGBA );
		Graphic::Image testBlendRGBA2( Math::Vec2<Graphic::Size>( 200, 200 ), Graphic::Format::RGBA );

		testBlendRGBA1.fillImage( colorRed );
		testBlendRGBA2.fillImage( colorWhite );

		Graphic::ImageT<float> testBlendRGBAFloat1( Math::Vec2<Graphic::Size>( 100, 100 ), Graphic::Format::RGBA );
		Graphic::ImageT<float> testBlendRGBAFloat2( Math::Vec2<Graphic::Size>( 100, 100 ), Graphic::Format::RGBA );

		Graphic::ColorRGBA<float> colorWhiteF( 1.0f, 1.0f, 1.0f, float( 127 ) / float( 255 ) );
		Graphic::ColorRGBA<float> colorRedF( 1.0f, 0.0f, 0.0f, float(127) / float(255) );

		testBlendRGBAFloat1.fillImage( colorRedF );
		testBlendRGBAFloat2.fillImage( colorWhiteF );

		Graphic::Rectangle rectangle( testBlendRGBA2.getSize() );

		Log::startChrono();
		for ( size_t i = 0; i < K10; i++ ) {
			testBlendRGBA2.drawImage( Graphic::Point( 0, 0 ), testBlendRGBA1 );
		}
		Log::stopChrono();
		Log::displayChrono( "INT BLENDING RGBA -> RGB (last 1215ms)" );


		Log::startChrono();
		for ( size_t i = 0; i < K10; i++ ) {
			testBlendRGBAFloat2.drawImage( Graphic::Point( 0, 0 ), testBlendRGBAFloat1 );
		}
		Log::stopChrono();
		Log::displayChrono( "FLOAT BLENDING RGBA -> RGB (last 205ms)" );

		Log::startChrono();
		for ( size_t i = 0; i < K10; i++ ) {
			testBlendRGBA2.drawImage( Graphic::Point( 0, 0 ), rectangle, testBlendRGBA1, Graphic::BlendingFunc::Normal() );
		}
		Log::stopChrono();
		Log::displayChrono( "INT BLENDING FUNCTOR RGBA -> RGB (last 1200ms)" );


		Log::startChrono();
		for ( size_t i = 0; i < K10; i++ ) {
			testBlendRGBAFloat2.drawImage( Graphic::Point( 0, 0 ), rectangle, testBlendRGBAFloat1, Graphic::BlendingFunc::Normal() );
		}
		Log::stopChrono();
		Log::displayChrono( "FLOAT BLENDING FUNCTOR RGBA -> RGB (last 206ms)" );

		Graphic::Image testblendCasted( testBlendRGBAFloat2 );

		Graphic::FreeImage freeImage;
		freeImage.loadFromDatas( ( unsigned char * ) testblendCasted.getDatas(), testblendCasted.getSize(), Graphic::FreeImage::Format::RGBA );
		freeImage.saveToFile( "blending.png", Graphic::FreeImage::SavingFormat::PNG );
	}
	#endif

	#ifdef SPEEDTEST_DATE
	//////////////////////////////////////////////////////////////////////////
	// SPEED TEST : Dates									//
	{
		struct tm timeinfo;
		Time::Date date;
		Log::startChrono();
		for ( unsigned long i = 0; i < M10; i++ ) {
			date = Time::Date( Time::getTime() );
		}
		Log::stopChrono();
		Log::displayChrono( String() << "Date" );

		Log::startChrono();
		for ( unsigned long i = 0; i < M10; i++ ) {
			time_t now = time( NULL );
			localtime_s( &timeinfo, &now );
		}
		Log::stopChrono();
		Log::displayChrono( String() << "localtime_s" );
	}
	#endif

	#ifdef SPEEDTEST_STRING_CONCAT
	//////////////////////////////////////////////////////////////////////////
	// SPEED TEST : Concat Strings							//
	{
		String testStr( "STRING STREAM : " );
		std::string testStr2( "STRING : " );

		String strConcat( "Hello World!" );
		std::string strConcat2( "Hello World!" );


		Log::startChrono();
		for ( size_t i = 0; i < M10; i++ ) {
			testStr += String( "Hello World!" );
		}
		Log::stopChrono();
		Log::displayChrono( testStr.getSubStr( 0, 30 ) );

		Log::startChrono();
		for ( size_t i = 0; i < M10; i++ ) {
			testStr2 += std::string( "Hello World!" );
		}
		Log::stopChrono();
		Log::displayChrono( testStr2.substr( 0, 30 ) );
	}
	#endif

	#ifdef SPEEDTEST_STRING_CAST
	//////////////////////////////////////////////////////////////////////////
	// SPEED TEST : Cast Strings								//
	{
		float sum = 0;
		Log::startChrono();
		for ( unsigned long i = 0; i < 10000000; i++ ) {
			sum += atof( "42.054217" );
		}
		Log::stopChrono();
		Log::displayChrono( "ATOF : " + String( sum ) );

		Log::startChrono();
		for ( unsigned long i = 0; i < 10000000; i++ ) {
			sum += String::toFloat( "42.054217" );
		}
		Log::stopChrono();
		Log::displayChrono( "toFloat : " + String( sum ) );
	}
	#endif

	#ifdef SPEEDTEST_REGEX
	//////////////////////////////////////////////////////////////////////////
	// SPEED TEST : Regex									//
	{
		for ( unsigned int i = 0; i < 260; i++ ) {
			log( String( i ) + " : " + Regex::match( i, "^2([0-4][0-9]|5[0-5])|1[0-9][0-9]?|[0-9]$" ) );
		}
		for ( unsigned int i = 0; i < 260; i++ ) {
			log( String( i ) + " : " + Regex::match( i, "^2([0-4][0-9]?|5[0-5]?|[6-9])?|([3-9]|1)[0-9]?[0-9]?|0$" ) );
		}

		std::string stdString = "________255";

		bool stdResult = true;

		std::string txt_regex( "2([0-4][0-9]|5[0-5])|1[0-9][0-9]?|[0-9]$" );
		std::regex stdRegex( txt_regex, std::regex_constants::optimize );
		Log::startChrono();
		for ( unsigned long i = 0; i < M1; i++ ) {
			stdResult &= std::regex_search( stdString, stdRegex );
		}
		Log::stopChrono();
		Log::displayChrono( "Regex .regex_match(); STD : " + String( stdResult ) );


		bool mineResult = true;
		String mineRegex = "2([0-4][0-9]|5[0-5])|1[0-9][0-9]?|[0-9]$";
		String mineString = "________255";

		Log::startChrono();
		for ( unsigned long i = 0; i < M1; i++ ) {
			mineResult &= Regex::match( mineString, mineRegex );
		}
		Log::stopChrono();
		Log::displayChrono( "Vector .regex_match(); Mine : " + String( mineResult ) );
	}
	#endif

	#ifdef SPEEDTEST_VECTOR
	//////////////////////////////////////////////////////////////////////////
	// SPEED TEST : Vectors									//
	{
		Vector<unsigned long> vectorMine;
		std::vector<unsigned long> vectorSTD;

		Log::startChrono();
		for ( unsigned long i = 0; i < 10000000; i++ ) {
			vectorMine.push( i );
		}
		Log::stopChrono();
		Log::displayChrono( "Vector .push_back(); Mine" );

		Log::startChrono();
		for ( unsigned long i = 0; i < 10000000; i++ ) {
			vectorSTD.push_back( i );
		}
		Log::stopChrono();
		Log::displayChrono( "Vector .push_back(); STD" );
	}
	#endif

	#ifdef SPEEDTEST_MAP
	//////////////////////////////////////////////////////////////////////////
	// SPEED TEST : Maps									//
	{
		{
			Map<unsigned long, unsigned long> mapRedBlackTree;
			std::map<unsigned long, unsigned long> mapSTD;

			Log::startChrono();
			for ( unsigned long i = 0; i < M1; i++ ) {
				mapSTD.insert( std::pair<unsigned long, unsigned long>( Math::random( 0, 1000000 ), i ) );
			}
			Log::stopChrono();
			Log::displayChrono( "Map .insert(); STD" );


			Log::startChrono();
			for ( unsigned long i = 0; i < M1; i++ ) {
				mapRedBlackTree.insert( Math::random( 0, 1000000 ), i );
			}
			Log::stopChrono();
			Log::displayChrono( String( "Map Red Black Tree .insert(); Mine " ) );
		}
		{
			Map<unsigned long, unsigned long> mapRedBlackTree;
			std::map<unsigned long, unsigned long> mapSTD;

			for ( unsigned long i = 0; i < M1; i++ ) {
				mapSTD.insert( std::pair<unsigned long, unsigned long>( i, i ) );
				mapRedBlackTree.insert( i, i );
			}
			volatile unsigned long tmp(0);
			Log::startChrono();
			for ( unsigned long i = 0; i < M1; i++ ) {
				tmp += mapSTD[i];
			}
			Log::stopChrono();
			Log::displayChrono( "Map .operator[] STD" );


			Log::startChrono();
			for ( unsigned long i = 0; i < M1; i++ ) {
				tmp += *( mapRedBlackTree[i] );
			}
			Log::stopChrono();
			Log::displayChrono( String( "Map Red Black Tree .operator[] Mine " )  );

		}

		
	}
	#endif
	#ifdef SPEEDTEST_ARITHMETIC 
	//////////////////////////////////////////////////////////////////////////
	// SPEED TEST : Arithmetic												//
	{

		volatile float f0(1);
		Log::startChrono();
		for ( unsigned long i = 0; i < M100; i++ ) {
			f0 += f0;
		}
		Log::stopChrono();
		Log::displayChrono( String("Float ADD ( Last 284ms ) : " ) << f0 );

		volatile float f1( 1 );
		Log::startChrono();
		for ( unsigned long i = 0; i < M100; i++ ) {
			f1 *= f1;
		}
		Log::stopChrono();
		Log::displayChrono( String( "Float MULT ( Last 331ms ) : " ) << f1 );

		volatile int i0( 1 );
		Log::startChrono();
		for ( unsigned long i = 0; i < M100; i++ ) {
			i0 += i0;
		}
		Log::stopChrono();
		Log::displayChrono( String( "Float ADD ( Last 284ms ) : " ) << String(int(i0)) );

		volatile int i1( 1 );
		Log::startChrono();
		for ( unsigned long i = 0; i < M100; i++ ) {
			i1 *= i1;
		}
		Log::stopChrono();
		Log::displayChrono( String( "Float MULT ( Last 331ms ) : " ) << String( int( i1 ) ) );



	}

	#endif 


	#ifdef SPEEDTEST_CAST
	//////////////////////////////////////////////////////////////////////////
	// SPEED TEST : Cast									//
	{


		{
			testExplicitCast<int> i1, i2, i3;
			testExplicitCast<unsigned char> c1, c2, c3;

			Log::startChrono();
			for ( unsigned long i = 0; i < G1; i++ ) {
				i1 += ( c1 );
				i2 += ( c2 );
				i3 += ( c3 );

				c1 += ( i1 );
				c2 += ( i2 );
				c3 += ( i3 );
			}
			Log::stopChrono();
			Log::displayChrono( String( "EXPLICIT CAST (Last Result : ???)" ) << c1.v << c2.v1 << c3.v );
		}

		{
			testImplicitCast<int> i1, i2, i3;
			testImplicitCast<unsigned char> c1, c2, c3;

			Log::startChrono();
			for ( unsigned long i = 0; i < G1; i++ ) {
				i1 += ( c1 );
				i2 += ( c2 );
				i3 += ( c3 );

				c1 += ( i1 );
				c2 += ( i2 );
				c3 += ( i3 );
			}
			Log::stopChrono();
			Log::displayChrono( String( "IMPLICIT CAST (Last Result : ???)" ) << c1.v << c2.v1 << c3.v );
		}

	}
	#endif


	#ifdef SPEEDTEST_NETWORK
	//////////////////////////////////////////////////////////////////////////
	// SPEED TEST : Network									//
	{
		int result;
		std::cout << "0 : Client, 1 : Server, Google Test : 2" << std::endl;
		scanf_s( "%d", &result );

		char testData[50] = "Hello World";
		char testData2[50] = "";

		if ( result == 0 ) {
			/////CLIENT
			Network::Server myUDPServer;
			myUDPServer.listen( 5001, Network::SockType::UDP, Network::IpFamily::Undefined );

			Network::Connection myTCPConnection;
			myTCPConnection.connect( "::1", 5001, Network::SockType::TCP );

			Network::Address addressFrom;
			if ( myUDPServer.receive( testData2, sizeof( testData2 ), &addressFrom ) )
				Log::displayLog( String() << "We got an UDP message from the server " << testData2 );

		} else if ( result == 1 ) {
			//SERVER
			Network::Server myTCPServer;
			myTCPServer.listen( 5001, Network::SockType::TCP, Network::IpFamily::Undefined );
			myTCPServer.listen( 5002, Network::SockType::TCP, Network::IpFamily::Undefined );

			Network::Connection clientConnection;
			while ( myTCPServer.accept( &clientConnection ) ) {
				clientConnection.setSockType( Network::SockType::UDP );
				clientConnection.connect();

				Log::displayLog( "Sending UDP Message to client." );

				clientConnection.send( testData, sizeof( testData ) );
			}
		} else {
			/////GOOGLE TEST
			Network::Connection myTCPConnection;

			if ( myTCPConnection.connect( "www.google.fr", 80, Network::SockType::TCP ) ) {
				Log::displayLog( String( "Connected to Google ! IP:" ) << myTCPConnection.getIp() );
			}
		}
	}
	#endif

	#endif	//DEBUG
	return 0;
}

#endif
