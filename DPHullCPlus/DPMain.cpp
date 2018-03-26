#include  <iostream>
#include "LineApproximator.h"
#include "DPHull.h"
#include "PathHull.h"
#include <vector>
//#include "Containers.h"
using namespace std;
using namespace hull;
//typedef vector<TPoint<float>> VectorPointContainer;
//typedef vector<VectorPointContainer::const_iterator> ListKeyContainer;
//typedef TDPHull<float,VectorPointContainer,ListKeyContainer> CDPHullF;
typedef TPoint<float> FP;


int main() {
	CDPHullF dp;
	CDPHullF::PointContainer& pc = dp.GetPoints();
	CDPHullF::KeyContainer& kc  = dp.GetKeys();
	CDPHullF::PointContainer::const_iterator it,a;
	CDPHullF::KeyContainer::const_iterator k;
	for(int i = 1; i<=10; i++ ) {
		float x = (float) i;
		float y = sin(x);
		FP fp(x,y);
		pc.push_back(fp);
	}

	dp.ComputeBoundingBox();
	dp.SetTol(0.1);
	dp.Simplify();

	for(k = kc.begin(); k != kc.end(); k++) {
		cout<<"x="<< (*k)->x <<endl;
	}


	cout<<"Hello World!"<<endl;
}


