/*
 ============================================================================
 Name        : DataNode.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <utilidades/Sockets.c>
#include <stdio.h>
#include <stdlib.h>
#include <commons/log.h>
#include <commons/config.h>
//
int puertoFs = 0;
int id = 1;
char* ipFs = "";
t_log* log;

void leerConfiguracion(){
	char* path = "/home/utnso/workspace/tp-2017-2c-Grupo-1---K3525/DataNode/src/nodo-config.cfg";
	t_config* archivo_configuracion = config_create(path);
	puertoFs = config_get_int_value(archivo_configuracion, "PUERTO_FILESYSTEM");
	printf("El puerto FS es: %i \n", puertoFs);
	ipFs = config_get_string_value(archivo_configuracion, "IP_FILESYSTEM");
	printf("La IP FS es: %s \n", ipFs);

	config_destroy(archivo_configuracion);
}

int main(void) {
	puts("Comienza DataNode");
	///Se crea el log
	log = log_create("dataNode.log", "DataNode", false, LOG_LEVEL_TRACE);
	log_trace(log, "Leyendo configuracion");
	leerConfiguracion();
	log_trace(log, "Configuracion leida");

	//cliente(ipFs, puertoFs, id);
	escribirArchivo("metadata/archivo.txt", "polenta", 3);
	return EXIT_SUCCESS;
}

void escribirArchivo(char* path, char* data, int offset){
	FILE* archivo;
	if (!(archivo = fopen(path, "r"))){
		log_error(log, "El archivo no existe o no se pudo abrir");
	}else{
		archivo = fopen(path,"rb+");
		fseek(archivo, offset, SEEK_SET);
		fwrite(data, strlen(data), 1, archivo);
		fclose(archivo);
		puts("Escritura Completa");
	}

}
