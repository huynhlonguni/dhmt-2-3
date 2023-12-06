#pragma once

#include <queue>
using namespace std;

void floodFill(int xc, int yc, int w, int h, char *img, char fillColor, char outlineColor) {
	if (xc < 0) xc = 0;
	else if (xc > w - 1) xc = w - 1;

	if (yc < 0) yc = 0;
	else if (yc > h - 1) yc = h - 1;

	struct Vector2i {
		int x, y;
	};

	queue<Vector2i> q;

	q.push({xc, yc});

	while (!q.empty()) {
		Vector2i pixel = q.front();
		q.pop();

		int x = pixel.x;
		int y = pixel.y;

		if (img[y * w + x] != fillColor && img[y * w + x] != outlineColor) {
			img[y * w + x] = fillColor;
			if (x - 1 >= 0)
				q.push({x - 1, y});
			if (y - 1 >= 0)
				q.push({x, y - 1});
			if (x + 1 < w)
				q.push({x + 1, y});
			if (y + 1 < h)
				q.push({x, y + 1});
		}
	}
}