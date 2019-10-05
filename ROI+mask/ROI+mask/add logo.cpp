#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
	Mat bg = imread("bg.jpg");
	Mat logo = imread("logo.png");

	//设定ROI区域
	Mat Roi = bg(Rect(500, 200, logo.cols, logo.rows));

	Mat mask = imread("logo.png", 0);
	//把logo在mask的那部分复制到ROI图上
	logo.copyTo(Roi, mask);
	imshow("restult", bg);

	waitKey(0);
	return 0;

}