import "UI/Views"
import "UI/Views/Root"
import "UI/Views/Layout"
import "UI/Views/Text"
import "UI/Views/Image"
import "UI/Views/Conditionals"

View('TestView', { count = 0 })
function TestView:body()
    return HStack {
        Text("Count x2: "..self.count * 2),
        VStack {
            Text(self.props.title),
            _if(self.count > 2) {
                Image("Images/SignAvoid")
            }
        }
    }
end
function TestView:buttonPressed(button)
    if button == playdate.kButtonA then
        self.count = self.count + 1
    else
        self.count = self.count - 1
    end
end

-- Counter view that increments and decrements an amount
View('ContentView', { count = 0 })
function ContentView:body()
    return HStack {
        Text("Count: "..self.count),
        TestView({title = "testing"..self.count}),
        Image("Images/SignAvoid")
    }
end
function ContentView:onAppear()
    local topStoriesCount = #json.decode(playdate.simulator.getURL("https://hacker-news.firebaseio.com/v0/topstories.json"))
    self.count = topStoriesCount
end
function ContentView:buttonPressed(button)
    if button == playdate.kButtonA then
        self.count = self.count + 1
    else
        self.count = self.count - 1
    end
end

Root(ContentView)