#include <opencv_test.h>

using namespace cv;  
using namespace std;

int main(int argc, char* argv[])  
{  
	Mat srcImage, hsvImage;
	srcImage = imread("../res/2.jpg");
	if (!srcImage.data) {
		cout << "read image failed" << endl;
		return -1;
	}
	cvtColor(srcImage, hsvImage, COLOR_BGR2HSV);

	int hueBinNum = 30;
	int saturationBinNum = 32;
	int histSize[] = {hueBinNum, saturationBinNum};

	float hueRanges[] = {0, 180};
	float saturationRanges[] = {0, 255};
	const float* ranges[] = {hueRanges, saturationRanges};
	MatND dstHist;

	int channels[] = {0, 1};

	calcHist(&hsvImage, 1, channels, Mat(), dstHist, 2, histSize,
			ranges, true, false);

	double maxValue = 0;
	minMaxLoc(dstHist, 0, &maxValue, 0, 0);
	int scale = 10;

	Mat histImage = Mat::zeros(saturationBinNum * scale, hueBinNum * 10, CV_8UC3);

	for (int hue = 0; hue < hueBinNum; ++hue) {
		for (int saturation = 0; saturation < saturationBinNum; ++saturation) {
			float binValue = dstHist.at<float>(hue, saturation);
			int intensity = cvRound(binValue * 255 / maxValue);

			rectangle(histImage, Point(hue * scale, saturation * scale),
					Point((hue + 1) * scale - 1, (saturation * scale - 1)),
					Scalar::all(intensity), CV_FILLED);
		}
	}

	imshow("src image", srcImage);
	imshow("h-s image", histImage);
	waitKey();
	return 0;
}
