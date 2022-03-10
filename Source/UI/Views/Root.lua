import "UI/Internal/Render"

-- TODO: clean this mess up
function Root(viewClosure)
    local handlers = {
        AButtonUp = function()
            render(viewClosure())
        end,
        BButtonUp = function()
            render(viewClosure())
        end,
        upButtonUp = function()
            render(viewClosure())
        end,
        downButtonUp = function()
            render(viewClosure())
        end,
        leftButtonUp = function()
            render(viewClosure())
        end,
        rightButtonUp = function()
            render(viewClosure())
        end,
    }
    playdate.stop()
    playdate.inputHandlers.push(handlers)
    render(viewClosure()) -- begin!
end

function playdate.update()
    print("updates shouldn't run.")
end