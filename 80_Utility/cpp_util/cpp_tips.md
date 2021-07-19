# 【C++】マクロを使った、ローカル環境のみ挙動を変えるプログラム
主に競技プログラミングのTipsとして活用。
自分の環境でのみ実行するコードを書くことで、
ローカルでテストしたコードをそのまま提出することができるようになる。

## 1. g++/gcc のオプション
オプションを使用してコンパイル時にマクロを定義する。具体的には`g++ -D`を使用。

```console
$ g++ -D=__LOCAL -g test.cpp -o test.out
```
`-D`オプションを使用することによって、`test.cpp`コードの中に`#define __LOCAL`と書かれたことと同じ挙動をする。

## 2. マクロの使用
コンパイル時に定義した変数`__LOCAL`をつかってif文を書くことによって
ローカル時のみ実行されるマクロを定義することができる。
私が個人的に利用しているのは次のフォーマット。
input.txtだけ別途用意すればよく、output.txtは自動で作成される。
別ファイルからの読み書きは他にもifstream、ofstreamを使用する方法があるが
競技プログラム提出の流用が簡単なfreopen()を使用した。

```txt:input.txt
98
```


```cpp:test.cpp
#include <bits/stdc++.h>
#ifdef __LOCAL
#define DBG(X) cout << #X << " = " << (X) << endl;
#define SAY(X) cout << (X) << endl;
#else
#define DBG(X)
#define SAY(X)
#endif

using namespace std;

int main(){
    #ifdef __LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    int N;
    cin >> N;
    DBG(N*N);
}
```

```txt:output.txt
N*N = 9604
```
主に計算途中の変数を見る役割でDBG(X)やSAY(X)を使う。
また shift operator (<<) をオーバーロードすることによって
vectorやmap の中身を見れるようにもできる。

```txt:input.txt
4
98 65 87 10
```

```cpp:test.cpp
#include <bits/stdc++.h>
#ifdef __LOCAL
#define DBG(X) cout << #X << " = " << (X) << endl;
#define SAY(X) cout << (X) << endl;
#else
#define DBG(X)
#define SAY(X)
#endif

using namespace std;

template<typename T> inline ostream& operator<<(ostream& os, const vector<T>& v) { for (auto el : v) cout << el << " "; return os; }
template<typename T> inline vector<T> fetch_vec(int sz) { vector<T> ret(sz); for (auto& elem : ret) cin >> elem; return ret; }

int main(){
    #ifdef __LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    int N;
    cin >> N;
    vector<int> V = fetch_vec<int>(N);

    DBG(N);
    DBG(V);
    sort(V.begin(),V.end());
    DBG(V);
}
```

```txt:output.txt
N = 4
V = 98 65 87 10 
V = 10 65 87 98 
```
### デバッガの使用
上記のように、変数の中身を確認するだけの用途ではデバッガを使ったほうがいいかもしれない。
ただ、ループを何重も行う場合など、中身を逐一確認するのが面倒なこともあるので、個人的には外部に出力するほうが楽かなと思っている。
まぁ、自分のデバッガの使用技術も向上すれば考え方も変わるのかも。

あと言い訳だけど、ちゃんとログ出力させるならロガーが必要だし、競技プログラミングのコードは利用時間が短く、再利用しないので
結構適当でもいいよね精神でやってる。

## 3. Visual Studio Code の設定
主に Ubuntu 18.04 で Visual Studio Code を使用している。
簡単にビルドするために ./vscode/tasks.json の中身を変更する。
私が使用している設定は以下の通り。

```json:tasks.json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Compile and run C++",
            "type": "shell",
            "command": "",
            "args": [
                "g++","-D=__LOCAL" ,"-g", "${relativeFile}", "-o","${fileBasenameNoExtension}.out", "&&" , "./${fileBasenameNoExtension}.out"
            ], // -D=__LOCAL でマクロを定義している。
            "group": {
                "kind": "build",
                "isDefault": true  
            }, // "group"{...} を設定することによって ctrl + shift + B で build & run するようにしている。
            "problemMatcher": {
                "owner": "cpp",
                "fileLocation": ["relative", "${workspaceRoot}"],
                "pattern": {
                    "regexp": "^(.*):(\\d+):(\\d+):\\s+(warning|error):\\s+(.*)$",
                    "file": 1,
                    "line": 2,
                    "column": 3,
                    "severity": 4,
                    "message": 5
                }
            }
        },
        
    ]
}
```
以上。

# 参考文献
[man g++](http://www.skrenta.com/rt/man/g++.1.html)
[Integrate with External Tools via Tasks](https://code.visualstudio.com/Docs/editor/tasks#_variable-substitution)