/*
 * CControlComp.h
 *
 *  Created on: Dec 13, 2017
 *      Author: ChriPhiPa
 */

#ifndef CCONTROLCOMP_H_
#define CCONTROLCOMP_H_

// allgemeine Includes
#include <unistd.h>
#include <sys/time.h>
#include <iostream>
#include <cmath>

// Lokale Includes
#include "CContainer.h"
#include "Global.h"
#include "IRunnable.h"
#include "CBBBHardware.h"

// Deklaration eines globalen Objektes
extern CContainer myContainer;

// Erstellung der Klasse "CControlComp" inklusive erben der public Parameter von der Klasse "IRunnable"
class CControlComp:public IRunnable
{

	public:
		void run();
		void init();
		void fetchValues();					// Auslesen aller Sensorwerte des Systems
		void calib();						// Anpassen und korrigieren der Sensorwerte
		void filter();						// Filterung der angepassten Sensorwerte
		void control();						// Regeln der Ausgangsgröße
		void motor();						// Ansteuern des Motors


	private:
		CBBBHardware mHardware;				// Attribut um auf das System zuzugreifen
		UInt16 mAdcValue;					// Aktuelle Drehzahl des Motors
		SMPU6050Data mSensorData1;			// Sensordaten des oberen Beschleunigungssensor
		SMPU6050Data mSensorData2;			// Sensordaten des unteren Beschleunigungssensor
		SStateVectorData mSensorData;		// Attribut um aktuelle Sensordaten zu speichern

		double mTorque;						// Variable um Drehmoment zu übertragen
};

#endif /* CCONTROLCOMP_H_ */
