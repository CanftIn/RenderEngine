#include "image.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

void _line(int x0, int y0, int x1, int y1, Image &image, TGAColor color) {
	for (float t = 0.; t<1.; t += .1) {
		int x = x0*(1. - t) + x1*t;
		int y = y0*(1. - t) + y1*t;
		image.set(x, y, color);
	}
}

void __line(int x0, int y0, int x1, int y1, Image &image, TGAColor color) {
	for (int x = x0; x <= x1; x++) {
		float t = (x - x0) / (float)(x1 - x0);
		int y = y0*(1. - t) + y1*t;
		image.set(x, y, color);
	}
}

void line(int x0, int y0, int x1, int y1, Image &image, TGAColor color) {
	bool steep = false;
	if (std::abs(x0 - x1)<std::abs(y0 - y1)) { // if the line is steep, we transpose the image 
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}
	if (x0>x1) { // make it left−to−right 
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	for (int x = x0; x <= x1; x++) {
		float t = (x - x0) / (float)(x1 - x0);
		int y = y0*(1. - t) + y1*t;
		if (steep) {
			image.set(y, x, color); // if transposed, de−transpose 
		}
		else {
			image.set(x, y, color);
		}
	}
}

int main(int argc, char** argv) {
	Image image(100, 100, Image::RGB);
	line(13, 20, 80, 40, image, white);
	line(20, 13, 40, 80, image, red);
	line(80, 40, 13, 20, image, red);
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output1.tga");
	return 0;
}