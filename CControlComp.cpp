/*
 * CControlComp.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: ChriPhiPa
 */

#include "CControlComp.h"

void CControlComp::run()
{

	struct timeval timebegin, timemid, timeend; // Zur Zeitdifferenzberechnung
	time_t seconds, useconds; // Um Stückchen der Zeit zu bekommen


	while (1) {

		// Aktuelle Zeit erfassen
		gettimeofday(&timebegin, (struct timezone *)0);

		// Sensorwerte holen
		fetchValues();

		calib();

		filter();

		// Zeitdifferenz nach "Fetchen"
//		gettimeofday(&timemid, (struct timezone *)0);
//		seconds = timemid.tv_sec - timebegin.tv_sec;
//		useconds = timemid.tv_usec - timebegin.tv_usec;
//		useconds += seconds*1000^2;
//		std::cout<<"Die Zeit nach fetch: "<<useconds<<std::endl;

//		std::cout << "Phi_c: " << mPhi_c << std::endl;
//		std::cout << "Phi_d: " << mPhi_d << std::endl;
//		std::cout << "Psi: " << mPsi_d << std::endl;
		// Pipeline von Regler
		control();

		// Dummy-Werte schreiben

		//myContainer.writeADCValue(mAdcValue);
//		myContainer.writeTorqueValue(torque);			//optional... nur zum Testen
		//myContainer.writeSensor1Data (mSensorData1);
		//myContainer.writeSensor2Data(mSensorData2);
//		myContainer.writeStateData(mSensorData);

		//myContainer.signalReader();

		// Gesamtzeit erfassen
		gettimeofday(&timeend, (struct timezone *)0);
		seconds = timeend.tv_sec - timebegin.tv_sec;
		useconds = timeend.tv_usec - timebegin.tv_usec;
		useconds += seconds*1000^2;
		std::cout<<"Die Zeit nach fetch und Dummy-Schreiben: "<<useconds<<std::endl;

		// Sleep 20ms minus abgelaufene Zeit
		//usleep(24000 - useconds);
		usleep(20000);

	};
};

void CControlComp::fetchValues()
{
	mHardware.fetchValues(mAdcValue, mSensorData1, mSensorData2);

	//	UInt16 adcValue = 1623;
	//	SMPU6050Data sensorData1 = {123, 456, 789, 159};
	//	SMPU6050Data sensorData2 = {753, 951, 357, 001};
	//	SStateVectorData sensorData = {12.3, 45.6, 78.9, 15.9, 75.3};
};

void CControlComp::init()
{
	mPhi_c_old = 0;
	mHardware.enableMotor();
};


void CControlComp::calib()
{
	double alpha = 0.14 / 0.062;

	double mX1__dd = 5.980598960492827e-04 * mSensorData1.mX__dd + 0.263600503859318;
	double mX2__dd = 6.031429757892340e-04 * mSensorData2.mX__dd + 0.037980947144835;
	double mY1__dd = 5.974907801400647e-04 * mSensorData1.mY__dd + 0.058901030155490;
	double mY2__dd = 6.079657184865545e-04 * mSensorData2.mY__dd + 0.178075230701661;

	mPhi = atan2(-1*(mX1__dd - alpha*mX2__dd),-1*(mY1__dd - alpha*mY2__dd)); //[rad]

	const float LSB_Gyro=16.4;

	double mPhi1__d = -1*mSensorData1.mPhi__d / LSB_Gyro * M_PI/180.0;	//[rad/s] //17.01. 14:57 -- -1* hinzugefügt
	double mPhi2__d = -1*mSensorData2.mPhi__d / LSB_Gyro * M_PI/180.0;	//[rad/s]

	mPhi_d = -1 * (mPhi1__d + mPhi2__d)/2.0; //17.01. 15:30 -- -1* hinzugefügt


	//Motordrehzahl ermitteln

	mPsi_d = -1 * (mAdcValue - 2031) * 4.88 * M_PI/30; //[rad/s] //17.01. 15:30 -- -1* hinzugefügt

};

void CControlComp::filter()
{
	const double Alpha = 0.98;
	const double T = 0.02;

	mPhi_c = Alpha*(mPhi_c + T*mPhi_d) + (1-Alpha)*mPhi;

	//mPhi_c_old = mPhi_c;
};

void CControlComp::control()
{
	double Torque = (-1.464735886304992)*mPhi_c + (-0.108561236227978)*mPhi_d + (-4.090628420214130e-04)*mPsi_d;
//	std::cout << "gewolltes Drehmoment: " << Torque << std::endl;

	if (mPhi_c > -0.13 && mPhi_c < 0.13)
	{
		mHardware.setTorque(-Torque);
	}

	else
	{
		mHardware.setTorque(0.0);
	}

};
