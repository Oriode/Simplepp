/**
 * @file		Simple++.cpp.
 *
 * @brief		Main file used for doing some test. ( Will be ignored in release )
 * @author	Clément Gerber
 * @date		26/05/2016 (DMY)
 */

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
 //#define SPEEDTEST_DATE_PARSE
 //#define SPEEDTEST_STRING_CONCAT_STRING
 //#define SPEEDTEST_STRING_CONCAT_NUMBER
 //#define SPEEDTEST_STRING_FORMAT
 //#define SPEEDTEST_STRING_CAST
 //#define SPEEDTEST_REGEX
 //#define SPEEDTEST_VECTOR
 //#define SPEEDTEST_MAP
 //#define SPEEDTEST_CAST
 //#define SPEEDTEST_ARITHMETIC
 //#define SPEEDTEST_PATH
#define SPEEDTEST_BASE64


//#define DEBUG_GRAPHIC
//#define DEBUG_XML
//#define DEBUG_JSON
//#define DEBUG_LIST
//#define DEBUG_MAP
//#define DEBUG_UI
//#define DEBUG_IO
//#define DEBUG_NETWORK
//#define DEBUG_SSL
// #define DEBUG_HTTP
//#define DEBUG_CRYPTO
//#define DEBUG_BASE64
//#define DEBUG_HEXADECIMAL
//#define DEBUG_STRING
//#define DEBUG_TIME
// #define DEBUG_DATE
//#define DEBUG_PATH
//#define DEBUG_STREAM
//#define DEBUG_VEC
#define DEBUG_MAT
//#define DEBUG_TENSOR


#ifndef _LIB
#include <iostream>
#include <string>
#include <chrono>
#include <map>
#include <regex>
#include <functional>
#include <filesystem>
#include <sys/stat.h>

#include "Network/Network.h"
#include "Network/HTTPClient.h"
#include "Math/Math.h"
#include "Math/Vec.h"
#include "Math/Mat.h"
#include "Math/Tensor.h"
#include "String.h"
#include "Log.h"
#include "UTF8String.h"
#include "List.h"
#include "Map.h"
#include "Application.h"
#include "FreeImage.h"
#include "Graphic.h"
#include "Utility.h"
#include "Regex.h"
#include "Time/Time.h"
#include "Test.h"
#include "XML/XMLDocument.h"
#include "JSON/Node.h"
// #include "UI/UI.h"
// #include "UI/Window.h"
#include <functional>
#include "IO/Resource.h"
#include "IO/Manager.h"
#include "IO/Loadable.h"
#include "Math/BasicDistanceable.h"
#include "MultiMap.h"
#include "OS/Path.h"
#include "Stream.h"
#include "Crypto/Crypto.h"

namespace AI {


	class BasicInput {
	public:
		BasicInput() {}
	};


	/**
	 * @brief		Basic Class representing a Data ( An Entry of our AI Database )
	 *
	 * @tparam	InputT		Type of the input of the AI ( eg : for an AI doing image upscaling, the input will be an Image )
	 * @tparam	OutpuT		Type of the output of the AI
	 * @tparam	DistanceT		Type of the distance between two Data.
	 */
	template< typename InputT, typename OutputT, typename DistanceT = int >
	class BasicData {
	public:
		typedef DistanceT Distance;
		typedef InputT Input;
		typedef OutputT Output;

		BasicData(const Input& input) :
			_input(input),
			_distance(1) {}

		const typename Distance& getDistance() const {
			return this->_distance;
		}

		const typename Distance getDistance(const typename Input& input) const {
			return this->_distance;
		}

		void setDistance(const typename Distance& distance) {
			this->_distance = distance;
		}

	private:
		typename Distance _distance;
		typename Input _input;

	};


	/**
	 * @brief		An AI Neurode.
	 * @tparam	Distanceable	Object Base of Math.Compare.BasicDistanceable.
	 * @tparam	T			Entry of our AI Database.
	 */
	template< typename Input, typename DataT, typename HashTypeT = int >
	class BasicNeurode {
	public:
		typedef DataT Data;
		typedef HashTypeT HashType;

		/** @brief	Default constructor */
		BasicNeurode() {

		}

		/**
		 * @brief		Function to be implemented. Should retreive the Sub Data for this Neurode using the inputData.
		 *
		 * @param		inputData		Input Data to be comared.
		 *
		 * @returns	Null if no data has been founded ( or empty Vector )
		 * @sa		this.getDataMap();
		 */
		const Vector< typename Data* >* getSubData(const Input& inputData) const {
			/** to be overloaded */
			return NULL;
		}

		/**
		 * @brief		Get the Data Map.
		 *
		 * @returns	The Data Map.
		 */
		const MultiMap< typename Data::HashType, typename Data* >& getDataMap() {
			return this->_dataMap;
		}

		/**
		 * @brief		Gets the nearest value of a given one.
		 * @param		distanceable	Object to be compared.
		 * @param		resultMap [in, out]	Map to be edited.
		 */
		void updateResultMap(const Input& inputData, Map< const typename Data*, typename Data::Distance >& resultMap) const {
			// Retrieve the sub data for this neurode.
			const Vector< Data* >* nearestData = getSubData(inputData);

			// Check if we have founded something.
			if ( nearestData ) {
				for ( auto it(nearestData->getBegin()); it != nearestData->getEnd(); nearestData->iterate(&it) ) {
					const typename Data* data = nearestData->getValueIt(it);
					const typename Map< const typename Data*, typename Data::Distance >::Iterator distanceNodeIt(resultMap.getNodeI(data));

					// If the Value has already been founded.
					if ( distanceNodeIt ) {
						const typename Data::Distance oldDistance(resultMap.getValueIt(distanceNodeIt));
						const typename Data::Distance newDistance(oldDistance + data.getDistance(inputData));

						// Update the old Value.
						resultMap.setValueIt(distanceNodeIt, newDistance);
					} else {
						// The value does'nt exists actually.
						const typename Data::Distance newDistance(data.getDistance(inputData));

						// Insert into the Map.
						resultMap.insert(data, newDistance);
					}
				}
			}
		}


		/**
		 * @brief		Learn operation of this neurode.
		 *
		 * @param		inputData Data used to learn.
		 */
		void learn(const Input& inputData) {

		}


	private:
		/** @brief	The data map */
		MultiMap< typename Data::HashType, typename Data* > _dataMap;

	};
}




/**
 * @class		ImageFunctor
 *
 * @brief		Test of an Image Functor.
 *
 * @tparam	T	Generic type parameter.
 */
template<typename T>
class ImageFunctor {
public:
	ImageFunctor() {};
	ImageFunctor& operator()(const Math::Vec2<Graphic::Size>& p, Graphic::ColorR<T>& color) {
		return *this;
	}
	ImageFunctor& operator()(const Math::Vec2<Graphic::Size>& p, Graphic::ColorRGB<T>& color) {
		unsigned int len = Math::length(p);
		color.r += len;
		color.g -= len;
		color.b += color.r + color.g;
		return *this;
	}
	ImageFunctor& operator()(const Math::Vec2<Graphic::Size>& p, Graphic::ColorRGBA<T>& color) {
		return *this;
	}
};


// In case of Size error : (typename )?(Size


int main(int argc, char* argv[]) {
#ifdef DEBUG 
	/************************************************************************/
	/* DEBUG PART														*/
	/************************************************************************/
	Application<char> app(argc, argv);


	/************************************************************************/
	/* IO                                                                   */
	/************************************************************************/
#ifdef DEBUG_IO
	{

		{
			IO::Manager<Graphic::Texture<unsigned char>> textureManager;
			IO::Resource<Graphic::Texture<unsigned char>> textureResource(&textureManager);
			OS::Path filePath("sanctum.ctexture");

			//assert( IO::write( "TextureManager.cmanager", &textureManager ) );
			//assert( IO::read( "TextureManager.cmanager", &textureManager ) );
			info(StringASCII("Resource counter : (expected : 0) : ") << textureManager.getNbUses(filePath));

			// Adding one resource with the Resource
			assert(textureResource.setObject(filePath));
			info(StringASCII("Resource counter : (expected : 1) : ") << textureManager.getNbUses(filePath));

			info(StringASCII("Texture Height : (expected : 500) : ") << textureResource.getObject()->getHeight());

			// Adding a texture directly to the manager.
			assert(textureManager.addObject(filePath));
			info(StringASCII("Resource counter : (expected : 2) : ") << textureManager.getNbUses(filePath));

			// Changing resource to something external.
			Graphic::Texture<unsigned char> textureTest;
			assert(textureResource.setObject(&textureTest));
			// One Resource has been deleted, the counter should be 1.
			info(StringASCII("Resource counter : (expected : 1) : ") << textureManager.getNbUses(filePath));

			// Set back an internaly texture.
			assert(textureResource.setObject(filePath));
			info(StringASCII("Resource counter : (expected : 2) : ") << textureManager.getNbUses(filePath));
			// Now the texture should be managed by the textureManager.

			// Add a texture directly to the manager.
			assert(textureManager.addObject(filePath));
			info(StringASCII("Resource counter : (expected : 3) : ") << textureManager.getNbUses(filePath));

			IO::Loadable<Graphic::Texture<unsigned char>> textureLoadable(filePath);

			assert(textureLoadable.load());
			info(StringASCII("Texture Loaded as a Loadable, Height : (expected : 500) : ") << textureLoadable.getObject()->getHeight());

			// Now try to write the loadable as a BasicIO.
			assert(IO::write(filePath, &textureLoadable));

			// And now read it again.
			assert(IO::read(filePath, &textureLoadable));
			info(StringASCII("Texture Loaded as a BasicIO, Height : (expected : 500) : ") << textureLoadable.getObject()->getHeight());


			info("Every IO Tests passed.");
		}
		/*
		{
			IO::IOManagerLoadable<Graphic::Texture<unsigned char>> textureManager;
			IO::IOHandlerLoadable<Graphic::Texture<unsigned char>> textureResource(&textureManager);


			//assert( IO::write( "TextureManager.cmanager", &textureManager ) );
			//assert( IO::read( "TextureManager.cmanager", &textureManager ) );
			assert( textureResource.setObject( "sanctum.ctexture" ) );

			Graphic::Texture<unsigned char> textureTest;

			assert( textureManager.load() );

			// Should be loaded by the Manager.
			assert( textureResource.isLoaded() );
			assert( textureResource.load() );
			assert( textureResource.unload() );
			assert( textureResource.load() );


			assert( textureResource.setObject( &textureTest ) );

			assert( textureResource.setObject( "sanctum.ctexture" ) );
		}
		*/



		/*
		Graphic::FreeImage freeImage;
		freeImage.loadFromDatas( ( unsigned char * ) textureResource.getObject() -> getDatas( 0 ), textureResource.getObject() -> getSize( 0 ), Graphic::FreeImage::Format::RGB );
		freeImage.saveToFile( "sanctum test textureManager i will delete.png", Graphic::FreeImage::SavingFormat::PNG );
		*/
	}
#endif


	/************************************************************************/
	/* UI                                                                   */
	/************************************************************************/
#ifdef DEBUG_UI
	{
		Graphic::FreeImage freeImage("sanctum.png", Graphic::FreeImage::Format::RGB, true);
		freeImage.load();

		Graphic::Image imageTmp(( unsigned char* ) freeImage.getDatas(), freeImage.getSize(), Graphic::LoadingFormat::BGR);

		Graphic::TextureLoadable<unsigned char> texture;

		texture.setDatas(imageTmp.toFormat(Graphic::Format::RGBA));
		texture.generateMipmaps();



		GLFW::load();




		UI::Window window;
		window.setCursorMode(GLFW::Window::CursorMode::Disabled);

		//window.setCursor( &( texture[0] ) );

		window.load();



		window.setIcon(&texture);


		//window.setFullscreen(NULL, Math::Vec2<unsigned int>(800,600), 60);

		window.show();

	}
#endif




	/************************************************************************/
	/* XML PART																*/
	/************************************************************************/
#ifdef DEBUG_XML
	{
		UTF8String testStr("Hello world");
		UTF8String testDocumentStr("<?xml version=\"1.0\" encoding=\"UTF - 8\"?><class testParam=\"xD\">test</class>");
		XML::Document testDocument(OS::Path("test.xml"));

		auto nodeTest(testDocument.getElementsById("test"));

		UTF8String TEST = UTF8String::null;

		if ( nodeTest.getSize() ) {
			nodeTest[ 0 ]->appendXML(WString("<span id=\"new\"><child>New Value 1 !</child><child>New Value 2 !</child></span>"));

			nodeTest[ 0 ]->getChild(0)->addChild(new XML::NodeText(" Hello World!"));
			UTF8String value(nodeTest[ 0 ]->getValue());
			info(value);
		}

		assert(IO::write(WString("testXML.cxml"), &testDocument));
		assert(IO::read(WString("testXML.cxml"), &testDocument));





		Log::displayLog(testDocument.toString<WString>());
		testDocument.writeFileXML(OS::Path("testOut.xml"));



		int test;

	}
#endif




	/************************************************************************/
	/* JSON PART															*/
	/************************************************************************/
#ifdef DEBUG_JSON
	{
		{
			JSON::Document jsonDocument;
			JSON::NodeMap* rootNode(new JSON::NodeMap());
			JSON::NodeMap* childNode(new JSON::NodeMap("childNode"));
			JSON::NodeMap* arrayNode(new JSON::NodeArray("arrayNode"));

			arrayNode->addChild(new JSON::NodeValue(1));
			arrayNode->addChild(new JSON::NodeValue(2));
			arrayNode->addChild(new JSON::NodeValue(3));
			arrayNode->addChild(new JSON::NodeValue(4));

			rootNode->addChild(childNode);
			rootNode->addChild(arrayNode);

			childNode->addChild(new JSON::NodeValue("test", 43));
			childNode->addChild(NULL);

			Log::displayLog(rootNode->toString());
		}
		{
			JSON::Document jsonDocument;
			jsonDocument.readJSON("{ \"test\": { \"test2\" : \"Hello World !\" }, \"xD\":42, \"empty\":{}, \"null\": null, \"array\" : [ \"Hello\" , 42, [{\"object\":10}] ] }");

			Vector<JSON::NodeMap*> searchNode = jsonDocument.getElementsByName("test2");

			if ( searchNode.getSize() ) {
				// Should display "Hello World !"
				Log::displayLog(searchNode[ 0 ]->getValue());
			}

			Log::displayLog(jsonDocument.getRoot()->getName());
			Log::displayLog(jsonDocument.toString());
		}
		{
			JSON::Document jsonDocument;
			jsonDocument.readFileJSON("test.json");

			Log::displayLog(jsonDocument.toString());


			assert(IO::write(WString("testJSON.cjson"), &jsonDocument));
			assert(IO::read(WString("testJSON.cjson"), &jsonDocument));

			Log::displayLog(jsonDocument.toString());
		}
		{
			StringASCII jsonStr("{\"futuresType\":\"\",\"rateLimits\":[{\"rateLimitType\":\"\",\"interval\":\"\",\"intervalNum\":1,\"limit\":2400}],\"exchangeFilters\":[],\"assets\":\"\"}");

			JSON::Document jsonDocument;
			jsonDocument.readJSON(jsonStr);
			Log::displayLog(jsonDocument.toString());
		}
		{
			StringASCII jsonStr("[1,2,3,4,5,6,7,8,9]");

			JSON::Document jsonDocument;
			jsonDocument.readJSON(jsonStr);

			assert(IO::write(WString("testJSONArray.cjson"), &jsonDocument));
			assert(IO::read(WString("testJSONArray.cjson"), &jsonDocument));

			Log::displayLog(jsonDocument.toString());
		}
		{
			StringASCII jsonStr("");

			JSON::Document jsonDocument;
			jsonDocument.readJSON(jsonStr);
			Log::displayLog(jsonDocument.toString());
		}
	}
#endif
#ifdef DEBUG_LIST
	{
		info("Debugging Lists...");

		List<float> floatList;
		floatList.push(42.0f);
		floatList.push(1.0f);
		floatList.push(2.0f);
		floatList.push(3.0f);
		typename List<float>::Iterator it4(floatList.push(4.0f));
		typename List<float>::Iterator it5(floatList.push(5.0f));
		floatList.push(6.0f);

		floatList.insert(7.0f, it4);
		floatList.eraseIt(it5);
		floatList.popBegin();
		floatList.pop();
		floatList.pushBegin(42.0f);
		floatList.pushBegin(42.0f);
		floatList.eraseAll(42.0f);
		floatList.replaceFirst(1.0f, 42.0f);

		List<float> floatListCopy = floatList;

		IO::write(OS::Path("floatList.cl"), &floatListCopy);
		IO::read(OS::Path("floatList.cl"), &floatListCopy);

		info(floatListCopy.toString());
	}
#endif // DEBUG_LIST
#ifdef DEBUG_MAP
	{
		info("Debuging Maps...");

		// Test if the compare is working fine.
		auto r = Math::Compare::compare(UTF8String("Hello"), UTF8String("World"));

		// Test if the convertion to String is working.
		info(String(r));

		Map<unsigned long int, unsigned long int> testMap;

		testMap.insert(0, 0);
		testMap.insert(1, 1);
		testMap.insert(2, 2);
		testMap.insert(3, 3);
		testMap.insert(4, 4);
		testMap.insert(5, 5);
		testMap.insert(6, 6);
		testMap.insert(7, 7);
		testMap.insert(8, 8);
		testMap.insert(9, 9);

		info("Map : ");
		for ( auto it(testMap.getBegin()); it != testMap.getEnd(); testMap.iterate(&it) ) {
			info(testMap.getValueIt(it));
		}

		info("Map Ascending : ");
		for ( auto it(testMap.getSmallest()); it != testMap.getEnd(); testMap.iterateAscending(&it) ) {
			info(testMap.getValueIt(it));
		}

		info(StringASCII(testMap));


		{
			// Testing IN/OUT
			assert(IO::write(WString("myMap.font"), &testMap));

			Map<unsigned long int, unsigned long int> mapLoaded;
			assert(IO::read(WString("myMap.font"), &mapLoaded));

			info(StringASCII(mapLoaded));
		}

		{
			// Testing Copy
			Map<unsigned long int, unsigned long int> mapCopied = testMap;

			info(StringASCII(mapCopied));

		}

		for ( unsigned long int j(0); j < 100; j++ ) {
			Map<unsigned long int, unsigned long int> testMap;
			for ( unsigned long int i(0); i < 100; i++ ) {
				testMap.insert(i, i);
			}
			testMap.eraseI(j);
		}

		for ( unsigned long int i(0); i < 1000; i++ ) {
			testMap.insert(Math::random(0, 1000), i);
		}


		for ( unsigned long int i(0); i < 1000; i++ ) {
			testMap.eraseI(Math::random(0, 1000));
		}
		//info( StringASCII( testMap ) );

		Map<int, String> mapTest;
		mapTest.insert(42, "Hello World !");

		String* nodeResult(mapTest[ 42 ]);
		if ( nodeResult ) {
			info(StringASCII("Node 42 (expected : Hello World !) : ") << *nodeResult);
		} else {
			error("Index 42 not founded.");
		}

	}
#endif





#ifdef DEBUG_GRAPHIC
	/************************************************************************/
	/* GRAPHIC PART									                        */
	/************************************************************************/

	Graphic::ColorRGB<unsigned char> colorUC(6, 0, 8);
	Graphic::ColorRGB<float> colorF(0.33, 0.86, 0.96);

	info(StringASCII(colorF.HSLtoRGB()));



	Graphic::TrueTypeFont<unsigned char> font(L"consola.ttf", 40);
	font.load();
	font.loadGlyph(Graphic::Font<unsigned char>::Template::Ascii);
	IO::write(L"consola.cfont", &font);


	Graphic::Font<unsigned char> font2;
	IO::read(L"consola.cfont", &font2);

	IO::write(L"consola2.cfont", &font2);

	Graphic::FreeImage glyphFreeImage;
	glyphFreeImage.loadFromDatas(( unsigned char* ) font2[ 'A' ]->getDatas(), font2[ 'A' ]->getSize(), Graphic::FreeImage::Format::R);
	glyphFreeImage.saveToFile("glyph_A.png", Graphic::FreeImage::SavingFormat::PNG);


	Graphic::FreeImage freeImage("sanctum.png", Graphic::FreeImage::Format::RGB);
	freeImage.load();

	Graphic::Texture<unsigned char> texture;
	texture.setDatas(( unsigned char* ) freeImage.getDatas(), freeImage.getSize(), Graphic::LoadingFormat::BGR);
	texture.generateMipmaps();
	IO::write("sanctum.ctexture", &texture);


	IO::Loadable<Graphic::Texture<unsigned char>> textureLoadable("sanctum.ctexture");
	assert(textureLoadable.load());
	Graphic::Texture<unsigned char>& textureLoaded(*textureLoadable.getObject());


	IO::write("sanctum2.ctexture", &textureLoadable);

	/************************************************************************/
	/* DOING SOME TEST IN imageTest2                                        */
	/************************************************************************/

	Graphic::ColorRGBA<unsigned char> colorWhite(255, 255, 255, 100);
	Graphic::ColorRGBA<unsigned char> colorRed(255, 0, 0, 255);
	Graphic::ColorRGB<unsigned char> colorMagenta(255, 0, 150);
	Graphic::ColorRGBA<unsigned char> colorBlack(0, 0, 0, 150);
	Graphic::ColorRGBA<unsigned char> colorTransluscient(0, 0, 0, 0);


	Graphic::Gradient::Vertical<Graphic::ColorRGBA<unsigned char>, Math::InterpolationFunc::Linear> gradientVertical;
	gradientVertical.addPoint(0.0f, Graphic::ColorRGBA<unsigned char>(255, 255, 255, 255));
	gradientVertical.addPoint(1.0f, Graphic::ColorRGBA<unsigned char>(100, 100, 100, 255));



	Graphic::Gradient::Horizontal<Graphic::ColorRGBA<unsigned char>, Math::InterpolationFunc::Linear> gradientHorizontal;
	gradientHorizontal.addPoint(0.0f, Graphic::ColorRGBA<unsigned char>(0, 0, 0, 255));
	gradientHorizontal.addPoint(1.0f, Graphic::ColorRGBA<unsigned char>(255, 255, 255, 255));


	Graphic::Gradient::Linear<Graphic::ColorRGBA<unsigned char>, Math::InterpolationFunc::Cubic> gradientLinear(45);
	gradientLinear.addPoint(0.0f, Graphic::ColorRGBA<unsigned char>(0, 0, 0, 255));
	gradientLinear.addPoint(0.2f, Graphic::ColorRGBA<unsigned char>(255, 0, 0, 255));
	gradientLinear.addPoint(0.4f, Graphic::ColorRGBA<unsigned char>(0, 255, 0, 255));
	gradientLinear.addPoint(0.6f, Graphic::ColorRGBA<unsigned char>(0, 0, 0, 0));
	gradientLinear.addPoint(0.8f, Graphic::ColorRGBA<unsigned char>(0, 255, 255, 255));
	gradientLinear.addPoint(1.0f, Graphic::ColorRGBA<unsigned char>(0, 255, 255, 255));


	Graphic::Gradient::Radial<Graphic::ColorRGBA<unsigned char>, Math::InterpolationFunc::Cubic> gradientRadial(Math::Vec2<float>(0.5, 0.5), Math::Vec2<float>(0.5, 0.5));
	gradientRadial.addPoint(0.0f, Graphic::ColorRGBA<unsigned char>(0, 0, 0, 255));
	gradientRadial.addPoint(0.2f, Graphic::ColorRGBA<unsigned char>(255, 0, 0, 255));
	gradientRadial.addPoint(0.4f, Graphic::ColorRGBA<unsigned char>(0, 255, 0, 255));
	gradientRadial.addPoint(0.6f, Graphic::ColorRGBA<unsigned char>(0, 0, 0, 0));
	gradientRadial.addPoint(0.8f, Graphic::ColorRGBA<unsigned char>(0, 255, 255, 255));
	gradientRadial.addPoint(1.0f, Graphic::ColorRGBA<unsigned char>(0, 255, 255, 255));

	Graphic::Image image(textureLoaded[ 0 ]);


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
		UTF8String testStr("Hello World\nThis Lib is Awesome !");

		typedef Graphic::FontEffect<unsigned char, Graphic::ColorFunc::SimpleColor<Graphic::ColorRGBA<unsigned char>>, Graphic::ColorFunc::SimpleColor<Graphic::ColorRGBA<unsigned char>>> FontType;
		FontType myFont(L"consola.ttf", 30);

		myFont.setOverlayColorFunc(Graphic::ColorFunc::SimpleColor<Graphic::ColorRGBA<unsigned char>>(Graphic::ColorRGBA<unsigned char>(255, 255, 255, 255)));
		myFont.setShadowActivated(false);
		myFont.setShadowColorFunc(Graphic::ColorFunc::SimpleColor<Graphic::ColorRGBA<unsigned char>>(Graphic::ColorRGBA<unsigned char>(0, 0, 0, 250)));
		myFont.setShadowRadius(2);
		myFont.setShadowBias(Math::Vec2<float>(1, -1));


		myFont.setStrokeActivated(true);
		myFont.setStrokeSize(1.9f);
		myFont.setStrokeColorFunc(Graphic::ColorFunc::SimpleColor<Graphic::ColorRGBA<unsigned char>>(Graphic::ColorRGBA<unsigned char>(0, 0, 0, 150)));

		FontType myFontCOPY = myFont;
		myFontCOPY.loadGlyph(Graphic::FontEffect<unsigned char>::Template::Ascii);

		assert(IO::write(WString("myFontCustomdeOUF.font"), &myFontCOPY));


		FontType myFontCp;


		assert(IO::read(WString("myFontCustomdeOUF.font"), &myFontCp));



		auto maskTest = myFontCp[ 'A' ];
		//image.drawImage(Graphic::Point(300, 300), *maskTest);

		Graphic::Text<unsigned char> myText;
		myText.setText(myFontCp, testStr, Math::Vec2<bool>(true, true));

		//Graphic::drawText( &image, myFontCp, Graphic::Point(250,250), testStr,  Math::Vec2<bool>( true, true ) );

		assert(IO::write(WString("myText.cimg"), &myText));
		Graphic::Text<unsigned char> myTextCp;
		assert(IO::read(WString("myText.cimg"), &myTextCp));

		auto mipmap = myTextCp.resample(Math::Vec2<Graphic::Size>(myTextCp.getSize() / 2), Graphic::Image::ResamplingMode::Lanczos);
		image.drawImage(Graphic::Point(myTextCp.getBias() / 2.0f) + Graphic::Point(250, 250), mipmap);

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
			image.drawImage( Graphic::Point( 0, 0 ), textureLoadable[0] -> resample( Math::Vec2<Graphic::Size>( 100, 500 ), Graphic::Image::ResamplingMode::Lanczos ) );
			image.drawImage( Graphic::Point( 200, 0 ), textureLoadable[0] -> resample( Math::Vec2<Graphic::Size>( 100, 100 ), Graphic::Image::ResamplingMode::Lanczos ) );
			image.drawImage( Graphic::Point( 300, 0 ), textureLoadable[0] -> resample( Math::Vec2<Graphic::Size>( 50, 50 ), Graphic::Image::ResamplingMode::Lanczos ) );
			image.drawImage( Graphic::Point( 350, 0 ), textureLoadable[0] -> resample( Math::Vec2<Graphic::Size>( 25, 25 ), Graphic::Image::ResamplingMode::Lanczos ) );

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


	textureLoaded[ 0 ] = image;

	{
		//////////////////////////////////////////////////////////////////////////
		// Generate Mipmaps									//
		textureLoaded.generateMipmaps();
	}


	{
		//////////////////////////////////////////////////////////////////////////
		// Draw Mipmaps										//
		for ( size_t i = 1; i < textureLoaded.getNbMipmaps(); i++ ) {
			//imageTest2[0] -> drawImage(Graphic::Point(0, 0), *imageTest2[i]);
		}
	}


	//////////////////////////////////////////////////////////////////////////
	// Saving to file										//
	Graphic::FreeImage freeImage2;
	freeImage2.loadFromDatas(( unsigned char* ) textureLoaded.getDatas(0), textureLoaded.getSize(0), Graphic::FreeImage::Format::RGB);
	freeImage2.saveToFile("sanctum3.png", Graphic::FreeImage::SavingFormat::PNG);
#endif

#ifdef DEBUG_NETWORK
	//////////////////////////////////////////////////////////////////////////
	// DEBUG : Network									//
	{
		int result;
		std::cout << "0 : Client, 1 : Server, Google Test : 2" << std::endl;
		scanf_s("%d", &result);

		char messageToSend[] = "Hello World !\xE2\x9C\xAD";
		char buffer[ 50 ] = "";

		if ( result == 0 ) {
			/////CLIENT
			Network::Server myUDPServer;
			myUDPServer.listen(5001, Network::SockType::UDP, Network::IpFamily::Undefined);

			Network::Connection myTCPConnection;
			myTCPConnection.connect("::1", 5001, Network::SockType::TCP);
			myTCPConnection.receive(buffer, sizeof(buffer));
			Log::displayLog(StringASCII() << "We are connected to the server and received the message : " << buffer);

			Network::Address addressFrom;
			if ( myUDPServer.receive(buffer, sizeof(buffer), &addressFrom) )
				Log::displayLog(StringASCII() << "We got an UDP message from the server " << buffer);

		} else if ( result == 1 ) {
			//SERVER
			Network::Server myTCPServer;
			myTCPServer.listen(5001, Network::SockType::TCP, Network::IpFamily::Undefined);
			// myTCPServer.listen( 5002, Network::SockType::TCP, Network::IpFamily::Undefined );

			Network::Connection clientConnection;
			while ( myTCPServer.accept(&clientConnection) ) {


				while ( true ) {
					if ( !clientConnection.receive(buffer, sizeof(buffer)) ) {
						break;
					}
					Log::displayLog(StringASCII::format("Received String \"%\" from client.", buffer));
				}

				/*
				clientConnection.setSockType( Network::SockType::UDP );
				clientConnection.connect();

				Log::displayLog( "Sending UDP Message to client." );

				clientConnection.send( messageToSend, sizeof( messageToSend ) );
				*/
			}
		} else {
			/////GOOGLE TEST
			Network::Connection myTCPConnection;

			if ( myTCPConnection.connect("www.google.fr", 80, Network::SockType::TCP) ) {
				Log::displayLog(StringASCII("Connected to Google ! IP:") << myTCPConnection.getIp());
			}
		}
	}
#endif
#ifdef DEBUG_SSL
	//////////////////////////////////////////////////////////////////////////
	// DEBUG : SSL									//

	/////GOOGLE TEST
	{
		Network::TLSConnection myTCPConnection;

		if ( myTCPConnection.connect("google.com", 443, Network::SockType::TCP) ) {
			Log::displayLog(StringASCII("Connected to Google ! IP:") << myTCPConnection.getIp());

			char query[] = "GET https://about.google HTTP/1.1\r\nAccept: */*\r\nConnection: close\r\n\r\n";
			if ( !myTCPConnection.send(query, sizeof(query)) ) {
				Log::displayError("Unable to send the query.");
			}

			char receiveBuffer[ 1000000 ];
			int receivedLength(myTCPConnection.receive(receiveBuffer, sizeof(receiveBuffer)));

			Log::displayLog(StringASCII(receiveBuffer, receivedLength));
		}
	}
#endif
#ifdef DEBUG_HTTP
	//////////////////////////////////////////////////////////////////////////
	// DEBUG : HTTP									//
	{
		Network::HTTPClient client(Network::HTTPRequest::Type::HTTPS, StringASCII("fapi.binance.com"));
		client.setHeaderParam(StringASCII("X-MBX-APIKEY"), StringASCII("q4Uuz9yQUUrj5zA3PGRROFeq03Binump7hkytN19qCBlitr8NCWICT2Wvqybn8Y8"));
		StringASCII secretKey("qi3IiH87ajbcxfEzQeBSAPf9dlHhnSzUYAE75pCdeETi3VN7iJHq0q0RrR4a1ZKW");

		Vector<Network::HTTPParam> paramVector;
		// paramVector.push(Param(StringASCII("symbol"), StringASCII("BTCUSDT")));
		Time::TimeT timestamp(Time::getTime<Time::MilliSecond>().getValue());
		paramVector.push(Param(StringASCII("timestamp"), StringASCII(timestamp)));
		paramVector.push(Param(StringASCII("recvWindow"), StringASCII(20000)));

		StringASCII paramsStr(Network::Url::formatParams(paramVector));

		Vector<unsigned char> hashBinary(Crypto::HMACSha256<char>(secretKey, paramsStr));
		StringASCII signatureStr(StringASCII::encodeHexadecimal(hashBinary));

		paramVector.push(Param(StringASCII("signature"), signatureStr));

		Network::HTTPResponse* response1(client.query(Network::HTTPRequest::Method::GET, StringASCII("/fapi/v2/account"), paramVector));

		Time::sleep(10000);

		Network::HTTPResponse* response2(client.query(Network::HTTPRequest::Method::GET, StringASCII("/fapi/v2/account"), paramVector));

		if ( response1 && response2 ) {
			Log::displayLog(response2->getContent());
		} else {
			Log::displayError("Query failed.");
		}

		paramVector.clear();
		paramVector.push(Param(StringASCII("symbol"), StringASCII("BTCUSDT")));

		for ( Size i(0); i < Size(10); i++ ) {
			if ( !client.query(Network::HTTPRequest::Method::GET, StringASCII("/fapi/v1/premiumIndex"), paramVector) ) {
				Log::displayError("Query failed.");
				break;
			}
			Log::displayLog(response1->getContent());
		}

		Log::displaySuccess("Success.");
	}
#endif
#ifdef DEBUG_CRYPTO
	//////////////////////////////////////////////////////////////////////////
	// DEBUG : CRYPTO									//
	{
		StringASCII keyStr("NhqPtmdSJYdKjVHjA7PZj4Mge3R5YNiP1e3UZjInClVN65XAbvqqM6A7H5fATj0j");
		StringASCII dataStr("symbol=LTCBTC&side=BUY&type=LIMIT&timeInForce=GTC&quantity=1&price=0.1&recvWindow=5000&timestamp=1499827319559");

		Vector<unsigned char> keyBinary(keyStr);
		Vector<unsigned char> dataBinary(dataStr);

		Vector<unsigned char> digestBinary(Crypto::digestSha256<char>(dataBinary));

		Vector<unsigned char> hashBinary(Crypto::HMACSha256<char>(keyBinary, dataBinary));

		StringASCII hashStr(StringASCII::encodeHexadecimal(hashBinary));

		info(hashStr);
	}
#endif
#ifdef DEBUG_BASE64
	//////////////////////////////////////////////////////////////////////////
	// DEBUG : BASE64									//
	{
		struct GenerateVectorFunctor {
			GenerateVectorFunctor(Size sizeMin, Size sizeMax) :
				sizeMin(sizeMin),
				sizeMax(sizeMax) {}

			Vector<unsigned char> operator()() const {
				Vector<unsigned char> outputVector;
				Size newSize(Math::random(this->sizeMin, this->sizeMax));
				outputVector.resize(newSize);

				for ( Size i(0); i < outputVector.getSize(); i++ ) {
					outputVector.setValueI(i, unsigned char(Math::random(unsigned char(0), unsigned char(255))));
				}

				return outputVector;
			}

			Size sizeMin;
			Size sizeMax;
		};

		GenerateVectorFunctor generateVectorFunctor(Size(128), Size(256));
		Size nbTests(10000);

		for ( Size i(0); i < nbTests; i++ ) {
			Vector<unsigned char> dataVector(generateVectorFunctor());

			StringASCII outputStr(StringASCII::encodeBase64(dataVector));
			Vector<unsigned char> outputVector(StringASCII::decodeBase64(outputStr));

			info(outputStr);

			if ( dataVector != outputVector ) {
				error("Error.");
				break;
			}
		}

		info("Success !");
	}
#endif
#ifdef DEBUG_HEXADECIMAL
	//////////////////////////////////////////////////////////////////////////
	// DEBUG : HEXADECIMAL									//
	{
		struct GenerateVectorFunctor {
			GenerateVectorFunctor(Size sizeMin, Size sizeMax) :
				sizeMin(sizeMin),
				sizeMax(sizeMax) {}

			Vector<unsigned char> operator()() const {
				Vector<unsigned char> outputVector;
				Size newSize(Math::random(this->sizeMin, this->sizeMax));
				outputVector.resize(newSize);

				for ( Size i(0); i < outputVector.getSize(); i++ ) {
					outputVector.setValueI(i, unsigned char(Math::random(unsigned char(0), unsigned char(255))));
				}

				return outputVector;
			}

			Size sizeMin;
			Size sizeMax;
		};

		GenerateVectorFunctor generateVectorFunctor(Size(128), Size(256));
		Size nbTests(10000);

		for ( Size i(0); i < nbTests; i++ ) {
			Vector<unsigned char> dataVector(generateVectorFunctor());

			StringASCII outputStr(StringASCII::encodeHexadecimal(dataVector));
			Vector<unsigned char> outputVector(StringASCII::decodeHexadecimal(outputStr));

			info(outputStr);

			if ( dataVector != outputVector ) {
				error("Error.");
				break;
			}
		}

		info("Success !");
	}
#endif
#ifdef DEBUG_STRING
	//////////////////////////////////////////////////////////////////////////
	// DEBUG : Strings											//
	{
		info("Hello World !");
		info(StringASCII("hElLo WoRlD !").toUpper());
		info(StringASCII("hElLo WoRlD !").toLower());
		StringASCII testStr("STRING 1 : ");
		StringASCII strConcat("Hello World!");
		Log::displayLog(StringASCII("10 in binary : ") << StringASCII(10, 2));
		Log::displayLog(StringASCII("test:").concatFill(255, StringASCII::Size(5), '-', 16));
		Log::displayLog(StringASCII(100.0f));
		Log::displayLog(StringASCII(0.2f));
		Log::displayLog(StringASCII(0.02f));
		Log::displayLog(StringASCII(0.002f));
		Log::displayLog(StringASCII(0.0002f));
		Log::displayLog(StringASCII(0.00002f));



		for ( size_t i(0); i < 2; i++ ) {
			testStr += StringASCII(testStr);
		}
		Log::displayLog(testStr.getSubStr(StringASCII::Size(0), StringASCII::Size(30)));

		Log::displayLog(StringASCII::format("__/%__%__%__%__", "Hello World !", 50, 2.5f));

		class EndFunc {
		public:
			bool operator()(const char* it) const {
				return ( *it == char(' ') );
			}
		};

		const char* testParse = "42784.27 18";
		const char** iterable(&testParse);
		float parsedValue(StringASCII::toFloat(iterable, 10, EndFunc()));
		Log::displayLog(parsedValue);
		Log::displayLog(StringASCII::toInt(iterable));

	}
#endif
#ifdef DEBUG_TIME
	//////////////////////////////////////////////////////////////////////////
	// DEBUG : TIME															//
	{
		Time::TimePointMS tpS(Time::getTime<Time::Second>());
		Time::TimePointMS tpMS(Time::getTime<Time::MilliSecond>());
		Time::TimePoint<Time::Day> tpD(Time::getTime<Time::Day>());
		Time::Duration<Time::MilliSecond> d(tpMS - tpS);
		info(d.getValue());
		info(tpD.getValue());
		info(Time::Duration<Time::Second>(12).toValue<Time::MilliSecond>());
	}
#endif
#ifdef DEBUG_DATE
	//////////////////////////////////////////////////////////////////////////
	// DEBUG : Date															//
	{
		info("Debuging Date...");
		Time::Date nowDate = Time::getDate();
		info(nowDate.toString(StringASCII("HHH")));
		info(nowDate.toString());
		info(nowDate.toStringISO(Time::Date::ISOFormat::DateOnly));
		info(Time::Date::getLocalUTCBias());
		info(StringASCII("This is the date ! ") << Time::getDate() << " YES !");
		info(Time::Date::parse("2000-03-05T10:35:18-01:00").toStringISO());
		info(Time::Date::parse("2000-03-05").toStringISO());
		info(Time::Date::parse("T10:35:18.54547221Z").toStringISO());
		// int n = StringASCII::charToNumber<int, 4>( "2242" );
		// info( StringASCII( n ) );
	}
#endif
#ifdef DEBUG_PATH
	//////////////////////////////////////////////////////////////////////////
	// DEBUG : Path															//
	{
		info("Debuging Pathes...");
		OS::Path path("C:\\testfolder");

		info(path.exists());
		info(path.toString());

		path.join("folder2", "HelloWorld.txt");
		info(path.toString());

		info(path.basename());
	}
#endif
#ifdef DEBUG_STREAM
	//////////////////////////////////////////////////////////////////////////
	// DEBUG : Stream														//
	{
		info(StringASCII("Hello World !").concatFill(-42, 4, '0'));
		info(42);
		Stream streamTest = WString("Hello World !");
		streamTest << 'H';
		streamTest << 42;
		streamTest << L"TEST Wide.";
		StringASCII strRaw(streamTest.toStringRaw());
		info(strRaw);
		StringASCII strHexa(streamTest.toStringHexa());
		info(streamTest.toStringHexa());
	}
#endif
#ifdef DEBUG_VEC
	//////////////////////////////////////////////////////////////////////////
	// DEBUG : Vec															//
	{
		Math::Vec<double> v1({ 1,1,1,1 });
		Math::Vec<double> v2({ 3,3,3,3 });
		Math::Vec<double> v3(v1 + v2);
		Math::Vec<double> v4({ 1,2,3,4 });
		Math::Vec<double> v5(v1 + v4);
		Math::Vec<double> v6(v1 + 2.0);
		Table<double> t1(v6);

		// v6 = Math::Vec2<double>(5, 5);

		v5.sortDesc();

		v5 += v5;

		v5 = -v5;

		v5 = abs(v5);

		v5 += t1;

		info(v5.toString());

		info(Math::length(Math::normalize(v5)));

		v1 = { 2,2,2,2 };

		int i;
	}
#endif
#ifdef DEBUG_MAT
	//////////////////////////////////////////////////////////////////////////
	// DEBUG : Mat															//
	{
		Math::Mat<double> m1(Size(100), Size(100));
		Math::Mat<double> m2({ {1,2}, {3,4} });
		Math::Mat<double> m3(m2);
		Math::Mat<double> m4(m2.transpose());
		Math::Mat<double> m5({ {1,2,3}, {4,5,6} });
		Math::Mat<double> m6({ {10,11}, {20,21}, {30,31} });

		m3 = { {1,0}, {0,1} };

		m3 += 1.0;
		m3 *= 2.0;

		m3 = m3 + 100.0;
		m3 = m3 + Math::Mat<double>(2, 2).identity();
		m3 = m3 * Math::Vec<double>(2).fill(10);
		m3 *= Math::Vec<double>(2).fill(0.1);
		m3 *= Math::Mat<double>(2, 2).identity();

		m1.identity();

		info((m5 * m6).toString());
		info(m5 == m6);
	}
#endif
#ifdef DEBUG_TENSOR
	//////////////////////////////////////////////////////////////////////////
	// DEBUG : Tensor														//
	{
		Math::Tensor<double> t1({ 1,2,3,4 });
		Math::Tensor<double> t2({ {1,2}, {3,4} });
		Math::Tensor<double> t3({ {{1,0},{2,0}}, {{3,0},{4,0}} });

		Math::Tensor<double> t4(t3[ 0 ]);

		info(t3[ 0 ][ 1 ][ 0 ]);	// 2.0
		info(t4.toString());
		// info(t2[ 0 ].toString());
		info(t1.toString());
		info(t2.toString());
		info(t3.toString());
	}
#endif

#else		//DEBUG
	constexpr unsigned long long int G10(10000000000);
	constexpr unsigned long long int G1(1000000000);
	constexpr unsigned long long int M100(100000000);
	constexpr unsigned long long int M10(10000000);
	constexpr unsigned long long int M1(1000000);
	constexpr unsigned long long int K100(100000);
	constexpr unsigned long long int K10(10000);
	constexpr unsigned long long int K1(1000);

#ifdef SPEEDTEST_DRAWLINE
	{
		//////////////////////////////////////////////////////////////////////////
		// SPEED TEST : Draw Lines								//

		Graphic::ImageT<unsigned char> image(Math::Vec2<Graphic::Size>(500), Graphic::Format::R);

		Graphic::Gradient::Horizontal<Graphic::ColorRGBA<unsigned char>, Graphic::InterpolationFunc::Cubic> gradientHorizontal;
		gradientHorizontal.addPoint(0.0f, Graphic::ColorRGBA<unsigned char>(0, 0, 0, 255));
		gradientHorizontal.addPoint(1.0f, Graphic::ColorRGBA<unsigned char>(255, 255, 255, 255));
		Graphic::ColorFunc::Gradient::Horizontal<Graphic::ColorRGBA<unsigned char>, Graphic::InterpolationFunc::Cubic> colorFunctor(gradientHorizontal);



		Log::startChrono();
		for ( size_t i = 0; i < M1; i++ ) {
			//image.drawLine(Graphic::LineF(0, 20, 500, 480), Graphic::ColorR<unsigned char>(255), 5);
			image.drawLineFunctor(Graphic::LineF(0, 20, 500, 480), Graphic::ColorFunc::SimpleColor<Graphic::ColorR<unsigned char>>(Graphic::ColorR<unsigned char>(255)), 1);

			//image.drawLineFunctor(Graphic::LineF(0, 20, 500, 480), colorFunctor, 5);
		}
		Log::stopChrono();
		Log::displayChrono("DRAW LINES R -> R (Last Result: 1.581s for M1)");

		Graphic::FreeImage freeImage;
		freeImage.loadFromDatas(( unsigned char* ) image.getDatas(), image.getSize(), Graphic::FreeImage::Format::R);
		freeImage.saveToFile("drawline.png", Graphic::FreeImage::SavingFormat::PNG);
	}
#endif

#ifdef SPEEDTEST_DRAWLINE_FLOAT
	{
		//////////////////////////////////////////////////////////////////////////
		// SPEED TEST : Draw Lines								//

		Graphic::ImageT<float> image(Math::Vec2<Graphic::Size>(500), Graphic::Format::R);

		Log::startChrono();
		for ( size_t i = 0; i < M1; i++ ) {
			image.drawLineFunctor(Graphic::LineF(0, 20, 500, 480), Graphic::ColorFunc::SimpleColor<Graphic::ColorR<float>>(Graphic::ColorR<float>(1)), 1);
		}
		Log::stopChrono();
		Log::displayChrono("DRAW LINES R -> R (Last Result: 1.6s for M1)");


		Graphic::ImageT<unsigned char> imageUC(image);
		Graphic::FreeImage freeImage;
		freeImage.loadFromDatas(( unsigned char* ) imageUC.getDatas(), imageUC.getSize(), Graphic::FreeImage::Format::R);
		freeImage.saveToFile("drawline_float.png", Graphic::FreeImage::SavingFormat::PNG);
	}

#endif

#ifdef SPEEDTEST_GRAPH
	{
		//////////////////////////////////////////////////////////////////////////
		// SPEED TEST : Graph									//

		Graphic::ImageT<unsigned char> image(Math::Vec2<Graphic::Size>(500), Graphic::Format::R);


		Math::Vec2<float> vStatic[] = { Math::Vec2<float>(0.0f, 0.2f), Math::Vec2<float>(0.25f, 0.2f), Math::Vec2<float>(0.5f, 0.1f), Math::Vec2<float>(0.6f, 0.8f), Math::Vec2<float>(0.7f, 0.1f), Math::Vec2<float>(1.0f, 0.8f) };
		Vector<Math::Vec2<float>> v(vStatic);

		Log::startChrono();
		for ( size_t i = 0; i < K10; i++ ) {
			image.drawGraphValuesFunctor(v, Graphic::Rectangle(0, 0, 500, 500), Graphic::ColorFunc::SimpleColor<Graphic::ColorR<unsigned char>>(Graphic::ColorR<unsigned char>(128)));
		}
		Log::stopChrono();
		Log::displayChrono("DRAW GRAPH R -> R (Last Result: 6.0s for K100)");

		Graphic::FreeImage freeImage;
		freeImage.loadFromDatas(( unsigned char* ) image.getDatas(), image.getSize(), Graphic::FreeImage::Format::R);
		freeImage.saveToFile("graph.png", Graphic::FreeImage::SavingFormat::PNG);
	}
#endif


#ifdef SPEEDTEST_ROUNDEDRECTANGLE
	{
		//////////////////////////////////////////////////////////////////////////
		// SPEED TEST : Rounded Rectangle							//

		Graphic::ImageT<unsigned char> image(Math::Vec2<Graphic::Size>(500), Graphic::Format::R);


		Log::startChrono();
		for ( size_t i = 0; i < K10; i++ ) {
			image.drawRectangleRounded(Graphic::Rectangle(0, 0, 500, 500), 100, Graphic::ColorR<unsigned char>(255));

		}
		Log::stopChrono();
		Log::displayChrono("DRAW ROUNDED RECTANGLE R -> R (Last Result: 0.883s for K10)");

		Graphic::FreeImage freeImage;
		freeImage.loadFromDatas(( unsigned char* ) image.getDatas(), image.getSize(), Graphic::FreeImage::Format::R);
		freeImage.saveToFile("rectangleRounded.png", Graphic::FreeImage::SavingFormat::PNG);
	}
#endif

#ifdef SPEEDTEST_DISK
	{
		//////////////////////////////////////////////////////////////////////////
		// SPEED TEST : Rounded Rectangle							//

		Graphic::ImageT<unsigned char> image(Math::Vec2<Graphic::Size>(500), Graphic::Format::R);

		Graphic::ColorFunc::SimpleColor<Graphic::ColorR<unsigned char>> colorFunc(Graphic::ColorR<unsigned char>(255));


		Log::startChrono();
		for ( size_t i = 0; i < K10; i++ ) {
			image.drawRectangleRounded(Graphic::Rectangle(0, 0, 500, 500), 250, Graphic::ColorR<unsigned char>(255));

		}
		Log::stopChrono();
		Log::displayChrono("DRAW ROUNDED RECTANGLE R -> R (Last Result: 0.779s for K10)");

		Log::startChrono();
		for ( size_t i = 0; i < K10; i++ ) {
			image._drawDiskFunctor<Graphic::ColorFunc::SimpleColor<Graphic::ColorR<unsigned char>>, Graphic::BlendingFunc::Normal, Graphic::ColorR<unsigned char>>(Graphic::Point(250, 250), 250, colorFunc);

		}
		Log::stopChrono();
		Log::displayChrono("DRAW DISK RECTANGLE R -> R (Last Result: 0.778s for K10)");

		Graphic::FreeImage freeImage;
		freeImage.loadFromDatas(( unsigned char* ) image.getDatas(), image.getSize(), Graphic::FreeImage::Format::R);
		freeImage.saveToFile("rectangleRounded.png", Graphic::FreeImage::SavingFormat::PNG);
	}
#endif

#ifdef SPEEDTEST_DRAWTEXT
	{
		//////////////////////////////////////////////////////////////////////////
		// SPEED TEST : Draw Text											//
		Graphic::TrueTypeFont<unsigned char> font(L"consola.ttf", 15);
		font.load();
		font.loadGlyph(Graphic::Font<unsigned char>::Template::Ascii);

		Graphic::ImageT<unsigned char> image(Math::Vec2<Graphic::Size>(500), Graphic::Format::RGB);

		UTF8String testStr("Hello World");

		Log::startChrono();
		for ( size_t i = 0; i < M1; i++ ) {
			Graphic::drawText(&image, font, Graphic::Rectangle(0, 0, 250, 250), testStr, Graphic::ColorRGB<unsigned char>(255, 100, 200), Math::Vec2<bool>(true, true));
		}
		Log::stopChrono();
		Log::displayChrono("DRAW \"Hello World\" (Last Result: 1.629s for M1)");


		Graphic::FreeImage freeImage;
		freeImage.loadFromDatas(( unsigned char* ) image.getDatas(), image.getSize(), Graphic::FreeImage::Format::RGB);
		freeImage.saveToFile("drawText.png", Graphic::FreeImage::SavingFormat::PNG);
	}
#endif


#ifdef SPEEDTEST_RESAMPLE
	{
		//////////////////////////////////////////////////////////////////////////
		// SPEED TEST : Re sample												//

		Graphic::FreeImage freeImageIn("sanctum.png", Graphic::FreeImage::Format::RGB);
		Graphic::FreeImage freeImageOriginal("sanctum.png", Graphic::FreeImage::Format::RGB);
		freeImageIn.load();
		freeImageOriginal.load();
		Graphic::ImageT<unsigned char> imageOriginal(freeImageIn.getDatas(), freeImageIn.getSize(), Graphic::LoadingFormat::BGR, false);
		Graphic::ImageT<unsigned char> image(imageOriginal);
		Graphic::ImageT<unsigned char> image2(imageOriginal.getSize(), Graphic::Format::RGB);

		Log::startChrono();
		for ( size_t i = 0; i < K10; i++ ) {
			image2 = image.resample(Math::Vec2<Graphic::Size>(100, 400), Graphic::Image::ResamplingMode::Nearest);
			image = image2.resample(Math::Vec2<Graphic::Size>(500, 100), Graphic::Image::ResamplingMode::Nearest);

			image2 = image;
			image = image2;

		}
		Log::stopChrono();
		Log::displayChrono("RESAMPLE NEAREST RGB (Last Result: 8.1s for K10)");

		Log::startChrono();
		for ( size_t i = 0; i < K1; i++ ) {
			image2 = image.resample(Math::Vec2<Graphic::Size>(100, 400), Graphic::Image::ResamplingMode::Bilinear);
			image = image2.resample(Math::Vec2<Graphic::Size>(500, 100), Graphic::Image::ResamplingMode::Bilinear);
		}

		Log::stopChrono();
		Log::displayChrono("RESAMPLE LINEAR RGB (Last Result: 780ms for K1)");

		Log::startChrono();
		for ( size_t i = 0; i < K1; i++ ) {
			image = imageOriginal;
			image = image.resample(Math::Vec2<Graphic::Size>(200, 200), Graphic::Image::ResamplingMode::Lanczos);
			//image = image2.resample( Math::Vec2<Graphic::Size>( 500, 500 ), Graphic::Image::ResamplingMode::Linear );
		}

		Log::stopChrono();
		Log::displayChrono("RESAMPLE LANCZOS RGB (Last Result: 3450ms for K1)");

		Log::startChrono();
		for ( size_t i = 0; i < K1; i++ ) {
			freeImageIn.resize(Math::Vec2<Graphic::Size>(100, 400), Graphic::FreeImage::Filter::Bilinear);
			freeImageIn.resize(Math::Vec2<Graphic::Size>(500, 100), Graphic::FreeImage::Filter::Bilinear);

		}
		Log::stopChrono();
		Log::displayChrono("RESAMPLE FreeImage LINEAR RGB (Last Result: 1900ms for K1)");


		Graphic::FreeImage freeImageOut;
		freeImageOut.loadFromDatas(( unsigned char* ) image.getDatas(), image.getSize(), Graphic::FreeImage::Format::RGB);
		freeImageOut.saveToFile("resample.png", Graphic::FreeImage::SavingFormat::PNG);

	}
#endif


#ifdef SPEEDTEST_POLYGON
	{
		//////////////////////////////////////////////////////////////////////////
		// SPEED TEST : Polygon									//

		Graphic::ImageT<unsigned char> image(Math::Vec2<Graphic::Size>(500), Graphic::Format::R);

		Math::Vec2<float> vertices[] = { Math::Vec2<float>(0.0f, 0.2f), Math::Vec2<float>(0.2f, 0.5f), Math::Vec2<float>(0.0f, 0.8f), Math::Vec2<float>(1.0f, 0.5f) };
		Graphic::ColorFunc::SimpleColor<Graphic::ColorR<unsigned char>> colorFunc(Graphic::ColorR<unsigned char>(128));

		Log::startChrono();
		for ( size_t i = 0; i < K100; i++ ) {
			image.drawPolygonFunctor<Graphic::ColorFunc::SimpleColor<Graphic::ColorR<unsigned char>>>(vertices, 4, Graphic::Rectangle(100, 100, 400, 400), colorFunc);

		}
		Log::stopChrono();
		Log::displayChrono("DRAW POLYGON R -> R (Last Result: 1.4s for K100)");

		Graphic::FreeImage freeImage;
		freeImage.loadFromDatas(( unsigned char* ) image.getDatas(), image.getSize(), Graphic::FreeImage::Format::R);
		freeImage.saveToFile("polygon.png", Graphic::FreeImage::SavingFormat::PNG);
	}
#endif

#ifdef SPEEDTEST_FILTER
	{
		//////////////////////////////////////////////////////////////////////////
		// Filter											//
		Graphic::FreeImage freeImageIn("sanctum.png", Graphic::FreeImage::Format::RGB);
		freeImageIn.load();
		Graphic::ImageT<unsigned char> image(freeImageIn.getDatas(), Math::Vec2<Graphic::Size>(500), Graphic::LoadingFormat::BGR, false);
		Graphic::ImageT<float> imagef(image);




		Log::startChrono();
		for ( size_t i = 0; i < K1; i++ ) {
			image = image.applyGaussianBlur(5, Graphic::Image::ConvolutionMode::NormalSize, Graphic::ColorRGBA<unsigned char>(0, 0, 0, 0));
		}
		Log::stopChrono();
		Log::displayChrono("FILTER RGB UCHAR (Last Result: 9.5s for K1)");


		Log::startChrono();
		for ( size_t i = 0; i < K1; i++ ) {
			imagef = imagef.applyGaussianBlur(5, Graphic::ImageT<float>::ConvolutionMode::NormalSize, Graphic::ColorRGBA<float>(0, 0, 0, 0));
		}
		Log::stopChrono();
		Log::displayChrono("FILTER RGB FLOAT (Last Result: 15.1s for K1)");


		Graphic::FreeImage freeImageOut;
		freeImageOut.loadFromDatas(( unsigned char* ) image.getDatas(), image.getSize(), Graphic::FreeImage::Format::RGB);
		freeImageOut.saveToFile("filterUCHAR.png", Graphic::FreeImage::SavingFormat::PNG);


		image = imagef;
		freeImageOut.loadFromDatas(( unsigned char* ) image.getDatas(), image.getSize(), Graphic::FreeImage::Format::RGB);
		freeImageOut.saveToFile("filterFLOAT.png", Graphic::FreeImage::SavingFormat::PNG);
	}
#endif


#ifdef SPEEDTEST_STROKE
	{
		//////////////////////////////////////////////////////////////////////////
		// Stroke											//
		Graphic::FreeImage freeImageIn("sanctum.png", Graphic::FreeImage::Format::RGB);
		freeImageIn.load();
		Graphic::ImageT<unsigned char> image(freeImageIn.getDatas(), freeImageIn.getSize(), Graphic::LoadingFormat::RGB, false);
		image.threshold(Graphic::ColorRGBA<unsigned char>(255), Graphic::ColorRGBA<unsigned char>(0), Graphic::ColorRGBA<unsigned char>(128, 0, 0, 0));

		Log::startChrono();
		for ( size_t i = 0; i < K1; i++ ) {
			image.drawStrokeFunctor(Graphic::Point(0, 0), image, 2, Graphic::ColorFunc::SimpleColor<Graphic::ColorRGB<unsigned char>>(Graphic::ColorRGB<unsigned char>(0, 255, 0)), Graphic::Image::StrokeType::Outside);
		}
		Log::stopChrono();
		Log::displayChrono("STROKE THICKNESS 2 RGB UCHAR (Last Result: 11000ms for K1)");

		Graphic::FreeImage freeImageOut;
		freeImageOut.loadFromDatas(( unsigned char* ) image.getDatas(), image.getSize(), Graphic::FreeImage::Format::RGB);
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
		Log::displayChrono(StringASCII("LOGICAL < (Last : 5914ms) ") + sum);

		sum = 0;
		Log::startChrono();
		for ( size_t i = 0; i < G10; i++ ) {
			sum += ( i <= i + 2 ) ? 1 : 0;
		}
		Log::stopChrono();
		Log::displayChrono(StringASCII("LOGICAL <= (Last : 8281ms) ") + sum);
	}
#endif

#ifdef SPEEDTEST_ARRAYACCESS
	//////////////////////////////////////////////////////////////////////////
	// SPEED TEST : INT VS UINT Array access times.					//
	{
		int* testArray = new int[ 10000000 ];
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
		Graphic::ColorRGBA<unsigned char> colorWhite(255, 255, 255, 10);
		Graphic::ColorRGBA<unsigned char> colorRed(255, 0, 0, 10);

		Graphic::Image testBlendRGBA1(Math::Vec2<Graphic::Size>(200, 200), Graphic::Format::RGBA);
		Graphic::Image testBlendRGBA2(Math::Vec2<Graphic::Size>(200, 200), Graphic::Format::RGBA);

		testBlendRGBA1.fillImage(colorRed);
		testBlendRGBA2.fillImage(colorWhite);

		Graphic::ImageT<float> testBlendRGBAFloat1(Math::Vec2<Graphic::Size>(100, 100), Graphic::Format::RGBA);
		Graphic::ImageT<float> testBlendRGBAFloat2(Math::Vec2<Graphic::Size>(100, 100), Graphic::Format::RGBA);

		Graphic::ColorRGBA<float> colorWhiteF(1.0f, 1.0f, 1.0f, float(127) / float(255));
		Graphic::ColorRGBA<float> colorRedF(1.0f, 0.0f, 0.0f, float(127) / float(255));

		testBlendRGBAFloat1.fillImage(colorRedF);
		testBlendRGBAFloat2.fillImage(colorWhiteF);

		Graphic::Rectangle rectangle(testBlendRGBA2.getSize());

		Log::startChrono();
		for ( size_t i = 0; i < K10; i++ ) {
			testBlendRGBA2.drawImage(Graphic::Point(0, 0), testBlendRGBA1);
		}
		Log::stopChrono();
		Log::displayChrono("INT BLENDING RGBA -> RGB (last 1215ms)");


		Log::startChrono();
		for ( size_t i = 0; i < K10; i++ ) {
			testBlendRGBAFloat2.drawImage(Graphic::Point(0, 0), testBlendRGBAFloat1);
		}
		Log::stopChrono();
		Log::displayChrono("FLOAT BLENDING RGBA -> RGB (last 205ms)");

		Log::startChrono();
		for ( size_t i = 0; i < K10; i++ ) {
			testBlendRGBA2.drawImage(Graphic::Point(0, 0), rectangle, testBlendRGBA1, Graphic::BlendingFunc::Normal());
		}
		Log::stopChrono();
		Log::displayChrono("INT BLENDING FUNCTOR RGBA -> RGB (last 1200ms)");


		Log::startChrono();
		for ( size_t i = 0; i < K10; i++ ) {
			testBlendRGBAFloat2.drawImage(Graphic::Point(0, 0), rectangle, testBlendRGBAFloat1, Graphic::BlendingFunc::Normal());
		}
		Log::stopChrono();
		Log::displayChrono("FLOAT BLENDING FUNCTOR RGBA -> RGB (last 206ms)");

		Graphic::Image testblendCasted(testBlendRGBAFloat2);

		Graphic::FreeImage freeImage;
		freeImage.loadFromDatas(( unsigned char* ) testblendCasted.getDatas(), testblendCasted.getSize(), Graphic::FreeImage::Format::RGBA);
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
		for ( unsigned long int i = 0; i < M10; i++ ) {
			date = Time::Date(Time::getValue());
		}
		Log::stopChrono();
		Log::displayChrono(StringASCII() << "Date");

		Log::startChrono();
		for ( unsigned long int i = 0; i < M10; i++ ) {
			time_t now = time(NULL);
			localtime_s(&timeinfo, &now);
		}
		Log::stopChrono();
		Log::displayChrono(StringASCII() << "localtime_s");
	}
#endif
#ifdef  SPEEDTEST_DATE_PARSE
	//////////////////////////////////////////////////////////////////////////
	// SPEED TEST : Dates Parse									//
	{
		StringASCII dateStr("2020-11-11T16:17:00.00+01:00");
		std::string dateStrStd("2020-11-11T16:17:00.00+01:00");

		Time::Date date;
		tm dateStd;

		int tmpVar = 0;

		Log::startChrono();
		for ( unsigned long int i = 0; i < M10; i++ ) {
			tmpVar += Time::Date::parse(dateStr).getMinutes();
		}
		Log::stopChrono();
		Log::displayChrono(StringASCII(tmpVar));
	}
#endif //  SPEEDTEST_DATE_PARSE


#ifdef SPEEDTEST_STRING_CONCAT_STRING
	//////////////////////////////////////////////////////////////////////////
	// SPEED TEST : Concat Strings with Strings							//
	{
		StringASCII testStr1("STRING 1 : ");
		std::string testStr2("STRING 2 : ");

		StringASCII strConcat1("Hello World!");
		std::string strConcat2("Hello World!");


		Log::startChrono();
		for ( size_t i = 0; i < M100; i++ ) {
			testStr1 += strConcat1;
		}
		Log::stopChrono();
		Log::displayChrono(testStr1.getSubStr(StringASCII::Size(0), StringASCII::Size(30)));

		Log::startChrono();
		for ( size_t i = 0; i < M100; i++ ) {
			testStr2 += strConcat2;
		}
		Log::stopChrono();
		Log::displayChrono(testStr2.substr(0, 30).c_str());
	}
#endif

#ifdef SPEEDTEST_STRING_CONCAT_NUMBER
	//////////////////////////////////////////////////////////////////////////
	// SPEED TEST : Concat Strings with numbers							//
	{
		StringASCII testMyStr1("STRING 1 : ");
		StringASCII testMyStr2("STRING 1 : ");
		std::string testStdStr1("STRING 2 : ");

		int numberInt = Math::random();
		double numberFloat = 0.123456789123456789;

		Log::startChrono();
		for ( size_t i = 0; i < M10; i++ ) {
			testMyStr1.concat(numberFloat, 7, 2);
		}
		Log::stopChrono();
		Log::displayChrono(StringASCII("Simple++ concat float.") << testMyStr1.getSubStr(StringASCII::Size(0), StringASCII::Size(30)));

		Log::startChrono();
		for ( size_t i = 0; i < M10; i++ ) {
			testMyStr2.concat(numberInt, 2);
		}
		Log::stopChrono();
		Log::displayChrono(StringASCII("Simple++ concat int.") << testMyStr2.getSubStr(StringASCII::Size(0), StringASCII::Size(30)));

		Log::startChrono();
		for ( size_t i = 0; i < M10; i++ ) {
			testStdStr1 += std::to_string(numberFloat);
		}
		Log::stopChrono();
		Log::displayChrono(( std::string("std concat float.") + testStdStr1.substr(0, 30).c_str() ).data());
	}
#endif

#ifdef SPEEDTEST_STRING_FORMAT
	//////////////////////////////////////////////////////////////////////////
	// SPEED TEST : Concat Strings							//
	{
		StringASCII testStr("STRING 1 : (%)");
		StringASCII strConcat("STR %");

		Log::startChrono();
		for ( size_t i = 0; i < K100; i++ ) {
			testStr = StringASCII::format(testStr, strConcat);
		}
		Log::stopChrono();
		Log::displayChrono(testStr.getSubStr(StringASCII::Size(0), StringASCII::Size(30)));
	}
#endif



#ifdef SPEEDTEST_STRING_CAST
	//////////////////////////////////////////////////////////////////////////
	// SPEED TEST : Cast Strings								//
	{
		float sum = 0.0f;
		Log::startChrono();
		for ( unsigned long int i = 0; i < 10000000; i++ ) {
			sum += atof("42.054217");
		}
		Log::stopChrono();
		Log::displayChrono("ATOF : " + StringASCII(sum));

		sum = 0.0f;
		Log::startChrono();
		for ( unsigned long int i = 0; i < 10000000; i++ ) {
			sum += StringASCII::toFloat("42.054217");
		}
		Log::stopChrono();
		Log::displayChrono("toFloat : " + StringASCII(sum));
	}
#endif

#ifdef SPEEDTEST_REGEX
	//////////////////////////////////////////////////////////////////////////
	// SPEED TEST : Regex									//
	{
		for ( unsigned int i = 0; i < 260; i++ ) {
			info(StringASCII(i) + " : " + Regex::match(i, "^2([0-4][0-9]|5[0-5])|1[0-9][0-9]?|[0-9]$"));
		}
		for ( unsigned int i = 0; i < 260; i++ ) {
			info(StringASCII(i) + " : " + Regex::match(i, "^2([0-4][0-9]?|5[0-5]?|[6-9])?|([3-9]|1)[0-9]?[0-9]?|0$"));
		}

		std::string stdString = "________255";

		bool stdResult = true;

		std::string txt_regex("2([0-4][0-9]|5[0-5])|1[0-9][0-9]?|[0-9]$");
		std::regex stdRegex(txt_regex, std::regex_constants::optimize);
		Log::startChrono();
		for ( unsigned long int i = 0; i < M1; i++ ) {
			stdResult &= std::regex_search(stdString, stdRegex);
		}
		Log::stopChrono();
		Log::displayChrono("Regex .regex_match(); STD : " + StringASCII(stdResult));


		bool mineResult = true;
		StringASCII mineRegex = "2([0-4][0-9]|5[0-5])|1[0-9][0-9]?|[0-9]$";
		StringASCII mineString = "________255";

		Log::startChrono();
		for ( unsigned long int i = 0; i < M1; i++ ) {
			mineResult &= Regex::match(mineString, mineRegex);
		}
		Log::stopChrono();
		Log::displayChrono("Vector .regex_match(); Mine : " + StringASCII(mineResult));
	}
#endif

#ifdef SPEEDTEST_VECTOR
	//////////////////////////////////////////////////////////////////////////
	// SPEED TEST : Vectors									//
	{
		Vector<unsigned long int> vectorMine;
		std::vector<unsigned long int> vectorSTD;

		Log::startChrono();
		for ( unsigned long int i = 0; i < 10000000; i++ ) {
			vectorMine.push(i);
		}
		Log::stopChrono();
		Log::displayChrono("Vector .push_back(); Mine");

		Log::startChrono();
		for ( unsigned long int i = 0; i < 10000000; i++ ) {
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
		{
			Map<unsigned long int, unsigned long int> mapRedBlackTree;
			std::map<unsigned long int, unsigned long int> mapSTD;

			Log::startChrono();
			for ( unsigned long int i = 0; i < M1; i++ ) {
				mapSTD.insert(std::pair<unsigned long int, unsigned long int>(Math::random(0, 1000000), i));
			}
			Log::stopChrono();
			Log::displayChrono("Map .insert(); STD");


			Log::startChrono();
			for ( unsigned long int i = 0; i < M1; i++ ) {
				mapRedBlackTree.insert(Math::random(0, 1000000), i);
			}
			Log::stopChrono();
			Log::displayChrono(StringASCII("Map Red Black Tree .insert(); Mine "));
		}
		{
			Map<unsigned long int, unsigned long int> mapRedBlackTree;
			std::map<unsigned long int, unsigned long int> mapSTD;

			for ( unsigned long int i = 0; i < M1; i++ ) {
				mapSTD.insert(std::pair<unsigned long int, unsigned long int>(i, i));
				mapRedBlackTree.insert(i, i);
			}
			volatile unsigned long int tmp(0);
			Log::startChrono();
			for ( unsigned long int i = 0; i < M1; i++ ) {
				tmp += mapSTD[ i ];
			}
			Log::stopChrono();
			Log::displayChrono("Map .operator[] STD");


			Log::startChrono();
			for ( unsigned long int i = 0; i < M1; i++ ) {
				tmp += *( mapRedBlackTree[ i ] );
			}
			Log::stopChrono();
			Log::displayChrono(StringASCII("Map Red Black Tree .operator[] Mine "));

		}


	}
#endif
#ifdef SPEEDTEST_ARITHMETIC 
	//////////////////////////////////////////////////////////////////////////
	// SPEED TEST : Arithmetic												//
	{

		volatile float f0(1);
		Log::startChrono();
		for ( unsigned long int i = 0; i < M100; i++ ) {
			f0 += f0;
		}
		Log::stopChrono();
		Log::displayChrono(StringASCII("Float ADD ( Last 284ms ) : ") << f0);

		volatile float f1(1);
		Log::startChrono();
		for ( unsigned long int i = 0; i < M100; i++ ) {
			f1 *= f1;
		}
		Log::stopChrono();
		Log::displayChrono(StringASCII("Float MULT ( Last 331ms ) : ") << f1);

		volatile int i0(1);
		Log::startChrono();
		for ( unsigned long int i = 0; i < M100; i++ ) {
			i0 += i0;
		}
		Log::stopChrono();
		Log::displayChrono(StringASCII("Float ADD ( Last 284ms ) : ") << StringASCII(int(i0)));

		volatile int i1(1);
		Log::startChrono();
		for ( unsigned long int i = 0; i < M100; i++ ) {
			i1 *= i1;
		}
		Log::stopChrono();
		Log::displayChrono(StringASCII("Float MULT ( Last 331ms ) : ") << StringASCII(int(i1)));



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
			for ( unsigned long int i = 0; i < G1; i++ ) {
				i1 += ( c1 );
				i2 += ( c2 );
				i3 += ( c3 );

				c1 += ( i1 );
				c2 += ( i2 );
				c3 += ( i3 );
			}
			Log::stopChrono();
			Log::displayChrono(StringASCII("EXPLICIT CAST (Last Result : ???)") << c1.v << c2.v1 << c3.v);
		}

		{
			testImplicitCast<int> i1, i2, i3;
			testImplicitCast<unsigned char> c1, c2, c3;

			Log::startChrono();
			for ( unsigned long int i = 0; i < G1; i++ ) {
				i1 += ( c1 );
				i2 += ( c2 );
				i3 += ( c3 );

				c1 += ( i1 );
				c2 += ( i2 );
				c3 += ( i3 );
			}
			Log::stopChrono();
			Log::displayChrono(StringASCII("IMPLICIT CAST (Last Result : ???)") << c1.v << c2.v1 << c3.v);
		}

	}
#endif
#if defined SPEEDTEST_PATH
	{
		OS::Path path("C:\\Users\\Clement\\VirtualBox VMs\\Debian64\\Debian64.vbox");
		StringASCII pathStrASCII("C:\\Users\\Clement\\VirtualBox VMs\\Debian64\\Debian64.vbox");
		WString pathStringW("C:\\Users\\Clement\\VirtualBox VMs\\Debian64\\Debian64.vbox");
		std::string pathStrStdASCII("C:\\Users\\Clement\\VirtualBox VMs\\Debian64\\Debian64.vbox");
		std::wstring pathStrStdW(L"C:\\Users\\Clement\\VirtualBox VMs\\Debian64\\Debian64.vbox");

		std::error_code ec;

		int tmp;
		struct _stat64 s;

		Log::startChrono();
		for ( unsigned long int i(0); i < K100; i++ ) {
			// tmp += ( int ) OS::Path::exists( pathStrASCII );
			tmp += ( int ) ( _wstat64(pathStringW.toCString(), &s) == 0 );
		}
		Log::stopChrono();
		Log::displayChrono(String::format("My Path.exists() : %", tmp));

		Log::startChrono();
		for ( unsigned long int i(0); i < K100; i++ ) {
			tmp += ( int ) std::filesystem::exists(pathStrStdASCII.c_str(), ec);
		}
		Log::stopChrono();
		Log::displayChrono(String::format("Std Path.exists(ASCII) : %", tmp));

		Log::startChrono();
		for ( unsigned long int i(0); i < K100; i++ ) {
			tmp += ( int ) std::filesystem::exists(pathStrStdW.c_str());
			/*
			__std_fs_stats _Stats;

			const auto _Error = __std_fs_get_stats( pathStrStdW.c_str(), &_Stats, __std_fs_stats_flags::_Attributes | __std_fs_stats_flags::_Follow_symlinks );

			tmp += ( int ) ( _Stats._Attributes != __std_fs_file_attr::_Invalid );
			*/
		}
		Log::stopChrono();
		Log::displayChrono(String::format("Std Path.exists(WString) : %", tmp));
	}
#endif
#ifdef SPEEDTEST_BASE64
	{
		Vector<unsigned int> dataVector;
		dataVector.resize(32000000);

		Log::startChrono();
		StringASCII outputStr(StringASCII::encodeBase64(dataVector));
		Log::stopChrono();
		Log::displayChrono(String::format("Base64 encoding : %", outputStr.getSubStr(Size(0), Size(10))));
	}
#endif



#endif	//DEBUG
	return 0;
}

#endif
