C:\RepositorioCPP\22-253-06\22-253-06\15 Arreglos & Dimensiones -Total de Ventas>g++ --version
g++ (Rev3, Built by MSYS2 project) 12.1.0
Copyright (C) 2022 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

Iniciando la compilación...
C:\msys64\mingw64\bin\g++.exe -std=c++20 -fdiagnostics-color=always "C:\RepositorioCPP\22-253-06\22-253-06\15 Arreglos & Dimensiones -Total de Ventas\DIM3.cpp" -o "C:\RepositorioCPP\22-253-06\22-253-06\15 Arreglos & Dimensiones -Total de Ventas\DIM3.exe"

C:\RepositorioCPP\22-253-06\22-253-06\15 Arreglos & Dimensiones -Total de Ventas>DIM3.exe < Test3.txt  
1       1       1       1       1       1       1       1       1       1       1       1
2       2       2       2       2       2       2       2       2       2       2       2
3       3       3       3       3       3       3       3       3       3       3       3

1       1       1       1       1       1       1       1       1       1       1       1
2       2       2       2       2       2       2       2       2       2       2       2
3       3       3       3       3       3       3       3       3       3       3       3

1       1       1       1       1       1       1       1       1       1       1       1
2       2       2       2       2       2       2       2       2       2       2       2
3       3       3       3       3       3       3       3       3       3       3       3

1       1       1       1       1       1       1       1       1       1       1       1
2       2       2       2       2       2       2       2       2       2       2       2
3       3       3       3       3       3       3       3       3       3       3       3

Crédito Extra:
Describir en readme.md las ventajas y desventajas de
aplicar:
◦ for-intervalo en vez de for clásico.
◦ std::array<T,N> en vez de T[N].
◦ •.at(•) en vez de •[•].


◦ for-intervalo en vez de for clásico.
Ventajas:
El for-intervalo permite iterar a través a un array con mayor facilidad y menos código que con el for clásico. 
Desventajas:
Por defecto itera linearmente, en cambio, con for clásico uno puede aplicar criterios de iteracion mas variados de forma mas intuitiva.


◦ std::array<T,N> en vez de T[N].
Ventajas:
Es una versión mejorada del array nativo y tiene member functions adicionales.
Permite ser utilizado como argumento de una función.
Tiene un modo de acceso a sus elementos adicional (.at) además del clasico[]

Desventajas:
No encontré


◦ •.at(•) en vez de •[•].
Ventajas:
Verifica que el valor que pasamos sea valido para el índice del arreglo.

Desventajas:
Esta verificación implica una operación adicional
