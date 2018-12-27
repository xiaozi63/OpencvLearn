#include <image_opencv.h>

using namespace std;
using namespace cv;


Mat g_srcImage;
Mat g_grayImage;
int g_nThresh = 80;
int g_nThresh_max = 255;
RNG g_rng(12345);
Mat g_cannyMatOutPut;
vector<vector<Point>> g_vContours;
vector<Vec4i> g_vHierarchy;


void on_ThreshChange(int, void*);

int main(int args, char* argv[]) 
{
	g_srcImage = imread("../res/1.jpg");
	if(!g_srcImage.data) {
		cout << "read image failed" << endl;
		return -1;
	}

	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);

	blur(g_grayImage, g_grayImage, Size(3, 3));

	namedWindow("src image", 1);
	imshow("src image", g_srcImage);

	createTrackbar("canny threshold", "src image", 
					&g_nThresh, g_nThresh_max, on_ThreshChange);
	on_ThreshChange(0, 0);

	waitKey(0);
	return 0;
}

void on_ThreshChange(int, void*) {

	Canny(g_grayImage, g_cannyMatOutPut, g_nThresh, g_nThresh * 2, 3);
	imshow("mid image", g_cannyMatOutPut);

	findContours(g_cannyMatOutPut, g_vContours, g_vHierarchy,
					RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	Mat drawing = Mat::zeros(g_cannyMatOutPut.size(), CV_8UC3);
	for (int i = 0; i < g_vContours.size(); ++i) {
		Scalar color = Scalar(g_rng.uniform(0, 255),
						g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy,
						0, Point());
	}

	imshow("dst image", drawing);
}
