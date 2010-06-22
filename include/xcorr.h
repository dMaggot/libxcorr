#ifndef XCORR
#define XCORR

#include <complex.h>
#include <fftw3.h>

void xcorr(fftw_complex *, fftw_complex *, fftw_complex *, int);

#endif
