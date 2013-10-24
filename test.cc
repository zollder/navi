//// --- INCLUDE FILE
//
//#include <assert.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <sys/neutrino.h>
//#include <sys/netmgr.h>
//#include <sys/syspage.h>
//
//#include <unistd.h>
//
//// --- FUNCTION (from Bottom to Top, and/or sorted)
//
//int main( int argc, char *argv[] )
//{
//    _uint64 last_cycles=-1;
//    _uint64 current_cycles;
//    float cpu_freq;
//    time_t start;
//
//    // --- Get CPU frequency in order to do precise time calculation
//    cpu_freq =  SYSPAGE_ENTRY( qtime )->cycles_per_sec;
//    int temp =0;
//
//
//    // --- keep track of time
//    start = time(NULL);
//    while(temp++ < 10){
//        // --- should put pulse validation here ...
//        current_cycles = ClockCycles();
//
//        if ( last_cycles != -1 )    // --- don't print first iteration
//        {
//            // --- could get rid of timer by using more
//            // --- clever timer setup
//            float elapse = (current_cycles - last_cycles) / cpu_freq;
//
//            // --- printf if request is 50us longer then requested...
//            if ( elapse > .00105 )
//            {
//                printf("Elapse %f at %d\n", elapse, time(NULL)-start );
//            }
//        }
//
//        last_cycles = current_cycles;
//        delay(1000);
//    }
//}
