# bitcoin script を検証する（理論編）

ブロックチェインが正しく繋がっていることを
計算する。

理論編
実践編
実践編（プログラミング）
実践編（アプリケーション）
https://en.bitcoin.it/wiki/Script

## UTXOはどこでかんりしてるの？

UTXO(Unspent Transaction Output)
SPVにはトランザクションの情報はない。フルノードしか管理していない。
マークルルートを使ってSPVはトランザクションの情報を確認する。

メモリプールにトランザクションを保存する。
マイニングに成功するとメモリプールからは削除される。

## トランザクションの検証

コインベースの検証。
マイニングの検証。

ScriptSig + Script Pubkeyの検証

### トランザクションの構造

### P2PKHの検証

1からはじまるアドレス

### P2SHの検証

3からはじまるアドレス

### P2WKHの検証

bcからはじまるアドレス

### P2WSHの検証

bcからはじまるアドレス

## ブロックの検証

マイナーがつなげたブロックが妥当かどうか検証する。
トランザクションを複数取り込んだものを1つのブロックとして
