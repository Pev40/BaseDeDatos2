#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <algorithm>
#include <cctype>
#include "Megatron.h"
#include "Esquema.h"
using namespace std;
void importarEsquema(std::string nombreArchivo,Esquema& ReferenciaEsquema ){
    std::map<std::string, std::map<std::string, std::string>> map1;

    // Abrir el archivo de texto para leer
    std::ifstream archivo(nombreArchivo);
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo" << std::endl;
        return ;
    }

    // Leer cada línea del archivo
    std::string linea;
    while (std::getline(archivo, linea)) {
        // Crear un flujo de cadena a partir de la línea leída
        std::stringstream ss(linea);

        // Leer la clave exterior del mapa
        std::string clave_exterior;
        if (!std::getline(ss, clave_exterior, '#')) {
            std::cerr << "Error al leer la clave exterior" << std::endl;
            return;
        }
        clave_exterior.erase(remove_if(clave_exterior.begin(), clave_exterior.end(), ::isspace), clave_exterior.end());
        // Crear un mapa interior para la clave exterior actual
        std::map<std::string, std::string> mapa_interior;

        // Leer cada par clave-valor del mapa interior
        std::string clave, valor;
        while (std::getline(ss, clave, '#') && std::getline(ss, valor, '#')) {
            // Eliminar espacios en blanco de cada palabra
            clave.erase(remove_if(clave.begin(), clave.end(), ::isspace), clave.end());
            valor.erase(remove_if(valor.begin(), valor.end(), ::isspace), valor.end());

            // Agregar el par clave-valor al mapa interior
            mapa_interior[clave] = valor;
        }

        // Agregar el mapa interior al mapa exterior
        map1[clave_exterior] = mapa_interior;
    }

    // Mostrar el mapa de mapas leído
    Esquema schema = Esquema();
    for (auto const& exterior : map1) {
        ReferenciaEsquema.addTable(exterior.first);
        for (auto const& interior : exterior.second) {
            ReferenciaEsquema.addAtributo(exterior.first,interior.first,interior.second);
        }
    }
    std::cout<<"Importado"<<std::endl;
    // Cerrar el archivo
    archivo.close();
    
    //ReferenciaEsquema = schema;
    return ;
}

int main(){

/*
    Esquema schema = Esquema();
    string nombresTablas[] = {"students","depts"};
    string atributos1[] = {"name","str" ,"id","int" ,"dept","str"};
    string atributos2[] = {"name","str" ,"office","int"};
    schema.addTable(nombresTablas[0]);
    //cout<<""<<atributos[0]<<atributos1[1]<<endl;
    for (int i = 0; i < (sizeof atributos1/sizeof atributos1[0]); i=i+2)
    {
        schema.addAtributo(nombresTablas[0],atributos1[i],atributos1[i+1]);
    }
    schema.addTable(nombresTablas[1]);
        for (int i = 0; i < (sizeof atributos2/sizeof atributos2[0]); i=i+2)
    {
        schema.addAtributo(nombresTablas[1],atributos2[i],atributos2[i+1]);
    }
    schema.viewSchemas();
    */
    //schema.exportEsquema("esquema");
    //Esquema schema2 = Esquema();
    //importarEsquema("esquem.txt",schema2);
    //schema2.exportEsquema("esquema");
    Megatron dbms = Megatron();
    dbms.importarEsquema("esquema.txt");
    //dbms.start().viewSchemas();
    //cout<<dbms.start().search("students");
    std::vector<std::string> data1 = {"Piero","200","CS"};
    dbms.insertRegistro("students",data1);

    std::vector<std::string> data2 = {"CS","Pabellon Alan Turing"};
    dbms.insertRegistro("depts",data2);

    return 0;
}
