import "UI/Internal/Render"

function Root(viewClosure)
    local handlers = {
        AButtonUp = function()
            render(viewClosure())
        end,
        BButtonUp = function()
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