#include "data_structure.h"
#include "parameters.h"

float calcMatchDistance(CvPoint point, KeyPoint rotatedPoint){
	int x = rotatedPoint.pt.x - point.x;
	int y = rotatedPoint.pt.y - point.y;
	return sqrt((float)x*(float)x+(float)y*(float)y);
}


void countCorrectMatch(vector<KeyPoint> referenceKeyPoint, Mat &refernceDescriptors, vector<KeyPoint> &transformedKeyPoints, 
struct ImageData &imageData, vector<struct Data>& result, int width, int height, 
	CvPoint center,Mat &transformedDescriptors, std::vector<DMatch> matches)
{

	for(int i = 0; i < matches.size(); i++){
		int i1 = matches[i].queryIdx; 
		int i2 = matches[i].trainIdx; 
		
		CvPoint point = cvPoint(referenceKeyPoint[i1].pt.x* imageData.scale + (center.x - (width * imageData.scale / 2)) , referenceKeyPoint[i1].pt.y*imageData.scale + (center.y - (height * imageData.scale / 2)));
		point.x = point.x - center.x;
		point.y = point.y - center.y;

		CvPoint rotatePoint;
		rotatePoint.x = center.x + point.x * cos(imageData.angle * DEG_TO_RAD) - point.y * sin(imageData.angle * DEG_TO_RAD);
		rotatePoint.y = center.y + (point.x * sin(imageData.angle * DEG_TO_RAD)) + (point.y * cos(imageData.angle * DEG_TO_RAD));
		

		if(calcMatchDistance(rotatePoint,transformedKeyPoints.at(i2)) < 2){
			result[i1].matchScore++;
		}
	}
}


void MatchingCountTest(vector<KeyPoint> &referenceKeyPoints, Mat &referenceDescriptors, 
	vector<KeyPoint> &transformedKeyPoints ,Mat &transformedDescriptors, struct ImageData &imageData, 
	vector<struct Data>& result, int width, int height)
{
	BruteForceMatcher<Hamming> matcher; 
	std::vector<DMatch> matches, matches_opp, matches_best;
	int w = width*imageData.scale;
	int h = height*imageData.scale;
	if(transformedDescriptors.rows>0){
		matcher.match(referenceDescriptors, transformedDescriptors, matches);
		matcher.match(transformedDescriptors, referenceDescriptors, matches_opp);
		gcFilterMatches(matches, matches_opp, matches_best, referenceKeyPoints, transformedKeyPoints);			

		float rotatedWidth = sqrt((double)w * (double)w + h * h);

		CvPoint center;
		center.x = center.y = rotatedWidth / 2.0;
		if(matches_best.size()>0)
			countCorrectMatch(referenceKeyPoints,referenceDescriptors,transformedKeyPoints,imageData,result,width,height,center,transformedDescriptors, matches_best);
	}
}