#include "lib.h"

int main()
{

    eClient clientes[TAMC];
    eRent rentas[TAMR];

    char seguir = 's';

    inicializarClientes(clientes,TAMC);//INICIALIZA ESTADOS DE CLIENTES EN 0
    inicializarRenta(rentas,TAMR);//INICIALIZA LAS RENTAS EN -1
    hardCodear(clientes,rentas);//HARDCODEA LOS PRIMERO CINCO CLIENTES Y ALQUILERES

     while(seguir=='s')
    {
        switch(menu("1-Alta cliente \n2-Modificar cliente \n3-Baja cliente \n4-Nuevo alquiler \n5-Finalizar alquiler \n\nInformes:\n\n'6'\t-Listado de clientes\n'7'\t-Cliente con mas alquileres\n'8'\t-Equipos mas alquilados\n'9'\t-Tiempo promedio de alquieleres por equipo\n'10'\t-Todos los clientes con sus alquileres\n\n11-Salir\n\n"))// FUNCION MENU SOLO MUESTRA Y LEE LA OPCION
        {
        case 1:
         {
            if(alta(clientes,TAMC)) // ALTA
                {
                printf("Alta exitosa\n");
                }
            break;
         }
        case 2:
         {
            if(modificar(clientes,rentas,TAMC,TAMR))//MODIFICACION
            {
                printf("Modificacion exitosa\n");
            }
            break;
         }

        case 3:
            {
            bajaCliente(clientes,TAMC);//BAJA
            break;
            }
        case 4:
            {
            nuevoAlquiler(clientes,rentas,TAMC,TAMR);
            break;
            }

        case 5:
            {
             finAlquiler(clientes,rentas,TAMC,TAMR);
             break;
            }
        case 6://LISTADO DE CLIENTES
            {
                mostrarClientes(clientes,TAMC);
                break;
            }
        case 7:
            {
            mejorCliente(clientes,rentas,TAMC,TAMR);
            break;
            }
        case 8:
            {
            equipoMasAlquilado(rentas,TAMR);
            break;
            }
        case 9:
            {
            promedioAlquileres(rentas,TAMR);
            break;
            }
        case 10:
            {
            system("cls");
            rentasxclientes(clientes,rentas,TAMC,TAMR);
            break;
            }
        case 11:
            {
            seguir='n';
            break;
            }
        default:
            {
            printf("Opcion incorrecta.\n");
            break;
            }
        }
        getch();
        system("cls");

    }
    return 0;
}


