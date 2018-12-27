#include <image_opencv.h>

using namespace std;
using namespace cv;

Mat g_srcImage, g_grayImage;
int g_maxCornerNumber = 33;
int g_maxTrackbarNumber = 500;
RNG g_rng(12345);

void on_GoodFeaturesToTrack(int, void*) {
		
	if (g_maxCornerNumber <= 1) {
			g_maxCornerNumber = 1;
	}

	vector<Point2f> corners;

	Mat copy = g_srcImage.clone();

	Size winSize = Size(5, 5);
	Size zeroZone = Size(-1, -1);

	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::MAX_ITER, 40, 0.001);

	cornerSubPix(g_grayImage, corners, winSize, zeroZone, criteria);
	
	cout << "corner ponit num = " << corners.size() << endl;

	if (corners.size() <= 0) {
		return;
	}

	int r = 4;
	for (unsigned int i = 0; i < corners.size(); ++i) {
		circle(copy, corners[i], r, Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255),
								g_rng.uniform(0, 255)), -1, 8, 0);
		cout << "point.x = " << corners[i].x << "    point.y = " << corners[i].y << endl;
	}
	
	imshow("dst image", copy);
}

int main(int args, char* argv[]) {

	g_srcImage = imread("../res/1.png");
	if (!g_srcImage.data) {
		cout << "read image failed" << endl;
		return -1;
	}

	resize(g_srcImage, g_srcImage, Size(400, 300));

	imshow("src image", g_srcImage);

	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);

	imshow("gray image", g_grayImage);

	namedWindow("dst image", WINDOW_AUTOSIZE);
	createTrackbar("max corner point", "dst image", &g_maxCornerNumber, g_maxTrackbarNumber, on_GoodFeaturesToTrack);

	on_GoodFeaturesToTrack(0, 0);
	waitKey(0);
	return 0;
}
