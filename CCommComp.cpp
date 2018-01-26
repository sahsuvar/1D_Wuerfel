/*
 * CCommComp.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: ChriPhiPa
 */

// include der zur Klasse gehörigen Headerdatei
#include "CCommComp.h"

// Deklaration der Laufzeitfunktion
void CCommComp::run()
{
		while (1)
		{
			myContainer.getContent(true ,mContent);		// Abrufen aktueller in myContainer gespeicherter Werte
			mServer.transmitMessage(mContent);			// übertragen der abgerufenen Werte über die Socketschnittstelle an den Client
		};
};


// Deklaration der Initialisierungsfunktion
void CCommComp::init()
{
	mServer.init();										// Aufrauf der Funktion init() der Klasse CServer
	mServer.waitForClient();							// Aufruf der Funktion waitForClient(), um den Thread bis zu einer erfolgreichen
														// Verbindung mit einem Client zu pausieren
};
