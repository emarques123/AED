#include <cassert>
#include <string>


int main()
{
	using namespace std::literals;//para pruebas con strings

	assert(2 == 1 + 1); //por algo hay que empezar ^^

	//prueba tipo de dato boole
	assert(false == false);
	assert(true != false);
	assert(not false);
	assert(not false == true);
	assert((false or true) and false == false);
	assert(false or true and false == false); //orden de precedencia de los operadores or and e igual
	assert(false == 0);
	assert(true == 1);
	assert(true != (1 / 0));

	
	// prueba tipo de dato char
	assert('E' == 69);
	assert('E' != 'e');
	assert('E' <= 'e');
	assert('E' == 'e' - 32);
	assert('E' * 'e' == 6969);
	assert('E' + 'n' + 'r' + 'i' + 'q' + 'u' + 'e' == 729);

	
	//prueba tipo de dato string
	assert("enrique"s != "marques"s);
	assert("enrique"s == "en"s + "rique"s);
	assert("enrique"s.length() == 7);
	assert("E"s <= "M"s);


	// prueba tipo de dato int
	assert(1 * 1 + 2 / 2 == 2);
	assert(100 % 3 == 1);
	assert(-9223372036854775807 * -2 + 1 == 18446744073709551615);
	//assert(0 == 18446744073709551616u); //intenté probar si pasandome del valor maximo "18446744073709551615" volvía al cero pero tiró error el compilador "C2177 constante demasiado grande"
	//en valores altos visual studio me muestra tipo de dato "int/unsinged long long". Encontré que ocupan 64bits
	


	// prueba tipo de dato double
	assert(2.0 == 1.0 + 1.0);
	assert(0.1 == 1.0 / 10.0);
	assert(16 == 1.6 * 10); // promocion tipo de dato
	assert(2.56 == 0.16 * 16); //promocion tipo de dato
	assert(2.0 == 1 + 1.0); //promocion tipo de dato
	assert(2.0 != 0.2 + 0.2 + 0.2 + 0.2 + 0.2 + 0.2 + 0.2 + 0.2 + 0.2 + 0.2); // si igualamos da error de redondeo
	assert(10000000000000001 == 0.1 * 100000000000000000); // no da error xq 0.1 se guarda como 0,10000000000000001



	assert(1 == 1); //voy cambiando esta igualdad entre prueba y prueba para verificar si estoy corriendo ejecutable correcto

}