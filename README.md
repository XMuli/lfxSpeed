# lfxSpeed
<p align="right"><br><a href="README.md">English</a> | <a href="README.zh_CN.md">简体中文</a> | <a href="README.zh_TW.md">繁體中文</a></p>

![](https://img.shields.io/github/license/XMuli/lfxSpeed) ![](https://img.shields.io/github/v/release/XMuli/lfxSpeed?style=flat&color=birightgreen) ![](https://img.shields.io/badge/powered%20by-XMuli-ff69b4) 

![](https://img.shields.io/github/languages/code-size/XMuli/lfxSpeed)  ![](https://img.shields.io/github/downloads/XMuli/lfxSpeed/total)  ![](https://img.shields.io/github/stars/XMuli/lfxSpeed?style=social) ![](https://img.shields.io/github/forks/XMuli/lfxSpeed?style=social&label=Fork)
<br>

A lightweight and fast Internet speed plugin. （**Recommended refactored version: [NetSpeed](https://github.com/xmuli/NetSpeed)** ）

<img src="images/lfxSpeed.gif" alt="lfxSpeed" width="70%;" />
<img src="https://fastly.jsdelivr.net/gh/XMuli/xmuliPic@pic/2024/202402192320479.png" width=70%"/>

<br>

## Contents.

- [background](#background)
- [Compile](#Compile)
- [Uninstall](#Uninstall)
- [Author](#Author)
- [Other](#Other)
- [License](#License)

<br>

### Background

I think `DDE` environment desktop is beautiful, `Deepin` lover, and also one of the developers, see used to have a taskbar net speed plugin on other systems, but not on this `Deepin v20 / UOS v20`, so I have this project. This works on `DDE` desktop environment for `Linux` distributions such as `Deepin / UOS`.
<img src="https://cdn.jsdelivr.net/gh/xmuli/xmuliPic@pic/2021/20210325_133103.png" width="50%"/>   <img src="https://cdn.jsdelivr.net/gh/xmuli/xmuliPic@pic/2021/20210325_130838.png" width="40%"/>
<br>

### Compile

Using the ``cmake`` build, after entering the source directory, execute the following.

```bash
mkdir build && cd build
cmake ..
make -j16
sudo make install
```

Or just use `IDE` to click the build button (not the run button) and copy the shared libraries manually: `sudo cp liblfxSpeed.so /usr/lib/dde-dock/plugins`.

<br>

**Note:** If it doesn't take effect, you can execute `killall dde-dock` to restart the taskbar and it will take effect

**Development Documentation:** [ifmet.cn](https://ifmet.cn/posts/c225b552) or [link](https://xmuli.blog.csdn.net/article/details/110672252)

<br>

### Uninstall

Execute the following in any path.

```bash
sudo rm -rf /usr/lib/dde-dock/plugins/liblfxSpeed.so
```

<br>

### Author

[偕臧](https://github.com/xmuli)

<br>

### Other

This project is no longer maintained; but based on its ideas and new implementation goals, the source code will be redesigned to achieve a more powerful network speed plug-in, will also provide the corresponding library to facilitate the secondary development of later, the new project in [NetSpeed](https://github.com/xmuli/NetSpeed), Wuhu ~

<br>

### License 

<img src="images/MIT.png" alt="MIT" width="15%">

This project is distributed and used based on the `MIT` protocol. For more information, see [LICENSE ](/LICENSE).
