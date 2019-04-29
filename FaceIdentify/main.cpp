#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main1(int argc, char** argv)
{
	Mat src = imread("D:/test/test.jpg ");
	if (src.empty())
	{
		cout << "can't load image" << endl;
		return -1;
	}
	imshow("input img", src);
	Mat means, stddev;
	meanStdDev(src, means, stddev);
	cout << "means rows:" << means.rows << "means.cols:" << means.cols << endl;
	cout << "std rows:" << stddev.rows << "std cols:" << stddev.cols << "\n" << endl;
	for (int row = 0; row < means.rows; row++)
	{
		cout << "means " << row << means.at<double>(row);
		cout << "stddev" << row << stddev.at<double>(row) << "\n";
	}

	Mat samples = (Mat_<double>(5, 3) << 3, 3, 4, 5, 2, 5, 65, 3, 5, 6, 3, 67, 4, 67, 2);
	Mat cov, mu;
	calcCovarMatrix(samples, cov, mu, CV_COVAR_NORMAL | CV_COVAR_ROWS);

	cout << cov << endl;

	cout << means << endl;
	//Mat samples = (Mat_<double>(5, 3) << 90, 60, 90, 90, 90, 30, 60, 60, 60, 60, 60, 90, 30, 30, 30);
	//Mat cov, mu;
	//calcCovarMatrix(samples, cov, mu, CV_COVAR_NORMAL | CV_COVAR_ROWS);

	//cout << "=============================" << endl;
	//cout << "cov : " << endl;
	//cout << cov / 5 << endl;

	//cout << "means : " << endl;
	//cout << mu << endl;

	waitKey(0);
	return 0;

	//均值和方差

}