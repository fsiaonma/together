user
======

接口文档：
--------------

### 注册：
+ 传入参数：

>     操作代号：action=101
>     用户名：username
>     密码：password
>
>     eg: aciton=101&username=sam&password=123456

+ 返回参数：

>     请求状态码：code
>     成功标识：success
>     返回信息：msg

### 登陆：
+ 传入参数：

>     操作代号：action=102
>     用户名：username
>     密码：password
>     设备id：dev_id
>
>     eg: aciton=102&username=sam&password=123456&dev_id=123

+ 返回参数：

>     请求状态码：code
>     成功标识：success
>     返回信息：msg
>     登陆操作对应的 protobuf 信息：LoginResponse

### 登出：
+ 传入参数：

>     操作代号：action=103
>     用户名：username
>     session id: sid
>
>     eg: action=103&username=test_regiest&sid=ef9aadcea02583a798d48870e2512c7c

+ 返回参数：

>     请求状态码：code
>     成功标识：success
>     返回信息：msg

### 查看用户信息：
+ 传入参数：

>     操作代号：action=104
>     需要查看的用户的用户名：username
>     session id: sid
>
>     eg: action=104&username=tony&sid=ef9aadcea02583a798d48870e2512c7c

+ 返回参数：

>     请求状态码：code
>     成功标识：success
>     返回信息：msg
>     查看操作对应的 protobuf 信息：DetailResponse

### 设置用户信息:
+ 传入参数：

>     操作代号：action=105
>     设置用户的用户昵称（可选）：nick_name
>     设置用户的生日（可选）：birthday
>     设置用户的文字签名（可选）：signature_text
>     设置用户的录音签名 id （可选）：signature_record_id
>     session id: sid
>
>     eg: action=104&username=tony&sid=ef9aadcea02583a798d48870e2512c7c

+ 返回参数：

>     请求状态码：code
>     成功标识：success
>     返回信息：msg

### 赞操作：
+ 传入参数：

>     操作代号：action=106
>     需要赞的用户的用户名：username
>     session id: sid
>
>     eg: action=107&username=fsiaonma&sid=ef9aadcea02583a798d48870e2512c7c

+ 返回参数：

>     请求状态码：code
>     成功标识：success
>     返回信息：msg

### 关注操作：
+ 传入参数：

>     操作代号：action=107
>     需要关注的用户的用户名：username
>     session id: sid
>
>     eg: action=108&username=fsiaonma&sid=ef9aadcea02583a798d48870e2512c7c

+ 返回参数：

>     请求状态码：code
>     成功标识：success
>     返回信息：msg



用户系统功能
--------------

### V1.0.0
+ 注册登陆。
+ 查看他人的信息，查找用户信息，查看关注，查看粉丝，添加关注，取消关注。
+ 个人信息
  
>     个人头像
>     语音自我介绍和文字自我介绍
>     年龄，岁数，性别，职业，个人标签。
>     好评和差评。  

+ 发消息。
+ 自己创建的房间以及相关信息。

### 后续版本
+ 个人信息

>     荣誉值
>     经验值
>     相册
>     访问量

+ 个人动态，好友动态，好友推荐。
+ 参加过的房间 和 创建过的房间。

























