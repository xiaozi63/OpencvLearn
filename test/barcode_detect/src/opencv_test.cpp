#include <opencv_test.h>
using namespace cv;  
using namespace std;
using namespace cv::xfeatures2d;

#define WIDTH 400
#define HEIGHT 400

#define SIZE(a)	(sizeof(a) / sizeof(a[0]))

static unsigned char code128Head[] = 
{
	255, 255, 255,
	0, 0, 0,
	255, 255,
	0,
	255, 255, 255, 255, 255,
};

Point* getBarcodeCoordinate(Mat srcMat /* must be a gray image*/, int searchTimes) {

	Point* point = new Point(0, 0);
	if (NULL == srcMat.data) {
		cout << "srcMat is null" << endl;
		return point;
	}

	if (searchTimes <= 0) {
		cout << "searchTimes is invalide" << endl;
		return point;
	}

	int width = srcMat.cols * srcMat.channels();
	int height = srcMat.rows;

	int searchY = 1;
	int testHeight = 100;
	Mat barcodeMat = Mat::zeros(testHeight, srcMat.cols, CV_8UC1);
	int showImageRows = 5;
	int imageThreshold = 100;

	for (int index = 0; index < searchTimes; ++index) {
		unsigned char* data = srcMat.ptr<unsigned char>(index * (height / searchTimes));
		int meadianValue = 0;
		int totalValue = 0;
		for (int j = 0; j < width; ++j) {
			printf("srcMat[%d][%d] = %d\n", index * (height / searchTimes), j, *(data + j)); 
			totalValue += *(data + j);
		}
		
		meadianValue = totalValue / width;

		if (showImageRows == index) {
			for (int i = 0; i < width; ++i) {
				if (*(data + i) >= meadianValue) {
					int imageData = 255;
					for (int j = 0; j < testHeight; ++j) {
						unsigned char* testData = barcodeMat.ptr<unsigned char>(j);
						testData[i] = imageData;
						cout << "image data = " << imageData << endl;
					}
				} else {
					int imageData = 0;
					for (int j = 0; j < testHeight; ++j) {
						unsigned char* testData = barcodeMat.ptr<unsigned char>(j);
						testData[i] = imageData;
						cout << "image data = " << imageData << endl;
					}
				}
			}
		}
	}

	unsigned char* srcData = srcMat.ptr<unsigned char>(showImageRows * (height / searchTimes));
	for (int i = 0; i < width; ++i) {
		srcData[i] = 255;
	}


	/*
	for (int n = 160; n < 195; ++n) {
		unsigned char* testData = barcodeMat.ptr<unsigned char>(0);
		printf("testData[%d] = %d\n", n, testData[n]);
	}
	*/


	imshow("dst image", barcodeMat);
	
	

	unsigned char* testData = barcodeMat.ptr<unsigned char>(0);
	int minDistance = 100000;
	int pointX = 0;

	for (int i = 0; i < width - SIZE(code128Head); ++i) {
		int distance = 0;
		for (int j = 0; j < SIZE(code128Head); ++j) {
			distance += abs(testData[i + j] - code128Head[j]);
		}

		if (distance < minDistance) {
			minDistance = distance;
			pointX = i;
			point->x = i;
			point->y = 100; 
		}
	}
	printf("min distance = %d\n", minDistance);
	circle(srcMat, Point(point->x, point->y), 3, CV_RGB(125, 125, 125));
	imshow("dstImgae", srcMat);

	return point;
}

int main(int argc, char* argv[])  
{  
	Mat image = imread("../res/image11.jpg", 1);	
	if (NULL == image.data) {
		cout << "read image failed" << endl; 
		return -1;
	}


	resize(image, image, Size(WIDTH, HEIGHT));

	cvtColor(image, image, COLOR_BGR2GRAY);

	namedWindow("image");

	imshow("image", image);



	Point* barcodePoint = getBarcodeCoordinate(image, 10);
	cout << "point.x = " << barcodePoint->x << endl;
	cout << "point.y = " << barcodePoint->y << endl;

	waitKey(0);
	return 0;
}
