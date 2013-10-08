// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>

using namespace cv;
using namespace std;

int main() 
{
/*cout << "\nInput Number of Clusters: K = ";
cin >> newK;*/

Mat src = imread("house0.jpg");
imshow("original", src);
Mat src0 = imread("house0.ppm");
imshow("original0", src0);
Mat src1 = imread("house0Out.ppm");
imshow("original1", src1);

    waitKey();  
    return 0;
}