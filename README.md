# robotsystem_device_driver

8個のLEDを一つずつ制御するデバイスドライバを作成しました。

## 動作環境

Ubuntu 20.04.3 LTS

RaspberryPi4

## 使用したもの

RaspberryPi4

電源用USBケーブル　TypeC

ジャンパ線

LED

抵抗(200Ω)

## 回路・配線図
![bab479262b70244152235324d0c3639e](https://user-images.githubusercontent.com/77446351/146252630-d78beb55-0155-4534-ac2e-2a4741e0edee.png)

![IMG_9357](https://user-images.githubusercontent.com/77446351/146291218-65c515be-d98c-4922-8667-c6c15da3ecf2.jpg)

## 実行方法
### セットアップ
```
  $ git clone https://github.com/KawauchiKentarou/robotsystem_device_driver.git
```

 ```
 $ cd robotsystem_device_driver
 ```


### インストール
```
 $ make
```
```
 $ sudo insmod kadai1.ko
```
### アンインストール・デバイスファイルの削除
```
 $ sudo rmmod kadai1
```
```
 $ make clean
``` 
## 実行

### 書き込み権限付与
```
 $ sudo chmod 666 /dev/kadai10
```
### 点灯させたいLEDの番号を入力
 echoの後に0~8の数字を入力
``` 
 $ echo 1 > /dev/kadai10
```
## 実行した様子
https://youtu.be/GIAbCfO5WVQ
