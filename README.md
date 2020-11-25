# lfxSpeed
一款轻巧、快速的网速插件。



<img src="docs/images/Fashion Patterns.png" alt="Fashion Patterns" />

<img src="docs/images/Efficient Mode.png" alt="Efficient Mode" />

<br>

## 目录

- [背景](#背景)
- [编译](#编译)
- [安装](#安装)
- [卸载](#卸载)
- [使用](#使用)
- [维护者](#维护者)
- [许可协议](#许可协议)

<br>

### 背景

认为`DDE` 环境桌面很漂亮， `Deepin` 爱好者，同时也是开发者之一，看习惯了在其他系统上有一个任务栏网速插件，但此 `Deepin v20 / UOS v20`上没有，于是便有了这个项目。此适用于 `DDE` 桌面环境的 `Linux` 发行版、如 `Deepin / UOS `上。



这个仓库的目标是：

1. 一个显示实时网速插件，且能长期维护更新
2. 一个编码插件的项目示范

<br>

### 编译

采用 `cmake` 构建，进入源码目录后，执行如下：

```bash
mkdir build
cd build
cmake ..
make -j16
```

或直接使用 `IDE` 点击构建按钮（非运行按钮）

<br>

### 安装

会生成一个 `liblfxSpeed.so` 共享库；在此路径下执行如下：

```bash
sudo cp liblfxSpeed.so /usr/lib/dde-dock/plugins
```

<br>

### 卸载

任意路径下执行如下：

```bash
sudo rm -rf /usr/lib/dde-dock/plugins/liblfxSpeed.so
```

<br>

### 使用

采用运行时候加载，安装或者卸载后，都需要执行如下命令，重启任务栏后会生效

```bash
killall dde-dock
dde-dock
```

<br>

### 维护者

[@偕臧](https://github.com/xmuli)

<br>

### 许可协议

![](https://img.shields.io/github/license/xmuli/lfxSpeed)  [MIT](LICENSE) © xmuli <偕臧>

