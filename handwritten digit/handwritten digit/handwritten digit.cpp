#include <opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main()
{
	//切图片成20*20
	Mat src = imread("digits.png");
	Mat gray;
	cvtColor(src, gray, CV_BGR2GRAY);
	int b = 20;
	int m = gray.rows / b;   //每一行图片的个数
	int n = gray.cols / b;   //每一列图片的个数
	Mat data, labels;   //特征矩阵???不太懂
	for (int i = 0; i < n; i++)
	{
		int offsetCol = i * b; //列上的偏移量
		for (int j = 0; j < m; j++)
		{
			int offsetRow = j * b;  //行上的偏移量								
			Mat tmp;
			gray(Range(offsetRow, offsetRow + b), Range(offsetCol, offsetCol + b)).copyTo(tmp);//把gray里的一小块copy到tmp中
			data.push_back(tmp.reshape(0, 1));  //序列化后放入特征矩阵
			labels.push_back((int)j / 5);  //对应的标注
		}

	}



}