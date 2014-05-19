/************************************************************************/
/* �̹��� ��ȯ �� ���� ���
/*		������ $(SolutionDir)/$(ConfigurationName) �� ����Ǳ� ������ �̰��� �����ϸ� �ٷ� ���� ������Ʈ���� ���� �� ����
/************************************************************************/

#include <stdio.h>

#include <opencv2/legacy/legacy.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/gpu/gpu.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "OpenCv2.4.5_libs.h"
#include "value.h"
#include "brisk/brisk.h"
using namespace cv;
using namespace std;

/************************************************************************/
/* �̹��� Rotate
/************************************************************************/
IplImage *transform(const IplImage *src, float angle, float centerX, float centerY,
	float scaleX, float scaleY,
	float moveX, float moveY ){
		IplImage *imageRotated = cvCreateImage(cvSize(src->width,src->height),src->depth,3);

		float sina = sin(-angle * DEG_TO_RAD);
		float cosa = cos(-angle * DEG_TO_RAD);
		CvMat*  transmat = cvCreateMat( 2,3, CV_32F );
		cvmSet( transmat, 0,0, scaleX*cosa );
		cvmSet( transmat, 0,1, scaleY*sina );
		cvmSet( transmat, 0,2, -centerX*scaleX*cosa - centerY*scaleY*sina + moveX + centerX );
		cvmSet( transmat, 1,0, -1.0*scaleX*sina );
		cvmSet( transmat, 1,1, scaleY*cosa );
		cvmSet( transmat, 1,2, -centerY*scaleY*cosa + centerX*scaleX*sina + moveY + centerY);

		cvWarpAffine( src, imageRotated, transmat);

		cvReleaseMat( &transmat );
		return imageRotated;
}

/************************************************************************/
/* �̹��� ������ ���� �� Rotate
/************************************************************************/
IplImage *rotateImage(const IplImage *src, int angleDegrees, double scale)
{
	//resize
	int w = src->width * scale;
	int h = src->height * scale;
	IplImage* temp= cvCreateImage( cvSize(w,h), IPL_DEPTH_8U, 3 );
	cvResize( src, temp );

	float width = sqrt((double)temp->width * (double)temp->width + temp->height * temp->height);

	IplImage* rotateImage = cvCreateImage( cvSize(width,width), IPL_DEPTH_8U, 3 );
	cvSet(rotateImage,cvScalar(0));

	CvPoint center;
	center.x = rotateImage->width / 2.0;
	center.y = rotateImage->height / 2.0;


	//�����ϰ� ȸ��
	cvSetImageROI(rotateImage, cvRect(center.x - temp->width / 2.0, center.y - temp->height / 2.0, temp->width, temp->height));
	cvCopy(temp,rotateImage);
	cvResetImageROI(rotateImage);


	IplImage *imageRotated;
	imageRotated = transform(rotateImage, angleDegrees, rotateImage->width/2, rotateImage->height/2, 1,1, 0,0 );

	cvReleaseImage(&temp);
	cvReleaseImage(&rotateImage);

	return imageRotated;
}

void computeDescriptors(FileStorage* fs,IplImage* image,Ptr<FeatureDetector>& detector, cv::Ptr<cv::DescriptorExtractor>& descriptor, int imageNum,float scale, int angle, int gaussian)
{
	char name[100];
	vector<cv::KeyPoint> keyPoints;

	vector<cv::KeyPoint> keyPoints_brisk;
	Mat descriptors;

	Mat mat = Mat(image);
	Mat mat_gray(mat.size(),CV_8U);

	cv::cvtColor(mat, mat_gray, CV_BGR2GRAY);

	detector->detect(mat_gray, keyPoints);
	descriptor->compute(mat_gray, keyPoints, descriptors);

	sprintf(name, "K_%d_%d_%d_%d",imageNum,(int)(scale*10),angle,gaussian);
	write(*fs, name, keyPoints);
	sprintf(name, "D_%d_%d_%d_%d",imageNum,(int)(scale*10),angle,gaussian);
	write(*fs, name, descriptors);
	
}



int main()
{
	char filename[100];
	char dbFilename[100]={0,};

	IplImage* rotImage = NULL;
	IplImage* gaussianImage = NULL;

	float maxScale = MAX_SCALE;
	int maxDBSize = MAX_DB_SIZE;

	FileStorage fs("Data.xml",FileStorage::WRITE);
	
	//brisk ����
	Ptr<FeatureDetector> detector;
	cv::Ptr<cv::DescriptorExtractor> descriptor;

	detector = new BriskFeatureDetector(130, 5);
	descriptor = new cv::BriskDescriptorExtractor();
	memset(dbFilename, 0x00, sizeof(dbFilename));
	
	
	for(int i = 0 ; i < maxDBSize; i++ ){
		sprintf(dbFilename,"dbImage/%d.jpg", i+1);	
		IplImage *dbImage = cvLoadImage(dbFilename);

		computeDescriptors( &fs, dbImage, detector,  descriptor, i+1, -1, -1, -1);
		
		for(float scale = MIN_SCALE; scale <= maxScale; scale += SCALE_INCREASE){			//scale ��ȭ
			for(int angle = 0; angle < 360; angle += ANGLE_INCREASE){						//angle ��ȭ
				//rotate
				rotImage = rotateImage(dbImage,angle,scale);

				//Save Image (����)
				sprintf(filename,"testset/%d_%.1f_%d_%d.png", i+1,scale,angle,0);	
				cvSaveImage(filename,rotImage);
				computeDescriptors( &fs, rotImage, detector,  descriptor, i+1, scale, angle, 0);

				cout<<filename << " is saved."<<endl;

				//Gaussian blur �� 3���� �Ѵ�.
				for(int g = 3 ; g < 8;g+=2){
					gaussianImage = cvCreateImage(cvSize(rotImage->width, rotImage->height), IPL_DEPTH_8U, 3);
					cvSmooth(rotImage,gaussianImage,CV_GAUSSIAN,g,g);

					//Save Image (Gaussian)
					sprintf(filename,"testset/%d_%.1f_%d_%d.png", 1,scale,angle,g);	
					cvSaveImage(filename,gaussianImage);
					computeDescriptors( &fs, gaussianImage, detector,  descriptor, i+1, scale, angle, g);

					cvReleaseImage(&gaussianImage);

				}
				cvReleaseImage(&rotImage);
			}
		}
	}
}