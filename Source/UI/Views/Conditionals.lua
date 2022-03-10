function switch(value)
    return function (conditions)
        for k,v in pairs(conditions) do
            if k == value then
                return v
            end
        end
        if conditions.default then
            return conditions.default
        elseif value ~= false then
            print(table.concat({"Unhandled case: ", tostring(value)}))
        end
    end
end

function _if(condition)
    return function(conditions)
        return switch(condition) {
            [true] = conditions[1],
            [false] = conditions[2]
        }
    end
end