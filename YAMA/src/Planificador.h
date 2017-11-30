/*
 * Planificador.h
 *
 *  Created on: 20/10/2017
 *      Author: utnso
 */

#ifndef PLANIFICADOR_H_
#define PLANIFICADOR_H_

#include "YAMA.h"
#include <utilidades/protocol/types.h>
#include <utilidades/protocol/senders.h>
#include <utilidades/socket_utils.h>

t_dictionary* diccionarioJobNodos; //JOB ID - Lista nodos para ese JOB

// FUNCIONES DE PLANIFICADOR
void iniciarPlanificacion(char* nombreArchivo, t_job_master* job_master);
void responderSolicitudMaster(payload_RESPUESTA_MASTER* infoMaster, t_job_master* job_master);
void inicializarPlanificador(t_job_master* job_master, char* nombreArchivo);
void finalizarCorrectamente(t_job* job);
void abortarJob(t_job* job);
t_list* cargarNodosParaPlanificacion(char* nombreArchivo, int jobID);
t_worker* elegirEncargadoRedGlobal(int jobID);
void realizarReduccionGlobal(t_job_master* job_master);
void realizarTransformacion(t_job_master* job_master);
void realizarReduccionLocal(t_worker* nodo, t_job_master* job_master);
void replanificar(t_job_master* job_master, t_worker* nodoFallido);

//FUNCIONES DE JOB
t_job *newJob();

// UTILES

char* castearTarea(Tarea tarea);
char* castearEstado(YAMA_STATUS estado);
Tarea etapaActiva(t_worker* nodo);
char* getArchivoTemporal(payload_RESPUESTA_MASTER* infoMaster);
char* getNombreArchivoTemporalRedLocal(int jobID, int nodoID);
char* getNombreArchivoTemporalTransformacion(int jobID, int bloque, int nodoID);
char* getNombreArchivoTemporalRedGlobal(int jobID, int masterID);
int registroTerminoExitosamente(t_tablaEstados* registroEstado);
t_infoBloque* buscarInfoBloque(t_list* bloques, int bloqueArchivo);

// FUNCIONES DE NODO
t_list* getNodosDeJob(int jobID);
void agregarListaNodosAJob(t_list* listaNodos, int jobID);
int todosLosNodosTerminaronReduccionLocal(int jobID);
int nodoTerminoTransformacion(int idJob, int jobID);
void nodoPasarAEtapa(t_worker* nodo, Tarea etapa);
t_worker* getNodo(int nodoID, int jobID);
int estaActivo(t_worker* worker);
void aumentarCarga(t_worker* nodo);
void disminuirCarga(t_worker* nodo);

// ACTUALIZACIONES
void actualizarEstados(payload_RESPUESTA_MASTER* respuesta, t_job_master* job_master);
void actualizarTablaEstados(payload_RESPUESTA_MASTER* respuesta, t_job_master* job_master);
t_tablaEstados* getRegistro(payload_RESPUESTA_MASTER* infoMaster, int jobID);
void actualizarLog(payload_RESPUESTA_MASTER* infoMaster);
void actualizarTablaEstadosConTransformacion(t_job_master* job_master, t_worker* nodo, int bloque, char* nombreArchivoTemporal);
void actualizarTablaEstadosConReduccion(t_job_master* job_master, t_worker* nodo, char* nombreArchivoTemporal, Tarea etapa);

//FUNCIONES DE PLANIFICACION
void planificacionWClock(t_job_master* job_master);
int existeEn(t_list* lista , int bloqueArchivo);
int obtenerDisponibilidadNodo(t_worker* worker);
int PWL(t_worker* worker, int jobID);
int WLmax(int jobID);
int carga(t_worker* worker);
void ordenarListaNodosPorDisponibilidad(t_list* listaNodos);
void calcularDisponibilidad(t_worker* worker, int jobID);
int disponibilidad(t_worker* worker);
int tareasHistoricas(t_worker* worker);
void aumentarTareasHistoricas(t_worker* worker);

#endif /* PLANIFICADOR_H_ */
