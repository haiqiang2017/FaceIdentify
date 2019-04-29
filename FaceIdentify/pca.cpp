#include <opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

double calcPCAOrientation(vector<Point> &pts, Mat &image);
int main(int argc, char** argv)
{
	Mat src = imread("D:/test/test.jpg");
	if (src.empty())
	{
		cout << "can't load image" << endl;
		return -1;
	}
	imshow("src", src);

	Mat gray, binary;//定义灰度和二值化
	cvtColor(src, gray, COLOR_BGR2GRAY);
	imshow("gray", gray);

	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("binary", binary);

	vector<Vec4i>hireachy;
	vector<vector<Point>> contours;
	findContours(binary, contours, hireachy, RETR_LIST, CHAIN_APPROX_NONE);

	Mat result = src.clone();
	for (int i = 0; i < contours.size(); i++)
	{
		double area = contourArea(contours[i]);
		if (area > 1e5 || area < 1e2) continue;
		drawContours(result, contours, i, Scalar(0, 0, 255), 2, 8);
		double theta = calcPCAOrientation(contours[i], result);
	}


	waitKey(0);
	return 0;
}

double calcPCAOrientation(vector<Point> &pts, Mat &CALIB_CB_NORMALIZE_IMAGE)
{
	int size = static_cast<int>(pts.size());
	Mat data_pts = Mat(size, 2, CV_64FC1);
	for (int i = 0; i < size; i++)
	{
		data_pts.at<double>(i, 0) = pts[i].x;
		data_pts.at<double>(i, 1) = pts[i].y;
	}
	PCA pca_analysis(data_pts, Mat(), CV_PCA_DATA_AS_ROW);
}