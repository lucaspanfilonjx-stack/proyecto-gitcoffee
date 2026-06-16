#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "Funciones.h"
#include "Pedido.h"

using namespace std;

int main()
{
    vector<Pedido> pedidos;

    const string NOMBRE_ARCHIVO = "pedidos.txt";

    int opcion = 0;

    do
    {
        mostrarMenu();
        cin >> opcion;

        if (cin.fail())
        {
            cin.clear();

            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            cout << "\nError: debe ingresar una opcion numerica.\n";
            continue;
        }

        switch (opcion)
        {
            case 1:
                cargarPedidos(pedidos, NOMBRE_ARCHIVO);
                break;

            case 2:
                mostrarListadoCompleto(pedidos);
                break;

            case 3:
                mostrarCalculoTotales(pedidos);
                break;

            case 4:
                mostrarResumenTotales(pedidos);
                break;

            case 5:
                mostrarPedidosPorSucursal(pedidos);
                break;

            case 6:
                buscarPedido(pedidos);
                break;

            case 7:
                mostrarProductoMasVendido(pedidos);
                break;

            case 8:
                cout << "\nPrograma finalizado.\n";
                break;

            default:
                cout << "\nOpcion incorrecta. "
                     << "Ingrese un numero del 1 al 8.\n";
        }

    } while (opcion != 8);

    return 0;
}
