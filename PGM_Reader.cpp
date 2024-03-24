#include "PGM_Reader.hpp"

PGM_Reader::PGM_Reader(std::string imagePath)
{
	width = 0;
	height = 0;
	maxVal = 0;
	imageFile.open(imagePath, std::ios::in);
	if (imageFile.good())
	{
		std::string line;
		std::stringstream row(line);
		while (std::getline(imageFile, line))
		{
			if (line[0] == 'P')
			{
				fileType = line;
				if (fileType != "P2")
				{
					std::cout << "Niepoprawny format pliku. Poprawny format to P2" << "\n";
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
					int tmp;
					line2 >> tmp;
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

void PGM_Reader::printImageInfo()
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

void PGM_Reader::printMostFrequentColor()
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
		std::cout << *i << " ";
	}

	std::cout << "w liczbie " << maxCount << "\n";
}

int PGM_Reader::calculateNumberOfUniqueColors()
{
	std::set<int> uniqueColors(imageData.begin(), imageData.end());

	return uniqueColors.size();
}

void PGM_Reader::printImageData()
{
	std::cout << "\n";
	for (int i = 0; i < imageData.size(); i++)
	{
		std::cout << std::setw(spacing) << imageData[i] << " ";
		if ((i + 1) % width == 0)
		{
			std::cout << "\n";
		}
	}
}

void PGM_Reader::printLeastFrequentColor()
{
	int minCount = width * height;
	int leastFrequentValue = 0;
	std::set<int> sameAmount;

	for (const auto& color : colorAmounts) {
		if (color.second < minCount) 
		{
			minCount = color.second;
			leastFrequentValue = color.first;
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
		std::cout << *i << " ";
	}

	std::cout << "w liczbie " << minCount << "\n";
}

void PGM_Reader::setSpacing(int max)
{
	if (max > 99)
	{
		spacing = 3;
	}
	else if (max > 9)
	{
		spacing = 2;
	}
	else
	{
		spacing = 1;
	}
}

void PGM_Reader::rotateLeft()
{
	std::vector<int> rotatedImageData(width * height);
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
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