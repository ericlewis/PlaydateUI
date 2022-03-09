import "UI/Views"
import "CoreLibs/graphics"

local gfx <const> = playdate.graphics

_LeafView('Rectangle', { isLeaf = true })
function Rectangle:draw()
    gfx.fillRect(self:_getComputedLayout())
end

_LeafView('RoundedRectangle', { isLeaf = true })
function RoundedRectangle:init(cornerRadius)
    self.cornerRadius = cornerRadius or 3
end
function RoundedRectangle:draw()
    gfx.fillRoundRect(self:_getComputedLayout(), self.cornerRadius)
end

_LeafView('Circle', { isLeaf = true })
function Circle:draw()
    gfx.fillCircleInRect(self:_getComputedLayout())
end