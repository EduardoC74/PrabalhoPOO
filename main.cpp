#include "interface.h"

int main(){

   auto *interface = new Interface();
   interface->Inicializa();

   delete interface;

   return 0;
}
