-- state management, state can only be updated from within a body.
-- TODO: explain how this works.
local states = {}
local disallowed = {_boxUpdatedState=true,props=true,super=true,node=true}
local function _updateState(v, seed)
    for key, value in pairs(v) do
        if not disallowed[key] then
            states[seed][key] = value
        end
    end
end

local function _viewWithHydratedState(view, seed)
    table.shallowcopy(states[seed], view)
    return view
end

function _bindState(v, seed)
    local view = v
    if seed == nil then
        view._boxUpdatedState = function()
        end
        return view
    elseif states[seed] ~= nil then
        view = _viewWithHydratedState(view, seed)
    else
        states[seed] = {}
        _updateState(v, seed)
    end
    view._boxUpdatedState = function(view)
        _updateState(view, seed)
    end
    return view
end