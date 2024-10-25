#include <windows.h>
#include <math.h>
#include <stdio.h>

#define multipler 1000000
#define M 1000
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

// Definir tamaño de la ventana
#define WIDTH 400
#define HEIGHT 300

// Prototipo de la función de la ventana
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

// Variables globales para los controles
HWND hDistancia, hFreq, hHb, hHm, hBotonCalcular, hSalida;

int WINAPI WinMain(HINSTANCE hInstanciaActual, HINSTANCE hInstanciaPrevia, LPSTR lpCmdLinea, int nCmdShow){

    // Estructura de la ventana
    WNDCLASSW wc = {0};
    wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInstanciaActual;
    wc.lpszClassName = L"VentanaPrincipal";
    wc.lpfnWndProc = WindowProcedure;

    // Registro de la ventana
    if (!RegisterClassW(&wc)) {
        return -1;
    }

    // Crear la ventana con el nuevo tamaño
    CreateWindowW(L"VentanaPrincipal", L"Modelo Otaku Mejorado", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                  100, 100, WIDTH, HEIGHT, NULL, NULL, hInstanciaActual, NULL);

    // Ejecutar el loop principal de mensajes
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

// Procedimiento de la ventana
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    char buffer[256];

    switch (msg) {
    case WM_CREATE:
        // Ajustes en las posiciones y tamaños de los controles
        CreateWindowW(L"Static", L"Distancia (Km):", WS_VISIBLE | WS_CHILD, 100, 50, 150, 25, hwnd, NULL, NULL, NULL);
        hDistancia = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 250, 50, 200, 25, hwnd, NULL, NULL, NULL);

        CreateWindowW(L"Static", L"Frecuencia (Mhz):", WS_VISIBLE | WS_CHILD, 100, 100, 150, 25, hwnd, NULL, NULL, NULL);
        hFreq = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 250, 100, 200, 25, hwnd, NULL, NULL, NULL);

        CreateWindowW(L"Static", L"Hb (m):", WS_VISIBLE | WS_CHILD, 100, 150, 150, 25, hwnd, NULL, NULL, NULL);
        hHb = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 250, 150, 200, 25, hwnd, NULL, NULL, NULL);

        CreateWindowW(L"Static", L"Hm (m):", WS_VISIBLE | WS_CHILD, 100, 200, 150, 25, hwnd, NULL, NULL, NULL);
        hHm = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 250, 200, 200, 25, hwnd, NULL, NULL, NULL);

        // Botón para calcular con ajuste de tamaño y posición
        hBotonCalcular = CreateWindowW(L"Button", L"Calcular", WS_VISIBLE | WS_CHILD, 200, 250, 100, 35, hwnd, (HMENU)1, NULL, NULL);

        // Área de salida para mostrar el resultado
        hSalida = CreateWindowW(L"Static", L"", WS_VISIBLE | WS_CHILD, 50, 300, 400, 50, hwnd, NULL, NULL, NULL);
        break;

    case WM_COMMAND:
        // Si se presiona el botón
        if (LOWORD(wp) == 1) {
            char distanciaStr[10], freqStr[10], hbStr[10], hmStr[10];
            GetWindowText(hDistancia, distanciaStr, 10);
            GetWindowText(hFreq, freqStr, 10);
            GetWindowText(hHb, hbStr, 10);
            GetWindowText(hHm, hmStr, 10);

            // Convertir las entradas a números
            double D = atof(distanciaStr);
            int fc = atoi(freqStr);
            double hb = atof(hbStr);
            double hm = atof(hmStr);

            // Variables de cálculo
            double aparametre = 0, consC = 0, A = 0, B = 0, modelOtaku = 0;

            // Llamar a la función de cálculo
            calAparametrehm(1, fc, hm, &aparametre, &consC);  // Ejemplo con ciudad 1
            A = 69.55 + 26.16 * log10(fc) - 13.82 * log10(hb) - aparametre;
            B = 44.9 - 6.55 * log10(hb);
            modelOtaku = A + (B * log10(D)) + consC;

            // Mostrar el resultado en la ventana
            sprintf(buffer, "Modelo Otaku: %.2f dB", modelOtaku);
            SetWindowText(hSalida, buffer);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wp, lp);
    }
    return 0;
}
