
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "app.h"

int main(int *argc, char** argv) {

    srand(time(NULL));

    Application mainApplication;

    bool isInitialized = mainApplication.Initialize();

    if (isInitialized) {
        mainApplication.Update();
    }
    else {
        printf("[ERROR] The application has not been initialized correctly, shutting down.\n");
    }

    mainApplication.Shutdown();
    
    return 0;
}