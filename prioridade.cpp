#include <iostream>
#include "../BlackGPIO/BlackGPIO.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "../ADC/Adc.h"
#include <stdio.h>
#include <sys/time.h>     // getpriority(int which, int who)  setpriority(int which, int who, int prio);
#include <sys/resource.h>
#include <math.h>


using namespace BlackLib;


// funcao que realiza loops e calculos que tomam tempo na CPU.
// dependendo da prioridade do processo, esses calculos podem ser
// feitos mais rapidamente ou nao
void carga(int k)
{
  float f = 0.999999;
  for(int i=0; i<k; i++)
    {
      f = f*f*f*f*f;
      f = 1.56;
        for(int j=0; j<k; j++)
           {
	     f = sin(f)*sin(f)*f*f*f;

            }
    }

}

int main(int argc, char* argv[]){
	pid_t pid1;

	BlackGPIO saida2(GPIO_69, output); // pino P8_8
	BlackGPIO saida(GPIO_67, output); // pino P8_9
	
	ADC adc(AINx::AIN0); //pino P9_39
	ADC adc_filho(AINx::AIN2); // pino p9_37
	
	pid1 = fork(); // abrindo um novo processo para mudarmos a prioridade de pai e filho separadamente

	switch(pid1)
	    {
	    case -1:       // erro na abertura do processo filho
	      exit(1);  
	    case 0:        // Parte a ser executada pelo processo Filho
	      while(1) {
		// setamos a prioridade para o valor do adc/200 pois irá de 0 a 20
		setpriority(PRIO_PROCESS, 0, adc_filho.getIntValue()/200); 

    		cout << "valor da prioridade do processo filho, após setpriority(): " << getpriority(PRIO_PROCESS, 0 ) <<endl;
	        printf("Sou o processo Filho e peguei o adc taqui: %d\n", adc_filho.getIntValue());

		// esse high e low vao fazer piscar o led, e a velocidade depende do tempo que levar pra fazer a carga
		// e a carga demorara mais ou menos, dependendo da prioridade do processo
		saida.setValue(high);
		cout<<"vou fazer a carga pra desligar o filho..."<<endl;
		carga(1000);
		saida.setValue(low);
		cout<<"vou fazer a carga pra ligar o filho..."<<endl;
		carga(1000);
	      }
	      break;
	    default:       // parte a ser executada pelo processo Pai
	      while(1) {
		setpriority(PRIO_PROCESS, 0, adc.getIntValue()/200);

    		cout << "valor da prioridade do processo pai, após setpriority(): " << getpriority(PRIO_PROCESS, 0 ) <<endl;
	        printf("\nSou o processo Pai e tbm peguei o adc, olha so: %d \n", adc.getIntValue());


		saida2.setValue(high);
		cout<<"vou fazer a carga pra desligar o pai..."<<endl;
		carga(1000);
		saida2.setValue(low);
		cout<<"vou fazer a carga pra ligar o pai..."<<endl;
		carga(1000);

	      }
		break;
	}
	

	return 0;
}

