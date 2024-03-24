#include "PPM_Reader.hpp"

PPM_Reader::PPM_Reader(std::string imagePath)
{
	width = 0;
	height = 0;
	maxVal = 0;
	imageFile.open(imagePath, std::ios::in);
	if (imageFile.good())
	{
		std::string line;
		std::stringstream row;
		while (std::getline(imageFile, line))
		{
			if (line[0] == 'P')
			{
				fileType = line;
				if (fileType != "P3")
				{
					std::cout << "Niepoprawny format pliku. Poprawny format to P3" << "\n";
					break;
				}
			}
			else if (line[0] == '#')
			{
				comment = line;
			}
			else if (line.empty())
			{

			}
			else if (width == 0 && height == 0)
			{
				row << line;
				row >> width >> height;
			}
			else if (maxVal == 0)
			{
				std::stringstream line2(line);
				line2 >> maxVal;
			}
			else
			{
				std::stringstream line2(line);
				for (int i = 0; i < width; i++)
				{
					int tmp = 0;
					int r, g, b;

					line2 >> r >> g >> b;
					tmp = (r << 16) | (g << 8) | b;
					imageData.push_back(tmp);
				}
			}
		}
	}
	else
	{
		std::cout << "Nie udalo sie otworzyc pliku " << imagePath << "\n";
	}
	imageFile.close();

	setSpacing(maxVal);
}

void PPM_Reader::printImageInfo()
{
	std::cout << "\nFormat pliku to: " << fileType << "\n";
	if (comment.empty())
	{
		std::cout << "Plik nie posiada ¿adnego komentarza" << "\n";
	}
	else
	{
		std::cout << "Komentarz zawarty w pliku: " << comment << "\n";
	}
	std::cout << "Wymiary obrazu to " << width << "x" << height << "\n";
	std::cout << "Obraz zawiera " << width * height << " pikseli" << "\n"; 
	std::cout << "Iloœæ unikatowych kolorów wynosi " << calculateNumberOfUniqueColors() << "\n";
	printMostFrequentColor();
	printLeastFrequentColor();
}

void PPM_Reader::printMostFrequentColor()
{
	int maxCount = 0;
	int mostFrequentValue = 0;
	std::set<int> sameAmount;

	for (int value : imageData)
	{
		colorAmounts[value]++;
	}

	for (const auto& color : colorAmounts) {
		if (color.second > maxCount) {
			maxCount = color.second;
			mostFrequentValue = color.first;
		}
	}

	for (const auto& check : colorAmounts)
	{
		if (check.second == maxCount)
		{
			sameAmount.insert(check.first);
		}
	}

	std::cout << "Najczêœciej wystêpuj¹cy kolor to ";

	for (auto i = sameAmount.begin(); i != sameAmount.end(); i++)
	{
		int r, g, b;
		r = (*i >> 16) & 0xFF;
		g = (*i >> 8) & 0xFF;
		b = *i & 0xFF;

		std::cout << *i << " (" << r << " " << g << " " << b << ") ";
	}

	std::cout << "w liczbie " << maxCount << "\n";
}

int PPM_Reader::calculateNumberOfUniqueColors()
{
	std::set<int> uniqueColors(imageData.begin(), imageData.end());

	return uniqueColors.size();
}

void PPM_Reader::printImageData()
{
	std::cout << "\n";
	for (int i = 0; i < imageData.size(); i++)
	{
		int r, g, b;
		r = (imageData[i] >> 16) & 0xFF;
		g = (imageData[i] >> 8) & 0xFF;
		b = imageData[i] & 0xFF;

		std::cout << std::setw(spacing) << "| " << r << " " << g << " " << b;
		if ((i + 1) % width == 0)
		{
			std::cout << " |" << "\n";
		}
	}
}

void PPM_Reader::printLeastFrequentColor()
{
	int minCount = width * height;
	int leastFrequentColor = 0;
	std::set<int> sameAmount;

	for (const auto& color : colorAmounts) {
		if (color.second < minCount)
		{
			minCount = color.second;
			leastFrequentColor = color.first;
		}
	}

	for (const auto& check : colorAmounts)
	{
		if (check.second == minCount)
		{
			sameAmount.insert(check.first);
		}
	}

	std::cout << "Najrzadziej wystêpuj¹cy kolor to ";

	for (auto i = sameAmount.begin(); i != sameAmount.end(); i++)
	{
		int r, g, b;
		r = (*i >> 16) & 0xFF;
		g = (*i >> 8) & 0xFF;
		b = *i & 0xFF;

		std::cout << *i << " (" << r << " " << g << " " << b << ") ";
	}

	std::cout << "w liczbie " << minCount << "\n";
}

void PPM_Reader::setSpacing(int max)
{
	if (max > 99)
	{
		spacing = 4;
	}
	else if (max > 9)
	{
		spacing = 3;
	}
	else
	{
		spacing = 2;
	}
}
 
void PPM_Reader::rotateLeft()
{
	std::vector<int> rotatedImageData(width * height);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			rotatedImageData[(width - 1 - j) * height + i] = imageData[i * width + j];
		}
	}

	imageData.clear();
	imageData.reserve(width * height);
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			imageData.push_back(rotatedImageData[i * height + j]);
		}
	}

	int tmp = 0;
	tmp = width;
	width = height;
	height = tmp;
}