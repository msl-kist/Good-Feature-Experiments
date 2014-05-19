#include "data_structure.h"

float calcDistance(CvPoint point, KeyPoint rotatedPoint){
	int x = rotatedPoint.pt.x - point.x;
	int y = rotatedPoint.pt.y - point.y;
	return sqrt((float)x*(float)x+(float)y*(float)y);
}


CvPoint rotatePoint;
float scale;
int angle;

bool getRotatedPoint(KeyPoint refernceKeyPoint, vector<KeyPoint> &transformedKeyPoints, 
struct ImageData &result,int width, int height, CvPoint center,struct Data& temp,Mat &transformedDescriptors)
{

	CvPoint point = cvPoint(refernceKeyPoint.pt.x* result.scale + (center.x - (width * result.scale / 2)) , refernceKeyPoint.pt.y*result.scale + (center.y - (height * result.scale / 2)));
	point.x = point.x - center.x;
	point.y = point.y - center.y;


	rotatePoint.x = center.x + point.x * cos(result.angle * DEG_TO_RAD) - point.y * sin(result.angle * DEG_TO_RAD);
	rotatePoint.y = center.y + (point.x * sin(result.angle * DEG_TO_RAD)) + (point.y * cos(result.angle * DEG_TO_RAD));

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
			temp.keypoint = transformedKeyPoints.at(i);
              temp.cornerness = 1;
			temp.descriptor = transformedDescriptors.row(i);
			

			return true;
		}
	}	
	temp.keypoint = NULL_KEYPOINT;
	temp.cornerness = 0;

	return false;
}

void CornernessTest(vector<KeyPoint> &referenceKeyPoints, vector<KeyPoint> &transformedKeyPoints 				// K and K'
	,Mat &transformedDescriptors, struct ImageData &result, int width, int height)
{
	int t = 0;
	int f = 0;
	int w = width*result.scale;
	int h = height*result.scale;

	scale = result.scale;
	angle = result.angle;

	float rotatedWidth = sqrt((double)w * (double)w + h * h);

	CvPoint center;
	center.x = center.y = rotatedWidth / 2.0;


	for(int i = 0; i < referenceKeyPoints.size(); i++){
		struct Data temp;
		if(getRotatedPoint(referenceKeyPoints.at(i),transformedKeyPoints,result,width,height,center,temp,transformedDescriptors)){
			t++;
		}
		else{
			f++;
		}
		result.data.push_back(temp);
	}

	cout<<t << " " << f<<endl;
}