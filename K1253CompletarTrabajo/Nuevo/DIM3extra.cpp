#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <string>
#include <cassert>
#include "Blockstream.h"

//para definir tamaño del "CUBO"
#define CantidadRegiones 4      //si mas de 4 agregar a enum regiones, si menos definir en enum cuales
#define CantidadVendedores 3    //si mas de 3 modificar "ListaVendedores" si menos, definir cuales quedan
#define CantidadMeses 12        //si se pone mas de 12 modificar "ListaMeses", si se pone menos de 12, definir cuales en "ListaMeses"    
//para definir tamaño del "CUVO"
#define CantidadCapos 1         //para definir tamaño array vendedores en "ventas del capo"
#define RegionesCapos 1         //para definir tamaño array regiones en "ventas del capo"
#define ElCapo 0                //para definir que vendedor es el capo
#define RegionDelCapo 0         //para definir cual es la region del capo
// #define InicioVector 16          //para posible seteo de tamaño inicial para cada mes-vector del capo (hacer funcion?) *desestimado atm
#define ArchivoDeTexto "data.txt"   //para definir nombre de archivo
#define ArchivoBinario "data.bin"   //aca podria tenerotro para la cantidad de ventas             *revisar
#define CapoBIN "capo.bin"          //para definir el nombre de archivo

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

// MostrarV3: Z^N^3 -->ε/ EDL cout<<V3
void MostrarV3(const V3 &);

// MostrarTotalesCubo: (Z^12,Z^3,Z^4)-->ε/ EDL cout<<Totales Cubo
void MostrarTotalesCubo(const TotalesCubo &);




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



// para agrupar funciones modulares y no tener que anidar llamados en main
void MostrarMejoresCubo(const CUBO &);

// para agrupar funciones modulares y no tener que anidar llamados en main
void MostrarPeoresCubo(const CUBO &);








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

//MostrarVentasCapoFormato: CUVO --> void/ EDL cout << CUVO
void MostrarVentasCapoFormato(const CUVO &);

//MostrarTotalesCuboFormato: Struct TotalesCubo--> void/ EDL cout << TotalesCubo
void MostrarTotalesCuboFormato(const TotalesCubo &);

//
void MostrarV3Formato(const V3 &);

//
void MostrarMejoresCuboFormato(const CUBO &);

//
void MostrarPeoresCuboFormato(const CUBO &);










//se alimentan desde CIN o archivo txt
CUBO ImporteMesVendedorRegion{};
CUBO TrxMesVendedorRegion{};
CUVO VentasDelCapo{};

//se alimentan desde archivos binarios, los diferencie para facilitarme verificacion si flujo a .bin ok 
CUBO IMVRbin{};
CUBO TMVRbin{};
CUVO VCbin{};

//::::::::MAIN:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
int main(){

assert(1 == Regiones::Sur);

LeerDatosTxt();
GuardarCuboBin(ImporteMesVendedorRegion);
LeerCuboBin(IMVRbin);
GuardarCuvoBin(VentasDelCapo);
MostrarTotalesConFormato(IMVRbin);
LeerCuvoBIN(VCbin);
MostrarVentasCapoFormato(VCbin);

assert(sizeof ImporteMesVendedorRegion == sizeof TrxMesVendedorRegion);
assert(sizeof VentasDelCapo == sizeof VCbin);

MostrarTotalesCuboFormato(CalcularTotales(ImporteMesVendedorRegion));
MostrarMejoresCuboFormato(ImporteMesVendedorRegion);
MostrarPeoresCuboFormato(IMVRbin);
//cout << GetPromedioVentas(0,1);

}















//:::::::::::::::::::::::Implementaciones::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

//::Flujo de Datos:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

void LeerDatosCIN(){
    
    for (int Importe{}, Mes{}, Vendedor{}, Region{};cin >> Importe >> Mes >> Vendedor >> Region;){

    ImporteMesVendedorRegion.at(Region).at(Vendedor).at(Mes) += Importe;
    ++TrxMesVendedorRegion.at(Region).at(Vendedor).at(Mes);

    if (Vendedor == ElCapo && Region == RegionDelCapo) // si hubiera mas de un capo >> llamar funcion "SosUnCapo?" (x ahora fuera del scope tp)
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

    if (Vendedor == ElCapo && Region == RegionDelCapo){ // si hubiera mas de un capo >> llamar funcion "SosUnCapo?" *pendiente se va de scope tp?
        GuardarVentaDelCapo(Region, Vendedor, Mes, Importe);
        }
    }
    ifdatatxt.close();
}

void GuardarVentaDelCapo(const int r,const int c,const int m,const int v){
    VentasDelCapo.at(r).at(c).at(m).push_back(v);
}


void GuardarCuboBin(const CUBO &array){
    //constexpr auto filename{DataFileBIN}; ??? << investigar
    static ofstream ofcubobin{ArchivoBinario, std::ios::binary};
	WriteBlock(ofcubobin, array);
	ofcubobin.close();
}

void LeerCuboBin(CUBO &array){   
    static ifstream ifcubobin{ArchivoBinario, std::ios::binary};
    ReadBlock(ifcubobin, array);
    ifcubobin.close();
}

void GuardarCuvoBin(const CUVO &cuvo){
    static ofstream ofcuvobin{CapoBIN, std::ios::binary};

    int ir{};
    for(auto r : cuvo){  //itero x regiones capos, ya predefinido en #define, marco nro region
        WriteBlock (ofcuvobin, ir);
        int ic{};
        for(auto c : r){  //itero x cada capo, ya predefinido en #define,  marco nro capo
            WriteBlock(ofcuvobin, ic);
            int im{};
            for(auto m : c){ //itero x cada mes, marco mes
                WriteBlock(ofcuvobin, im);
                int cantidad{};
                cantidad = m.size();
                WriteBlock(ofcuvobin, cantidad); //marco cuantas ventas tiene el mes
                for (auto v : m){
                    WriteBlock(ofcuvobin, v); //escribo ventas
                }            
                ++im;
            }
            ++ic;
        }
        ++ir;
    }
    ofcuvobin.close();
}

void LeerCuvoBIN(CUVO &cuvo){
    static ifstream ifcuvobin{CapoBIN, std::ios::binary};
    int ir{};
    for(auto r : cuvo){ //itero x regiones capos, ya predefinido en #define
        ReadBlock(ifcuvobin, ir); //leo que region es
        int ic{};
        for(auto c : r){    //itero x cada capo, ya predefinido en #define
            ReadBlock(ifcuvobin, ic); //leo cual capo es
            int im{};
            for(auto m : c){    //itero x cada mes,
                ReadBlock(ifcuvobin,im); //leo que mes es
                int cantidad{};
                ReadBlock(ifcuvobin, cantidad);  //leo cantidad ventas del mes
                cuvo.at(ir).at(ic).at(im).resize(cantidad); //acomodo capacidad del vector mes a esa cantidad
                cuvo.at(ir).at(ic).at(im).clear();  //limpio vector destino en caso que hubiese algun dato residual, quizas redundante
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
for( auto r : Array){ 
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
    for( auto r : vector){ 
        for (auto c : r){
            for (auto m : c){
                for(auto v :m){
                cout << v << ' ';              
                }
            cout << '\n';
            }
        cout << '\n';
        }
    cout << '\n';    
    }
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


//::Cálculo de Estadísticas::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

//::Stats Simples::::::::: (mejor/peor Región, Vendedor, Mes) 
//Plan A: stats en 2 pasos: iterar buscando mayor/menor venta, luego iterar buscando coincidencia > guardarla > mostrarla


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


    
void MostrarMejoresCubo(const CUBO &cubo){
    TotalesCubo tc{};
    tc = CalcularTotales(cubo);
    MostrarV3(BuscarCoincidencia(ObtenerMejores(tc),tc));
}

void MostrarPeoresCubo(const CUBO &cubo){
    TotalesCubo tc{};
    tc = CalcularTotales(cubo);
    MostrarV3(BuscarCoincidencia(ObtenerPeores(tc),tc));
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




//::Stats con Parametros Variables:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

















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

void MostrarVentasCapoFormato(const CUVO &cuvo){
cout << "Las ventas del Capo:";
int ir{};    
for( auto r : cuvo){
    int ic{};
    cout << "(Region:" << NombreRegion(ir) <<" "; 
    for (auto c : r){
        int im{};
        cout << "Vendedor:" << NombreVendedor(ic) << ")\n"; 
        for (auto m : c){
            cout << NombreMesAbrev(im) <<"\t";
            for(auto v :m)
            cout << "$"<< v << ' ';
            ++im;
            cout << '\n';     
            }
        cout << '\n';
        ++ic;
        }
    cout << '\n';
    ++ir;
    }
}

void MostrarTotalesCuboFormato(const TotalesCubo &tcubo){
    cout << "La venta total fue:$" << tcubo.Vendedores.at(0)+ tcubo.Vendedores.at(1)+ tcubo.Vendedores.at(2); // *a mejorar con loop

    cout << "\n\nTotales agrupados por Mes, Vendedor y Region:\n";
    for (size_t i = 0; i < CantidadMeses; ++i){
        cout << NombreMesAbrev(i) << ":$" << tcubo.Meses.at(i) << "  ";
    }
    cout << '\n';
    for (size_t i = 0; i < CantidadVendedores; ++i){
        cout << NombreVendedor(i) << ":$"<< tcubo.Vendedores.at(i) << "   ";
    }    
    cout << '\n';
    for (size_t i = 0; i < CantidadRegiones; ++i){
        cout << NombreRegion(i) << ":$" << tcubo.Regiones.at(i) << "   ";
    }
    cout << "\n\n";
}

void MostrarV3Formato(const V3 &v3){
    cout << "Por Mes:$" << v3.at(0).at(0) << " en ";
    for (unsigned im{1}; im < v3.at(0).size(); ++im){
       cout << NombreMes(v3.at(0).at(im)) << ' ';
    }

    cout << '\n';
    cout << "Por Vendedor:$"<< v3.at(1).at(0) << " de ";
    for (unsigned iv{1}; iv < v3.at(1).size(); ++iv){
       cout << NombreVendedor(v3.at(1).at(iv)) << ' ';
    }    

    cout << '\n';
    cout << "Por Region:$"<< v3.at(2).at(0) << " en el ";
    for (unsigned ir{1}; ir < v3.at(2).size(); ++ir){
       cout << NombreRegion(v3.at(2).at(ir)) << ' ';
    }
    cout << "\n\n";
}

void MostrarMejoresCuboFormato(const CUBO &cubo){
    cout << "Las mejores ventas fueron:\n";

    TotalesCubo tc{};
    tc = CalcularTotales(cubo);
    MostrarV3Formato(BuscarCoincidencia(ObtenerMejores(tc),tc));

}


void MostrarPeoresCuboFormato(const CUBO &cubo){
    cout << "Las peores ventas fueron:\n";

    TotalesCubo tc{};
    tc = CalcularTotales(cubo);
    MostrarV3Formato(BuscarCoincidencia(ObtenerPeores(tc),tc));

}