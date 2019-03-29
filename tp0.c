/*
 * main.c
 *
 *  Created on: 28 feb. 2019
 *      Author: utnso
 */

#include "tp0.h"

int main(void)
{
	int conexion;



	//las variables de logger y config estan declaradas como globales en el encabezado de este tp0

	iniciar_logger();

	leer_config();

	leer_consola();

	//antes de continuar, tenemos que asegurarnos que el servidor esté corriendo porque lo necesitaremos para lo que sigue.

	//Una vez hecho eso, tenemos que conectarnos a él! Las conexiones se representan mediante enteros por cosas que hablaremos más adelante.
	//Esta parte la vamos a hacer aca en el main por simpleza.

	//Primero vas a tener que levantar los valores IP y PUERTO del archivo de configuracion con esas claves. Adivina a quien se los tenes que asignar :P

	//Hecho esto, vamos a conectarnos! usamos la funcion ya dada para hacerlo, y le asignamos el entero que devuelve a conexion
	 conexion = crear_conexion(ip, puerto);



	//ahora que tenemos la conexion, es hora de empezar a enviar cosas. Primero, el mensaje.
	//Levantá el valor que le corresponde a CLAVE del archivo de configuracion de nuevo.

	//Ahora le podés mandar el mensaje al servidor!
	enviar_mensaje(valor, conexion);

	paquete(conexion);

	terminar_programa(conexion);
}

void iniciar_logger(void)
{

	char * rutaDelArchivo= strdup("/home/utnso/tp0/logger.log");
	g_logger = log_create(rutaDelArchivo,"Logger",1,LOG_LEVEL_INFO);
	//creemos el log! Este se debe crear con el nombre "tp0.log", se debe mostrar por consola y debe estar en el nivel INFO
	//g_logger = log_create(/*nombre del archivo, nombre del programa, 1 para mostrar por consola 0 caso contrario, nivel de log deseado */);

	//logeemos el mensaje "Soy un log"
	log_info(g_logger, "Soy un log");
}

void leer_config()
{

	g_config = config_create("/home/utnso/tp0/tp0.config");
	//ahora, vamos a abrir el archivo de configuracion "tp0.config"
	//g_config = config_create(/*path*/);
	valor= strdup(config_get_string_value(g_config,"CLAVE"));
	//tenemos que levantar en valor asociado a la clave "CLAVE" del archivo y asignarselo a la variable valor
	//config_get_string_value(/*config, clave*/);
	log_info(g_logger,valor);
	ip = strdup(config_get_string_value(g_config,"IP"));
	log_info(g_logger,ip);
	puerto =strdup( config_get_string_value(g_config,"PUERTO"));
	log_info(g_logger,puerto);
	//Por último, logeame ese valor :)
}

void leer_consola(void)
{
	char* leido= malloc(sizeof(char*));

	//El primero te lo dejo de yapa
	leido = readline(">");

	//Los siguiente 4 pasos vas a tener que meterlos en algun tipo de bucle. Te tiro una pista, no es con for ;)

	//Voy a dejar esto por aca porque quizas complemente al enunciado: http://faq.utnso.com/punteros


	while(strcmp(leido, "\0")){

		//Primero, logeame lo leido
		log_info(g_logger,leido);
		//ahora que ya usamos el string, liberamelo con free
		free(leido);
		//free NO asigna el valor NULL a los punteros que libera, pero es buena practica asignarselo a tenerlo apuntando a basura
		leido= malloc(sizeof(char*));
		leido = readline("");

	}
	//volvemos a poner el readline para poder seguir loggeando.
}

void paquete(int conexion)
{
	//Ahora toca lo divertido!

	char* leido;
	t_paquete* paquete = crear_paquete();

	//De nuevo vas a tener que usar readline hasta que te llegue un nulo igual que antes, solo que ahora en lugar de logear, vas a agregar esa cadena al paquete!
	//Recomiendo revisar bien el enunciado del TP ya que ahi está explicado con detalles

	leido=readline("");
	while(strcmp(leido,"\0")){

		log_info(g_logger,leido);
		agregar_a_paquete(paquete,leido,sizeof(leido));
		free(leido);
		leido= malloc(sizeof(char*));
		leido = readline("");

	}

	//agregar_a_paquete(/*paquete, mensaje, tamanio*/);

	//Una vez hayamos terminado de ingresar valores, toca enviarlo
	enviar_paquete(paquete, conexion);
	eliminar_paquete(paquete);
	//Y no nos olvidemos de borrar el paquete con eliminar_paquete
}

void terminar_programa(int conexion)
{

	log_destroy(g_logger);
	config_destroy(g_config);
	eliminar_conexion(conexion);
	//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado
}


char* ingresarDatos () {

	char* leido= malloc(sizeof(char*));

	leido=readline("");
	while(strcmp(leido,"\0")){

		log_info(g_logger,leido);



	}


}


