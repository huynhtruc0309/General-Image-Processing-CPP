#include "pch.h"
#include "ColorTransformer.h"

int ColorTransformer::ChangeBrighness(const Mat& sourceImage, Mat& destinationImage, short b)
{
	return 0;
}

int ColorTransformer::ChangeContrast(const Mat& sourceImage, Mat& destinationImage, float c)
{
	if (!sourceImage.data) {
		return 0;
	}
	destinationImage.create(sourceImage.size(), sourceImage.type());
	float r, g, b;
	int rows = sourceImage.rows;
	int cols = sourceImage.cols;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			b = (float)sourceImage.at<cv::Vec3b>(i, j)[0] * c;
			g = (float)sourceImage.at<cv::Vec3b>(i, j)[1] * c;
			r = (float)sourceImage.at<cv::Vec3b>(i, j)[2] * c;
			b = (b > 255) ? 255 : b;
			g = (g > 255) ? 255 : g;
			r = (r > 255) ? 255 : r;
			destinationImage.at<cv::Vec3b>(i, j)[0] = (uchar)b;
			destinationImage.at<cv::Vec3b>(i, j)[1] = (uchar)g;
			destinationImage.at<cv::Vec3b>(i, j)[2] = (uchar)r;
		}
	}

	return 1;
}

int ColorTransformer::HistogramEqualization(const Mat& sourceImage, Mat& destinationImage)
{
	return 0;
}

int ColorTransformer::HistogramVisualization(const Mat& sourceImage, Mat& destinationImage)
{
	if (sourceImage.empty()) //Kiểm tra hình đâu vào và thoát ra nếu lỗi
		return 0;
	
	vector<Mat> img_rgb; //Vector chứa các ma trận được tách ra theo channel màu

	int w = 512, h = 400; //Kích thước khung histogram
	int sizeHist = 256; //Kích thước của histogram
	split(sourceImage, img_rgb); //Tách thành các channel

	int red, green, blue;
	float histogram[3][256] = { 0 };
	for (int x = 0; x < sourceImage.cols; x++)
		for (int y = 0; y < sourceImage.rows; y++)
		{
			// truy xuất đến toạ độ ảnh ở kênh màu Blue
			blue = img_rgb[0].at<uchar>(y, x);
			histogram[0][blue]++;
			// truy xuất đến toạ độ ảnh ở kênh màu Green
			green = img_rgb[1].at<uchar>(y, x);
			histogram[1][green]++;
			// truy xuất đến toạ độ ảnh ở kênh màu Red
			red = img_rgb[2].at<uchar>(y, x);
			histogram[2][red]++;
		}
	
	//Chuyển mảng histogram vào Mat img_b, img_g, img_r
	Mat img_b(256, 1, CV_32F, histogram[0]);
	memcpy(img_b.data, histogram[0], 1 * 256 * sizeof(float));
	Mat img_g(256, 1, CV_32F, histogram[1]);
	memcpy(img_g.data, histogram[1], 1 * 256 * sizeof(float));
	Mat img_r(256, 1, CV_32F, histogram[2]);
	memcpy(img_r.data, histogram[2], 1 * 256 * sizeof(float));

	//Tạo ra một hình để hiện histogram
	int bin = cvRound((double)w / sizeHist);
	Mat histImage(h, w, CV_8UC3, Scalar(0, 0, 0));

	//Chuẩn hoá giá trị
	normalize(img_b, img_b, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(img_g, img_g, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(img_r, img_r, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	for (int i = 1; i < sizeHist; i++)
	{
		line(histImage, Point(bin*(i - 1), h - cvRound(img_b.at<float>(i - 1))),
			Point(bin*(i), h - cvRound(img_b.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point(bin*(i - 1), h - cvRound(img_g.at<float>(i - 1))),
			Point(bin*(i), h - cvRound(img_g.at<float>(i))),
			Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin*(i - 1), h - cvRound(img_r.at<float>(i - 1))),
			Point(bin*(i), h - cvRound(img_r.at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0);
	}

	destinationImage = histImage;

	cv::waitKey(0);
	return 1;
}

float ColorTransformer::CompareImage(const Mat& image1, Mat& image2)
{
	return 0.0f;
}

ColorTransformer::ColorTransformer()
{
}

ColorTransformer::~ColorTransformer()
{
}
