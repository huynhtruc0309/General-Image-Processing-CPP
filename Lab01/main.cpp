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
	temp[2] = _strdup("E:\\test1.png");
	temp[3] = _strdup("commandArgs");
	argv = temp;
#pragma endregion

	char* command, *inputPath;

	try
	{
		if (argc < 3)
		{
			//Print exception
			return 1;
		}

		command = argv[1];
		inputPath = argv[2];

		if (strcmp(command, "--rgb2gray") == 0)
		{

		}
		else if (strcmp(command, "--gray2rgb") == 0)
		{
		}
		else if (strcmp(command, "--rgb2hsv") == 0)
		{
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
		}
		else if (strcmp(command, "--contrast") == 0)
		{
			if (argc < 4)
			{
				throw "Missing parameter!";
			}
		}
		else if (strcmp(command, "--hist") == 0)
		{
		}
		else if (strcmp(command, "--equalhist") == 0)
		{
		}
		else if (strcmp(command, "--drawhist") == 0)
		{
			Mat input = imread(inputPath, IMREAD_COLOR);
			int isSuccess;

			ColorTransformer ColorTrans;
			Mat output;
			isSuccess = ColorTrans.HistogramVisualization(input, output);

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
		}
		else
		{
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