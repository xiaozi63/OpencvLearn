#include <opencv_test.h>

using namespace cv;  
using namespace std;

Mat g_srcImage, g_templateImage, g_resultImage;
int g_nMatchMethod;
int g_nMaxTrackbarNum = 5;

void on_Matching(int, void*);

int main(int argc, char* argv[])  
{  
	g_srcImage = imread("../res/1.jpg");	
	if (!g_srcImage.data) {
		cout << "read image failed" << endl;
		return -1;
	}
	resize(g_srcImage, g_srcImage, Size(500, 600));

	Mat tmpImage = g_srcImage(Rect(200, 100, 100, 100));
	tmpImage.copyTo(g_templateImage);
	if (!g_templateImage.data) {
		cout << "read roi image failed" << endl;
		return -2;
	}

	imshow("src image", g_srcImage);
	imshow("mid image", g_templateImage);

	
	createTrackbar("faction", "src image", &g_nMatchMethod, g_nMaxTrackbarNum, on_Matching);

	on_Matching(0, 0);
	waitKey(0);
	return 0;
}	

void on_Matching(int, void*) {

	Mat srcImage;
	g_srcImage.copyTo(srcImage);

	int resultImage_cols = g_srcImage.cols - g_templateImage.cols + 1;
	int resultImage_rows = g_srcImage.rows - g_templateImage.rows + 1;
	g_resultImage.create(resultImage_cols, resultImage_rows, CV_32FC1);

	matchTemplate(g_srcImage, g_templateImage, g_resultImage, g_nMatchMethod);
	normalize(g_resultImage, g_resultImage, 0, 1, NORM_MINMAX, -1, Mat());

	double minValue, maxValue;
	Point minLocation, maxLocation;
	Point matchLocation;
	minMaxLoc(g_resultImage, &minValue, &maxValue, &minLocation, &maxLocation, Mat());

	if (TM_SQDIFF == g_nMatchMethod || TM_SQDIFF_NORMED == g_nMatchMethod) {
		matchLocation = minLocation;
	} else {
		matchLocation = maxLocation;
	}

	rectangle(srcImage, matchLocation, Point(matchLocation.x + g_templateImage.cols, 
				matchLocation.y + g_templateImage.rows), Scalar(0, 0, 255), 2, 8, 0);

	rectangle(g_resultImage, matchLocation, Point(matchLocation.x + g_templateImage.cols,
				matchLocation.y + g_templateImage.rows), Scalar(0, 0, 255), 2, 8, 0);

	imshow("src image", srcImage);
	imshow("dst image", g_resultImage);
}
