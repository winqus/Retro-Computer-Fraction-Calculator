#ifndef FRACTIONCALCULATOR_H
#define FRACTIONCALCULATOR_H

#include "fraction.h"

 class DLL_API cFractionCalculator
{
	private:
		static	unsigned	nFractionCalculatorCount;								//Trupmenu kalkuliatoriu skaicius - globalus parametras
		cFraction	*p_obj_FirstFraction;
		cFraction	*p_obj_SecondFraction;


	public:
		//Konstruktoriai, destruktoriai
		cFractionCalculator();
		~cFractionCalculator();
	
		//-----------------------------------Viesieji metodai --------------------------------------------------------------
		void		m_PushFraction(const cFraction&);								//ideda i steka antra trupmena
		cFraction	m_GetSum();														//Skaiciuoja trupmenu suma/skirtuma ir prastina rezultata
		unsigned	m_GetGCD()const;												//Skaiciuoja didziausia bendra dalikli
		unsigned	m_GetLCM()const;												//Skaiciuoja maziausia bendra daugikli 

	private:
		//-----------------------------------Utilites --------------------------------------------------------------
		void		m_ReduceFraction(cFraction*);									//Trupmenos prastinimas
};
		//-----------------------------------Global functions belongs to calculator---------------------------------

 extern DLL_API cFraction operator + (const cFraction, const cFraction);						//Dvieju trupmenu sudetis				
#endif
