# lfxSpeed

一款輕巧、快速的網速外掛程式。



<img src="docs/images/Fashion Patterns.png" alt="Fashion Patterns" />

<img src="docs/images/Efficient Mode.png" alt="Efficient Mode" />

<br>

## 目錄

- [背景](#背景)
- [編譯](#編譯)
- [安裝](#安裝)
- [卸載](#卸載)
- [使用](#使用)
- [維護者](#維護者)
- [許可協議](#許可協議)

<br>

### 背景

認為`DDE` 環境桌面很漂亮， `Deepin` 愛好者，同時也是開發者之一，看習慣了在其他系統上有一個任務欄網速外掛程式，但此 `Deepin v20 / UOS v20`上沒有，于是便有了這個項目。此適用于 `DDE` 桌面環境的 `Linux` 發行版、如 `Deepin / UOS `上。



這個倉庫的目標是：

1. 一個顯示實時網速外掛程式，且能長期維護更新
2. 一個編碼外掛程式的項目示範

<br>

### 編譯

採用 `cmake` 構建，進入源碼目錄後，執行如下：

```bash
mkdir build
cd build
cmake ..
make -j16
```

或直接使用 `IDE` 點擊構建按鈕（非運行按鈕）

<br>

### 安裝

會生成一個 `liblfxSpeed.so` 共用庫；在此路徑下執行如下：

```bash
sudo cp liblfxSpeed.so /usr/lib/dde-dock/plugins
```

<br>

### 卸載

任意路徑下執行如下：

```bash
sudo rm -rf /usr/lib/dde-dock/plugins/liblfxSpeed.so
```

<br>

### 使用

採用運行時候載入，安裝或者卸載後，都需要執行如下命令，重啟任務欄後會生效

```bash
killall dde-dock
dde-dock
```

<br>

### 維護者

[@偕臧](https://github.com/xmuli)

<br>

### 許可協議

![](https://img.shields.io/github/license/xmuli/lfxSpeed)  [MIT](LICENSE) © xmuli <偕臧>