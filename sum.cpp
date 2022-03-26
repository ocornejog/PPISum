//Oscar Humberto Cornejo Guillen SUMA POR TECLADO EN PPI ETN-903
//Diseñar un sistema de computación que permita leer desde un teclado números enteros de
//maximo dos digitos. Los números serán sumados y el resultado se presentara en un display
//compuesto por displays de 7 segmentos ánodo común. Para el desarrollo utilizar el PPI,
//lenguaje C/C++, la librería NCURSES y plataforma Linux.

//Compilar:
//g++ sum.cpp -o sum -lncurses
#include <stdio.h>
#include <unistd.h>
#include <sys/io.h>
#include <time.h>
#include <ncurses.h>
/*direccion del puerto*/
#define puertoa 0x0300
#define puertob 0x0301
#define puertoc 0x0302
#define puertocntrl 0x0302
int key();
void display(int a, int b, int c);
int e=1;
char keyboard[]={0xEE,0xED,0xEB,0xE7,0xDE,0xDD,0xDB,0xD7,0xBE,0xBD,0xBB,0xB7,0x7E,0x7D,0x7B,0x77};

main()
{
	while(1){
	int numA1,numA2,numB1,numB2,result,cent,dec,uni,a;
		
	initscr();
	clear();
        start_color();
        init_pair(1,COLOR_WHITE,COLOR_BLUE);
        bkgd(COLOR_PAIR(1));                    //ponemos un color al lienzo y al texto que se escribira
	move (0,23);                            //ponemos cursor
	refresh();
	printw( "CORNEJO GUILLEN OSCAR HUMBERTO\n" );
	move (1,25);
	refresh();
	printw( "SUMA POR TECLADO EN PPI ETN 903 II/2019\n" );
        move (2,0);
	refresh();
	printw( "Oscar Humberto Cornejo Guillen SUMA POR TECLADO EN PPI ETN-903. Diseñar un sistema de \ncomputación que permita leer desde un teclado números enteros de maximo \ndos digitos. Los números serán sumados y el resultado se presentara en\nun display compuesto por displays de 7 segmentos ánodo común. Para el\ndesarrollo utilizar el PPI,lenguaje C/C++, la librería NCURSES y plataforma\nLinux.\n");
	move (9,0);
	refresh();
	a=0x90; //Palabra de control
	ioperm(puertocntrl, 1, 1); //Puerto de control habilitaddo
    	outb(a,puertocntrl); //Transferimos la palabra de control 90h al puerto 0x0300 (Control)
    	ioperm(puertocntrl, 1, 0); //Inhabilitamos puerto de control

	if(e==1){
	numA1=key(); //primer dato insertado en numA
	}
        else{if(e==2){
	numA2=key(); //segundo dato insertado en numA
	}
        else{if(e==3){
        numB1=key(); //primer dato insertado en numB
        }
	else{if(e==4){
        numB2=key(); //segundo dato insertado en numB
	}
        else {}
        }
        }
        }
        result=numA2*16+numA1+numB2*16+numB1; //suma con respecto a los pesos posicionales de cada parte de los numeros introducidos
	cent=result/100; //se realiza la conversion a centenas, decenas y unidades --> centenas = resultado div 100
	uni=result%10; //unidades = resultado modulo 10
        dec=(result%100-uni)/10; // decenas= (resultado modulo 100 - unidades) div 10
	display(cent,dec,uni); //se lleva estos datos a la función display
	e=0;
	break;//Con el prototipo implementado se deberia borrar este break para asi realizar las iteraciones constantes para la adquisicion y exposicion de datos
	}
	refresh();
	endwin();
}
	


//Función de adquisición de datos
int key()
{
	int a;
        int i=0, j=0;
	while(1)
	{
                ioperm(puertoa, 1, 1);//Puerto A habilitado
    		a=inb(puertoa); //Transferimos el contenido del puerto a "a"
    		ioperm(puertoa, 1, 0);//Inhabilitamos el Puerto A
                for(i=0;i<=15;i++)
                {
                       if(keyboard[i]==a)
                       {
                           j=i;  //asignamos el valor de i a la variable que tomara el nuevo valor para el calculo
                                 //nuevo[]={0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F}
 		       }
                      else
                       {
                       }
                }  
		usleep(500000);
                e=e++;//el valor de e variará de 1 a 4, indicando el numero de valores presionados
		return j;
	}
}

void display(int a, int b, int c)
{	
	while (1){
	int unida,dece,unidec,cente;
	initscr();
	unida=c&&0x000f;//se precarga un bit en la parte de alta del puerto b en una variable
	dece=b&&0x000f;//se quita posible informacion adicional de la variable
        dece=dece*16;//desplazamos las decenas hacia su posicion 
	unidec=unida||dece;//se realiza un or para unir tanto parte alta como parte baja del puerto b
	ioperm(puertob, 1, 1);
    	outb(unidec,puertob);//se carga el dato al Puerto B
    	ioperm(puertob, 1, 0);

	cente=a&&0x000f;//se quita la informacion adicional de las centenas
	ioperm(puertoc, 1, 1);
    	outb(cente,puertoc);//cargamos las centenas al puerto C o
    	ioperm(puertoc, 1, 0);
	}

	printw( "Presione una tecla para finalizar\n" );//salir del programa
	getch();
	refresh();
	endwin();
}

