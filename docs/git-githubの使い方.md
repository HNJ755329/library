# git/github の使い方

KENTAさんの動画のまとめ

- [僕のGitとGitHubの使い方を紹介します。](https://www.youtube.com/watch?v=wlY8YG-eB8E)

ローカル環境でGitHubのIssueに対応する作業ブランチをmasterブランチから作成.
（チームの方針によってはdevelopブランチから作成する場合も）
作業ブランチ名にはチームごとに決まりがあるかもしれないが,
特に決まり事がない場合には feature/add_name_column みたいな感じで,
feature/というprefixつきで作成する場合が多い.
（feature/の後ろにはその改修の簡単な概要を書く）
不具合を改修するブランチの場合は fix/というprefixをつけたりすることもあるが,
一般的にブランチ名に関してはそんなに厳しくルールを定めてない現場のほうが多い.

ローカル環境で作業が完了したら,

```shell
git status
```

で変更したファイルの一覧を見て,

```shell
git diff
```

で差分を見て,
問題がなければ,

```shell
git add -A
git commit -m
git push origin HEAD
```

を実行してGitHubのリモートブランチにpushする.

```shell
git push origin HEAD
```

を使うとブランチ名を指定しなくてもカレントブランチをリモートにpushすることができる.
コミットメッセージに関してはチームの決まりがあればそれに従う.
特に決まりがない場合は外国人の方がチームに入ってくる場合もあるので,
なるべく英語で書くようにする.

pushしたブランチからpull requestを作成して,
pull request用のテンプレートが設定されている場合はそれに必要事項を記入して,
レビューして頂きたい方たちをReviewersの欄で選択する.
この際にプルリクのコメントに,
close #Issue番号(またはIssueのURL)
を入力しておいて、プルリクがマージされた際にIssueも同時にcloseされるようにしておく.

またslackとかのチャットツールにgithubとの連携アプリをインストールしておいて
Reviewersで選択しておいた方たちに対してチャットツール上で通知がいくように
しているチームが最近は多い.

そしてレビューしてもらって改修依頼があった場合にはローカル環境で改修を加えて再度,

```shell
git add
git commit
```

した上で,

```shell
git rebase -i
```

コマンドを使ってコミットを一つにまとめた上で,

```shell
git push -f origin HEAD
```

コマンドを実行.

この際にコミットを一つにまとめない場合もあるが.
そこら辺はチームの方針に合わせるという感じ.
（タスクの精度が十分に小さければこの手法で特に問題はないと思う）

そしてGitHub上でLGTMをもらったらプルリク画面でマージを実行して完了.
という感じ.

あと最近はapprove機能を使ってレビュワーのうち誰か一人が
approveするまではマージ不可という設定にしている現場も多い.

そしてこのマージの際には大抵の現場ではリポジトリの設定で,
Automatically delete head branches
が選択してあるので,
Github上の作業branchは自動的に削除される.
また最近はそのリポジトリの設定で,
Allow squash merging
だけが選択されていることも多いので,
マージされる際には自動的にコミットが一つにまとめられるという感じになる.

Github上でマージが完了した後はローカル環境で,

```shell
git checkout master
git pull origin master
```

を実行して,
masterブランチを更新しておいて次のタスクに備えておくという感じ.

## 補足

### git stash

そのブランチで作業中の内容を一旦退避させて,
別のブランチで別のタスクに対応しなければならない場合とかも現場では結構よくあり,
こういう場合には,

```shell
git stash
```

コマンドを使い、ローカルの変更内容を一時的に退避させる.
退避させた内容をもとに戻すには下記を叩けばok.

```shell
git stash pop
```

### git reset

```shell
git reset
```

で直前のaddやcommitを取り消したい場合には,
どういうオプションを使うか等は,
メモとかにしっかり書いておいた方がよい.
詳細は
[[git reset (--hard/--soft)]ワーキングツリー、インデックス、HEADを使いこなす方法](https://qiita.com/shuntaro_tamura/items/db1aef9cf9d78db50ffe)

#### 直前のcommit取り消したい

```shell
git reset --soft HEAD^
```

#### 直前のadd取り消したい

```shell
git reset --mixed HEAD
```

もしくは

```shell
git reset HEAD
```

#### commit後の変更すべて消したい

```shell
git reset --hard HEAD
```

#### まちがえてgit resetしちゃったら

```shell
git reset --hard ORIG_HEAD
```

をすればOK.

### コンフリクト

一人での開発ではなかなか遭遇できないのがコンフリクトだが,
将来的にチーム開発に参加した際には必ず生じる.
その際にコンフリクトの解消経験がないと相当テンパってしまうので,
自分であえて発生させてコンフリクトの解消を練習しておくと良い.

## LINK

- [僕のGitとGitHubの使い方を紹介します。](https://www.youtube.com/watch?v=wlY8YG-eB8E)

- [[git reset (--hard/--soft)]ワーキングツリー、インデックス、HEADを使いこなす方法](https://qiita.com/shuntaro_tamura/items/db1aef9cf9d78db50ffe)
