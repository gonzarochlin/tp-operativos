/*
 ============================================================================
 Name        : YAMA.c
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

#include "serverYAMA/responses/responses.h"
#include "serverYAMA/serverYAMA.h"
#include "Job.h"

typedef struct {

	char *nombre;
	char *ip;
	char *puerto;
	int carga;
	t_list bloque;

} t_nodo;

typedef struct {
	t_job job;
	int master;
	t_nodo nodo;
	int bloque;
	char* etapa;
	char* archivoTemporal;
	YAMA_STATUS estado;
} t_tablaEstados;



int id = 1;
int puertoFs = 0;
char* ipFs = "";
int puertoYAMA = 0;
int retardoPlanificacion = 0;
char* algoritmoBalanceo = "";

t_log* logs;

void leerConfiguracion(){
	char* path = "/home/utnso/workspace/tp-2017-2c-Grupo-1---K3525/YAMA/src/yama-config.cfg";
	t_config* archivo_configuracion = config_create(path);
	puertoFs = config_get_int_value(archivo_configuracion, "FS_PUERTO");
	printf("El puerto FS es: %i \n", puertoFs);
	ipFs = config_get_string_value(archivo_configuracion, "FS_IP");
	printf("La IP FS es: %s \n", ipFs);
	retardoPlanificacion = config_get_int_value(archivo_configuracion, "RETARDO_PLANIFICACION");
	printf("El retardo de la Planificacion es: %i \n", retardoPlanificacion);
	algoritmoBalanceo = config_get_string_value(archivo_configuracion, "ALGORITMO_BALANCEO");
	printf("El Algoritmo de Balanceo es: %s \n", algoritmoBalanceo);
	puertoYAMA = config_get_int_value(archivo_configuracion, "YAMA_PUERTO");
	printf("YAMA se conectara en el puerto: %d \n", puertoYAMA);

	config_destroy(archivo_configuracion);
}

int main(void) {
	puts("Comienza el proceso YAMA");

	logs = log_create("yama.log", "YAMA", false, LOG_LEVEL_TRACE);

	log_trace(logs, "Leyendo configuracion");
	leerConfiguracion();
	log_trace(logs, "Configuracion leida");

	//cliente(ipFs, puertoFs, id);
	init_serverMaster(puertoYAMA);

	return EXIT_SUCCESS;
}


