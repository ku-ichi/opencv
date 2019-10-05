//以线型混合为例
#include <opencv2/opencv.hpp>

using namespace cv;

//全局变量
const int MaxAlpha = 100;
int nowAlpha;
double proportion, rest;

//存储图像变量
Mat im1, im2, dst;

//回调函数
void on_trackbar(int, void*)
{
	proportion = (double)nowAlpha / MaxAlpha;
	rest = 1.0 - proportion;
	
	//参数5为偏差
	addWeighted(im1, proportion, im2, rest, 0.0, dst);
	imshow("线性混合", dst);	
}

int main()
{
	im1 = imread("ta.jpg");
	im2 = imread("lv.jpg");

	nowAlpha = 50;//初始化滑动条为50

	namedWindow("线性混合", 2);
	//滑动条标题
	char trackbarname[50];
	snprintf(trackbarname,sizeof(trackbarname), "透明度为：%d", MaxAlpha);

	//创建滑动条,滑动条名，窗口名，滑动条实时值，最大值，回调函数
	createTrackbar(trackbarname, "线性混合", &nowAlpha, MaxAlpha, on_trackbar);
	on_trackbar(nowAlpha, 0);

	waitKey(0);
	return 0;
}