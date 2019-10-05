#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	//用Mat()构造
	Mat m(10, 10, CV_8UC3, Scalar(0, 0, 255));
	//CV_位数/有无符号/C/通道数
	//Scalar设置纯色背景	
	imshow("m", m);

	//用M.create，不能设定初值
	Mat m4;
	m4.create(2,2,CV_8UC3);

	//逐个赋值
	Mat m6 = (Mat_<double>(2, 2) << 1, 0, 0, 1);
	cout << m6 << endl;

	//构造函数初始化
	int size[2] = { 10,10 };//存放每个维度的尺寸
	Mat m2(2, size, CV_8UC3, Scalar::all(0));//指定维度
	imshow("m2", m2);

	//IplImage读入转为Mat
	IplImage* im1 = cvLoadImage("1.jpg", 1);
	Mat m3=cvarrToMat(im1);
	
	//Matlab式，eyes(单位矩阵)/ones/zeros
	Mat m5 = Mat::zeros(10, 10, CV_8UC3);
	
	//克隆
	Mat m7 = m6.row(1).clone();
	cout << m7 << endl;

	//二维点
	Point p;
		p.x = 2;
		p.y = 3;
	Point p2 = Point(2, 3);



	waitKey(0);
}