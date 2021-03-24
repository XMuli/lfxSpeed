# lfxSpeed
<p align="right"><br><a href="README.md">English</a> | <a href="README.zh_CN.md">简体中文</a> | <a href="README.zh_TW.md">繁體中文</a></p>

 ![](https://img.shields.io/badge/language-c++-orange.svg) ![](https://img.shields.io/badge/language-Qt-orange.svg) ![](https://img.shields.io/github/license/xmuli/lfxSpeed) ![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/xmuli/lfxSpeed)  

 ![GitHub All Releases](https://img.shields.io/github/downloads/xmuli/lfxSpeed/total)  ![GitHub stars](https://img.shields.io/github/stars/xmuli/lfxSpeed?style=social) ![GitHub forks](https://img.shields.io/github/forks/xmuli/lfxSpeed?style=social) 

<br>

一款輕巧、快速的網速外掛程式。（**建议使用重构版本：[NetSpeed](https://github.com/xmuli/NetSpeed)** ）

<img src="images/lfxSpeed.gif" alt="lfxSpeed" width="70%;" />

<br>


## 目錄

- [背景](#背景)
- [編譯](#編譯)
- [卸載](#卸載)
- [更新 2021-03-24](#更新 2021-03-24)
- [作者](#作者)
- [其它](#其它)
- [協議](#協議)

<br>

### 背景

認為`DDE` 環境桌面很漂亮， `Deepin` 愛好者，同時也是開發者之一，看習慣了在其他系統上有一個任務欄網速外掛程式，但此 `Deepin v20 / UOS v20`上沒有，于是便有了這個項目。此適用于 `DDE` 桌面環境的 `Linux` 發行版、如 `Deepin / UOS `上。

<br>

<img src="images/setting.png" alt="setting" width="55%;" />   <img src="images/Author.png" alt="Author" width="40%;" />

<br>

### 編譯

採用 `cmake` 構建，進入源碼目錄後，執行如下：

```bash
mkdir build && cd build
cmake ..
make -j16
sudo make install
```

<br>

或直接使用 `IDE` 點擊構建按鈕（非運行按鈕），然後手動複製共用庫： `sudo cp liblfxSpeed.so /usr/lib/dde-dock/plugins` ；

**注意：** 若未生效，可執行 `killall dde-dock` 重啟任務欄後生效

**開發文檔：**  [ifmet.cn](https://ifmet.cn/posts/c225b552)  or [link](https://xmuli.blog.csdn.net/article/details/110672252)

<br>

### 卸載

任意路徑下執行如下：

```bash
sudo rm -rf /usr/lib/dde-dock/plugins/liblfxSpeed.so
```
<br>

### 更新 2021-03-24

下載地址： [v0.6.2](https://github.com/xmuli/lfxSpeed/releases/tag/v0.6.2) 

安裝之後建議點擊一下 “刷新” 生效，切換主題要重啟 dde-dock 生效，emmm，再應該沒啥人來報告缺陷了吧。

**修復缺陷**

- 網速單位固定寬度，不再跳動
- 使用等寬字體，默認大小為 8
- 更新版本， 替換 LOGO
- 支持暗色模式為白色字體；白色主題為暗色字體

<br>

<img src="https://cdn.jsdelivr.net/gh/xmuli/xmuliPic@pic/2021/Peek%202021-03-24%2016-54.gif" width="55%"/> <img src="https://cdn.jsdelivr.net/gh/xmuli/xmuliPic@pic/2021/20210324_165816.png" width="40%"/>

<br>


### 作者

[偕臧](https://github.com/xmuli)

<br>

### 其它：

此項目不再維護；但基于其思路和新的實現目標，源碼將會重新設計實現，一個功能更加強大的網速外掛程式，也會提供對應的庫便于後來者二次開發，新的項目在 [NetSpeed](https://github.com/xmuli/NetSpeed) ，蕪湖～

<br>

### 協議

<img src="images/MIT.png" alt="MIT" width="15%">

該項目基于 `MIT` 協議進行分發和使用。 有關更多信息，請參閱 [協議文件](/LICENSE)。