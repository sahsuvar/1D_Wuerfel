/*
 * CCommComp.h
 *
 *  Created on: Dec 13, 2017
 *      Author: ChriPhiPa
 */

#ifndef CCOMMCOMP_H_
#define CCOMMCOMP_H_

// allgemeine Includes
#include <unistd.h>
#include <iostream>

// lokale Includes
#include "CContainer.h"
#include "Global.h"
#include "SContent.h"
#include "IRunnable.h"
#include "socket/CServer.h"

// deklaration eines globalen Objektes
extern CContainer myContainer;

// Erstellung der Klasse "CCommComp" inklusive erben der public Parameter von der Klasse "IRunnable"
class CCommComp:public IRunnable
{
	public:
		void run();
		void init();

	private:
		CServer mServer;
		SContent mContent;
};

#endif /* CCOMMCOMP_H_ */
