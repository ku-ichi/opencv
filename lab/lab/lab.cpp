#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

	int iLowH = 100;
	int iHighH = 140;

	int iLowS = 90;
	int iHighS = 255;

	int iLowV = 90;
	int iHighV = 255;

	//Create trackbars in "Control" window
	cvCreateTrackbar("LowH", "Control", &iLowH, 180); //Hue (0 - 179)
	cvCreateTrackbar("HighH", "Control", &iHighH, 180);

	cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	cvCreateTrackbar("HighS", "Control", &iHighS, 255);

	cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
	cvCreateTrackbar("HighV", "Control", &iHighV, 255);

	while (true)
	{
		Mat imgOriginal;

		imgOriginal = imread("1.jpg");				//选择源图像

					

		Mat imgHSV;
		vector<Mat> hsvSplit;
		cvtColor(imgOriginal, imgHSV, COLOR_BGR2YUV); //Convert the captured frame from BGR to HSV
													  //因为我们读取的是彩色图，直方图均衡化需要在HSV空间做
		split(imgHSV, hsvSplit);
		equalizeHist(hsvSplit[0], hsvSplit[0]);
		merge(hsvSplit, imgHSV);
		Mat imgThresholded;

		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

		//开操作 (去除一些噪点)
		Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
		morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);

		//闭操作 (连接一些连通域)
		morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);

		imshow("Thresholded Image", imgThresholded); //输入图像
		imshow("Original", imgOriginal); //输出图像

		char key = (char)waitKey(300);
		if (key == 27)
			break;
	}
	
}