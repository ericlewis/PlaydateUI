import "UI/Views"

local flexDirectionColumn <const> = 0
local flexDirectionRow <const> = 2

View '_Layout'
function _Layout:init(isHorizontal, children)
    self.isHorizontal = isHorizontal
    self.children = children or {}
end
function _Layout:_transformNode(node)
    if self.isHorizontal then
        node:setFlexDirection(flexDirectionRow)
    else
        node:setFlexDirection(flexDirectionColumn)
    end
end

function VStack(props)
    if type(props) == "table" then
        return _Layout(false, props)
    end

    return function(children)
        return _Layout(false, children)
    end
end

function HStack(props)
    if type(props) == "table" then
        return _Layout(true, props)
    end

    return function(children)
        return _Layout(true, children)
    end
end