#include "pch.h"
#include "EdgeDetector.h"
#include "Convolution.h"

int EdgeDetector::DetectEdge(const Mat & sourceImage, Mat & destinationImage, int kWidth, int kHeight, int method)
{
	if (sourceImage.empty()) //Kiểm tra hình đâu vào và thoát ra nếu lỗi
		return 0;

	Convolution conv;
	Mat fx, fy;
	vector<float> Wx = { -1/3, 0, 1/3,
						 -1/3, 0, 1/3,
						 -1/3, 0, 1/3};
	conv.SetKernel(Wx, 3, 3);
	
	int calCov = conv.DoConvolution(sourceImage, fx);

	if (calCov == 0)
		return 0;

	vector<float> Wy = { -1/3, -1/3, -1/3,
						  0, 0, 0,
						  1/3, 1/3, 1/3 };
	conv.SetKernel(Wy, 3, 3);
	
	calCov = conv.DoConvolution(sourceImage, fy);

	if (calCov == 0)
		return 0;
	return 0;
}

EdgeDetector::EdgeDetector()
{
}

EdgeDetector::~EdgeDetector()
{
}
