# 概要

やりっぱなしでdocker触ると忘れた頃に困るから最低限の使い方をメモっておく。

- Dockerはミドルウェアのインストールや各種環境設定をコード化して管理する
- コード化されたファイルを共有することで、どこでも誰でも同じ環境が作れる。
- 作成した環境を配布しやすい。
- スクラップ＆ビルドが容易にできる。

## 使い方

- Dockerfileを作る
- $ docker-compose build
- docker-compose.ymlをつくる
- $ docker-compose up -d
- $ docker-compose down
