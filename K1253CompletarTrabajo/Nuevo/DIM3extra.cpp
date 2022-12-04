#include <iostream>
#include <string>
#include <array>
#include <cassert>

using std::array;
using std::string;
using std::cin;
using std::cout;

/*  Credito Extra:
"Implementar las funciones que permitan representar a los vendedores con strings 
y las regiones con enum (Norte, Sur, Este, y Oeste), en vez de representarlos con números)"
??? representarlos así donde? en el txt de entrada? en las pruebas? en la salida? Voy a tratar de cubrir las 3 posibilidades
*/

/* Vendedores:Σ*-->N/{0  si Vendedor1
                     {1  si Vendedor2
                     {2  si Vendedor3 
                     {3  e.o.c         */
unsigned NumVendedor(string);

enum Regiones{Norte, Sur, Este, Oeste, Otra};
/* NumRegion:Σ*-->Z /{0   si Norte  
                     {1   si Sur    
                     {2   si Este   
                     {3   si Oeste  
                     {4   e.o.c        */
Regiones NumRegion(string);

/* NombreRegion:Z-->Σ* /{Norte  si 0
                        {Sur    si 1
                        {Este   si 2
                        {Oeste  e.o.c  */
string NombreRegion(int);

/* NombreVendedor:Z-->Σ* /{Norte  si 0
                          {Sur    si 1
                          {Este   si 2
                          {Oeste  e.o.c  */
string NombreVendedor(int);

/* Credito Extra: Implementar las funciones LeerDatos y MostrarTotales */
// LeerDatos:ε --> ε/ EDL cin>>array
void LeerDatos(); //hacer opcion con lectura desde test.txt y dejarla comentada "void LeerDatos(std::ifstream&)" LeerDatos:Test.txt --> ε/

// MostrarTotales:Z^12^3^4-->ε/ EDL cout<<array
void MostrarTotales(array<array<array<int,12>,3>,4>);

/*Credito Extra:Presentar las tablas lo más claro posible con formato, alineación numérica y con títulos.*/
// MostrarTotalesConFormato:Z^12^3^4-->ε/ EDL cout<<array
void MostrarTotalesConFormato(array<array<array<int,12>,3>,4>);

/*Credito Extra: Agregar estadísticas, por lo menos una que aplique máximo, otra mínimo, y otra promedio.*/
//GetVendedorConMasVentas:(MESxRegion)--->Σ*/ 
string GetVendedorConMasVentas(int, Regiones);

//GetVendedorConMenosVentas(mes, región)--->Σ*/
string GetVendedorConMenosVentas(int, Regiones);

//FALTA:
//GetPromedioVentas(desde mes, hasta mes) #1
//GetPromedioVentas(desde mes, hasta mes, Vendedor) #2
//GetPromedioVentas(desde mes, hasta mes, Vendedor, Región) #3 

double GetPromedioVentas(int, int);

array<array<array<int,12>,3>,4> ImporteMesVendedorRegion{};
array<array<array<int,12>,3>,4> TrxMesVendedorRegion{};

int main(){

assert(1 == Regiones::Sur);

LeerDatos();

/*
MostrarTotalesConFormato(ImporteMesVendedorRegion);
assert(GetVendedorConMasVentas(8, Regiones::Este) == GetVendedorConMasVentas(8, Regiones::Oeste));
cout << "El Vendedor con mas ventas en " << "Enero" << ", Region:" <<" Norte" <<" es: ";
cout << GetVendedorConMasVentas(0,Regiones::Norte) <<'\n';
cout << "El Vendedor con mas ventas en " << "Mayo" << ", Region:" <<" Sur" <<" es: ";
cout << GetVendedorConMasVentas(4,Regiones::Sur) <<'\n';
cout << "El Vendedor con menos ventas en " << "Enero" << ", Region:" <<" Norte" <<" es: ";
cout << GetVendedorConMenosVentas(0,Regiones::Norte) <<'\n';
*/

cout << GetPromedioVentas(0,1);
//MostrarTotalesConFormato(TrxMesVendedorRegion);

}

///////////////////////////////////////////////////////////////////////////////////////////////
void LeerDatos(){
    string Vendedor, Region;
    for (int Importe, Mes;cin >> Importe >> Mes >> Vendedor >> Region;){

    ImporteMesVendedorRegion.at(NumRegion(Region)).at(NumVendedor(Vendedor)).at(Mes) += Importe;
    ++TrxMesVendedorRegion.at(NumRegion(Region)).at(NumVendedor(Vendedor)).at(Mes);
}
}

void MostrarTotales(array<array<array<int,12>,3>,4> Array){
for( auto r : Array) { 
    for (auto v : r){
        for (auto t : v){
            cout << t << "\t";
        }
        cout << "\n";
    }
    cout << "\n";
}
}

void MostrarTotalesConFormato(array<array<array<int,12>,3>,4> Array){
int ir{0};
cout << "Las ventas totales por Region, Vendedor y Meses son:\n";
for( auto r : Array) {
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

// cambiar int r x enum Regiones::Norte, etc
string NombreRegion(int numr){
   return numr == Regiones::Norte? "Norte":
          numr == Regiones::Sur?   "Sur":
          numr == Regiones::Este?  "Este": 
                                   "Oeste";
}

Regiones NumRegion(string nomr){
    return nomr == "Norte"? Norte:
           nomr == "Sur"?   Sur:
           nomr == "Este"?  Este:
           nomr == "Oeste"? Oeste:
                            Otra; // para evitar que cualquier string entre como "Oeste"
}

string NombreVendedor(int numv){
    return numv == 0 ? "Juan":
           numv == 1 ? "Juana":
                       "Jorge";
}

unsigned NumVendedor(string NombreVendedor){
    return NombreVendedor == "Juan"?    0:
           NombreVendedor == "Juana"?   1:
           NombreVendedor == "Jorge"?   2:
                                        3;// para evitar que cualquier otro string pase como "Jorge"
}

string GetVendedorConMasVentas(int Mes, Regiones Region){
    int A, B, C;
    
    A = ImporteMesVendedorRegion.at(Region)[0].at(Mes);
    B = ImporteMesVendedorRegion.at(Region)[1].at(Mes);
    C = ImporteMesVendedorRegion.at(Region)[2].at(Mes);

    return 
    (A == B) && (A == C)? "Todos tienen la misma venta":
    (A > B) && (A > C)? "Juan":
    (B > A) && (B > C)? "Juana":
    (C > A) && (C > B)? "Jorge":
    (A == B) && (A > C)? "Juan y Juana":
    (A == C) && (A > B)? "Juan y Jorge":
    (B == C) && (B > A)? "Juana y Jorge":"Algo falló";
    
}

string GetVendedorConMenosVentas(int Mes, Regiones Region){
    int A, B, C;
    
    A = ImporteMesVendedorRegion.at(Region)[0].at(Mes);
    B = ImporteMesVendedorRegion.at(Region)[1].at(Mes);
    C = ImporteMesVendedorRegion.at(Region)[2].at(Mes);

    return 
    (A == B) && (A == C)? "Todos tienen la misma venta":
    (A < B) && (A < C)? "Juan":
    (B < A) && (B < C)? "Juana":
    (C < A) && (C < B)? "Jorge":
    (A == B) && (A < C)? "Juan y Juana":
    (A == C) && (A < B)? "Juan y Jorge":
    (B == C) && (B < A)? "Juana y Jorge":"Algo falló";

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
