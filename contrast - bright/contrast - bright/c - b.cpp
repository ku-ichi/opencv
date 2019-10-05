#include<opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

static void on_ContrastandBright(int,void *);

int contrast;
int bright;
Mat src, dst;

int main()
{
	src = imread("1.jpg");
	dst = Mat::zeros(src.size(), src.type());

	//初始化
	contrast = 80;
	bright = 80;

	namedWindow("效果图", 1);

	//创建滑动条
	createTrackbar("对比度:", "效果图", &contrast, 300, on_ContrastandBright);
	createTrackbar("亮度:", "效果图", &bright, 200, on_ContrastandBright);

	on_ContrastandBright(contrast, 0);
	on_ContrastandBright(bright, 0);

	waitKey(0);
	return 0;
}

static void on_ContrastandBright(int, void*)
{
	for (int y = 0; y < src.rows; y++)
	{
		for (int x = 0; x < src.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				dst.at<Vec3b>(y, x)[c] = saturate_cast<char>((contrast*0.01)*(src.at<Vec3b>(y, x)[c]) + bright);

			}
		}
	}
	imshow("效果图",dst);
}