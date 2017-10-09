#include "lib.h"


void inicializarClientes(eClient clientes[],int tamC)
{
    int i;

    for(i=0; i<tamC; i++)
    {
        clientes[i].estado=0;
        clientes[i].cantRent=0;
    }

}

void inicializarRenta(eRent rentas[],int tamR)
{
    int i;
    for(i=0; i<tamR; i++)
    {
        rentas[i].idCliente=-1;
        rentas[i].equipo=-1;
        rentas[i].tiempoEstimado=-1;
        rentas[i].tiempoReal=-1;
        rentas[i].estado=-1;
    }
}

int menu(char mensaje[])
{
    int opcion;
    printf("%s",mensaje);
    printf("Ingrese una opcion: ");
    scanf("%d",&opcion);
    printf("\n");
    return opcion;
}

char menuI(char mensaje[])
{
    char opcion;
    printf("%s",mensaje);
    printf("Ingrese una opcion: ");
    scanf("%c",&opcion);
    printf("\n");
    opcion=tolower(opcion);
    return opcion;
}

int posicionLibre(eClient clientes[],int tam)
{
    int i;
    for(i=0; i<tam; i++)
    {
        if(clientes[i].estado==0)
            return i;
    }
    return -1;
}

int posicionLibreR(eRent rentas[],int tam)
{
    int i;
    for(i=0; i<tam; i++)
    {
        if(rentas[i].estado==-1)
            return i;
    }
    return -1;
}

int alta(eClient clientes[],int tam)
{
    char auxStringNombre[100], auxStringApellido[100],auxStringDni[100]; // VARIABLES AUXILIARES STRINGS
    int auxDni,libre,i;//VARIABLES AUXILIARES ENTERAS
    libre=posicionLibre(clientes,tam);//ASIGNA LA POSICION LIBRE A LA VARIABLE SINO HAY LIBRES ENTREGA -1
    if(libre==-1)//SI LIBRE ES -1 ES POR QUE ESTA LLENO
    {
        printf("Error 404 la base de datos esta llena.\n");
        return 0;
    }
    if(!getStringLetras("Ingrese nombre: ",auxStringNombre)) // VERIFICACION DEL NOMBRE
    {
        printf("El nombre debe contener solo letras.\n");
        return 0;
    }
    if(!getStringLetras("Ingrese apellido: ",auxStringApellido))// VERIFICACION APELLIDO
    {
        printf("El apellido debe contener solo letras.\n");
        return 0;
    }

    if(!getStringNumeros("Ingrese dni para crear cliente: ",auxStringDni)) // VERIFICACION DEL DNI
    {
        printf("El DNI debe contener solo numeros.\n");
        return 0;
    }
    auxDni=atoi(auxStringDni);// PASA EL STRING DE DNI AL INT
    if(!verificarDni(clientes,tam,auxDni))// VERIFICACION DEL DNI
    {
        printf("El DNI ya se encuentra en uso.");
        return 0;
    }


    for(i=0;i<tam;i++)
    {
    if(clientes[i].estado==0)
        {
        clientes[i].id= (i+1);
        }
    }



    strcpy(clientes[libre].nombre,auxStringNombre);
    strcpy(clientes[libre].apellido,auxStringApellido);
    clientes[libre].dni=auxDni;
    clientes[libre].estado=1;
    return 1;
}

int verificarId(eClient clientes[],int tam,int id)
{
    for(int i=0; i<tam; i++)
    {
        if(clientes[i].id==id) // SI MATCHEA RETORNA FALSO
        {
            return 0;
        }
    }
    return 1;
}


int verificarDni(eClient clientes[],int tam,int dni)
{
    for(int i=0; i<tam; i++)
    {
        if(clientes[i].dni==dni) // SI MATCHEA RETORNA FALSO
        {
            return 0;
        }
    }
    return 1;
}

int getStringNumeros(char mensaje[],char input[])
{
    char aux[256];
    getString(mensaje,aux);
    if(esNumerico(aux))
    {
        strcpy(input,aux);
        return 1;
    }
    return 0;
}

int getStringLetras(char mensaje[],char input[])
{
    char aux[256];
    getString(mensaje,aux);
    if(esSoloLetras(aux))
    {
        strcpy(input,aux);
        return 1;
    }
    return 0;
}

int esSoloLetras(char str[])
{
    int i=0;
    while(str[i] != '\0')
    {
        if((str[i] != ' ') && (str[i] < 'a' || str[i] > 'z') && (str[i] < 'A' || str[i] > 'Z'))
            return 0;
        i++;
    }
    return 1;
}

void getString(char mensaje[],char input[])
{
    printf("%s",mensaje);
    fflush(stdin);
    gets(input);
}

int esNumerico(char str[])
{
    int i=0;
    while(str[i] != '\0')
    {
        if(str[i] < '0' || str[i] > '9')
            return 0;
        i++;
    }
    return 1;
}


void hardCodear(eClient clientes[],eRent rentas[])
{
    //AUX CLIENTES
    eClient AuxClientes[5]= {{1,"Lucas","Massa",39456789,1,1},{2,"Augusto","Alviggi",37852456,1,1},{3,"Martin","Alberio",40753951,1,2},{4,"Santiago","Bonasi",41741654,1,1},{5,"Leandro","Ripo",38274159,1,1}};
    // CARGA 5 CLIENTES CON EL AUXILIAR
    for(int i=0; i<5; i++)
    {
        clientes[i]=AuxClientes[i];
    }
    //AUX PROYECTOS
    eRent AuxRentas[6]= {{1,1,101,6.5,-1,"Juan carlos",1},{2,2,102,10.0,-1,"Roberto",1},{3,3,103,4.3,6,"Omar",1},{4,4,101,2.15,-1,"Eduardo",1},{5,5,103,4.0,-1,"Jose",1},{3,6,103,4.3,-1,"Omar",1}};
    //CARGA 5 PROYECTOS CON EL AUXILIAR
    for(int i=0; i<6; i++)
    {
        rentas[i]=AuxRentas[i];
    }

}


void rentasxclientes(eClient clientes[],eRent rentas[],int tamC, int tamR)
{
    int i,j;

    for(i=0; i<tamC; i++)
    {
        if(clientes[i].estado==1)
        {
            printf("\nEl cliente [%s %s] posee los siguientes alquileres:\n", clientes[i].nombre,clientes[i].apellido);



            for(j=0; j<tamR; j++)
            {
                if(rentas[j].idCliente == clientes[i].id)
                {
                    //esto hay que cambiarlo por un switch
                    switch(rentas[j].equipo)
                    {
                    case 101:
                            {
                            printf("\nID de operacion: %d\n",rentas[j].idOP);
                            printf("Equipo: Amoladora\n");
                            printf("Horas estimadas de uso: %d\n",rentas[j].tiempoEstimado);
                            if(rentas[j].tiempoReal==-1)
                            {
                            printf("Tiempo real de alquiler: En curso...\n");
                            }
                            else
                            {
                            printf("Tiempo real de alquiler: %d\n",rentas[j].tiempoReal);
                            }
                            printf("Operado por: %s\n\n",rentas[j].operador);
                            break;
                            }
                    case 102:
                            {
                            printf("\nID de operacion: %d\n",rentas[j].idOP);
                            printf("Equipo: Mezcladora\n");
                            printf("Horas estimadas de uso: %d\n",rentas[j].tiempoEstimado);
                            if(rentas[j].tiempoReal==-1)
                            {
                            printf("Tiempo real de alquiler: En curso...\n");
                            }
                            else
                            {
                            printf("Tiempo real de alquiler: %d\n",rentas[j].tiempoReal);
                            }
                            printf("Operado por: %s\n\n",rentas[j].operador);
                            break;
                            }
                    case 103:
                        {
                        printf("\nID de operacion: %d\n",rentas[j].idOP);
                        printf("Equipo: Taladro\n");
                        printf("Horas estimadas de uso: %d\n",rentas[j].tiempoEstimado);
                        if(rentas[j].tiempoReal==-1)
                        {
                        printf("Tiempo real de alquiler: En curso...\n");
                        }
                        else
                        {
                        printf("Tiempo real de alquiler: %d\n",rentas[j].tiempoReal);
                        }
                        printf("Operado por: %s",rentas[j].operador);
                        break;
                        }}
                        printf("\n");
                }

            }


        }
    }

}

    int modificar(eClient clientes[],eRent rentas[],int tamC,int tamR)
    {
        char auxStringId[100],auxStringNombre[100], auxStringApellido[100],auxStringDni[100]; // 4 VARIABLES AUXILIARES STRINGS
        int id,auxDni,flag=0;// 3 VARIABLES AUXILIARES ENTERAS
        if(!getStringNumeros("Ingrese ID a modificar: ",auxStringId)) // VERIFICACION DEL ID
        {
            printf("El id debe contener solo numeros.\n");
            return 0;
        }
        id=atoi(auxStringId);// PASA EL STRING DE ID AL INT
        for(int i=0; i<tamC; i++)
        {
            if(id==clientes[i].id && clientes[i].estado==1)
            {
                flag=1;

                printf("\nEl cliente a modificar es: \n");
                printf("Nombre:\t %s %s\n",clientes[i].nombre,clientes[i].apellido);
                printf("DNI:\t %d\n\n",clientes[i].dni);


                switch(menu("¿Que opcion quiere modificar?\n\n1-Nombre\n2-Apellido\n3-dni\n4-Ninguna\n"))
                {


                case 1:
                    if(!getStringLetras("Nombre modificado: ",auxStringNombre))//VERIFICA QUE TENGA SOLO LETRAS
                    {
                        printf("El nombre debe tener solo letras.\n");
                        return 0;
                    }
                    strcpy(clientes[i].nombre,auxStringNombre);//COPIA EL AUXILIAR A EL ORIGINAL
                    break;
                case 2:
                    if(!getStringLetras("Apellido modificado: ",auxStringApellido))//VERIFICA QUE TENGA SOLO LETRAS
                    {
                        printf("El nombre debe tener solo letras.\n");
                        return 0;
                    }
                    strcpy(clientes[i].apellido,auxStringApellido);//COPIA EL AUXILIAR A EL ORIGINAL
                    break;
                case 3:
                    if(!getStringNumeros("Dni modificado: ",auxStringDni))// VERIFICA EL ID
                    {
                        printf("El Dni debe tener solo numeros\n");
                        return 0;
                    }
                    auxDni=atoi(auxStringDni);// PASA LA CADENA A UN ENTERO
                    if(!verificarId(clientes,tamC,auxDni))//VERIFICA QUE NO SEA UN ID REPETIDO
                    {
                        printf("Ese Dni ya existe.\n");
                        return 0;
                    }
                    clientes[i].dni=auxDni;
                    break;

                default:
                    printf("Modificacion cancelada");
                    return 0;
                    break;
                }
            }
        }
        if(!flag)// FLAG DE CONTROL PARA VER SI NO ENCONTRO EL IF
        {
            printf("No se encuentra el ID ingresado.\n");
            return 0;
        }
        return 1;
    }

    int nuevoAlquiler(eClient clientes[],eRent rentas[],int tamC,int tamR)
    {
        char auxOperador[100];
        int auxId,auxI,libre;// VARIABLES AUXILIARES ENTERAS
        int auxTime;// VARIABLE AUXILIAR DE TIEMPO
        libre=posicionLibreR(rentas,tamR);//ASIGNA LA POSICION LIBRE A LA VARIABLE SI NO HAY LIBRES ENTREGA -1
        if(libre==-1)//SI LIBRE ES -1 ES POR QUE ESTA LLENO
        {
            printf("Error 404 la base de datos esta llena.\n");
            return 0;
        }

        rentas[libre].idOP=(libre+1);
        printf("Ingrese ID del cliente que desea alquilar: \n");
        scanf("%d",&auxId);
        auxI=auxId-1;
        rentas[libre].idCliente=auxId;

        if(clientes[auxI].estado==0)
        {
            printf("El cliente no existe");
            return 0;
        }

        if(clientes[auxI].estado==1)
        {
            printf("El cliente [%s %s] desea realizar un nuevo alquiler.\n",clientes[auxI].nombre,clientes[auxI].apellido);

            switch(menu("\nSeleccione el equipo que desea alquilar:\n1:Amoladora\n2:Mezcladora\n3:Taladro"))
            {
            case 1:
                rentas[libre].equipo=101;
                break;
            case 2:
                rentas[libre].equipo=102;
                break;
            case 3:
                rentas[libre].equipo=103;
                break;
            }

            printf("\nIngrese la cantidad de horas estimado del alquiler: \n");
            scanf("%d",&auxTime);
            rentas[libre].tiempoEstimado=auxTime;


            getStringLetras("\nIngrese el nombre del operador: \n",auxOperador);
            strcpy(rentas[libre].operador,auxOperador);
            rentas[libre].estado=1;
            clientes[auxI].cantRent++;

            system("pause");
            system("cls");


        }


        printf("Cliente: %s %s\n",clientes[auxI].nombre,clientes[auxI].apellido);

        switch(rentas[libre].equipo)//Muestra los detalles del alquiler
        {
        case 101:
        {
            printf("\nID de operacion: %d\n",rentas[libre].idOP);
            printf("\nEquipo: Amoladora\n");
            printf("\nHoras estimadas de uso: %d\n",rentas[libre].tiempoEstimado);
            printf("\nNombre del operador: %s\n\n",rentas[libre].operador);
            break;
        }

        case 102:
        {
            printf("\nID de operacion: %d\n",rentas[libre].idOP);
            printf("\nEquipo: Mezcladora\n");
            printf("\nHoras estimadas de uso: %d\n",rentas[libre].tiempoEstimado);
            printf("\nNombre del operador: %s\n\n",rentas[libre].operador);
            break;
        }
        case 103:
        {
            printf("\nID de operacion: %d\n",rentas[libre].idOP);
            printf("\nEquipo: Taladro\n");
            printf("\nHoras estimadas de uso: %d\n",rentas[libre].tiempoEstimado);
            printf("\nNombre del operador: %s\n\n",rentas[libre].operador);
            break;
        }}

        system("pause");
        system("cls");

        return 1;
    }

    void mostrarClientes(eClient clientes[],int tam)
{
    int i;
    for(i=0;i<tam;i++)
    {
        if(clientes[i].estado==1)
        {
        printf("ID:\t %d\n",clientes[i].id);
        printf("Nombre:\t %s %s\n",clientes[i].nombre,clientes[i].apellido);
        printf("DNI:\t %d\n",clientes[i].dni);
        printf("La cantidad de alquileres de cliente es: %d\n\n",clientes[i].cantRent);
        }
    }
}

void bajaCliente(eClient clientes[],int tam)
{
        char auxStringId[100],confirm;
        int id;// 3 VARIABLES AUXILIARES ENTERAS
        if(!getStringNumeros("Ingrese ID a dar de baja: ",auxStringId)) // VERIFICACION DEL ID
        {
            printf("El id debe contener solo numeros.\n");
        }
        id=atoi(auxStringId);// PASA EL STRING DE ID AL INT
        for(int i=0; i<tam; i++)
        {
            if(id==clientes[i].id && clientes[i].estado==1)
            {


                printf("\nEl cliente a dar de baja es: \n");
                printf("Nombre:\t %s %s\n",clientes[i].nombre,clientes[i].apellido);
                printf("DNI:\t %d\n\n",clientes[i].dni);
                printf("Confirmar baja: S/N");
                scanf("%c",&confirm);
                if(confirm=='s'||confirm=='S')
                {
                    clientes[i].estado=0;
                    printf("Baja exitosa");

                }

            }
        }

}

void finAlquiler(eClient clientes[],eRent rentas[],int tamC,int tamR)
{

    int auxIDC,auxIDR;
    int auxDuracionReal;
    int i,j;
    system("cls");
    printf("Ingrese ID de cliente:\n\n");
    mostrarClientes(clientes,TAMC);
    scanf("%d",&auxIDC);

     for(i=0; i<tamC; i++)
    {
        if(clientes[i].id==auxIDC)
        {
            printf("\nEl cliente [%s %s] posee los siguientes alquileres en curso:\n\n", clientes[i].nombre,clientes[i].apellido);



            for(j=0; j<tamR; j++)
            {
                if(rentas[j].idCliente == clientes[i].id && rentas[j].tiempoReal==-1)
                {
                    //esto hay que cambiarlo por un switch
                    if(rentas[j].equipo==101)
                    {
                        printf("ID de operacion: %d\n",rentas[j].idOP);
                        printf("Equipo: Amoladora\n");
                        printf("Horas estimadas de uso: %d\n",rentas[j].tiempoEstimado);
                        printf("Operado por: %s\n\n",rentas[j].operador);
                    }

                    if(rentas[j].equipo==102)
                    {
                        printf("ID de operacion: %d\n",rentas[j].idOP);
                        printf("Equipo: Mezcladora\n");
                        printf("Horas estimadas de uso: %d\n",rentas[j].tiempoEstimado);
                        printf("Operado por: %s\n\n",rentas[j].operador);
                    }
                    if(rentas[j].equipo==103)
                    {
                        printf("ID de operacion: %d\n",rentas[j].idOP);
                        printf("Equipo: Taladro\n");
                        printf("Horas estimadas de uso: %d\n",rentas[j].tiempoEstimado);
                        printf("Operado por: %s",rentas[j].operador);
                    }
                    printf("\n");

                }
            }

            printf("\nIngrese el ID de operacion a finalizar: \n");
            scanf("%d",&auxIDR);
            auxIDR=auxIDR-1;
            printf("Ingrese la duracion real (en horas) del alquiler: \n");
            scanf("%d",&auxDuracionReal);

            rentas[auxIDR].tiempoReal=auxDuracionReal;
            printf("Alquiler finalizado con exito!");

        }

    }

}



void mejorCliente(eClient clientes[],eRent rentas[],int tamC,int tamR)
{

    int i;
    int flag,maximo;
    flag = 0;

    for(i=0;i<tamC;i++)
    {
        if(flag==0)
        {
            maximo=clientes[i].cantRent;
            flag=1;
        }

        else if (maximo<clientes[i].cantRent)
        {
        maximo=clientes[i].cantRent;
        }
    }

    printf("El/Los cliente/s con mas alquileres es/son: \n\n");

    for(i=0;i<tamC;i++)
    {
        if(maximo==clientes[i].cantRent&&clientes[i].estado==1)
        {
            printf("%s %s.\nCantidad de alquileres: %d.\n",clientes[i].nombre,clientes[i].apellido,maximo);
        }
    }


}



void promedioAlquileres(eRent rentas[],int tamR)
{
    int i,acum,cont;
    float prom;
    acum=0;
    cont=0;
    for(i=0;i<tamR;i++)
    {
        if(rentas[i].tiempoReal!=-1)
        {
        acum=acum+rentas[i].tiempoReal;
        cont++;
        }
    }
    prom= acum/cont;

    printf("El promedio del tiempo real de los alquileres es %.2f",prom);
}


void equipoMasAlquilado(eRent rentas[],int tamR)
{
    int i;
    int cont1,cont2,cont3;
    cont1=0;
    cont2=0;
    cont3=0;


    for(i=0;i<tamR;i++)
    {
        switch(rentas[i].equipo)
            {
            case 101:
                {
                cont1++;
                break;
                }
            case 102:
                {
                cont2++;
                break;
                }
            case 103:
                {
                cont3++;
                break;
                }
            }

    }

    if(cont1>cont2&&cont1>cont3)
        {
        printf("El equipo mas alquilado es: Amoladora\nCantidad de veces alquiado: %d",cont1);
        }
    else if(cont2>cont1&&cont2>cont3)
        {
        printf("El equipo mas alquilado es: Mezcladora\nCantidad de veces alquiado: %d",cont2);
        }
    else
        {
        printf("El equipo mas alquilado es: Taladro\nCantidad de veces alquiado: %d",cont3);
        }

}
