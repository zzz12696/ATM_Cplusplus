# 模拟ATM机存取款管理系统设计
### **特别鸣谢**：[加号](https://github.com/plu-s)提供的系统逻辑设计和文件处理方案。

### 1. 问题描述：
模拟银行的自动取款机使用过程中的界面和用户交互过程。设计出主界面，实现查询银行卡余额、取款、修改密码、退出系统等功能。这一系列功能要在后台中显示出来。
### 2. 功能要求：
（1）卡号、密码输入最多三次，否则直接退出系统。
（2）取款功能：取款金额受卡余额、机单笔最大取款金额及机当前剩余金额的限制。
（3）查询功能：实现查询余额功能。
（4）更改密码：实现密码更改功能，对于密码要有2次验证。
（5）锁卡功能：实现卡被锁的功能。
（6）退卡功能：实现退出系统功能。
（7）保存功能：可将当前系统中各类记录存入文件中，存入方式任意。
（8）读取功能：可将保存在文件中的信息读入到当前系统中，供用户进行使用。

### 3. 需求分析
主要是模拟银行的自动取款机使用过程。服务的对象有ATM机和用户，用户通过银行卡进行唯一验证，才能操作属于自己的账户。所以我们不是直接面向用户，而是面向一个包含用户信息的银行卡，因此除了ATM类之外，我还设计了一个卡代理类CardAgent作为用户通过银行卡与ATM机交互的主要类。

因为测试要用到卡数据和ATM机余额数据，而卡的数据不可能在ATM机生成，因为ATM机不负责开卡，因此我新建一个工程BkgData用于生成卡数据和ATM余额数据。
### 4. 系统逻辑设计
![逻辑设计.png](https://github.com/zzz12696/ATM_Cplusplus/blob/master/Screenshots/%E9%80%BB%E8%BE%91%E8%AE%BE%E8%AE%A1.png)
### 5. 系统展示
![001_登录验证.png](https://github.com/zzz12696/ATM_Cplusplus/blob/master/Screenshots/001_%E7%99%BB%E5%BD%95%E9%AA%8C%E8%AF%81.png)
![002_取款.png](https://github.com/zzz12696/ATM_Cplusplus/blob/master/Screenshots/002_%E5%8F%96%E6%AC%BE.png)
![003_修改密码.png](https://github.com/zzz12696/ATM_Cplusplus/blob/master/Screenshots/003_%E4%BF%AE%E6%94%B9%E5%AF%86%E7%A0%81.png)
![004_锁卡.png](https://github.com/zzz12696/ATM_Cplusplus/blob/master/Screenshots/004_%E9%94%81%E5%8D%A1.png)
