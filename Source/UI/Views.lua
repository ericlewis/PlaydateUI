import "CoreLibs/object"

class('_View', { isLeaf = false }).extends()
function _View:init(props)
    self.props = props or {}
end
function _View:calculateDrawingPosition()
    -- this would be better top down, i think.
    local left = 0
    local top = 0
    local currentNode = self.node
    while currentNode ~= nil do
        left = left + currentNode:getLeft()
        top = top + currentNode:getTop()
        currentNode = currentNode:getParent()
    end
    return left, top
end
function _View:body()
    print("must implement body.")
end

function View(name, initialState)
    class(name, initialState).extends(_View)
end