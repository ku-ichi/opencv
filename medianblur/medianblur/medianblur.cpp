#include<opencv2/opencv.hpp>
#include<iostream>
#include<algorithm>#sort����
 
using namespace cv;
using namespace std;

int main()
{
	vector<int>grayv(9);
	Mat image = imread("1.bmp", 0);
	if (!image.data)
	{
		return -1;
	}
	Mat self;//��������Լ�д����ֵ�˲�
	image.copyTo(self);
	Mat api;//�������opencv�Դ�����ֵ�˲�
	for (int i = 1; i < image.rows - 1; i++)
	{
		//(i,j)��Ҫ�ı�����������
		//ָ��i-1��һ����
		uchar* preptr = image.ptr(i - 1);
		uchar* ptr = image.ptr(i);
		uchar* nextptr = image.ptr(i + 1);
		uchar* imgptr = self.ptr(i);

		for (int j = 1; j < image.cols - 1; j++)
		{
			grayv[0] = (preptr[j - 1]);
			grayv[1] = (preptr[j]);
			grayv[2] = (preptr[j + 1]);
			grayv[3] = (ptr[j - 1]);
			grayv[4] = (ptr[j]);
			grayv[5] = (ptr[j + 1]);
			grayv[6] = (nextptr[j - 1]);
			grayv[7] = (nextptr[j]);
			grayv[8] = (nextptr[j + 1]);

			//Ĭ������			
			sort(grayv.begin(), grayv.end());
			imgptr[j] = int(grayv[4]);
		}
	}
	medianBlur(image, api, 3);
	imshow("src", image);
	imshow("self", self);
	imshow("api", api);
	waitKey(0);
	return 0;
}