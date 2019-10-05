#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{	//��ȡ��ʾͼƬ
	Mat src = imread("1.jpg",1);//1����ͼ,0���Ҷ�ͼ��2����
	Mat src2 = imread("1.jpg", 0);
	//д��ͼƬ�ļ�
	imwrite("2.jpg", src2);

	//��������
	namedWindow("gray", 2);//WINDOW_AUTOSIZE��1�������ֶ��ı��С��WINDOW_NORMAL��2������
	imshow("gray", src2);

	imshow("src", src);
	waitKey(0);

	//ͼ��ʴ����Խ��Ч��Խ����
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	Mat dst1;
	erode(src, dst1, element);
	imshow("dst", dst1);

	//��ֵ�˲�,����
	Mat dst2;
	blur(src, dst2, Size(14, 14));
	imshow("dst2", dst2);
	waitKey(0);

	//��Ե���
	Mat dst3, edge, gray;
	//������ԭͼ��һ���ľ���
	dst3.create(src.size(), src.type());//type���أ���ȣ�ͨ������
	cvtColor(src, gray, COLOR_BGR2GRAY);
	blur(gray, edge, Size(3, 3));
	//���룬�����������ֵ1�Ǳ�Ե��������ֵ2�Ǳ�Ե�����Ӵ�С��
	Canny(edge, edge, 10, 100, 3);    
	imshow("dst3",edge);
	waitKey(0);





}