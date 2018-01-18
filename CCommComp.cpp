/*
 * CCommComp.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: ChriPhiPa
 */


#include "CCommComp.h"

void CCommComp::run()
{
		while (1)
		{
			myContainer.getContent(true ,mContent);
			mServer.transmitMessage(mContent);
		};
};


void CCommComp::init()
{
	mServer.init();
	mServer.waitForClient();
};
