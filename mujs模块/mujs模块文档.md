# js引擎

- [js引擎](#js引擎)
    - [调试输出](#调试输出)
    - [获取日期](#获取日期)
    - [eq类](#eq类)
      - [输出文本到控制台](#输出文本到控制台)
      - [发送QQ私聊消息](#发送qq私聊消息)
      - [发送QQ群聊消息](#发送qq群聊消息)
      - [获取操作系统名称](#获取操作系统名称)
      - [获取CPU占用率](#获取cpu占用率)
      - [获取内存占用率](#获取内存占用率)
      - [获取总内存大小](#获取总内存大小)
      - [获取已经使用的内存大小](#获取已经使用的内存大小)
      - [获取CPU名称](#获取cpu名称)
      - [获取BDS启动状态](#获取bds启动状态)
      - [获取当前加载的地图名称](#获取当前加载的地图名称)
      - [获取BDS配置项(server.properties内容)](#获取bds配置项serverproperties内容)
      - [执行BDS控制台命令](#执行bds控制台命令)

建议事先使用``mujs调试器.exe``进行调试，确认能运行后再输入到面板里面

这个调试器就在面板目录下，直接双击打开

>⚠注意：\
1.js引擎支持的语法为ES5。\
2.setInterval()setTimeout()等Window对象下的语句均不支持(因为需要尽快执行完脚本)。\
3.为了避免死循环，尽量避免使用while循环，如要使用，务必加上计数变量并且在循环的开头加上计数break的判断！\
4.正则匹配到的文本将保存在全局文本变量regularTxt里面，正则匹配到的子匹配项保存在一个全局数组regularTxtList里面。\
5.换行符是``\r\n``\
6.js引擎为严格模式，每一个命令后面需要加分号，请不要使用隐式变量声明等操作，if等代码块无论多短都必须使用{}括起来。\
7.js引擎天然阻止混淆后的代码运行，请不要混淆你的js代码。

下面是详细的API和接口：

### 调试输出

``console.log``、``eq.log``，这两个命令都能将文本输出到命令行

``eq.log("hello world!");``

>⚠注意：\
输出的信息会被当成由BDS产生的信息处理，并且会被正则匹配！\
一定要注意，⚠不要形成死循环！！！

### 获取日期

见下面的示例程序
```
var t=new Date();
eq.log("日期:"+t.toLocaleDateString());
eq.log("年:"+t.getFullYear());
eq.log("月:"+t.getMonth());
eq.log("日:"+t.getDate());
eq.log("时间:"+t.toLocaleTimeString());
eq.log("星期:"+t.getDay());
eq.log("小时:"+t.getHours());
eq.log("分钟:"+t.getMinutes());
eq.log("秒:"+t.getSeconds());
eq.log("毫秒:"+t.getMilliseconds());
eq.log("13位时间戳:"+t.getTime());
```
输出结果：
```
日期:2022-07-19
年:2022
月:6
日:19
时间:12:05:03.498+08:00
星期:2
小时:12
分钟:5
秒:3
毫秒:498
13位时间戳:1658203503498
```

### eq类

#### 输出文本到控制台

``eq.log(text);``

+ 参数：
  + text: ``String``

    待输出的文本

+ 返回值：无

+ 返回值类型：``Null``

#### 发送QQ私聊消息

``eq.sendQQP(qqnumber,text);``

+ 参数：
  + qqnumber: String

    发送目标的QQ号文本
  + text: String
    需要发送的文本

+ 返回值：无

+ 返回值类型：``Null``

#### 发送QQ群聊消息

``eq.sendQQG(groupnumber,text,atQQnumber);``

+ 参数：
  + groupnumber: ``String``

    发送目标的QQ群号文本
  + text: ``String``

    需要发送的文本
  + atQQnumber: ``String``

    需要@群成员的QQ号文本，填"0"或不填表示不@，填"-1"@全体成员(需要是群管理员才能@全体成员)

+ 返回值：无

+ 返回值类型：``Null``

#### 获取操作系统名称

``eq.getOS();``

+ 参数：无

+ 返回值：返回操作系统名称，如：``Microsoft Windows 10 专业版``

+ 返回值类型：``String``

#### 获取CPU占用率

``eq.getCPUUsage();``

+ 参数：无

+ 返回值：返回CPU占用率，精确到两位小数的百分比，如：``28``

+ 返回值类型：``Integer``

#### 获取内存占用率

``eq.getMemoryUsage();``

+ 参数：无

+ 返回值：返回内存占用率，整数百分比，如：``60.66``

+ 返回值类型：``Float``

#### 获取总内存大小

``eq.getTotalRAM();``

+ 参数：无

+ 返回值：返回总内存大小，单位**KB**，如：``8320280``

+ 返回值类型：``Integer``

#### 获取已经使用的内存大小

``eq.getUsedRAM();``

+ 参数：无

+ 返回值：返回已经使用的内存大小，单位**KB**，如：``5156176``

+ 返回值类型：``Integer``

#### 获取CPU名称

``eq.getCPUName();``

+ 参数：无

+ 返回值：返回CPU的名称信息，如：``Intel(R) Core(TM) i5-9400F CPU @ 2.90GHz``

+ 返回值类型：``String``

#### 获取BDS启动状态

``eq.getStatus();``

+ 参数：无

+ 返回值：返回BDS启动状态的文本，只有两种值：``已启动/未启动``

+ 返回值类型：``String``

#### 获取当前加载的地图名称

``eq.getLevelName();``

+ 参数：无

+ 返回值：返回当前加载的地图名称文本，如：``Bedrock level``

+ 返回值类型：``String``

#### 获取BDS配置项(server.properties内容)

``eq.getBDSconfig(configName);``

+ 参数：
  + configName: ``String``

    server.properties文件配置项等号左边的部分，如：``server-name``、``allow-list``、``difficulty``

    ![图片](./images/28460930.png)

+ 返回值：返回对应配置项的内容文本，如：``Dedicated Server``、``true``、``10``。失败返回``null``

+ 返回值类型：``String/null``

#### 执行BDS控制台命令

相当于你在BDS的控制台输入指令

``eq.runcmd(cmd);``

+ 参数：

  + cmd: ``String``

    想要执行的控制台命令

+ 返回值：无

+ 返回值类型：``null``