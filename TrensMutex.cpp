#include <iostream>
#include "../BlackGPIO/BlackGPIO.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include "../ADC/Adc.h"
#include <string.h>
using namespace BlackLib;

void *thread_function_1(void *arg); // declaração da função a ser executada na thread
void *thread_function_2(void *arg); // declaração da função a ser executada na thread
void *thread_function_3(void *arg);
void *thread_function_4(void *arg);

pthread_mutex_t work_mutex_1, work_mutex_2;

BlackGPIO saida_led_1_branco(GPIO_66, output); // ok primeiro led branco io7
BlackGPIO saida_led_1_amarelo(GPIO_67, output); // ok primeiro led amarel io8
BlackGPIO saida_led_1_verde(GPIO_69, output); // ok primeiro led verde io9
BlackGPIO saida_led_2_amarelo(GPIO_23, output); // ok segundo led amarel io13
BlackGPIO saida_led_2_verde(GPIO_45, output); // ok segundo led verde io11
BlackGPIO saida_led_2_azul(GPIO_46, output); // ok segundo led azul io16
BlackGPIO saida_led_3_verde(GPIO_47, output); // ok terceiro led verde io15
BlackGPIO saida_led_3_branco(GPIO_27, output); // ok terceiro led branco io 17
BlackGPIO saida_led_3_amarelo(GPIO_65, output); // ok terceiro led amarel io18
BlackGPIO saida_led_4_verde(GPIO_44, output); // ok quarto led verde io12
BlackGPIO saida_led_4_amarelo(GPIO_68, output); // ok quarto led amarel io10
BlackGPIO saida_led_4_azul(GPIO_26, output); // ok quarto led azul io14

BlackGPIO leds[12] = {saida_led_1_branco,
										saida_led_1_amarelo,
										saida_led_1_verde,
										saida_led_2_amarelo,
										saida_led_2_verde,
										saida_led_2_azul,
										saida_led_3_verde,
										saida_led_3_branco,
										saida_led_3_amarelo,
										saida_led_4_verde,
										saida_led_4_amarelo,
										saida_led_4_azul
										};

ADC adc_1(AINx::AIN4);
ADC adc_2(AINx::AIN6);
ADC adc_3(AINx::AIN2);

int tempo_1 = 1;
int tempo_2 = 1;
int tempo_3 = 1;

void L(int trem, int apagar_1, int apagar_2, int apagar_3) {
		leds[trem].setValue(high);
		leds[apagar_1].setValue(low);
		leds[apagar_2].setValue(low);
		leds[apagar_3].setValue(low);
}

int main(int argc, char* argv[]){
	// while (1){
	// 	saida_led_1_branco.setValue(high);
	// 									saida_led_1_amarelo.setValue(high);
	// 									saida_led_1_verde.setValue(high);
	// 									saida_led_2_amarelo.setValue(high);
	// 									saida_led_2_verde.setValue(high);
	// 									saida_led_2_azul.setValue(high);
	// 									saida_led_3_verde.setValue(high);
	// 									saida_led_3_branco.setValue(high);
	// 									saida_led_3_amarelo.setValue(high);
	// 									saida_led_4_verde.setValue(high);
	// 									saida_led_4_amarelo.setValue(high);
	// 									saida_led_4_azul.setValue(high);
	// 	printf("saida do adc 1: %d\n", adc_1.getIntValue());
	// 	printf("saida do adc 2: %d\n", adc_2.getIntValue());
	// 	printf("saida do adc 3: %d\n", adc_3.getIntValue());
	// 	sleep(1);
	// }
	// return 0;
	int res;
	pthread_t a_thread, b_thread, c_thread, d_thread;
	void *thread_result;

	// Iniciar Mutex
	res = pthread_mutex_init(&work_mutex_1, NULL);
	if (res != 0) {
			perror("Iniciação do Mutex falhou");
			exit(EXIT_FAILURE);
	}

	res = pthread_mutex_init(&work_mutex_2, NULL);
	if (res != 0) {
			perror("Iniciação do Mutex falhou");
			exit(EXIT_FAILURE);
	}
	// Criar thread
	res = pthread_create(&a_thread, NULL, thread_function_1, NULL);
	if (res != 0) {
			perror("Criação da Thread falhou");
			exit(EXIT_FAILURE);
	}

 res = pthread_create(&b_thread, NULL, thread_function_2, NULL);
	if (res != 0) {
			perror("Criação da Thread falhou");
			exit(EXIT_FAILURE);
	}

	res = pthread_create(&c_thread, NULL, thread_function_3, NULL);
	if (res != 0) {
			perror("Criação da Thread falhou");
			exit(EXIT_FAILURE);
	}

	res = pthread_create(&d_thread, NULL, thread_function_4, NULL);
	if (res != 0) {
			perror("Criação da Thread falhou");
			exit(EXIT_FAILURE);
	}

	// Juntando thread main() com a_thread

	res = pthread_join(a_thread, &thread_result);
	if (res != 0) {
			perror("Junção da Thread falhou");
			exit(EXIT_FAILURE);
	}
	res = pthread_join(b_thread, &thread_result);
	if (res != 0) {
			perror("Junção da Thread falhou");
			exit(EXIT_FAILURE);
	}
	res = pthread_join(c_thread, &thread_result);
	if (res != 0) {
			perror("Junção da Thread falhou");
			exit(EXIT_FAILURE);
	}
	res = pthread_join(d_thread, &thread_result);
	if (res != 0) {
			perror("Junção da Thread falhou");
			exit(EXIT_FAILURE);
	}

	pthread_mutex_destroy(&work_mutex_1);  // destruição do multex
	pthread_mutex_destroy(&work_mutex_2);  // destruição do multex

	exit(EXIT_SUCCESS);

	// BlackGPIO saida16(GPIO_22, output); // ok
	// BlackGPIO saida17(GPIO_63, output); // ruim
	// BlackGPIO saida18(GPIO_36, output); // ruim
	// BlackGPIO saida19(GPIO_33, output);
	// BlackGPIO saida20(GPIO_32, output);
	// BlackGPIO saida21(GPIO_61, output); // ok
	// BlackGPIO saida22(GPIO_86, output); // ok
	// BlackGPIO saida23(GPIO_88, output); // ruim
	// BlackGPIO saida24(GPIO_87, output); // ruim
	// BlackGPIO saida25(GPIO_89, output); // ruim
	// BlackGPIO saida26(GPIO_10, output); //ruim
	// BlackGPIO saida27(GPIO_11, output); //ruim
	// BlackGPIO saida28(GPIO_9, output);
	// BlackGPIO saida29(GPIO_81, output);
	// BlackGPIO saida30(GPIO_117, output);
	// BlackGPIO saida31(GPIO_14, output);

}

void *thread_function_1(void *arg) {
    while (1) {
        L(2,4,6,9);
				usleep(tempo_1);

				pthread_mutex_lock(&work_mutex_1);
        L(4,2,6,9);
				usleep(tempo_1);
				pthread_mutex_unlock(&work_mutex_1);

        L(6,4,2,9);
				usleep(tempo_1);

        L(9,6,4,2);
				usleep(tempo_1);
    }
    pthread_exit(0);
}

void *thread_function_2(void *arg) {
    while(1) {
        L(1,3,8,10);
				usleep(tempo_2);

      	pthread_mutex_lock(&work_mutex_2);
        L(3,1,8,10);
				usleep(tempo_2);
				pthread_mutex_unlock(&work_mutex_2);

        L(8,1,3,10);
				usleep(tempo_2);

				pthread_mutex_lock(&work_mutex_1);
        L(10,3,8,1);
				usleep(tempo_2);
				pthread_mutex_unlock(&work_mutex_1);

    }
    pthread_exit(0);
}

void *thread_function_3(void *arg) {
    while(1) {
        L(0,5,7,11);
				usleep(tempo_3);

        L(5,11,7,0);
				usleep(tempo_3);

        L(7,11,5,0);
				usleep(tempo_3);

				pthread_mutex_lock(&work_mutex_2);
        L(11,7,5,0);
				usleep(tempo_3);
				pthread_mutex_unlock(&work_mutex_2);
    }
    pthread_exit(0);
}

void *thread_function_4(void *arg) {
	while(1) {
		printf("Lendo o adc1: %d\n", adc_1.getIntValue()*1800);
		printf("Lendo o adc2: %d\n", adc_2.getIntValue()*1800);
		printf("Lendo o adc3: %d\n", adc_3.getIntValue()*1800);
		tempo_1 = adc_1.getIntValue()*1800;
		tempo_2 = adc_2.getIntValue()*1800;
		tempo_3 = adc_3.getIntValue()*1800;
		sleep(1);
	}
	pthread_exit(0);
}
