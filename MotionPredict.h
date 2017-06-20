#ifndef MOTIONPREDICT_HPP
#define MOTIONPREDICT_HPP

#include <iostream>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

class Motion{
public:
	int fr;//record lastest tracked frame num and object location
	float cx;
	float cy;
	float w;
	float h;
	int index;//record the oldest index of the velocity
	vector<float> Vx;//the memory of the lastest tracked velocity
	vector<float> Vy;
	vector<float> Vw;
	vector<float> Vh;

	int len;//the length of memory

	Motion(int n);
	Rect predict(int frnum);//prediction next frame location
	void update(Rect observ,int fr);
};

#endif