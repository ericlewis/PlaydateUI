#include "yoga_bindings.h"
#include "yoga/Yoga.h"

static PlaydateAPI *pd = NULL;
static char *name = (char *) "yoga";

typedef struct {
    const char *text;
} Context;

static YGSize _textMeasurement(
        YGNodeRef node,
        float width,
        YGMeasureMode widthMode,
        float height,
        YGMeasureMode heightMode) {
    Context *p = (Context *) YGNodeGetContext(node);
    float defaultHeight = 20; // TODO: this should be measured too.
    float textWidth = pd->graphics->getTextWidth(NULL, p->text, strlen(p->text), kUTF8Encoding, 1);
    return (YGSize) {
            .width = textWidth,
            .height = defaultHeight,
    };
}

static YGNodeRef getSelfNode() {
    return (YGNodeRef) pd->lua->getArgObject(1, name, NULL);
}

static YGNodeRef getChildNode() {
    return (YGNodeRef) pd->lua->getArgObject(2, name, NULL);
}

static int yoga_newObject(lua_State *L) {
    const YGNodeRef node = YGNodeNew();

    // handle text nodes
    if (pd->lua->getArgCount() > 0 && pd->lua->getArgType(1, NULL) == kTypeString) {
        const char *text = pd->lua->getArgString(1);
        Context *context = (Context *) pd->system->realloc(NULL, sizeof(Context));
        context->text = text;
        YGNodeSetContext(node, context);
        YGNodeSetMeasureFunc(node, _textMeasurement);
    }
    pd->lua->pushObject(node, name, 0);
    return 1;
}

static int yoga_gc(lua_State *L) {
    const YGNodeRef node = getSelfNode();
    if (!node) return 0;
    void *context = YGNodeGetContext(node);
    if (context != NULL) {
        pd->system->realloc(context, 0);
        YGNodeSetContext(node, NULL);
    }
    YGNodeFree(node);
    return 0;
}

static int yoga_getParent(lua_State *L) {
    YGNodeRef parentNode = YGNodeGetParent(getSelfNode());
    if (parentNode == NULL) {
        pd->lua->pushNil();
    } else {
        pd->lua->pushObject(parentNode, name, 0);
    }
    return 1;
}

static int yoga_getWidth(lua_State *L) {
    pd->lua->pushFloat(YGNodeLayoutGetWidth(getSelfNode()));
    return 1;
}

static int yoga_setWidth(lua_State *L) {
    YGNodeStyleSetWidth(getSelfNode(),
                        pd->lua->getArgFloat(2));
    return 0;
}

static int yoga_getHeight(lua_State *L) {
    pd->lua->pushFloat(YGNodeLayoutGetHeight(getSelfNode()));
    return 1;
}

static int yoga_getLeft(lua_State *L) {
    pd->lua->pushFloat(YGNodeLayoutGetLeft(getSelfNode()));
    return 1;
}

static int yoga_getTop(lua_State *L) {
    pd->lua->pushFloat(YGNodeLayoutGetTop(getSelfNode()));
    return 1;
}

static int yoga_setHeight(lua_State *L) {
    YGNodeStyleSetHeight(getSelfNode(),
                         pd->lua->getArgFloat(2));
    return 0;
}

static int yoga_setFlexGrow(lua_State *L) {
    YGNodeStyleSetFlexGrow(getSelfNode(),
                           pd->lua->getArgFloat(2));
    return 0;
}

static int yoga_setFlexBasis(lua_State *L) {
    YGNodeStyleSetFlexBasis(getSelfNode(),
                            pd->lua->getArgFloat(2));
    return 0;
}

static int yoga_setFlexDirection(lua_State *L) {
    YGNodeStyleSetFlexDirection(getSelfNode(), (pd->lua->getArgInt(2)));
    return 0;
}

static int yoga_setFlex(lua_State *L) {
    YGNodeStyleSetFlex(getSelfNode(),
                       pd->lua->getArgFloat(2));
    return 0;
}

static int yoga_setPadding(lua_State *L) {
    YGNodeRef node = getSelfNode();
    YGNodeStyleSetPadding(node, YGEdgeLeft, pd->lua->getArgFloat(2));
    YGNodeStyleSetPadding(node, YGEdgeTop, pd->lua->getArgFloat(3));
    YGNodeStyleSetPadding(node, YGEdgeRight, pd->lua->getArgFloat(4));
    YGNodeStyleSetPadding(node, YGEdgeBottom, pd->lua->getArgFloat(5));
    return 0;
}

static int yoga_setMargin(lua_State *L) {
    YGNodeRef node = getSelfNode();
    YGNodeStyleSetMargin(node, YGEdgeLeft, pd->lua->getArgFloat(2));
    YGNodeStyleSetMargin(node, YGEdgeTop, pd->lua->getArgFloat(3));
    YGNodeStyleSetMargin(node, YGEdgeRight, pd->lua->getArgFloat(4));
    YGNodeStyleSetMargin(node, YGEdgeBottom, pd->lua->getArgFloat(5));
    return 0;
}

static int yoga_insertChild(lua_State *L) {
    YGNodeInsertChild(getSelfNode(),
                      getChildNode(),
                      pd->lua->getArgInt(3));
    return 0;
}

static int yoga_removeChild(lua_State *L) {
    YGNodeRemoveChild(getSelfNode(), getChildNode());
    return 0;
}

static int yoga_markDirty(lua_State *L) {
    YGNodeMarkDirty(getSelfNode());
    return 0;
}

static int yoga_isDirty(lua_State *L) {
    pd->lua->pushBool(YGNodeIsDirty(getSelfNode()));
    return 0;
}

static int yoga_getChildCount(lua_State *L) {
    pd->lua->pushInt(YGNodeGetChildCount(getSelfNode()));
    return 0;
}

static int yoga_calculateLayout(lua_State *L) {
    YGNodeRef node = getSelfNode();
    YGNodeCalculateLayout(node,
                          YGUndefined,
                          YGUndefined,
                          YGDirectionLTR);
    return 0;
}

static int yoga_setAlignItems(lua_State *L) {
    YGNodeStyleSetAlignItems(getSelfNode(), (pd->lua->getArgInt(2)));
    return 0;
}

static int yoga_setJustifyContent(lua_State *L) {
    YGNodeStyleSetJustifyContent(getSelfNode(), (pd->lua->getArgInt(2)));
    return 0;
}

static int yoga_setAlignContent(lua_State *L) {
    YGNodeStyleSetAlignContent(getSelfNode(), (pd->lua->getArgInt(2)));
    return 0;
}

static int yoga_appendChild(lua_State *L) {
    YGNodeRef node = getSelfNode();
    YGNodeRef childNode = getChildNode();
    YGNodeInsertChild(node, childNode, YGNodeGetChildCount(node));
    return 0;
}

static const lua_reg yogaLib[] =
        {
                {"node",              yoga_newObject},
                {"__gc",              yoga_gc},
                {"setWidth",          yoga_setWidth},
                {"setHeight",         yoga_setHeight},
                {"getWidth",          yoga_getWidth},
                {"getHeight",         yoga_getHeight},
                {"getTop",            yoga_getTop},
                {"getLeft",           yoga_getLeft},
                {"setFlexGrow",       yoga_setFlexGrow},
                {"setFlexBasis",      yoga_setFlexBasis},
                {"setFlex",           yoga_setFlex},
                {"insertChild",       yoga_insertChild},
                {"removeChild",       yoga_removeChild},
                {"setMargin",         yoga_setMargin},
                {"markDirty",         yoga_markDirty},
                {"isDirty",           yoga_isDirty},
                {"getChildCount",     yoga_getChildCount},
                {"calculateLayout",   yoga_calculateLayout},
                {"setFlexDirection",  yoga_setFlexDirection},
                {"getParent",         yoga_getParent},
                {"setAlignItems",     yoga_setAlignItems},
                {"setJustifyContent", yoga_setJustifyContent},
                {"setAlignContent",   yoga_setAlignContent},
                {"setPadding",        yoga_setPadding},
                {"appendChild",       yoga_appendChild},
                {NULL, NULL}
        };

static void* pd_malloc(size_t size) {
    return pd->system->realloc(NULL, size);
}

static void* pd_calloc(size_t count, size_t size) {
    return memset(pd_malloc(count * size), 0, count * size);
}

static void* pd_realloc(void* ptr, size_t size) {
    return pd->system->realloc(ptr, size);
}

static void pd_free(void* ptr) {
    pd->system->realloc(ptr, 0);
}

void registerYoga(PlaydateAPI *playdate) {
    pd = playdate;

    // setup yoga's memory functions
    YGSetMemoryFuncs(pd_malloc, pd_calloc, pd_realloc, pd_free);

    const char *err;
    if (!pd->lua->registerClass(name, yogaLib, NULL, 0, &err)) {
        pd->system->logToConsole("%s:%i: registerClass failed, %s", __FILE__, __LINE__, err);
    }
}
