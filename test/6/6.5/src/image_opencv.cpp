#include <image_opencv.h>

using namespace std;
using namespace cv;

int main(int args, char* argv[]) 
{
	Mat image = imread("../res/1.png");
	imshow("image", image);
	Rect rect;
	Mat dstImage = Mat_<Vec3b>(image.cols, image.rows);
	floodFill(image, dstImage, Point(20, 200), Scalar(0, 200, 200), &rect, Scalar(20, 20, 20), Scalar(29, 20, 20));
	imshow("dstImage", image);
	waitKey(0);
	
	return 0;
}
