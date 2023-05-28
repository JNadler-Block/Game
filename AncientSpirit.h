#pragma once
#include <iostream>

#include "Character.h"

#ifndef _ANCIENTSPIRIT_H_
#define _ANCIENTSPIRIT_H_

class AncientSpirit
{
	private:
		int Cost = 100;
		double DropRate = 0.05;
		double EternalRate = 0.20;
	public:
		AncientSpirit() { }
		
		// Accessor Functions
		int SeeCost() { return Cost; }
		double SeeDropRate() { return DropRate; }
		double SeeEternalRate() { return EternalRate; }

		// Other
		void AncientUsed(Character &c, int x);
		void EternalUsed(Character& c, int x);

};

#endif

