#include <image_opencv.h>

using namespace std;
using namespace cv;

#define DIALTE 0
#define ERODE 1

int main(int args, char* argv[]) 
{
#if DIALTE
	Mat image = imread("../res/1.png");
	Mat kernel = getStructuringElement(MORPH_RECT, Size(20, 20));
	Mat dstImage = image.clone();

	dilate(image, dstImage, kernel);
	imshow("image", dstImage);
	waitKey(0);
#elif ERODE
	Mat image = imread("../res/1.png", 0);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(10, 10));
	Mat dstImage = image.clone();
	erode(image, dstImage, kernel);
	imshow("image", dstImage);
	waitKey(0);
#else
	return 0;
#endif
}
