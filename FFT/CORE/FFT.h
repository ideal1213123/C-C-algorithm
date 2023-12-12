#ifndef __FFT_H__
#define __FFT_H__

#define N  (128)

#define MAX_COEF_N (2048)
typedef float FFT_TYPE;
#define FFT_SWAP(a0,a1,b0,b1,t0,t1) t0=a0;t1=a1;a0=b0;a1=b1;b0=t0;b1=t1
#define COMPLEX_MULT(ra,ia,rb,ib,or,oi) or=rarb-iaib;oi=raib+iarb

void FFTinitRevs(size_t n);
void FFTinit(size_t n);
void IFFTinit(size_t n);
void FFTcore(FFT_TYPE reals, FFT_TYPE imags, size_t n);
void IFFTcore(FFT_TYPE reals, FFT_TYPE imags, size_t n);


#endif

