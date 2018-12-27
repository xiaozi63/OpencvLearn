#include <image_opencv.h>

using namespace std;
using namespace cv;

Mat g_srcImage, g_grayImage;
int g_nThresh = 50;
int g_maxThresh = 255;
RNG g_rng(12345);
Mat srcImage_copy = g_srcImage.clone();
Mat g_thresholdImage_output;
vector<vector<Point>> g_vContours;
vector<Vec4i> g_vHierarchy;

void on_ThreshChange(int, void*);

int main(int args, char* argv[]) 
{
	g_srcImage = imread("../res/1.jpg", 1);
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	blur(g_grayImage, g_grayImage, Size(3, 3));

	namedWindow("src image", WINDOW_AUTOSIZE);
	imshow("src image", g_srcImage);

	createTrackbar("threshold", "src image", &g_nThresh, g_maxThresh, on_ThreshChange);
	on_ThreshChange(0, 0);
	waitKey(0);
	return 0;
}

void on_ThreshChange(int, void*) {
		threshold(g_grayImage, g_thresholdImage_output, g_nThresh, 255, THRESH_BINARY);

		findContours(g_thresholdImage_output, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

		vector<vector<Point>> hull(g_vContours.size());
		for (unsigned int i = 0; i < g_vContours.size(); ++i) {
				convexHull(Mat(g_vContours[i]), hull[i], false);
		}

		Mat drawing = Mat::zeros(g_thresholdImage_output.size(), CV_8UC3);
		for (unsigned int i = 0; i < g_vContours.size(); ++i) {
				Scalar color = Scalar(g_rng.uniform(0, 255), 
								g_rng.uniform(0, 255), g_rng.uniform(0, 255));
				drawContours(drawing, g_vContours, i, color, 1, 8, vector<Vec4i>(), 0, Point());
				drawContours(drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point());
		}

		imshow("dst image", drawing);
}
