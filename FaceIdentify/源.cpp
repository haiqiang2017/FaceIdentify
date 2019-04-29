#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main1(int argc, char** argv) {
	Mat data = (Mat_<double>(2, 2) <<
		2, 4,
		4, 2);
	Mat eigenvalues, eigenvector;
	eigen(data, eigenvalues, eigenvector);

	for (int i = 0; i < eigenvalues.rows; i++) {
		printf("eigen value %d  :  %.3f \n", i, eigenvalues.at<double>(i));
	}

	cout << " eigen vector : " << endl;
	cout << eigenvector << endl;

	waitKey(0);
	return 0;
}