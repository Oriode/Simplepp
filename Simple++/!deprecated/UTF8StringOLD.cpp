#include "UTF8StringOLD.h"


UTF8StringOLD::UTF8StringOLD(const std::string & text, bool bufferize ){
	this -> useCodePointBuffer = bufferize;

	*this = text;
}

UTF8StringOLD::UTF8StringOLD( const char * text, bool bufferize  ) :
useCodePointBuffer(bufferize),
charData(String::getSize(text))


{
	this -> useCodePointBuffer = bufferize;
	memcpy(this->charData.getData(), text, this->charData.getSize());

	updateCodePoints();
	this->needUpdateSize = true;
}

UTF8StringOLD::UTF8StringOLD( bool bufferize ) :
useCodePointBuffer(bufferize),
needUpdateSize(false),
numChars(0)
{


}



UTF8StringOLD::UTF8StringOLD( const char * text, unsigned int size, bool bufferize) :
charData(size, size),
needUpdateSize(true),
useCodePointBuffer(bufferize)
{
	this -> charData.copy(text, size);
	updateCodePoints();
}



UTF8StringOLD & UTF8StringOLD::operator=( const std::string & text ){
	this -> charData.resize((unsigned int) text.size());
	memcpy(this -> charData.getData(), text.data(), this -> charData.getSize());

	updateCodePoints();
	this -> needUpdateSize = true;
	return *this;

}

UTF8StringOLD & UTF8StringOLD::operator=( const char * text ){
	this -> charData.resize((unsigned int) strlen(text));
	memcpy(this -> charData.getData(), text, this -> charData.getSize());

	updateCodePoints();
	this -> needUpdateSize = true;
	return *this;
}

UTF8StringOLD & UTF8StringOLD::operator=( const UTF8StringOLD & text ){
	this -> charData = text.charData;
	this -> codePoints = text.codePoints;
	this -> numChars = text.numChars;
	return *this;
}



UTF8StringOLD UTF8StringOLD::getDirectory( const UTF8StringOLD & filePath ){
	int slashIndex = -1;
	for (int i = 0; filePath.getDataSize(); i++){
		if(filePath[i] == '\\' || filePath[i] == '/'){
			slashIndex = i;
			break;
		}
	}
	return filePath.substr(0, slashIndex+1);
}




UTF8StringOLD UTF8StringOLD::getDirectory() const{
	return getDirectory(*this);
}





Vector<UTF8StringOLD> UTF8StringOLD::split( const UTF8StringOLD & s, char delimiter ){
	Vector<UTF8StringOLD> result;
	unsigned int lastIndex = 0;

	for (unsigned int i = 0; i < s.getDataSize(); i++){
		if (s[i] == delimiter){
			result.push(s.substr(lastIndex, i - lastIndex));
			lastIndex = i + 1;
		}
	}
	result.push(s.substr(lastIndex, s.getDataSize() - lastIndex));

	return result;
}

Vector<UTF8StringOLD> UTF8StringOLD::split( char delimiter ) const{
	return split(*this, delimiter);
}


UTF8StringOLD::~UTF8StringOLD(void){
}



bool UTF8StringOLD::isNumeric( const UTF8StringOLD & v ){
	for (unsigned int i = 0; i < v.getDataSize(); i++){
		if (v[i] < 42 || v[i] > 57)
			return false;
	}
	return true;
}

bool UTF8StringOLD::isNumeric() const{
	return isNumeric(*this);
}



UTF8StringOLD UTF8StringOLD::getFirstWord( const UTF8StringOLD & text ){
	for (unsigned int i = 0; i< text.getDataSize(); i++){
		if (text[i] == ' ')
			return text.substr(0, i);
	}
	return text.substr(0, text.getDataSize());
}

UTF8StringOLD UTF8StringOLD::getFirstWord() const{
	return getFirstWord(*this);
}



UTF8StringOLD UTF8StringOLD::getFileName( const UTF8StringOLD & filePath ){
	Vector<UTF8StringOLD> file = UTF8StringOLD::split(filePath, '/');
	return file[file.getSize() - 1];
}

UTF8StringOLD UTF8StringOLD::getFileName() const{
	return getFileName(*this);
}


UTF8StringOLD UTF8StringOLD::replace( const UTF8StringOLD & text, char toReplace, const UTF8StringOLD & change ){
	UTF8StringOLD result;
	result.reserve(text.getDataSize());
	for (unsigned int i = 0; i < text.getDataSize(); i++){
		if (text[i] == toReplace){
			result += change;
		} else {
			result += text[i];
		}
	}
	return result;
}


void UTF8StringOLD::replace( char toReplace, char change ){
	for (unsigned int i = 0; i < this -> charData.getSize(); i++){
		if (this -> charData[i] == toReplace)
			this -> charData[i] = change;
	}

	updateCodePoints();
}



unsigned int UTF8StringOLD::getCodePoint( unsigned int index ){
	if (this -> useCodePointBuffer){
		return this -> codePoints[index];
	} else {
		unsigned int charNum = 0;
		unsigned char charTMP[4];

		unsigned int i = 0;
		while (i < this -> charData.getSize()){
			charTMP[0] = this -> charData[i];
			if (this -> charData[i] & 0x80){				//1100 0000
				charTMP[1] = this -> charData[i + 1];
				if (this -> charData[i] & 0x20){			//1110 0000
					charTMP[2] = this -> charData[i + 2];
					if (this -> charData[i] & 0x10){		//1111 0000
						charTMP[3] = this -> charData[i + 3];

						if (charNum == index)
							return ((charTMP[0] & 0x7) << 18) | ((charTMP[1] & 0x3F) << 12) | ((charTMP[2] & 0x3F) << 6) | (charTMP[3] & 0x3F);
						i+= 4;
					} else { //If the code point is on THREE Bytes ONLY !
						if (charNum == index)
							return ((charTMP[0] & 0xF) << 12) | ((charTMP[1] & 0x3F) << 6) | (charTMP[2] & 0x3F);
						i+= 3;
					}
				} else { //If the code point is on TWO Bytes ONLY !
					if (charNum == index)
						return ((charTMP[0] & 0x1F) << 6) | (charTMP[1] & 0x3F);
					i+= 2;
				}
			} else {  //If the code point is on ONE Byte ONLY !
				if (charNum == index)
					return (unsigned char) this -> charData[i];
				i++;
			}
			charNum++;
		}

	}
	return 0;
}

void UTF8StringOLD::updateCodePoints(){
	if (!this -> useCodePointBuffer)
		return;

	//reserve for optimization
	this -> codePoints.clear();
	this -> codePoints.reserve(this -> charData.getSize() / 4);


	unsigned char charTMP[4];


	unsigned int i = 0;
	while (i < this -> charData.getSize()){
		charTMP[0] = this -> charData[i];
		if (this -> charData[i] & 0x80){				//1100 0000
			charTMP[1] = this -> charData[i + 1];
			if (this -> charData[i] & 0x20){			//1110 0000
				charTMP[2] = this -> charData[i + 2];
				if (this -> charData[i] & 0x10){		//1111 0000
					charTMP[3] = this -> charData[i + 3];

					unsigned int codePoint = ((charTMP[0] & 0x7) << 18) | ((charTMP[1] & 0x3F) << 12) | ((charTMP[2] & 0x3F) << 6) | (charTMP[3] & 0x3F);
					this -> codePoints.push(codePoint);
					i+= 4;
				} else { //If the code point is on THREE Bytes ONLY !
					unsigned int codePoint = ((charTMP[0] & 0xF) << 12) | ((charTMP[1] & 0x3F) << 6) | (charTMP[2] & 0x3F);
					this -> codePoints.push(codePoint);
					i+= 3;
				}
			} else { //If the code point is on TWO Bytes ONLY !
				unsigned int codePoint = ((charTMP[0] & 0x1F) << 6) | (charTMP[1] & 0x3F);
				this -> codePoints.push(codePoint);
				i+= 2;
			}
		} else {  //If the code point is on ONE Byte ONLY !
			this -> codePoints.push(charTMP[0]);
			i++;
		}
	}

}

void UTF8StringOLD::updateSize(){
	if (this -> needUpdateSize){
		if (this -> useCodePointBuffer){
			this -> numChars = this -> codePoints.getSize();
		} else {
			unsigned int size = 0;
			for (unsigned int i = 0; iterate(&i); size++);
			this -> numChars = size;
		}
		this -> needUpdateSize = false;
	}
}

char UTF8StringOLD::operator[]( unsigned int i ) const{
	return this -> charData[i];
}

unsigned int UTF8StringOLD::getSize(){
	updateSize();
	return this -> numChars;
}

std::string UTF8StringOLD::toStdString(){
	return std::string(this -> charData.getData(), this -> charData.getSize());
}

unsigned int UTF8StringOLD::size(){
	return getSize();
}

UTF8StringOLD UTF8StringOLD::substr( unsigned int index, unsigned int length ) const{
	UTF8StringOLD result;
	result.copy(*this, index, length);
	return result;
}

UTF8StringOLD & UTF8StringOLD::operator+=( const UTF8StringOLD & text ){
	this -> numChars += text.numChars;
	this -> charData += text.charData;

	if (this -> useCodePointBuffer && text.useCodePointBuffer)
		this -> codePoints += text.codePoints;
	else if (this -> useCodePointBuffer)
		updateCodePoints();
	else
		this -> codePoints.reset();

	return *this;
}

UTF8StringOLD & UTF8StringOLD::operator+=( char c ){
	this -> charData.push(c);
	if (this -> useCodePointBuffer)
		this -> codePoints.push(c);
	this -> numChars++;
	return *this;
}

void UTF8StringOLD::push( char c ){
	*this += c;
}

void UTF8StringOLD::push( const UTF8StringOLD & text ){
	*this += text;
}

void UTF8StringOLD::reserve( unsigned int size ){
	this -> charData.reserve(size);
}

void UTF8StringOLD::copy( const UTF8StringOLD & text, unsigned int index, unsigned int size ){
	this -> numChars = size;


	unsigned int startIndex = 0;

	while (startIndex < index && iterate(&startIndex));
	unsigned int endIndex = startIndex;
	unsigned int max = index + size;
	while (endIndex < max && iterate(&endIndex));



	this -> charData.resize(endIndex - startIndex);
	for (unsigned int i = 0; i < this -> charData.getSize(); i++){
		this -> charData[i] = text[i + startIndex];
	}


}

void UTF8StringOLD::clear(){
	this -> charData.clear();
	this -> codePoints.clear();
	this -> numChars = 0;
}

void UTF8StringOLD::reset(){
	this -> charData.reset();
	this -> codePoints.reset();
	this -> numChars = 0;
}


unsigned int UTF8StringOLD::getDataSize( unsigned int index, unsigned int size ){

	unsigned int dataSize = 0;

	if (this -> useCodePointBuffer){
		unsigned int max = size + index;
		for (unsigned int i = index; i < max; i++){
			if (this -> codePoints[i] < 128)
				dataSize++;
			else if (this -> codePoints[i] < 2048)
				dataSize+=2;
			else if (this -> codePoints[i] < 65536)
				dataSize+=3;
			else
				dataSize+=4;
		}
	} else {
		unsigned int startIndex = 0;

		while (startIndex < index && iterate(&startIndex));
		unsigned int endIndex = startIndex;
		unsigned int max = index + size;
		while (endIndex < max && iterate(&endIndex));

		dataSize = endIndex - startIndex;
	}
	return dataSize;


}

unsigned int UTF8StringOLD::getDataSize() const{
	return this -> charData.getSize();
}

bool UTF8StringOLD::iterate( unsigned int * i ) const{

	if (this -> useCodePointBuffer){
		if (*i > this->codePoints.getSize())
			return false;

		(*i) += 1;
	} else {
		if (this -> charData[*i] & 0x80){				//1100 0000
			if (this -> charData[*i] & 0x20){			//1110 0000
				if (this -> charData[*i] & 0x10){		//1111 0000
					(*i) += 4;
				} else { //If the code point is on THREE Bytes ONLY 
					(*i) += 3;
				}
			} else { //If the code point is on TWO Bytes ONLY !
				(*i) += 2;
			}
		} else {  //If the code point is on ONE Byte ONLY !
			(*i) += 1;
		}

		if (*i > this -> charData.getSize())
			return false;
	}



	return true;
}

bool UTF8StringOLD::iterate( unsigned int * i , UCodePoint * codePoint ) const{

	if (this -> useCodePointBuffer){
		*codePoint = this -> codePoints[*i];
		(*i)++;

		if (*i > this -> codePoints.getSize())
			return false;
	} else {
		unsigned char charTMP[4];
		charTMP[0] = this -> charData[*i];
		if (this -> charData[*i] & 0x80){				//1100 0000
			charTMP[1] = this -> charData[*i + 1];
			if (this -> charData[*i] & 0x20){			//1110 0000
				charTMP[2] = this -> charData[*i + 2];
				if (this -> charData[*i] & 0x10){		//1111 0000
					charTMP[3] = this -> charData[*i + 3];

					*codePoint = ((charTMP[0] & 0x7) << 18) | ((charTMP[1] & 0x3F) << 12) | ((charTMP[2] & 0x3F) << 6) | (charTMP[3] & 0x3F);
					(*i)+= 4;
				} else { //If the code point is on THREE Bytes ONLY !
					*codePoint = ((charTMP[0] & 0xF) << 12) | ((charTMP[1] & 0x3F) << 6) | (charTMP[2] & 0x3F);
					(*i)+= 3;
				}
			} else { //If the code point is on TWO Bytes ONLY !
				*codePoint = ((charTMP[0] & 0x1F) << 6) | (charTMP[1] & 0x3F);
				(*i)+= 2;
			}
		} else {  //If the code point is on ONE Byte ONLY !
			*codePoint = charTMP[0];
			(*i)++;
		}

		if (*i > this -> charData.getSize())
			return false;

	}



	return true;
}





bool UTF8StringOLD::operator!=( const UTF8StringOLD & text ) const{
	if (this -> numChars != text.numChars)
		return true;


	for (unsigned int i = 0; i < this -> charData.getSize(); i++){
		if (this -> charData[i] != text.charData[i])
			return true;

	}
	return false;
}

bool UTF8StringOLD::operator==( const UTF8StringOLD & text ) const{
	if (this -> numChars != text.numChars)
		return false;


	for (unsigned int i = 0; i < this -> charData.getSize(); i++){
		if (this -> charData[i] != text.charData[i])
			return false;

	}
	return true;
}

bool UTF8StringOLD::operator>( const UTF8StringOLD & text ) const{
	unsigned int max = Math::min(this -> charData.getSize(), text.charData.getSize());
	for (unsigned int i = 0; i < max; i++){
		if (this -> charData[i] > text.charData[i])
			return true;
		else if (this -> charData[i] < text.charData[i])
			return false;
	}
	return false;
}

bool UTF8StringOLD::operator<( const UTF8StringOLD & text ) const{
	unsigned int max = Math::min(this -> charData.getSize(), text.charData.getSize());
	for (unsigned int i = 0; i < max; i++){
		if (this -> charData[i] < text.charData[i])
			return true;
		else if (this -> charData[i] > text.charData[i])
			return false;
	}
	return false;
}

bool UTF8StringOLD::operator>=( const UTF8StringOLD & text ) const{
	unsigned int max = Math::min(this -> charData.getSize(), text.charData.getSize());
	for (unsigned int i = 0; i < max; i++){
		if (this -> charData[i] > text.charData[i])
			return true;
		else if (this -> charData[i] < text.charData[i])
			return false;
	}
	return true;
}

bool UTF8StringOLD::operator<=( const UTF8StringOLD & text ) const{
	unsigned int max = Math::min(this -> charData.getSize(), text.charData.getSize());
	for (unsigned int i = 0; i < max; i++){
		if (this -> charData[i] < text.charData[i])
			return true;
		else if (this -> charData[i] > text.charData[i])
			return false;
	}
	return true;
}

void UTF8StringOLD::setUseCodePointBuffer( bool useCodePointBuffer ){
	if (this -> useCodePointBuffer == useCodePointBuffer)
		return;

	this -> useCodePointBuffer = useCodePointBuffer;
	if (this -> useCodePointBuffer){
		updateCodePoints();
	} else {
		this -> codePoints.reset();
	}

}

const char * UTF8StringOLD::getData() const{
	return this -> charData.getData();
}

char * UTF8StringOLD::getData(){
	return this->charData.getData();
}



UTF8StringOLD operator+( const UTF8StringOLD & text1, const UTF8StringOLD & text2 ){
	UTF8StringOLD result = text1;
	result += text2;
	return result;
}

std::ostream & operator<<( std::ostream & out, UTF8StringOLD & text ){
	out << text.getData();
	return out;
}
