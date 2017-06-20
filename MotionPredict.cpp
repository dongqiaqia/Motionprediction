#include "MotionPredict.h"

Motion::Motion(int n){
	len = n;
	index = 0;
	fr = 0;
}

Rect Motion::predict(int fnum){
	float vx,vy,vw,vh,predictX,predictY,predictW,predictH;	
	if(Vx.empty()){
		vx = 0.0;
		vy = 0.0;
		vw = 0.0;
		vh = 0.0;	
	}
	else{
		float sumVx = std::accumulate(std::begin(Vx), std::end(Vx),0.0);
		float sumVy = std::accumulate(std::begin(Vy), std::end(Vy),0.0);
		float sumVw = std::accumulate(std::begin(Vw), std::end(Vw),0.0);
		float sumVh = std::accumulate(std::begin(Vh), std::end(Vh),0.0);
		vx = sumVx/Vx.size();
		vy = sumVy/Vy.size();
		vw = sumVw/Vw.size();
		vh = sumVh/Vh.size();
	}

	predictX = cx + vx*(fnum-fr);
	predictY = cy + vy*(fnum-fr);
	predictW = w + vw*(fnum-fr);
	predictH = h + vh*(fnum-fr);

	cout<<"prediction velocity (dx,dy,dw,dh)"<< "("<<vx<<","<<vy<<","<<vw<<","<<vh<<")"<<endl;
	cout<<"prediction location (predictx,predicty)"<< "("<<predictX<<","<<predictY<<")"<<endl;
	cout<<"prediction scale (w,h)"<< "("<<predictW<<","<<predictH<<")"<<endl; 

	Rect pred(cx-w/2.0,cy-h/2.0,w,h);
	return pred;
}

void Motion::update(Rect observ,int fnum){
	float curr_cx = observ.x + observ.width/2.0;
	float curr_cy = observ.y + observ.height/2.0;

	cout<<"real location (cx,cy)"<< "("<<curr_cx<<","<<curr_cy<<")"<<endl;
	cout<<"real scale (w,h)"<< "("<<observ.width<<","<<observ.height<<")"<<endl; 

	if(fr != 0){

		float vx,vy,vw,vh;
		vx = (curr_cx - cx)/(fnum - fr);
		vy = (curr_cy - cy)/(fnum - fr);
		vw = (observ.width - w)/(fnum - fr);
		vh = (observ.height - h)/(fnum - fr);

		if(Vx.size()<len){
			Vx.push_back(vx);
			Vy.push_back(vy);
			Vw.push_back(vw);
			Vh.push_back(vh);
		}
		else{
			Vx[index] = vx;
			Vy[index] = vy;
			Vx[index] = vw;
			Vy[index] = vh;
			index ++;
			if(index == len)
				index = 0;
		}
	}
	fr = fnum;
	cx = curr_cx;
	cy = curr_cy;
	w = observ.width;
	h = observ.height;
}