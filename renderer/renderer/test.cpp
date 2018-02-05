#include <cmath>
#include <vector>
#include "model.h"
#include "geometry.h"
#include "image.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);
Model *model = NULL;
const int width = 800;
const int height = 800;

void line(Vec2i p0, Vec2i p1, Image &image, TGAColor color) {
	bool steep = false;
	if (std::abs(p0.x - p1.x)<std::abs(p0.y - p1.y)) {
		std::swap(p0.x, p0.y);
		std::swap(p1.x, p1.y);
		steep = true;
	}
	if (p0.x>p1.x) {
		std::swap(p0, p1);
	}

	for (int x = p0.x; x <= p1.x; x++) {
		float t = (x - p0.x) / (float)(p1.x - p0.x);
		int y = p0.y*(1. - t) + p1.y*t;
		if (steep) {
			image.set(y, x, color);
		}
		else {
			image.set(x, y, color);
		}
	}
}

void triangle(Vec2i t0, Vec2i t1, Vec2i t2, Image &image, TGAColor color) {
	line(t0, t1, image, color);
	line(t1, t2, image, color);
	line(t2, t0, image, color);
}
int main(int argc, char** argv) 
{

	Image image(width, height, Image::RGB);
	Vec2i t0[3] = { Vec2i(100, 700),   Vec2i(500, 160),  Vec2i(700, 80) };
	Vec2i t1[3] = { Vec2i(180, 500),  Vec2i(150, 400),   Vec2i(70, 180) };
	Vec2i t2[3] = { Vec2i(180, 150), Vec2i(620, 360), Vec2i(230, 680) };

	triangle(t0[0], t0[1], t0[2], image, red);
	triangle(t1[0], t1[1], t1[2], image, white);
	triangle(t2[0], t2[1], t2[2], image, green);
	image.flip_vertically();
	image.write_tga_file("output.tga");
	delete model;
	return 0;
}