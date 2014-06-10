#include "data_structure.h"

float calcDistance(CvPoint point, KeyPoint rotatedPoint){
	int x = rotatedPoint.pt.x - point.x;
	int y = rotatedPoint.pt.y - point.y;
	return sqrt((float)x*(float)x+(float)y*(float)y);
}


CvPoint rotatePoint;
float scale;
int angle;

bool getRotatedPoint(KeyPoint refernceKeyPoint, Mat &refernceDescriptors, vector<KeyPoint> &transformedKeyPoints, 
	struct ImageData &imageData,int width, int height, CvPoint center,Mat &transformedDescriptors, 
		vector<KeyPoint> &cornerTestKeyPoints, Mat &cornerTestDescriptors)
{

	CvPoint point = cvPoint(refernceKeyPoint.pt.x* imageData.scale + (center.x - (width * imageData.scale / 2)) , refernceKeyPoint.pt.y*imageData.scale + (center.y - (height * imageData.scale / 2)));
	point.x = point.x - center.x;
	point.y = point.y - center.y;


	rotatePoint.x = center.x + point.x * cos(imageData.angle * DEG_TO_RAD) - point.y * sin(imageData.angle * DEG_TO_RAD);
	rotatePoint.y = center.y + (point.x * sin(imageData.angle * DEG_TO_RAD)) + (point.y * cos(imageData.angle * DEG_TO_RAD));

	for(int i = 0; i < transformedKeyPoints.size(); i++){
		// 		char filename[100];
		// 		memset(filename,0,100);
		// 		sprintf(filename,"../Transformed Images Generator/testset/%d_%.1f_%d_0.png", 1,scale,angle);	
		// 		IplImage *image = cvLoadImage(filename);
		// 
		// 		cvCircle(image,rotatePoint,2,cvScalar(0,255,0),2);
		// 
		// 		cvCircle(image,transformedKeyPoints.at(i).pt,2,cvScalar(0,255,0),2);
		// 		cvShowImage("sss",image);
		// 		cvWaitKey(0);
		//		cvReleaseImage(&image);
		if(calcDistance(rotatePoint,transformedKeyPoints.at(i)) < 2){
			cornerTestKeyPoints.push_back(transformedKeyPoints.at(i));
			cornerTestDescriptors.push_back(transformedDescriptors.row(i));
			return true;
		}
	}	
	cornerTestKeyPoints.push_back(NULL_KEYPOINT);
	cornerTestDescriptors.push_back(refernceDescriptors.row(0));

	return false;
}

void CornernessTest(vector<KeyPoint> &referenceKeyPoints, Mat &referenceDescriptors, 
	vector<KeyPoint> &transformedKeyPoints ,Mat &transformedDescriptors, struct ImageData &imageData, 
	vector<struct Data>& result, vector<KeyPoint> &cornerTestKeyPoints, Mat &cornerTestDescriptors, 
	int width, int height)
{
	int t = 0;
	int f = 0;
	int w = width*imageData.scale;
	int h = height*imageData.scale;

	scale = imageData.scale;
	angle = imageData.angle;

	float rotatedWidth = sqrt((double)w * (double)w + h * h);

	CvPoint center;
	center.x = center.y = rotatedWidth / 2.0;


	for(int i = 0; i < referenceKeyPoints.size(); i++){

		if(getRotatedPoint(referenceKeyPoints.at(i), referenceDescriptors, transformedKeyPoints,imageData, width, height, center, transformedDescriptors, cornerTestKeyPoints, cornerTestDescriptors)){
			result[i].cornerness++;
			t++;
		}
		else{
			f++;
		}
	}

	//cout<< angle<< " " << scale << " " << t << " " << f<<endl;
}