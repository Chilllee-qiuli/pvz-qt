# pvz-qt
这是一个植物大战僵尸游戏的Qt移植版本

通过 game.cpp 实现游戏主体逻辑  
通过 Qt 实现图形界面和用户交互  
所有植物继承自 plant 类  
所有僵尸继承自 zombie 类  
同时攻击子弹继承自 bullet 类  
游戏包含多种植物和僵尸类型  

## 游戏刷怪
采用普通刷新+波次刷新模式
- 普通刷新
  设置发育保护和难度梯度，越往后刷出越难越多僵尸1
- 波次刷新
  封装为接口。此外增加波次只需要在 WaveCfg waveCfgs[]中设置，可以更改：触发,持续 ,总数,喷发间隔,每次喷几只, 权重等

## 植物与僵尸图鉴
  注册表存元信息 → 左侧卡片列表 → 右侧详情面板（支持 gif）→ QSS 统一换肤    
  使用QSS改写，封装为背景渲染、排版、植物图标处理多个接口，只需要打包对应信息传入即可。

## 
- 类的封装：每个类（如 zombie、plant、basiczombie 等）都封装了自身的属性和方法。
- 继承 父类 zombie 定义了所有僵尸的共同特征（如血量、攻击力、移动和攻击行为），子类（basiczombie、ConeZombie、FootballZombie 等）继承 zombie 并扩展具体实现。例如，basiczombie（普通僵尸）继承 zombie，复用了 attackPlant、moveForward 等方法，并通过构造函数初始化自身特有的属性（hp=270、speed=30.0*33/1000）。
- 多态 父类 zombie 中定义了纯虚函数（如 getHp、getAtk、advance），子类必须实现这些方法，且可以重写父类的虚函数（如 attackPlant、handleDeath）。例如，zombie 类中的 advance 方法（更新逻辑）在子类中被重写，不同僵尸的更新行为不同：普通僵尸、路障僵尸、足球僵尸的移动速度、攻击动画各不相同，但都通过 advance 接口触发。
- 抽象基类：zombie 和 plant 类是对 “僵尸” 和 “植物” 的抽象，它们定义了所有僵尸 / 植物的共同属性（如 hp、atk）和行为（如 attack、advance），但不涉及具体实现（通过纯虚函数）。例如，plant 类定义了 getInfo 纯虚函数（获取植物信息），具体实现由子类（如 thorn 地刺、potato 土豆雷）完成，体现了对 “植物信息” 这一概念的抽象。
