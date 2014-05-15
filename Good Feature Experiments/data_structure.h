#include "data_structure.h"

struct Data
{
	cv::KeyPoint	keypoint;
	cv::Mat			descriptor;

	int	cornerness;					// ���� 1) cornerness(n_exist)  - n_exist / n_transformed
	vector<float>	selfSimilarity; // ���� 2) Self Similarity	- ����: # of transformed images
	//vector						// ���� 3) Histogram
};