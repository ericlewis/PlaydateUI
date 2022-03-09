import "UI/Views"
import "UI/Views/Root"
import "UI/Views/Layout"
import "UI/Views/Text"
import "UI/Views/Image"

View('TestView', { count = 0 })
function TestView:body()
    if playdate.buttonJustReleased(playdate.kButtonA) then
        self.count = self.count + 1
    end
    if playdate.buttonJustReleased(playdate.kButtonB) then
        self.count = self.count - 1
    end
    return VStack {
        Text("Counting: " .. self.count * 2),
        Text("Counting2: " .. self.count * 3),
        HStack {
            VStack {
                Text("wee")
            },
            Text(self.props.title)
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
        Text("Count: "..self.count * 10),
        Text("Count2: "..self.count),
        TestView({title = "testing"..self.count}),
        Image("Images/SignAvoid")
    }
end

-- Create our root node & state then start listening for events.
Root(ContentView)