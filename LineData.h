#pragma once
#include "stdafx.h"

class LineData {
public:
	LineData(const int& iX1, const int& iY1, const int& iX2, const int& iY2, Mat& aMat, bool drawLine = false, Vec3b color = 0);
	~LineData() {}
	vector<Vec3b> getRawData() const { return rawData; }
	const int& iX1;
	const int& iX2;
	const int& iY1;
	const int& iY2;
	int getILength() const { return iLength; }
	vector<int> pointOnLine(int distance, bool draw = false);
private:
	int iLength;
	vector<Vec3b> rawData;
	Mat& aMat;
	bool drawLine;
	Vec3b color;
	void calculateILength(const int& iX1, const int& iY1, const int& iX2, const int& iY2);
	void setILength(int length) { iLength = length; }
	void allocateRawData(int uX1, int uY1, int uX2, int uY2, Mat& aMat, bool& drawLine, Vec3b& color);
	Vec3b bgrToRgb(Vec3b&);
};