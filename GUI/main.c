#include "calculo.h"

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
  
  return 0;
}
