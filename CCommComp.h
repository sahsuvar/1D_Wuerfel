/*
 * CCommComp.h
 *
 *  Created on: Dec 13, 2017
 *      Author: ChriPhiPa
 */

#ifndef CCOMMCOMP_H_
#define CCOMMCOMP_H_

#include <unistd.h>
#include <iostream>

#include "CContainer.h"
#include "Global.h"
#include "SContent.h"
#include "IRunnable.h"
#include "socket/CServer.h"


extern CContainer myContainer;

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
