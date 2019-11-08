#include "pch.h"
#include "Blur.h"

vector<vector<int>> MeanCalculate(vector<vector<int>> ht, int kWidth = 3, int kHeight = 3)
{
	// Mặc định Kernel Mean có ma trận 3x3 khi chập với ảnh
	vector<vector<int>> hist;
	hist.resize(ht.size());

	for (int i = 0; i < hist.size(); i++) hist[i].resize(ht[i].size());

	for (int i = 1; i < ht.size() - 1; i++)
	{
		for (int k = 1; k < ht[i].size() - 1; k++)
		{
			hist[i][k] = ht[i - 1][k - 1] + ht[i - 1][k] + ht[i - 1][k + 1] + ht[i][k - 1] + ht[i][k] + ht[i][k + 1] + ht[i + 1][k - 1] + ht[i + 1][k] + ht[i + 1][k + 1];
			hist[i][k] = round(hist[i][k] / 9);
		}
	}

	for (int i = 1; i < ht.size() - 1; i++)
	{
		hist[i][0] = ht[i - 1][0] + ht[i][0] + ht[i + 1][0] + ht[i - 1][1] + ht[i][1] + ht[i + 1][1];
		hist[i][0] = round(hist[i][0] / 6);
	}

	for (int i = 1; i < ht[0].size() - 1; i++)
	{
		hist[0][i] = ht[0][i - 1] + ht[0][i] + ht[0][i + 1] + ht[1][i - 1] + ht[1][i] + ht[1][i + 1];
		hist[0][i] = round(hist[0][i] / 6);
	}

	int n = ht.size() - 1;

	for (int i = 1; i < ht.size() - 1; i++)
	{
		hist[i][n] = ht[i - 1][n] + ht[i][n] + ht[i + 1][n] + ht[i - 1][n - 1] + ht[i][n - 1] + ht[i + 1][n - 1];
		hist[i][n] = round(hist[i][n] / 6);
	}

	for (int i = 1; i < ht[0].size() - 1; i++)
	{
		hist[n][i] = ht[n][i - 1] + ht[n][i] + ht[n][i + 1] + ht[n - 1][i - 1] + ht[n - 1][i] + ht[n - 1][i + 1];
		hist[n][i] = round(hist[n][i] / 6);
	}

	hist[0][0] = round((ht[0][0] + ht[0][1] + ht[1][1] + ht[1][0]) / 4);
	hist[n][0] = round((ht[n][0] + ht[n][1] + ht[n - 1][1] + ht[n - 1][0]) / 4);
	hist[0][n] = round((ht[0][n] + ht[0][n - 1] + ht[1][n - 1] + ht[1][n]) / 4);
	hist[n][n] = round((ht[n][n] + ht[n][n - 1] + ht[n - 1][n - 1] + ht[n - 1][n]) / 4);

	return hist;
}

Mat Meanfilter(const Mat a, int kWidth = 3, int kHeight = 3)
{
	Mat newmap = a.clone();

	vector<vector<int>> hist;

	hist.resize(a.rows);

	for (int i = 0; i < a.rows; i++) hist[i].resize(a.cols);

	for (int i = 0; i < newmap.rows; i++)
	{
		for (int k = 0; k < newmap.cols; k++)
		{
			hist[i][k] = newmap.at<uchar>(i, k);
		}
	}

	hist = MeanCalculate(hist);

	for (int i = 0; i < newmap.rows; i++)
	{
		for (int k = 0; k < newmap.cols; k++)
		{
			newmap.at<uchar>(i, k) = hist[i][k];
		}
	}

	return newmap;
}

vector<vector<int>> MedianCalculate(vector<vector<int>> ht, int kWidth = 3, int kHeight = 3)
{
	// Mặc định Kernel Median có ma trận 3x3 khi chập với ảnh
	vector<vector<int>> hist;
	hist.resize(ht.size());

	for (int i = 0; i < hist.size(); i++) hist[i].resize(ht[i].size());

	for (int i = 1; i < ht.size() - 1; i++)
	{
		for (int k = 1; k < ht[i].size() - 1; k++)
		{
			vector<int> myvec;
			myvec = { ht[i - 1][k - 1], ht[i - 1][k] ,ht[i - 1][k + 1] , ht[i][k - 1] , ht[i][k] , ht[i][k + 1] , ht[i + 1][k - 1] , ht[i + 1][k] , ht[i + 1][k + 1] };
			sort(myvec.begin(), myvec.end());
			hist[i][k] = myvec[4];
		}
	}

	for (int i = 1; i < ht.size() - 1; i++)
	{
		vector<int> myvec;
		myvec = { ht[i - 1][0] , ht[i][0] , ht[i + 1][0] , ht[i - 1][1] , ht[i][1] , ht[i + 1][1] };
		sort(myvec.begin(), myvec.end());
		hist[i][0] = round((myvec[2]+myvec[3])/2);
	}

	for (int i = 1; i < ht[0].size() - 1; i++)
	{
		vector<int> myvec;
		myvec = { ht[0][i - 1] , ht[0][i] , ht[0][i + 1] , ht[1][i - 1] , ht[1][i] , ht[1][i + 1] };
		sort(myvec.begin(), myvec.end());
		hist[0][i] = round((myvec[2] + myvec[3]) / 2);
	}

	int n = ht.size() - 1;

	for (int i = 1; i < ht.size() - 1; i++)
	{
		vector<int> myvec;
		myvec = { ht[i - 1][n] ,+ht[i][n] , ht[i + 1][n] , ht[i - 1][n - 1] , ht[i][n - 1] , ht[i + 1][n - 1] };
		sort(myvec.begin(), myvec.end());
		hist[i][n] = round((myvec[2] + myvec[3]) / 2);
	}

	for (int i = 1; i < ht[0].size() - 1; i++)
	{
		vector<int> myvec;
		myvec = { ht[n][i - 1] , ht[n][i] , ht[n][i + 1] , ht[n - 1][i - 1] , ht[n - 1][i] , ht[n - 1][i + 1] };
		sort(myvec.begin(), myvec.end());
		hist[n][i] = round((myvec[2] + myvec[3]) / 2);
	}

	hist[0][0] = ht[0][0];
	hist[n][0] = ht[n][0];
	hist[0][n] = ht[0][n];
	hist[n][n] = ht[n][n];

	return hist;
}

Mat Medianfilter(const Mat a, int kWidth = 3, int kHeight = 3)
{
	Mat newmap = a.clone();

	vector<vector<int>> hist;

	hist.resize(a.rows);

	for (int i = 0; i < a.rows; i++) hist[i].resize(a.cols);

	for (int i = 0; i < newmap.rows; i++)
	{
		for (int k = 0; k < newmap.cols; k++)
		{
			hist[i][k] = static_cast<int>(newmap.at<uchar>(i, k));
		}
	}

	hist = MedianCalculate(hist);

	for (int i = 0; i < newmap.rows; i++)
	{
		for (int k = 0; k < newmap.cols; k++)
		{
			newmap.at<uchar>(i, k) = static_cast<uchar>(hist[i][k]);
		}
	}

	return newmap;
}

void GaussianFilterCreation(vector<vector<double>> &GKernel, int kWidth, int kHeight)
{
	// Kernel Gauss có ma trận 3x3, 5x5, 7x7, 9x9,...
	GKernel.resize(kWidth);
	for (int i = 0; i < kWidth; i++) GKernel[i].resize(kHeight);
	
	double sigma = 1.0;
	double r, s = 2.0 * sigma * sigma;
	
	double sum = 0.0;
	// Khởi tạo kWidth x kHeight kernel
	for (int x = round(-kWidth/2); x <= round(kWidth/2); x++) {
		for (int y = round(-kHeight/2); y <= round(kHeight/2); y++) {
			r = x * x + y * y;
			GKernel[x + round(kWidth / 2)][y + round(kHeight / 2)] = (exp(-r / s)) / (3.14159 * s);
			sum += GKernel[x + round(kWidth / 2)][y + round(kHeight / 2)];
		}
	}
	// Chuẩn hoá the Kernel 
	for (int i = 0; i < kWidth; ++i)
		for (int j = 0; j < kHeight; ++j)
			GKernel[i][j] /= sum;
}

vector<vector<int>> GaussianCalculate(vector<vector<int>> ht, int kWidth, int kHeight)
{
	vector<vector<int>> hist;
	hist.resize(ht.size());

	for (int i = 0; i < hist.size(); i++) hist[i].resize(ht[i].size());
	hist = ht;
	vector <vector<double>> gauss;
	GaussianFilterCreation(gauss, kWidth, kHeight);
	
	for (int i = round(kWidth / 2); i < ht.size() - round(kWidth / 2); i++)
	{
		for (int k = round(kHeight / 2); k < ht[i].size() - round(kHeight / 2); k++)
		{
			double sum = 0;
			for (int s = round(-kWidth / 2); s <= round(kWidth / 2); s++)
			{
				for (int l = round(-kHeight / 2); l <= round(kHeight / 2); l++)
				{
					int fi = ht[i + s][k + l];
					sum += fi*gauss[s + round(kWidth / 2)][l + round(kWidth / 2)];
				}
			}
			hist[i][k] = round(sum);
		}
	}

	return hist;
}

Mat Gaussianfilter(const Mat a, int kWidth, int kHeight)
{
	Mat newmap = a.clone();

	vector<vector<int>> hist;

	hist.resize(a.rows);

	for (int i = 0; i < a.rows; i++) hist[i].resize(a.cols);

	for (int i = 0; i < newmap.rows; i++)
	{
		for (int k = 0; k < newmap.cols; k++)
		{
			hist[i][k] = static_cast<int>(newmap.at<uchar>(i, k));
		}
	}

	hist = GaussianCalculate(hist,kWidth,kHeight);

	for (int i = 0; i < newmap.rows; i++)
	{
		for (int k = 0; k < newmap.cols; k++)
		{
			newmap.at<uchar>(i, k) = static_cast<uchar>(hist[i][k]);
		}
	}

	return newmap;
}

int Blur::BlurImage(const Mat& sourceImage, Mat& destinationImage, int kWidth, int kHeight, int method)
{
	//0: Mean Filter
	//1: Median Filter
	//2: Gaussian Filter
	if (sourceImage.empty()) return 1;

	if (method == 0) destinationImage = Meanfilter(sourceImage, kWidth, kHeight);

	if (method == 1) destinationImage = Medianfilter(sourceImage, kWidth, kHeight);

	if (method == 2) destinationImage = Gaussianfilter(sourceImage, kWidth, kHeight);

	return 0;
}

Blur::Blur()
{
}

Blur::~Blur()
{
}
