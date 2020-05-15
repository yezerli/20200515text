#include <iostream>  
#include <opencv2\core\core.hpp>  
#include <opencv2\highgui\highgui.hpp>  
#include <opencv2\imgproc\imgproc.hpp>  
#include<cmath>
using namespace cv;

Mat gammaTransform(Mat &srcImage, float k)
{
	unsigned char LUT[256];
	for (int i = 0; i < 256; i++)
	{
		float f = (i + 0.5f) / 255;
		f = (float)(pow(f, k));
		LUT[i] = saturate_cast<uchar>(f*255.0f);
	}
	Mat resultImage = srcImage.clone();

	if (srcImage.channels() == 1)
	{
		MatIterator_<uchar> iterator = resultImage.begin<uchar>();
		MatIterator_<uchar> iteratorEnd = resultImage.end<uchar>();
		for (; iterator != iteratorEnd; iterator++)
		{
			*iterator = LUT[(*iterator)];
		}
	}
	return resultImage;
}
int main()
{
	Mat srcImage = imread("E:\\Git\\face.jpg",0);
	if (!srcImage.data)
	{
		printf("could not load image...\n");
		return -1;
	}
	//取两种不同的gamma值
	float gamma = 3.33f;
	float kFactor = 1 / gamma;
	Mat result = gammaTransform(srcImage, kFactor);
	imshow("srcImage", srcImage);
	imshow("res", result);
	waitKey(0);
	return 0;
}