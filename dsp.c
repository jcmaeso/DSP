/*
 * dsp.c
 *
 *  Created on: 22 feb. 2018
 *      Author: jcala
 */


#include "dsp.h"
#include <stdlib.h>
#include <math.h>

void oscilator(double fc,double* sin_buffer,double* cos_buffer){
	//Variables
	double* tmp_buffer;
	double k1 = tan(PI*fc/FS);
	double k2 = 2*k1/(1+k1*k1);
	int i = 1;
	//Memory
	tmp_buffer = malloc(sizeof(double)*BUFFER_SIZE);
	//Initial conditions
	*(sin_buffer) = 0;
	*(cos_buffer) = 1;
	//Loop
	for(;i < BUFFER_SIZE;i++){
		*(tmp_buffer+i-1) = *(cos_buffer+i-1) - k1* (*(sin_buffer+i-1));
		*(sin_buffer+i) = *(sin_buffer+i-1) + k2*(*(tmp_buffer+i-1));
		*(cos_buffer+i) = *(tmp_buffer+i-1) - k1*(*(sin_buffer+i));
	}
	//Free Memory
	free(tmp_buffer);
}
//Filtro que selecciona la banda de paso
void bpf_108(double* im_buffer){

}

void demodulator(double* re_buffer,double* im_buffer, double* out_buffer){
	double* h1;
	double* h2;
	double* h3;
	double* h4;
	double old_re = *(re_buffer);
	double old_im = *(im_buffer);
	double new_im;
	double new_re;
	int i = 1;

	h1 = (double*)malloc(sizeof(double)*BUFFER_SIZE);
	h2 = (double*)malloc(sizeof(double)*BUFFER_SIZE);
	h3 = (double*)malloc(sizeof(double)*BUFFER_SIZE);
	h4 = (double*)malloc(sizeof(double)*BUFFER_SIZE);

	for(; i < BUFFER_SIZE;i++){
		new_im = *(im_buffer+i);
		new_re = *(re_buffer+i);
		*(h1+i-1) = old_re * new_im;
		*(h2+i-1) = old_im * new_re;
		*(h3+i-1) = *(h1+i-1)-*(h2+i-1);
		*(h4+i-1) = asin(*(h3+i-1));
		*(out_buffer+i-1) = *(h4+i-1) * FS/KFM;
		old_im = new_im;
		old_re = new_re;
	}

	free(h1);
	free(h2);
	free(h3);
	free(h4);
}
//filtro que selecciona la emisora
void bpf_200(double* im_buffer){

}


