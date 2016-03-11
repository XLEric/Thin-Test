// Thin.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <cv.h>
#include <opencv2/opencv.hpp>
#include <highgui.h>

using namespace cv;
void Thin_Fun(cv::Mat& src, cv::Mat& dst, int intera, int &Cnt_intera)
{
	if (src.type() != CV_8UC1)
	{
		printf("只能处理二值或灰度图像\n");
		return;
	}
	//非原地操作时候，copy src到dst
	if (dst.data != src.data)
	{
		src.copyTo(dst);
	}

	int i, j, n;
	int width, height;
	width = src.cols - 1;
	//之所以减1，是方便处理8邻域，防止越界
	height = src.rows - 1;
	int step = src.step;
	int  p2, p3, p4, p5, p6, p7, p8, p9;
	unsigned char* img;
	bool ifEnd;
	int A1;
	cv::Mat tmpimg;
	//n表示迭代次数
	for (n = 0; n < intera; n++)
	{
		dst.copyTo(tmpimg);
		ifEnd = false;
		img = tmpimg.data;
		for (i = 1; i < height; i++)
		{
			img += step;
			for (j = 1; j < width; j++)
			{
				unsigned char* p = img + j;
				A1 = 0;
				if (p[0] > 0)
				{
					if (p[-step] == 0 && p[-step + 1] > 0) //p2,p3 01模式
					{
						A1++;
					}
					if (p[-step + 1] == 0 && p[1] > 0) //p3,p4 01模式
					{
						A1++;
					}
					if (p[1] == 0 && p[step + 1] > 0) //p4,p5 01模式
					{
						A1++;
					}
					if (p[step + 1] == 0 && p[step] > 0) //p5,p6 01模式
					{
						A1++;
					}
					if (p[step] == 0 && p[step - 1] > 0) //p6,p7 01模式
					{
						A1++;
					}
					if (p[step - 1] == 0 && p[-1] > 0) //p7,p8 01模式
					{
						A1++;
					}
					if (p[-1] == 0 && p[-step - 1] > 0) //p8,p9 01模式
					{
						A1++;
					}
					if (p[-step - 1] == 0 && p[-step] > 0) //p9,p2 01模式
					{
						A1++;
					}
					p2 = p[-step] > 0 ? 1 : 0;
					p3 = p[-step + 1] > 0 ? 1 : 0;
					p4 = p[1] > 0 ? 1 : 0;
					p5 = p[step + 1] > 0 ? 1 : 0;
					p6 = p[step] > 0 ? 1 : 0;
					p7 = p[step - 1] > 0 ? 1 : 0;
					p8 = p[-1] > 0 ? 1 : 0;
					p9 = p[-step - 1] > 0 ? 1 : 0;
					if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) > 1 && (p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) < 7 && A1 == 1)
					{
						if ((p2 == 0 || p4 == 0 || p6 == 0) && (p4 == 0 || p6 == 0 || p8 == 0)) //p2*p4*p6=0 && p4*p6*p8==0
						{
							dst.at<unsigned char>(i, j) = 0; //满足删除条件，设置当前像素为0
							ifEnd = true;
						}
					}
				}
			}
		}

		
		dst.copyTo(tmpimg);
		img = tmpimg.data;
		for (i = 1; i < height; i++)
		{
			img += step;
			for (j = 1; j < width; j++)
			{
				A1 = 0;
				unsigned char* p = img + j;
				if (p[0] > 0)
				{
					if (p[-step] == 0 && p[-step + 1] > 0) //p2,p3 01模式
					{
						A1++;
					}
					if (p[-step + 1] == 0 && p[1] > 0) //p3,p4 01模式
					{
						A1++;
					}
					if (p[1] == 0 && p[step + 1] > 0) //p4,p5 01模式
					{
						A1++;
					}
					if (p[step + 1] == 0 && p[step] > 0) //p5,p6 01模式
					{
						A1++;
					}
					if (p[step] == 0 && p[step - 1] > 0) //p6,p7 01模式
					{
						A1++;
					}
					if (p[step - 1] == 0 && p[-1] > 0) //p7,p8 01模式
					{
						A1++;
					}
					if (p[-1] == 0 && p[-step - 1] > 0) //p8,p9 01模式
					{
						A1++;
					}
					if (p[-step - 1] == 0 && p[-step] > 0) //p9,p2 01模式
					{
						A1++;
					}
					p2 = p[-step] > 0 ? 1 : 0;
					p3 = p[-step + 1] > 0 ? 1 : 0;
					p4 = p[1] > 0 ? 1 : 0;
					p5 = p[step + 1] > 0 ? 1 : 0;
					p6 = p[step] > 0 ? 1 : 0;
					p7 = p[step - 1] > 0 ? 1 : 0;
					p8 = p[-1] > 0 ? 1 : 0;
					p9 = p[-step - 1] > 0 ? 1 : 0;
					if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) > 1 && (p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) < 7 && A1 == 1)
					{
						if ((p2 == 0 || p4 == 0 || p8 == 0) && (p2 == 0 || p6 == 0 || p8 == 0)) //p2*p4*p8=0 && p2*p6*p8==0
						{
							dst.at<unsigned char>(i, j) = 0; //满足删除条件，设置当前像素为0
							ifEnd = true;
						}
					}
				}
			}
		}

		//如果两个子迭代已经没有可以细化的像素了，则退出迭代
		Cnt_intera++;
		if (!ifEnd) break;
	}

}

int _tmain(int argc, _TCHAR* argv[])
{


	int w = 176, h = 120;
	IplImage *gray = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 1);
	IplImage *Bimg = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 1);
	IplImage* src = cvLoadImage("A99.bmp");


	cvCvtColor(src, gray, CV_BGR2GRAY);
	//cvShowImage("Gray",gray);
	cvThreshold(gray, Bimg, 40, 1, CV_THRESH_BINARY);

	Mat mat = cvCreateMat(src->height, src->width, CV_32SC1);
	mat = Bimg;
	//mat(Bimg);

	Mat dst = cvCreateMat(src->height, src->width, CV_32SC1);

	FILE* file = fopen("log.txt", "a+");
	long start_time = clock();//Cpu测试算法时间 起始：
	int Cnt_intera = 0;
	Thin_Fun(mat, dst, 100, Cnt_intera);
	long end_time = clock();//Cpu 算法计时完成
	float timex = float(end_time - start_time);

	printf("递归次数= %d\n\n", Cnt_intera);
	printf("算法运行时间=%d毫秒\n\n", timex);

	printf("\n");
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			//printf(" %d ", dst.at<unsigned char>(i, j));
			fprintf(file, "%d", dst.at<unsigned char>(i, j));
		}
		//printf("\n");
		fprintf(file, "\n");
	}
	
	fclose(file);
	
	system("pause");
	return 0;
}