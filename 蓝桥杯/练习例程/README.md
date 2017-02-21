### 练习例程

**注意！！部分例程中调用了self.h或者lq.h，具体看例程的头文件，将包含的文件拷贝至工程目录下即可完成编译，否则会出错！**

#### led控制练习例程（LED）

* led_jiaoti.c    
>实现8个led交替亮灭

* led_water.c
>实现8个led从右往左实现单个led的流水灯点亮，最后熄灭，如此循环

* led_water2.c
>实现8个led流水灯从右往左单个点亮，实现流水灯，最后全部交替闪烁两次

#### 键盘控制例程（keyboard）

* 按键控制led亮法.c
>实现不同的按键按下显示不同的led点亮过程

* 16按键控制led亮法.c
>实现不同的按键按下显示不同的led点亮过程

#### 数码管控制例程（leds）

* leds indepandent.c
>数码管逐个显示1-F

* leds together.c
>由软件延时实现8个数码管同时显示1-F

* leds together-key16.c
>实现了由矩阵键盘控制，8位数码管同时显示按键数值

* leds together-key16-led.c
>实现了由矩阵键盘控制，8位数码管同时显示按键数值，同时led也作出相应变化

* leds dongtai.c
>数码管动态扫描（利用软件延时）

* leds dongtai-zhongduan.c
>利用定时器中断实现数码管的动态扫描

#### 蜂鸣器、继电器控制（beef）

* beef.c
>实现四个按键控制蜂鸣器和继电器，按下不同的案件控制蜂鸣器和继电器启动次数
