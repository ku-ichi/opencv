#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat A = imread("img.png");
	imshow("ǳ����Ա�",A);

	//ǳ�������޸�ABC����һ��Ӱ����������Mat
	Mat B(A);
	Mat C=A;

	//���
	Mat D = A.clone();
	Mat E;
	A.copyTo(E);

	//����һ�У���֤cols��ͬ����
	/*
	Mat src,dst��
	Mat insert = src.row();//��ȡһ��
	dst.push_back(insert);//��ӵ��ײ�
	*/
	








	waitKey(0);
}
