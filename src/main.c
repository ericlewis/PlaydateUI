#include "pd_api.h"
#include "yoga_bindings.h"

PlaydateAPI *pd = NULL;

#ifdef _WINDLL
__declspec(dllexport)
#endif

int eventHandler(PlaydateAPI *playdate, PDSystemEvent event, uint32_t arg) {
    if (event == kEventInitLua) {
        pd = playdate;
        registerYoga(pd);
    }
    return 0;
}
