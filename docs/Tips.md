# Tips

たまに使うがあまり使わないので忘れることをメモしておく．

## bashrc

~/.bashrcに気に入った処理を関数として登録しておく．
これで複雑な処理も簡単にできる．
python等で書いてもいいけどファイルの管理がめんどくなるので
規模が小さいものは.bashrcに直接かく．
OS変えるときに適当にファイルにまとめてgitで管理したい．

## vimrc

~/.vimrc
結局vimはsshかすぐ使用したいときしか使わないので
簡素なものでいい．
便利なものが必要な場合はgithub等で検索する．

## tmux

複数terminalの操作をしたい場合便利．
設定ファイル
~/.tmux.conf
byobu,screenが類似アプリ

## terminalを透過させたい

たまに透明なterminalを使いたい欲がでてくるが，
そのときには設定したことなんて忘れてる．

```
$ devilspie
```
設定ファイルは~/.devilspie/*.ds

## git

別で書く

## docker

dockerfile, docker-compose.ymlに書ききってしまって
あとはdocker-compose upで済ませる．
テスト的にやるならいいけど，コマンドにちまちま書くのはdokcerの主義に反する．

## オライリー

書籍はACM経由で読む．全部英語だけどまぁ仕方ないよね．

## CPU解析等

htop
よく使う．

## ファイル削除

$ find  ./ -regex '.*/\([a-z]\|main\).out' -deletet
正規表現を使って該当するファイルの削除

## 競技プログラミング

.bashrcによく使うoj-s-cpp,oj-t-cppを登録している．
$ oj-prepare URL
でコンテストのテストケース，テンプレートを自動で作成
過去にはaccも使っていたがojの方が使いやすい．

## Dualdisplay

```
$ xrandr
```

xrandrで画面の配置や回転を行う
