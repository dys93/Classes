# Classes
Cocos2d-x写的游戏

## 模块划分：
### 控制类：
* SceneManager：控制各个场景界面的跳转
### 实体类：
* MapFactory：保存游戏地图信息，对游戏框架注入具体信息
* SpriteFactory：保存单位信息，初始化单位信息
### 工具类：
* LoadAndSave：保存简单的信息，比如是否打开音效
* Toast：用于显示简单的提示，比如到达你的回合
### 场景类：
1. GameScene：游戏地图场景，包含游戏逻辑处理等部分
2. HelpLayer：帮助界面，显示简单的帮助信息
3. LoadLayer：载入界面，在游戏载入阶段显示的界面
4. MenuLayer：菜单界面，程序载入后的第一个界面
5. MusicLayer：音乐界面，设置是否打开音效以及音乐
6. ResultScene：结果界面，显示用户胜利或者失败

### 数据设定文件：
Infor.h：统一保存一些基本的数据，方便调试与修改

## 游戏界面
<img alt="游戏界面" src="https://github.com/dys93/Classes/blob/master/cocos2d.jpg" width="30%" height="30%">
