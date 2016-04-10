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



int main(int argc, char * argv[]){
	const unsigned long long G1 =		1000000000;
	const unsigned long long M100 =	100000000;
	const unsigned long long M10 =	10000000;
	const unsigned long long M1 =		1000000;
	const unsigned long long K100 =	100000;
	const unsigned long long K10 =	10000;
	const unsigned long long K1 =		1000;





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
	imageTest.setDatas((unsigned char * ) image.getDatas(), image.getSize(), Graphic::Format::RGB);
	imageTest.generateMipmaps();
	imageTest.writeToFile("myImageTest.cimage");
	
	Graphic::TextureLoadable<unsigned char> imageTest2(WString("myImageTest.cimage"));
	imageTest2.load();
	imageTest2.writeToFile("myImageTest2.cimage");




	/************************************************************************/
	/* DOING SOME TEST IN imageTest2                                        */
	/************************************************************************/

	Graphic::ColorRGBA<unsigned char> colorWhite(255,255,255,100);
	Graphic::ColorRGBA<unsigned char> colorRed(255, 0, 0, 100); 
	Graphic::ColorRGB<unsigned char> colorMagenta(255, 0, 150);
	Graphic::ColorRGBA<unsigned char> colorBlack(0, 0, 0, 150);


	//imageTest2[1] -> fill((const unsigned char *) &myColor);
	//imageTest2[1] -> drawText(fontTest, Graphic::Point(100,100), "Hello World");

	//imageTest2[1] -> fill((const unsigned char *) &myColor);





	UTF8String testStr("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Proin finibus eu risus vitae feugiat.  ");


	Graphic::Image testBlend(Math::vec2ui(200, 200), Graphic::Format::RGBA);
	Graphic::Image testBlend2(Math::vec2ui(100, 100), Graphic::Format::RGB);

	testBlend.fill(colorWhite);
	testBlend2.fill(colorWhite);
	//testBlend.drawImage(Graphic::Point(50, 50), testBlend2);
	//imageTest2[0] -> drawImage(Graphic::Point(-50, 250), *imageTest2[1]);

	



	//0.035822	0.05879	0.086425	0.113806	0.13424	0.141836	0.13424	0.113806	0.086425	0.05879	0.035822

	float gaussianKernel[] = { 0.011254,	0.016436,	0.023066,	0.031105,	0.040306,	0.050187,	0.060049,	0.069041,	0.076276,	0.080977,	0.082607,	0.080977,	0.076276,	0.069041,	0.060049,	0.050187,	0.040306,	0.031105,	0.023066,	0.016436,	0.011254 };

	unsigned int filterWeight = unsigned int(-1) / ( 21 * 256);
	unsigned int filter[21];

	Graphic::_Image<float> imageFloated(*imageTest2[0]);

	for ( size_t i = 0; i < 21; i++ ) {
		filter[i] = gaussianKernel[i] * float(filterWeight);
	}
	Graphic::_Image<float> imageBlurred = imageFloated.applyFilter(gaussianKernel, Graphic::ImageF::ConvolutionMode::ExtendedSize, Graphic::ColorRGBA<float>(0,0,0,0));
	*( imageTest2[0] ) = imageBlurred;



	Graphic::drawText(imageTest2[0], fontTest, Graphic::Point(250, 250), testStr, colorBlack, Math::Vec2<bool>(true, true));

	//Graphic::Image textImage(Math::vec2ui(textRectangle.getRight() - textRectangle.getLeft(), textRectangle.getTop() - textRectangle.getBottom()), Graphic::Format::RGBA);
	//textImage.fill(colorWhite);

	//imageTest2[0] -> drawImage(Graphic::Point(250 + textRectangle.getLeft(), 250 + textRectangle.getBottom()), textImage);


	imageTest2.generateMipmaps();

	for ( size_t i = 1; i < imageTest2.getNumMipmaps(); i++ ) {
		//imageTest2[0] -> drawImage(Graphic::Point(0, 0), *imageTest2[i]);
	}


	FreeImage freeImage2;
	freeImage2.loadFromDatas((unsigned char *) imageTest2.getDatas(0), imageTest2.getSize(0), FreeImage::Format::RGBA);
	freeImage2.saveToFile("ultimateTest2.png", FreeImage::SavingFormat::PNG);


	Graphic::_Image<float> testBlend1Float(Math::vec2ui(100, 100), Graphic::Format::RGBA);
	Graphic::_Image<float> testBlend2Float(Math::vec2ui(100, 100), Graphic::Format::RGB);


	Math::vec4f colorWhiteF(1.0, 1.0, 1.0, 1.0);
	Math::vec4f colorRedF(1.0, 0.0, 0.0, 1.0/255.0);

	testBlend1Float.fill((const float *) &colorRedF);
	testBlend2Float.fill((const float *) &colorWhiteF);

	

	Log::startChrono();
	for ( size_t i = 0; i < 1; i++ ) {
		testBlend2.drawImage(Graphic::Point(0, 0), testBlend);
	}
	Log::getChrono("INT BLENDING");


	Log::startChrono();
	for ( size_t i = 0; i < 1; i++ ) {
		testBlend2Float.drawImage(Graphic::Point(0, 0), testBlend1Float);
	}
	Log::getChrono("FLOAT BLENDING");


	Graphic::Image testblendCasted(testBlend2Float);

	FreeImage freeImage3;
	freeImage2.loadFromDatas((unsigned char *) testblendCasted.getDatas(), testblendCasted.getSize(), FreeImage::Format::RGB);
	freeImage2.saveToFile("testBlend2.png", FreeImage::SavingFormat::PNG);

	return 0;

	Application<char> a(argc, argv);



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
		Network::Server myUDPConnection(Network::SockType::UDP, Network::IpFamily::Undefined);
		myUDPConnection.Listen(5001, 100);

		Network::Connection myTCPConnection(Network::SockType::TCP, Network::IpFamily::Undefined);
		myTCPConnection.Connect("127.0.0.1", 5001);

		Network::Address addresFrom;
		if (myUDPConnection.ReceiveFrom(testData2, sizeof(testData2), &addresFrom))
			Log::displayLog(String() << "We got an UDP message from the server " << testData2);

	} else if (result == 1) {
		//SERVER
		Network::Server myConnection(Network::SockType::TCP, Network::IpFamily::Undefined);
		myConnection.Listen(5001, 100);
		Network::Connection clientConnection;
		while (myConnection.Accept(&clientConnection)){
			Log::displayLog(String() << "We got a client ! IP : " << clientConnection.getIp());

			Network::Connection myUDPConnection(Network::SockType::UDP, Network::IpFamily::Undefined);
			myUDPConnection.Connect(clientConnection, 5001);

			Log::displayLog("Sending UDP Message to client.");

			myUDPConnection.Send(testData, sizeof(testData));
		}
	} else {
		/////CLIENT
		Network::Connection myTCPConnection(Network::SockType::TCP, Network::IpFamily::Undefined);
		
		if (myTCPConnection.Connect("www.google.fr", 80)){
			Log::displayLog(std::string("Connected to Google ! IP:" + myTCPConnection.getIp()).c_str());
		}

		

		while (1);

	}*/

	
	return 0;
}

#endif