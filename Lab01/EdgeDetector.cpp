#include "pch.h"
#include "EdgeDetector.h"
#include "Convolution.h"
#include "Converter.h"
#include "Blur.h"

int EdgeDetector::DetectEdge(const Mat & sourceImage, Mat & destinationImage, int kWidth, int kHeight, int method)
{
	if (sourceImage.empty()) //Kiểm tra hình đâu vào và thoát ra nếu lỗi
		return 0;

	Mat blurImg, grayImg;

	//Khử nhiễu ảnh trước bằng Gaussian filter (kernel size = 3)
	GaussianBlur(sourceImage, blurImg, Size(3, 3), 0, 0, BORDER_DEFAULT);

	//Chuyển ảnh về dạng gray_scale
	cvtColor(blurImg, grayImg, COLOR_BGR2GRAY);


	if (method == 1) // Sobel Edge Detection
	{
		destinationImage.create(grayImg.size(), grayImg.type());
		vector<vector<int>> matrix;
		matrix.resize(grayImg.rows);
		for (int i = 0; i < grayImg.rows; i++)
		{// Lưu ma trận của ảnh sourceImage
			matrix[i].resize(grayImg.cols);
			for (int k = 0; k < grayImg.cols; k++)
			{
				matrix[i][k] = static_cast<int>(grayImg.at<uchar>(i, k));
			}
		}

		for (int i = 1; i < grayImg.rows - 1; i++)
		{// Tính toán theo mặt nạ Sobel để có được biên cạnh
			for (int k = 1; k < grayImg.cols - 1; k++)
			{
				int Gx = matrix[i - 1][k + 1] + 2 * matrix[i][k + 1] + matrix[i + 1][k + 1];
				Gx -=    matrix[i - 1][k - 1] + 2 * matrix[i][k - 1] + matrix[i + 1][k - 1];
				int Gy = matrix[i + 1][k - 1] + 2 * matrix[i + 1][k] + matrix[i + 1][k + 1];
				Gy -=    matrix[i - 1][k - 1] + 2 * matrix[i - 1][k] + matrix[i - 1][k + 1];
				
				float alpha = round(sqrt(Gx*Gx + Gy*Gy));// Có thể chọn alpha = |Gx| + |Gy|
				destinationImage.at<uchar>(i, k) = static_cast<uchar>(alpha);
			}
		}
	}
	
	else if (method == 2) // Prewitt Edge Detection
	{
		destinationImage.create(grayImg.size(), grayImg.type());
		vector<vector<int>> matrix;
		matrix.resize(grayImg.rows);
		for (int i = 0; i < grayImg.rows; i++)
		{// Lưu ma trận của ảnh sourceImage
			matrix[i].resize(grayImg.cols);
			for (int k = 0; k < grayImg.cols; k++)
			{
				matrix[i][k] = static_cast<int>(grayImg.at<uchar>(i, k));
			}
		}

		for (int i = 1; i < grayImg.rows - 1; i++)
		{// Tính toán theo mặt nạ Prewitt để có được biên cạnh
			for (int k = 1; k < grayImg.cols - 1; k++)
			{
				int Gx = matrix[i - 1][k + 1] + matrix[i][k + 1] + matrix[i + 1][k + 1];
				Gx -= matrix[i - 1][k - 1] + matrix[i][k - 1] + matrix[i + 1][k - 1];
				int Gy = matrix[i + 1][k - 1] + matrix[i + 1][k] + matrix[i + 1][k + 1];
				Gy -= matrix[i - 1][k - 1] + matrix[i - 1][k] + matrix[i - 1][k + 1];

				float alpha = round(sqrt(Gx*Gx + Gy * Gy));// Có thể chọn alpha = |Gx| + |Gy|
				destinationImage.at<uchar>(i, k) = static_cast<uchar>(alpha);
			}
		}
	}

	else if (method == 3) // Laplance Edge Detection
	{
		destinationImage.create(grayImg.size(), grayImg.type());
		vector<vector<int>> matrix;
		matrix.resize(grayImg.rows);
		for (int i = 0; i < grayImg.rows; i++)
		{// Lưu ma trận của ảnh sourceImage
			matrix[i].resize(grayImg.cols);
			for (int k = 0; k < grayImg.cols; k++)
			{
				matrix[i][k] = static_cast<int>(grayImg.at<uchar>(i, k));
			}
		}

		for (int i = 1; i < grayImg.rows - 1; i++)
		{// Tính toán theo mặt nạ Laplance để có được biên cạnh
			for (int k = 1; k < grayImg.cols - 1; k++)
			{
				int G = matrix[i + 1][k] + matrix[i - 1][k] + matrix[i][k + 1] + matrix[i][k - 1] - 4 * matrix[i][k];
				
				float alpha = round(sqrt(G));
				destinationImage.at<uchar>(i, k) = static_cast<uchar>(alpha);
			}
		}
	}
	
	return 1;
}

EdgeDetector::EdgeDetector()
{
}

EdgeDetector::~EdgeDetector()
{
}
