// Entry point for example code

#include <ch554.h>
#include <debug.h>
#include <i2c_bb.h>

void main(void) {
    CfgFsys();
    i2c_bb_init();

    while (1);
}
