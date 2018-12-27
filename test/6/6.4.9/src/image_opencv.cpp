#include <image_opencv.h>

using namespace std;
using namespace cv;

Mat g_srcImage, g_dstImage;

int g_kernelSize = 3;
int g_erodeSwitch = 1;

void on_TrackKernelCB(int, void*);



void openOrClose(Mat& srcImage, Mat& dstImage, Mat kernel, int isOpen);

int main(int args, char* argv[]) 
{
	g_srcImage = imread("../res/1.png", 0);	
	g_dstImage = g_srcImage.clone();

	namedWindow("image");
	imshow("image", g_srcImage);

	namedWindow("erode/dilate");
	namedWindow("open/close");

	Mat kernel = getStructuringElement(MORPH_RECT, Size(7, 7), Point(3, 3));

	erode(g_srcImage, g_dstImage, kernel);

	imshow("erode/dilate", g_dstImage);
	Mat tmpImage = g_srcImage.clone();
	openOrClose(g_srcImage, tmpImage, kernel, 0);
	imshow("open/close", tmpImage);

	createTrackbar("1", "erode/dilate", &g_kernelSize, 20, on_TrackKernelCB);
	createTrackbar("2", "erode/dilate", &g_erodeSwitch, 1, on_TrackKernelCB);


	createTrackbar("3", "open/close", &g_erodeSwitch, 1, on_TrackKernelCB);
	while((waitKey(1) != 'q')) {

	}

	cout << "main exit" << endl;
	return 0;
}


void on_TrackKernelCB(int, void*) {

		Mat kernel = getStructuringElement(MORPH_RECT, Size(g_kernelSize * 2 +1, g_kernelSize * 2 +1), 
						Point(g_kernelSize, g_kernelSize));
		if (0 == g_erodeSwitch) {
			dilate(g_srcImage, g_dstImage, kernel);
		} else if (1 == g_erodeSwitch) {
			erode(g_srcImage, g_dstImage, kernel);
		}

		imshow("erode/dilate", g_dstImage);
}

void openOrClose(Mat& srcImage, Mat& dstImage, Mat kernel, int isOpen) {

	Mat tmpImage = srcImage.clone();
	if (0 == isOpen) {
		dilate(srcImage, tmpImage, kernel);
		erode(tmpImage, dstImage, kernel);
	} else if (1 == isOpen) {
		erode(srcImage, tmpImage, kernel);
		dilate(tmpImage, dstImage, kernel);
	}
}
