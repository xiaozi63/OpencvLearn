#include <image_opencv.h>

using namespace std;
using namespace cv;

#define SRC_WINDOW_NAME	"src image"
#define DST_WINDOW_NAME	"dst image"
Mat g_srcImage, g_inpaintMask;
Point previousPoint(-1, -1);

void On_Mouse(int event, int x, int y, int flags, void*) {
	
	cout << "on Mouse call back\n";
	
	if (EVENT_LBUTTONUP == event || !(flags & EVENT_FLAG_LBUTTON)) {
		previousPoint = Point(-1, -1);
		cout << "1\n";
	} else if (EVENT_LBUTTONDOWN == event) {
		cout << "2\n";
		previousPoint = Point(x, y);
	} else if (EVENT_MOUSEMOVE == event && (flags & EVENT_FLAG_LBUTTON)) {
		Point pt(x, y);
		if (previousPoint.x < 0) {
			previousPoint = pt;
		}

		cout << "3\n";
		line(g_inpaintMask, previousPoint, pt, Scalar::all(255), 5, 8, 0);
		line(g_srcImage, previousPoint, pt, Scalar::all(255), 5, 8, 0);
		previousPoint = pt;
		imshow(SRC_WINDOW_NAME, g_srcImage);
	}
}

int main(int args, char* argv[]) 
{
	Mat srcImage = imread("../res/1.jpg");	
	if (!srcImage.data) {
		cout << "read image failed" << endl;
		return -1;
	}

	g_srcImage = srcImage.clone();
	g_inpaintMask = Mat::zeros(srcImage.size(), CV_8U);

	imshow(SRC_WINDOW_NAME, srcImage);
	setMouseCallback(SRC_WINDOW_NAME, On_Mouse, 0);
	char ch;
	while((ch = waitKey()) != 'q' && (ch != 27)) {
			cout << "ch = " << ch << endl;
		switch(ch) {
			case 'r':
				g_inpaintMask = Scalar::all(0);
				srcImage.copyTo(g_srcImage);
				imshow(SRC_WINDOW_NAME, g_srcImage);
				break;
			case 'd':
				{
					Mat inpaintedImage;
					inpaint(g_srcImage, g_inpaintMask, inpaintedImage, 3, INPAINT_TELEA);
					imshow(DST_WINDOW_NAME, inpaintedImage);
					break;
				}
			default:
				break;
		}
	}

	cout << "exit\n";
	return 0;
}
