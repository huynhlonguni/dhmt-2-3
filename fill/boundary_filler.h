#pragma once

#include <stack>
using namespace std;

class BoundaryFiller {
public:
	static void fill(int xc, int yc, int w, int h, char *img, char fillColor, char outlineColor) {
		if (xc < 0) xc = 0;
		else if (xc > w - 1) xc = w - 1;

		if (yc < 0) yc = 0;
		else if (yc > h - 1) yc = h - 1;

		struct Vector2i {
			int x, y;
		};

		stack<Vector2i> st;

		st.push({xc, yc});

		while (!st.empty()) {
			Vector2i pixel = st.top();
			st.pop();

			int x = pixel.x;
			int y = pixel.y;

			if (img[y * w + x] != fillColor && img[y * w + x] != outlineColor) {
				img[y * w + x] = fillColor;
				if (x - 1 >= 0)
					st.push({x - 1, y});
				if (y - 1 >= 0)
					st.push({x, y - 1});
				if (x + 1 < w)
					st.push({x + 1, y});
				if (y + 1 < h)
					st.push({x, y + 1});
			}
		}
	}
};