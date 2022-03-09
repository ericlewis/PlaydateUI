import "CoreLibs/graphics"
import "State"

local gfx <const> = playdate.graphics

local flexDirectionColumn = 0
local flexDirectionRow = 2

function render(_rootView)
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
                local node = yoga.node(view.text)
                view.node = node
                parentNode:appendChild(node)
            else
                local node = yoga.node()
                view.node = node
                parentNode:appendChild(node)
            end
            table.insert(displayList, view)
        elseif view.children then
            local n = yoga.node()
            if view.className == "HStack" then
                n:setFlexDirection(flexDirectionRow)
            else
                n:setFlexDirection(flexDirectionColumn)
            end
            for idx = 1, #view.children do
                makeDisplayList(n, view.children[idx])
            end
            parentNode:appendChild(n)
        else
            local node = yoga.node()
            view.node = node
            local _view = _bindState(view, seed)
            local body = _view:body()
            -- this is also where we should call on appear if needed.
            _view:_boxUpdatedState()
            if body then
                makeDisplayList(node, body)
            end
            parentNode:appendChild(node)
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
end