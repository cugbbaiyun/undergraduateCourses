import Foundation
import UIKit

class rankLabel: UIView{
    var labels: [UILabel] = []
    let height:CGFloat = 30
    var wwidth: CGFloat
    var strs = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    func test(){
        if ranklist.ranklist.count >= 100 {
            return
        }
        for i in 0 ..< 100 {
            var t : Int = 0
            while t == 0{
                t = Int(arc4random() % 10)
            }
            var str : String = ""
            for _ in 0 ..< t{
                let t: Int = ( Int(arc4random()) % Int(strs.count))
                var j = 0;
                for c in strs {
                    if  j == t{
                        str.append(c)
                        break
                    }
                    j += 1
                }
            }
            let _ = ranklist.addMan(name: str, score: i)
            ranklist.sortbyscoredown()
            for  c in 0 ..< ranklist.ranklist.count {
                ranklist.ranklist[c].rk = c + 1
            }
        }
    }
    func readd(){
        var i: Int = 0
        while i < ranklist.ranklist.count {
            let rk = UILabel(frame: CGRect(x: CGFloat(0), y: CGFloat( CGFloat(i) * height ), width: CGFloat(75), height:CGFloat(30)))
            rk.textAlignment = .right
            rk.text = "\(ranklist.ranklist[i].rk)"
            rk.backgroundColor = UIColor(red: 118/255.0, green: 179/255.0, blue:157/255.0, alpha: 1.0)
            rk.textColor  = UIColor(red:5/255.0, green: 0/255.0, blue: 78/255.0, alpha: 1.0)
            super.addSubview(rk)
            let t = UILabel(frame: CGRect(x: rk.bounds.width, y: CGFloat( CGFloat(i) * height ), width: wwidth / CGFloat(2), height:CGFloat(30)))
            t.text = "\(ranklist.getName(rk:i))"
            t.textAlignment = .right
            t.backgroundColor = UIColor(red: 255.0/255.0, green: 230.0/255.0, blue:235.0/255.0, alpha:1.0)
            t.textColor = UIColor(red: 27.0/255.0, green:18.0 / 255.0, blue:15.0/255.0, alpha:1.0)
            let t2 = UILabel(frame: CGRect(x: rk.bounds.width + t.bounds.width, y: CGFloat( CGFloat(i) * height), width: wwidth / CGFloat(2),  height:CGFloat(30)))
            t2.backgroundColor = UIColor(red: 253/255.0, green: 95.0/255.0 , blue: 0/255.0, alpha: 1.0)
            t2.text = "\(ranklist.getScore(rk:i))"
            t2.textColor = UIColor(red: 249.0/255.0, green: 248.0/255.0, blue: 235.0/255.0, alpha: 1.0)
            t2.textAlignment = .right
            super.addSubview(t)
            super.addSubview(t2)
            i += 1
        }
    }
    override init(frame: CGRect){
        wwidth = frame.width
        super.init(frame:frame)
        test()
        wwidth -= 75
        readd()
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}

class rankControl: UIViewController {
    var rkup = true
    var label = rankLabel(frame: CGRect(x:0, y:0, width:0, height:0))
    var scoreup = true
    var nameup = false
    var scroll = UIScrollView(frame: CGRect(x: 0, y:0, width:0, height:0))
    init() {
        super.init(nibName: nil, bundle: nil)
    }
    override func viewDidLoad() {
        super.viewDidLoad()
        show()
    }
    func doreturn(){
        self.dismiss(animated: true, completion: nil)
    }
    @objc func hadnlereturn(_ sender: UIButton){
        doreturn()
    }
    @objc func handlerkup(_ sender: UIButton) {
        if rkup {
            ranklist.sortbyrkdown()
        } else {
            ranklist.sortbyrkup()
        }
        rkup = (!rkup)
        label.removeFromSuperview()
        label = rankLabel(frame: view.bounds)
        scroll.addSubview(label)
    }
    @objc func handlenameup(_ sender: UIButton) {
        if nameup {
            ranklist.sortbynamedown()
        } else {
            ranklist.sortbynameup()
        }
        rkup = (!nameup)
        label.removeFromSuperview()
        label = rankLabel(frame: view.bounds)
        scroll.addSubview(label)
    }
    @objc func handlescoreup(_ sender: UIButton) {
        if scoreup {
            ranklist.sortbyscoredown()
        } else {
            ranklist.sortbyscoreup()
        }
        scoreup = (!scoreup)
        label.removeFromSuperview()
        label = rankLabel(frame: view.bounds)
        scroll.addSubview(label)
    }
    func show(){
        let button = UIButton(frame: CGRect(x:0, y:20, width:60, height:20))
        button.setTitle(" <Back", for: UIControl.State())
        button.titleLabel?.textAlignment = .left
        button.contentHorizontalAlignment = .left
        button.titleLabel?.textColor = .black
        button.setTitleColor( UIColor.black, for: UIControl.State())
        button.addTarget(self, action: #selector(hadnlereturn(_:)), for: .touchUpInside)
        let title = UILabel(frame:CGRect(x:0, y:button.bounds.height, width:view.bounds.width, height: 60))
        title.text = "Rank"
        button.backgroundColor = title.backgroundColor
        title.textAlignment = .center
        title.backgroundColor = UIColor(red:235.0/255.0, green:255.0/255.0, blue:251.0/255.0, alpha:1.0)
        title.textColor = .black
        view.backgroundColor = title.backgroundColor
        title.font = UIFont(name: "Arial-ItalicMT", size: 45)
        view.addSubview(button)
        view.addSubview(title)
        view.bringSubviewToFront(button)
        let rktitle = UIButton(frame: CGRect(x:0, y: title.bounds.height + 10 , width: 50,height:30))
        rktitle.setTitle("Rank", for: UIControl.State())
        let usertitle = UIButton(frame: CGRect(x: rktitle.bounds.width, y:title.bounds.height + 10, width: (view.bounds.width - rktitle.bounds.width)/2, height:30))
        let scoretitle = UIButton(frame: CGRect(x: rktitle.bounds.width + usertitle.bounds.width, y: title.bounds.height + 10, width:usertitle.bounds.width, height: 30))
        usertitle.setTitle("Name", for: UIControl.State())
        scoretitle.setTitle("Score", for: UIControl.State())
        rktitle.contentHorizontalAlignment = .right
        usertitle.contentHorizontalAlignment = .right
        scoretitle.contentHorizontalAlignment = .right
        usertitle.setTitleColor(.black, for: UIControl.State())
        rktitle.setTitleColor(.black, for: UIControl.State())
        scoretitle.setTitleColor(.black, for: UIControl.State())
        usertitle.addTarget(self, action: #selector(handlenameup(_:)), for: .touchUpInside)
        rktitle.addTarget(self, action: #selector(handlerkup(_:)), for: .touchUpInside)
        scoretitle.addTarget(self, action: #selector(handlescoreup(_:)), for: .touchUpInside)
        usertitle.backgroundColor = title.backgroundColor
        rktitle.backgroundColor = title.backgroundColor
        scoretitle.backgroundColor = title.backgroundColor
        view.addSubview(usertitle)
        view.addSubview(scoretitle)
        view.addSubview(rktitle)
        scroll = UIScrollView(frame: CGRect(x:0, y:title.bounds.height + rktitle.bounds.height + 10, width: view.bounds.width, height: view.bounds.height - rktitle.bounds.height - title.bounds.height))
        label = rankLabel(frame: view.bounds)
        scroll.contentSize.height = CGFloat( ranklist.ranklist.count * 30)
        scroll.contentSize.width = view.bounds.width
        scroll.addSubview(label)
        scroll.isScrollEnabled = true
        scroll.showsVerticalScrollIndicator = false
        scroll.showsHorizontalScrollIndicator = true
        view.addSubview(scroll)
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}
class rank {
    var ranklist:[man] = []
    var minScore:Int = -1
    init() {
        minScore = 2
    }
    func sortbyrkup(){
        ranklist.sort(by: {(a1: man, a2: man) -> Bool in return a1.rk < a2.rk})
    }
    func sortbyrkdown(){
        ranklist.sort(by: {(a1: man, a2: man) -> Bool in return a1.rk > a2.rk})
    }
    func sortbyscoreup(){
        ranklist.sort(by: {(a1: man, a2: man) -> Bool in return a1.score < a2.score})
    }
    func sortbyscoredown(){
        ranklist.sort(by: {(a1: man, a2: man) -> Bool in return a1.score > a2.score})
    }
    func sortbynameup(){
        ranklist.sort(by: {(a1: man, a2: man) -> Bool in return a1.name < a2.name})
    }
    func sortbynamedown(){
        ranklist.sort(by: {(a1: man, a2: man) -> Bool in return a1.name > a2.name})
    }
    func getMinScore() -> Int {
        return minScore
    }
    func getName(rk:Int) -> String{
        return ranklist[rk].name
    }
    func getScore(rk: Int) -> Int {
        return ranklist[rk].score
    }
    func updateRanklist(m: man) {
        for c in ranklist {
            if c.name == m.name {
                c.score = max(c.score, m.score)
                return
            }
        }
        var _ = addMan(name: m.name, score: m.score)
    }
    func addMan(name:String, score: Int) -> Int{
        let mm = man(nn:name, ss:score)
        var back:[man] = []
        var k: Int = 0
        sortbyscoredown()
        while k < ranklist.count {
            if ranklist[k].score > score {
                back.append(ranklist[k])
            } else {
                break
            }
            k += 1
        }
        back.append(mm)
        while k < ranklist.count {
            back.append(ranklist[k])
            k += 1
        }
        k = 0
        ranklist.removeAll()
        while k < 100  && k < back.count {
            back[k].rk = k + 1
            ranklist.append(back[k])
            k += 1
        }
        return minScore
    }
}

class man{
    var name: String
    var score: Int
    var rk: Int
    func set(nn: String, ss: Int) {
        name = nn
        score = ss
    }
    init(nn: String, ss: Int){
        rk = 1000
        name = nn
        score = ss
    }
}


