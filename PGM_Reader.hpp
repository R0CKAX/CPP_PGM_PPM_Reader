#ifndef _PGM_READER_HPP_
#define _PGM_READER_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <sstream>
#include <iomanip>

#include "ImageReader.hpp"

class PGM_Reader : public ImageReader
{
private:
	std::fstream imageFile;
	int width, height, maxVal;
	std::string comment, fileType;
	std::vector<int> imageData;
	std::map<int, int> colorAmounts;
	int spacing;

public:
	/// <summary>
	/// Reads values of all pixels from a .pgm file and extracts all useful information from the file. 
	/// Also allows user to rotate the image.
	/// Returns imageData
	/// </summary>
	/// <param name = "imageFile"> A .pgm file </param>
	/// <param name = "width"> The amount of pixels in one row of a .pgm file </param>
	/// <param name = "height"> The amount of rows in a .pgm file </param>
	/// <param name = "maxVal"> The maximum value that will appear in all of the pixels </param>
	/// <param name = "comment"> Comment extracted from a .pgm file </param>
	/// <param name = "fileType"> File type extracted from a .pgm file </param>
	/// <param name = "imageData"> Vector used for storing values of all pixels in a .pgm file </param>
	/// <param name = "colorAmounts"> Map used to count the amount of all color types in an image </param>
	/// <param name = "spacing"> the amount of characters that are able to fit in one column used with std::setw() </param>

	// Constructor that reads width, height, maxVal and all pixel values from a file
	PGM_Reader(std::string imagePath);

	// Method used for displaying all important information about the image
	void printImageInfo() override;

	// Method displaying the most frequently present color/s on an image
	void printMostFrequentColor() override;

	// Method counting the amount of unique colors present on an image
	int calculateNumberOfUniqueColors() override;

	// Method displaying all pixel values from an image
	void printImageData();

	// Method displaying the least frequently present color/s on an image
	void printLeastFrequentColor();

	// Method that rotates our image left by 90 degrees
	void rotateLeft();

	// Method that sets a fixed amount of space for one column of values extracted from a .pgm file
	void setSpacing(int max);
};
#endif // _PGM_READER_HPP_