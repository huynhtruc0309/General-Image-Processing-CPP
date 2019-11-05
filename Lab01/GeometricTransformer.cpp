#include "pch.h"
#include "GeometricTransformer.h"

PixelInterpolate::PixelInterpolate()
{
}

PixelInterpolate::~PixelInterpolate()
{
}

//Lớp nội suy màu theo phương pháp song tuyến tính

uchar BilinearInterpolate::Interpolate(float tx, float ty, uchar * pSrc, int srcWidthStep, int nChannels, int xChannel)
{
	int l = (int)round(tx), k = (int)round(ty);
	int a = abs(l - tx), b = abs(ty - k);

	return (1 - a)*(1 - b)*(int)pSrc[srcWidthStep * k + nChannels * l + xChannel] + a * (1 - b) *pSrc[srcWidthStep * k + nChannels * (l + 1) + xChannel]
		+ b * (1 - a)*pSrc[srcWidthStep * (k + 1) + nChannels * l + xChannel] + a * b*pSrc[srcWidthStep * (k + 1) + nChannels * (l + 1) + xChannel];
}

BilinearInterpolate::BilinearInterpolate()
{
}

BilinearInterpolate::~BilinearInterpolate()
{
}

/*
Lớp nội suy màu theo phương pháp láng giềng gần nhất
*/

uchar NearestNeighborInterpolate::Interpolate(float tx, float ty, uchar * pSrc, int srcWidthStep, int nChannels, int xChannel)
{	
	return pSrc[srcWidthStep * (int)round(ty) + nChannels * (int)round(tx) + xChannel];
}

NearestNeighborInterpolate::NearestNeighborInterpolate()
{
}

NearestNeighborInterpolate::~NearestNeighborInterpolate()
{
}

void AffineTransform::Translate(float dx, float dy)
{
	float matrix[3][3] = { {1, 0 , dx},
						   {0, 1, dy},
						   {0, 0, 1} };
	this->_matrixTransform = Mat(3, 3, CV_32F, matrix);
}

void AffineTransform::Rotate(float angle)
{
	float matrix[3][3] = { {cos(angle), -sin(angle) , 0},
						   {sin(angle), cos(angle), 0},
						   {0, 0, 1} };
	this->_matrixTransform = Mat(3, 3, CV_32F, matrix);
}

void AffineTransform::Scale(float sx, float sy)
{
	float matrix[3][3] = { {sx, 0 , 0},
						   {0, sy, 0},
						   {0, 0, 1} };
	this->_matrixTransform = Mat(3, 3, CV_32F, matrix);
}

void AffineTransform::TransformPoint(float & x, float & y)
{
	x = this->_matrixTransform.at<float>(0, 0)*x + this->_matrixTransform.at<float>(0, 1)*y + this->_matrixTransform.at<float>(0, 2);
	y = this->_matrixTransform.at<float>(1, 0)*x + this->_matrixTransform.at<float>(1, 1)*y + this->_matrixTransform.at<float>(1, 2);
}

AffineTransform::AffineTransform()
{
	float matrix[3][3] = { 0 };
	this->_matrixTransform = Mat(3, 3, CV_32F, matrix);
}

AffineTransform::~AffineTransform()
{
}

int GeometricTransformer::Transform(const Mat & beforeImage, Mat & afterImage, AffineTransform * transformer, PixelInterpolate * interpolator)
{
	//if (beforeImage.empty())
	//	return 0;

	//w_src : chiều rộng ảnh nguồn, h_src : chiều cao ảnh nguồn
	//w_dst : chiều rộng ảnh đích, h_dst : chiều cao ảnh đích
	//int w_src = beforeImage.cols, h_src = beforeImage.rows;
	//int w_dst = afterImage.cols, h_dst = afterImage.rows;

	//int nChannels = beforeImage.channels(); // 

	// khoang cach giữa 2 px cùng cột 2 dong liên tiếp
	//int w_srcStep = beforeImage.step[0];
	//int w_dstStep = afterImage.step[0];

	//uchar* res = (uchar*)afterImage.data;
	//uchar* src = (uchar*)beforeImage.data;

	//for (int i = 0; i < h_dst; i++, res += w_srcStep)
	//{
	//	
	//	uchar* pRes = res; // con tro dong anh dich

	//	for (int j = 0; j < w_dst; j++, pRes += nChannels)
	//	{
	//		float x = i;
	//		float y = j;
	//		transformer->TransformPoint(x, y);

	//		if (round(x) < h_src && round(y) < w_src)
	//			interpolator->Interpolate(x, y, src, w_srcStep, nChannels, pRes);
	//	}
	//		
	//}
	return 1;
}

int GeometricTransformer::RotateKeepImage(const Mat & srcImage, Mat & dstImage, float angle, PixelInterpolate * interpolator)
{

	return 0;
}

int GeometricTransformer::RotateUnkeepImage(const Mat & srcImage, Mat & dstImage, float angle, PixelInterpolate * interpolator)
{
	return 0;
}

int GeometricTransformer::Scale(const Mat & srcImage, Mat & dstImage, float sx, float sy, PixelInterpolate * interpolator)
{
	return 0;
}

int GeometricTransformer::Resize(const Mat & srcImage, Mat & dstImage, int newWidth, int newHeight, PixelInterpolate * interpolator)
{
	return 0;
}

int GeometricTransformer::Flip(const Mat & srcImage, Mat & dstImage, bool direction, PixelInterpolate * interpolator)
{
	return 0;
}

GeometricTransformer::GeometricTransformer()
{
}

GeometricTransformer::~GeometricTransformer()
{
}
