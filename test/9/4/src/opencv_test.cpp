#include <opencv_test.h>

using namespace cv;  
using namespace std;

Mat g_srcImage, g_hsvImage, g_hueImage;
int g_bins = 30;

#define WIDTH 400
#define HEIGHT 300

void on_BinChange(int, void*);

int main(int argc, char* argv[])  
{  
	g_srcImage = imread("../res/5.jpg", 1);	
	if (!g_srcImage.data) {
		cout << "read image failed" << endl;
		return -1;
	}

	Mat midImage = Mat::zeros(WIDTH, HEIGHT, g_srcImage.type());

	resize(g_srcImage, midImage, Size(WIDTH, HEIGHT), INTER_LINEAR);	
	g_srcImage = midImage.clone();

	cvtColor(g_srcImage, g_hsvImage, COLOR_BGR2HSV);

	g_hueImage.create(g_hsvImage.size(), g_hsvImage.depth());
	int ch[] = {0, 0};

	mixChannels(&g_hsvImage, 1, &g_hueImage, 1, ch, 1);

	namedWindow("src image", WINDOW_AUTOSIZE);
	createTrackbar("hue", "src image", &g_bins, 180, on_BinChange);
	on_BinChange(0, 0);

	imshow("src image", g_srcImage);
	waitKey(0);
	return 0;
}

void on_BinChange(int, void*) {

	MatND hist;
	int histSize = MAX(g_bins, 2);
	float hue_range[] = {0, 180};
	const float* ranges = {hue_range};

	long start_time = getTickCount();
	calcHist(&g_hueImage, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false);
	normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());

	MatND backproj;
	calcBackProject(&g_hueImage, 1, 0, hist, backproj, &ranges, 1, true);

	imshow("hist image", backproj);

	int w = 400, h = 400;
	int bin_w = cvRound((double) w / histSize);
	Mat histImg = Mat::zeros(w, h, CV_8UC3);

	for(int i = 0; i < g_bins; ++i) {
		rectangle(histImg, Point(i * bin_w, h), 
				Point((i + 1) * bin_w, h -cvRound(hist.at<float>(i) * h / 255.0)), 
				Scalar(100, 123, 255), -1);
	}
	
	long end_time = getTickCount();
	cout << "time is " << (end_time - start_time) * 1000 / getTickFrequency() << "ms" << endl;
	imshow("hist 2", histImg);
}
