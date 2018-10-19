package controllers

import (
	 "fmt"
	"github.com/astaxie/beego/orm"
	_ "github.com/go-sql-driver/mysql"
	"github.com/astaxie/beego"
)
func DBinit(datatype string) interface{}{
	orm.RegisterDataBase("default","mysql","root:12345678@tcp(localhost:3306)/LOT?charset=utf8",30)
	var maps []orm.Params
	o := orm.NewOrm()
	res,err := o.Raw("SELECT "+datatype+"  FROM KQ ORDER BY ID DESC LIMIT 1;").Values(&maps)
	if err == nil && res > 0 {
	s := maps[0][datatype]
	fmt.Println(s)
	//if v,ok := interface{}(s).(int);ok{
	return s
	//}else{
	//return -10}
}
	return 10
}

type MainController struct {
	beego.Controller
}

type Data1Controller struct {
	beego.Controller
}

func (c *Data1Controller) Get() {
	c.Data["tem"] = DBinit("tem")
	c.TplName = "1.html"
}
type Data2Controller struct {
        beego.Controller
}

func (c *Data2Controller) Get() {
        c.Data["hum"] = DBinit("hum")
        c.TplName = "2.html"
}
type Data3Controller struct {
        beego.Controller
}

func (c *Data3Controller) Get() {
        c.Data["smoke"] = DBinit("smo")
        c.TplName = "3.html"
}
type Data4Controller struct {
        beego.Controller
}

func (c *Data4Controller) Get() {
        c.Data["pm"] = DBinit("pm")
        c.TplName = "4.html"
}
type Data5Controller struct {
        beego.Controller
}

func (c *Data5Controller) Get() {
        c.Data["qua"] = DBinit("qua")
        c.TplName = "5.html"
}


func (c *MainController) Get() {
	c.Data["Website"] = "CUMT"
	c.Data["Email"] = "jin1ming@vip.qq.com"
	//c.SetStaticPath("/static")
	c.TplName = "index.html"
}
