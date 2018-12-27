#include <image_opencv.h>

using namespace std;
using namespace cv;

int main(int args, char* argv[]) 
{

	Mat srcImage = imread("../res/1.png");
//	Mat dstImage = Mat::zeros(srcImage.cols / 2, srcImage.rows / 2, srcImage.type());

	Mat dstImage;
	imshow("image", srcImage);
	waitKey(0);
	//resize(srcImage, dstImage, Size(srcImage.cols / 2, srcImage.rows / 2), (0, 0), (0, 0), 3);
	resize(srcImage, dstImage, Size(srcImage.cols / 4, srcImage.rows / 4), 0.1, 0.1, 3);

	imshow("dst image", dstImage);
	
	waitKey(0);
	return 0;
}
