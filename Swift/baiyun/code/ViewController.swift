import UIKit
import Photos
import UserNotifications
var ranklist = rank()
class ViewController: UIViewController {
    @objc func changecolor(_ sender: Any) {
        let color = colorChange()
        self.present(color, animated: true, completion: nil)
    }
    @objc func showrank(_ sender: Any) {
        let rank = rankControl()
        self.present(rank,animated: true, completion: nil)
    }
    @objc func tet(_ sender: Any) {
        let gm = game(maxNumber: 2048)
        self.present(gm , animated:true , completion: nil)
    }
    var time = 0
    var label4size: CGFloat = 0
    var label2 = UILabel(frame:CGRect(x: 50, y: -150, width: 100,height:100))
    var label0 = UILabel(frame:CGRect(x:150, y: -150, width: 100, height:100))
    var label4 = UILabel(frame:CGRect(x:250, y:150, width:100, height:100))
    var label8 = UILabel(frame:CGRect(x:600, y:150,width:100,height:100))
    @objc func bgrun(){
        time += 1
        if time < 150 {
            label2.center.y += 2
            self.view.bringSubviewToFront(label2)
        }else if (time < 300) {
            label0.center.y += 2
            self.view.bringSubviewToFront(label0)
        } else if(time < 370) {
            label4.font = UIFont(name: "Helvetica", size: label4size + 1)
            label4size += 1
        } else if (time < 495) {
            label8.center.x -= 2
            self.view.bringSubviewToFront(label0)
        }
    }
    func show(){
        self.view.backgroundColor = viewbgcolor
        label2.text = "2"
        label2.font = UIFont(name: "Helvetica", size: 70)
        label2.textColor = .white
        label0.text = "0"
        label0.font = UIFont(name: "Helvetica", size: 70)
        label0.textColor = .white
        label4.text = "4"
        label4.textColor = .white
        label4.font = UIFont(name: "Helvetica", size:0)
        label8.text = "8"
        label8.textColor = .white
        label8.font = UIFont(name: "Helvetica", size:70)
        self.view.addSubview(label2)
        self.view.addSubview(label4)
        self.view.addSubview(label0)
        self.view.addSubview(label8)
        let sg = UIButton.init(frame: CGRect(x: 140, y: 300, width: 120, height:50))
        let rk = UIButton.init(frame: CGRect(x: 140, y: 350, width: 120, height:50))
        let cc = UIButton.init(frame: CGRect(x: 140, y: 400, width: 120, height:50))
        sg.backgroundColor = UIColor(red:255.0/255.0, green: 233/255.0, blue: 138/255.0, alpha :1.0)
        rk.backgroundColor = UIColor(red:243/255, green: 163/255.0, blue: 51/255.0, alpha :1.0)
        cc.backgroundColor = UIColor(red:241/255, green: 104/255.0, blue: 33/255.0, alpha :1.0)
        sg.setTitleColor(UIColor(red:15/255.0, green: 10/255.0, blue: 60/255.0, alpha: 1.0), for: UIControl.State())
        sg.setTitle("Start Game", for: UIControl.State())
        rk.setTitle("Show Rank", for: UIControl.State())
        cc.setTitle("Change Color", for: UIControl.State())
        sg.addTarget(self, action: #selector(tet(_ : )), for: .touchUpInside)
        rk.addTarget(self, action: #selector(showrank(_:)), for: .touchUpInside)
        cc.addTarget(self, action: #selector(changecolor(_:)), for: .touchUpInside)
        view.addSubview(sg)
        view.addSubview(rk)
        view.addSubview(cc)
        self.view.bringSubviewToFront(label2)
        let st = Timer.scheduledTimer(timeInterval: 0.01, target: self, selector: #selector(bgrun), userInfo: nil, repeats: true)
        st.fire()
    }
    override func viewDidLoad() {
        super.viewDidLoad()
        show()
    }
}
