/*
 * main.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: ChriPhiPa
 */
// allgemeine Includes
#include <sys/types.h>
#include <pthread.h>

// locale Includes
#include "CContainer.h"
#include "CThread.h"

// eigene Header-Includes
#include "CCommComp.h"
#include "CControlComp.h"

// globale Objekte
CContainer myContainer;
//pthread_t CommComp_TID, ControlComp_TID;

int main()
{

	CCommComp commcomp;
	CControlComp controlcomp;

	CThread commThread(&commcomp,CThread::PRIORITY_ABOVE_NORM);
	CThread controlThread(&controlcomp,CThread::PRIORITY_ABOVE_NORM);

	commThread.start();
	controlThread.start();

	commThread.join();
	controlThread.join();




	return 0;
}
