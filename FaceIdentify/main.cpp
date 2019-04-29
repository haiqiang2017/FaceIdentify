#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat image = imread("D:/images/1.png");
	if (image.empty())
	{
		cout << "can't load image" << endl;
		return -1;
	}
	imshow("imput image", image);

	waitKey(0);
	return 0;
}
