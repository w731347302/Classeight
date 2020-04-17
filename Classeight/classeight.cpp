#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void text1(Mat t1)
{
	Mat gray;
	cvtColor(t1, gray, COLOR_RGB2GRAY);
	medianBlur(gray, gray, 3);
	Mat thre;
	threshold(gray, thre, 120, 255, THRESH_BINARY_INV);

	Mat kernal = getStructuringElement(MORPH_RECT, Size(3, 3));
	erode(thre, thre, kernal);

	vector<vector<Point>> con;
	findContours(thre, con, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	//vector<double> area;
	for (size_t i = 0; i < con.size(); i++)
	{
		RotatedRect rbox = minAreaRect(con[i]);
		//area.push_back(contourArea(con[i]));
		//
		if ((rbox.size.height / rbox.size.width) < 1 && contourArea(con[i]) > 1000)
		{
			drawContours(t1, con, i, Scalar(0, 255, 255), -1, 8);
			/*
			Point2f vtx[4];
			rbox.points(vtx);
			for (int j = 0; j < 4; j++)
			{
				line(t1, vtx[j], vtx[j < 3 ? j + 1 : 0], Scalar(0, 0, 255));
			}
			*/
		}
	}

	imshow("res", t1);
	waitKey(0);
}


void text2(Mat t2)
{
	Mat gray;
	cvtColor(t2, gray, COLOR_RGB2GRAY);
	//medianBlur(gray, gray, 3);
	Mat thre;
	threshold(gray, thre, 120, 255, THRESH_BINARY);

	Mat kernal = getStructuringElement(MORPH_RECT, Size(3, 3));
	erode(thre, thre, kernal);

	vector<vector<Point>> con;
	findContours(thre, con, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	//vector<double> area;
	for (size_t i = 0; i < con.size(); i++)
	{
		RotatedRect rbox = minAreaRect(con[i]);
		//area.push_back(contourArea(con[i]));
		
		if (contourArea(con[i]) > 2000)
		{
			drawContours(t2, con, i, Scalar(0, 255, 255), 1, 8);
			Point2f vtx[4];
			rbox.points(vtx);
			for (int j = 0; j < 4; j++)
			{
				line(t2, vtx[j], vtx[j < 3 ? j + 1 : 0], Scalar(0, 0, 255));
			}
			
		}
	}

	imshow("res2", t2);
	waitKey(0);
}

int main()
{
	Mat t1 = imread("rim.png");
	Mat t2 = imread("die_on_chip.png");
	Mat t3 = imread("topic1.JPG");

	text1(t1);
	text2(t2);


	return 0;
}