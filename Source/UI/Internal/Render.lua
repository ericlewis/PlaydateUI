import "CoreLibs/graphics"
import "State"
import "Log"

local gfx <const> = playdate.graphics
local milli <const> = playdate.getCurrentTimeMilliseconds

local focusedIndex
local focusables = {}
local focusablesLocked = false
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
        seed = seed + 1
        view = view or rootView
        parentNode = parentNode or rootNode

        -- focusable
        local focusable = view.buttonPressed ~= nil
        if focusable then
            if not focusablesLocked then table.insert(focusables, seed) end
            if focusedIndex == nil or focusables[focusedIndex] == nil then
                focusedIndex = #focusables
            end
        end
        local focused = focusables[focusedIndex] == seed

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
            _view.env = { focused = (focused) }
            if _view.onAppear then _view:onAppear() end
            if focused and focusable then
                -- if we are the focused seed, then allow action through, if one was taken.
                if  playdate.buttonJustReleased(playdate.kButtonB) then
                    _view:buttonPressed(playdate.kButtonB)
                elseif playdate.buttonJustReleased(playdate.kButtonA) then
                    _view:buttonPressed(playdate.kButtonA)
                elseif playdate.buttonJustReleased(playdate.kButtonUp) then
                    focusedIndex = focusedIndex - 1
                elseif playdate.buttonJustReleased(playdate.kButtonDown) then
                    focusedIndex = focusedIndex + 1
                end
            end
            local body = _view:body()
            _view:_boxUpdatedState()
            if body then
                makeDisplayList(view.node, body)
            end
            parentNode:appendChild(view.node)
            table.insert(displayList, _view)
        end
    end
    makeDisplayList()
    focusablesLocked = true
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