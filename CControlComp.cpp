/*
 * CControlComp.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: ChriPhiPa
 */

// Include der zur Klasse gehörigen Headerdatei
#include "CControlComp.h"

// Deklaration der Laufzeitfunktion
void CControlComp::run()
{

	struct timeval timebegin, timeend; 						// Zur Zeitdifferenzberechnung
	time_t seconds, useconds; 								// Um Stückchen der Zeit zu bekommen
	int t_diff = 0;											// Um Zeitdifferenz zwischenzuspeichern

	while (1) {

		// Aktuelle Zeit bei Beginn des Durchlaufs erfassen
		gettimeofday(&timebegin, (struct timezone *)0);

		// Sensorwerte auslesen
		fetchValues();

		// Anpassen und korrigieren der Sensorwerte
		calib();

		// Filterung der angepassten Sensorwerte
		filter();

	//	std::cout << "Letzte Zeitdifferenz:\t" << t_diff << std::endl;
	//	std::cout << "Phi_c Winkel des Würfels:\t" << mSensorData.mPhi_C << std::endl;		// Ausgabe des gefilterten Sensorwerte
	//	std::cout << "Phi_d Geschwindigkeit des Würfels:\t" << mSensorData.mPhi__d << std::endl;
	//	std::cout << "Psi_d Geschwindigkeit des Motors:\t" << mSensorData.mPsi__d << std::endl;
	//	std::cout << "Motordrehtmoment: \t" << mTorque << std::endl << std::endl;

		// Regeln der Ausgangsgröße
		control();

		// Ansteuern des Motors
		motor();

		// Gesamtzeit erfassen
		gettimeofday(&timeend, (struct timezone *)0);
		seconds = timeend.tv_sec - timebegin.tv_sec;
		useconds = timeend.tv_usec - timebegin.tv_usec;
		useconds += seconds*1000^2;
		std::cout<<"Die Zeit nach fetch und Dummy-Schreiben: "<<useconds<<std::endl;		//Gesamtzeit eines Durchlaufs
//		t_diff = 20000 - (int)useconds;										// Berechnung der Zeitdifferenz um das Abstastintervall einzuhalten
		//usleep(t_diff);
		usleep(20000);														// 20ms Pause bis zum nächsten Durchlauf zur Einhaltung der Abtastzeit
	};
};

void CControlComp::fetchValues()
{
	mHardware.fetchValues(mAdcValue, mSensorData1, mSensorData2);					// Sensorwerte auslesen und in den Attributen der Control Klasse speichern
};

// Deklaration der Initialisierungsfunktion
void CControlComp::init()
{
	mSensorData.mPhi_C = 0;															// Winkel des Würfels mit Null initialisieren
	mHardware.enableMotor();														// Motorfreigabe aktivieren
};

// Anpassen und korrigieren der Sensorwerte
void CControlComp::calib()
{
	// Aktuellen Winkel des Würfels aus den Beschleunigungswerten ermitteln
	const double  rs1 = 0.14;						// Abstand des oberen Sensors zum Würfeldrehpunkt A in Meter
	const double  rs2 = 0.062;						// Abstand des unteren Sensors zum Würfeldrehpunkt A in Meter
	double alpha = rs1 / rs2;						// Quotient der beiden Sensorabstände

	double mX1__dd = 5.980598960492827e-04 * mSensorData1.mX__dd + 0.263600503859318; // Anpassung des X-Wertes des ersten Sensors mit einer Ausgeleichsgeraden
	double mX2__dd = 6.031429757892340e-04 * mSensorData2.mX__dd + 0.037980947144835; // Anpassung des X-Wertes des zweiten Sensors mit einer Ausgeleichsgeraden
	double mY1__dd = 5.974907801400647e-04 * mSensorData1.mY__dd + 0.058901030155490; // Anpassung des Y-Wertes des ersten Sensors mit einer Ausgeleichsgeraden
	double mY2__dd = 6.079657184865545e-04 * mSensorData2.mY__dd + 0.178075230701661; // Anpassung des Y-Wertes des zweiten Sensors mit einer Ausgeleichsgeraden

	mSensorData.mPhi_A = (float)(atan2(-1*(mX1__dd - alpha*mX2__dd),-1*(mY1__dd - alpha*mY2__dd))); //[rad] Zusammenführen der Sensorwerte

	// Ermitteln des Geschwindigkeitswertes des Würfels aus den Gyro-Sensoren
	const float LSB_Gyro=16.4;											// Least significant Bit der Beschleunigungssensoren

	float mPhi1__d = -1*mSensorData1.mPhi__d / LSB_Gyro * M_PI/180.0;	//[rad/s] //Umrechnung des Digitalwertes in rad/s
	float mPhi2__d = -1*mSensorData2.mPhi__d / LSB_Gyro * M_PI/180.0;	//[rad/s]

	mSensorData.mPhi__d = -1 * (mPhi1__d + mPhi2__d)/2.0; 							// Berechnung des Mittelwertes der Geschwindigkeitswerte


	// Aktuelle Motordrehzahl ermitteln
	mSensorData.mPsi__d = -1 * (mAdcValue - 2031) * 4.88 * M_PI/30.0; //[rad/s] // Digitalwert der aktuellen Drehzahl in rad/s umrechnen
};

// Filterung der angepassten Sensorwerte
void CControlComp::filter()
{
	const double Alpha = 0.98;									// Koeffizient des Filters
	const double T = 0.02;										// Abtastperiodendauer

	mSensorData.mPhi_C = Alpha*(mSensorData.mPhi_C + T*mSensorData.mPhi__d) + (1-Alpha)*mSensorData.mPhi_A;	//Ermitteln des gefilterten Winkels aus den
																											//Sensordaten mit Hilfe eines Komplementärfilters

};
// Regeln der Ausgangsgröße
void CControlComp::control()
{
	//Ermitteln des notwendigen Drehmoments zur Positionsregelung durch die Reglerparameter, welche mit Matlab ermittelt wurden
	mTorque = (-1.464735886304992)*mSensorData.mPhi_C + (-0.108561236227978)*mSensorData.mPhi__d + (-4.090628420214130e-04)*mSensorData.mPsi__d;

};

// Ansteuern des Motors
void CControlComp::motor()
{
	if (mSensorData.mPhi_C > -0.13 && mSensorData.mPhi_C < 0.13)	//Wenn der Würfel im kontrolliebaren Bereich,
	{																//das im Regler ermittelte Drehmoment auf den Motor gegeben
		mHardware.setTorque(-mTorque);
	}

	else															//Wenn der Würfel im nicht kontrolliebaren Bereich,
	{																//kein Drehmoment auf den Motor gegeben
		mHardware.setTorque(0.0);
	}
};
