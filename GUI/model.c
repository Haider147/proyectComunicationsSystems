#include <math.h>
#include <stdio.h>

#define multipler 1000000
#define M 1000

void calAparametrehm(int city, int fc, double hm, double *aparametre,
                     double *consC) {
  if (fc < 2000 * multipler) {
    switch (city) {
    case 2: // Case for small and medium size city
      *aparametre = ((1.1 * log10(fc) - 0.7) * hm) - (1.56 * log10(fc) - .8);
      *consC = 0;
      break;

    case 1: // Case for metropolian city
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

int main() {
  int city = 4;             // Ejemplo de ciudad
  int fc = 900;             // Ejemplo de frecuencia
  double hm = 1.5;          // Ejemplo de altura
  double hb = 30;
  double D = 10;
  double aparametre = 0, consC = 0, A = 0, B = 0, modelOtaku = 0;
    
  for(int i = 1; i<5; i++){
      calAparametrehm(i, fc, hm, &aparametre, &consC);
      A = 69.55 + 26.16 * log10(fc) - 13.82 * log10(hb) - aparametre;
      B = 44.9 - 6.55 * log10(hb);
      modelOtaku = A + (B * log10(D)) + consC;
      printf("El modelo otaku para la ciudad %d", i);
      printf(": %f", modelOtaku);
      printf("db\n");
      
  }
  // Llamar a la función y pasar las direcciones de las variables
  
  /* A = 46.3 + 33.9*log10(fc) - 13.82*log10(hb) - aparametre;
   B = 44.9 - (6.55*log10(hb));
  A = 69.55 + 26.16 * log10(fc) - 13.82 * log10(hb) - aparametre;
  B = 44.9 - 6.55 * log10(hb);
  modelOtaku = A + (B * log10(D)) + consC;
  // Imprimir los resultados
  printf("El modelo dio para 1: %f", modelOtaku);
  printf(" db\n");*/

  return 0;
}
