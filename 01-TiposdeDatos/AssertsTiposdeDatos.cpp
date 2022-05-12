#include <cassert>
#include <string>
using namespace std::literals;
//luego de ejemplo error double 0.1 x10 != 1 agregamos otras librerias
//#include <iostream> comentado para pruebas string
//#include <iomanip>  comentado para pruebas string

int main()
{
	//prueba tipo de dato boole//
	assert(2 == 1 + 1);
	assert(false);
	assert(true);
	assert(false == false);
	assert(true != false);
	assert(not false);
	assert(not false == true);
	assert(false ^ true);
	assert(true and true);
	assert(false or true and false); // da error x precedencia de operadores, toma primero el AND//
	assert(false or true and false==false);
	assert((false or true) and false == false);
	assert(true or true and false); //para probar la precedencia: si toma el OR primero debe dar error, si toma el false no da error//

	// prueba tipo de dato double

	assert(2.0 == 1.0 + 1.0);
	assert(0.1 == 1.0 / 10.0);
	assert(1.0 == 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1);
	// el ejemplo de arriba da error aunque NO deberia, por que es para medicion continua
	//AVERIGUAR XQ FALLA . respuesta rapida = double no es preciso, representa bien potencias de 2 y no potencias de 10
	
	//esto de abajo es para mostrar la inexactitud de double, agregamos 2 librerias, lo comento para probar compilar
	//std::cout << std::setprecision(17) << s << '\n';
	//std::cout << std::setprecision(17) << 1.0 / 5.0 << '\n';

	//prueba tipo de dato string

	//agregar using namespace std::literals;
	assert("enrique"s == "en"s + "rique"s);
	assert("enrique"s.length() == 7); //"asd"s es la forma de poner que es una cadena, sino lo toma como algo mas viejo



}