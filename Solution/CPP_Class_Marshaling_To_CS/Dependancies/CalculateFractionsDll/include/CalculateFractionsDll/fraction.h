#ifdef CALCULATEFRACTIONSDLL_EXPORT
#  define DLL_API __declspec(dllexport)
#else
#  define DLL_API __declspec(dllimport)
#endif

#ifndef FRACTION_H
#define FRACTION_H

class DLL_API cFraction
{
	private:

static	unsigned	nFractionCount;	//Trupmenu	skaicius - globalus parametras
		unsigned	nTrupmenosNr;	//Trupmenos objekto eiles numeris	
		short		nSign;			//Trupmenos zenklas
		double		dDecimal;		//Trupmenos desimtaine interpretacija
		unsigned	nNumerator;		//Skaitiklis
		unsigned	nDenominator;	//Vardiklis

	public:

		//Konstruktoriai, destruktoriai
					cFraction ();
					cFraction (short Numerator, short Denominator);

		//-----------------------------------Viesieji metodai --------------------------------------------------------------
		
		void		m_SetFraction(short Numerator, short Denominator);			//Suteikia egzistuojanciai trupmenai naujas skaitiklio ir vardiklio reiksmes
		unsigned	m_GetNumerator() const;										//Grazina skaitiklio reiksme be zenklo
		unsigned	m_GetDenominator() const;									//Grazina vardiklio reiksme be zenklo
		short		m_GetSign() const;											//Grazina trupmenos zenkla 1 arba -1
		double		m_GetDecimal() const;										//Grazina desimtaine trupmenos interpretacija
static	void		m_ResetFractionCount();										//Skaitiklio inicializacija nuline reiksme
cFraction	operator = (const cFraction&);										//trupmenos priskyrimo operatorius. Ne kopijos konstruktorius !
cFraction	operator ++ ();														//Preinkremento perkrovimas
cFraction	operator ++(int notused);									        //Poinkremento  perkrovimas  

	

	private:
		//---------------------------------Utilites-------------------------------------------------------------------------
		void		m_SetFractionSign(short nNumber);							//Trupmenos zenklas
		void		m_SetNumerator(short nNumber);								//Skaitiklis be zenklo
		void		m_SetDenominator(short nNumber);							//Vardiklis be zenklo
		void		m_CalculateDecimal();										//Skaiciuoja desimtaine trupmena
};


#endif