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
int newK = 8;
cout << "\nInput Number of Clusters: K = ";
cin >> newK;

Mat src = imread("house0.jpg");
    imshow("original", src);

    // Размытие
    blur(src, src, Size(15,15));        
    imshow("blurred", src);

    Mat p = Mat::zeros(src.cols*src.rows, 5, CV_32F);
    Mat bestLabels, centers, clustered;

    // Перевод в нужный формат
    vector<Mat> bgr(3);
    split(src, bgr);    
    for(int i=0; i<src.cols*src.rows; i++) {
        p.at<float>(i,0) = (i/src.cols) / src.rows;
        p.at<float>(i,1) = (i%src.cols) / src.cols;
        p.at<float>(i,2) = bgr[0].data[i] / 255.0;
        p.at<float>(i,3) = bgr[1].data[i] / 255.0;
        p.at<float>(i,4) = bgr[2].data[i] / 255.0;
    }

    // Kmeans в действии
    int K = newK;
    cv::kmeans(p, K, bestLabels,
            TermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 10, 1.0),
            3, KMEANS_PP_CENTERS);
 
    int* colors = new int[K];
    for(int i=0; i<K; i++) {
        colors[i] = 255/(i+1);
    }
    // Определяем цвета
    clustered = Mat(src.rows, src.cols, CV_32F);
    for(int i=0; i<src.cols*src.rows; i++) {            
        clustered.at<float>(i/src.cols, i%src.cols) = (float)(colors[bestLabels.at<int>(i,0)]);
    }

    clustered.convertTo(clustered, CV_8U);
    imshow("clustered", clustered);

    waitKey();  
    return 0;
}