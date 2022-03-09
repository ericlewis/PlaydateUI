//
//  array.c
//  Array
//
//  Created by Dave Hayden on 2/24/22.
//  Copyright © 2022 Panic, Inc. All rights reserved.
//

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

static YGNodeRef getNode() {
    YGNodeRef node = (YGNodeRef) pd->lua->getArgObject(1, (char *) "yoga", NULL);
    return node;
}

static YGNodeRef getChildNode() {
    YGNodeRef node = (YGNodeRef) pd->lua->getArgObject(2, (char *) "yoga", NULL);
    return node;
}

static int yoga_newObject(lua_State *L) {
    const YGNodeRef node = YGNodeNew();

    if (pd->lua->getArgCount() > 0 && pd->lua->getArgType(1, NULL) == kTypeString) {
        const char *s = pd->lua->getArgString(1);
        Context *context = (Context *) pd->system->realloc(NULL, sizeof(Context));
        context->text = s;
        YGNodeSetContext(node, context);
        YGNodeSetMeasureFunc(node, _textMeasurement);
    }

    pd->lua->pushObject(node, name, 0);

    return 1;
}

static int yoga_gc(lua_State *L) {
    const YGNodeRef node = getNode();
    if (!node) return 0;
    void* context = YGNodeGetContext(node);
    if (context != nullptr) {
        pd->system->realloc(context, 0);
        YGNodeSetContext(node, nullptr);
    }
    YGNodeFree(node);
    return 0;
}

static int yoga_freeNodes(lua_State *L) {
    const YGNodeRef node = getNode();
    if (node != NULL) {
        YGNodeFreeRecursive(node);
    }
    return 0;
}

static int yoga_getParent(lua_State *L) {
    YGNodeRef node = getNode();
    YGNodeRef parent = YGNodeGetParent(node);
    if (parent == NULL) {
        pd->lua->pushNil();
    } else {
        pd->lua->pushObject(parent, name, 0);
    }
    return 1;
}

static int yoga_getWidth(lua_State *L) {
    const YGNodeRef node = getNode();
    pd->lua->pushFloat(YGNodeLayoutGetWidth(node));
    return 1;
}

static int yoga_setWidth(lua_State *L) {
    YGNodeRef node = getNode();
    YGNodeStyleSetWidth(node, pd->lua->getArgFloat(2));
    return 0;
}

static int yoga_getHeight(lua_State *L) {
    YGNodeRef node = getNode();
    pd->lua->pushFloat(YGNodeLayoutGetHeight(node));
    return 1;
}

static int yoga_getLeft(lua_State *L) {
    YGNodeRef node = getNode();
    pd->lua->pushFloat(YGNodeLayoutGetLeft(node));
    return 1;
}

static int yoga_getTop(lua_State *L) {
    YGNodeRef node = getNode();
    pd->lua->pushFloat(YGNodeLayoutGetTop(node));
    return 1;
}

static int yoga_setHeight(lua_State *L) {
    YGNodeRef node = getNode();
    YGNodeStyleSetHeight(node, pd->lua->getArgFloat(2));
    return 0;
}

static int yoga_setFlexGrow(lua_State *L) {
    YGNodeRef node = getNode();
    YGNodeStyleSetFlexGrow(node, pd->lua->getArgFloat(2));
    return 0;
}

static int yoga_setFlexBasis(lua_State *L) {
    YGNodeRef node = getNode();
    YGNodeStyleSetFlexBasis(node, pd->lua->getArgFloat(2));
    return 0;
}

static int yoga_setFlexDirection(lua_State *L) {
    YGNodeRef node = getNode();
    YGNodeStyleSetFlexDirection(node, static_cast<YGFlexDirection>(pd->lua->getArgInt(2)));
    return 0;
}

static int yoga_setFlex(lua_State *L) {
    YGNodeRef node = getNode();
    YGNodeStyleSetFlex(node, pd->lua->getArgFloat(2));
    return 0;
}

static int yoga_setPadding(lua_State *L) {
    YGNodeRef node = getNode();
    YGNodeStyleSetPadding(node, YGEdgeLeft, pd->lua->getArgFloat(2));
    YGNodeStyleSetPadding(node, YGEdgeTop, pd->lua->getArgFloat(3));
    YGNodeStyleSetPadding(node, YGEdgeRight, pd->lua->getArgFloat(4));
    YGNodeStyleSetPadding(node, YGEdgeBottom, pd->lua->getArgFloat(5));
    return 0;
}

static int yoga_setMargin(lua_State *L) {
    YGNodeRef node = getNode();
    YGNodeStyleSetMargin(node, YGEdgeLeft, pd->lua->getArgFloat(2));
    YGNodeStyleSetMargin(node, YGEdgeTop, pd->lua->getArgFloat(3));
    YGNodeStyleSetMargin(node, YGEdgeRight, pd->lua->getArgFloat(4));
    YGNodeStyleSetMargin(node, YGEdgeBottom, pd->lua->getArgFloat(5));
    return 0;
}

static int yoga_insertChild(lua_State *L) {
    YGNodeRef node = getNode();
    YGNodeRef childNode = (YGNodeRef) pd->lua->getArgObject(2, name, NULL);
    YGNodeInsertChild(node, childNode, pd->lua->getArgInt(3));
    return 0;
}

static int yoga_removeChild(lua_State *L) {
    YGNodeRef node = getNode();
    YGNodeRef childNode = (YGNodeRef) pd->lua->getArgObject(2, name, NULL);
    YGNodeRemoveChild(node, childNode);
    return 0;
}

static int yoga_markDirty(lua_State *L) {
    YGNodeRef node = getNode();
    YGNodeMarkDirty(node);
    return 0;
}

static int yoga_isDirty(lua_State *L) {
    YGNodeRef node = getNode();
    pd->lua->pushBool(YGNodeIsDirty(node));
    return 0;
}

static int yoga_getChildCount(lua_State *L) {
    YGNodeRef node = getNode();
    pd->lua->pushInt(YGNodeGetChildCount(node));
    return 0;
}

static int yoga_calculateLayout(lua_State *L) {
    YGNodeRef node = getNode();
    YGNodeCalculateLayout(node, YGUndefined, YGUndefined, YGDirectionLTR);
    return 0;
}

static int yoga_setAlignItems(lua_State *L) {
    YGNodeRef node = getNode();
    YGNodeStyleSetAlignItems(node, static_cast<YGAlign>(pd->lua->getArgInt(2)));
    return 0;
}

static int yoga_setJustifyContent(lua_State *L) {
    YGNodeRef node = getNode();
    YGNodeStyleSetJustifyContent(node, static_cast<YGJustify>(pd->lua->getArgInt(2)));
    return 0;
}

static int yoga_setAlignContent(lua_State *L) {
    YGNodeRef node = getNode();
    YGNodeStyleSetAlignContent(node, static_cast<YGAlign>(pd->lua->getArgInt(2)));
    return 0;
}

static int yoga_appendChild(lua_State *L) {
    YGNodeRef node = getNode();
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
                {"free", yoga_freeNodes},
                {"appendChild", yoga_appendChild},
                {NULL, NULL}
        };

void registerYoga(PlaydateAPI *playdate) {
    pd = playdate;
    const char *err;
    if (!pd->lua->registerClass(name, yogaLib, NULL, 0, &err)) {
        pd->system->logToConsole("%s:%i: registerClass failed, %s", __FILE__, __LINE__, err);
    }
}
