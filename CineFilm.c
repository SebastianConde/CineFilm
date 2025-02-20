/* 
   Este proyecto es un cine de la ciudad de Pereira llamado CineFilm el cúal brinda 
   el servicio de venta de boletas para las funciones.
*/

//BIBLIOTECAS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <cstdlib>
#include <windows.h>
#include <ctype.h>
#include <conio.h>
#include<sys/stat.h>


//Estructura inicial
typedef struct{ 
  char codigo[11];
  char nombre[30];
  char apellido[30];
  char silla[4]; //las sillas serán ejemplo: A0,A1...K20; son 11 columnas (A-K) y 20 filas
}boletas;

//Variables globales:
int filas = 20; //hace parte de la funcion mostrar sillas
int columnas = 11; //hace parte de la función mostrar sillas
int sala_de_cine [21][12]; //hace parte de la función mostrar sillas
int MAXIMO; //número de registros o boletas a comprar (fundamental para la memoria dinámica)
boletas *vector; //vector que permite guardar cada registro en una de sus posiciones
int i; //Hace funcionar cada bucle dentro de las mismas funciones
int MAXIMO_1=0; //Guarda el número de registros ingresados anteriormente para luego adicionarlos al vector.
int *vector3; //Vector que contiene los códigos ordenados
int selector=0;
int total;
int NUM_ACTUALIZACIONES = 0;
FILE *boletas_comprar;


//Prototipos de Funciones:
void consulta_precios();
void leer_datos(char *, char *, char *, char *);
void proceso_leer();
void mostrar_datos (char *, char *, char *, char *);
void mostrar_sala_de_cine();
void proceso_sala_de_cine();
void sillas_ocupadas();
void proceso_mostrar();
void verifica_silla_ocupada(char *, char *);
void busqueda();
void proceso_busqueda();
void ordenamiento();
void borrar();
void borrar(char *);
void proceso_ordenamiento();
void proceso_modificar();
void modificar_registro();
void proceso_borrar();
void borrar();
void gotoxy(int, int);
void contacto();
void proceso_recibo();
void recibo();
void recibo2();


//Función Principal:
int main() {
  setlocale(LC_ALL, "spanish");
  system("mode con: cols=80 lines=50");
  system("color 04");
  system("title Proyecto Final Programación II");
  
  //Menú:
  int selector;
  	gotoxy(35, 10);printf("                                                                                        \n");
	gotoxy(35, 12);printf("         *******************************************************************************\n");
	gotoxy(35, 14);printf("         *                                                                             *\n");
	gotoxy(35, 16);printf("         *           ******* ** **    ** *****  ****** ** **    **    **               *\n");
	gotoxy(35, 18);printf("         *           **      ** ***   ** **     **     ** **    ***  ***               *\n");
	gotoxy(35, 20);printf("         *           **      ** ** *  ** *****  ****** ** **    ** ** **               *\n");
	gotoxy(35, 22);printf("         *           **      ** **  * ** **     **     ** **    **    **               *\n");
	gotoxy(35, 24);printf("         *           ******* ** **   *** *****  **     ** ***** **    **               *\n");
	gotoxy(35, 26);printf("         *                                                                             *\n");
	gotoxy(35, 28);printf("         *******************************************************************************\n");
	gotoxy(35, 30);printf("                                                                                        \n");
	gotoxy(35, 32);printf("                                                                                        \n");
	gotoxy(35, 34);printf("                                                                                        \n");
	gotoxy(35, 36);printf("                                     BIENVENIDO SEÑOR USUARIO                               \n");
	gotoxy(35, 38);printf("                                Presiona Una Tecla Para Continuar...");
	
   int  opc, ok=0;
	while(opc<=10)
	{
		getchar();
		system ("cls");
		system("color 0D");
		gotoxy(35, 2);	printf("     *********************************************************************************************\n");
		gotoxy(35, 4);  printf("     *                                                                                           *\n");
		gotoxy(35, 6);	printf("     *                                MENÚ PRINCIPAL DE CINEFILM                                 *\n");
		gotoxy(35, 8);	printf("     *                                                                                           *\n");
		gotoxy(35, 10);	printf("     *                                                                                           *\n");
		gotoxy(35, 12);	printf("     *                           (1) - Registrar boletos (Leer datos)                            *\n");
		gotoxy(35, 14);	printf("     *                           (2) Consulta Los Precios De Boleteria                           *\n");
		gotoxy(35, 16);	printf("     *                         (3) - Confirmar Datos Boleta (mostrar datos)                      *\n");
		gotoxy(35, 18);	printf("     *                        (4) - Mostrar sillas ocupadas (Ordenar datos)                      *\n");
		gotoxy(35, 20);	printf("     *                       (5) - Ordenar Registros De Boletas (Ordenar datos)                  *\n");
		gotoxy(35, 22);	printf("     *                             (6) - Buscar Registros (Buscar datos)                         *\n");
		gotoxy(35, 24);	printf("     *                    (7) - Actualizar datos para alguna boleta (Actualizar datos)           *\n");
		gotoxy(35, 26);	printf("     *                      (8) - Cancelar la compra de alguna boleta (Borrar datos)             *\n");
		gotoxy(35, 28);	printf("     *                                     (9) - Contactanos                                     *\n");
		gotoxy(35, 30);	printf("     *                           (10) - Descargar recibo o restablecer datos                     *\n");
		gotoxy(35, 32);	printf("     *                                       (0) - Salir                                         *\n");
		gotoxy(35, 34);	printf("     *                                                                                           *\n");
		gotoxy(35, 36);	printf("     *********************************************************************************************\n");
		gotoxy(35, 38);	printf("                                                                                                  \n");
		gotoxy(35, 40);	printf("                                 Ingrese la opcion que desea ejecutar: ");
		
		MAXIMO_1=MAXIMO;
		
  		//Número de registros y memoria dinamica:
        if(MAXIMO==NULL){
        vector = (boletas *)malloc((MAXIMO)*sizeof(boletas));
        }
		   	do
			scanf("%d", &opc);
			while(opc<0 || opc>10);
			//Switch de opc( Ejecuta el menú)
			switch(opc)
			{	
				// Caso 0: Salir Del menú
				case 0: opc=11;
				    printf("\n\t\t\t\t\t\t\t\t   Has abandonado el menú, ¡Hasta la proxima!");
			        break;
				 
				// Caso 1: Ingresar datos para comprar boletas
				case 1: 
				if(MAXIMO==NULL){
					system("cls");
					system("color 0B");
					gotoxy(35, 5);	printf("     *********************************************************************************************\n");
					gotoxy(35, 6);  printf("     *                                                                                           *\n");
					gotoxy(35, 7);	printf("     *                                                                                           *\n");
					gotoxy(35, 8);	printf("     *                                                                                           *\n");
					gotoxy(35, 9);  printf("     *                                      REGISTRO DE BOLETAS(1)                               *\n");
					gotoxy(35, 10); printf("     *                                                                                           *\n");
					gotoxy(35, 11); printf("     *                                                                                           *\n");
					gotoxy(35, 12); printf("     *                                                                                           *\n");
	 				gotoxy(35, 13); printf("     *                                                                                           *\n");
					gotoxy(35, 14); printf("     *********************************************************************************************\n");
					gotoxy(35, 15); printf("                                                                                                  \n");
     				gotoxy(35, 16); printf("                                    INGRESE EL NUMERO DE REGISTROS: ");
        			scanf("%d",&MAXIMO);
           			}else{
          				 char opcion2[1];
          				 system("cls");
          				 system("color 04");
          				 gotoxy(35, 5);	 printf("     *********************************************************************************************\n");
						 gotoxy(35, 6);  printf("     *                                                                                           *\n");
						 gotoxy(35, 7);	 printf("     *                                                                                           *\n");
						 gotoxy(35, 8);	 printf("     *                                                                                           *\n");
						 gotoxy(35, 9);  printf("     *                                      REGISTRO DE BOLETAS NUEVAS(1)                        *\n");
						 gotoxy(35, 10); printf("     *                                                                                           *\n");
						 gotoxy(35, 11); printf("     *                                                                                           *\n");
						 gotoxy(35, 12); printf("     *                                                                                           *\n");
	 					 gotoxy(35, 13); printf("     *                                                                                           *\n");
					   	 gotoxy(35, 14); printf("     *********************************************************************************************\n");
						 gotoxy(35, 15); printf("                                                                                                  \n");
          				 printf("\t\t\t\t\t\t\t\t\t¿Desea Agregar Más Registros? s/n ");
           				 scanf("%s",opcion2);
          				 printf("\n");
          				 if((strcmp(opcion2,"s"))==0){
           				 printf("\t\t\t\t\t\t\t\t\t\t\t¿Cuántos? ");
           			     scanf("%d",&MAXIMO);
          				 }else{
          				 	main();
						   }
           			}
         			MAXIMO=MAXIMO+MAXIMO_1;
					proceso_leer();  
     				 break;
				
				// Caso 2: Consultar Precios Boleteria	
				case 2:
					consulta_precios();
					break;
				
				// Caso 3: Confirmar Datos Ingresados
				case 3:
					system("cls");
					system("color 01");
					gotoxy(35, 5);	printf("     *********************************************************************************************\n");
					gotoxy(35, 6);  printf("     *                                                                                           *\n");
					gotoxy(35, 7);	printf("     *                                                                                           *\n");
					gotoxy(35, 8);	printf("     *                                                                                           *\n");
					gotoxy(35, 9);  printf("     *                                  CONFIRMAR DATOS DE BOLETAS(3)                            *\n");
					gotoxy(35, 10); printf("     *                                                                                           *\n");
					gotoxy(35, 11); printf("     *                                                                                           *\n");
					gotoxy(35, 12); printf("     *                                                                                           *\n");
	 				gotoxy(35, 13); printf("     *                                                                                           *\n");
					gotoxy(35, 14); printf("     *********************************************************************************************\n");
					gotoxy(35, 15); printf("                                                                                                  \n");
				 	proceso_mostrar();
				 break;
				 
    			//Caso 4: Mostrar sillas ocupadas
    			case 4:
        		 system("cls");
        		 system("color 03");
					gotoxy(35, 5);	printf("     *********************************************************************************************\n");
					gotoxy(35, 6);  printf("     *                                                                                           *\n");
					gotoxy(35, 7);	printf("     *                                                                                           *\n");
					gotoxy(35, 8);	printf("     *                                                                                           *\n");
					gotoxy(35, 9);  printf("     *                                SALA DE CINE-SILLAS OCUPADAS(4)                            *\n");
					gotoxy(35, 10); printf("     *                                                                                           *\n");
					gotoxy(35, 11); printf("     *                                                                                           *\n");
					gotoxy(35, 12); printf("     *                                                                                           *\n");
	 				gotoxy(35, 13); printf("     *                                                                                           *\n");
					gotoxy(35, 14); printf("     *********************************************************************************************\n");
					gotoxy(35, 15); printf("                                                                                                  \n");
				 proceso_sala_de_cine();
     			 break;
     			 
     			//Caso 5: Ordenar Datos de Boleteria (Registros) por el código
     			case 5:
     				system("cls");
        		 	system("color 0C");
					gotoxy(35, 3);	printf("     *********************************************************************************************\n");
					gotoxy(35, 4);  printf("     *                                                                                           *\n");
					gotoxy(35, 5);	printf("     *                                                                                           *\n");
					gotoxy(35, 6);	printf("     *                                                                                           *\n");
					gotoxy(35, 7);  printf("     *                                      REGISTROS ORDENADOS(5)                               *\n");
					gotoxy(35, 8);  printf("     *                                                                                           *\n");
					gotoxy(35, 9);  printf("     *                                                                                           *\n");
					gotoxy(35, 10); printf("     *                                                                                           *\n");
	 				gotoxy(35, 11); printf("     *                                                                                           *\n");
					gotoxy(35, 12); printf("     *********************************************************************************************\n");
					gotoxy(35, 13); printf("                                                                                                  \n");
     				proceso_ordenamiento();
     				break;
    			
    			//Caso 6: Busqueda de un registro luego de haber sido ordenado
    			case 6:
    				system("cls");
					system("color 0A");
					gotoxy(35, 5);	printf("     *********************************************************************************************\n");
					gotoxy(35, 6);  printf("     *                                                                                           *\n");
					gotoxy(35, 7);	printf("     *                                                                                           *\n");
					gotoxy(35, 8);	printf("     *                                                                                           *\n");
					gotoxy(35, 9);  printf("     *                                    BUSQUEDA DE REGISTROS(6)                                *\n");
					gotoxy(35, 10); printf("     *                                                                                           *\n");
					gotoxy(35, 11); printf("     *                                                                                           *\n");
					gotoxy(35, 12); printf("     *                                                                                           *\n");
	 				gotoxy(35, 13); printf("     *                                                                                           *\n");
					gotoxy(35, 14); printf("     *********************************************************************************************\n");
					gotoxy(35, 15); printf("                                                                                                  \n");
    				proceso_busqueda();
    				break;
    				
    			//Caso 7: Actualización Datos De Boletas(Registros)
    			case 7:
    				system("cls");
        		 	system("color 05");
					gotoxy(35, 5);	printf("     *********************************************************************************************\n");
					gotoxy(35, 6);  printf("     *                                                                                           *\n");
					gotoxy(35, 7);	printf("     *                                                                                           *\n");
					gotoxy(35, 8);	printf("     *                                                                                           *\n");
					gotoxy(35, 9);  printf("     *                                  ACTUALIZAR DATOS BOLETERIA(7)                            *\n");
					gotoxy(35, 10); printf("     *                                                                                           *\n");
					gotoxy(35, 11); printf("     *                                                                                           *\n");
					gotoxy(35, 12); printf("     *                                                                                           *\n");
	 				gotoxy(35, 13); printf("     *                                                                                           *\n");
					gotoxy(35, 14); printf("     *********************************************************************************************\n");
					gotoxy(35, 15); printf("                                                                                                  \n");
    			    proceso_modificar();
    			    NUM_ACTUALIZACIONES = NUM_ACTUALIZACIONES+1;
    				break;
    			
    			//Caso 8:Borrar datos(registros)
    			case 8:
    				system("cls");
        		 	system("color 0F");
					gotoxy(35, 5);	printf("     *********************************************************************************************\n");
					gotoxy(35, 6);  printf("     *                                                                                           *\n");
					gotoxy(35, 7);	printf("     *                                                                                           *\n");
					gotoxy(35, 8);	printf("     *                                                                                           *\n");
					gotoxy(35, 9);  printf("     *                                 BORRAR REGISTROS DE BOLETERIA(8)                          *\n");
					gotoxy(35, 10); printf("     *                                                                                           *\n");
					gotoxy(35, 11); printf("     *                                                                                           *\n");
					gotoxy(35, 12); printf("     *                                                                                           *\n");
	 				gotoxy(35, 13); printf("     *                                                                                           *\n");
					gotoxy(35, 14); printf("     *********************************************************************************************\n");
					gotoxy(35, 15); printf("                                                                                                  \n");
    				proceso_borrar();
    				break;
				
				//Caso 9: Acerca De Nosotros
    			case 9:
    				contacto();
    				break;
    				
    			//Caso 10: Uso de archivos
    			case 10:
    				proceso_recibo();
    				break;
    			
    			//Caso Default (Si ningún caso se cumple)
    			default: 
					printf("\tError. Debe ingresar a una opción existente en el menú");
    				break;
    		}
    }  
}


void consulta_precios(){
	
	int k = 0, 	n=1;
	for (k = 0; k < n; k++)
	{
		system("cls");
		system("color 06");
		gotoxy(35, 5);  printf("     *********************************************************************************************\n");
		gotoxy(35, 6);  printf("     *                                                                                           *\n");
		gotoxy(35, 7);  printf("     *                                                                                           *\n");
		gotoxy(35, 8);  printf("     *                                                                                           *\n");
		gotoxy(35, 9);  printf("     *                                       PRECIOS BOLETERIA(2)                                *\n");
		gotoxy(35, 10); printf("     *                                                                                           *\n");
		gotoxy(35, 11); printf("     *                                                                                           *\n");
		gotoxy(35, 12); printf("     *                                                                                           *\n");
	    gotoxy(35, 13); printf("     *                                                                                           *\n");
		gotoxy(35, 14); printf("     *********************************************************************************************\n");
		gotoxy(35, 15); printf("                                                                                                  \n");
		gotoxy(35, 16); printf("                                                                                                  \n");
		gotoxy(35, 17); printf("                                   EL PRECIO PARA LAS FUNCIONES EN 2D SON:                        \n");
		gotoxy(35, 18); printf("                                   (1) NIÑOS MENORES DE 12 AÑOS $4.000                            \n");
		gotoxy(35, 19); printf("                                   (2) NIÑOS ENTRE 13 Y 17 AÑOS $4.500                            \n");
		gotoxy(35, 20); printf("                                       (3) MAYORES DE 18 AÑOS $5.500                              \n");
		gotoxy(35, 21); printf("                                                                                                  \n");
		gotoxy(35, 22); printf("     *********************************************************************************************\n");
		gotoxy(35, 23); printf("                                                                                                  \n");
		gotoxy(35, 24); printf("                                   EL PRECIO PARA LAS FUNCIONES EN 3D SON:                        \n");
		gotoxy(35, 25); printf("                                   (4) NIÑOS MENORES DE 12 AÑOS $6.000                            \n");
		gotoxy(35, 26); printf("                                   (5) NIÑOS ENTRE 13 Y 17 AÑOS $7.500                            \n");
		gotoxy(35, 27); printf("                                       (6) MAYORES DE 18 AÑOS $9.500                              \n");
		gotoxy(35, 28); printf("                                                                                                  \n");
		gotoxy(35, 29); printf("     *********************************************************************************************\n");
		gotoxy(35, 30); printf("                                                                                                  \n");
	}
		if(selector==0){
			printf("\t\t\t\t\t\t\t\tElija el tipo y precio de la(s) boleta(s) que va a comprar: ");
			scanf("%d",&selector);
		}
		switch(selector){
			case 1:
				total=4000*MAXIMO;
				printf("\n\t\t\t\t\t\t\t\tEl total a pagar es($): %d",total);
				gotoxy(38, 35); printf("                                Presiona Enter Para Volver Al Menú Principal...");
		        getchar();
			    break;
			case 2:
				total=4500*MAXIMO;
				printf("\n\t\t\t\t\t\t\t\tEl total a pagar es($): %d",total);
				gotoxy(38, 35); printf("                                Presiona Enter Para Volver Al Menú Principal...");
		        getchar();
				break;
			case 3:
				total=5500*MAXIMO;
				printf("\n\t\t\t\t\t\t\t\tEl total a pagar es($): %d",total);
				gotoxy(38, 35); printf("                                Presiona Enter Para Volver Al Menú Principal...");
		        getchar();
			    break;
			case 4:
				total=6000*MAXIMO;
				printf("\n\t\t\t\t\t\t\t\tEl total a pagar es($): %d",total);
				gotoxy(38, 35); printf("                                Presiona Enter Para Volver Al Menú Principal...");
		        getchar();
			    break;
			case 5:
				total=7500*MAXIMO;
				printf("\n\t\t\t\t\t\t\t\tEl total a pagar es($): %d",total);
				gotoxy(38, 35); printf("                                Presiona Enter Para Volver Al Menú Principal...");
	        	getchar();
			    break;
			case 6:
				total=9500*MAXIMO;
				printf("\n\t\t\t\t\t\t\t\tEl total a pagar es($): %d",total);
				gotoxy(38, 35); printf("                                Presiona Enter Para Volver Al Menú Principal...");
		        getchar();
			    break;	
			default:
				printf("\n\t\t\t\t\t\t\t\tError, opción no especificada...");
				gotoxy(38, 35); printf("                                Presiona Enter Para Volver Al Menú Principal...");
	        	getchar();
				break;
		}
}
	
//Procedimiento para ejecutar la función que lee los datos de la estructura(registros) ingresados por el usuario
void proceso_leer(){
       for(i=MAXIMO_1;i<MAXIMO;i++){
         fflush(stdin);
         printf("\n");
         leer_datos(vector[i].codigo, vector[i].nombre, vector[i].apellido, vector[i].silla);
        }

          printf("\n\t\t\t\t\t*********************************************************************************************\n");
          printf("\n\t\t\t\t\t\t\t\tPresiona Enter Para Volver Al Menú Principal...");
          getchar();
}

//Función Para Verificar Si hay una silla acupada
void verificar_silla_ocupada(char *silla, char *silla1){
    if((strcmp(silla,silla1))==0){
           printf("\n\tERROR DEL PROGRAMA, SE DETECTARON VARIOS REGISTROS CON LA MISMA NÚMERACIÓN DE SILLA, ¡VUELVA A INTENTARLO!");
           exit(-1);
             }
}

//Función para leer y almacenar los datos ingresados por el usuario(registros)
void leer_datos(char *codigo, char *nombre, char *apellido, char *silla){
	
	  printf("\t\t\t\t\t*********************************************************************************************\n");

      printf("\n\t\t\t\t\t\t\tIngrese su número de documento de identidad: ");
      scanf("%s",codigo);

      printf("\t\t\t\t\t\t\tIngrese su primer nombre: ");
      scanf("%s",nombre);

      printf("\t\t\t\t\t\t\tIngrese su apellido: ");
      scanf("%s",apellido);

      printf("\t\t\t\t\t\t\tIngrese el número de la silla que quiere: ");
      scanf("%s",silla);
      

  }

//Funcion para mostrar los datos de la estructura(registros) ingresados por el usuario
void mostrar_datos (char *codigo, char *nombre, char *apellido, char *silla){
  printf("\t\t\t\t\t\t\t\tNombre: "); printf("%s",nombre); printf("\n");
  printf("\t\t\t\t\t\t\t\tApellido: "); printf("%s",apellido);printf("\n");
  printf("\t\t\t\t\t\t\t\tDocumento de identidad: "); printf("%s",codigo);printf("\n");
  printf ("\t\t\t\t\t\t\t\tNumero de silla: "); printf("%s",silla);
  printf("\n\n");
  
}

//Función para mostrar la sala de cine con todas las sillas disponibles
void mostrar_sala_de_cine(){
 if(NUM_ACTUALIZACIONES==0){
  for(int k=0; k<MAXIMO; k++){
    char *silla=vector[k].silla;
    for(int j=0;j<MAXIMO;j++){
                 if(j==k){
                     j=j+1;
                 }
                 verificar_silla_ocupada(vector[k].silla,vector[j].silla);
            }
    char sillcon[2];
    char sillcon2[3];
    strncpy(sillcon,&silla[0],1); //Dejo solo la letra
    sillcon[1]='\0';
    
    strncpy(sillcon2,&silla[1],3);
    sillcon2[2]='\0';
    int convertido= atoi(sillcon2); //Dejo solo el número
    int col2;
    switch(*sillcon){
        case 'a': col2=0;
        break;
        case 'b': col2=1;
        break;
        case 'c': col2=2;
        break;
        case 'd': col2=3;
        break;
        case 'e': col2=4;
        break;
        case 'f': col2=5;
        break;
        case 'g': col2=6;
        break;
        case 'h': col2=7;
        break;
        case 'i': col2=8;
        break;
        case 'j': col2=9;
        break;
        case 'k': col2=10;
        break;
    }
  
  
	 		for (i=0; i < filas; i++){
				 for (int j=0; j < columnas; j++){
		 		 if((j==col2)&&(i==convertido)){
		  		 sala_de_cine[i][j]=1;
	   	  		 }else{
         		  if(sala_de_cine[i][j]==NULL){
				   sala_de_cine[i][j]=0;  
		  		}
		  }
		}
	}
	gotoxy(42, 17); printf("\t A\t B\t C\t D\t E\t F\t G\t H\t I\t J\t K\t \n");
    for(i=0; i<filas; i++){
      printf("\n");
      printf("                                         %d\t", i);
      for(int j=0; j<columnas; j++){
        printf("[%d]\t",sala_de_cine[i][j]);
      }
    }
}
}else{
	if(NUM_ACTUALIZACIONES!=0){
		for(int i=0;i<21;i++){
			for(int j=0;j<12;j++){
				sala_de_cine[i][j]=0;
			}
		}
		for(int k=0; k<MAXIMO; k++){
    char *silla=vector[k].silla;
    char sillcon[2];
    char sillcon2[3];
    strncpy(sillcon,&silla[0],1); //Dejo solo la letra
    sillcon[1]='\0';
    
    strncpy(sillcon2,&silla[1],3);
    sillcon2[2]='\0';
    int convertido= atoi(sillcon2); //Dejo solo el número
    int col2;
    switch(*sillcon){
        case 'a': col2=0;
        break;
        case 'b': col2=1;
        break;
        case 'c': col2=2;
        break;
        case 'd': col2=3;
        break;
        case 'e': col2=4;
        break;
        case 'f': col2=5;
        break;
        case 'g': col2=6;
        break;
        case 'h': col2=7;
        break;
        case 'i': col2=8;
        break;
        case 'j': col2=9;
        break;
        case 'k': col2=10;
        break;
    }
  
  
	 		for (i=0; i < filas; i++){
				 for (int j=0; j < columnas; j++){
		 		 if((j==col2)&&(i==convertido)){
		  		 sala_de_cine[i][j]=1;
	   	  		 }else{
         		  if(sala_de_cine[i][j]==NULL){
				   sala_de_cine[i][j]=0;  
		  		}
		  }
		}
	}
	gotoxy(42, 17); printf("\t A\t B\t C\t D\t E\t F\t G\t H\t I\t J\t K\t \n");
    for(i=0; i<filas; i++){
      printf("\n");
      printf("                                         %d\t", i);
      for(int j=0; j<columnas; j++){
        printf("[%d]\t",sala_de_cine[i][j]);
      }
    }
}
	}
}

    printf("\n\n");
          gotoxy(65, 40); printf("Presiona Enter Para Volver Al Menú Principal..."); 
          getchar();
}

//Procemiento para ejecutar la función que imprime la sala de cine
void proceso_sala_de_cine(){
         fflush(stdin);
         mostrar_sala_de_cine();
}

//Función para mostrar los datos ingresados por el usuario(registros)
void proceso_mostrar(){
       char opcion[1];
       printf("\t\t\t\t\t\t\t\t¿Desea mostrar los datos ingresados? s/n ");
       scanf("%s",opcion);
       printf("\n");
     
       if((strcmp(opcion,"s"))==0){
         for(i=0;i<MAXIMO;i++){
         fflush(stdin);
         mostrar_datos(vector[i].codigo, vector[i].nombre, vector[i].apellido, vector[i].silla);
         for(int j=0;j<MAXIMO;j++){
                 if(j==i){
                     j=j+1;
                 }
                 verificar_silla_ocupada(vector[i].silla,vector[j].silla);
            }
        }
        
         
          printf("\n\t\t\t\t\t*********************************************************************************************\n");
          printf("\n\t\t\t\t\t\t\t\tPresiona Enter Para Volver Al Menú Principal...");
          getchar();
      }
}

//Procedimiento para ejecutar la función ordenamiento (seleccion indirecta)
void proceso_ordenamiento(){
          fflush(stdin);
          ordenamiento();
  		  printf("\n");
  		  printf("\n\t\t\t\t\t\t\t\tLos Registros Han Sido Ordenados Correctamente \n\n");
          printf("\n\t\t\t\t\t*********************************************************************************************\n");
          printf("\n\t\t\t\t\t\t\t\tPresiona Enter Para Volver Al Menú Principal...");
          getchar();
}

//Función para ordenar los registros de acuerdo a la silla de cine(Seleccion indirecta)
void ordenamiento(){
  if(vector3==NULL){
  vector3=(int *)malloc(MAXIMO*sizeof(int *));
    } 
  for(i=0;i<MAXIMO;i++){
    int convertido;
    convertido=atoi(vector[i].codigo);
    vector3[i]=convertido;
    }
  for(i=0;i<MAXIMO-1;i++){
    int min= vector3[i];
    int jmin=i;
    for(int j=i+1; j<MAXIMO; j++){
      if(vector3[j]<min){
        min=vector3[j];
        jmin=j;
      }
    }
    vector3[jmin]=vector3[i];
    vector3[i]=min;
  }
  char convertir_num[11];
  for(i=0;i<MAXIMO;i++){
    sprintf(convertir_num,"%d",vector3[i]);
    for(int j=0;j<MAXIMO;j++){
      if((strcmp(vector[j].codigo,convertir_num))==0){
      mostrar_datos(vector[j].codigo,vector[j].nombre,vector[j].apellido,vector[j].silla);
      }
      for(int k=0;k<MAXIMO;k++){
                 if(k==j){
                     k=k+1;
                 }
                 verificar_silla_ocupada(vector[j].silla,vector[k].silla);
            }
    }
  }
}

//Procedimiento para ejecutar la función de búsqueda de un registro
void proceso_busqueda(){
  //solo se necesita recorrer el vector[i].codigo, y que lo vaya comparando con strcmp al string de documento ingresado por el usuario a buscar
          fflush(stdin);
          busqueda();
          printf("\n\n");
          printf("\n\t\t\t\t\t*********************************************************************************************\n");
          printf("\n\t\t\t\t\t\t\t\tPresiona Enter Para Volver Al Menú Principal...");
          getchar();
        
}

//Función para buscar un registro de acuerdo al codigo
void busqueda (){
  char busqueda_codigo[20];
  
  printf("\n\t\t\t\t\t\t\tPor favor ingrese el Código del Registro que va a buscar: ");
  scanf ("%s", busqueda_codigo);
  printf("\n\n");
  for(i=0; i<MAXIMO; i++){
    if (strcmp(vector[i].codigo, busqueda_codigo)==0){
      printf("\n\t\t\t\t\t\t\t\tEste es el registro asociado a ese código \n\n");
      mostrar_datos(vector[i].codigo,vector[i].nombre,vector[i].apellido,vector[i].silla);
    	}
		for(int j=0;j<MAXIMO;j++){
                 if(j==i){
                     j=j+1;
                 }
                 verificar_silla_ocupada(vector[i].silla,vector[j].silla);
            }	  
    }  
} 

//Procedimiento para ejecutar la función de actualizamiento de un registro
void proceso_modificar(){
  //solo se necesita recorrer el vector[i].codigo, y que lo vaya comparando con strcmp al string de documento ingresado por el usuario a buscar
          fflush(stdin);
          modificar_registro();
          printf("\n\n");
          printf("\n\t\t\t\t\t*********************************************************************************************\n");
          printf("\n\t\t\t\t\t\t\t\tPresiona Enter Para Volver Al Menú Principal...");
          getchar();
        
}

////Función para modificar un registro de acuerdo al codigo

void modificar_registro(){
	char nuevo_codigo[11];//Guarda el número de documento con el que vamos a buscar
	char codigo,apellido,nombre,silla;
  	printf("\n\t\t\t\t\t\t\tPor Favor ingrese el código del registro que va a modificar: ");
 	 scanf ("%s", nuevo_codigo);
 	 printf("\n\n");
  		for(i=0; i<MAXIMO; i++){
    		if ((strcmp(vector[i].codigo, nuevo_codigo))==0){
    		printf("\t\t\t\t\t\t\t\tEste es el registro asociado a ese código:\n\n");
    		mostrar_datos(vector[i].codigo,vector[i].nombre,vector[i].apellido,vector[i].silla);
    		printf("\n\t\t\t\t\t*********************************************************************************************\n");
			printf("\t\t\t\t\t\tIngrese los Nuevos Datos del Registro \n\n");
       		leer_datos(vector[i].codigo, vector[i].nombre,vector[i].apellido, vector[i].silla);
       		printf("\n\n\t\t\t\t\t\t\t\t\tDatos Actualizados Correctamente");
			}
			for(int j=0;j<MAXIMO;j++){
                 if(j==i){
                     j=j+1;
                 }
                 verificar_silla_ocupada(vector[i].silla,vector[j].silla);
            }
		}
}

//Procedimiento para ejecutar la función de borrar registros
void proceso_borrar(){
          fflush(stdin);
          borrar();
          printf("\n\n");
          printf("\n\t\t\t\t\t*********************************************************************************************\n");
          printf("\n\t\t\t\t\t\t\t\tPresiona Enter Para Volver Al Menú Principal...");
          getchar();
}

//Función para eliminar un registro deacuerdo a su código
void borrar(){
 char codigo_eliminar[20]; 
 char opc[1]; 
  
 printf("\n\t\t\t\t\t\t\tIngrese el documento del registro que quiere eliminar: ");
 scanf("%s", codigo_eliminar);
 printf("\n");
 for(int i=0; i<MAXIMO; i++){
   if(strcmp(vector[i].codigo, codigo_eliminar)==0){
   	 printf("\t\t\t\t\t\t\t\tEste es el Registro asociado a ese Código:\n\n");
     mostrar_datos(vector[i].codigo,vector[i].nombre,vector[i].apellido,vector[i].silla);
     printf("\n");
     printf("\n\t\t\t\t\t\t\t\t\tDesea Eliminar este registro? s/n: ");
     scanf("%s", opc);
     if (strcmp(opc, "s")==0){
       for (int j=i+1; j<=MAXIMO; j++ ){
         vector[j-1] = vector[j]; 
     }
       MAXIMO = MAXIMO-1;
    printf("\n\n\t\t\t\t\t\t\t\t\t  Registro Eliminado Correctamente"); 
     }
   }
   for(int j=0;j<MAXIMO;j++){
                 if(j==i){
                     j=j+1;
                 }
                 verificar_silla_ocupada(vector[i].silla,vector[j].silla);
            }
  } 
}

//Función para imprimir datos de contacto del cine
void contacto(){
	
	int k = 0, 	n=1;
	for (k = 0; k < n; k++)
	{
		system("cls");
		system("color 09");
		gotoxy(35, 5);  printf("     *********************************************************************************************\n");
		gotoxy(35, 6);  printf("     *                                                                                           *\n");
		gotoxy(35, 7);  printf("     *                                                                                           *\n");
		gotoxy(35, 8);  printf("     *                                                                                           *\n");
		gotoxy(35, 9);  printf("     *                                       ACERCA DE NOSOTROS(9)                               *\n");
		gotoxy(35, 10); printf("     *                                                                                           *\n");
		gotoxy(35, 11); printf("     *                                                                                           *\n");
		gotoxy(35, 12); printf("     *                                                                                           *\n");
	    gotoxy(35, 13); printf("     *                                                                                           *\n");
		gotoxy(35, 14); printf("     *********************************************************************************************\n");
		gotoxy(35, 15); printf("                                                                                                  \n");
		gotoxy(35, 16); printf("                                                                                                  \n");
		gotoxy(35, 17); printf("                                            ESTAMOS UBICADOS EN:                                  \n");
		gotoxy(35, 18); printf("                                      Cra.11a###6-46,Pereira,Risaralda                            \n");
		gotoxy(35, 19); printf("                                                                                                  \n");
		gotoxy(35, 20); printf("     *********************************************************************************************\n");
		gotoxy(35, 21); printf("                                                                                                  \n");
		gotoxy(35, 22); printf("                                           NÚMEROS DE CONTACTO:                                   \n");
		gotoxy(35, 23); printf("                                     CEL: 3156738924     TEL: 3087890                             \n");
		gotoxy(35, 24); printf("                                                                                                  \n");
		gotoxy(35, 25); printf("     *********************************************************************************************\n");
		gotoxy(35, 26); printf("                                                                                                  \n");
		gotoxy(35, 27); printf("                                           CORREO ELECTRONICO:                                    \n");
		gotoxy(35, 28); printf("                                         cinefilmpereira@gmail.com                                \n");
		gotoxy(35, 29); printf("                                                                                                  \n");
		gotoxy(35, 30); printf("     *********************************************************************************************\n");
		gotoxy(35, 31); printf("                                                                                                  \n");
		gotoxy(35, 32); printf("                            Presiona Una Tecla Para Volver Al Menú Principal...                   \n");
		getchar();

	}
}

//Procedimiento para ejecutar la funcion de imprimir recibo(Archivos)
void proceso_recibo(){
          				 system("cls");
          				 system("color 04");
          				 gotoxy(35, 5);	 printf("     *********************************************************************************************\n");
						 gotoxy(35, 6);  printf("     *                                                                                           *\n");
						 gotoxy(35, 7);	 printf("     *                                                                                           *\n");
						 gotoxy(35, 8);	 printf("     *                                                                                           *\n");
						 gotoxy(35, 9);  printf("     *                                            RECIBO(10)                                     *\n");
						 gotoxy(35, 10); printf("     *                                                                                           *\n");
						 gotoxy(35, 11); printf("     *                                                                                           *\n");
						 gotoxy(35, 12); printf("     *                                                                                           *\n");
	 					 gotoxy(35, 13); printf("     *                                                                                           *\n");
					   	 gotoxy(35, 14); printf("     *********************************************************************************************\n");
						 gotoxy(35, 15); printf("                                                                                                  \n");
						 char opcion[1];
						 printf("\t\t\t\t\tIndique 's' si tiene su recibo guardado o 'n' si es la primera vez que descarga su recibo[s/n]: ");
						 scanf("%s",opcion);
       					 printf("\n");
     
      					 if((strcmp(opcion,"n"))==0){
         					for(i=0;i<MAXIMO;i++){
         					fflush(stdin);
         					mostrar_datos(vector[i].codigo, vector[i].nombre, vector[i].apellido, vector[i].silla);
        				}
        
         					for(i=0;i<MAXIMO;i++){
             					for(int j=0;j<MAXIMO;j++){
                 					if(j==i){
                    				   j=j+1;
                 				}
                 			verificar_silla_ocupada(vector[i].silla,vector[j].silla);
            				}
         				}
         				printf("\n\t\t\t\t\t\t\t\tEl total a pagar es($): %d",total);
     					 printf("\n");
     					 printf("\n\t\t\t\t\t*********************************************************************************************\n");
						 char opcion2[1];
          				 printf("\t\t\t\t\t\t\t\t\t¿Desea Imprimir Su recibo? [s/n]:");
           				 scanf("%s",opcion2);
          				 printf("\n");
						 recibo();
     			        }else{
     				      recibo2();   
     				      printf("\n\n\t\t\t\t\t\t\t\t Los datos han sido reestablecidos...");
     				      printf("\n\n\t\t\t\t\t\t\t\t Presiona Una Tecla Para Volver Al Menú Principal...\n");
				   		  getchar();
				        }
}

//Función Que imprime el recibo de compra de boleteria y lo almacena en un archivo
void recibo(){
	boletas_comprar=fopen("BOLETAS.txt","w");
  if(boletas_comprar=fopen("BOLETAS.txt","w")){
  	printf("\n\n\t\t\t\t\t\t\t  El Recibo se Imprimio y Su Archivo se Descargó Correctamente...\n");
  	printf("n\n\t\t\t\t\t\t\t\t Presiona Una Tecla Para Volver Al Menú Principal...\n");
    getchar();
  }else{
  	printf("\n\n\t\t\t\t\t\t\t\t\t  Error al descargar...\n");
  	printf("n\n\t\t\t\t\t\t\t\t Presiona Una Tecla Para Volver Al Menú Principal...\n");
    getchar();
  }
 fprintf(boletas_comprar,"%d",MAXIMO);
 fprintf(boletas_comprar," %d",selector);
  for(i=0;i<MAXIMO;i++){
  fwrite(" ",1,strlen(" "),boletas_comprar);
  fwrite(vector[i].codigo,1,strlen(vector[i].codigo),boletas_comprar);
  fwrite(" ",1,strlen(" "),boletas_comprar);
  fwrite(vector[i].nombre,1,strlen(vector[i].nombre),boletas_comprar);
  fwrite(" ",1,strlen(" "),boletas_comprar);
  fwrite(vector[i].apellido,1,strlen(vector[i].apellido),boletas_comprar);
  fwrite(" ",1,strlen(" "),boletas_comprar);
  fwrite(vector[i].silla,1,strlen(vector[i].silla),boletas_comprar);
  fwrite(" ",1,strlen(" "),boletas_comprar);
 }

 fclose(boletas_comprar);
}

void recibo2(){
	boletas_comprar=fopen("BOLETAS.txt","r");
	if(boletas_comprar!=NULL){
		system("cls");
		fseek(boletas_comprar,0,SEEK_SET);
		fscanf(boletas_comprar, "%d %d",&MAXIMO,&selector);
        for(i=0;i<MAXIMO;i++){
		fscanf(boletas_comprar, " %s %s %s %s ",vector[i].codigo,vector[i].nombre,vector[i].apellido,vector[i].silla);
	   }
	}else{
		printf("\n\n\t\t\t\t\t\t\t\t ERROR, NO SE PUEDE LEER EL RECIBO\n");
		printf("\n\n\t\t\t\t\t\t\t\t Presiona Una Tecla Para Volver Al Menú Principal...\n");
        getchar();
	}
	fclose(boletas_comprar);
}

void gotoxy (int x, int y){
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon,dwPos);
}





