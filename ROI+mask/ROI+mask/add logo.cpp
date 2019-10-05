#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
	Mat bg = imread("bg.jpg");
	Mat logo = imread("logo.png");

	//�趨ROI����
	Mat Roi = bg(Rect(500, 200, logo.cols, logo.rows));

	Mat mask = imread("logo.png", 0);
	//��logo��mask���ǲ��ָ��Ƶ�ROIͼ��
	logo.copyTo(Roi, mask);
	imshow("restult", bg);

	waitKey(0);
	return 0;

}