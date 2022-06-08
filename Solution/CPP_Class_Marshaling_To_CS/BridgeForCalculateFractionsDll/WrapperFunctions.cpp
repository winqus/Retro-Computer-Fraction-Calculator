#include <iostream>
#include "WrapperFunctions.h"

void PrintText() {
		std::cout << "Test text 1!\n";
}
void PrintText2() {
		std::cout << "Test text 2!\n";
}

cFraction* cFraction_Create() { return new cFraction(); }
cFraction* cFraction_CreateWithND(short Numerator, short Denominator) { return new cFraction(Numerator, Denominator); }
void cFraction_Dispose(cFraction* pFractionObj) {
	if (pFractionObj != NULL)
	{
		delete pFractionObj;
		pFractionObj = NULL;
	}
}
void		cFraction_SetFraction (cFraction* pFractionObj, short Numerator, short Denominator) { pFractionObj->m_SetFraction(Numerator, Denominator); }
unsigned	cFraction_GetNumerator (cFraction* pFractionObj) { return pFractionObj->m_GetNumerator(); }
unsigned	cFraction_GetDenominator (cFraction* pFractionObj) { return pFractionObj->m_GetDenominator(); }
short		cFraction_GetSign (cFraction* pFractionObj) { return pFractionObj->m_GetSign(); }
double		cFraction_GetDecimal (cFraction* pFractionObj) { return pFractionObj->m_GetDecimal(); }
void		cFraction_ResetFractionCount (cFraction* pFractionObj) { return pFractionObj->m_ResetFractionCount(); }
void		cFraction_Assign (cFraction* pFractionObj_FROM, cFraction* pFractionObj_TO) { *pFractionObj_TO = *pFractionObj_FROM; }
void		cFraction_PreInc (cFraction* pFractionObj) { ++(*pFractionObj); }
void		cFraction_Inc (cFraction* pFractionObj) { (*pFractionObj)++; }


cFractionCalculator* cFractionCalculator_Create() { return new cFractionCalculator; }
void cFractionCalculator_Dispose(cFractionCalculator* pFCalculatorObj) {
	if (pFCalculatorObj != NULL)
	{
		delete pFCalculatorObj;
		pFCalculatorObj = NULL;
	}
}
void cFractionCalculator_PushFraction(cFractionCalculator* pFCalculatorObj, cFraction* pFractionObj) { pFCalculatorObj->m_PushFraction(*pFractionObj); }
cFraction* cFractionCalculator_GetSum(cFractionCalculator* pFCalculatorObj) { 
	cFraction* tmpFrac = new cFraction();
	*tmpFrac = (pFCalculatorObj->m_GetSum());
	return tmpFrac;
}
unsigned cFractionCalculator_GetGCD(cFractionCalculator* pFCalculatorObj) { return pFCalculatorObj->m_GetGCD(); }
unsigned cFractionCalculator_GetLCM(cFractionCalculator* pFCalculatorObj) { return pFCalculatorObj->m_GetLCM(); }
cFraction* cFraction_AddFractions(cFraction* pFractionObj1, cFraction* pFractionObj2) {
	cFraction* tmpFrac = new cFraction();
	cFractionCalculator* tmpCalc = new cFractionCalculator;
	tmpCalc->m_PushFraction(*pFractionObj1);
	tmpCalc->m_PushFraction(*pFractionObj2);
	*tmpFrac = tmpCalc->m_GetSum();
	delete tmpCalc; tmpCalc = NULL;
	return tmpFrac;
}