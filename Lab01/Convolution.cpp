#include "pch.h"
#include "Convolution.h"

vector<float> Convolution::GetKernel()
{
	return this->_kernel;
}

void Convolution::SetKernel(vector<float> kernel, int kWidth, int kHeight)
{
	this->_kernel = kernel;
	this->_kernelHeight = kHeight;
	this->_kernelWidth = kWidth;
}

int Convolution::DoConvolution(const Mat & sourceImage, Mat & destinationImage)
{
	//int height = sourceImage.row, width = sourceImage.col;
	//int nChannel = sourceImage.channels();

	//int row = this->_kernelWidth, col = this->_kernelHeight;

	//for (int y = 0; y < height; y++)
	//{
	//	lấy con trỏ đầu mỗi dòng
	//	uchar* desRow = (uchar*)destinationImage.ptr<uchar>(y);

	//	for (int x = 0; x < width; x++, desRow+= nChannel)
	//	{
	//		truy xuất đến toạ độ (x,y) của 1 pixel
	//		for (int i = 0; i < row; i++)
	//		{
	//			for (int j = 0; j < height; j++)
	//			{
	//				desRow[0] += srcRow[0];//truy xuất pixel (x,y) channel thứ 0
	//				desRow[1] = ...;//truy xuất pixel (x,y) channel thứ 1
	//				desRow[2] = ...;//truy xuất pixel (x,y) channel thứ 2
	//			}
	//		}
	//	}
	//}

	return 0;
}

Convolution::Convolution()
{
}

Convolution::~Convolution()
{
}
