#include <iostream>

#include "common.h"
#include "FixItem.h"
#include "FixItemViewer.h"
#include "FixMsg.h"


int main(int argc, const char** argv) {
    string rawstr="8=FIX.4.4\0019=176\00135=S\00134=6\00149=BARCP\00152=20150611-08:12:58.034\001"
            "56=UOB-PRICES\0115=EUR\00155=EUR/USD\001117=1434010378_1434010378033705\001"
            "131=1d9:25: EUR/USD\001132=1.19823\001133=1.20145\001134=1000000\001135=1000000\001"
            "10=115\001";

    int num = atoi(argv[1]);
    cout << "loop num:" << num << endl;
    for(int i = 0; i < num; i++)
    {
        FixMsg msg(rawstr);
        while( msg.getNextItemViewer());
    }
    return 0;
}