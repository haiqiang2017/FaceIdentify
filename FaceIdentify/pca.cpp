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
	imshow("contours", result);

	waitKey(0);
	return 0;
}


double calcPCAOrientation(vector<Point> &pts, Mat &image)
{
	int size = static_cast<int>(pts.size());
	Mat data_pts = Mat(size, 2, CV_64FC1);
	for (int i = 0; i < size; i++)
	{
		data_pts.at<double>(i, 0) = pts[i].x;
		data_pts.at<double>(i, 1) = pts[i].y;
	}
	PCA pca_analysis(data_pts, Mat(), CV_PCA_DATA_AS_ROW);
	Point cnt = Point(static_cast<int>(pca_analysis.mean.at<double>(0, 0)),
		   static_cast<int>(pca_analysis.mean.at<double>(0,1)));

	circle(image, cnt, 2, Scalar(0, 255, 0), 2, 8, 0);
	//STL技术
	vector<Point2d> vecs(2);
	vector<double>	vals(2);
	for (int i = 0; i < 2; i++)
	{
		vals[i] = pca_analysis.eigenvalues.at<double>(i, 0);
		cout << "eigen value" << i << vals[i] << endl;
		vecs[i] = Point2d(pca_analysis.eigenvectors.at<double>(i, 0), pca_analysis.eigenvectors.at<double>(i, 1));
	}
	Point p1 = cnt + 0.02*Point(static_cast<int>(vecs[0].x*vals[0]), static_cast<int>(vecs[0].y*vals[0]));
	Point p2 = cnt + 0.02*Point(static_cast<int>(vecs[1].x*vals[1]), static_cast<int>(vecs[1].y*vals[1]));

	line(image, cnt, p1, Scalar(255, 0, 0), 2, 8, 0);
	line(image, cnt, p2, Scalar(255, 255, 0), 2, 8, 0);

	double angle = atan2(vecs[0].y, vecs[0].x);
	return angle;

}