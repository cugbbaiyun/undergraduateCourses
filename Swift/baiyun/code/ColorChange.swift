import Foundation
import UIKit

class colorChange: UIViewController {
    var r: Int = 57
    var g: Int = 62
    var b: Int = 70
    var choice: Int = 0
    let rtextfield = UITextField(frame: CGRect(x:155, y: 240, width:100 ,height:30))
    let gtextfield = UITextField(frame: CGRect(x:155, y: 340, width:100 ,height:30))
    let btextfield = UITextField(frame: CGRect(x:155, y: 440, width:100 ,height:30))
    let rlabel = UILabel(frame: CGRect(x:120, y: 230, width:20, height:40))
    let glabel = UILabel(frame: CGRect(x:120, y: 330, width:20, height:40))
    let blabel = UILabel(frame: CGRect(x:120, y: 430, width:20, height:40))
    let rpre = UILabel(frame: CGRect(x: 270, y: 240, width: 30, height:30))
    let gpre = UILabel(frame: CGRect(x: 270, y:340, width: 30, height:30))
    let bpre = UILabel(frame: CGRect(x:270, y:440, width:30, height:30))
    let preLabel = UILabel(frame: CGRect(x:270, y:150, width:30, height:30))
    let choicefield = UITextField(frame: CGRect(x:155, y: 150, width:100 ,height:30))
    let choicelabel = UILabel(frame: CGRect(x:90, y: 140, width:60, height:40))
    init(){
        super.init(nibName: nil, bundle: nil)
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    @objc func handleListen(_ sender:UIButton){
        rtextfield.resignFirstResponder()
        gtextfield.resignFirstResponder()
        btextfield.resignFirstResponder()
        choicefield.resignFirstResponder()
        
        if let str = rtextfield.text {
            if str.count != 0 {
                r = Int(str)!
                rpre.backgroundColor = UIColor(red : CGFloat(r)/255.0, green:0, blue:0, alpha:1.0)
            }
        }
        if let gg = gtextfield.text {
            if gg.count != 0 {
                g = Int(gg)!
                gpre.backgroundColor = UIColor(red : 0, green: CGFloat(g)/255.0, blue:0, alpha:1.0)
            }
        }
        if let bb = btextfield.text {
            if bb.count != 0{
                b = Int(bb)!
                bpre.backgroundColor = UIColor(red : 0, green:0, blue:CGFloat(b)/255.0, alpha:1.0)
            }
        }
        if let cc = choicefield.text{
            if cc.count != 0{
                choice = Int(cc)!
            }
        }
        preLabel.backgroundColor = UIColor(red: CGFloat(r)/255.0, green: CGFloat(g)/255.0, blue: CGFloat(b)/255.0, alpha:1.0)
    }
    @objc func confirm(_ sender:UIButton){
        let nowColor = UIColor(red: CGFloat(r)/255.0, green: CGFloat(g)/255.0, blue: CGFloat(b)/255.0, alpha:1.0)
        if choice == 0 {
            viewbgcolor = nowColor
        } else if choice == 2 {
            color2 = nowColor
        } else if choice == 4 {
            color4 = nowColor
        } else if choice == 8 {
            color8 = nowColor
        } else if choice == 16 {
            color16 = nowColor
        } else if choice == 32 {
            color32 = nowColor
        } else if choice == 64 {
            color64 = nowColor
        } else if choice == 128 {
            color128 = nowColor
        } else if choice == 256 {
            color256 = nowColor
        } else if choice == 512 {
            color512 = nowColor
        } else if choice == 1024 {
            color1024 = nowColor
        } else {
            color1024 = nowColor
        }
        dismiss(animated: true, completion: nil)
    }
    @objc func cancel(_ sender:UIButton) {
        dismiss(animated: true, completion: nil)
    }
    func show(){
        let cancelButton = UIButton(frame: CGRect(x:230, y:500, width:60, height:30))
        cancelButton.setTitle("Cancel", for: UIControl.State())
        cancelButton.addTarget(self, action: #selector(cancel(_:)), for: .touchUpInside)
        let confirmButton = UIButton(frame: CGRect(x:100, y:500, width:60, height:30))
        confirmButton.layer.cornerRadius = 6
        confirmButton.setTitle( "Confirm", for: UIControl.State())
        confirmButton.titleLabel?.font = UIFont.systemFont(ofSize: 15)
        confirmButton.addTarget(self, action: #selector(confirm(_:)), for: .touchUpInside)
        preLabel.backgroundColor = viewbgcolor
        let bgButton = UIButton(frame: CGRect(x:0, y: 0, width: view.bounds.width, height:view.bounds.height))
        self.view.backgroundColor = viewbgcolor
        bgButton.addTarget(self, action: #selector(handleListen(_ :)), for: .touchUpInside)
        view.addSubview(bgButton)
        choicelabel.text = "For:"
        choicefield.placeholder = "0 for background, 2 for block 2, etc."
        choicefield.font = UIFont.systemFont(ofSize: 15)
        choicelabel.textColor = .white
        choicelabel.font = UIFont.systemFont(ofSize:30)
        choicefield.layer.cornerRadius = 6
        choicefield.backgroundColor = .white
        rlabel.text = "r:"
        rlabel.textColor = .red
        rlabel.font = UIFont.systemFont(ofSize: 30)
        glabel.text = "g:"
        glabel.textColor = .green
        glabel.font = UIFont.systemFont(ofSize: 30)
        blabel.text = "b:"
        blabel.textColor = .blue
        blabel.font = UIFont.systemFont(ofSize: 30)
        rtextfield.backgroundColor = .white
        rtextfield.placeholder = "57"
        rtextfield.layer.cornerRadius = 6
        gtextfield.placeholder = "62"
        btextfield.backgroundColor = .white
        btextfield.layer.cornerRadius = 6
        gtextfield.backgroundColor = .white
        btextfield.placeholder = "70"
        gtextfield.layer.cornerRadius = 6
        rpre.backgroundColor = UIColor(red:57 / 255, green:0, blue: 0, alpha: 1.0)
        rpre.layer.cornerRadius = 6
        gpre.backgroundColor = UIColor(red: 0, green:62/255, blue: 0, alpha: 1.0)
        bpre.backgroundColor = UIColor(red:0 , green: 0, blue: 70/255, alpha: 1.0)
        gpre.layer.cornerRadius = 6
        bpre.layer.cornerRadius = 6
        preLabel.layer.cornerRadius = 6
        rtextfield.keyboardType = .numberPad
        gtextfield.keyboardType = .numberPad
        btextfield.keyboardType = .numberPad
        choicefield.keyboardType = .numberPad
        view.addSubview(choicefield)
        view.addSubview(choicelabel)
        view.addSubview(preLabel)
        view.addSubview(rlabel)
        view.addSubview(glabel)
        view.addSubview(blabel)
        view.addSubview(rpre)
        view.addSubview(bpre)
        view.addSubview(gpre)
        view.addSubview(confirmButton)
        view.addSubview(rtextfield)
        view.addSubview(gtextfield)
        view.addSubview(btextfield)
        view.addSubview(cancelButton)
        view.bringSubviewToFront(choicefield)
        view.bringSubviewToFront(rtextfield)
        view.bringSubviewToFront(gtextfield)
        view.bringSubviewToFront(btextfield)
    }
    override func viewDidLoad() {
        super.viewDidLoad()
        show()
    }
}
