#include <opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main()
{
	//��ͼƬ��20*20
	Mat src = imread("digits.png");
	Mat gray;
	cvtColor(src, gray, CV_BGR2GRAY);
	int b = 20;
	int m = gray.rows / b;   //ÿһ��ͼƬ�ĸ���
	int n = gray.cols / b;   //ÿһ��ͼƬ�ĸ���
	Mat data, labels;   //��������???��̫��
	for (int i = 0; i < n; i++)
	{
		int offsetCol = i * b; //���ϵ�ƫ����
		for (int j = 0; j < m; j++)
		{
			int offsetRow = j * b;  //���ϵ�ƫ����								
			Mat tmp;
			gray(Range(offsetRow, offsetRow + b), Range(offsetCol, offsetCol + b)).copyTo(tmp);//��gray���һС��copy��tmp��
			data.push_back(tmp.reshape(0, 1));  //���л��������������
			labels.push_back((int)j / 5);  //��Ӧ�ı�ע
		}

	}



}