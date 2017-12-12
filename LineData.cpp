#include "LineData.h"

LineData::LineData(const int& iX1, const int& iY1, const int& iX2, const int& iY2, Mat& aMat, bool drawLine, Vec3b color):
iX1(iX1),
iY1(iY1),
iX2(iX2),
iY2(iY2),
aMat(aMat),
drawLine(drawLine),
color(color){
	calculateILength(iX1, iY1, iX2, iY2);
	allocateRawData(iY1, iX1, iY2, iX2, aMat, drawLine, color);
}

void LineData::calculateILength(const int& iX1, const int& iY1, const int& iX2, const int& iY2) {
	iLength = static_cast<int>(norm(Point(iX1, iY1) - Point(iX2, iY2)));
	setILength(iLength);
}

void LineData::allocateRawData(int uX1, int uY1, int uX2, int uY2, Mat& aMat, bool& drawLine, Vec3b& color) {

	// Bresenham's line algorithm
	const bool steep = (fabs(uY2 - uY1) > fabs(uX2 - uX1));

	if (steep) {
		swap(uX1, uY1);
		swap(uX2, uY2);
	}

	if (uX1 > uX2) {
		swap(uX1, uX2);
		swap(uY1, uY2);
	}

	const int dX = static_cast<int>(uX2 - uX1);
	const int dY = static_cast<int>((fabs(uY2 - uY1)));

	float error = dX / 2.0f;
	const int yStep = (uY1 < uY2) ? 1 : -1;
	int y = uY1;

	const int maxX = uX2;

	for (int x = uX1; x < maxX; x++) {
		if (steep) {
			rawData.push_back(bgrToRgb(aMat.ptr<Vec3b>(y)[x]));
			if (drawLine) aMat.ptr<Vec3b>(y)[x] = color;
		} else {
			rawData.push_back(bgrToRgb(aMat.ptr<Vec3b>(x)[y]));
			if (drawLine) aMat.ptr<Vec3b>(x)[y] = color;
		}
		error -= dY;

		if (error < 0) {
			y += yStep;
			error += dX;
		}
	}

}

vector<int> LineData::pointOnLine(int distance, bool draw)
{
	// Calculate vectors
	double vx = iX2 - iX1;
	double vy = iY2 - iY1;

	// Normalize the vector to unit length
	vx /= (double)iLength;
	vy /= (double)iLength;

	// Calculate new vectors
	int px = static_cast<int>(iX1 + (vx * distance));
	int py = static_cast<int>(iY1 + (vy * distance));

	vector<int> point;
	point.push_back(px);
	point.push_back(py);

	if(draw && distance < iLength) circle(aMat, Point(px, py), 3, Scalar(0, 0, 255), CV_FILLED, 8, 0);
	
	return point;
}

Vec3b LineData::bgrToRgb(Vec3b& vec)
{
	Vec3b rgb;
	rgb.val[0] = vec.val[2];
	rgb.val[1] = vec.val[1];
	rgb.val[2] = vec.val[0];
	return rgb;
}

