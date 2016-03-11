// Thin.cpp : �������̨Ӧ�ó������ڵ㡣
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
		printf("ֻ�ܴ����ֵ��Ҷ�ͼ��\n");
		return;
	}
	//��ԭ�ز���ʱ��copy src��dst
	if (dst.data != src.data)
	{
		src.copyTo(dst);
	}

	int i, j, n;
	int width, height;
	width = src.cols - 1;
	//֮���Լ�1���Ƿ��㴦��8���򣬷�ֹԽ��
	height = src.rows - 1;
	int step = src.step;
	int  p2, p3, p4, p5, p6, p7, p8, p9;
	unsigned char* img;
	bool ifEnd;
	int A1;
	cv::Mat tmpimg;
	//n��ʾ��������
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
					if (p[-step] == 0 && p[-step + 1] > 0) //p2,p3 01ģʽ
					{
						A1++;
					}
					if (p[-step + 1] == 0 && p[1] > 0) //p3,p4 01ģʽ
					{
						A1++;
					}
					if (p[1] == 0 && p[step + 1] > 0) //p4,p5 01ģʽ
					{
						A1++;
					}
					if (p[step + 1] == 0 && p[step] > 0) //p5,p6 01ģʽ
					{
						A1++;
					}
					if (p[step] == 0 && p[step - 1] > 0) //p6,p7 01ģʽ
					{
						A1++;
					}
					if (p[step - 1] == 0 && p[-1] > 0) //p7,p8 01ģʽ
					{
						A1++;
					}
					if (p[-1] == 0 && p[-step - 1] > 0) //p8,p9 01ģʽ
					{
						A1++;
					}
					if (p[-step - 1] == 0 && p[-step] > 0) //p9,p2 01ģʽ
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
							dst.at<unsigned char>(i, j) = 0; //����ɾ�����������õ�ǰ����Ϊ0
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
					if (p[-step] == 0 && p[-step + 1] > 0) //p2,p3 01ģʽ
					{
						A1++;
					}
					if (p[-step + 1] == 0 && p[1] > 0) //p3,p4 01ģʽ
					{
						A1++;
					}
					if (p[1] == 0 && p[step + 1] > 0) //p4,p5 01ģʽ
					{
						A1++;
					}
					if (p[step + 1] == 0 && p[step] > 0) //p5,p6 01ģʽ
					{
						A1++;
					}
					if (p[step] == 0 && p[step - 1] > 0) //p6,p7 01ģʽ
					{
						A1++;
					}
					if (p[step - 1] == 0 && p[-1] > 0) //p7,p8 01ģʽ
					{
						A1++;
					}
					if (p[-1] == 0 && p[-step - 1] > 0) //p8,p9 01ģʽ
					{
						A1++;
					}
					if (p[-step - 1] == 0 && p[-step] > 0) //p9,p2 01ģʽ
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
							dst.at<unsigned char>(i, j) = 0; //����ɾ�����������õ�ǰ����Ϊ0
							ifEnd = true;
						}
					}
				}
			}
		}

		//��������ӵ����Ѿ�û�п���ϸ���������ˣ����˳�����
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
	long start_time = clock();//Cpu�����㷨ʱ�� ��ʼ��
	int Cnt_intera = 0;
	Thin_Fun(mat, dst, 100, Cnt_intera);
	long end_time = clock();//Cpu �㷨��ʱ���
	float timex = float(end_time - start_time);

	printf("�ݹ����= %d\n\n", Cnt_intera);
	printf("�㷨����ʱ��=%d����\n\n", timex);

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