/************************************************************************/
/* 이미지 변환 및 저장 모듈
/*		저장은 $(SolutionDir)/$(ConfigurationName) 에 저장되기 때문에 이곳에 저장하면 바로 실험 프로젝트에서 읽을 수 있음
/************************************************************************/

#include <stdio.h>

#include <opencv2/opencv.hpp>
#include "OpenCv2.4.5_libs.h"
#include "value.h"

using namespace cv;
using namespace std;

/************************************************************************/
/* 이미지 Rotate
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
/* 이미지 사이즈 조정 및 Rotate
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


	//복사하고 회전
	cvSetImageROI(rotateImage, cvRect(center.x - temp->width / 2.0, center.y - temp->height / 2.0, temp->width, temp->height));
	cvCopy(temp,rotateImage);
	cvResetImageROI(rotateImage);


	IplImage *imageRotated;
	imageRotated = transform(rotateImage, angleDegrees, rotateImage->width/2, rotateImage->height/2, 1,1, 0,0 );

	cvReleaseImage(&temp);
	cvReleaseImage(&rotateImage);

	return imageRotated;
}


int main()
{
	char filename[100];
	char dbFilename[100];

	IplImage* rotImage = NULL;
	IplImage* gaussianImage = NULL;

	int maxScale = MAX_SCALE;
	int maxDBSize = MAX_DB_SIZE;

	for(int i = 0 ; i < maxDBSize; i++ ){
		sprintf(dbFilename,"dbImage/%d.jpg", i+1);	
		IplImage *dbImage = cvLoadImage(dbFilename);
		
		for(float scale = MIN_SCALE; scale <= maxScale; scale += SCALE_INCREASE){			//scale 변화
			for(int angle = 0; angle < 360; angle += ANGLE_INCREASE){						//angle 변화
				//rotate
				rotImage = rotateImage(dbImage,angle,scale);

				//Save Image (원본)
				sprintf(filename,"testset/%d_%.1f_%d_%d.png", 1,scale,angle,0);	
				cvSaveImage(filename,rotImage);
				cout<<filename << " is saved."<<endl;

				//Gaussian blur 총 3번을 한다.
				for(int i = 3 ; i < 8;i+=2){
					gaussianImage = cvCreateImage(cvSize(rotImage->width, rotImage->height), IPL_DEPTH_8U, 3);
					cvSmooth(rotImage,gaussianImage,CV_GAUSSIAN,i,i);

					//Save Image (Gaussian)
					sprintf(filename,"testset/%d_%.1f_%d_%d.png", 1,scale,angle,i);	
					cvSaveImage(filename,gaussianImage);

					cvReleaseImage(&gaussianImage);

				}
				cvReleaseImage(&rotImage);
			}
		}
	}
}