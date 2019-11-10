
#include "Convolution.h"

vector<float> Convolution::GetKernel()
{
	return this->_kernel;
}

void Convolution::SetKernel(vector<float> kernel, int kWidth, int kHeight)
{
	this->_kernelWidth = kWidth;
	this->_kernelHeight = kHeight;
	copy(kernel.begin(), kernel.end(), back_inserter(this->_kernel));
}

int Convolution::DoConvolution(const Mat & sourceImage, Mat & destinationImage)
{
	if (sourceImage.empty())
	{
		return 1;
	}

	int rows = sourceImage.rows;
	int cols = sourceImage.cols;

	//Tính toạ độ bắt đầu của kernel
	//kernel=3x3 -> iStart=-1, jstart=-1
	int iStart = -_kernelWidth / 2;
	int jStart = -_kernelHeight / 2;

	//Khởi tạo ma trận kết quả
	Mat res(rows, cols, CV_32F);

	//Duyệt từng điểm của ảnh gốc
	for (int x = 0; x < cols; x++)
	{
		for (int y = 0; y < rows; y++)
		{
			float val = 0;
			//Duyệt qua từng phần tử của _kernel
			for (int k = 0; k < _kernel.size(); k++)
			{
				//Vì _kernel là mảng 1 chiều
				//nên cần quy đổi về toạ độ trong mảng 2 chiều để tính toán
				int i = iStart + k % _kernelWidth;
				int j = jStart + k / _kernelWidth;

				//Tính toạ độ điểm ảnh tương ứng để nhân với _kernel(i,j)
				int r = y - j;
				int c = x - i;

				//Nếu điểm ảnh vượt quá biên thì không cần tính
				if (r < 0 || r >= rows || c < 0 || c >= cols)
					continue;
				
				val += sourceImage.at<uchar>(r, c) * _kernel[k];
			}
			res.at<float>(y, x) = val;
		}
	}

	destinationImage = res;
	return 0;
}

Convolution::Convolution()
{
	this->_kernelWidth = 0;
	this->_kernelHeight = 0;
}

Convolution::~Convolution()
{
}
