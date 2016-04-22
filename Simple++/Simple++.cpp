// Simple++.cpp : Defines the entry point for the console application.
//

//Main only exists if we are in debug (.exe) and not in release (.lib)
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




class A {
public:
	A(){}

private:
	int a;
	
	
};



class B : public A {
public:
	B(){}

private:
	int b[2];
};



template<typename T>
class ImageFunctor {
public:
	ImageFunctor() {};
	ImageFunctor & operator()(const Math::Vec2<unsigned int> & p, Graphic::ColorR<T> & color) { return *this; }
	ImageFunctor & operator()(const Math::Vec2<unsigned int> & p, Graphic::ColorRGB<T> & color) {

		unsigned int len = Math::length(p);

		color.r += len;
		color.g -= len;
		color.b += color.r + color.g;

		
		return *this; }
	ImageFunctor & operator()(const Math::Vec2<unsigned int> & p, Graphic::ColorRGBA<T> & color) { return *this; }

};







int main(int argc, char * argv[]){
	const unsigned long long G1 =		1000000000;
	const unsigned long long M100 =	100000000;
	const unsigned long long M10 =	10000000;
	const unsigned long long M1 =		1000000;
	const unsigned long long K100 =	100000;
	const unsigned long long K10 =	10000;
	const unsigned long long K1 =		1000;


	Application<char> app(argc, argv);


	Graphic::FontLoadable fontTest(L"consola.ttf", 15);
	fontTest.load();
	fontTest.loadGlyph(Graphic::Font::Template::Ascii);
	fontTest.writeToFile(L"myFont.cfont");

	Graphic::FontLoadable fontTest2(L"myFont.cfont");
	fontTest2.load();



	fontTest.writeToFile(L"myFont2.cfont");

	FreeImage glyphFreeImage;
	glyphFreeImage.loadFromDatas((unsigned char *) fontTest2['A'] -> getDatas(), fontTest2['A'] -> getSize(), FreeImage::Format::R);
	glyphFreeImage.saveToFile("glyphTest.png", FreeImage::SavingFormat::PNG);


	FreeImage image("sanctum.png", FreeImage::Format::RGB);
	image.load();

	
	Graphic::TextureLoadable<unsigned char> imageTest;
	imageTest.setDatas((unsigned char * ) image.getDatas(), image.getSize(), Graphic::LoadingFormat::BGR);
	imageTest.generateMipmaps();
	imageTest.writeToFile("myImageTest.cimage");
	
	Graphic::TextureLoadable<unsigned char> imageTest2(WString("myImageTest.cimage"));
	imageTest2.load();
	imageTest2.writeToFile("myImageTest2.cimage");




	/************************************************************************/
	/* DOING SOME TEST IN imageTest2                                        */
	/************************************************************************/

	Graphic::ColorRGBA<unsigned char> colorWhite(255,255,255,100);
	Graphic::ColorRGBA<unsigned char> colorRed(255, 0, 0, 255); 
	Graphic::ColorRGB<unsigned char> colorMagenta(255, 0, 150);
	Graphic::ColorRGBA<unsigned char> colorBlack(0, 0, 0, 150);
	Graphic::ColorRGBA<unsigned char> colorTransluscient(0, 0, 0, 0);


	//imageTest2[1] -> fill((const unsigned char *) &myColor);
	//imageTest2[1] -> drawText(fontTest, Graphic::Point(100,100), "Hello World");

	//imageTest2[1] -> fill((const unsigned char *) &myColor);



	Graphic::GradientVertical<Graphic::ColorRGBA<unsigned char>, Graphic::InterpolationFunc::Cubic> gradient;
	gradient.addPoint(0.0f, Graphic::ColorRGBA<unsigned char>(0,0,0,255));
	gradient.addPoint(0.2f, Graphic::ColorRGBA<unsigned char>(255, 0, 0, 255));
	gradient.addPoint(0.4f, Graphic::ColorRGBA<unsigned char>(0, 255, 0, 255));
	gradient.addPoint(0.6f, Graphic::ColorRGBA<unsigned char>(0, 0, 0, 0));
	gradient.addPoint(0.8f, Graphic::ColorRGBA<unsigned char>(0, 255, 255, 255));
	gradient.addPoint(1.0f, Graphic::ColorRGBA<unsigned char>(0,255,255,255));



	UTF8String testStr("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Proin finibus eu risus vitae feugiat.  ");


	Graphic::Image testBlendRGBA(Math::vec2ui(200, 200), Graphic::Format::RGBA);
	Graphic::Image testBlendRGB(Math::vec2ui(200, 200), Graphic::Format::RGB);

	testBlendRGBA.fillImage(colorWhite);
	testBlendRGB.fillImage(colorWhite);


	constexpr size_t KERNELRADIUS = 10;
	unsigned int mySuperKernel10[KERNELRADIUS * 2 + 1];
	unsigned int filterWeight = Graphic::computeGaussianKernel(mySuperKernel10);

	unsigned int testDR[1];

	log(String() << Vector<unsigned int>(mySuperKernel10));
	log(String("Weight : ") << filterWeight);
	Graphic::_Image<float> imageFloated(*imageTest2[0]);


	//switch to luminance
	Graphic::Image imageBlurred = *(imageTest2[0]);

	//imageBlurred.fill(colorRed);
	//*( imageTest2[0] ) = imageBlurred.applyFilter(mySuperKernel, Graphic::Image::ConvolutionMode::ExtendedSize, Graphic::ColorRGBA<unsigned char>(0, 0, 0, 0));

	//apply functor

	
	std::numeric_limits<float>::min();
	log(Utility::TypesInfos<int>::getMin() + 1);

	*( imageTest2[0] ) = imageBlurred.applyFilter(mySuperKernel10, Graphic::Image::ConvolutionMode::NormalSize, Graphic::ColorRGBA<unsigned char>(0, 0, 0, 0));
	//*( imageTest2[0] ) = imageBlurred;


	imageTest2[0] -> setPixels(ImageFunctor<unsigned char>());
	unsigned int mySuperKernel2[5];
	unsigned int filterWeight2 = Graphic::computeGaussianKernel(mySuperKernel2);

	*( imageTest2[0] ) = imageTest2[0] -> applyFilter(mySuperKernel2, Graphic::Image::ConvolutionMode::NormalSize, Graphic::ColorRGBA<unsigned char>(0, 0, 0, 0));


	auto maskTest = fontTest['A'];
	imageTest2[0] -> drawImage(Graphic::Point(300,300), colorRed, Graphic::Rectangle(maskTest ->getSize()), *maskTest);
	imageTest2[0] -> drawRectangle(Graphic::Rectangle(0, 0, 250, 250), Graphic::ColorRGBA<unsigned char>(0, 255, 255, 100));

	Graphic::drawText(imageTest2[0], fontTest, Graphic::Point(250, 250), testStr, colorBlack, Math::Vec2<bool>(true, true));

	imageTest2[0] -> drawRectangle(Graphic::Rectangle(0, 0, 500, 500), gradient);

	//Graphic::Image textImage(Math::vec2ui(textRectangle.getRight() - textRectangle.getLeft(), textRectangle.getTop() - textRectangle.getBottom()), Graphic::Format::RGBA);
	//textImage.fill(colorWhite);

	//imageTest2[0] -> drawImage(Graphic::Point(250 + textRectangle.getLeft(), 250 + textRectangle.getBottom()), textImage);


	imageTest2.generateMipmaps();

	for ( size_t i = 1; i < imageTest2.getNumMipmaps(); i++ ) {
		//imageTest2[0] -> drawImage(Graphic::Point(0, 0), *imageTest2[i]);
	}


	FreeImage freeImage2;
	freeImage2.loadFromDatas((unsigned char *) imageTest2.getDatas(0), imageTest2.getSize(0), FreeImage::Format::RGB);
	freeImage2.saveToFile("ultimateTest2.png", FreeImage::SavingFormat::PNG);


	Graphic::_Image<float> testBlendRGBAFloat(Math::vec2ui(100, 100), Graphic::Format::RGBA);
	Graphic::_Image<float> testBlendRGBFloat(Math::vec2ui(100, 100), Graphic::Format::RGB);


	Math::vec4f colorWhiteF(1.0, 1.0, 1.0, 1.0);
	Math::vec4f colorRedF(1.0, 0.0, 0.0, 0.0001);

	testBlendRGBAFloat.fillImage((const float *) &colorRedF);
	testBlendRGBFloat.fillImage((const float *) &colorWhiteF);

	
	return 0;

	Log::startChrono();
	for ( size_t i = 0; i < 10000; i++ ) {
		testBlendRGB.drawImage(Graphic::Point(0, 0), Graphic::Rectangle(0, testBlendRGB.getSize()), testBlendRGBA);
	}
	Log::getChrono("INT BLENDING RGBA -> RGB (last 2288ms)");


	Log::startChrono();
	for ( size_t i = 0; i < 10000; i++ ) {
		testBlendRGBFloat.drawImage(Graphic::Point(0, 0), Graphic::Rectangle(0, testBlendRGB.getSize()), testBlendRGBAFloat);
	}
	Log::getChrono("FLOAT BLENDING RGBA -> RGB (last 205ms)");

	Log::startChrono();
	for ( size_t i = 0; i < 10000; i++ ) {
		testBlendRGB.drawImage(Graphic::Point(0, 0), Graphic::Rectangle(0, testBlendRGB.getSize()), testBlendRGBA, Graphic::BlendingFunc::Normal());
	}
	Log::getChrono("INT BLENDING FUNCTOR RGBA -> RGB (last 2337ms)");


	Log::startChrono();
	for ( size_t i = 0; i < 10000; i++ ) {
		testBlendRGBFloat.drawImage(Graphic::Point(0, 0), Graphic::Rectangle(0, testBlendRGB.getSize()), testBlendRGBAFloat, Graphic::BlendingFunc::Normal());
	}
	Log::getChrono("FLOAT BLENDING FUNCTOR RGBA -> RGB (last 206ms)");




	Graphic::Image testblendCasted(testBlendRGBFloat);

	FreeImage freeImage3;
	freeImage2.loadFromDatas((unsigned char *) testblendCasted.getDatas(), testblendCasted.getSize(), FreeImage::Format::RGB);
	freeImage2.saveToFile("testBlend2.png", FreeImage::SavingFormat::PNG);


	
	/*Application<char> a(argc, argv);



	log(String::format("hello % %", 15, 20));

	

	std::fstream testFile;
	testFile.open("test.txt", std::ios::out);

	Vector<A> testFileVector;
	testFileVector.resize(10);
	testFileVector.write(&testFile);




	String dateStr = Time::getDate().toString<char>();
	log(dateStr);

	
	using shakes = std::chrono::duration<int, std::ratio<1, 100000000>>;

	auto r = Math::Ratio<1000, 10>();

	Time::Duration<Math::Ratio<10, 1000>> d1(500);
	Time::Duration<Math::Ratio<2, 4>> d2(d1);

	auto c1 = Time::getClock();

	Time::sleep(10);

	auto d3 = d1 + d2;

	log(Time::Duration<Time::MilliSecond>(Time::getClock() - c1).getValue());

	//Vector<int> testVectorInt({ 42,56 });




	OrderedMap<Math::Vec3<size_t>, CoordinateChunk<float, size_t, 1000> *> chunkMap;
	Log::startChrono();
	for ( unsigned long i = 0; i < K1; i++ ) {
		chunkMap.insert(Math::Vec3<size_t>(Math::random(), Math::random(), Math::random()), new CoordinateChunk<float, size_t, 1000>(i));
	}
	Log::getChrono(String() << "CHUNK INSERT MAP");
	*/

	/*CoordinateChunk<float, size_t, 1000> * zeroChunk = new CoordinateChunk<float, size_t, 1000>(0);
	Log::startChrono();
	for ( unsigned long i = 0; i < 15000; i++ ) {
		zeroChunk -> insertChunk(Math::Vec3<size_t>(Math::random(), Math::random(), Math::random()));
	}
	Log::getChrono(String() << "CHUNK INSERT");
	*/


	/************************************************************************/
	/* TESTING DATE		                                                */
	/************************************************************************/
	/*
	struct tm timeinfo;
	Time::Date date;
	Log::startChrono();
	for ( unsigned long i = 0; i < M1$0; i++ ) {
		date = Time::Date(Time::getTime());
	}
	Log::getChrono(String() << "Date");

	Log::startChrono();
	for ( unsigned long i = 0; i < M10; i++ ) {
		time_t now = time(NULL);
		localtime_s(&timeinfo, &now);
	}
	Log::getChrono(String() << "localtime_s");
	*/

	/************************************************************************/
	/* TESTING STRING STREAM                                                */
	/************************************************************************/
	/*String testStr("STRING STREAM : ");
	std::string testStr2("STRING : ");

	String strConcat("Hello World!");
	std::string strConcat2("Hello World!");


	Log::startChrono();
	for (unsigned long i = 0; i < 10000000; i++) {
		testStr += String("Hello World!");
	}
	Log::getChrono(testStr.getSubStr(0, 30));

	Log::startChrono();
	for (unsigned long i = 0; i < 10000000; i++) {
		testStr2 += std::string("Hello World!");
	}
	Log::getChrono(testStr2.substr(0,30));*/



	/************************************************************************/
	/* TESTING CONVERTION STRING -> NUMBER                                  */
	/************************************************************************/
	/*float sum = 0;
	Log::startChrono();
	for (unsigned long i = 0; i < 10000000; i++) {
		sum += atof("42.054217");
	}
	Log::getChrono("ATOF : " + String(sum)); 

	Log::startChrono();
	for (unsigned long i = 0; i < 10000000; i++) {
		sum += String::toFloat("42.054217");
	}
	Log::getChrono("toFloat : " + String(sum));*/
/*




	/************************************************************************/
	/* TESTING REGEX EXACTITUDE                                             */
	/************************************************************************/
	/*
	//log(preg_match("259", "^2([0-4][0-9]|5[0-5])|1[0-9][0-9]?|[0-9]$"));

	//return 0;
	for (unsigned int i = 0; i < 260; i++) {
		log(String(i) + " : " + preg_match(i, "^2([0-4][0-9]|5[0-5])|1[0-9][0-9]?|[0-9]$"));
	}
	//log(preg_match("257", "2([0-4][0-9]?|5[0-5]?|[6-9])?|([3-9]|1)[0-9]?[0-9]?|0"));
	//return 0;
	for (unsigned int i = 0; i < 260; i++) {
		log(String(i) + " : " + preg_match(i, "^2([0-4][0-9]?|5[0-5]?|[6-9])?|([3-9]|1)[0-9]?[0-9]?|0$"));
	}
	//log(preg_match("256", "2([0-4][0-9]?|5[0-5]?|[6-9])?|[1-9][0-9]?[0-9]?|0"));
	log(String(std::regex_match("ab", std::regex("(a|ab)+"))));
	//log(preg_match("foo.txt", "[a-z]+\\.txt"));

	
	/************************************************************************/
	/* TESTING REGEX MATCH                                                  */
	/************************************************************************/
	/*
	//std::string stdString =  "256" ;
	std::string stdString = "________255";

	bool stdResult = true;

	//std::string txt_regex("^2([0-4][0-9]|5[0-5])|1[0-9][0-9]?|[0-9]$");
	std::string txt_regex("2([0-4][0-9]|5[0-5])|1[0-9][0-9]?|[0-9]$");
	std::regex stdRegex(txt_regex, std::regex_constants::optimize );
	Log::startChrono();
	for (unsigned long i = 0; i < 1000000; i++) {
		stdResult &= std::regex_search(stdString, stdRegex);
	}
	Log::getChrono("Regex .regex_match(); STD : " + String(stdResult));


	bool mineResult = true;
	//String mineRegex = "^2([0-4][0-9]|5[0-5])|1[0-9][0-9]?|[0-9]$";
	String mineRegex = "2([0-4][0-9]|5[0-5])|1[0-9][0-9]?|[0-9]$";
	//String mineString = "256";
	String mineString = "________255";

	Log::startChrono();
	for (unsigned long i = 0; i < 1000000; i++) {
		mineResult &= preg_match(mineString, mineRegex);
	}
	Log::getChrono("Vector .regex_match(); Mine : " + String(mineResult));



	
	*/
	/************************************************************************/
	/* TESTING VECTORS SPEED                                                */
	/************************************************************************/
	
	/*Vector<unsigned long> vectorMine;
	std::vector<unsigned long> vectorSTD;

	Log::startChrono();
	for (unsigned long i = 0; i < 10000000; i++){
		vectorMine.push(i);
	}
	Log::getChrono("Vector .push_back(); Mine");

	Log::startChrono();
	for (unsigned long i = 0; i < 10000000; i++){
		vectorSTD.push_back(i);
	}
	Log::getChrono("Vector .push_back(); STD");*/

	
	/************************************************************************/
	/* TESTING MAPS SPEED													*/
	/************************************************************************/

	/*OrderedMap<unsigned long, unsigned long> mapMine;
	std::map<unsigned long, unsigned long> mapSTD;

	Log::startChrono();
	for (unsigned long i = 0; i < M1; i++){
		mapSTD.insert(std::pair<unsigned long, unsigned long>(Math::random(0, 100000), i));
	}
	Log::getChrono("Map .insert(); STD");

	Log::startChrono();
	for (unsigned long i = 0; i < M1; i++){
		mapMine.insertFast(Math::random(0, 100000), i);
	}
	unsigned long _4572 = mapMine[10];
	Log::getChrono(String("Map .insert(); Mine ") + _4572);
	for ( auto it = mapMine.getBegin(); it != mapMine.getEnd(); it++ ) {
		Log::displayLog(String(it -> getIndex()) + " : " + it -> getValue());
	}*/






	/************************************************************************/
	/* TESTING STRINGS                                                      */
	/************************************************************************/
/*
	UTF8String utf8String;
	utf8String = 50.2f;

	std::cout << utf8String << std::endl;
	std::cout << String("test concat ") + 'L' << std::endl;

	std::cout << String(UTF8String("MDR")) << std::endl;
	//log(String("HELLO WORLD").getSubStr(6, 5));

	std::cout << String("http://www.amazon.fr/product-reviews/B005FEGYCO/ref.php").getFileName() << std::endl;

	String testHello("Hello World");
	testHello += 'X';
	testHello.replace("Hello", "___XX___");


	std::cout << testHello << std::endl;

	std::cout << String("HELLO WORLD").split(' ') << std::endl;


	String test8;
	//test8.allocate(1000000);
	String testLOL("LOL");
	std::string testLOLSTD("LOL");

	std::string test8std;

	int i = 50;
	std::cout << String::toString(i, 16) << std::endl;
	std::cout << String('c') + 50 + "mdr" + L"MDR" << std::endl;

	Log::startChrono();
	for (unsigned int i = 0; i < 10000000; i++){
		test8 += testLOL;
	}
	Log::getChrono("MINE");


	Log::startChrono();
	for (unsigned int i = 0; i < 10000000; i++){
		test8std += testLOLSTD;
	}
	Log::getChrono("STD");*/

	

	/************************************************************************/
	/* TESTING NETWORK API                                                  */
	/************************************************************************/
/*

	int result;
	std::cout << "0 : Client, 1 : Server, Google Test : 2" << std::endl;
	scanf_s("%d", &result);

	char testData[50] = "Hello World";
	char testData2[50] = "";

	if (result == 0){
		/////CLIENT
		Network::Server myUDPServer;
		myUDPServer.listen(5001, Network::SockType::UDP, Network::IpFamily::Undefined);

		Network::Connection myTCPConnection;
		myTCPConnection.connect("::1", 5001, Network::SockType::TCP);

		Network::Address addressFrom;
		if (myUDPServer.receive(testData2, sizeof(testData2), &addressFrom))
			Log::displayLog(String() << "We got an UDP message from the server " << testData2);

	} else if (result == 1) {
		//SERVER
		Network::Server myTCPServer;
		myTCPServer.listen(5001, Network::SockType::TCP, Network::IpFamily::Undefined);
		myTCPServer.listen(5002, Network::SockType::TCP, Network::IpFamily::Undefined);

		Network::Connection clientConnection;
		while (myTCPServer.accept(&clientConnection)){
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

	*/
	return 0;
}

#endif
