#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <string>
#include <cassert>
#include "Blockstream.h"

#define CantidadRegiones 4      //
#define CantidadVendedores 3    //para definir tamaño del "CUBO"
#define CantidadMeses 12        //si se pone mas de 12 modificar "ListaMesesAbrev", si se pone menos de 12, definir cuales en "ListaMesesAbrev"    
#define CantidadCapos 1         //para definir tamaño array vendedores en "ventas del capo"
#define RegionesCapos 1         //para definir tamaño array regiones en "ventas del capo"
#define ElCapo 0                //para definir que vendedor es el capo
#define RegionDelCapo 0         //para definir cual es la region del capo
#define InicioVector 16         //para setear un tamaño inicial a cada mes-vector del capo           *revisar
#define ArchivoDeTexto "data.txt"   //para definir nombre de archivo
#define DataFileBIN "data.bin"  //aca deberia haber otro para la cantidad de ventas             *revisar
#define CapoBIN "capo.bin"      //para definir el nombre de archivo

using std::array;
using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::ifstream;
using std::ofstream;

using CUBO = array<array<array<int,CantidadMeses>,CantidadVendedores>,CantidadRegiones>;
using CUVO = array<array<array<vector<int>,CantidadMeses>,CantidadCapos>,RegionesCapos>;
using V3 = array<vector<int>,3>;    //para mostrar stats. Dimensiones x Vector{ValorDeReferencia, coincidencia, ..., coincidencia}

struct TotalesCubo{                 //para uso estadisticas CUBO
array<int,CantidadMeses> Meses;
array<int,CantidadVendedores> Vendedores;
array<int,CantidadRegiones> Regiones;
};

enum Regiones{Norte, Sur, Este, Oeste, NoDefinida};
enum MayorMenorIgual{Menor = -1, Igual = 0, Mayor = 1};

//Listado de Vendedores, revisar si la utiliza mas de una funcion? sino pasar a static dentro de funcion, aunque quizas pierde visibilidad
array<string,CantidadVendedores> ListaVendedores{
    "Capo",         //0
    "Juan",         //1
    "Juana",        //2
};


//:::::::::::::::::::::::::::Prototipos::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

//::Flujo de Datos:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
/* Credito Extra: Implementar las funciones LeerDatos y MostrarTotales */

// LeerDatosCIN: ε --> ε/ EDL cin->array
void LeerDatosCIN();
//hacer opcion con lectura desde test.txt y dejarla comentada "void LeerDatos(std::ifstream&)" LeerDatos:Test.txt --> ε/

// LeerDatosTxt: ε --> ε/ EDL data.txt->array
void LeerDatosTxt();

// GuardarVentaDelCapo: Z^12^1^4 --> ε/ EDL cin->Cuvo de Vectores
void GuardarVentaDelCapo(const int, int, int, int);

// GuardarCuboBin: Z^12^3^4 --> ε/ EDL CUBO->file.bin
void GuardarCuboBin(const CUBO &);

// LeerCuboBin: Z^12^3^4 --> ε/ EDL data.bin->CUBO
void LeerCuboBin(CUBO &);

// GuardarVectorBin: Z^N^12^1^4-->ε/ EDL cuvo de vectores->file.bin
void GuardarCuvoBin(const CUVO &);

// LeerVectorBIN: Z^N^12^1^4-->ε/ EDL file.bin->cuvo de vectores
void LeerCuvoBIN(CUVO &);

// MostrarTotales: Z^12^3^4-->ε/ EDL cout<-array
void MostrarTotales(const CUBO &);

// MostrarVentasCapo: Z^N^12^1^4-->ε/ EDL cout<-vector
void MostrarVentasCapo(const CUVO &);





//::Cálculo de Estadísticas::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
/*Credito Extra: Agregar estadísticas, por lo menos una que aplique máximo, otra mínimo, y otra promedio.*/

//CompararValores: Z^Z --> {1,0,-1}
MayorMenorIgual CompararValores(const int &, const int &);

//CalcularTotales: Z^12^3^4 --> (Z^12,Z^3,Z^4) *completar
TotalesCubo CalcularTotales(const CUBO &);

// ObtenerMejores:(Z^12,Z^3,Z^4)-->Z^3
array<int,3> ObtenerMejores(const TotalesCubo &);

// ObtenerPeores:(Z^12,Z^3,Z^4)-->Z^3
array<int,3> ObtenerPeores(const TotalesCubo &);

// BuscarCoincidencia: Z^3,(Z^12,Z^3,Z^4)-->Z^N^3
V3 BuscarCoincidencia(const array<int,3> &, const TotalesCubo &);



// MostrarV3: Z^N^3 -->ε/ EDL cout<<V3
void MostrarV3(const V3 &);

// MostrarTotalesCubo: (Z^12,Z^3,Z^4)-->ε/ EDL cout<<Totales Cubo
void MostrarTotalesCubo(const TotalesCubo &);



// para agrupar funciones modulares y no tener que anidar llamados en main
void MostrarMejores(const CUBO &);











/*
Deprecado?
*/
//GetVendedorConMasVentas:(MESxRegion)--->Σ*/ 
string GetVendedorConMasVentas(int, Regiones);

//GetVendedorConMenosVentas(mes, región)--->Σ*/
string GetVendedorConMenosVentas(int, Regiones);

//FALTA:
//GetPromedioVentas(desde mes, hasta mes) #1
//GetPromedioVentas(desde mes, hasta mes, Vendedor) #2
//GetPromedioVentas(desde mes, hasta mes, Vendedor, Región) #3 

double GetPromedioVentas(int, int);




















//::Presentación de Datos::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


/* NombreRegion:Z-->Σ* /{Norte  si 0
                        {Sur    si 1
                        {Este   si 2
                        {Oeste  si 3
                        {No Def e.o.c  */
string NombreRegion(const int);

/* NombreVendedor:Z-->Σ* /{"ElCapo"  si 0
                          {"Juan"    si 1
                          {... 
                          {"No Definido"  e.o.c */
string NombreVendedor(const int);


string NombreMes(const int);


string NombreMesAbrev(const int);


/*Credito Extra:Presentar las tablas lo más claro posible con formato, alineación numérica y con títulos.*/
// MostrarTotalesConFormato:Z^12^3^4-->ε/ EDL cout<<CUBO
void MostrarTotalesConFormato(const CUBO &);


void MostrarVentasCapoFormato(const CUVO &);














//se alimentan desde CIN o archivo txt
CUBO ImporteMesVendedorRegion{};
CUBO TrxMesVendedorRegion{};
CUVO VentasDelCapo{};

//se alimentan desde archivos binarios, los diferencio para verificar facilmente si recuperan info ok dsd bin
CUBO IMVRbin{};
CUBO TMVRbin{};
CUVO VCbin{};

//::::::::MAIN:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
int main(){

assert(1 == Regiones::Sur);
//VentasDelCapo reservar vector***** hacer funcion?

LeerDatosTxt();
GuardarCuboBin(ImporteMesVendedorRegion);
LeerCuboBin(IMVRbin);
MostrarTotalesConFormato(IMVRbin);
GuardarCuvoBin(VentasDelCapo);
LeerCuvoBIN(VCbin);

MostrarVentasCapo(VentasDelCapo);
MostrarVentasCapo(VCbin);

assert(sizeof ImporteMesVendedorRegion == sizeof TrxMesVendedorRegion);

cout << "Totales:\n";
MostrarTotalesCubo(CalcularTotales(ImporteMesVendedorRegion));
cout << "Mejores:\n";
MostrarV3(BuscarCoincidencia(ObtenerMejores(CalcularTotales(IMVRbin)),(CalcularTotales(IMVRbin))));
cout << "Peores:\n";
MostrarV3(BuscarCoincidencia(ObtenerPeores(CalcularTotales(IMVRbin)),(CalcularTotales(IMVRbin))));


//cout << GetPromedioVentas(0,1);
//MostrarTotalesConFormato(TrxMesVendedorRegion);

}















//:::::::::::::::::::::::Implementaciones::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

//::Flujo de Datos:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

void LeerDatosCIN(){
    
    for (int Importe{}, Mes{}, Vendedor{}, Region{};cin >> Importe >> Mes >> Vendedor >> Region;){

    ImporteMesVendedorRegion.at(Region).at(Vendedor).at(Mes) += Importe;
    ++TrxMesVendedorRegion.at(Region).at(Vendedor).at(Mes);

    if (Vendedor == ElCapo && Region == RegionDelCapo) // si hubiera mas de un capo >> llamar funcion "SosUnCapo?"
    {
        GuardarVentaDelCapo(Region, Vendedor, Mes, Importe);
    }
    
}
}

void LeerDatosTxt(){

static ifstream ifdatatxt;

ifdatatxt.open(ArchivoDeTexto);

    for (int Importe{}, Mes{}, Vendedor{}, Region{};ifdatatxt >> Importe >> Mes >> Vendedor >> Region;){

    ImporteMesVendedorRegion.at(Region).at(Vendedor).at(Mes) += Importe;
    ++TrxMesVendedorRegion.at(Region).at(Vendedor).at(Mes);

    if (Vendedor == ElCapo && Region == RegionDelCapo) // si hubiera mas de un capo >> llamar funcion "SosUnCapo?"
    {
        GuardarVentaDelCapo(Region, Vendedor, Mes, Importe);
    }
    }
    
ifdatatxt.close();
}

void GuardarVentaDelCapo(const int r,const int c,const int m,const int v){

    VentasDelCapo.at(r).at(c).at(m).push_back(v);
}


void GuardarCuboBin(const CUBO &array){

    //constexpr auto filename{DataFileBIN}; << investigar
    static ofstream ofcubobin{DataFileBIN, std::ios::binary};
	WriteBlock(ofcubobin, array);
	ofcubobin.close();    

}

void LeerCuboBin(CUBO &array){   
    static ifstream ifcubobin{DataFileBIN, std::ios::binary};
    ReadBlock(ifcubobin, array);
    ifcubobin.close();
}

void GuardarCuvoBin(const CUVO &cuvo){
    static ofstream ofcuvobin{CapoBIN, std::ios::binary};

    int ir{};
    for(auto r : cuvo){  //itero x regiones capos, ya predefinido en #define
        WriteBlock (ofcuvobin, ir);
        int ic{};
        for(auto c : r){  //itero x cada capo, ya predefinido en #define
            WriteBlock(ofcuvobin, ic);
            int im{};
            for(auto m : c){ //itero x cada mes, ya predefinido en #define, pero necesito marcar cuantas ventas tiene cada vector
                WriteBlock(ofcuvobin, im);
                int cantidad{};
                cantidad = m.size();
                WriteBlock(ofcuvobin, cantidad);
                for (auto v : m){
                    WriteBlock(ofcuvobin, v);
                }            
                ++im;
            }
            ++ic;
        }
        ++ir;
    }
    ofcuvobin.close();
}
/*
void GuardarCuvoBin(const CUVO &cuvo){
    static ofstream ofcuvobin{CapoBIN, std::ios::binary};

    for(auto r : cuvo){  //itero x regiones capos, ya predefinido en #define
        int ir{};
        for(auto c : r){  //itero x cada capo, ya predefinido en #define
            int ic{};
            for(auto m : c){ //itero x cada mes, ya predefinido en #define, pero necesito marcar cuantas ventas tiene cada vector
                int im{},
                    venta{},
                    cantidad{};
                cantidad = m.size();
                WriteBlock(ofcuvobin, cantidad);
                
                //for(int i{}; i < cantidad; ++i){ //itero x cada venta del mes
                //    venta = cuvo.at(ir).at(ic).at(im).at(i);
                //    WriteBlock(ofcuvobin, venta);
                
                for (auto v : m){
                    WriteBlock(ofcuvobin, v);
                }            
                ++im;
            }
            ++ic;
        }
        ++ir;
    }
    ofcuvobin.close();
}
*/

void LeerCuvoBIN(CUVO &cuvo){
    static ifstream ifcuvobin{CapoBIN, std::ios::binary};
    int ir{};
    for(auto r : cuvo){ //itero x regiones capos, ya predefinido en #define
        ReadBlock(ifcuvobin, ir);
        int ic{};
        for(auto c : r){    //itero x cada capo, ya predefinido en #define
            ReadBlock(ifcuvobin, ic);
            int im{};
            for(auto m : c){    //itero x cada mes, ya predefinido en #define, pero necesito marcar cuantas ventas tiene cada vector
                ReadBlock(ifcuvobin,im);
                int cantidad{};
                ReadBlock(ifcuvobin, cantidad);  //leo primer int indicando cantidad ventas del mes
                cuvo.at(ir).at(ic).at(im).resize(cantidad); //acomodo capacidad del vector mes a esa cantidad
                cuvo.at(ir).at(ic).at(im).clear();  //limpio vector destino en caso que hubiese sido utilizado previamente
                int venta{};
                    for(int i{}; i < cantidad; ++i){    //itero x la cantidad de ventas indicadas para ese mes
                    ReadBlock(ifcuvobin, venta);    //leo siguientes bytes que contienen venta
                    cuvo.at(ir).at(ic).at(im).push_back(venta); //la guardo en el cuvo de vectores
                }
                ++im;
            }
            ++ic;    
        }
        ++ir;    
    }
    ifcuvobin.close();


}


void MostrarTotales(const CUBO &Array){
for( auto r : Array) { 
    for (auto v : r){
        for (auto t : v){
            cout << t << '\t';
        }
        cout << '\n';
    }
    cout << '\n';
}
}

void MostrarVentasCapo(const CUVO &vector){
for( auto r : vector) { 
    for (auto c : r){
        for (auto m : c){
            for(auto v :m)
              cout << v << ' ';
         cout << '\n';     
        }
        cout << '\n';
    }
    cout << '\n';
}
}

//::Cálculo de Estadísticas::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

//::Stats Simples::::::::: (mejor/peor Región, Vendedor, Mes) 
//Plan A: stats en 2 pasos: iterar buscando mayor/menor venta, luego iterar 


MayorMenorIgual CompararValores(const int &a,const int &b){
    return
    a > b?  MayorMenorIgual::Mayor:
    a == b? MayorMenorIgual::Igual:MayorMenorIgual::Menor;
}


TotalesCubo CalcularTotales(const CUBO &cubo){
    TotalesCubo totales{};
    for(int ir{};ir < CantidadRegiones; ++ir){

        for(int iv{}; iv < CantidadVendedores; ++iv){

            for(int im{}; im < CantidadMeses; ++im){

                totales.Meses.at(im) += cubo[ir][iv][im];
                totales.Vendedores.at(iv) += cubo[ir][iv][im];
                totales.Regiones.at(ir) += cubo[ir][iv][im];

            }
        }
    }
    return totales;
}


array<int,3> ObtenerMejores(const TotalesCubo &tcubo){
    int mejormes{tcubo.Meses.at(0)},
        mejorvendedor{tcubo.Vendedores.at(0)},
        mejorregion{tcubo.Regiones.at(0)};    

    for(int im{}; im < CantidadMeses; ++im){
        if (CompararValores(tcubo.Meses.at(im), mejormes)!=MayorMenorIgual::Menor){
            mejormes = tcubo.Meses.at(im);        
        }
    }
    for(int iv{}; iv < CantidadVendedores; ++iv){
        if (CompararValores(tcubo.Vendedores.at(iv), mejorvendedor)!=MayorMenorIgual::Menor){
            mejorvendedor = tcubo.Vendedores.at(iv);        
        }
    }
    for(int ir{}; ir < CantidadRegiones; ++ir){
        if (CompararValores(tcubo.Regiones.at(ir), mejorregion)!=MayorMenorIgual::Menor){
            mejorregion = tcubo.Regiones.at(ir);        
        }
    }
    
    array<int,3> mejores{mejormes, mejorvendedor, mejorregion};
    return mejores;
}    

array<int,3> ObtenerPeores(const TotalesCubo &tcubo){
    int peormes{tcubo.Meses.at(0)},
        peorvendedor{tcubo.Vendedores.at(0)},
        peorregion{tcubo.Regiones.at(0)};

    for(int im{}; im < CantidadMeses; ++im){
        if (CompararValores(tcubo.Meses.at(im), peormes)!=MayorMenorIgual::Mayor){
            peormes = tcubo.Meses.at(im);        
        }
    }
    for(int iv{}; iv < CantidadVendedores; ++iv){
        if (CompararValores(tcubo.Vendedores.at(iv), peorvendedor)!=MayorMenorIgual::Mayor){
            peorvendedor = tcubo.Vendedores.at(iv);        
        }
    }
    for(int ir{}; ir < CantidadRegiones; ++ir){
        if (CompararValores(tcubo.Regiones.at(ir), peorregion)!=MayorMenorIgual::Mayor){
            peorregion = tcubo.Regiones.at(ir);        
        }
    }
    
    array<int,3> peores{peormes, peorvendedor, peorregion};
    return peores;    

}

V3 BuscarCoincidencia(const array<int,3> &array, const TotalesCubo &tcubo){
    V3 vector{};

    for(int i{}; i < 3; ++i){
        vector[i].push_back(array.at(i));
    }
    
    for(int im{}; im < CantidadMeses; ++im){
        if (CompararValores(array[0], tcubo.Meses.at(im))==MayorMenorIgual::Igual){
            vector[0].push_back(im);        
        }
    }
    for(int iv{}; iv < CantidadVendedores; ++iv){
        if (CompararValores(array[1], tcubo.Vendedores.at(iv))==MayorMenorIgual::Igual){
            vector[1].push_back(iv);        
        }
    }
    for(int ir{}; ir < CantidadRegiones; ++ir){
        if (CompararValores(array[2], tcubo.Regiones.at(ir))==MayorMenorIgual::Igual){
            vector[2].push_back(ir);        
        }
    }
    return vector;
}

void MostrarV3(const V3 &vector){
    for (auto v : vector){
        for (auto i : v){
            cout << i << " ";
        }
        cout << '\n';    
    }
}

void MostrarTotalesCubo(const TotalesCubo &tcubo){
    for (size_t i = 0; i < CantidadMeses; ++i){
        cout << tcubo.Meses.at(i) << ' ';
    }
    cout << '\n';
    for (size_t i = 0; i < CantidadVendedores; ++i){
        cout << tcubo.Vendedores.at(i) << ' ';
    }    
    cout << '\n';
    for (size_t i = 0; i < CantidadRegiones; ++i){
        cout << tcubo.Regiones.at(i) << ' ';
    }
    cout << '\n';
}
    
void MostrarMejores(const CUBO &){

}





















//no funciona, tira 100 siempre, revisar!
double GetPromedioVentas(int Desde, int Hasta){

double Sumatoria{0}, Contador{0};
int ir{0};

for ( auto r : ImporteMesVendedorRegion) { 
    int iv{0};
    for (auto v : r){
        //for (auto t : v){
        for (; Desde <= Hasta; ++Desde){
            Sumatoria += ImporteMesVendedorRegion[ir][iv].at(Desde);
            Contador += TrxMesVendedorRegion[ir][iv].at(Desde);
        }
        ++iv;
    }
    ++ir;
}
//return Contador == 0? 0:(Sumatoria/Contador);
cout << Contador << " "<< Sumatoria;
return 0;
}

//::Stats Simples::::::::: Plan B (combinar pasos plan A y evitar segunda iteracion x TotalesCubo)






















//::Presentación de Datos::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

string NombreRegion(const int numr){
   return numr == Regiones::Norte? "Norte":
          numr == Regiones::Sur?   "Sur":
          numr == Regiones::Este?  "Este": 
          numr == Regiones::Oeste? "Oeste":
                                   "No Definida";
}

string NombreVendedor(const int numv){
    if(numv+1 > CantidadVendedores || numv < 0)
        return "No Definido";
    else
    return ListaVendedores.at(numv);
}

string NombreMes(const int numm){
static array<string,CantidadMeses> ListaMeses{
    "Enero",        //0
    "Febrero",      //1
    "Marzo",        //2
    "Abril",        //3
    "Mayo",         //4
    "Junio",        //5
    "Julio",        //6
    "Agosto",       //7
    "Septiembre",   //8
    "Octubre",      //9
    "Noviembre",    //10
    "Diciembre",    //11
};
    if (numm+1 > CantidadMeses || numm < 0)
        return "No Definido";
    else
    return ListaMeses.at(numm);
}

string NombreMesAbrev(const int numm){
static array<string,CantidadMeses> ListaMesesAbrev{
    "Ene",      //0
    "Feb",      //1
    "Mar",      //2
    "Abr",      //3
    "May",      //4
    "Jun",      //5
    "Jul",      //6
    "Ago",      //7
    "Sep",      //8
    "Oct",      //9
    "Nov",      //10
    "Dic",      //11
};

    if (numm+1 > CantidadMeses || numm < 0)
        return "No Def";
    else
    return ListaMesesAbrev.at(numm);
}


void MostrarTotalesConFormato(const CUBO &cubo){
int ir{0};
cout << "Las ventas totales por Region, Vendedor y Meses son:\n";
for( auto r : cubo) {
    int iv{0};

    cout << '\t' << "Region: " << NombreRegion(ir) << '\n' 
         << "\tEne\tFeb\tMar\tAbr\tMay\tJun\tJul\tAgo\tSep\tOct\tNov\tDic\n";
    for (auto v : r){
        
        cout << NombreVendedor(iv) <<'\t';

        for (auto t : v){
            cout << t << "\t";
        }
        ++iv;
        cout << "\n";
    }
    ++ir;
    cout << "\n";
}
}

void MostrarVentasCapoFormato(const CUVO &vector){
for( auto r : vector) { 
    for (auto c : r){
        for (auto m : c){
            for(auto v :m)
              cout << v << ' ';
         cout << '\n';     
        }
        cout << '\n';
    }
    cout << '\n';
}
}