#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/objdetect/objdetect.hpp>
using namespace std;
using namespace cv;

int main()
{

    Mat a;
    VideoCapture cap(0);
    while(true){

    if(!cap.isOpened()){

         cout<< "Camera cannot be opened"<<endl;
        exit(1);

    }
    else{
      cap >> a;
      imshow("Test ",a);
      waitKey(2);


    }
    }



    return 0;
}
