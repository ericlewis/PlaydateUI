#include "pd_api.h"
#include "yoga_bindings.h"

int eventHandler(PlaydateAPI *playdate, PDSystemEvent event, uint32_t arg) {
    if (event == kEventInitLua) {
        registerYoga(playdate);
    }
    return 0;
}
