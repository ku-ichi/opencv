#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

//此代码中所有HSV为YUV
int main()
{
	namedWindow("Control", CV_WINDOW_AUTOSIZE);
	int iLowH = 0;
	int iHighH = 255;
	int iLowS = 0;
	int iHighS = 255;
	int iLowV = 0;
	int iHighV = 255;
	
	cvCreateTrackbar("LowH", "Control", &iLowH, 255); //亮度0-255
	cvCreateTrackbar("HighH", "Control", &iHighH, 255);
	cvCreateTrackbar("LowS", "Control", &iLowS, 255); 
	cvCreateTrackbar("HighS", "Control", &iHighS, 255);
	cvCreateTrackbar("LowV", "Control", &iLowV, 255); 
	cvCreateTrackbar("HighV", "Control", &iHighV, 255);

	while (true)
	{
		Mat imgOriginal;
		imgOriginal = imread("1.jpg");				//选择源图像

		Mat imgHSV;
		vector<Mat> hsvSplit;
		cvtColor(imgOriginal, imgHSV, COLOR_BGR2YUV);//因为我们读取的是彩色图，直方图均衡化需要灰度中
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

				
		//输出红色和蓝色方块图像
		char key = (char)waitKey(300);
		if (key == 27)
		{
			//imwrite("blue.jpg", imgThresholded);
			break;
		}
			
	}
	
}