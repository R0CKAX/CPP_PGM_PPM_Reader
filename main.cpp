#include "PGM_Reader.hpp"
#include "PPM_Reader.hpp"

int main()
{
	setlocale(LC_ALL, "");

	PGM_Reader r("feep.pgm");
	ImageReader* reader = &r;

	r.printImageInfo();
	r.printImageData();
	r.rotateLeft();
	r.printImageData();
	r.rotateLeft();
	r.printImageData();

	PPM_Reader re("rgb.ppm");
	ImageReader* readerr = &re;

	re.printImageInfo();
	re.printImageData();
	re.rotateLeft();
	re.printImageData();
	re.rotateLeft();
	re.printImageData();

	return 0;
}