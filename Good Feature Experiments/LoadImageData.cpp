#include "data_structure.h"

void save(FileStorage fs,vector<vector<KeyPoint>> &transformedKeyPoints,vector<Mat> &transformedDescriptors, vector<struct ImageData> &result, int imageNum, float scale, int angle, int gaussian, int cnt){
	struct ImageData data ;
	vector<KeyPoint> keypointTemp;
	Mat descriptorTemp;
	char name[100];

	data.angle = angle;
	data.scale = scale;
	data.dbImageNum = imageNum;
	data.gaussian = gaussian;

	sprintf(name, "K_%d_%d_%d_%d",imageNum,(int)(scale*10),angle,gaussian);
	FileNode features = fs[name];
	read(features, keypointTemp);

	sprintf(name, "D_%d_%d_%d_%d",imageNum,(int)(scale*10),angle,gaussian);
	fs[name] >> descriptorTemp;

	transformedKeyPoints.push_back(keypointTemp);
	transformedDescriptors.push_back(descriptorTemp);

	result.push_back(data);
	return;
}

void LoadData(vector<KeyPoint> &referenceKeyPoints, vector<vector<KeyPoint>> &transformedKeyPoints, Mat &referenceDescriptor, vector<Mat> &transformedDescriptors, vector<struct ImageData> &result){
	int cnt = 0;	
	char name[100];
	
	float maxScale = MAX_SCALE;
	int maxDBSize = MAX_DB_SIZE;

	//File open 
	FileStorage fs("../Transformed Images Generator/Data.xml",FileStorage::READ);

	if(!fs.isOpened())
	{
		cout << "FILE NOT FOUND";
		return;
	}

	//Read reference image keypoints and descriptors
	sprintf(name, "K_%d_%d_%d_%d",1, -10, -1, -1);
	FileNode features = fs[name];
	read(features, referenceKeyPoints);

	sprintf(name, "D_%d_%d_%d_%d",1, -10, -1, -1);
	fs[name] >> referenceDescriptor;


	//Read transformed image keypoints and descriptors
	for(int imageNum = 1 ; imageNum <= maxDBSize; imageNum++){
		for(float scale = MIN_SCALE; scale <= maxScale; scale += SCALE_INCREASE){			//scale 변화
			for(int angle = 0; angle < 360; angle += ANGLE_INCREASE){						//angle 변화
				for(int gaussian = 0; gaussian < 8; gaussian+=2){
					if(gaussian == 2)
						gaussian++;

					save(fs, transformedKeyPoints,transformedDescriptors, result, imageNum, scale, angle, gaussian,cnt);
					cnt++;
				}
			}
		}
	}
	return;
}

void LoadImage(int num, int& width, int& height){
	char dbFilename[100];
	sprintf(dbFilename,"../Transformed Images Generator/dbImage/%d.jpg", num);	
	IplImage *dbImage = cvLoadImage(dbFilename);

	width = dbImage->width;
	height = dbImage->height;

	return;
}