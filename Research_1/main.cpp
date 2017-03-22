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

    int keyboard = 0;
	VideoCapture cap("/media/pi/MULTIBOOT/people.mp4");
	Mat image,a,b,c;



    while ((char)keyboard != 'q' && (char)keyboard != 27) {
		if (!cap.isOpened())
		{
			exit(EXIT_FAILURE);
		}
		cap >> c;
		if (c.empty())
		{
			exit(EXIT_FAILURE);

		}
		resize(c, a, Size(), 0.5, 0.5, INTER_CUBIC);
		b = a.clone();
		/////////use hog descriptor /////////////

		HOGDescriptor hog;
		hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
		vector<Rect> found, found_filtered;
		hog.detectMultiScale(a, found, 0, Size(4, 4), Size(16, 16), 1.05, 2);

		size_t i, j;
		for (i = 0; i < found.size(); i++)
		{
			Rect r = found[i];
			for (j = 0; j < found.size(); j++)
				if (j != i && (r & found[j]) == r)
					break;
			if (j == found.size())
				found_filtered.push_back(r);
		}
		vector<Mat> people;


		for (i = 0; i < found_filtered.size(); i++)
		{
			Rect r = found_filtered[i];


			///////draw the rectangle//////////////////////////////
			/*r.x += cvRound(r.width*0.1);
			r.width = cvRound(r.width*0.8);
			r.y += cvRound(r.height*0.06);
			r.height = cvRound(r.height*0.9);*/
			if (r.y > 0 && r.x > 0)
			{
			//	people.push_back(a(r));
			//	image = a(r).clone();
				rectangle(b, r.tl(), r.br(), cv::Scalar(0, 255, 0), 2);
			}


			cv::Mat result; // segmentation result (4 possible values)
			cv::Mat bgModel, fgModel;

			cv::grabCut(a,result,r,bgModel, fgModel,1,cv::GC_INIT_WITH_RECT);

			cv::compare(result, cv::GC_PR_FGD, result, cv::CMP_EQ);
			// Generate output image
			cv::Mat foreground(a.size(), CV_8UC3, cv::Scalar(255, 255, 255));
			a.copyTo(foreground, result); // bg pixels not copied
			//cv::rectangle(image rectangle, cv::Scalar(255, 255, 255), 1);
			//cv::imshow("Image",a);
			cv::imshow("Segmented Image", foreground);
			keyboard = waitKey(1);

		}

    }

return 0;
}
