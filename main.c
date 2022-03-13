
#include <stdlib.h>
#include "input.h"



int main() {
    struct Form form;
    inputForm(&form);

    printf("%s", form.address);
    return 0;
}

