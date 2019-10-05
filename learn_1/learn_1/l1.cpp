#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{	//读取显示图片
	Mat src = imread("1.jpg",1);//1读彩图,0读灰度图，2无损
	Mat src2 = imread("1.jpg", 0);
	//写入图片文件
	imwrite("2.jpg", src2);

	//命名窗口
	namedWindow("gray", 2);//WINDOW_AUTOSIZE（1）不能手动改变大小，WINDOW_NORMAL（2）可以
	imshow("gray", src2);

	imshow("src", src);
	waitKey(0);

	//图像腐蚀，核越大效果越明显
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	Mat dst1;
	erode(src, dst1, element);
	imshow("dst", dst1);

	//均值滤波,降噪
	Mat dst2;
	blur(src, dst2, Size(14, 14));
	imshow("dst2", dst2);
	waitKey(0);

	//边缘检测
	Mat dst3, edge, gray;
	//创建和原图形一样的矩阵
	dst3.create(src.size(), src.type());//type返回（深度，通道数）
	cvtColor(src, gray, COLOR_BGR2GRAY);
	blur(gray, edge, Size(3, 3));
	//输入，输出，低于阈值1非边缘，高于阈值2是边缘，算子大小；
	Canny(edge, edge, 10, 100, 3);    
	imshow("dst3",edge);
	waitKey(0);





}