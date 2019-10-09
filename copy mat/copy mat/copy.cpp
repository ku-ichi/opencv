#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat A = imread("img.png");
	imshow("浅深拷贝对比",A);

	//浅拷贝，修改ABC中任一会影响其他所有Mat
	Mat B(A);
	Mat C=A;

	//深拷贝
	Mat D = A.clone();
	Mat E;
	A.copyTo(E);

	//插入一行，保证cols相同即可
	/*
	Mat src,dst；
	Mat insert = src.row();//提取一行
	dst.push_back(insert);//添加到底部
	*/
	








	waitKey(0);
}
