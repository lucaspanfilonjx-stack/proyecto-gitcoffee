#include "Funciones.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

using namespace std;

// Comprueba si hay pedidos cargados
bool hayPedidosCargados(const vector<Pedido>& pedidos)
{
    if (pedidos.empty())
    {
        cout << "\nPrimero debe cargar los pedidos desde el archivo.\n";
        return false;
    }

    return true;
}

// Muestra todos los datos de un pedido
void mostrarDatosPedido(const Pedido& pedido)
{
    cout << fixed << setprecision(2);

    cout << "\n----------------------------------------\n";
    cout << "Numero de pedido: " << pedido.numeroPedido << "\n";
    cout << "Nombre del cliente: " << pedido.nombreCliente << "\n";
    cout << "Producto: " << pedido.producto << "\n";
    cout << "Cantidad: " << pedido.cantidad << "\n";
    cout << "Precio unitario: $" << pedido.precioUnitario << "\n";
    cout << "Sucursal: " << pedido.sucursal << "\n";
    cout << "Total del pedido: $" << calcularTotal(pedido) << "\n";
    cout << "----------------------------------------\n";
}

// Calcula cantidad por precio unitario
double calcularTotal(const Pedido& pedido)
{
    return pedido.cantidad * pedido.precioUnitario;
}

// 1. Carga los pedidos desde pedidos.txt
bool cargarPedidos(
    vector<Pedido>& pedidos,
    const string& nombreArchivo
)
{
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open())
    {
        cout << "\nError: no se pudo abrir "
             << nombreArchivo << ".\n";

        cout << "Revise que el archivo se encuentre "
             << "en la carpeta del proyecto.\n";

        return false;
    }

    // Evita duplicar pedidos si se carga dos veces
    pedidos.clear();

    string linea;
    int numeroLinea = 0;

    while (getline(archivo, linea))
    {
        numeroLinea++;

        if (linea.empty())
        {
            continue;
        }

        stringstream registro(linea);

        Pedido pedido;
        string numeroTexto;
        string cantidadTexto;
        string precioTexto;

        if (
            getline(registro, numeroTexto, ';') &&
            getline(registro, pedido.nombreCliente, ';') &&
            getline(registro, pedido.producto, ';') &&
            getline(registro, cantidadTexto, ';') &&
            getline(registro, precioTexto, ';') &&
            getline(registro, pedido.sucursal)
        )
        {
            try
            {
                pedido.numeroPedido = stoi(numeroTexto);
                pedido.cantidad = stoi(cantidadTexto);
                pedido.precioUnitario = stod(precioTexto);

                pedidos.push_back(pedido);
            }
            catch (...)
            {
                cout << "Linea " << numeroLinea
                     << ": contiene datos numericos incorrectos.\n";
            }
        }
        else
        {
            cout << "Linea " << numeroLinea
                 << ": tiene un formato incorrecto.\n";
        }
    }

    archivo.close();

    cout << "\nArchivo cargado correctamente.\n";
    cout << "Pedidos cargados: " << pedidos.size() << "\n";

    return !pedidos.empty();
}

// 2. Muestra el listado completo
void mostrarListadoCompleto(const vector<Pedido>& pedidos)
{
    if (!hayPedidosCargados(pedidos))
    {
        return;
    }

    cout << "\n========== LISTADO COMPLETO DE PEDIDOS ==========\n";

    for (const Pedido& pedido : pedidos)
    {
        mostrarDatosPedido(pedido);
    }
}

// 3. Calcula el total de cada pedido
void mostrarCalculoTotales(const vector<Pedido>& pedidos)
{
    if (!hayPedidosCargados(pedidos))
    {
        return;
    }

    cout << fixed << setprecision(2);

    cout << "\n========== CALCULO DEL TOTAL DE CADA PEDIDO ==========\n";

    for (const Pedido& pedido : pedidos)
    {
        cout << "Pedido " << pedido.numeroPedido << ": "
             << pedido.cantidad
             << " x $" << pedido.precioUnitario
             << " = $" << calcularTotal(pedido)
             << "\n";
    }
}

// 4. Muestra número, cliente y total
void mostrarResumenTotales(const vector<Pedido>& pedidos)
{
    if (!hayPedidosCargados(pedidos))
    {
        return;
    }

    cout << fixed << setprecision(2);

    cout << "\n========== RESUMEN DE PEDIDOS ==========\n";

    for (const Pedido& pedido : pedidos)
    {
        cout << "\nNumero de pedido: "
             << pedido.numeroPedido << "\n";

        cout << "Nombre del cliente: "
             << pedido.nombreCliente << "\n";

        cout << "Total del pedido: $"
             << calcularTotal(pedido) << "\n";

        cout << "----------------------------------------\n";
    }
}

// 5. Cuenta los pedidos por sucursal
void mostrarPedidosPorSucursal(const vector<Pedido>& pedidos)
{
    if (!hayPedidosCargados(pedidos))
    {
        return;
    }

    int centro = 0;
    int nuevaCordoba = 0;
    int generalPaz = 0;
    int otras = 0;

    for (const Pedido& pedido : pedidos)
    {
        if (pedido.sucursal == "Centro")
        {
            centro++;
        }
        else if (pedido.sucursal == "Nueva Cordoba")
        {
            nuevaCordoba++;
        }
        else if (pedido.sucursal == "General Paz")
        {
            generalPaz++;
        }
        else
        {
            otras++;
        }
    }

    cout << "\n========== PEDIDOS POR SUCURSAL ==========\n";
    cout << "Centro: " << centro << " pedidos\n";
    cout << "Nueva Cordoba: " << nuevaCordoba << " pedidos\n";
    cout << "General Paz: " << generalPaz << " pedidos\n";

    if (otras > 0)
    {
        cout << "Sucursal no reconocida: "
             << otras << " pedidos\n";
    }
}

// 6. Busca un pedido por número
void buscarPedido(const vector<Pedido>& pedidos)
{
    if (!hayPedidosCargados(pedidos))
    {
        return;
    }

    int numeroBuscado;

    cout << "\nIngrese el numero de pedido: ";
    cin >> numeroBuscado;

    if (cin.fail())
    {
        cin.clear();

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );

        cout << "Debe ingresar un numero valido.\n";
        return;
    }

    for (const Pedido& pedido : pedidos)
    {
        if (pedido.numeroPedido == numeroBuscado)
        {
            cout << "\nPedido encontrado:\n";
            mostrarDatosPedido(pedido);
            return;
        }
    }

    cout << "\nNo se encontro el pedido numero "
         << numeroBuscado << ".\n";
}

// 7. Busca el producto con mayor cantidad vendida
void mostrarProductoMasVendido(const vector<Pedido>& pedidos)
{
    if (!hayPedidosCargados(pedidos))
    {
        return;
    }

    vector<string> productos;
    vector<int> cantidadesVendidas;

    // Agrupa y suma las cantidades de cada producto
    for (const Pedido& pedido : pedidos)
    {
        bool encontrado = false;

        for (size_t i = 0; i < productos.size(); i++)
        {
            if (productos[i] == pedido.producto)
            {
                cantidadesVendidas[i] += pedido.cantidad;
                encontrado = true;
                break;
            }
        }

        if (!encontrado)
        {
            productos.push_back(pedido.producto);
            cantidadesVendidas.push_back(pedido.cantidad);
        }
    }

    int mayorCantidad = cantidadesVendidas[0];

    for (size_t i = 1; i < cantidadesVendidas.size(); i++)
    {
        if (cantidadesVendidas[i] > mayorCantidad)
        {
            mayorCantidad = cantidadesVendidas[i];
        }
    }

    cout << "\n========== PRODUCTO MAS VENDIDO ==========\n";

    // También muestra posibles empates
    for (size_t i = 0; i < productos.size(); i++)
    {
        if (cantidadesVendidas[i] == mayorCantidad)
        {
            cout << "Producto: " << productos[i] << "\n";

            cout << "Cantidad total vendida: "
                 << cantidadesVendidas[i] << "\n";
        }
    }
}

// Muestra el menú principal
void mostrarMenu()
{
    cout << "\n============================================\n";
    cout << "   SISTEMA DE PEDIDOS - CAFETERIA GITCOFFEE\n";
    cout << "============================================\n";
    cout << "1. Cargar pedidos desde pedidos.txt\n";
    cout << "2. Mostrar listado completo\n";
    cout << "3. Calcular el total de cada pedido\n";
    cout << "4. Mostrar numero, cliente y total\n";
    cout << "5. Mostrar cantidad de pedidos por sucursal\n";
    cout << "6. Buscar un pedido por numero\n";
    cout << "7. Mostrar el producto mas vendido\n";
    cout << "8. Salir\n";
    cout << "============================================\n";
    cout << "Seleccione una opcion: ";
}
