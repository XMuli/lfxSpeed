# lfxSpeed
<p align="right"><br><a href="README.md">English</a> | <a href="README.zh_CN.md">简体中文</a> | <a href="README.zh_TW.md">繁體中文</a></p>

A lightweight and fast Internet speed plugin. （**Recommended refactored version: [lfxNet](https://github.com/xmuli/lfxNet)** ）

<img src="images/lfxSpeed.gif" alt="lfxSpeed" width="70%;" />

<br>

## Contents.

- [background](#background)
- [Compile](#Compile)
- [Uninstall](#Uninstall)
- [Maintainer](#Maintainer)
- [License](#License)

<br>

### Background

I think `DDE` environment desktop is beautiful, `Deepin` lover, and also one of the developers, see used to have a taskbar net speed plugin on other systems, but not on this `Deepin v20 / UOS v20`, so I have this project. This works on `DDE` desktop environment for `Linux` distributions such as `Deepin / UOS`.

<br>

<img src="images/setting.png" alt="setting" width="55%;" />   <img src="images/Author.png" alt="Author" width="40%;" />

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

**Development Documentation:** [Deepin Development Taskbar Internet Speed Plugin lfxSpeed](https://xmuli.tech/posts/c225b552/) or [link](https://xmuli.blog.csdn.net/article/details/110672252)

<br>

### Uninstall

Execute the following in any path.

```bash
sudo rm -rf /usr/lib/dde-dock/plugins/liblfxSpeed.so
```

<br>

### Maintainer

[@偕臧](https://github.com/xmuli)

<br>

### Other.

This project is no longer maintained; but based on its ideas and new implementation goals, the source code will be redesigned to achieve a more powerful network speed plug-in, will also provide the corresponding library to facilitate the secondary development of later, the new project in [lfxNet](https://github.com/xmuli/lfxNet), Wuhu ~

<br>

### License 

![](https://img.shields.io/github/license/xmuli/lfxSpeed) [MIT](LICENSE) © xmuli <偕臧>
