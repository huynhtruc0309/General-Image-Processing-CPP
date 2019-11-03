#include "pch.h"
#include "Converter.h"

int Converter::RGB2GrayScale(const Mat& sourceImage, Mat& destinationImage)
{
	return 0;
}

int Converter::GrayScale2RGB(const Mat& sourceImage, Mat& destinationImage)
{
	return 0;
}

int Converter::RGB2HSV(const Mat& sourceImage, Mat& destinationImage)
{
	return 0;
}

int Converter::HSV2RGB(const Mat& sourceImage, Mat& destinationImage)
{
	return 0;
}

int Converter::Convert(Mat& sourceImage, Mat& destinationImage, int type)
{
	switch (type)
	{
	case 0:
		return RGB2GrayScale(sourceImage, destinationImage);
		break;
	case 1:
		return GrayScale2RGB(sourceImage, destinationImage);
		break;
	case 2:
		return RGB2HSV(sourceImage, destinationImage);
		break;
	case 3:
		return HSV2RGB(sourceImage, destinationImage);
		break;
	default:
		break;
	}
	return 1;
}

int Converter::Convert(IplImage* sourceImage, IplImage* destinationImage, int type)
{
	return 0;
}

Converter::Converter()
{
}

Converter::~Converter()
{
}
