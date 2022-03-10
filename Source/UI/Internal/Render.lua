import "CoreLibs/graphics"
import "State"
import "Log"

local gfx <const> = playdate.graphics
local milli <const> = playdate.getCurrentTimeMilliseconds

function render(_rootView)
    local start = milli()
    gfx.clear()
    local rootNode = yoga.node()
    rootNode:setWidth(400)
    rootNode:setHeight(240)

    local displayList = {}
    local seed = 1
    local rootView = _rootView
    _rootView.node = rootNode

    function makeDisplayList(parentNode, view)
        view = view or rootView
        parentNode = parentNode or rootNode
        seed = seed + 1
        if view.isLeaf then
            if view.text then
                view.node = yoga.node(view.text)
                parentNode:appendChild(view.node)
            else
                view.node = yoga.node()
                view:_transformNode(view.node)
                parentNode:appendChild(view.node)
            end
            table.insert(displayList, view)
        elseif view.children then
            view.node = yoga.node()
            view:_transformNode(view.node)
            for idx = 1, #view.children do
                makeDisplayList(view.node, view.children[idx])
            end
            parentNode:appendChild(view.node)
        else
            view.node =  yoga.node()
            local _view = _bindState(view, seed)
            local body = _view:body()
            -- this is also where we should call on appear if needed.
            _view:_boxUpdatedState()
            if body then
                makeDisplayList(view.node, body)
            end
            parentNode:appendChild(view.node)
            table.insert(displayList, _view)
        end
    end
    makeDisplayList()
    rootNode:calculateLayout()
    for idx = 1, #displayList do
        local view = displayList[idx]
        if view.isLeaf then
            view:draw()
        end
    end
    rootNode = nil
    rootView = nil
    ui_log(table.concat({"draw took ~", (milli() - start), "ms."}))
end