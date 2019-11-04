#include "pch.h"
#include "GeometricTransformer.h"

PixelInterpolate::PixelInterpolate()
{
}

PixelInterpolate::~PixelInterpolate()
{
}

//Lớp nội suy màu theo phương pháp song tuyến tính

uchar BilinearInterpolate::Interpolate(float tx, float ty, uchar * pSrc, int srcWidthStep, int nChannels)
{
	uchar *pDst;
	int l = round(tx), r = round(ty);
	float a = tx - l, b = ty - r;
	
	uchar * pSrcRow0 = pSrc + (l * srcWidthStep + r * nChannels);				// f(l, r)  
	uchar * pSrcRow1 = pSrc + ((l + 1) * srcWidthStep + r * nChannels);			// f(l + 1, r)
	uchar * pSrcRow2 = pSrc + (l * srcWidthStep + (r + 1) * nChannels);			// f (l, r + 1)
	uchar * pSrcRow3 = pSrc + ((l + 1) * srcWidthStep + (r + 1) * nChannels);	// f(l + 1, r + 1)
	
	// r, g, b interpolation
	for (int i = 0; i < nChannels; i++)
		pDst[i] = saturate_cast<uchar>((1 - a)*(1 - b)*pSrcRow0[i] + a * (1 - b)*pSrcRow1[i] + b * (1 - a)*pSrcRow2[i] + a * b*pSrcRow3[i]);
	
	return *pDst;
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

uchar NearestNeighborInterpolate::Interpolate(float tx, float ty, uchar * pSrc, int srcWidthStep, int nChannels)
{	
	uchar *pDst;
	int x = (int)tx, y = (int)ty;
	uchar * pSrcRow = pSrc + (x * srcWidthStep + y * nChannels);

	for (int i = 0; i < nChannels; i++)
		pDst[i] = pSrcRow[i];
	
	return *pDst;
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
	if (beforeImage.empty())
		return 0;

	//w_src : chiều rộng ảnh nguồn, h_src : chiều cao ảnh nguồn
	//w_dst : chiều rộng ảnh đích, h_dst : chiều cao ảnh đích
	int w_src = beforeImage.cols, h_src = beforeImage.rows;
	int w_dst = afterImage.cols, h_dst = afterImage.rows;

	int nChannels = beforeImage.channels(); // 

	// khoang cach giữa 2 px cùng cột 2 dong liên tiếp
	int w_srcStep = beforeImage.step[0];
	int w_dstStep = afterImage.step[0];

	uchar* res = (uchar*)afterImage.data;
	uchar* src = (uchar*)beforeImage.data;

	for (int i = 0; i < h_dst; i++, res += w_srcStep)
	{
		
		uchar* pRes = res; // con tro dong anh dich

		for (int j = 0; j < w_dst; j++, pRes += nChannels)
		{
			float x = i;
			float y = j;
			transformer->TransformPoint(x, y);

			if (round(x) < h_src && round(y) < w_src)
				pRes[j] = interpolator->Interpolate(x, y, src, w_srcStep, nChannels);
		}
			
	}

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
