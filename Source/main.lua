import "UI/Views"
import "UI/Views/Root"
import "UI/Views/Layout"
import "UI/Views/Text"
import "UI/Views/Image"
import "UI/Views/Conditionals"

View('TestView', { count = 0 })
function TestView:body()
    if playdate.buttonJustReleased(playdate.kButtonA) then
        self.count = self.count + 1
    end
    if playdate.buttonJustReleased(playdate.kButtonB) then
        self.count = self.count - 1
    end
    return HStack {
        Text("Count x2: " .. self.count * 2),
        VStack {
            Text(self.props.title),
            Text(self.props.title),
            _if(self.count == 10) {
                Image("Images/SignAvoid")
            }
        }
    }
end

-- Counter view that increments and decrements an amount
View('ContentView', { count = 0 })
function ContentView:body()
    if playdate.buttonJustReleased(playdate.kButtonA) then
        self.count = self.count + 1
    end
    if playdate.buttonJustReleased(playdate.kButtonB) then
        self.count = self.count - 1
    end
    return HStack {
        Text("Count: "..self.count),
        TestView({title = "testing"..self.count}),
        Image("Images/SignAvoid")
    }
end

-- Create our root node & state then start listening for events.
Root(ContentView)