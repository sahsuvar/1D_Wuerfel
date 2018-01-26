/*
 * main.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: ChriPhiPa
 */
// Allgemeine Includes
#include <sys/types.h>
#include <pthread.h>

//Lokale Includes
#include "CContainer.h"
#include "CThread.h"

// Eigene Header-Includes
#include "CCommComp.h"
#include "CControlComp.h"

// Globale Objekte
CContainer myContainer;

int main()
{
	// Erzeugen der Zugriffsobjekte
	CCommComp commcomp;
	CControlComp controlcomp;

	// Erzeugen der Threadobjekte
	CThread commThread(&commcomp,CThread::PRIORITY_ABOVE_NORM);
	CThread controlThread(&controlcomp,CThread::PRIORITY_ABOVE_NORM);

	// Starten der Threads
	commThread.start();
	controlThread.start();

	// Warten auf Beendigung der Threads
	commThread.join();
	controlThread.join();


	return 0;
}
