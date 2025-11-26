#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>
#include <cstdlib>
#include <windows.h>
using namespace std;

struct Usuario {
    int idUsuario;
    string nombre;
    string correoElectronico;
    string contrasena; 
    string direccion;
    string metodoDePago;
};

struct CarritoDeCompras {
    int idCarrito;
    string nombreUsuario;     
    vector<int> productosIds;
    double subtotal;
    double impuestos;
};

struct OrdenDeCompra {
    int idOrden;
    vector<int> productosIds;
    long subtotal;
    double impuestos;
    double envio;
    double total;
};

struct Categoria {
    int idCategoria;
    string nombre;
};

struct Comentario {             
    int idComentario;
    string nombreProducto;
    string nombreUsuario;
    string comentario;
    string fecha;
};

struct Producto {
    int idProducto;
    string nombre;
    string descripcion;
    double precio;
    int stock;
};

vector<Usuario> usuarios;
vector<Producto> productos;
vector<Comentario> comentarios;        
vector<CarritoDeCompras> carritos;     
vector<OrdenDeCompra> ordenes;         
vector<Categoria> categorias;

// =====================================================
// FUNCIÓN: limpiarString() - NUEVA
// Elimina espacios en blanco al inicio y final
// =====================================================
string limpiarString(string str) {
    // Eliminar espacios al inicio
    size_t inicio = str.find_first_not_of(" \t\r\n");
    if (inicio == string::npos) return "";
    
    // Eliminar espacios al final
    size_t fin = str.find_last_not_of(" \t\r\n");
    return str.substr(inicio, fin - inicio + 1);
}

// =====================================================
// FUNCIÓN: dividirLinea() - NUEVA
// Divide una línea CSV en campos
// =====================================================
vector<string> dividirLinea(string linea) {
    vector<string> campos;
    stringstream ss(linea);
    string campo;
    
    while (getline(ss, campo, ',')) {
        campos.push_back(limpiarString(campo));
    }
    
    return campos;
}

// =====================================================
// FUNCIÓN: cargarUsuarios() - NUEVA
// Carga usuarios desde archivo Usuarios.txt
// =====================================================
bool cargarUsuarios() {
    ifstream archivo("Usuarios.txt");
    
    if (!archivo.is_open()) {
        cout << "ERROR: No se pudo abrir Usuarios.txt\n";
        return false;
    }
    
    string linea;
    getline(archivo, linea); // Saltar encabezado
    
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        
        vector<string> campos = dividirLinea(linea);
        
        if (campos.size() >= 6) {
            Usuario u;
            u.idUsuario = atoi(campos[0].c_str());
            u.nombre = campos[1];
            u.correoElectronico = campos[2];
            u.contrasena = campos[3];
            u.direccion = campos[4];
            u.metodoDePago = campos[5];
            
            usuarios.push_back(u);
        }
    }
    
    archivo.close();
    return true;
}

// =====================================================
// FUNCIÓN: cargarProductos() - NUEVA
// Carga productos desde archivo Productos.txt
// =====================================================
bool cargarProductos() {
    ifstream archivo("Productos.txt");
    
    if (!archivo.is_open()) {
        cout << "ERROR: No se pudo abrir Productos.txt\n";
        return false;
    }
    
    string linea;
    getline(archivo, linea); // Saltar encabezado
    
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        
        vector<string> campos = dividirLinea(linea);
        
        if (campos.size() >= 5) {
            Producto p;
            p.idProducto = atoi(campos[0].c_str());
            p.nombre = campos[1];
            p.descripcion = campos[2];
            p.precio = atof(campos[3].c_str());
            p.stock = atoi(campos[4].c_str());
            
            productos.push_back(p);
        }
    }
    
    archivo.close();
    return true;
}

// =====================================================
// FUNCIÓN: cargarComentarios() - NUEVA
// Carga comentarios desde archivo Comentarios.txt
// =====================================================
bool cargarComentarios() {
    ifstream archivo("Comentarios.txt");
    
    if (!archivo.is_open()) {
        cout << "ERROR: No se pudo abrir Comentarios.txt\n";
        return false;
    }
    
    string linea;
    getline(archivo, linea); // Saltar encabezado
    
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        
        vector<string> campos = dividirLinea(linea);
        
        if (campos.size() >= 5) {
            Comentario c;
            c.idComentario = atoi(campos[0].c_str());
            c.nombreProducto = campos[1];
            c.nombreUsuario = campos[2];
            c.comentario = campos[3];
            c.fecha = campos[4];
            
            comentarios.push_back(c);
        }
    }
    
    archivo.close();
    return true;
}

// =====================================================
// FUNCIÓN: guardarProductos() - NUEVA
// Guarda productos actualizados en archivo
// =====================================================
bool guardarProductos() {
    ofstream archivo("Productos.txt");
    
    if (!archivo.is_open()) {
        cout << "ERROR: No se pudo escribir en Productos.txt\n";
        return false;
    }
    
    // Escribir encabezado
    archivo << "idProducto,nombre,descripcion,precio,stock\n";
    
    // Escribir productos
    for (int i = 0; i < productos.size(); i++) {
        archivo << productos[i].idProducto << ","
                << productos[i].nombre << ","
                << productos[i].descripcion << ","
                << productos[i].precio << ","
                << productos[i].stock << "\n";
    }
    
    archivo.close();
    return true;
}

// =====================================================
// FUNCIÓN: cargarDatos() - MODIFICADA
// Carga todos los datos desde archivos
// =====================================================
void cargarDatos() {
    cout << "\n Cargando datos desde archivos...\n";
    
    bool usuariosOk = cargarUsuarios();
    bool productosOk = cargarProductos();
    bool comentariosOk = cargarComentarios();
    
    if (usuariosOk && productosOk && comentariosOk) {
        cout << " Datos cargados exitosamente!\n";
        cout << " - Usuarios: " << usuarios.size() << "\n";
        cout << " - Productos: " << productos.size() << "\n";
        cout << " - Comentarios: " << comentarios.size() << "\n";
    } else {
        cout << " ERROR: No se pudieron cargar todos los archivos.\n";
        cout << " Asegúrese de que los archivos TXT estén en el mismo directorio.\n";
    }
}

// =====================================================
// FUNCIÓN: mostrarDatosCargados() 
// =====================================================
void mostrarDatosCargados() {
    cout << "\n========== DATOS CARGADOS ==========\n";
    
    cout << "\n--- Usuarios cargados: " << usuarios.size() << " ---\n";
    for (int i = 0; i < usuarios.size(); i++) {
        cout << usuarios[i].idUsuario << " - " << usuarios[i].nombre 
             << " - " << usuarios[i].correoElectronico << endl;
    }

    cout << "\n--- Productos cargados: " << productos.size() << " ---\n";
    for (int i = 0; i < productos.size(); i++) {
        cout << productos[i].idProducto << " - " << productos[i].nombre 
             << " - Stock: " << productos[i].stock << endl;
    }

    cout << "\n--- Comentarios cargados: " << comentarios.size() << " ---\n";
    for (int i = 0; i < comentarios.size(); i++) {
        cout << comentarios[i].idComentario << " - " << comentarios[i].nombreUsuario 
             << " comentó sobre " << comentarios[i].nombreProducto << endl;
    }
}

// =====================================================
// FUNCIÓN: iniciarSesion()
// =====================================================
int iniciarSesion(){
    string correo, contrasena;
    cout << "\n========== INICIAR SESIÓN =========\n";
    cout << "Correo electrónico: ";
    cin >> correo;
    cout << "Contraseña: ";
    cin >> contrasena;

    for (int i = 0; i < usuarios.size(); i++) {
        if (usuarios[i].correoElectronico == correo && usuarios[i].contrasena == contrasena) {
            cout << "\n¡Bienvenido " << usuarios[i].nombre << "!\n";
            return i;
        }
    }
    
    cout << "\n Usuario inválido. Correo o contraseña incorrectos.\n";
    return -1;
}

// =====================================================
// FUNCIÓN: listarProductosBajoStock()
// =====================================================
void listarProductosBajoStock() {
    cout << "\n========== PRODUCTOS CON STOCK BAJO (<15) ==========\n";
    
    bool encontrado = false;
    for (int i = 0; i < productos.size(); i++) {
        if (productos[i].stock < 15) {
            cout << "\nID: " << productos[i].idProducto << endl;
            cout << "Nombre: " << productos[i].nombre << endl;
            cout << "Descripción: " << productos[i].descripcion << endl;
            cout << "Precio: $" << productos[i].precio << endl;
            cout << "Stock: " << productos[i].stock << " unidades " << endl;
            cout << "----------------------------------------\n";
            encontrado = true;
        }
    }
    
    if (!encontrado) {
        cout << "No hay productos con stock bajo.\n";
    }
}

// =====================================================
// FUNCIÓN: convertirFecha()
// =====================================================
int convertirFecha(string fecha) {
    int dia, mes, anio;
    
    size_t pos1 = fecha.find('/');
    size_t pos2 = fecha.find('/', pos1 + 1);
    
    if (pos1 == string::npos || pos2 == string::npos) {
        pos1 = fecha.find('-');
        pos2 = fecha.find('-', pos1 + 1);
    }
    
    dia = atoi(fecha.substr(0, pos1).c_str());
    mes = atoi(fecha.substr(pos1 + 1, pos2 - pos1 - 1).c_str());
    anio = atoi(fecha.substr(pos2 + 1).c_str());
    
    return anio * 10000 + mes * 100 + dia;
}

// =====================================================
// FUNCIÓN: listarComentariosDesdeFecha()
// =====================================================
void listarComentariosDesdeFecha() {
    string fechaBusqueda;
    
    cout << "\n========== COMENTARIOS DESDE UNA FECHA ==========\n";
    cout << "Ingrese la fecha (formato YYYY-MM-DD o DD/MM/YYYY): ";
    cin >> fechaBusqueda;
    
    int fechaComparar = convertirFecha(fechaBusqueda);
    bool encontrado = false;
    
    cout << "\nComentarios desde " << fechaBusqueda << ":\n";
    
    for (int i = 0; i < comentarios.size(); i++) {
        int fechaComentario = convertirFecha(comentarios[i].fecha);
        
        if (fechaComentario >= fechaComparar) {
            cout << "\n--- Comentario #" << comentarios[i].idComentario << " ---\n";
            cout << "Usuario: " << comentarios[i].nombreUsuario << endl;
            cout << "Producto: " << comentarios[i].nombreProducto << endl;
            cout << "Comentario: " << comentarios[i].comentario << endl;
            cout << "Fecha: " << comentarios[i].fecha << endl;
            encontrado = true;
        }
    }
    
    if (!encontrado) {
        cout << "\nNo hay comentarios desde esa fecha.\n";
    }
}

// =====================================================
// FUNCIÓN: convertirAMayusculas()
// =====================================================
string convertirAMayusculas(string texto) {
    for (int i = 0; i < texto.length(); i++) {
        texto[i] = toupper(texto[i]);
    }
    return texto;
}

// =====================================================
// FUNCIÓN: listarUsuarios()
// =====================================================
void listarUsuarios() {
    cout << "\n========== LISTA DE USUARIOS ==========\n";
    
    for (int i = 0; i < usuarios.size(); i++) {
        cout << "\nID: " << usuarios[i].idUsuario << endl;
        cout << "Nombre: " << convertirAMayusculas(usuarios[i].nombre) << endl;
        cout << "Correo: " << usuarios[i].correoElectronico << endl;
        cout << "Dirección: " << usuarios[i].direccion << endl;
        cout << "Método de Pago: " << usuarios[i].metodoDePago << endl;
        cout << "----------------------------------------\n";
    }
}

// =====================================================
// FUNCIÓN: obtenerUltimoIdCarrito()
// =====================================================
int obtenerUltimoIdCarrito() {
    if (carritos.empty()) {
        return 1;
    }
    
    int maxId = 0;
    for (int i = 0; i < carritos.size(); i++) {
        if (carritos[i].idCarrito > maxId) {
            maxId = carritos[i].idCarrito;
        }
    }
    return maxId + 1;
}

// =====================================================
// FUNCIÓN: buscarProductoPorId()
// =====================================================
int buscarProductoPorId(int idProducto) {
    for (int i = 0; i < productos.size(); i++) {
        if (productos[i].idProducto == idProducto) {
            return i;
        }
    }
    return -1;
}

// =====================================================
// FUNCIÓN: adicionarProductosCarrito() - MODIFICADA
// Ahora guarda los cambios de stock en el archivo
// =====================================================
void adicionarProductosCarrito(int indiceUsuario) {
    int nuevoIdCarrito = obtenerUltimoIdCarrito();
    CarritoDeCompras nuevoCarrito;
    nuevoCarrito.idCarrito = nuevoIdCarrito;
    nuevoCarrito.nombreUsuario = usuarios[indiceUsuario].nombre;
    nuevoCarrito.subtotal = 0;
    nuevoCarrito.impuestos = 0;
    
    char continuar = 's';
    
    cout << "\n========== ADICIONAR PRODUCTOS AL CARRITO ==========\n";
    
    while (continuar == 's' || continuar == 'S') {
        cout << "\n--- PRODUCTOS DISPONIBLES ---\n";
        for (int i = 0; i < productos.size(); i++) {
            if (productos[i].stock > 0) {
                cout << "ID: " << productos[i].idProducto 
                     << " | " << productos[i].nombre 
                     << " | Precio: $" << productos[i].precio 
                     << " | Stock: " << productos[i].stock << endl;
            }
        }
        
        int idProducto, cantidad;
        cout << "\nIngrese el ID del producto: ";
        cin >> idProducto;
        
        int indiceProducto = buscarProductoPorId(idProducto);
        
        if (indiceProducto == -1) {
            cout << "Producto no encontrado.\n";
        } else {
            cout << "Ingrese la cantidad: ";
            cin >> cantidad;
            
            if (cantidad > productos[indiceProducto].stock) {
                cout << "Stock insuficiente. Solo hay " 
                     << productos[indiceProducto].stock << " unidades.\n";
            } else if (cantidad <= 0) {
                cout << "Cantidad inválida.\n";
            } else {
                for (int i = 0; i < cantidad; i++) {
                    nuevoCarrito.productosIds.push_back(idProducto);
                    nuevoCarrito.subtotal += productos[indiceProducto].precio;
                }
                
                productos[indiceProducto].stock -= cantidad;
                nuevoCarrito.impuestos = nuevoCarrito.subtotal * 0.19;
                
                cout << " " << cantidad << " unidad(es) de " 
                     << productos[indiceProducto].nombre 
                     << " agregado(s) al carrito.\n";
                cout << "Stock restante: " << productos[indiceProducto].stock << endl;
            }
        }
        
        cout << "\n¿Desea agregar otro producto? (s/n): ";
        cin >> continuar;
    }
    
    if (!nuevoCarrito.productosIds.empty()) {
        carritos.push_back(nuevoCarrito);
        
        // GUARDAR cambios de stock en archivo
        if (guardarProductos()) {
            cout << "\n Stock actualizado en archivo.\n";
        }
        
        cout << "\nCarrito creado exitosamente con ID: " << nuevoCarrito.idCarrito << endl;
        cout << "Subtotal: $" << nuevoCarrito.subtotal << endl;
        cout << "Impuestos (19%): $" << nuevoCarrito.impuestos << endl;
        cout << "Total: $" << (nuevoCarrito.subtotal + nuevoCarrito.impuestos) << endl;
    } else {
        cout << "\n No se agregaron productos al carrito.\n";
    }
}

// =====================================================
// FUNCIÓN: listarProductosCarrito()
// =====================================================
void listarProductosCarrito(int indiceUsuario) {
    cout << "\n========== MIS CARRITOS DE COMPRAS ==========\n";
    
    bool encontrado = false;
    
    for (int i = 0; i < carritos.size(); i++) {
        if (carritos[i].nombreUsuario == usuarios[indiceUsuario].nombre) {
            encontrado = true;
            cout << "\n--- Carrito ID: " << carritos[i].idCarrito << " ---\n";
            cout << "Usuario: " << carritos[i].nombreUsuario << endl;
            cout << "\nProductos en el carrito:\n";
            
            vector<int> productosUnicos;
            vector<int> cantidades;
            
            for (int j = 0; j < carritos[i].productosIds.size(); j++) {
                int idProd = carritos[i].productosIds[j];
                bool encontradoUnico = false;
                
                for (int k = 0; k < productosUnicos.size(); k++) {
                    if (productosUnicos[k] == idProd) {
                        cantidades[k]++;
                        encontradoUnico = true;
                        break;
                    }
                }
                
                if (!encontradoUnico) {
                    productosUnicos.push_back(idProd);
                    cantidades.push_back(1);
                }
            }
            
            for (int j = 0; j < productosUnicos.size(); j++) {
                int indiceProducto = buscarProductoPorId(productosUnicos[j]);
                if (indiceProducto != -1) {
                    cout << "  - " << productos[indiceProducto].nombre 
                         << " x" << cantidades[j]
                         << " | Precio unitario: $" << productos[indiceProducto].precio
                         << " | Subtotal: $" << (productos[indiceProducto].precio * cantidades[j])
                         << endl;
                }
            }
            
            cout << "\nSubtotal: $" << carritos[i].subtotal << endl;
            cout << "Impuestos (19%): $" << carritos[i].impuestos << endl;
            cout << "Total: $" << (carritos[i].subtotal + carritos[i].impuestos) << endl;
            cout << "========================================\n";
        }
    }
    
    if (!encontrado) {
        cout << "\n No tienes carritos de compras.\n";
    }
}

void listarProductosmenor(){
cout << "\n===== REPORTE: 5 PRODUCTOS CON MENOR STOCK =====\n";

    if (productos.empty()) {
        cout << "No hay productos cargados.\n";
        return;
    }

    vector<Producto> copia = productos;

    for (int i = 0; i < copia.size() - 1; i++) {
        for (int j = 0; j < copia.size() - i - 1; j++) {
            if (copia[j].stock > copia[j + 1].stock) {
                Producto aux = copia[j];
                copia[j] = copia[j + 1];
                copia[j + 1] = aux;
            }
        }
    }

    cout << "\nID\tNombre\t\tStock\n";
    cout << "-----------------------------------\n";

    int limite = min(5, (int)copia.size());
    for (int i = 0; i < limite; i++) {
        cout << copia[i].idProducto << "\t"
             << copia[i].nombre << "\t\t"
             << copia[i].stock << endl;
    }
}

void reporteComentariosPorFecha(){
	 cout << "\n===== REPORTE: CANTIDAD DE COMENTARIOS EN UNA FECHA =====\n";

    string fechaBuscada;
    cout << "Ingrese la fecha (YYYY-MM-DD): ";
    cin >> fechaBuscada;

    int contador = 0;

    for (int i = 0; i < comentarios.size(); i++) {
        if (comentarios[i].fecha == fechaBuscada) {
            contador++;
        }
    }

    cout << "\nFecha: " << fechaBuscada << endl;
    cout << "Cantidad de comentarios: " << contador << endl;
}

void reportePrecioMaxMin(){
    cout << "\n===== REPORTE: PRECIO MÁXIMO Y MÍNIMO =====\n";

    if (productos.empty()) {
        cout << "No hay productos cargados.\n";
        return;
    }

    double precioMin = productos[0].precio;
    double precioMax = productos[0].precio;
    string nombreMin, nombreMax;

    for (int i = 0; i < productos.size(); i++) {
        if (productos[i].precio < precioMin) {
            precioMin = productos[i].precio;
            nombreMin = productos[i].nombre;
        }
        if (productos[i].precio > precioMax) {
            precioMax = productos[i].precio;
            nombreMax = productos[i].nombre;
        }
    }

    cout << "\nProducto más barato: " << nombreMin << " ($" << precioMin << ")\n";
    cout << "Producto más caro:   " << nombreMax << " ($" << precioMax << ")\n";
}


void menuReportes() {
    int opcion;

    do {
        cout << "\n===== MENÚ DE REPORTES =====\n";
        cout << "1. 5 productos con menor stock\n";
        cout << "2. Cantidad de comentarios en una fecha\n";
        cout << "3. Precio máximo y mínimo\n";
        cout << "0. Volver al menú anterior\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        system("cls");

        switch (opcion) {
            case 1: listarProductosmenor(); break;
            case 2: reporteComentariosPorFecha(); break;
            case 3: reportePrecioMaxMin(); break;
            case 0: break;
            default: cout << "Opción inválida.\n";
        }

        if (opcion != 0) {
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
        }

    } while (opcion != 0);
}


// =====================================================
// FUNCIÓN: mostrarMenu()
// =====================================================
void mostrarMenu(int indiceUsuario) {
    int opcion;
    
    do {
        cout << "\n+----------------------------------------+\n";
        cout << "¦        MENÚ PRINCIPAL                  ¦\n";
        cout << "+----------------------------------------+\n";
        cout << "  Usuario: " << usuarios[indiceUsuario].nombre << endl;
        cout << "----------------------------------------\n";
        cout << "  1. Listar Productos (stock < 15)\n";
        cout << "  2. Comentarios desde una fecha\n";
        cout << "  3. Listar Usuarios\n";
        cout << "  4. Adicionar productos al carrito\n";
        cout << "  5. Listar mis carritos\n";
        cout << "  6. Reportes\n";
        cout << "  0. Cerrar sesión\n";
        cout << "----------------------------------------\n";
        cout << " Seleccione una opción: ";
        cin >> opcion;
        system("cls");
        
        switch(opcion) {
            case 1:
                listarProductosBajoStock();
                break;
            case 2:
                listarComentariosDesdeFecha();
                break;
            case 3:
                listarUsuarios();
                break;
            case 4:
                adicionarProductosCarrito(indiceUsuario);
                break;
            case 5:
                listarProductosCarrito(indiceUsuario);
                break;
            case 6:
            	menuReportes();
            	break;
            case 0:
                cout << "\nCerrando sesión...\n";
                break;
            default:
                cout << "\nOpción inválida. Intente nuevamente.\n";
        }
        
        if (opcion != 0) {
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
        }
        
    } while(opcion != 0);
}


// =====================================================
// FUNCIÓN PRINCIPAL: main()
// =====================================================
int main() {
	
	setlocale(LC_ALL, "Spanish");
	SetConsoleOutputCP(CP_UTF8);
    cout << "\n+----------------------------------------+\n";
    cout << "¦   SISTEMA DE TIENDA ONLINE - PARCIAL II¦\n";
    cout << "+----------------------------------------+\n";
    
    cargarDatos();
    
    if (usuarios.empty() || productos.empty() || comentarios.empty()) {
        cout << "\nERROR FATAL: No se pudieron cargar los datos.\n";
        cout << "El programa se cerrará.\n";
        return 1;
    }
    
    mostrarDatosCargados();
    
    int indiceUsuario = -1;
    char intentarNuevamente;
    
    do {
        indiceUsuario = iniciarSesion();
        
        if (indiceUsuario != -1) {
            mostrarMenu(indiceUsuario);
            intentarNuevamente = 'n';
        } else {
            cout << "\n¿Desea intentar nuevamente? (s/n): ";
            cin >> intentarNuevamente;
        }
        
    } while (intentarNuevamente == 's' || intentarNuevamente == 'S');
    
    cout << "\n+----------------------------------------+\n";
    cout << "¦   Gracias por usar el sistema          ¦\n";
    cout << "+----------------------------------------+\n";
    
    return 0;
}
