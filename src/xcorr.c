#include "../include/xcorr.h"

void xcorr(fftw_complex * signala, fftw_complex * signalb, fftw_complex * result, int N)
{
  fftw_complex * signala_ext = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * (2 * N - 1));
  fftw_complex * signalb_ext = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * (2 * N - 1));
  fftw_complex * out_shifted = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * (2 * N - 1));
  fftw_complex * outa = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * (2 * N - 1));
  fftw_complex * outb = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * (2 * N - 1));
  fftw_complex * out = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * (2 * N - 1));
  
  fftw_plan pa = fftw_plan_dft_1d(2 * N - 1, signala_ext, outa, FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_plan pb = fftw_plan_dft_1d(2 * N - 1, signalb_ext, outb, FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_plan px = fftw_plan_dft_1d(2 * N - 1, out, out_shifted, FFTW_BACKWARD, FFTW_ESTIMATE);
  
  for (int i = 0; i < 2 * N - 1; i++)
    if(i<N)
      {
	signala_ext[i] = signala[i];
	signalb_ext[i] = signalb[i];
      }
    else
      {
	signala_ext[i] = 0;
	signalb_ext[i] = 0;
      }
  
  fftw_execute(pa);
  fftw_execute(pb);
  
  for (int i = 0; i < 2 * N - 1; i++)
    out[i] = outa[i] * conj(outb[i]);
  
  fftw_execute(px);
  
  for (int i = 0; i < 2 * N - 1; i++)
    result[i] = out_shifted[(i + N) % (2 * N - 1)] / (2 * N - 1);

  fftw_destroy_plan(pa);
  fftw_destroy_plan(pb);
  fftw_destroy_plan(px);

  fftw_free(signala_ext);
  fftw_free(signalb_ext);
  fftw_free(out_shifted);
  fftw_free(out);
  fftw_free(outa);
  fftw_free(outb);
  
  fftw_cleanup();

  return;
}
