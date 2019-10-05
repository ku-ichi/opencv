#include <iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void hsv(Mat src );
void bgr(Mat src );

int main()
{
	Mat src = imread("1.jpg");
	
	int mode;
	cout << "What mode?" << endl << "1-BGR 2-HSV" << endl;
	cin >> mode;

	switch (mode)
	{
		case 1:
			bgr(src);
			break;
		case 2:
			hsv(src);
			break;
		default:
			cout << "error code" << endl;

	}

	
	imshow("src", src);
	
}

void hsv(Mat src)
{
	int color;
	int minH, maxH, minS, maxS, minV, maxV, minH_2, maxH_2;

	
	Mat hsv;
	vector<Mat> hsvsplit;
	Mat thresholded;//用于一般颜色
	Mat lowrange, highrange;//用于红色

	cvtColor(src, hsv, COLOR_BGR2HSV);
	//直方图均衡化,在V（亮度）中操作；
	split(hsv, hsvsplit);
	equalizeHist(hsvsplit[2], hsvsplit[2]);
	merge(hsvsplit, hsv);

	cout << "What color do you want to recognize?" << endl << "1-red 2-blue" << endl;
	cin >> color;

	switch (color)
	{
	case 2:
	{
		minH = 100;
		maxH = 124;
		minS = 30;
		maxS = 255;
		minV = 31;
		maxV = 255;
		//二值化，阈值间为255,外为0；
		inRange(hsv, Scalar(minH, minS, minV), Scalar(maxH, maxS, maxV), thresholded);
		break;
	}
	case 1:
	{
		minH = 156;
		maxH = 180;
		minS = 43;
		maxS = 255;
		minV = 46;
		maxV = 255;

		minH_2 = 0;
		maxH_2 = 7;
		//设定两个范围
		inRange(hsv, Scalar(minH, minS, minV), Scalar(maxH, maxS, maxV), lowrange);
		inRange(hsv, Scalar(minH_2, minS, minV), Scalar(maxH_2, maxS, maxV), highrange);
		addWeighted(lowrange, 1.0, highrange, 1.0, 0.0, thresholded);
		break;
	}
	default:
		cout << "error code" << endl;

	}

	//开，除噪点
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(thresholded, thresholded, MORPH_OPEN, element);
	//闭，连接一些连通域
	morphologyEx(thresholded, thresholded, MORPH_CLOSE, element);

	imshow("HSV", thresholded);
	waitKey(0);
}

void bgr(Mat src )
{
	int minb, maxb, ming, maxg, minr, maxr, minb_2, maxb_2, ming_2, maxg_2, minr_2, maxr_2;
	Mat thresholded,low,high;
	int color;
	
	cout << "What color do you want to recognize?" << endl << "1-red 2-blue" << endl;
	cin >> color;

	switch (color)
	{
	case 2:
	{
		minb = 139;
		maxb = 180;
		ming = 97;
		maxg = 124;
		minr = 11;
		maxr = 76;

		minb_2 = 64;
		maxb_2 = 110;
		ming_2 = 37;
		maxg_2 = 86;
		minr_2 = 15;
		maxr_2 = 67;
		
		inRange(src, Scalar(minb, ming, minr), Scalar(maxb, maxg, maxr), low);
		inRange(src, Scalar(minb_2, ming_2, minr_2), Scalar(maxb_2, maxg_2, maxr_2), high);
		addWeighted(high, 1.0, low, 1.0, 0.0, thresholded);
		
		break;
	}
	case 1:
	{
		minb = 46;
		maxb = 82;
		ming = 44;
		maxg = 71;
		minr = 186;
		maxr = 204;

		minb_2 = 14;
		maxb_2 = 44;
		ming_2 = 21;
		maxg_2 = 46;
		minr_2 = 88;
		maxr_2 = 97;

		inRange(src, Scalar(minb, ming, minr), Scalar(maxb, maxg, maxr), low);
		inRange(src, Scalar(minb_2, ming_2, minr_2), Scalar(maxb_2, maxg_2, maxr_2), high);
		addWeighted(high, 1.0, low, 1.0, 0.0, thresholded);                                       
		
		break;
	}
	default:
		cout << "error code" << endl;
	}	

	//开，除噪点
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(thresholded, thresholded, MORPH_OPEN, element);
	//闭，连接一些连通域
	morphologyEx(thresholded, thresholded, MORPH_CLOSE, element);

	imshow("BGR", thresholded);
	waitKey(0);

}

