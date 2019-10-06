#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

//�˴���������HSVΪYUV
int main()
{
	namedWindow("Control", CV_WINDOW_AUTOSIZE);
	int iLowH = 0;
	int iHighH = 255;
	int iLowS = 0;
	int iHighS = 255;
	int iLowV = 0;
	int iHighV = 255;
	
	cvCreateTrackbar("LowH", "Control", &iLowH, 255); //����0-255
	cvCreateTrackbar("HighH", "Control", &iHighH, 255);
	cvCreateTrackbar("LowS", "Control", &iLowS, 255); 
	cvCreateTrackbar("HighS", "Control", &iHighS, 255);
	cvCreateTrackbar("LowV", "Control", &iLowV, 255); 
	cvCreateTrackbar("HighV", "Control", &iHighV, 255);

	while (true)
	{
		Mat imgOriginal;
		imgOriginal = imread("1.jpg");				//ѡ��Դͼ��

		Mat imgHSV;
		vector<Mat> hsvSplit;
		cvtColor(imgOriginal, imgHSV, COLOR_BGR2YUV);//��Ϊ���Ƕ�ȡ���ǲ�ɫͼ��ֱ��ͼ���⻯��Ҫ�Ҷ���
		split(imgHSV, hsvSplit);
		equalizeHist(hsvSplit[0], hsvSplit[0]);
		merge(hsvSplit, imgHSV);
		
		Mat imgThresholded;
		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

		//������ (ȥ��һЩ���)
		Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
		morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);

		//�ղ��� (����һЩ��ͨ��)
		morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);

		imshow("Thresholded Image", imgThresholded); //����ͼ��
		imshow("Original", imgOriginal); //���ͼ��

				
		//�����ɫ����ɫ����ͼ��
		char key = (char)waitKey(300);
		if (key == 27)
		{
			//imwrite("blue.jpg", imgThresholded);
			break;
		}
			
	}
	
}