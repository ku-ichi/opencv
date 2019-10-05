//�����ͻ��Ϊ��
#include <opencv2/opencv.hpp>

using namespace cv;

//ȫ�ֱ���
const int MaxAlpha = 100;
int nowAlpha;
double proportion, rest;

//�洢ͼ�����
Mat im1, im2, dst;

//�ص�����
void on_trackbar(int, void*)
{
	proportion = (double)nowAlpha / MaxAlpha;
	rest = 1.0 - proportion;
	
	//����5Ϊƫ��
	addWeighted(im1, proportion, im2, rest, 0.0, dst);
	imshow("���Ի��", dst);	
}

int main()
{
	im1 = imread("ta.jpg");
	im2 = imread("lv.jpg");

	nowAlpha = 50;//��ʼ��������Ϊ50

	namedWindow("���Ի��", 2);
	//����������
	char trackbarname[50];
	snprintf(trackbarname,sizeof(trackbarname), "͸����Ϊ��%d", MaxAlpha);

	//����������,������������������������ʵʱֵ�����ֵ���ص�����
	createTrackbar(trackbarname, "���Ի��", &nowAlpha, MaxAlpha, on_trackbar);
	on_trackbar(nowAlpha, 0);

	waitKey(0);
	return 0;
}