#include "fft.h"
#include "stdio.h"
#include "math.h"
#include "fft_test_signal.h"



FFT_TYPE creat_signal_1[TEST_N1] = { 0 };
FFT_TYPE creat_signal_2[TEST_N2] = { 0 };
FFT_TYPE creat_signal_3[TEST_N3] = { 0 };
FFT_TYPE creat_signal_4[TEST_N4] = { 0 };
FFT_TYPE creat_signal_5[TEST_N5] = { 0 };
FFT_TYPE creat_signal_6[TEST_N6] = { 0 };
FFT_TYPE creat_signal_7[TEST_N7] = { 0 };
FFT_TYPE creat_signal_8[TEST_N8] = { 0 };
FFT_TYPE creat_signal_9[TEST_N9] = { 0 };
FFT_TYPE creat_signal_10[TEST_N10] = { 0 };


FFT_TYPE signal_real[N] = {
    0,5,7,9,5,3,6,4,1,21,61,51,651,612,4,9,48,97,1,21,6,12,1,61,1,1,51,26,165,1,51,1, 
    0,5,7,9,5,3,6,4,1,21,61,51,651,612,4,9,48,97,1,21,6,12,1,61,1,1,51,26,165,1,51,1,
    0,5,7,9,5,3,6,4,1,21,61,51,651,612,4,9,48,97,1,21,6,12,1,61,1,1,51,26,165,1,51,1,
    0,5,7,9,5,3,6,4,1,21,61,51,651,612,4,9,48,97,1,21,6,12,1,61,1,1,51,26,165,1,51,1
};

FFT_TYPE signal_imag[N] = { 0

};

int main( ){

    FFTinit(N);
    FFTcore(signal_real, signal_imag, N);
    IFFTinit(N);
    IFFTcore(signal_real, signal_imag, N);

    printf("-----------\r\n");
    for (size_t i = 0; i < N; ++i) { printf("<num:%3d    real:%8.4f    imag:%8.4f>\r\n", i+1, signal_real[i], signal_imag[i]); }

    return 0;
}
