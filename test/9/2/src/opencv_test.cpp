#include <opencv_test.h>

using namespace cv;  
using namespace std;

int main(int argc, char* argv[])  
{  
	Mat srcImage = imread("../res/2.jpg");
	if (!srcImage.data) {
		cout << "read image failed" << endl;
		return -1;
	}

	imshow("src image", srcImage);
	waitKey(0);

	
	Mat grayImage = Mat::zeros(srcImage.size(), CV_8U);

	if (!grayImage.data) {
		cout << "read image failed" << endl;
		return -2;
	}

	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);

	MatND dstHist;
	int dims = 1;
	float hranges[] = {0, 255};
	const float* ranges[] = {hranges};
	int size = 256;
	int channels = 0;


	calcHist(&srcImage, 1, &channels, Mat(), dstHist, dims, &size, ranges);
/*
	imshow("min image", dstHist);
	waitKey(0);
*/
	
	int scale = 1;

	Mat dstImage(size * scale, size, CV_8U, Scalar(0));

	double minValue = 0;
	double maxValue = 0;
	minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);

	int hpt = saturate_cast<int>(0.9 * size);
	for (int i = 0; i < 256; ++i) {
		float binValue = dstHist.at<float>(i);
		cout << "binValue[i"<< i << "] = " << binValue  << endl;
		int realValue = saturate_cast<int>(binValue * hpt / maxValue);
		 
		rectangle(dstImage, Point(i * scale, size - 1), Point((i + 1) * scale - 1, size - realValue), Scalar(255));
	}

	imshow("hist image", dstImage);
	waitKey(0);
	return 0;
}
