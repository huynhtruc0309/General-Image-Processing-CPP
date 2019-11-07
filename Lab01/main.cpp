#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include "Converter.h"
#include "ColorTransformer.h"
#include <string.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
#pragma region ONLY_FOR_DEBUG
	argc = 4;
	char* temp[4];
	temp[0] = _strdup("Lab01.exe");
	temp[1] = _strdup("--drawhist");
	temp[2] = _strdup("E:\\Lenna_gray.png");
	temp[3] = _strdup("commandArgs");
	argv = temp;
#pragma endregion

	char* command, *inputPath, *interpolate, *cmdArguments;

	try
	{
		if (argc < 3)
		{
			//Print exception
			throw "Missing parameter!";
		}

		command = argv[1];

		// Command in LAB 1
		if (strcmp(command, "--rgb2gray") == 0)
		{
			inputPath = argv[2];
		}
		else if (strcmp(command, "--gray2rgb") == 0)
		{
			inputPath = argv[2];
		}
		else if (strcmp(command, "--rgb2hsv") == 0)
		{
			inputPath = argv[2];

			Mat input = imread(inputPath, IMREAD_COLOR);
			Mat output;

			Converter converter;
			int isSuccess = converter.Convert(input, output, 2);

			if (isSuccess == 0)
			{
				namedWindow("RGB to HSV");
				imshow("RGB to HSV", output);
				waitKey(0);
			}
			else
			{
				throw "Error:..........";
			}
		}
		else if (strcmp(command, "--hsv2rgb") == 0)
		{
			inputPath = argv[2];

			Mat input = imread(inputPath, IMREAD_COLOR);
			Mat output;

			Converter converter;
			int isSuccess = converter.Convert(input, output, 3);

			if (isSuccess == 0)
			{
				namedWindow("HSV to RGB");
				imshow("HSV to RGB", output);
				waitKey(0);
			}
			else
			{
				throw "Error:..........";
			}
		}
		else if (strcmp(command, "--bright") == 0)
		{
			if (argc < 4)
			{
				throw "Missing parameter!";
			}

			inputPath = argv[2];
		}
		else if (strcmp(command, "--contrast") == 0)
		{
			if (argc < 4)
			{
				throw "Missing parameter!";
			}

			inputPath = argv[2];
		}
		else if (strcmp(command, "--hist") == 0)
		{
			inputPath = argv[2];

			Mat input = imread(inputPath, IMREAD_COLOR);
			int isSuccess;

			ColorTransformer ColorTrans;
			Mat hist, output;
			isSuccess = ColorTrans.CalcHistogram(input, hist);

			if (isSuccess == 1)
			{
				namedWindow("Source Image", 0);
				imshow("Source Image", input);

				namedWindow("Histogram Calculation");
				imshow("Histogram Calculation", output);
				waitKey(0);
			}
			else
			{
				throw "Error:..........";
			}
		}
		else if (strcmp(command, "--equalhist") == 0)
		{
			inputPath = argv[2];
		}
		else if (strcmp(command, "--drawhist") == 0)
		{
			inputPath = argv[2];

			Mat input = imread(inputPath, IMREAD_COLOR);
			int isSuccess;

			ColorTransformer ColorTrans;
			Mat hist, output;
			isSuccess = ColorTrans.CalcHistogram(input, hist);

			if (isSuccess == 1)
				isSuccess = ColorTrans.DrawHistogram(hist, output);

			if (isSuccess == 1)
			{
				namedWindow("Source Image", 0);
				imshow("Source Image", input);

				namedWindow("Histogram Visualization");
				imshow("Histogram Visualization", output);
				waitKey(0);
			}
			else
			{
				throw "Error:..........";
			}
		}
		else if (strcmp(command, "--compare") == 0)
		{
			inputPath = argv[2];
		}
		//Command in LAB 2
		else if (strcmp(command, "--zoom") == 0)
			{
				if (argc < 5)
				{
					throw "Missing parameter!";
				}
				// khởi tạo mặc định 
				Mat srcImg, dstImg;
				GeometricTransformer GTF;
				PixelInterpolate *pxInterpolate;
				int res = 0;

				interpolate = argv[2];
				inputPath = argv[3];
				//-----------------------------------------------
				float sx = atof(argv[4]); //zoom theo x 
				float sy = atof(argv[5]); //zoom theo y

				// zoom = scale

				if (Interpolate == "--bl")
				{
					pxInterpolate = new BilinearInterpolate();
					res = GTf.Scale(srcImg, dstImg, sx, sy, pxInterpolate);
				}
				else
				{
					pxInterpolate = new NearestNeighborInterpolate();
					res = GTf.Scale(srcImg, dstImg, sx, sy, pxInterpolate);
				}

				//in kết quả
				if (res)
				{
					imshow("Source Image", srcImg);
					imshow("Destination Image", dstImg);
					waitKey(0);
				}
				else
				{
					throw "Error:..........";
				}
				//----------------------------------
			}
			else if (strcmp(command, "--resize") == 0)
			{
				if (argc < 5)
				{
					throw "Missing parameter!";
				}
				// khởi tạo mặc định 
				Mat srcImg, dstImg;
				GeometricTransformer GTF;
				PixelInterpolate *pxInterpolate;
				int res = 0;

				interpolate = argv[2];
				inputPath = argv[3];
				//-----------------------------------------------
				int newWidth = stoi(argv[4]); // kích thước mới 
				int newHeight = stoi(argv[5]); 

				if (Interpolate == "--bl")
				{
					pxInterpolate = new BilinearInterpolate();
					res = GTf.Resize(srcImg, dstImg, newWidth, newHeight, pxInterpolate);
				}
				else
				{
					pxInterpolate = new NearestNeighborInterpolate();
					res = GTf.Resize(srcImg, dstImg, newWidth, newHeight, pxInterpolate);
				}

				//in kết quả
				if (res)
				{
					imshow("Source Image", srcImg);
					imshow("Destination Image", dstImg);
					waitKey(0);
				}
				else
				{
					throw "Error:..........";
				}
				//----------------------------------

			}
			else if (strcmp(command, "--rotate") == 0)
			{
				if (argc < 5)
				{
					throw "Missing parameter!";
				}
				// khởi tạo mặc định 
				Mat srcImg, dstImg;
				GeometricTransformer GTF;
				PixelInterpolate *pxInterpolate;
				int res = 0;

				interpolate = argv[2];
				inputPath = argv[3];
				//-----------------------------------------------

				float angle = atof(argv[4]);  // góc xoay
				if (Interpolate == "--bl")
				{
					pxInterpolate = new BilinearInterpolate();
					res = GTf.RotateKeepImage(srcImg, dstImg, angle, pxInterpolate);
				}
				else
				{
					pxInterpolate = new NearestNeighborInterpolate();
					res = GTf.RotateKeepImage(srcImg, dstImg, angle, pxInterpolate);
				}

				//in kết quả
				if (res)
				{
					imshow("Source Image", srcImg);
					imshow("Destination Image", dstImg);
					waitKey(0);
				}
				else
				{
					throw "Error:..........";
				}
				//----------------------------------

			}
			else if (strcmp(command, "--rotateN") == 0)
			{
				if (argc < 5)
				{
					throw "Missing parameter!";
				}
				// khởi tạo mặc định 
				Mat srcImg, dstImg;
				GeometricTransformer GTF;
				PixelInterpolate *pxInterpolate;
				int res = 0;

				interpolate = argv[2];
				inputPath = argv[3];
				//-----------------------------------------------

				float angle = atof(argv[4]);  // góc xoay
				if (Interpolate == "--bl")
				{
					pxInterpolate = new BilinearInterpolate();
					res = GTf.RotateUnkeepImage(srcImg, dstImg, angle, pxInterpolate);
				}
				else
				{
					pxInterpolate = new NearestNeighborInterpolate();
					res = GTf.RotateUnkeepImage(srcImg, dstImg, angle, pxInterpolate);
				}
				//in kết quả
				if (res)
				{
					imshow("Source Image", srcImg);
					imshow("Destination Image", dstImg);
					waitKey(0);
				}
				else
				{
					throw "Error:..........";
				}
				//----------------------------------
			}
			else if (strcmp(command, "--flip") == 0)
			{
				if (argc < 5)
				{
					throw "Missing parameter!";
				}
				// khởi tạo mặc định 
				Mat srcImg, dstImg;
				GeometricTransformer GTF;
				PixelInterpolate *pxInterpolate;
				int res = 0;

				interpolate = argv[2];
				inputPath = argv[3];
				//-----------------------------------------------

				bool direction = (argv[4]);  // string to bool :)) 
				if (Interpolate == "--bl")
				{
					pxInterpolate = new BilinearInterpolate();
					res = GTf.Flip(srcImg, dstImg, direction, pxInterpolate);
				}
				else
				{
					pxInterpolate = new NearestNeighborInterpolate();
					res = GTf.Flip(srcImg, dstImg, direction, pxInterpolate);
				}

				if (res)
				{
					imshow("Source Image", srcImg);
					imshow("Destination Image", dstImg);
					waitKey(0);
				}
				else
				{
					throw "Error:..........";
				}
			}

		//Command in LAB 3
		else if (strcmp(command, "--mean") == 0)
		{
			if (argc < 4)
			{
				throw "Missing parameter!";
			}
			inputPath = argv[2];
			cmdArguments = argv[3];
		}
		else if (strcmp(command, "--median") == 0)
		{
			if (argc < 4)
			{
				throw "Missing parameter!";
			}
			inputPath = argv[2];
			cmdArguments = argv[3];
		}
		else if (strcmp(command, "--gauss") == 0)
		{
			if (argc < 4)
			{
				throw "Missing parameter!";
			}
			inputPath = argv[2];
			cmdArguments = argv[3];
		}
		else if (strcmp(command, "--sobel") == 0)
		{
			inputPath = argv[2];
		}
		else if (strcmp(command, "--prewitt") == 0)
		{
			inputPath = argv[2];
		}
		else if (strcmp(command, "--laplace") == 0)
		{
			inputPath = argv[2];
		}
	}
	catch (const char* msg)
	{
		cout << msg << endl;
		system("pause");
	}


#pragma region ONLY_FOR_DEBUG
	free(temp[0]);
	free(temp[1]);
	free(temp[2]);
	free(temp[3]);
#pragma endregion

	//system("pause");
	return 0;
}
