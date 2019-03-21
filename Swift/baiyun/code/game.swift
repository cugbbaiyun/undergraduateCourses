import UIKit
import Foundation

class game: UIViewController{
    var blockbuttons: [UIButton] = []
    var qqview: qView
    var pre : [[[Int]]] = []
    var rankButton : UIButton
    var returnButton: UIButton
    var changeButton: UIButton
    var maxk = 2
    var maxNumber: Int
    var timer: Timer?
    let winNumber: Int = 2048
    let boardWidth: CGFloat = 260.0
    let gapWidth: CGFloat = 3.0
    let viewPadding: CGFloat = 10.0
    let offeset: CGFloat = 0.0
    var broadx: CGFloat = 0.0
    var broady: CGFloat = 0.0
    var blockWidth: CGFloat = 0.0
    var nums = [
        [0,0,0,0],
        [0,0,0,0],
        [0,0,0,0],
        [0,0,0,0]
    ]
    func pushnums(){
        pre.append(nums)
        while pre.count > 20 {
            pre.remove(at: 0)
        }
    }
    func popnums() -> Bool {
        if pre.count  == 0 {
            return false
        } else {
            var c:[[Int]] = pre[pre.count - 1]
            clearnums()
            for i in 0 ..< 4 {
                for j in 0 ..< 4 {
                    nums[i][j] = c[i][j]
                }
            }
            var _ = pre.popLast()
        }
        clearBlobcks()
        update()
        return true
    }
    func showrank(){
        let rr = rankControl()
        self.present(rr,animated: true,completion: nil)
    }
    @objc func handlerank (_ sender: UIButton){
        showrank()
    }
    @objc func handlereturn(_ sender: UIButton){
        doreturn()
    }
    func doreturn(){
        self.dismiss(animated: true, completion: nil)
    }
    func imagePickerControllerDidCancel(picker: UIImagePickerController) {
        dismiss(animated: true, completion: nil)
    }
    @objc func handletimer(_ sender: UIButton) {
        if timer != nil {
            timer?.invalidate()
            timer = nil
        } else {
            timer = Timer.scheduledTimer(timeInterval: 1, target: self, selector: #selector(UpdateTimer), userInfo: nil, repeats: true)
            timer!.fire()
        }
    }
    func initButtons(){
        rankButton.titleLabel?.font = UIFont.systemFont(ofSize: 15)
        rankButton.titleLabel?.textAlignment = .center
        returnButton.titleLabel?.font = UIFont.systemFont(ofSize: 15)
        returnButton.titleLabel?.textAlignment = .center
        returnButton.setTitle("Exit", for: UIControl.State())
        rankButton.layer.cornerRadius = 8
        returnButton.layer.cornerRadius = 8
        returnButton.backgroundColor = UIColor(red: 240/255, green: 90/255, blue: 40/255, alpha: 1.0)
        rankButton.backgroundColor = UIColor(red: 240/255, green: 90/255, blue: 40/255, alpha: 1.0)
        rankButton.addTarget(self, action: #selector(handlerank(_:)), for: .touchUpInside)
        returnButton.addTarget(self, action: #selector(handlereturn(_:)),for: .touchUpInside)
        rankButton.setTitle("Rank", for: UIControl.State())
        changeButton.layer.cornerRadius = 8
        changeButton.backgroundColor = UIColor(red: 240/255, green: 90/255, blue: 40/255, alpha: 1.0)
        changeButton.addTarget(self, action: #selector(handletimer(_:)), for: .touchUpInside)
        changeButton.setTitle("Pause/\nContinue", for: UIControl.State())
        changeButton.titleLabel?.font = UIFont.systemFont(ofSize: 13)
        changeButton.titleLabel?.numberOfLines = 2
        changeButton.titleLabel?.textAlignment = .center
        view.addSubview(returnButton)
        view.addSubview(rankButton)
        view.addSubview(changeButton)
    }
    @objc func hanlerevoke(_ sender: UIButton){
        var _ = popnums()
        for c in blocks {
            c.removeFromSuperview()
        }
        blocks.removeAll()
        for i in 0 ..< 4 {
            for j in 0 ..< 4 {
                if nums[i][j] != 0 {
                    addBlock(value: nums[i][j], line: i, row: j)
                }
            }
        }
    }
    @objc func hanlereset(_ sender: UIButton) {
        setGame()
        qqview.clear()
    }
    @objc func handlepk(_ sender: UIButton) {
        var inputText = UITextField()
        inputText.keyboardType = .asciiCapable
        let msg = UIAlertController.init(title: "PK Rank!", message: "Input username",  preferredStyle: .alert)
        let ok = UIAlertAction.init(title:"Confirm", style: .default) {
            (action: UIAlertAction) -> () in   if (inputText.text != "") {
                let m = man(nn: inputText.text!, ss: self.qqview.score)
                ranklist.updateRanklist(m: m)
            }
        }
        let cancel = UIAlertAction.init(title:"Cancel", style: .cancel)
        msg.addAction(ok)
        msg.addAction(cancel)
        msg.addTextField(configurationHandler: {(textField) in
            inputText = textField
            inputText.placeholder = "Default user"
        })
        self.present(msg, animated: true, completion: nil)
        
    }
    @objc func handlehelp(_ sender: UIButton) {
        let t = colorChange()
        self.present(t, animated: true, completion: nil)
    }
    func initItems() {
        let revokeButton = UIButton(frame:CGRect(x:30, y:600, width: 60, height: 30))
        revokeButton.backgroundColor = UIColor(red: 240/255, green: 90/255, blue: 40/255, alpha: 1.0)
        revokeButton.setTitle("Revoke", for: UIControl.State())
        revokeButton.addTarget(self, action: #selector(hanlerevoke(_:)), for: .touchUpInside)
        revokeButton.layer.cornerRadius = 6
        let resetButton = UIButton(frame: CGRect(x:100, y: 600, width:60, height: 30))
        resetButton.backgroundColor = UIColor(red: 240/255, green: 90/255, blue: 40/255, alpha: 1.0)
        resetButton.setTitle("Reset", for: UIControl.State())
        resetButton.addTarget(self, action: #selector(hanlereset(_:)), for: .touchUpInside)
        resetButton.layer.cornerRadius = 6
        let pkButton = UIButton(frame: CGRect(x:230, y: 600, width:60, height:30))
        pkButton.setTitle("Rank PK!", for: UIControl.State())
        pkButton.addTarget(self, action: #selector(handlepk(_:)), for: .touchUpInside)
        pkButton.layer.cornerRadius = 6
        pkButton.backgroundColor = UIColor(red: 240/255, green: 90/255, blue: 40/255, alpha: 1.0)
        pkButton.titleLabel?.font = UIFont.systemFont(ofSize: 12.5)
        let helpButton = UIButton(frame: CGRect(x: 300, y: 600, width:60, height:30))
        helpButton.setTitle("Color", for: UIControl.State())
        helpButton.addTarget(self, action: #selector(handlehelp(_:)), for: .touchUpInside)
        helpButton.backgroundColor =  UIColor(red: 240/255, green: 90/255, blue: 40/255, alpha: 1.0)
        helpButton.layer.cornerRadius = 6
        for i in 0 ..< 4 {
            for j in 0 ..< 4 {
                addblockbutton(line: i, row: j)
            }
        }
        view.addSubview(helpButton)
        view.addSubview(pkButton)
        view.addSubview(resetButton)
        view.addSubview(revokeButton)
    }
    @objc func UpdateTimer() {
        qqview.incretime()
    }
    init(maxNumber t : Int){
        qqview = qView()
        timer = nil
        maxNumber = max( Int(8), t)
        rankButton = UIButton(frame: CGRect(x:250, y:55, width:65, height: 25))
        returnButton = UIButton(frame: CGRect(x:250, y:95, width:65, height: 25))
        changeButton = UIButton(frame: CGRect(x:325, y:55, width: 65, height: 65))
        super.init(nibName: nil, bundle: nil)
        timer = Timer.scheduledTimer(timeInterval: 1, target: self, selector: #selector(UpdateTimer), userInfo: nil, repeats: true)
        timer!.fire()
        initButtons()
        initListener()
        initItems()
        view.backgroundColor = viewbgcolor
    }
    var blocks: [littleblock] = []
    func getDelta(a: Int, b: Int) -> CGFloat{
        let step = gapWidth + blockWidth
        return CGFloat( CGFloat(b-a) * CGFloat(step))
    }
    
    func clearnums(){
        for i in 0 ..< 4 {
            for j in 0 ..< 4 {
                nums[i][j] = 0
            }
        }
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setGame()
    }
    func debug(){
        print(nums)
        //   print(mark)
    }
    @objc func handleup(_ recognizer:UISwipeGestureRecognizer){
        pushnums()
        var flag: Bool = false
        for i in 0 ..< 4 {
            for j in 0 ..< 4 {
                if nums[i][j] == 0 {
                    var nextj: Int = -1
                    for k in i + 1 ..< 4 {
                        if nums[k][j] != 0 {
                            nextj = k
                            nums[i][j] = nums[k][j]
                            nums[k][j] = 0
                            break
                        }
                    }
                    for k in 0 ..< blocks.count {
                        if blocks[k].line == nextj && blocks[k].row == j {
                            blocks[k].ychange = i
                            blocks[k].hasMerge = false
                        }
                    }
                    if nextj != -1 {
                        flag = true
                    }
                }
                if nums[i][j] != 0 {
                    var nextj: Int = -1
                    for k in i + 1 ..< 4 {
                        if nums[k][j] != 0 {
                            if nums[k][j] == nums[i][j] {
                                nextj = k
                                nums[i][j] = nums[i][j] * 2
                                nums[k][j] = 0
                                //mark[i][j] = 1
                            }
                            break
                        }
                    }
                    if nextj != -1 {
                        flag = true
                        for k in 0 ..< blocks.count {
                            if blocks[k].line == nextj && blocks[k].row == j {
                                blocks[k].ychange = i
                                blocks[k].hasMerge = true
                            }
                        }
                    }
                }
            }
        }
        if flag {
            yflash()
            for k in 0 ..< blocks.count {
                if blocks[k].ychange != -1 {
                    blocks[k].line = blocks[k].ychange
                    blocks[k].ychange = -1
                }
            }
            createnew()
            clearBlobcks()
            update()
        } else {
            var _ = popnums()
        }
    }
    func update(){
        for k in 0 ..< blocks.count {
            blocks[k].setNum(k: nums[blocks[k].line][blocks[k].row])
        }
        qqview.increstep()
        qqview.calScore(nums: nums)
        for c in blockbuttons {
            view.bringSubviewToFront(c)
        }
    }
    func createnew(){
        var c1: Int
        var c2: Int
        repeat {
            c1 = Int(arc4random()) % 4
            c2 = Int(arc4random()) % 4
        } while nums[c1][c2] != 0
        addBlock(value: 2, line: c1, row: c2)
    }
    
    func initListener() {
        let swipeup = UISwipeGestureRecognizer(target:self, action: #selector(handleup(_: )))
        swipeup.numberOfTouchesRequired = 1
        swipeup.direction = .up
        self.view.addGestureRecognizer(swipeup)
        let swipedown = UISwipeGestureRecognizer(target:self, action: #selector(handledown(_: )))
        swipedown.numberOfTouchesRequired = 1
        swipedown.direction = .down
        self.view.addGestureRecognizer(swipedown)
        let swipeleft = UISwipeGestureRecognizer(target:self, action: #selector(handleleft(_: )))
        swipeleft.numberOfTouchesRequired = 1
        swipeleft.direction = .left
        self.view.addGestureRecognizer(swipeleft)
        let swiperight = UISwipeGestureRecognizer(target:self, action: #selector(handleright(_: )))
        swiperight.numberOfTouchesRequired = 1
        swiperight.direction = .right
        self.view.addGestureRecognizer(swiperight)
    }
    
    func clearBlobcks(){
        var back: [littleblock] = []
        for t in blocks {
            if t.blockvalue == 0 || t.hasMerge == true || nums[t.line][t.row] == 0 {
                t.removeFromSuperview()
            } else {
                back.append(t)
            }
        }
        blocks.removeAll()
        for t in back {
            blocks.append(t)
        }
    }
    func yflash(){
        for c in blocks {
            if c.ychange != -1 {
                UIView.animate(withDuration: 0.2, delay: 0,  animations: {c.center.y -= (CGFloat(c.line - c.ychange)*CGFloat(self.gapWidth + self.blockWidth) ) }, completion: nil)
            }
        }
    }
    func xflash(){
        for c in blocks {
            if c.xchange != -1 {
                UIView.animate(withDuration: 0.2, delay: 0,  animations: {c.center.x -= (CGFloat(c.row - c.xchange)*CGFloat(self.gapWidth + self.blockWidth) ) }, completion: nil)
            }
        }
    }
    
    @objc func handledown(_ recognizer:UISwipeGestureRecognizer){
        pushnums()
        var flag: Bool = false
        let arr = [3,2,1,0]
        for i in arr  {
            for j in arr {
                if nums[i][j] == 0 {
                    var nextj: Int = -1
                    var k:Int = i - 1
                    while k > -1 {
                        if nums[k][j] != 0 {
                            nextj = k
                            nums[i][j] = nums[k][j]
                            nums[k][j] = 0
                            break
                        }
                        k -= 1
                    }
                    for k in 0 ..< blocks.count {
                        if blocks[k].line == nextj && blocks[k].row == j {
                            blocks[k].ychange = i
                            blocks[k].hasMerge = false
                        }
                    }
                    if nextj != -1 {
                        flag = true
                    }
                }
                if nums[i][j] != 0 {
                    var nextj: Int = -1
                    var k:Int = i - 1;
                    while k > -1{
                        if nums[k][j] != 0 {
                            if nums[k][j] == nums[i][j] {
                                nextj = k
                                nums[i][j] = nums[i][j] * 2
                                nums[k][j] = 0
                                //mark[i][j] = 1
                            }
                            break
                        }
                        k -= 1
                    }
                    if nextj != -1 {
                        flag = true
                        for k in 0 ..< blocks.count {
                            if blocks[k].line == nextj && blocks[k].row == j {
                                blocks[k].ychange = i
                                blocks[k].hasMerge = true
                            }
                        }
                    }
                }
            }
        }
        if flag {
            yflash()
            for k in 0 ..< blocks.count {
                if blocks[k].ychange != -1 {
                    blocks[k].line = blocks[k].ychange
                    blocks[k].ychange = -1
                }
            }
            //  merge()
            createnew()
            clearBlobcks()
            update();
        } else {
            var _ = popnums()
        }
    }
    
    @objc func handleleft(_ recognizer:UISwipeGestureRecognizer){
        pushnums()
        var flag: Bool = false
        for i in 0 ..< 4 {
            for j in 0 ..< 4 {
                if nums[i][j] == 0 {
                    var nextj: Int = -1
                    for k in j + 1 ..< 4 {
                        if nums[i][k] != 0 {
                            nextj = k
                            nums[i][j] = nums[i][k]
                            nums[i][k] = 0
                            break
                        }
                    }
                    for k in 0 ..< blocks.count {
                        if blocks[k].line == i && blocks[k].row == nextj {
                            blocks[k].xchange = j
                            blocks[k].hasMerge = false
                        }
                    }
                    if nextj != -1 {
                        flag = true
                    }
                }
                if nums[i][j] != 0 {
                    var nextj: Int = -1
                    for k in j + 1 ..< 4 {
                        if nums[i][k] != 0 {
                            if nums[i][k] == nums[i][j] {
                                nextj = k
                                nums[i][j] = nums[i][j] * 2
                                nums[i][k] = 0
                            }
                            break
                        }
                    }
                    if nextj != -1 {
                        flag = true
                        for k in 0 ..< blocks.count {
                            if blocks[k].line == i && blocks[k].row == nextj {
                                blocks[k].xchange = j
                                blocks[k].hasMerge = true
                            }
                        }
                    }
                }
            }
        }
        if flag {
            xflash()
            for k in 0 ..< blocks.count {
                if blocks[k].xchange != -1 {
                    blocks[k].row = blocks[k].xchange
                    blocks[k].xchange = -1
                }
            }
            createnew()
            clearBlobcks()
            update()
            
        } else {
            var _ = popnums()
        }
    }
    
    @objc func handleright(_ recognizer:UISwipeGestureRecognizer){
        pushnums()
        var flag: Bool = false
        let arr = [3,2,1,0]
        for i in 0 ..< 4 {
            for j in arr {
                if nums[i][j] == 0 {
                    var nextj: Int = -1
                    var k = j - 1
                    while k > -1 {
                        if nums[i][k] != 0 {
                            nextj = k
                            nums[i][j] = nums[i][k]
                            nums[i][k] = 0
                            break
                        }
                        k -= 1
                    }
                    for k in 0 ..< blocks.count {
                        if blocks[k].line == i && blocks[k].row == nextj {
                            blocks[k].xchange = j
                            blocks[k].hasMerge = false
                        }
                    }
                    if nextj != -1 {
                        flag = true
                    }
                }
                if nums[i][j] != 0 {
                    var nextj: Int = -1
                    var k = j - 1
                    while k > -1 {
                        if nums[i][k] != 0 {
                            if nums[i][k] == nums[i][j] {
                                nextj = k
                                nums[i][j] = nums[i][j] * 2
                                nums[i][k] = 0
                            }
                            break
                        }
                        k -= 1
                    }
                    if nextj != -1 {
                        flag = true
                        for k in 0 ..< blocks.count {
                            if blocks[k].line == i && blocks[k].row == nextj {
                                blocks[k].xchange = j
                                blocks[k].hasMerge = true
                            }
                        }
                    }
                }
            }
        }
        if flag {
            xflash()
            for k in 0 ..< blocks.count {
                if blocks[k].xchange != -1 {
                    blocks[k].row = blocks[k].xchange
                    blocks[k].xchange = -1
                }
            }
            createnew()
            clearBlobcks()
            update()
        } else {
            var _ = popnums()
        }
    }
    
    
    func getBlockX(value: Int) -> CGFloat {
        let step: CGFloat = gapWidth + blockWidth
        let start: CGFloat = broadx + gapWidth
        return start + CGFloat(value) * step
    }
    func getBlockY(value: Int) -> CGFloat {
        let step: CGFloat = gapWidth + blockWidth
        let start: CGFloat = broady + gapWidth
        return start + CGFloat(value) * step
    }
    func isAviliable(line:Int ,row: Int) -> Bool {
        if line < 0 || row < 0 || line >= 4 || row >= 4 {
            return false
        }
        if nums[line][row] == 0 {
            return true
        }else {
            return false
        }
    }
    @objc func hadnleblockbutton(_ sender: UIButton) {
        let sz = blocks.count
        if sz <= 1 {
            return
        }
        let row = sender.tag % 10
        let line = sender.tag / 10
        nums[line][row] = 0
        clearBlobcks()
        update()
    }
    func addblockbutton(line: Int, row: Int) {
        let xx = getBlockX(value: row)
        let yy = getBlockY(value: line)
        let bt = UIButton(frame: CGRect(x:xx, y:yy, width: blockWidth, height: blockWidth))
        bt.addTarget(self, action: #selector(hadnleblockbutton(_: )), for: .touchUpInside)
        bt.tag = line * 10 + row
        blockbuttons.append(bt)
        view.addSubview(bt)
        view.bringSubviewToFront(bt)
    }
    func addBlock( value: Int, line: Int, row: Int) {
        let blockx = getBlockX(value: row)
        let blocky = getBlockY(value: line)
        let bv = littleblock(x: blockx, y: blocky, width: blockWidth, value: value, l: line,r: row)
        super.view.addSubview(bv)
        super.view.bringSubviewToFront(bv)
        nums[line][row] = value
        blocks.append(bv)
    }
    
    
    func getViewX( subv : UIView) -> CGFloat {
        let ret = view.bounds.width - subv.bounds.width
        return (ret/2)
    }
    
    func getViewY(subv : UIView) -> CGFloat{
        let ret = view.bounds.midY - subv.bounds.height / 2
        return ret
    }
    func get2randBlock() -> [Int]{
        var nn: [Int] = [0,0,0,0]
        repeat {
            for i in 0 ..< 4 {
                let rr:Int  = Int(arc4random()) % 4
                nn[i] = rr
            }
        } while ( (nn[0] == nn[2]) && (nn[1] == nn[3]) )
        return nn
    }
    
    func setGame(){
        maxk = 2
        clearnums()
        pre.removeAll()
        view.addSubview(qqview)
        blockWidth = (boardWidth - gapWidth * CGFloat(4 + 1)) / CGFloat(4)
        let gamearea = gameBroad(d : 4, blockwidth: blockWidth, gapwidth:gapWidth, bgcolor: UIColor(red : 0x90/255, green: 0x8D/255, blue: 0x80/255, alpha: 1), forecolor:UIColor(red : 0xF9/255, green: 0xF9/255, blue: 0xE3/255, alpha: 0.5 ))
        gamearea.frame.origin.x = getViewX(subv: gamearea)
        gamearea.frame.origin.y = getViewY(subv: gamearea)
        broadx = gamearea.frame.origin.x
        broady = gamearea.frame.origin.y
        view.addSubview(gamearea)
        clearnums()
        let nn = get2randBlock()
        addBlock(value: 2, line: nn[0], row: nn[1])
        addBlock(value: 2, line: nn[2], row: nn[3])
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}

