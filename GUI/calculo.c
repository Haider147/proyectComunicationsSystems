#include "calculo.h"

// Definición de la función
void calAparametrehm(int city, int fc, double hm, double *aparametre, double *consC) {
  if (fc < 2000 * multipler) {
    switch (city) {
    case 2: // Case for small and medium size city
      *aparametre = ((1.1 * log10(fc) - 0.7) * hm) - (1.56 * log10(fc) - .8);
      *consC = 0;
      break;

    case 1: // Case for metropolitan city
      *consC = 0;
      if (fc <= 200) {
        *aparametre = 8.29 * (pow(log10(1.54 * hm), 2) - 1.1);
      } else if (fc >= 400) {
        *aparametre = 3.2 * (pow(log10(11.75 * hm), 2) - 4.97);
      } else {
        printf("Se equivocó pato, la frecuencia máxima es tochisima\n");
      }
      break;

    case 3: // Case for suburban environments
      *aparametre = ((1.1 * log10(fc) - 0.7) * hm) - (1.56 * log10(fc) - .8);
      *consC = -2 * (log10(fc / 28) * log10(fc / 28)) - 5.4;
      break;

    case 4: // Case for rural area
      *aparametre = ((1.1 * log10(fc) - 0.7) * hm) - (1.56 * log10(fc) - .8);
      *consC = -4.78 * (log10(fc) * log10(fc)) + 18.33 * log10(fc) - 40.78;
      break;
    }
  } else {
    printf("No se puede, alcanzó la máxima frecuencia del modelo :(\n");
  }
}
