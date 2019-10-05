#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	//��Mat()����
	Mat m(10, 10, CV_8UC3, Scalar(0, 0, 255));
	//CV_λ��/���޷���/C/ͨ����
	//Scalar���ô�ɫ����	
	imshow("m", m);

	//��M.create�������趨��ֵ
	Mat m4;
	m4.create(2,2,CV_8UC3);

	//�����ֵ
	Mat m6 = (Mat_<double>(2, 2) << 1, 0, 0, 1);
	cout << m6 << endl;

	//���캯����ʼ��
	int size[2] = { 10,10 };//���ÿ��ά�ȵĳߴ�
	Mat m2(2, size, CV_8UC3, Scalar::all(0));//ָ��ά��
	imshow("m2", m2);

	//IplImage����תΪMat
	IplImage* im1 = cvLoadImage("1.jpg", 1);
	Mat m3=cvarrToMat(im1);
	
	//Matlabʽ��eyes(��λ����)/ones/zeros
	Mat m5 = Mat::zeros(10, 10, CV_8UC3);
	
	//��¡
	Mat m7 = m6.row(1).clone();
	cout << m7 << endl;

	//��ά��
	Point p;
		p.x = 2;
		p.y = 3;
	Point p2 = Point(2, 3);



	waitKey(0);
}