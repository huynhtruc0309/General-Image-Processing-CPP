#include "pch.h"
#include "GeometricTransformer.h"

PixelInterpolate::PixelInterpolate()
{
}

PixelInterpolate::~PixelInterpolate()
{
}

uchar BilinearInterpolate::Interpolate(float tx, float ty, uchar * pSrc, int srcWidthStep, int nChannels)
{
	return uchar();
}

BilinearInterpolate::BilinearInterpolate()
{
}

BilinearInterpolate::~BilinearInterpolate()
{
}

uchar NearestNeighborInterpolate::Interpolate(float tx, float ty, uchar * pSrc, int srcWidthStep, int nChannels)
{
	return uchar();
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
	return 0;
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
