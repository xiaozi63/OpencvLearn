#include <image_opencv.h>

using namespace std;
using namespace cv;

int main(int args, char* argv[]) 
{
	Mat srcImage = imread("../res/2.jpg");

	Mat grayImage;

	imshow("image", srcImage);
	waitKey(0);

	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);

	GaussianBlur(grayImage, grayImage, Size(3, 3), 2, 2);

	imshow("mid image", grayImage);
	waitKey(0);

	vector<Vec3f> circles;

	HoughCircles(grayImage, circles, HOUGH_GRADIENT, 1.5, 10, 300, 100, 0, 0);

	for (size_t i = 0; i < circles.size(); ++i) {

		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		circle(srcImage, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		circle(srcImage, center, radius, Scalar(0, 255, 0), 3, 8, 0);
	}

	imshow("circle image", srcImage);
	waitKey(0);
	return 0;
}
