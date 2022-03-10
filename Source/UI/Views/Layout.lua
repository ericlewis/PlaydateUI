import "UI/Views"

local flexDirectionColumn <const> = 0
local flexDirectionRow <const> = 2

View '_Layout'
function _Layout:init(children)
    self.children = children or {}
end

class('VStack').extends(_Layout)
function VStack:_transformNode(node)
    node:setFlexDirection(flexDirectionColumn)
end

class('HStack').extends(_Layout)
function HStack:_transformNode(node)
    node:setFlexDirection(flexDirectionRow)
end