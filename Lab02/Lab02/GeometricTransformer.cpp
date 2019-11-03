#include "pch.h"
#include "GeometricTransformer.h"

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
}

void AffineTransform::Rotate(float angle)
{
}

void AffineTransform::Scale(float sx, float sy)
{
}

void AffineTransform::TransformPoint(float & x, float & y)
{
}

AffineTransform::AffineTransform()
{
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

PixelInterpolate::PixelInterpolate()
{
}

PixelInterpolate::~PixelInterpolate()
{
}
