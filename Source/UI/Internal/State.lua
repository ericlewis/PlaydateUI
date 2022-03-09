-- state management, state can only be updated from within a body.
local values = {}

local function _updateValues(v, seed)
    for key, value in pairs(v) do
        if key ~= "super" and key ~= "_boxUpdatedState" and key ~= "props" and key ~= "node" then
            values[seed][key] = value
        end
    end
end

local function _viewWithHydratedValues(view, seed)
    for key, value in pairs(values[seed]) do
        view[key] = value
    end
    return view
end

function _bindState(v, seed)
    local view = v
    if seed == nil then
        view._boxUpdatedState = function()
        end
        return view
    elseif values[seed] ~= nil then
        view = _viewWithHydratedValues(view, seed)
    else
        values[seed] = {}
        _updateValues(v, seed)
    end
    view._boxUpdatedState = function(view)
        _updateValues(view, seed)
    end
    return view
end