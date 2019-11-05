#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;
// Tinh histogram chung, ham ho tro
vector<int> CalculateNewLevelHistorgram(vector<int> hist, Mat newmap)
{
	vector <float> xacsuat;
	xacsuat.resize(256);
	for (int i = 0; i < 256; i++)
	{
		xacsuat[i] = hist[i] * 1.0 / (newmap.rows * newmap.cols);
	}

	vector<float> cdf;
	cdf.resize(256);
	cdf[0] = xacsuat[0];
	for (int i = 1; i < 256; i++)
	{
		cdf[i] = cdf[i - 1] + xacsuat[i];
	}

	vector<int> newLevel;
	newLevel.resize(256);
	for (int i = 0; i < 256; i++)
	{
		newLevel[i] = (int)(255 * cdf[i]);
	}
	return newLevel;
}
// Tinh histogram anh xam
vector <int> TinhHistogramAnhXam(Mat a)
{
	vector<int> histogram;
	histogram.resize(256);
	for (int i = 0; i < 256; i++)
	{
		histogram[i] = 0;
	}
	for (int i = 0; i < a.rows; i++)
	{
		for (int k = 0; k < a.cols; k++)
		{
			uchar intensity = a.at<uchar>(i, k);
			histogram[static_cast<int>(intensity)] ++;
		}
	}
	return histogram;
}
// Can bang anh xam
Mat EqualizeGrayHistogram(Mat a)
{
	Mat newmap = a.clone();
	vector<int> hist = TinhHistogramAnhXam(a);
	vector<int> newLevel = CalculateNewLevelHistorgram(hist, newmap);

	for (int i = 0; i < newmap.rows; i++)
	{
		for (int k = 0; k < newmap.cols; k++)
		{
			uchar &intensity = newmap.at<uchar>(i, k);
			int num = static_cast<int>(intensity);
			intensity = newLevel[num];
		}
	}
	return newmap;
}
// Tinh histogram anh mau
vector<vector<int>> TinhHistogramAnhMau(Mat a)
{
	vector<vector<int>> histogram;
	histogram.resize(3);
	for (int i = 0; i < 3; i++)
	{
		histogram[i].resize(256);
		for (int k = 0; k < 256; k++) histogram[i][k] = 0;
	}

	for (int i = 0; i < a.rows; i++)
	{
		for (int k = 0; k < a.cols; k++)
		{
			Vec3b intensity = a.at<Vec3b>(i, k);
			for (int j = 0; j < 3; j++) {
				histogram[j][static_cast<int>(intensity[j])] ++;
			}
		}
	}
	return histogram;
}
// Can bang anh mau
Mat EqualizeColorHistogram(Mat a)
{
	Mat newmap = a.clone();
	vector<vector<int>>hist;
	hist = TinhHistogramAnhMau(a);

	vector<vector<int>> newLevel;
	newLevel.resize(3);
	for (int i = 0; i < 3; i++)
	{
		newLevel[i].resize(256);
		vector<int> temp = CalculateNewLevelHistorgram(hist[i], newmap);
		for (int k = 0; k < 256; k++)
		{
			newLevel[i][k] = temp[k];
		}
	}

	for (int i = 0; i < newmap.rows; i++)
	{
		for (int k = 0; k < newmap.cols; k++)
		{
			Vec3b &intensity = newmap.at<Vec3b>(i, k);
			for (int j = 0; j < 3; j++) {
				int num = static_cast<int>(intensity[j]);
				intensity.val[j] = newLevel[j][num];
			}
		}
	}
	return newmap;
}