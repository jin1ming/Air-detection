package routers

import (
	"lotweb/controllers"
	"github.com/astaxie/beego"
)

func init() {
    beego.Router("/", &controllers.MainController{})
    beego.Router("/1",&controllers.Data1Controller{})
    beego.Router("/2",&controllers.Data2Controller{})
    beego.Router("/3",&controllers.Data3Controller{})
    beego.Router("/4",&controllers.Data4Controller{})
    beego.Router("/5",&controllers.Data5Controller{})

}
