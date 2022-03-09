import "UI/Views"
import "CoreLibs/graphics"

local gfx <const> = playdate.graphics

-- public
_LeafView('Text', { isLeaf = true })
function Text:init(text)
    self.text = text or ""
end

-- internal
function Text:draw()
    gfx.drawTextInRect(self.text, self:_getComputedLayout())
end