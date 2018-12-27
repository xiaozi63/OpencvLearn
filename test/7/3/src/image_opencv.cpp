#include <image_opencv.h>

using namespace std;
using namespace cv;

int main(int args, char* argv[]) 
{
	Mat srcImage, dstImage;
	srcImage = imread("../res/1.jpg");
	if (!srcImage.data) {
		cout << "read image failed" << endl;
		return -1;
	}

	imshow("src image", srcImage);
	dstImage.create(srcImage.size(), srcImage.type());
	
	Mat mapX, mapY;
	mapX.create(srcImage.size(), CV_32FC1);
	mapY.create(srcImage.size(), CV_32FC1);

	for (int i = 0; i < srcImage.rows; ++i) {
		for (int j = 0; j < srcImage.cols; ++j) {
			mapX.at<float>(i, j) = static_cast<float>(srcImage.cols - j) * 2;
			mapY.at<float>(i, j) = static_cast<float>(srcImage.rows - i) * 2;
		}
	}

	remap(srcImage, dstImage, mapX, mapY, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));

	imshow("dst image",dstImage);
	waitKey(0);
	return 0;
}
