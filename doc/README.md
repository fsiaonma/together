Linux github 使用说明
====================

一. 安装 git
----------
> apt-get install git


二. 设置 SSH key
-------------

### 1.找到 SSH key
> cd ~/.ssh

### 2.生成 SSH key （https://help.github.com/articles/generating-ssh-keys）
> ssh-keygen -t rsa -C "your_email@example.com"

### 3.添加 SSH key 到 github
>     sudo apt-get install xclip
>     xclip -sel clip < ~/.ssh/id_rsa.pub
>     到 github 操作

### 4.测试
> ssh -T git@github.com


三. 开始使用
----------
> 1. 创建一本地文件夹
> 2. git init
> 3. git clone 克隆远程库
> 4. git remote add origin git@github.com/xxxxx (添加库名)
> 5. git remote rm origin (删除库名)
> 6. git pull origin (同步远程)
> 7. git status (查看文件修改状态)
> 8. git add <filename> (添加要提交的文件)
> 9. git rm <filename> （添加要删除的文件）
> 10. git commit -m "message" 提交代码
> 11. git push origin 推送代码到远程库

issue
------
### 22 端口被屏蔽解决方法 (http://www.cnblogs.com/kysnail/archive/2012/03/31/2427397.html)
### 在 ~/.ssh 文件夹中添加 config 文件，输入如下内容    

>     Host github.com
>     User xxxx@gmail.com
>     Port 443
>     Hostname ssh.github.com
>     identityfile ~/.ssh/id_rsa




