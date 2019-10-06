#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;
int main()
{
	//������С��Ӿ��εĻ���
	Mat srcImg = imread("blue.jpg");//��������Ϊ0������255
	namedWindow("scr", 0);
	imshow("scr", srcImg);
	Mat dstImg = srcImg.clone();
	cvtColor(srcImg, srcImg, CV_BGR2GRAY);
	threshold(srcImg, srcImg, 0, 255, CV_THRESH_OTSU + CV_THRESH_BINARY_INV); //��ֵ��
	bitwise_not(srcImg, srcImg);//��ɫ
	//medianBlur(srcImg, srcImg, 9);
	imshow("threshold", srcImg);

	vector<vector<Point>> contours;
	findContours(srcImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);//��������������ڲ��Ķ�
	Rect boundRect;  //�������������
	RotatedRect box; //������С���б����

	vector<vector<Point>>::iterator itc = contours.begin();//�õ�������ָ��
	Point2f rect_point[4];
	int i = 0;
	for (; itc != contours.end(); itc++)
	{
		box = minAreaRect(Mat(*itc));  //����ÿ��������С��Ӿ���(��ת)
		boundRect = box.boundingRect();
		//boundRect = boundingRect(Mat(*itc));
		circle(dstImg, Point(box.center.x, box.center.y), 5, Scalar(0, 0, 255), -1, 8);  //������С��Ӿ��ε����ĵ�
	   // rectangle(dstImg, Point(boundRect.x, boundRect.y), Point(boundRect.x + boundRect.width, boundRect.y + boundRect.height), Scalar(0, 255, 0), 2, 8);
		rectangle(dstImg, boundRect.tl(), boundRect.br(), Scalar(0, 255, 0), 3, 8);//topleft,bottom right
		box.points(rect_point);  //����С��Ӿ����ĸ��˵㸴�Ƹ�rect����
		for (int j = 0; j < 4; j++)
		{
			line(dstImg, rect_point[j], rect_point[(j + 1) % 4], Scalar(0, 0, 255), 3, 8);  //������С��Ӿ���ÿ����
		}
		cout << "center x:" << box.center.x << endl;
		cout << "center y:" << box.center.y << endl;
		cout << "angle " << i << " :" << box.angle << endl;
		cout << "width " << i << " :" << box.size.width << endl;
		cout << "height " << i << " :" << box.size.height << endl << endl;
		char width[20], height[20], x[20], y[20];
		snprintf(width, sizeof(width),"width=%0.2f", box.size.width);
		snprintf(height, sizeof(height), "height=%0.2f", box.size.height);
		snprintf(x, sizeof(x), "center.x=%0.2f", box.center.x);
		snprintf(y, sizeof(y), "center.y=%0.2f", box.center.y);
		putText(dstImg, width, box.center+ Point2f(-250,-20), CV_FONT_HERSHEY_COMPLEX_SMALL, 0.85, Scalar(255, 0, 0));//����������Ϊ�ı������½�
		putText(dstImg, height, box.center + Point2f(-250, 0), CV_FONT_HERSHEY_COMPLEX_SMALL, 0.85, Scalar(255, 0, 0));
		putText(dstImg, x, box.center + Point2f(-250, 20), CV_FONT_HERSHEY_COMPLEX_SMALL, 0.85, Scalar(255, 0, 0));
		putText(dstImg, y, box.center + Point2f(-250, 40), CV_FONT_HERSHEY_COMPLEX_SMALL, 0.85, Scalar(255, 0, 0));

	}
	namedWindow("rec_dst", 0);
	imshow("rec_dst", dstImg);


	//��תУ��
	float angle_rotation;
	if ((box.size.width / box.size.height) < 1)
		angle_rotation = 90 + box.angle;//��������ʱ����ת
	else
		angle_rotation = box.angle; //������˳ʱ����ת

	double scale = 0.78;//���ű���
	Mat rot_m = getRotationMatrix2D(box.center, angle_rotation, scale);//�����ת����
	warpAffine(dstImg, dstImg, rot_m, dstImg.size());//����任

	namedWindow("dst", 0);
	imshow("dst", dstImg);

	waitKey(0);
}
