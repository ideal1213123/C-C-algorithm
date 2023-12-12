#include "fft.h"
#include "stdio.h"
#include "math.h"
#include "stdlib.h"



FFT_TYPE gFFTCoefReal[MAX_COEF_N] = { 0 };
FFT_TYPE gFFTCoefImag[MAX_COEF_N] = { 0 };
unsigned short gFFTRevPos[MAX_COEF_N] = { 0 };
size_t   gFFTlim = 0;
size_t   gFFTlen = 0;

void FFTinitRevs(size_t n) {
    for (size_t i = 0; i < MAX_COEF_N; ++i) { gFFTRevPos[i] = 0; }
    size_t pos = 0;
    gFFTlen = 0;
    gFFTlim = 1;
    while (gFFTlim < n) { gFFTlim <<= 1; ++gFFTlen; }
    for (size_t i = 0; i < gFFTlim; ++i) {
        pos = (gFFTRevPos[i >> 1] >> 1) | ((i & 1) << (gFFTlen - 1));
        gFFTRevPos[i] = pos;
    }
}

void FFTinit(size_t n) {
    double FFT_2PI = 2 * acos(-1);
    for (size_t i = 0; i < n; ++i) {
        double ang = FFT_2PI * i / n;
        gFFTCoefReal[i] = cos(ang);
        gFFTCoefImag[i] = sin(ang);
    }
    FFTinitRevs(n);
}

void IFFTinit(size_t n) {
    double FFT_2PI = 2 * acos(-1);
    for (size_t i = 0; i < n; ++i) {
        double ang = -FFT_2PI * i / n;
        gFFTCoefReal[i] = cos(ang);
        gFFTCoefImag[i] = sin(ang);
    }
    FFTinitRevs(n);
}

void FFTcore(FFT_TYPE* reals, FFT_TYPE* imags, size_t n) {
    FFT_TYPE tempR = 0, tempI = 0;
    size_t pos = 0, odpos = 0;
    size_t len = gFFTlen;
    size_t lim = gFFTlim;
    for (size_t i = 0; i < lim; ++i) {
        pos = gFFTRevPos[i];
        if (i < pos) {
            FFT_SWAP(reals[i], imags[i], reals[pos], imags[pos], tempR, tempI);
        }
    }

    for (size_t dep = 1; dep <= len; ++dep) {
        size_t m = 1 << dep;
        size_t half = m >> 1;
        size_t gap = n >> dep;
        for (size_t k = 0; k < lim; k += m) {
            size_t coefIdx = 0;
            for (size_t j = 0; j < half; ++j) {
                FFT_TYPE tr = 0, ti = 0;
                FFT_TYPE ur = 0, ui = 0;
                pos = k + j;
                odpos = pos + half;

                COMPLEX_MULT(gFFTCoefReal[coefIdx], gFFTCoefImag[coefIdx], reals[odpos], imags[odpos], tr, ti);
                ur = reals[pos];
                ui = imags[pos];
                reals[pos] = ur + tr;
                imags[pos] = ui + ti;
                reals[odpos] = ur - tr;
                imags[odpos] = ui - ti;

                coefIdx += gap;
            }
        }
    }
}

void IFFTcore(FFT_TYPE* reals, FFT_TYPE* imags, size_t n) {
    FFTcore(reals, imags, n);
    double rat = 1.0 / n;
    for (size_t i = 0; i < n; ++i) {
        reals[i] *= rat;
        imags[i] *= rat;
    }
}


