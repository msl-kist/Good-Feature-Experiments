#include "data_structure.h"

struct Data
{
	cv::KeyPoint	keypoint;
	cv::Mat			descriptor;

	int	cornerness;					// 실험 1) cornerness(n_exist)  - n_exist / n_transformed
	vector<float>	selfSimilarity; // 실험 2) Self Similarity	- 개수: # of transformed images
	//vector						// 실험 3) Histogram
};