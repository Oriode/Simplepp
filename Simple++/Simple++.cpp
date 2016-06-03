///@file Simple++.cpp
///@brief Main file used for doing some test
///@author Clément Gerber
///@date 26/05/2016 (DMY) 


//#define SPEEDTEST_DRAWLINE
#define SPEEDTEST_STROKE
//#define SPEEDTEST_FILTER
//#define SPEEDTEST_ARRAYACCESS
//#define SPEEDTEST_LOGICAL
//#define SPEEDTEST_BLENDING
//#define SPEEDTEST_DATE
//#define SPEEDTEST_STRING_CONCAT
//#define SPEEDTEST_STRING_CAST
//#define SPEEDTEST_REGEX
//#define SPEEDTEST_VECTOR
//#define SPEEDTEST_MAP
//#define SPEEDTEST_NETWORK

#ifndef _LIB 
#include <iostream>
#include <string>
#include <chrono>
#include <map>
#include <regex>
#include <functional>

#include "Network.h"
#include "Math.h"
#include "String.h"
#include "Log.h"
#include "UTF8String.h"
#include "OrderedMap.h"
#include "Time.h"
#include "CoordinateChunk.h"
#include "Application.h"
#include "FreeImage.h"
#include "Graphic.h"
#include "Test.h"
#include "TextureLoadable.h"
#include "FontLoadable.h"
#include "Utility.h"
#include "Regex.h"
#include "GradientInterpolated.h"


template<typename T>
class ImageFunctor {
public:
	ImageFunctor() {};
	ImageFunctor & operator()(const Math::Vec2<Graphic::Size> & p, Graphic::ColorR<T> & color) { return *this; }
	ImageFunctor & operator()(const Math::Vec2<Graphic::Size> & p, Graphic::ColorRGB<T> & color) {
		unsigned int len = Math::length(p);
		color.r += len;
		color.g -= len;
		color.b += color.r + color.g;
		return *this; 
	}
	ImageFunctor & operator()(const Math::Vec2<Graphic::Size> & p, Graphic::ColorRGBA<T> & color) { return *this; }
};



int main(int argc, char * argv[]){
#ifdef DEBUG 
	/************************************************************************/
	/* DEBUG PART			                                          */
	/************************************************************************/

	Application<char> app(argc, argv);

	Graphic::FontLoadable font(L"consola.ttf", 15);
	font.load();
	font.loadGlyph(Graphic::Font::Template::Ascii);
	font.writeToFile(L"consola.cfont");

	Graphic::FontLoadable font2(L"consola.cfont");
	font2.load();

	font.writeToFile(L"consola2.cfont");

	Graphic::FreeImage glyphFreeImage;
	glyphFreeImage.loadFromDatas((unsigned char *) font2['A'] -> getDatas(), font2['A'] -> getSize(), Graphic::FreeImage::Format::R);
	glyphFreeImage.saveToFile("glyph_A.png", Graphic::FreeImage::SavingFormat::PNG);


	Graphic::FreeImage freeImage("sanctum.png", Graphic::FreeImage::Format::RGB);
	freeImage.load();

	Graphic::TextureLoadable<unsigned char> texture;
	texture.setDatas((unsigned char * ) freeImage.getDatas(), freeImage.getSize(), Graphic::LoadingFormat::BGR);
	texture.generateMipmaps();
	texture.writeToFile("sanctum.ctexture");
	
	Graphic::TextureLoadable<unsigned char> texture2(WString("sanctum.ctexture"));
	texture2.load();
	texture2.writeToFile("sanctum2.ctexture");


	/************************************************************************/
	/* DOING SOME TEST IN imageTest2                                        */
	/************************************************************************/

	Graphic::ColorRGBA<unsigned char> colorWhite(255,255,255,100);
	Graphic::ColorRGBA<unsigned char> colorRed(255, 0, 0, 255); 
	Graphic::ColorRGB<unsigned char> colorMagenta(255, 0, 150);
	Graphic::ColorRGBA<unsigned char> colorBlack(0, 0, 0, 150);
	Graphic::ColorRGBA<unsigned char> colorTransluscient(0, 0, 0, 0);


	Graphic::GradientVertical<Graphic::ColorRGBA<unsigned char>, Graphic::InterpolationFunc::Cubic> gradientVertical;
	gradientVertical.addPoint(0.0f, Graphic::ColorRGBA<unsigned char>(0, 0, 0, 255));
	gradientVertical.addPoint(1.0f, Graphic::ColorRGBA<unsigned char>(255, 255, 255, 255));



	Graphic::GradientHorizontal<Graphic::ColorRGBA<unsigned char>, Graphic::InterpolationFunc::Cubic> gradientHorizontal;
	gradientHorizontal.addPoint(0.0f, Graphic::ColorRGBA<unsigned char>(0, 0, 0, 255));
	gradientHorizontal.addPoint(1.0f, Graphic::ColorRGBA<unsigned char>(255, 255, 255, 255));


	Graphic::GradientLinear<Graphic::ColorRGBA<unsigned char>, Graphic::InterpolationFunc::Cubic> gradientLinear(45);
	gradientLinear.addPoint(0.0f, Graphic::ColorRGBA<unsigned char>(0, 0, 0, 255));
	gradientLinear.addPoint(0.2f, Graphic::ColorRGBA<unsigned char>(255, 0, 0, 255));
	gradientLinear.addPoint(0.4f, Graphic::ColorRGBA<unsigned char>(0, 255, 0, 255));
	gradientLinear.addPoint(0.6f, Graphic::ColorRGBA<unsigned char>(0, 0, 0, 0));
	gradientLinear.addPoint(0.8f, Graphic::ColorRGBA<unsigned char>(0, 255, 255, 255));
	gradientLinear.addPoint(1.0f, Graphic::ColorRGBA<unsigned char>(0, 255, 255, 255));


	Graphic::GradientRadial<Graphic::ColorRGBA<unsigned char>, Graphic::InterpolationFunc::Cubic> gradientRadial(Math::Vec2<float>(0,0.5));
	gradientRadial.addPoint(0.0f, Graphic::ColorRGBA<unsigned char>(0, 0, 0, 255));
	gradientRadial.addPoint(0.2f, Graphic::ColorRGBA<unsigned char>(255, 0, 0, 255));
	gradientRadial.addPoint(0.4f, Graphic::ColorRGBA<unsigned char>(0, 255, 0, 255));
	gradientRadial.addPoint(0.6f, Graphic::ColorRGBA<unsigned char>(0, 0, 0, 0));
	gradientRadial.addPoint(0.8f, Graphic::ColorRGBA<unsigned char>(0, 255, 255, 255));
	gradientRadial.addPoint(1.0f, Graphic::ColorRGBA<unsigned char>(0, 255, 255, 255));

	Graphic::Image & image = *( texture2[0] );

	{
		//////////////////////////////////////////////////////////////////////////
		// Copy Image										//
		Graphic::Image imageCopy = image;
		image = imageCopy;
	}

	{
		//////////////////////////////////////////////////////////////////////////
		// Blur Image										//
		unsigned int mySuperKernel10[21];
		Graphic::computeGaussianKernel(mySuperKernel10);
		image = image.applyFilter(mySuperKernel10, Graphic::Image::ConvolutionMode::NormalSize, Graphic::ColorRGBA<unsigned char>(0, 0, 0, 0));
	}

	{
		//////////////////////////////////////////////////////////////////////////
		// Apply Functor										//
		//image.setPixels(ImageFunctor<unsigned char>());
	}

	{
		//////////////////////////////////////////////////////////////////////////
		// Thresholding the image								//
		image.threshold(Graphic::ColorRGBA<unsigned char>(255), Graphic::ColorRGBA<unsigned char>(0), Graphic::ColorRGBA<unsigned char>(128, 0, 0, 0));
	}

	

	{
		//////////////////////////////////////////////////////////////////////////
		// Blur Image										//
		unsigned int mySuperKernel2[11];
		Graphic::computeGaussianKernel(mySuperKernel2);
		image = image.applyFilter(mySuperKernel2, Graphic::Image::ConvolutionMode::NormalSize, Graphic::ColorRGBA<unsigned char>(0, 0, 0, 0));
	}

	{
		//////////////////////////////////////////////////////////////////////////
		// Stroke											//
		image.drawStrokeFunctor(Graphic::Point(0, 0), *texture2[0], 2, Graphic::ColorFunc::SimpleColor<Graphic::ColorRGBA<unsigned char>>(Graphic::ColorRGBA<unsigned char>(0, 255, 0, 255)), Graphic::Image::StrokeType::Middle);
	}

	
	{
		//////////////////////////////////////////////////////////////////////////
		// Draw Line										//
		Graphic::ColorR<unsigned char> color(0);

		image.drawLine(Graphic::Line(250, 250, 500, 500), color, 5);
		image.drawLine(Graphic::Line(250, 250, 500, 400), color, 5);
		image.drawLine(Graphic::Line(250, 250, 500, 300), color, 5);
		image.drawLine(Graphic::Line(250, 250, 500, 250), color, 5);
		image.drawLine(Graphic::Line(250, 250, 500, 200), color, 5);
		image.drawLine(Graphic::Line(250, 250, 500, 100), color, 5);
		image.drawLine(Graphic::Line(250, 250, 500, 0), color, 5);

		image.drawLine(Graphic::Line(250, 250, 0, 500), color, 10);
		image.drawLine(Graphic::Line(250, 250, 0, 400), color, 5);
		image.drawLine(Graphic::Line(250, 250, 0, 300), color, 5);
		image.drawLine(Graphic::Line(250, 250, 0, 250), color, 5);
		image.drawLine(Graphic::Line(250, 250, 0, 200), color, 5);
		image.drawLine(Graphic::Line(250, 250, 0, 100), color, 5);
		image.drawLine(Graphic::Line(250, 250, 0, 0), color, 5);

		image.drawLine(Graphic::Line(250, 250, 0, 0), color, 5);
		image.drawLine(Graphic::Line(250, 250, 100, 0), color, 5);
		image.drawLine(Graphic::Line(250, 250, 200, 0), color, 5);
		image.drawLine(Graphic::Line(250, 250, 250, 0), color, 5);
		image.drawLine(Graphic::Line(250, 250, 300, 0), color, 5);
		image.drawLine(Graphic::Line(250, 250, 400, 0), color, 5);
		image.drawLine(Graphic::Line(250, 250, 500, 0), color, 5);

		image.drawLine(Graphic::Line(250, 250, 100, 500), color, 5);
		image.drawLine(Graphic::Line(250, 250, 200, 500), color, 5);
		image.drawLine(Graphic::Line(250, 250, 250, 500), color, 5);
		image.drawLine(Graphic::Line(250, 250, 300, 500), color, 5);
		image.drawLine(Graphic::Line(250, 250, 400, 500), color, 5);
		image.drawLine(Graphic::Line(250, 250, 500, 500), color, 5);
	}



	                                                  

	{
		//////////////////////////////////////////////////////////////////////////
		// Draw Text Glyph									//
		auto maskTest = font['A'];
		image.drawImage(Graphic::Point(300, 300), colorRed, Graphic::Rectangle(maskTest ->getSize()), *maskTest);
	}



	{
		//////////////////////////////////////////////////////////////////////////
		// Draw Rectangle RGBA									//
		image.drawRectangle(Graphic::Rectangle(0, 0, 250, 250), Graphic::ColorRGBA<unsigned char>(0, 255, 255, 100));
	}


	{
		//////////////////////////////////////////////////////////////////////////
		// Draw Text Point									//
		UTF8String testStr("Hello World?\nHow are you mofo yyyy?\ndsqhjgjfsdhg sdfg sdfhsdv fhg sdfh sdhfgv sdhgfv ghsdfv ghsd fhgs dfh sdh svdhgf sghd ?\nshdfgshfsdhgfgsf");
		Graphic::drawText(&image, font, Graphic::Point(250, 250), testStr, gradientVertical, Math::Vec2<bool>(true, true));
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
		// Draw Gradient as Functor								//
		Graphic::ColorFunc::GradientHorizontal<Graphic::ColorRGBA<unsigned char>, Graphic::InterpolationFunc::Cubic> testFunctorGradient(gradientHorizontal);
		image.drawRectangleFunctor(Graphic::Rectangle(250, 250, 500, 500), testFunctorGradient);
	}

	{
		//////////////////////////////////////////////////////////////////////////
		// Draw Line as Functor									//
		Graphic::ColorFunc::GradientHorizontal<Graphic::ColorRGBA<unsigned char>, Graphic::InterpolationFunc::Cubic> testFunctorGradient42(gradientHorizontal);
		image.drawLineFunctor(Graphic::Line(0, 0, 499, 499), testFunctorGradient42, 5);
	}

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
	freeImage2.loadFromDatas((unsigned char *) texture2.getDatas(0), texture2.getSize(0), Graphic::FreeImage::Format::RGB);
	freeImage2.saveToFile("sanctum3.png", Graphic::FreeImage::SavingFormat::PNG);

#else		//DEBUG
	const unsigned long long G10 = 10000000000;
	const unsigned long long G1 = 1000000000;
	const unsigned long long M100 = 100000000;
	const unsigned long long M10 = 10000000;
	const unsigned long long M1 = 1000000;
	const unsigned long long K100 = 100000;
	const unsigned long long K10 = 10000;
	const unsigned long long K1 = 1000;

#ifdef SPEEDTEST_DRAWLINE
	{
		//////////////////////////////////////////////////////////////////////////
		// SPEED TEST : Draw Lines								//

		Graphic::_Image<unsigned char> image(Math::Vec2<Graphic::Size>(500), Graphic::Format::R);

		Graphic::GradientHorizontal<Graphic::ColorRGBA<unsigned char>, Graphic::InterpolationFunc::Cubic> gradientHorizontal;
		gradientHorizontal.addPoint(0.0f, Graphic::ColorRGBA<unsigned char>(0, 0, 0, 255));
		gradientHorizontal.addPoint(1.0f, Graphic::ColorRGBA<unsigned char>(255, 255, 255, 255));
		Graphic::ColorFunc::GradientHorizontal<Graphic::ColorRGBA<unsigned char>, Graphic::InterpolationFunc::Cubic> colorFunctor(gradientHorizontal);



		Log::startChrono();
		for ( size_t i = 0; i < M1; i++ ) {
			//image.drawLine(Graphic::Line(0, 20, 500, 480), Graphic::ColorR<unsigned char>(255), 5);
			image.drawLineFunctor(Graphic::Line(0, 20, 500, 480), Graphic::ColorFunc::SimpleColor<Graphic::ColorR<unsigned char>>(Graphic::ColorR<unsigned char>(255)) , 1);

			//image.drawLineFunctor(Graphic::Line(0, 20, 500, 480), colorFunctor, 5);
		}
		Log::stopChrono();
		Log::displayChrono("DRAW LINES R -> R (Last Result: 1.9s for M1)");

		Graphic::FreeImage freeImage;
		freeImage.loadFromDatas((unsigned char *) image.getDatas(), image.getSize(), Graphic::FreeImage::Format::R);
		freeImage.saveToFile("drawline.png", Graphic::FreeImage::SavingFormat::PNG);
	}
#endif

#ifdef SPEEDTEST_FILTER
	{
		//////////////////////////////////////////////////////////////////////////
		// Filter											//
		Graphic::FreeImage freeImageIn("sanctum.png", Graphic::FreeImage::Format::RGB);
		freeImageIn.load();
		Graphic::_Image<unsigned char> image(freeImageIn.getDatas(), Math::Vec2<Graphic::Size>(500), Graphic::LoadingFormat::BGR, false);

		unsigned int gaussianKernel[11];
		Graphic::computeGaussianKernel(gaussianKernel);

		Log::startChrono();
		for ( size_t i = 0; i < K1; i++ ) {
			image = image.applyFilter(gaussianKernel, Graphic::Image::ConvolutionMode::NormalSize, Graphic::ColorRGBA<unsigned char>(0, 0, 0, 0));
		}
		Log::stopChrono();
		Log::displayChrono("FILTER (Last Result: 10.8s for K1)");

		Graphic::FreeImage freeImageOut;
		freeImageOut.loadFromDatas((unsigned char *) image.getDatas(), image.getSize(), Graphic::FreeImage::Format::RGB);
		freeImageOut.saveToFile("filter.png", Graphic::FreeImage::SavingFormat::PNG);
	}
#endif


#ifdef SPEEDTEST_STROKE
	{
		//////////////////////////////////////////////////////////////////////////
		// Stroke											//
		Graphic::FreeImage freeImageIn("sanctum.png", Graphic::FreeImage::Format::RGB);
		freeImageIn.load();
		Graphic::_Image<unsigned char> image(freeImageIn.getDatas(), Math::Vec2<Graphic::Size>(500), Graphic::LoadingFormat::RGB, false);
		image.threshold(Graphic::ColorRGBA<unsigned char>(255), Graphic::ColorRGBA<unsigned char>(0), Graphic::ColorRGBA<unsigned char>(128, 0, 0, 0));

		Log::startChrono();
		for ( size_t i = 0; i < K1; i++ ) {
			image.drawStrokeFunctor(Graphic::Point(0, 0), image, 2, Graphic::ColorFunc::SimpleColor<Graphic::ColorRGB<unsigned char>>(Graphic::ColorRGB<unsigned char>(0, 255, 0)), Graphic::Image::StrokeType::Outside);
		}
		Log::stopChrono();
		Log::displayChrono("STROKE (Last Result: 3658ms for K1)");

		Graphic::FreeImage freeImageOut;
		freeImageOut.loadFromDatas((unsigned char *) image.getDatas(), image.getSize(), Graphic::FreeImage::Format::RGB);
		freeImageOut.saveToFile("stroke.png", Graphic::FreeImage::SavingFormat::PNG);
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
		Log::displayChrono(String("LOGICAL < (Last : 5914ms) ") + sum);

		sum = 0;
		Log::startChrono();
		for ( size_t i = 0; i < G10; i++ ) {
			sum += ( i <= i + 2 ) ? 1 : 0;
		}
		Log::stopChrono();
		Log::displayChrono(String("LOGICAL <= (Last : 8281ms) ") + sum);
	}
#endif

#ifdef SPEEDTEST_ARRAYACCESS
	//////////////////////////////////////////////////////////////////////////
	// SPEED TEST : INT VS UINT Array access times.					//
	{
		int * testArray = new int[10000000];
		int sum = 0;
		int iteratorInt;
		int iteratorAdd = Math::random(0, 100);
		size_t j;
		Log::startChrono();
		for ( j = 0; j < M10; j++ ) {
			for ( iteratorInt = 0; iteratorInt < 1000; iteratorInt++ ) {
				sum += *( testArray + iteratorInt * iteratorAdd );
			}
		}
		Log::stopChrono();
		Log::displayChrono("INT ARRAY ACCESS" + sum);

		sum = 0;
		unsigned int iteratorUInt;
		Log::startChrono();
		for ( j = 0; j < M10; j++ ) {
			for ( iteratorUInt = 0; iteratorUInt < 1000; iteratorUInt++ ) {
				sum += *( testArray + iteratorUInt * iteratorAdd );
			}
		}
		Log::stopChrono();
		Log::displayChrono("UINT ARRAY ACCESS" + sum);

		sum = 0;
		size_t iteratorSizeT;
		Log::startChrono();
		for ( j = 0; j < M10; j++ ) {
			for ( iteratorSizeT = 0; iteratorSizeT < 1000; iteratorSizeT++ ) {
				sum += *( testArray + iteratorSizeT * iteratorAdd );
			}
		}
		Log::stopChrono();
		Log::displayChrono("SIZE_T ARRAY ACCESS" + sum);

		//RESULT : UINT is the faster nearly followed by SIZET, INT is a bit slower.
		delete[] testArray;
	}
#endif

#ifdef SPEEDTEST_BLENDING
	//////////////////////////////////////////////////////////////////////////
	// Speed Test : Testing RGBA Blending times float VS unsigned char	//
	{
		Graphic::ColorRGBA<unsigned char> colorWhite(255, 255, 255, 100);

		Graphic::Image testBlendRGBA(Math::Vec2<unsigned int>(200, 200), Graphic::Format::RGBA);
		Graphic::Image testBlendRGB(Math::Vec2<unsigned int>(200, 200), Graphic::Format::RGB);

		testBlendRGBA.fillImage(colorWhite);
		testBlendRGB.fillImage(colorWhite);

		Graphic::_Image<float> testBlendRGBAFloat(Math::Vec2<unsigned int>(100, 100), Graphic::Format::RGBA);
		Graphic::_Image<float> testBlendRGBFloat(Math::Vec2<unsigned int>(100, 100), Graphic::Format::RGB);

		Math::vec4f colorWhiteF(1.0, 1.0, 1.0, 1.0);
		Math::vec4f colorRedF(1.0, 0.0, 0.0, 0.0001);

		testBlendRGBAFloat.fillImage((const float *) &colorRedF);
		testBlendRGBFloat.fillImage((const float *) &colorWhiteF);

		Log::startChrono();
		for ( size_t i = 0; i < 10000; i++ ) {
			testBlendRGB.drawImage(Graphic::Point(0, 0), Graphic::Rectangle(0, testBlendRGB.getSize()), testBlendRGBA);
		}
		Log::stopChrono();
		Log::displayChrono("INT BLENDING RGBA -> RGB (last 2288ms)");


		Log::startChrono();
		for ( size_t i = 0; i < 10000; i++ ) {
			testBlendRGBFloat.drawImage(Graphic::Point(0, 0), Graphic::Rectangle(0, testBlendRGB.getSize()), testBlendRGBAFloat);
		}
		Log::stopChrono();
		Log::displayChrono("FLOAT BLENDING RGBA -> RGB (last 205ms)");

		Log::startChrono();
		for ( size_t i = 0; i < 10000; i++ ) {
			testBlendRGB.drawImage(Graphic::Point(0, 0), Graphic::Rectangle(0, testBlendRGB.getSize()), testBlendRGBA, Graphic::BlendingFunc::Normal());
		}
		Log::stopChrono();
		Log::displayChrono("INT BLENDING FUNCTOR RGBA -> RGB (last 2337ms)");


		Log::startChrono();
		for ( size_t i = 0; i < 10000; i++ ) {
			testBlendRGBFloat.drawImage(Graphic::Point(0, 0), Graphic::Rectangle(0, testBlendRGB.getSize()), testBlendRGBAFloat, Graphic::BlendingFunc::Normal());
		}
		Log::stopChrono();
		Log::displayChrono("FLOAT BLENDING FUNCTOR RGBA -> RGB (last 206ms)");

		Graphic::Image testblendCasted(testBlendRGBFloat);

		Graphic::FreeImage freeImage;
		freeImage.loadFromDatas((unsigned char *) testblendCasted.getDatas(), testblendCasted.getSize(), Graphic::FreeImage::Format::RGB);
		freeImage.saveToFile("blending.png", Graphic::FreeImage::SavingFormat::PNG);
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
			date = Time::Date(Time::getTime());
		}
		Log::stopChrono();
		Log::displayChrono(String() << "Date");

		Log::startChrono();
		for ( unsigned long i = 0; i < M10; i++ ) {
			time_t now = time(NULL);
			localtime_s(&timeinfo, &now);
		}
		Log::stopChrono();
		Log::displayChrono(String() << "localtime_s");
	}
#endif

#ifdef SPEEDTEST_STRING_CONCAT
	//////////////////////////////////////////////////////////////////////////
	// SPEED TEST : Concat Strings							//
	{
		String testStr("STRING STREAM : ");
		std::string testStr2("STRING : ");

		String strConcat("Hello World!");
		std::string strConcat2("Hello World!");


		Log::startChrono();
		for ( size_t i = 0; i < M10; i++ ) {
			testStr += String("Hello World!");
		}
		Log::stopChrono();
		Log::displayChrono(testStr.getSubStr(0, 30));

		Log::startChrono();
		for ( size_t i = 0; i < M10; i++ ) {
			testStr2 += std::string("Hello World!");
		}
		Log::stopChrono();
		Log::displayChrono(testStr2.substr(0, 30));
	}
#endif

#ifdef SPEEDTEST_STRING_CAST
	//////////////////////////////////////////////////////////////////////////
	// SPEED TEST : Cast Strings								//
	{
		float sum = 0;
		Log::startChrono();
		for ( unsigned long i = 0; i < 10000000; i++ ) {
			sum += atof("42.054217");
		}
		Log::stopChrono();
		Log::displayChrono("ATOF : " + String(sum));

		Log::startChrono();
		for ( unsigned long i = 0; i < 10000000; i++ ) {
			sum += String::toFloat("42.054217");
		}
		Log::stopChrono();
		Log::displayChrono("toFloat : " + String(sum));
	}
#endif

#ifdef SPEEDTEST_REGEX
	//////////////////////////////////////////////////////////////////////////
	// SPEED TEST : Regex									//
	{
		for ( unsigned int i = 0; i < 260; i++ ) {
			log(String(i) + " : " + Regex::match(i, "^2([0-4][0-9]|5[0-5])|1[0-9][0-9]?|[0-9]$"));
		}
		for ( unsigned int i = 0; i < 260; i++ ) {
			log(String(i) + " : " + Regex::match(i, "^2([0-4][0-9]?|5[0-5]?|[6-9])?|([3-9]|1)[0-9]?[0-9]?|0$"));
		}

		std::string stdString = "________255";

		bool stdResult = true;

		std::string txt_regex("2([0-4][0-9]|5[0-5])|1[0-9][0-9]?|[0-9]$");
		std::regex stdRegex(txt_regex, std::regex_constants::optimize);
		Log::startChrono();
		for ( unsigned long i = 0; i < M1; i++ ) {
			stdResult &= std::regex_search(stdString, stdRegex);
		}
		Log::stopChrono();
		Log::displayChrono("Regex .regex_match(); STD : " + String(stdResult));


		bool mineResult = true;
		String mineRegex = "2([0-4][0-9]|5[0-5])|1[0-9][0-9]?|[0-9]$";
		String mineString = "________255";

		Log::startChrono();
		for ( unsigned long i = 0; i < M1; i++ ) {
			mineResult &= Regex::match(mineString, mineRegex);
		}
		Log::stopChrono();
		Log::displayChrono("Vector .regex_match(); Mine : " + String(mineResult));
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
			vectorMine.push(i);
		}
		Log::stopChrono();
		Log::displayChrono("Vector .push_back(); Mine");

		Log::startChrono();
		for ( unsigned long i = 0; i < 10000000; i++ ) {
			vectorSTD.push_back(i);
		}
		Log::stopChrono();
		Log::displayChrono("Vector .push_back(); STD");
	}
#endif

#ifdef SPEEDTEST_MAP
	//////////////////////////////////////////////////////////////////////////
	// SPEED TEST : Maps									//
	{
		OrderedMap<unsigned long, unsigned long> mapMine;
		std::map<unsigned long, unsigned long> mapSTD;

		Log::startChrono();
		for ( unsigned long i = 0; i < M1; i++ ) {
			mapSTD.insert(std::pair<unsigned long, unsigned long>(Math::random(0, 100000), i));
		}
		Log::stopChrono();
		Log::displayChrono("Map .insert(); STD");

		Log::startChrono();
		for ( unsigned long i = 0; i < M1; i++ ) {
			mapMine.insertFast(Math::random(0, 100000), i);
		}
		Log::stopChrono();
		unsigned long _4572 = *mapMine[10];
		Log::displayChrono(String("Map .insert(); Mine ") + _4572);
		for ( auto it = mapMine.getBegin(); it != mapMine.getEnd(); it++ ) {
			Log::displayLog(String(it -> getIndex()) + " : " + it -> getValue());
		}
	}
#endif

#ifdef SPEEDTEST_NETWORK
	//////////////////////////////////////////////////////////////////////////
	// SPEED TEST : Network									//
	{
		int result;
		std::cout << "0 : Client, 1 : Server, Google Test : 2" << std::endl;
		scanf_s("%d", &result);

		char testData[50] = "Hello World";
		char testData2[50] = "";

		if ( result == 0 ) {
			/////CLIENT
			Network::Server myUDPServer;
			myUDPServer.listen(5001, Network::SockType::UDP, Network::IpFamily::Undefined);

			Network::Connection myTCPConnection;
			myTCPConnection.connect("::1", 5001, Network::SockType::TCP);

			Network::Address addressFrom;
			if ( myUDPServer.receive(testData2, sizeof(testData2), &addressFrom) )
				Log::displayLog(String() << "We got an UDP message from the server " << testData2);

		} else if ( result == 1 ) {
			//SERVER
			Network::Server myTCPServer;
			myTCPServer.listen(5001, Network::SockType::TCP, Network::IpFamily::Undefined);
			myTCPServer.listen(5002, Network::SockType::TCP, Network::IpFamily::Undefined);

			Network::Connection clientConnection;
			while ( myTCPServer.accept(&clientConnection) ) {
				clientConnection.setSockType(Network::SockType::UDP);
				clientConnection.connect();

				Log::displayLog("Sending UDP Message to client.");

				clientConnection.send(testData, sizeof(testData));
			}
		} else {
			/////GOOGLE TEST
			Network::Connection myTCPConnection;

			if ( myTCPConnection.connect("www.google.fr", 80, Network::SockType::TCP) ) {
				Log::displayLog(String("Connected to Google ! IP:") << myTCPConnection.getIp());
			}
		}
	}
#endif

#endif	//DEBUG
	return 0;
}

#endif
