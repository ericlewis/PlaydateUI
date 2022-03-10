import "UI/Views"
import "CoreLibs/graphics"

local gfx <const> = playdate.graphics

_LeafView('Image', { isLeaf = true })
function Image:init(path)
    self.path = path
    self.imageSize = table.pack(gfx.imageSizeAtPath(path))
end
function Image:_transformNode(node)
    local width, height = table.unpack(self.imageSize)
    node:setWidth(width)
    node:setHeight(height)
end
function Image:draw()
    local bounds = self:_getComputedLayout()
    local image = gfx.image.new(self.path)
    image:draw(bounds.x, bounds.y)
end