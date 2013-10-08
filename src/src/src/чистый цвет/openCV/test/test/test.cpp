// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "opencv2/highgui/highgui_c.h"
#include "opencv2/core/core_c.h"
#include "opencv2/imgproc/imgproc_c.h"

int Cursor_x,Cursor_y;
void on_mouse( int event, int x, int y, int flags, void* param );

bool Point_On = false;

int main(int argc, char* argv[])
{
         char a[] = "house0.jpg\0";
		 const char* ff = a;
         IplImage *img = cvLoadImage( ff, 1 );
         uchar* ptr = (uchar*) (img->imageData);
         IplImage* img2 = cvCreateImage(cvGetSize(img),8,3);
         uchar* ptr_ = (uchar*) (img2->imageData);
         IplImage* Gray = cvCreateImage(cvSize(256,256),8,1);
         IplImage* Gray1 = cvCreateImage(cvSize(256,256),8,3);
         uchar* ptr2 = (uchar*) (Gray->imageData);
         cvSet(Gray,cvScalar(0));
         int m[256*256];
         memset(m,0,256*256*sizeof(int));

         int i,j;
         int Color1_;
         int Color2_;
         int k;
         for(i=0;i<img->height;i++)
                  for(j=0;j<img->width;j++)
                  {
                           k=(ptr[i*img->widthStep+j*3]+ptr[i*img->widthStep+j*3+1]+ptr[i*img->widthStep+j*3+2]);
                           if (k!=0) Color1_=int((double)256*ptr[i*img->widthStep+j*3]/k);
                           else Color1_ = 0;
                           if (Color1_>255) Color1_=255;                           
                           if (k!=0) Color2_=int((double)256*ptr[i*img->widthStep+j*3+1]/k);
                           else Color2_ = 0;
                           if (Color2_>255) Color2_=255;
                           m[Color2_+Color1_*256]++;
                  }
         int max = 1;
         for(i=0;i<256;i++)
                  for(j=0;j<256;j++)
                           if (m[i*256+j]>max) max=m[i*256+j];

         for(i=0;i<256;i++)
                  for(j=0;j<256;j++)
                  {
                           k=int((double)256*sqrt(sqrt((double)m[i*256+j]/max)));
                           if (k>255) k=255;
                           //if (m[i*256+j]>0) k = 255;
                           ptr2[i*Gray->widthStep+j]=k;
                  }

         cvNamedWindow( "2", 1 );       
         cvNamedWindow( "1", 1 ); 
         cvSetMouseCallback( "2", on_mouse, 0 );

         int radius = 5;

         for(;;)
         {
                  cvCvtColor(Gray,Gray1,CV_GRAY2BGR);
                  cvCopy(img,img2);
                  if (Point_On)
                  {
                           cvCircle(Gray1,cvPoint(Cursor_x,Cursor_y),radius,cvScalar(0,0,255));

                           for(i=0;i<img->height;i++)
                                        for(j=0;j<img->width;j++)
                                        {
                                                 k=(ptr[i*img->widthStep+j*3]+ptr[i*img->widthStep+j*3+1]+ptr[i*img->widthStep+j*3+2]);
                                                 if (k!=0) Color1_=int((double)256*ptr[i*img->widthStep+j*3]/k);
                                                 else Color1_ = 0;
                                                 if (Color1_>255) Color1_=255;                     
                                                 if (k!=0) Color2_=int((double)256*ptr[i*img->widthStep+j*3+1]/k);
                                                 else Color2_ = 0;
                                                 if (Color2_>255) Color2_=255;
                                                 if (sqrt((float)pow((float)Color2_-Cursor_y,2)+(float)pow((float)Color1_-Cursor_x,2))>radius)
                                                 {
                                                          ptr_[i*img2->widthStep+j*3] = 0;
                                                          ptr_[i*img2->widthStep+j*3+1] = 0;
                                                          ptr_[i*img2->widthStep+j*3+2] = 0;
                                                 }
                                        }
                  }               
                  cvShowImage("2",Gray1);
                  cvShowImage("1",img2);
                  int c=cvWaitKey(50);          
                  if (c=='w') radius++;
                  if (c=='s') radius--;
                  if (radius<1) radius = 1;
                  if (radius>40) radius=40;
                  if (c==32) break;
         }
}


void on_mouse( int event, int x, int y, int flags, void* param )
{
    switch( event )
    {
    case CV_EVENT_LBUTTONDOWN:      
                Cursor_x = x;
                Cursor_y = y;
                Point_On=!Point_On;
        break;
    case CV_EVENT_LBUTTONUP:                                    
        break;
        case CV_EVENT_MOUSEMOVE:        
                Cursor_x = x;
                Cursor_y = y;
                break;
    }
}

