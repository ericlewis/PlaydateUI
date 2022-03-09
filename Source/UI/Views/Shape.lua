import "UI/Views"
import "CoreLibs/graphics"

local gfx <const> = playdate.graphics

View('Rectangle', { isLeaf = true })
function Rectangle:draw()
    local x, y = self:calculateDrawingPosition()
    gfx.fillRect(
            x,
            y,
            self.node:getWidth(),
            self.node:getHeight()
    )
end