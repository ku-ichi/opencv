#include <opencv2/opencv.hpp>
#include<iostream>
//#include"stdafx.h"

using namespace cv;
using namespace std;
using namespace cv::ml;

int main()
{
	//��ͼƬ��20*20��ÿ������500��ͼ��5*100
	Mat src = imread("digits.png");
	Mat gray;
	cvtColor(src, gray, CV_BGR2GRAY);
	int b = 20;
	int m = gray.rows / b;   //ÿһ��ͼƬ�ĸ���
	int n = gray.cols / b;   //ÿһ��ͼƬ�ĸ���
	Mat data, labels;   //��������
	for (int i = 0; i < n; i++)
	{
		int offsetCol = i * b; //���ϵ�ƫ����
		for (int j = 0; j < m; j++)
		{
			int offsetRow = j * b;  //���ϵ�ƫ����								
			Mat tmp;
			gray(Range(offsetRow, offsetRow + b), Range(offsetCol, offsetCol + b)).copyTo(tmp);//��gray���һС��copy��tmp��
			data.push_back(tmp.reshape(0, 1));  //���������������������,20*20��1*400
			labels.push_back((int)j / 5);  //��Ӧ�ı�ע
		}
	}
	//src��1000*2000���data��400(20*20) * 5000(5*100*10)
	data.convertTo(data, CV_32F); //uchar��ת��Ϊcv_32f
	int samplesNum = data.rows;
	int trainNum = 4500;
	Mat trainData, trainLabels;
	trainData = data(Range(0, trainNum), Range::all());   //ǰ3000������Ϊѵ������
	trainLabels = labels(Range(0, trainNum), Range::all());

	//ʹ��KNN�㷨
	int K = 5;
	Ptr<TrainData> tData = TrainData::create(trainData, ROW_SAMPLE, trainLabels);
	Ptr<KNearest> model = KNearest::create();
	model->setDefaultK(K);
	model->setIsClassifier(true);
	model->train(tData);

	/*Ԥ�����
	double train_hr = 0, test_hr = 0;
	Mat response;
	// compute prediction error on train and test data
	for (int i = 0; i < samplesNum; i++)
	{
		Mat sample = data.row(i);
		float r = model->predict(sample);   //�������н���Ԥ��
											
		//Ԥ������ԭ�����ȣ����Ϊ1������Ϊ0
		r = std::abs(r - labels.at<int>(i)) <= FLT_EPSILON ? 1.f : 0.f;

		if (i < trainNum)
			train_hr += r;  //�ۻ���ȷ��
		else
			test_hr += r;
	}

	test_hr /= samplesNum - trainNum;
	train_hr = trainNum > 0 ? train_hr / trainNum : 1.;

	printf("accuracy: train = %.1f%%, test = %.1f%%\n",
		train_hr*100., test_hr*100.);

	
	*///����ͼƬ����
	Mat src_test = imread("4.jpg");
	imshow("Input img", src_test);
	//ͼ����
	Mat gray_test, thres_test, blur_test;
	cvtColor(src_test, gray_test, COLOR_BGR2GRAY);
	GaussianBlur(gray_test, blur_test, Size(3, 3), 3, 3);
	adaptiveThreshold(blur_test, thres_test, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 151, 10);
	Mat morph_test, predict_mat;
	morphologyEx(thres_test, morph_test, MORPH_OPEN, Mat(5, 5, CV_8U), Point(-1, -1));
	imshow("Bin", morph_test);

	vector<vector<Point>> contours_test;
	vector<Vec4i> hiearachy_test;
	findContours(morph_test, contours_test, hiearachy_test, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	for (int i = 0; i < contours_test.size(); ++i)
	{

		Rect minrect_test = boundingRect(contours_test[i]);
		float area_test = contourArea(contours_test[i]);
		float ckbi_test = minrect_test.width / minrect_test.height;//�����
		if (ckbi_test < 4 && area_test>50)
		{
			rectangle(src_test, minrect_test, Scalar(0, 255, 0), 1, 8);
			Mat tmp3;
			Rect ROI_test = minrect_test;
			Mat ROI_img_test = morph_test(ROI_test);
			resize(ROI_img_test, ROI_img_test, Size(20, 20));
			ROI_img_test.convertTo(ROI_img_test, CV_32F);
			ROI_img_test.copyTo(tmp3);
			predict_mat.push_back(tmp3.reshape(0, 1));
			Mat predict_simple = predict_mat.row(i);
			float r = model->predict(predict_simple);
			stringstream stream;
			stream << r;
			string str;
			stream >> str;
			putText(src_test, str, ROI_test.tl(), FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 0), 1, 8);
		}

	}
	imshow("img_test", src_test);
	waitKey(0);
	



















	
	return 0;






}