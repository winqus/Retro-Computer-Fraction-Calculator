For Windows. Python and .NET have to be installed. 
To run the applications use "runall.bat" and in your browser go to http://localhost:8000/falculator/

<runall.bat> - to start both calculator services (ASP.NET and Django);

<.venv> - Python virtual environment with necessary modules;

<falculator/> - django application
  <falculator/app/fractionsum/> :
   <static/>	 - JS, CSS files
   <templates/>  - HTML file
   <urls.py> ir <views.py> - calculator service code

<FCalculatorAPI/> - ASP.NET application that calls CalculateFractionsDll;




