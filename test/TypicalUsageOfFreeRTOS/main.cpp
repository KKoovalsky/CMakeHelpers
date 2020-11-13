#include "FreeRTOS.h"
#include "task.h"

#include <iostream>

int main(void)
{
    std::cout << tskKERNEL_VERSION_NUMBER << std::endl;   
    return 0;
}
