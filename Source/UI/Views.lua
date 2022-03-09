import "CoreLibs/object"

local rect <const> = playdate.geometry.rect

-- public
class('_View', { isLeaf = false }).extends()
function _View:init(props)
    self.props = props or {}
end

-- internal
function _View:_getComputedLayout()
    local left = 0
    local top = 0
    local currentNode = self.node
    while currentNode ~= nil do
        left = left + currentNode:getLeft()
        top = top + currentNode:getTop()
        currentNode = currentNode:getParent()
    end
    return rect.new(left, top, self.node:getWidth(), self.node:getHeight())
end

-- public
function _View:body()
    print("must implement body.")
end

-- internal
function _LeafView(name, initialState)
    class(name, table.shallowcopy({ isLeaf=true }, initialState or {})).extends(_View)
end

-- public
function View(name, initialState)
    class(name, initialState).extends(_View)
end
