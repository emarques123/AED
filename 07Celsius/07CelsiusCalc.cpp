#include<cassert>
#include<iostream>

double Celsius(double);
bool AreNear(double, double, double = 0.001);
int main()
{

    assert(Celsius(32) == 0);  
    assert(AreNear(1,1));
    assert(AreNear(1,0.99999999));
    assert(AreNear(1,11,10));
    assert(Celsius(41) == 5); //32+multiplo de 9 da un resultado exacto, o bien 32+k9 con k perteneciente a Z
    assert(Celsius(42) >= 5);
    assert(AreNear(Celsius(42),5.555));
    assert(AreNear(25.0001,Celsius(77)));
    assert(AreNear(30,Celsius(86)));
    assert(AreNear(31,Celsius(86),-1)); //tolerancia negativa ok, funcion arenear con modulo
    assert(not AreNear(31,Celsius(86),-0.000001));
    assert(not AreNear(15,Celsius(59.5 )));

    //Extra, quise probar el flujo de entrada/salida solicitando la temp en farenheit a convertir en celsius
    //double TempF;
    //std::cout << "Ingrese temperatura en grados Farenheit\n";
    //std::cin >> TempF;
    //std::cout << "Equivale a:" << Celsius(TempF) << " grados Celsius";

}
//f:R-->R/f(x)=5/9(x-32)
double Celsius(double TempF)
{
    //return 5/9*(TempF - 32);//de esta forma me da resultado 0 siempre... ¿?
    return (TempF - 32)*5/9;//asi arroja resultado correcto
}
//f:RxRxR-->B/f(x)=V si |x-y| <= |t|
//                 F si |x-y| > |t|
bool AreNear(double x, double y, double t)
{
    return abs(x-y) <= abs(t);
}

