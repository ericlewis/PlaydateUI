import "UI/Views"

View '_Layout'
function _Layout:init(children)
    self.children = children or {}
end

class('VStack').extends(_Layout)
class('HStack').extends(_Layout)