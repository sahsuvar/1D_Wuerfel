/*
 * CControlComp.h
 *
 *  Created on: Dec 13, 2017
 *      Author: ChriPhiPa
 */

#ifndef CCONTROLCOMP_H_
#define CCONTROLCOMP_H_

#include <unistd.h>
#include <sys/time.h>
#include <iostream>
#include <cmath>

#include"CContainer.h"
#include "Global.h"
#include "IRunnable.h"
#include "CBBBHardware.h"


extern CContainer myContainer;

class CControlComp:public IRunnable
{
	public:
		void run();
		void init();
		void fetchValues();
		void calib();
		void filter();
		void control();


	private:
		CBBBHardware mHardware;
		UInt16 mAdcValue;
//		float torque;
		SMPU6050Data mSensorData1;
		SMPU6050Data mSensorData2;
		SStateVectorData mSensorData;

		double mPhi;
		double mPhi_d;
		double mPhi_c;
		double mPhi_c_old;

		double mPsi_d;
};

#endif /* CCONTROLCOMP_H_ */
