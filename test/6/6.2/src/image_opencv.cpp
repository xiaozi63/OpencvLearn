#include <image_opencv.h>

using namespace std;
using namespace cv;

#define MEDIAN_BLUR 1
#define BILATERAL 0

int main(int args, char* argv[]) 
{

	Mat image = imread("../res/1.png", 0);	
	Mat blurImage = image.clone();
#if MEDIAN_BLUR
	medianBlur(image, blurImage, 5);
	imshow("image", blurImage);
	waitKey(0);
	return 0;
#elif BILATERAL
	/*
	Mat srcImage[3];
	split(image, srcImage);
	Mat dstImage = Mat_<unsigned char>(srcImage[0].size(), CV_8U);
	bilateralFilter(srcImage[1], dstImage, 25, 25*2, 25/2);
	imshow("image", dstImage);
	waitKey(0);
	*/

	Mat srcImage = imread("../res/1.png");
	Mat dstImage = srcImage.clone();
	bilateralFilter(srcImage, dstImage, 10, 10 *2, 10 / 2);
	imshow("image", dstImage);
	waitKey(0);
	return 0;
#else
	return 0;
#endif
}
