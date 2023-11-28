#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Producto {
    string nombre;
    float precio;
    int stock;
};

struct Usuario {
    string nombre;
    string clave;
};

struct Cliente {
    string nombre;
    string direccion;
    vector<pair<string, int>> productosComprados;  
};

struct MaterialBasico {
    string nombre;
    int cantidad;
    int valor;
};

struct Factura {
    string nombreCliente;
    vector<pair<string, int>> productosComprados;
    float subtotal;
    float iva;
    float total;
};

int main() {
    vector<Producto> inventario = {
        {"Pastel de garbanzo", 1500.0, 100},
        {"Pastel de pollo", 1800.0, 100},
        {"Pastel mixto", 1800.0, 100},
        {"Pastel de arroz con carne", 1600.0, 100},
        {"Papa rellena", 2000.0, 100}
    };

    vector<Usuario> usuarios = {{"Erick", "FESC"}, {"Marlen", "FESC"}};
    vector<Cliente> clientes;
    vector<MaterialBasico> stockMateriales;
    int cont;
    cont=0;
    int cont2;
    cont2=0;
    float gananciaNeta;
    int rol;
    string nombreUsuario, claveUsuario;

    inicio:

    while (true) {
        cout << "¿Eres propietario o cliente?" << endl;
        cout << "1: Cliente" << endl;
        cout << "2: Propietario" << endl;
        cin >> rol;

        switch (rol) {
             case 1: {
                Cliente cliente1;
                cout << "Nombre del cliente: ";
                cin >> cliente1.nombre;
                cout << "Dirección del domicilio: ";
                cin.ignore();
                getline(cin, cliente1.direccion);
                clientes.push_back(cliente1);

                do {
                    cout << "1: Pastel de garbanzo $1500" << endl;
                    cout << "2: Pastel de pollo $1800" << endl;
                    cout << "3: Pastel mixto $1800" << endl;
                    cout << "4: Pastel de arroz con carne $1600" << endl;
                    cout << "5: Papa rellena $2000" << endl;
                    int opcionCompra;
                    cout << "Selecciona el número del producto que deseas comprar (0 para salir): ";
                    cin >> opcionCompra;

                    if (opcionCompra == 0) {
                        break; 
                    }

                    if (opcionCompra < 1 || opcionCompra > inventario.size()) {
                        cout << "Opción de compra no válida. Intenta de nuevo." << endl;
                        continue; 
                    }

                    int cantidadCompra;
                    cout << "¿Cuántos productos deseas comprar? ";
                    cin >> cantidadCompra;

                    if (inventario[opcionCompra - 1].stock >= cantidadCompra) {
                        inventario[opcionCompra - 1].stock -= cantidadCompra;
                        clientes.back().productosComprados.push_back({inventario[opcionCompra - 1].nombre, cantidadCompra});
                    } else {
                        cout << "No hay suficiente stock disponible para la compra. Intenta de nuevo." << endl;
                    }

                } while (true); 
                Factura factura;
                factura.nombreCliente = clientes.back().nombre;
                factura.productosComprados = clientes.back().productosComprados;
                factura.subtotal = 0.0;
                for (const auto &producto : factura.productosComprados) {
                    int indiceProducto = -1;
                    for (int i = 0; i < inventario.size(); ++i) {
                        if (inventario[i].nombre == producto.first) {
                            indiceProducto = i;
                            break;
                        }
                    }
                    if (indiceProducto != -1) {
                        factura.subtotal += inventario[indiceProducto].precio * producto.second;
                    }
                }
                std::cout << std::fixed << std::setprecision(2);
                factura.iva = factura.subtotal * 0.19;
                factura.total = factura.subtotal + factura.iva;

                cout << "Compra realizada con éxito. Detalles de la factura:" << endl;
                cout << "Cliente: " << factura.nombreCliente << endl;
                cout << "Productos comprados:" << endl;
                for (const auto &producto : factura.productosComprados) {
                    cout << "  - " << producto.first << ": " << producto.second << " unidades" << endl;
                }
                cout << "Subtotal: $" << factura.subtotal << endl;
                cout << "IVA (19%): $" << factura.iva << endl;
                cout << "Total a pagar: $" << factura.total << endl;
                cont += factura.total;

                break; 
            }

            case 2: {
                cout << "Iniciar sesión:" << endl;
                cout << "Nombre de usuario: ";
                cin >> nombreUsuario;
                cout << "Clave: ";
                cin >> claveUsuario;

                bool autenticado = false;

                for (const Usuario &usuario : usuarios) {
                    if (usuario.nombre == nombreUsuario && usuario.clave == claveUsuario) {
                        autenticado = true;
                        cout << "Inicio de sesión exitoso." << endl;
                        break;
                    }
                }

                if (!autenticado) {
                    cout << "Inicio de sesión fallido. Usuario no autenticado." << endl;
                    break;
                }

                while (true) {
                    int opcion;
                    cout << "Menú:" << endl;
                    cout << "1. Agregar cantidad a inventario" << endl;
                    cout << "2. Mostrar inventario" << endl;
                    cout << "3. Mostrar información de los clientes" << endl;
                    cout << "4. Agregar material básico al stock" << endl;
                    cout << "5. Mostrar stock de materiales básicos" << endl;
                    cout << "6. Mostrar informe de ingresos y gastos" << endl;
                    cout << "7. Volver al menu principal" << endl;
                    cout << "8. Salir del programa" << endl;
                    cout << "Elige una opción: ";
                    cin >> opcion;

                    switch (opcion) {
                        case 1: {
                            int opcionAgregarStock;
                            cout << "Seleccione el producto al cual desea agregar stock:" << endl;
                            for (int i = 0; i < inventario.size(); ++i) {
                                cout << i + 1 << ": " << inventario[i].nombre << " - Stock: " << inventario[i].stock << endl;
                            }
                            cin >> opcionAgregarStock;

                            if (opcionAgregarStock >= 1 && opcionAgregarStock <= inventario.size()) {
                                int cantidadAgregarStock;
                                cout << "Ingrese la cantidad a agregar al stock: ";
                                cin >> cantidadAgregarStock;

                                inventario[opcionAgregarStock - 1].stock += cantidadAgregarStock;
                                cout << "Stock actualizado con éxito." << endl;
                            } else {
                                cout << "Opción no válida. Saliendo del programa." << endl;
                            }
                            break;
                        }

                       case 2:
                            cout << "Inventario:" << endl;
                            for (const Producto &producto1 : inventario) {
                                cout << "Nombre: " << producto1.nombre << endl;
                                cout << "Precio: " << producto1.precio << endl;
                                cout << "Stock: " << producto1.stock << endl;
                            }
                            break;
                            case 3:
                            cout << "Información de los clientes:" << endl;
                            for (const Cliente &cliente : clientes) {
                                cout << "Nombre: " << cliente.nombre << endl;
                                cout << "Dirección: " << cliente.direccion << endl;
                                cout << "Productos comprados:" << endl;
                                for (const auto &producto : cliente.productosComprados) {
                                    cout << "  - " << producto.first << ": " << producto.second << " unidades" << endl;
                                    
                                }
                                cout << "------------------------" << endl;
                                
                            }
                            break;
                      
                        case 4: {
                            MaterialBasico materialBasico1;
                            cout << "Nombre del material: ";
                            cin >> materialBasico1.nombre;
                            cout << "Cantidad en kilos del material: ";
                            cin >> materialBasico1.cantidad;
                            cout << "Precio: ";
                            cin >> materialBasico1.valor;
                            stockMateriales.push_back(materialBasico1);
                            cont2 += materialBasico1.valor;
                            cout << "Material básico agregado con éxito." << endl;
                        }
                        break;
                        case 5:
                            cout << "Stock de materiales básicos:" << endl;
                            for (const MaterialBasico &MaterialBasico1 : stockMateriales) {
                                cout << "Nombre: " << MaterialBasico1.nombre << endl;
                                cout << "Cantidad en stock: " << MaterialBasico1.cantidad << endl;
                            }
                            break;
                        case 6: {
                            cout << "La ganancia bruta es: " << cont << endl;
                            cout << "Los gastos son: " << cont2 << endl;
                            float gananciaNeta = cont - (cont2+450000);
                            cout << "La ganancia neta es: " << gananciaNeta << endl;
                            break;
                        }

                        case 7:
                            int respuesta;
                            cout << "¿Quieres pasar al rol de comprador? (1: si / 2: no): ";
                            cin >> respuesta;

                            if (respuesta == 1) {
                                goto inicio;
                            } else {
                                cout << "Volviendo al menú principal." << endl;
                                break;
                            }
                        case 8:
                        cout << "Saliendo del programa." << endl;
                        return 0;

                    }
                }
            }
            break;
        }
    }

    return 0;
}