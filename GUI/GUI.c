#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstanciaActual, HINSTANCE hInstanciaPrevia, LPSTR lpCmdLinea, int nCmdShow){

    MessageBox (NULL, "Hola pato", "Mensaje random", MB_OKCANCEL | MB_ICONQUESTION);
    return 0;
}
