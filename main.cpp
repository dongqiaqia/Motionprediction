#include "MotionPredict.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;




int main(int argc, char* argv[]){
	string filename = "../Pedestrian00001.ann";
	ifstream fn;
	fn.open(filename);
	string line;
	
	Motion motion(9);
	Rect _roi;

	while(!fn.eof()){
		getline(fn,line);

		istringstream ss(line);

		// Read groundtruth like a dumb
	  	float fr, xMin, yMin, xMax, yMax, cx,cy,width, height,vx,vy,vw,vh;
	  	ss >> fr;
		ss >> xMin;
		ss >> yMin;
		ss >> xMax;
		ss >> yMax;
		width = xMax - xMin;
		height = yMax - yMin;
		_roi = Rect(xMin,yMin,width,height);
		if(fr == 1){
			cout<<fr<<endl;
			motion.update(_roi,fr);
			cout<<endl;
			continue;			
		}
		else{
			cout<<fr<<endl;
			motion.predict(fr);
			motion.update(_roi,fr);
			cout<<endl;
		}
	}

}