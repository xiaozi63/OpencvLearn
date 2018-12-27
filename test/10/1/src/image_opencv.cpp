#include <image_opencv.h>

using namespace std;
using namespace cv;

Mat g_srcImage, g_srcImage1, g_grayImage;
int g_thresh = 30;
int g_max_thresh = 175;

void on_CornerHarris(int, void*);

int main(int args, char* argv[]) 
{
	g_srcImage = imread("../res/1.png");	
	if (!g_srcImage.data) {
		cout << "read image failed" << endl;
		return -1;
	}

	cout << "opencv version: " << CV_VERSION << endl; 

	imshow("src image", g_srcImage);
	g_srcImage1 = g_srcImage.clone();

	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);

	namedWindow("mid image", WINDOW_AUTOSIZE);

	createTrackbar("thresh", "mid image", &g_thresh, g_max_thresh, on_CornerHarris);

	on_CornerHarris(0, 0);

	waitKey(0);
	return 0;
}

void on_CornerHarris(int, void*) {
	
	Mat dstImage, normImage, scaledImage;
	dstImage = Mat::zeros(g_srcImage.size(), CV_32FC1);
	g_srcImage1 = g_srcImage.clone();

	cornerHarris(g_grayImage, dstImage, 2, 3, 0.04, BORDER_DEFAULT);

	normalize(dstImage, normImage, 0, 255, NORM_MINMAX, CV_32FC1, Mat());

	convertScaleAbs(normImage, scaledImage);

	for (int i = 0; i < normImage.rows; ++i) {
		for(int j = 0; j < normImage.cols; ++j) {
			if ((int)normImage.at<float>(i, j) > g_thresh + 80) {
				circle(g_srcImage1, Point(j, i), 5, Scalar(10, 10, 255), 2, 8, 0);
				circle(scaledImage, Point(j, i), 5, Scalar(0, 10, 255), 2, 8, 0);
			}

		}
	}

	imshow("src image", g_srcImage1);
	imshow("dst image", scaledImage);
}
