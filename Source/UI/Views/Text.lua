import "UI/Views"
import "CoreLibs/graphics"

local gfx <const> = playdate.graphics

View('Text', { isLeaf = true })
function Text:init(text)
    self.text = text or ""
end
function Text:draw()
    local x, y = self:calculateDrawingPosition()
    gfx.drawTextInRect(
            self.text,
            x,
            y,
            self.node:getWidth(),
            self.node:getHeight()
    )
end