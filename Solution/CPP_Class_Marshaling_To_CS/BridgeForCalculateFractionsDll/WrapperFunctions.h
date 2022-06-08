#ifndef WRAPPERFUNCTIONS_H
#define WRAPPERFUNCTIONS_H

#ifndef WRAPPER_DLL_API
#define WRAPPER_DLL_API __declspec(dllexport)
#endif

#include <CalculateFractionsDll/fraction.h>
#include <CalculateFractionsDll/fractioncalculator.h>

/*** fraction.h ***/
//cFraction();
//cFraction(short Numerator, short Denominator);
//~cFraction();
//void		m_SetFraction(short Numerator, short Denominator);			//Suteikia egzistuojanciai trupmenai naujas skaitiklio ir vardiklio reiksmes
//unsigned	m_GetNumerator() const;										//Grazina skaitiklio reiksme be zenklo
//unsigned	m_GetDenominator() const;									//Grazina vardiklio reiksme be zenklo
//short		m_GetSign() const;											//Grazina trupmenos zenkla 1 arba -1
//double	m_GetDecimal() const;										//Grazina desimtaine trupmenos interpretacija
//static	void m_ResetFractionCount();								//Skaitiklio inicializacija nuline reiksme
//cFraction	operator = (const cFraction&);								//trupmenos priskyrimo operatorius. Ne kopijos konstruktorius !
//cFraction	operator ++ ();												//Preinkremento perkrovimas
//cFraction	operator ++(int notused);									//Poinkremento  perkrovimas 

/*** fractioncalculator.h ***/
//cFractionCalculator();
//~cFractionCalculator();
//void		m_PushFraction(const cFraction&);							//ideda i steka antra trupmena
//cFraction	m_GetSum();													//Skaiciuoja trupmenu suma/skirtuma ir prastina rezultata
//unsigned	m_GetGCD()const;											//Skaiciuoja didziausia bendra dalikli
//unsigned	m_GetLCM()const;											//Skaiciuoja maziausia bendra daugikli 
//cFraction operator + (const cFraction, const cFraction)

extern "C" WRAPPER_DLL_API void PrintText();
extern "C" WRAPPER_DLL_API void PrintText2();

extern "C" {
	WRAPPER_DLL_API cFraction*	cFraction_Create();
	WRAPPER_DLL_API cFraction*	cFraction_CreateWithND(short Numerator, short Denominator);
	WRAPPER_DLL_API void		cFraction_Dispose(cFraction* pFractionObj);
	WRAPPER_DLL_API void		cFraction_SetFraction(cFraction* pFractionObj, short Numerator, short Denominator);
	WRAPPER_DLL_API unsigned	cFraction_GetNumerator(cFraction* pFractionObj);
	WRAPPER_DLL_API unsigned	cFraction_GetDenominator(cFraction* pFractionObj);
	WRAPPER_DLL_API short		cFraction_GetSign(cFraction* pFractionObj);
	WRAPPER_DLL_API double		cFraction_GetDecimal(cFraction* pFractionObj);
	WRAPPER_DLL_API void		cFraction_ResetFractionCount(cFraction* pFractionObj);
	WRAPPER_DLL_API void		cFraction_Assign(cFraction* pFractionObj_FROM, cFraction* pFractionObj_TO);
	WRAPPER_DLL_API void		cFraction_PreInc(cFraction* pFractionObj);
	WRAPPER_DLL_API void		cFraction_Inc(cFraction* pFractionObj);

	WRAPPER_DLL_API cFractionCalculator*	cFractionCalculator_Create();
	WRAPPER_DLL_API void					cFractionCalculator_Dispose(cFractionCalculator* pFCalculatorObj);
	WRAPPER_DLL_API void					cFractionCalculator_PushFraction(cFractionCalculator* pFCalculatorObj, cFraction* pFractionObj);
	WRAPPER_DLL_API cFraction*				cFractionCalculator_GetSum(cFractionCalculator* pFCalculatorObj);
	WRAPPER_DLL_API unsigned				cFractionCalculator_GetGCD(cFractionCalculator* pFCalculatorObj);
	WRAPPER_DLL_API unsigned				cFractionCalculator_GetLCM(cFractionCalculator* pFCalculatorObj);
	WRAPPER_DLL_API cFraction*				cFraction_AddFractions(cFraction* pFractionObj1, cFraction* pFractionObj2);
}
#endif