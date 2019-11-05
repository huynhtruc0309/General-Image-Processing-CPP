#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <vector>

// Ham ho tro tinh toan them: CalculateEqualizeHistogramVector, tham so: vector, Mat, ket qua tra ve: vector
// 5. Tinh Histogram anh mau / anh xam:
// Ham: GrayImageCalculate, tham so: Mat, ket qua tra ve: 1 vector 1 chieu
// Ham: ColorImageCalculate,tham so: Mat, ket qua tra ve: 1 vector 2 chieu
// 6. Can bang Histogram anh mau / anh xam:
// Ham: EqualizeGrayHistogram , thamso: Mat, ket qua tra ve: Mat
// Ham: EqualizeColorHistogram, thamso: Mat, ket qua tra ve: Mat

using namespace cv;
using namespace std;
// Tinh histogram chung, ham ho tro
vector<int> CalculateEqualizeHistogramVector(vector<int> hist, Mat newmap)
{
	vector <float> xacsuat;
	xacsuat.resize(256);
	//Tinh xac suat cua tung gia tri hist, hist co 256 gia tri tu 1->256 tuong ung
	for (int i = 0; i < 256; i++) xacsuat[i] = hist[i] * 1.0 / (newmap.rows * newmap.cols);

	//Tinh cdf (Compact Density Fiber Board), la tinh tong tang dan cua moi xac suat hist
	vector<float> cdf;
	cdf.resize(256);
	cdf[0] = xacsuat[0];
	for (int i = 1; i < 256; i++)
	{
		cdf[i] = cdf[i - 1] + xacsuat[i];
	}
	//Sau cung tinh Equalize Hist de phan phoi xac suat hop li
	vector<int> EqualizeHist;
	EqualizeHist.resize(256);
	for (int i = 0; i < 256; i++)
	{
		EqualizeHist[i] = (int)(255 * cdf[i]);
	}
	return EqualizeHist;
}
// Tinh histogram anh xam
vector <int> GrayImageCalculate(Mat a)
{
	//Doc anh a, moi diem anh co gia tri tu 1-256, tinh tan so cua tung gia tri
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
	// Lay vector histogram anh xam, equalize no, sau do quang nguoc tro lai anh goc
	Mat newmap = a.clone();
	vector<int> hist = GrayImageCalculate(a);
	vector<int> newLevel = CalculateEqualizeHistogramVector(hist, newmap);

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
vector<vector<int>> ColorImageCalculate(Mat a)
{
	// Tuong tu nhu tinh Histogram anh xam, nhung tach ra thanh 3 kenh R,G,B
	// Tuong ung voi histogram[0], histogram[1], histogram[2]
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
	// Tuong tu voi can bang anh xam, nhung tach ra thanh 3 kenh R,G,B
	// Sau do equalize tung kenh va dua lai vao anh goc
	Mat newmap = a.clone();
	vector<vector<int>>hist;
	hist = ColorImageCalculate(a);

	vector<vector<int>> newLevel;
	newLevel.resize(3);
	for (int i = 0; i < 3; i++)
	{
		newLevel[i].resize(256);
		vector<int> temp = CalculateEqualizeHistogramVector(hist[i], newmap);
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