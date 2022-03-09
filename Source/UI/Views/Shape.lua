import "UI/Views"
import "CoreLibs/graphics"

local gfx <const> = playdate.graphics

-- public
_LeafView('Rectangle', { isLeaf = true })

--internal
function Rectangle:draw()
    gfx.fillRect(self:_getComputedLayout())
end