#ifndef _IMAGE_READER_HPP_
#define _IMAGE_READER_HPP_

class ImageReader
{
public:
	virtual void printImageInfo() = 0;
	virtual void printMostFrequentColor() = 0;
	virtual int calculateNumberOfUniqueColors() = 0;
};
#endif // _IMAGE_READER_HPP_