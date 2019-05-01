#include<opencv2/opencv.hpp>	
#include<opencv2/face>
#include<iostream>
using namespace cv;
using namespace cv::face;
using namespace std;

int main(int argc, char** argv)
{
	string filename = string("D:/test/test.jpg");
	ifstream file(filename.c_str(), ifstream::in);
	if (!file)
	{
		cout << "load_data error" << endl;
		return -1;
	}
	string line, path, classlabel;
	vector<Mat> images;
	vector<int>labels;
	char separator = ';';
	while (getline(file, line))
	{
		stringstream liness(line);
		getline(liness, path, separator);
		getline(liness, classlabel);
		if (!!path.empty() && !classlabel.empty())
		{
			images.push_back(imread(path, 0));
			labels.push_back(atoi(classlabel.c_str()));
		}
	}
	if (images.size() < 1 || labels.size() < 1)
	{
		cout << "error images" << endl;
		return -1;
	}
	int height = images[0].rows;
	int weight = images[0].cols;

	Mat testSample = images[images.size() - 1];
	int testLabel = labels[labels.size() - 1];

	images.pop_back();
	labels.pop_back();
	//ÑµÁ·»·½Ú
	Ptr<BasicFaceRecofnizer>model = createEigenFaceRecognizer();
	model->train(images, labels);
	
	int predictedlabel = model->predict(testSample);

	cout << predictedlabel << testLabel << endl;

	Mat eigenvalues = model->getEigenValues();
	Mat W = model->getEigenVectors();
	Mat mean = model->getMean();
	Mat meanFace = mean.reshape(1, height);

	Mat dst;

	if (meanFace.channels() == 1)
	{
		normalize(meanFace, dst, 0, 255, NORM_MINMAX, CV_8UC1);
	}
	else
	{
		normalize(meanFace, dst, 0, 255, NORM_MINMAX, CV_8UC3);
	}
	imshow("Mean Face", dst);
}