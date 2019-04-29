#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main2(int argc, char** argv)
{	
	Mat data = (Mat_<double>(2, 2)<<
		1,2,
		2,1);//�������

	Mat eigenvalues, eigenvector;//��������ֵ����������
	eigen(data, eigenvalues, eigenvector);//����API ��������ֵ����������
	for (int i = 0; i < eigenvalues.rows; i++)
	{
		cout << "eigen value" << i << eigenvalues.at<double>(i) << endl;
	}
	cout << "eigen vector" << endl;
	cout << eigenvector << endl;

	waitKey(0);
	return 0;
}