#include <image_opencv.h>

using namespace std;
using namespace cv;


#define TEST_1	0
#define TEST_2	1


int main(int args, char* argv[]) 
{

#if TEST_1
	Mat srcImage = imread("../res/1.jpg", 0);

	Mat dstImage = srcImage.clone();

	imshow("image", srcImage);
	waitKey(0);

	Canny(srcImage, dstImage, 150, 100, 3);

	imshow("dst image", dstImage);
	waitKey(0);
	return 0;
#elif TEST_2
	Mat srcImage = imread("../res/1.jpg");
	Mat tmpImage = Mat::zeros(srcImage.cols, srcImage.rows, CV_8U);
	cvtColor(srcImage, tmpImage, COLOR_BGR2GRAY);
	Mat edgeImage = Mat::zeros(tmpImage.cols, tmpImage.rows, CV_8U);; 

//	blur(tmpImage, edgeImage, Size(3, 3));

	Canny(tmpImage, edgeImage, 150, 100, 3);

	Mat dstImage = Mat::zeros(srcImage.cols, srcImage.rows, srcImage.type());;
	srcImage.copyTo(dstImage, edgeImage);
	imshow("image", dstImage);
	waitKey(0);
	return 0;
#endif
}
