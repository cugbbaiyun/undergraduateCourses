import Foundation
import UIKit
class qView : UIView {
    var scoreLabel : UILabel
    var stepLabel : UILabel
    var timeLabel :UILabel
    var score: Int
    var step: Int
    var time: Int
    func updateShow(){
        stepLabel.text = "     Step: \(step)"
        stepLabel.text = "     Step: \(step)"
        setScore()
    }
    func increstep() {
        step += 1
        stepLabel.text = "     Step: \(step)"
    }
    func decstep(){
        if step > 0 {
            step -= 1
            stepLabel.text = "     Step: \(step)"
        }
    }
    func incretime(){
        time += 1
        timeLabel.text = "     Time: \(time)"
    }
    func calScore(nums: [[Int]]){
        var temscore: Int = 0
        for i in 0 ..< 4{
            for j in 0 ..< 4 {
                temscore += nums[i][j]
            }
        }
        score = temscore
        setScore()
    }
    func clear(){
        score = 0
        time = 0
        step = 0
        updateShow()
    }
    func setScore(){
        let scoretext = "Score\n\(score)"
        scoreLabel.numberOfLines = 2
        let paragraphStyle:NSMutableParagraphStyle = NSMutableParagraphStyle()
        paragraphStyle.lineSpacing = 7
        let attributedString:NSMutableAttributedString = NSMutableAttributedString(string: scoretext)
        attributedString.addAttribute(NSAttributedString.Key.paragraphStyle, value: paragraphStyle, range: NSMakeRange(0, scoretext.count))
        scoreLabel.attributedText = attributedString
        scoreLabel.lineBreakMode = NSLineBreakMode.byWordWrapping
        scoreLabel.backgroundColor = UIColor(red: 240/255, green: 90/255, blue: 40/255, alpha: 1.0)
        scoreLabel.textAlignment = .center
        stepLabel.textAlignment = .left
    }
    init(){
        step = 0
        time = 0
        score = 0
        scoreLabel = UILabel(frame: CGRect(x:130, y: 20, width: 100, height: 80))
        stepLabel = UILabel(frame: CGRect(x: 0, y: 20, width: 110, height: 30))
        timeLabel = UILabel(frame: CGRect(x: 0, y: 70, width: 110, height: 30))
        stepLabel.text = "     Step: \(step)"
        stepLabel.backgroundColor = UIColor(red: 240/255, green: 90/255, blue: 40/255, alpha: 1.0)
        timeLabel.backgroundColor = UIColor(red: 240/255, green: 90/255, blue: 40/255, alpha: 1.0)
        timeLabel.text = "     Time: \(time)"
        timeLabel.textAlignment = .left
        super.init(frame: CGRect(x:0, y: 30, width: 80, height: 200))
        setScore()
        super.addSubview(stepLabel)
        super.addSubview(timeLabel)
        super.addSubview(scoreLabel)
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}

class gameBroad: UIView {
    var blockWidth: CGFloat
    var gapWidth: CGFloat
    func setColor(bgcolor:UIColor, forecolor : UIColor){
        self.backgroundColor = bgcolor
        var nowx = gapWidth
        let step = gapWidth + blockWidth
        var nowy = gapWidth
        for _ in 0 ..< 4 {
            nowx = gapWidth
            for _ in 0 ..< 4 {
                let temFrame = UIView(frame: CGRect(x: nowx,y:nowy, width: blockWidth, height: blockWidth))
                temFrame.backgroundColor = forecolor
                temFrame.layer.cornerRadius = 8
                addSubview(temFrame)
                nowx += step
            }
            nowy += step
        }
    }
    init(d: Int, blockwidth:CGFloat, gapwidth:CGFloat , bgcolor: UIColor, forecolor: UIColor){
        blockWidth = blockwidth
        gapWidth = gapwidth
        let broadWidth = CGFloat(4) * (blockWidth) + CGFloat(4 + 1) * gapWidth
        super.init(frame: CGRect(x: 0, y: 0, width: broadWidth, height: broadWidth))
        self.backgroundColor = bgcolor
        setColor(bgcolor: bgcolor, forecolor: forecolor)
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}

class littleblock: UIView {
    var hasMerge: Bool = false
    var blockvalue : Int = 0
    var line: Int = -1
    var row: Int = -1
    var xchange = -1
    var ychange = -1
    var label: UILabel
    var died = false
    func getBackgroundColor(){
        let value = blockvalue
        if value == 2{
            backgroundColor = color2
        } else if value == 4 {
            backgroundColor = color4
        } else if value == 8 {
            backgroundColor = color8
        } else if value == 16 {
            backgroundColor = color16
        } else if value == 32 {
            backgroundColor = color32
        } else if value == 64 {
            backgroundColor = color64
        } else if value == 128 {
            backgroundColor = color128
        } else if value == 256 {
            backgroundColor = color256
        } else if value == 512 {
            backgroundColor = color512
        } else if value == 1024 {
            backgroundColor = color1024
        } else if value == 2048 {
            backgroundColor = color2048
        }
    }
    
    
    func getTextColor(value: Int) -> UIColor{
        return UIColor(red: 34/255, green: 40/255, blue: 49/255, alpha: 1)
    }
    
    func setNum(k: Int){
        label.text = "\(k)"
        blockvalue = k
        getBackgroundColor()
    }
    init(x:CGFloat, y: CGFloat , width:CGFloat, value:Int, l:Int, r:Int ){
        hasMerge = false
        line = l
        row = r
        label = UILabel(frame: CGRect(x: 0, y: 0, width: width, height: width))
        super.init(frame: CGRect(x: x, y: y, width: width, height: width))
        label.textAlignment = .center
        label.minimumScaleFactor = 0.5
        label.font = UIFont(name: "Helveticaneue-Bold", size: 25)
        blockvalue = value
        label.text = "\(blockvalue)"
        getBackgroundColor()
        super.addSubview(label)
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}

