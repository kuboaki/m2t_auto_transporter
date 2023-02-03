[English](README_en.md) | [日本語](README.md)

# Astah m2t Plugin を使ってモデル図から生成したEV3RTプログラム

このリポジトリは、TOPPERS/EV3RTを実行環境として動作するMindstorms EV3用のプログラムを、UMLモデリングツールであるAstah Professionalとそのプラグインのひとつであるm2tを使って、UMLのモデル図から生成するサンプルを提供します。

## 動機

ソフトウェアの設計書としてUMLのクラス図やステートマシン図を使っても、実装になると、その図の要素や構造と対応していない書き方でコードを書いてしまうことが多いです。手書きコードの場合には特にそのような状況になりがちです。

この問題を回避するには、「どのように記述すればよいか」と、実装時に考えるのをやめてください。
代わりに、設計の前に「モデルとコードの対応づけルール」を決めておきます。設計者は、実装者がそのルールを使う前提で設計します。実装者はそのルールに従って実装します。

この「モデルとコードの対応づけルール」というところを、モデル駆動開発（MDD:Model Driven Development）では「変換規則」と呼びます。MDDでは、変換処理の自動化を目指していますが、別に手動で変換したってかまいません。とはいえ、規則を作り、それを使って変換するということを実際に試すには、モデル図を変換してコードを得る「コード生成「を試してみるのが分かりやすいでしょう。

そこで、このリポジトリでは、モデリングツールで作成したモデル図をソースコードに自動変換する事例を紹介することにしました。

## 前提

このリポジトリで扱うサンプルは、荷物を運搬する「自動搬送ロボット」です。われわれは、元々、このロボットをLEGO Mindsorms EV3のキット（以降、単にEV3と呼びます）を使って製作しました。
ここでは、実際のEV3を使う代わりに、TOPPERSの箱庭プロジェクトが提供するシミュレーション環境を使って実験してみることにします。

モデリングツールには、株式会社チェンジビジョンが開発・販売している「Astah* Professional」を使います。変換処理には、Astahのプラグインのひとつ「m2t」を使うことにします。

* LEGO Mindstorms EV3(LEGO Group)
* hakoniwa-single_robot(TOPPERS Hakoniwa WG): v1.3.1
* TOPPERS/EV3RT(TOPPERS Project) 1.1-release
* Astah* Professional(Change Vision Inc.) 8.5.0
* m2t plugin(Hosoai) 1.5.2

NOTE: リポジトリ上のプログラムは、モーターのパワーやカラーセンサーの閾値が、hakoniwa の環境と合わせてあります。実機で動かす場合には、適宜調整してください。

## 手書きで作成したシステムのデモ


まず、対象のシステムがどんなものかを知っておくのがよいでしょう。
クラス図とステートマシン図をUMLを使って作成し、その図を参照して手書きでコードを作成して作ったものです。

1. 待機場所で、荷物が積まれるのを待つ
1. バンパーが押されたら走行開始指示とみなして、運搬を開始する
1. 経路に沿って運搬する
1. 配達先を検知したら停止する
1. 荷物が降ろされるのを待つ
1. バンパーが押されたら走行開始指示とみなして、回送を開始する
1. 車庫の壁を検知したら停止する

実機（実物のEV3のロボット）と箱庭（類似のものを仮想環境でシミュレーション）の動画を紹介します（細かいところで動作がちょっと違いますが、そこは目をつぶってください）。

* 手書きで作成した自動搬送システムのデモ（実機の場合）

下記のサムネールをクリックすると動画を再生します。
走行開始指示のバンバーを押す処理がなく、車庫の壁は正面にあります。


[![auto_transportor(EV3-sample04-02)](http://img.youtube.com/vi/uvHd9yemniY/hqdefault.jpg)](https://youtu.be/uvHd9yemniY)

* 手書きで作成した自動搬送システムのデモ（箱庭の場合）

下記のサムネールをクリックすると動画を再生します。

[![auto_transportor(hakoniwa-demo)](http://img.youtube.com/vi/eq0Dnm76bAs/hqdefault.jpg)](https://youtu.be/eq0Dnm76bAs)


## モデル作成の準備


### Astah* Professionalの入手

Astah* Professionalは、株式会社チェンジビジョンが開発・販売している商用のUML用モデリングツールです。
同社のWebサイトから購入できます。評価版を入手して試してみるのもよいでしょう。


[Astah* ProfessionalのWebページ](https://astah.change-vision.com/ja/product/astah-professional.html)


### ファカルティサイトライセンスが使えるか確認しよう

チェンジビジョンは、大学や専門学校などの教育機関向けに学部あるいは学科単位で利用できるファカルサイトティライセンスを提供しています。自分の学校が導入しているかどうか確認してみるとよいでしょう。

[ファカルティサイトライセンスのWebページ](https://astah.change-vision.com/ja/shopping/faculty-site-license.html)

### m2tプラグインのインストール

「m2tプラグイン」は、細合晋太郎（s-hosoai）さんが開発しています。プラグインのソースは、GitHubで公開しています。
m2tプラグインの入手とAstah* Professionalへのインストール方法については、次のページを参照してください。

[m2tプラグイン（チェンジビジョン）](https://astah.change-vision.com/ja/plugin/astahm2t.md-plugin.html)

[m2t - Model to Text（GitHub）](https://github.com/s-hosoai/astahm2t)


## サンプルの使用方法

### リポジトリの展開場所

このリポジトリは、EV3RTのビルド環境のなかのワークスペースに合わせてあります。
実機用の環境では、workspaceディレクトリの並びに配置すれば、そのままEV3RTのビルドスクリプトでビルドできます。

* 実機用のEV3RT環境へのサンプルリポジトリの配置

```shell
（説明に関係しないディレクトリは省略）
sdk
├── m2t_workspace
│   ├── m2t_auto_transporter
│   └── m2t_ev3rt_templates
└── workspace
```

### 箱庭で使う場合の注意

箱庭（hakoniwa-single_robot）は、各種スクリプトが `sdk/workspace` に配置してあると想定しています。
このため、別の場所に `m2t_workspace` を配置しても、シミュレータのスクリプトが認識してくれません。

* 箱庭では、 `m2t_workspace` を `workspace ` と並べて配置できない

```shell
（説明に関係しないディレクトリは省略）
sdk
├── m2t_workspace
│   ├── m2t_auto_transporter（ここに配置してもシミュレーションできない）
│   └── m2t_ev3rt_templates
└── workspace
```

箱庭で使う場合には、このリポジトリを `sdk` の中に配置したあとで、生成したソースコードのを既存の `workspace` ディレクトリにコピーしてください。

* 箱庭では、 `m2t_auto_transporter` を `workspace ` にコピーして使う

```shell
（説明に関係しないディレクトリは省略）
├── m2t_workspace
│   ├── m2t_auto_transporter（コード生成先はここにする）
│   └── m2t_ev3rt_templates
└── workspace
    ├── helloev3
    ├── m2t_auto_transporter（ここにコピーしてから使う）
    └── trike
```

みなさんがモデル図からコードを作成する場合にも、このリポジトリの構成を真似て `m2t_workspace` の中に自分たちのモデル図やEV3RT用ソースコードのディレクトリ、生成用テンプレートのディレクトリを置き、生成後のコードを `workspace` にコピーするとよいでしょう。


### このサンプルのモデル図を参照する

このリポジトリが提供しているサンプルのモデル図をAstah*で開いてみましょう。
モデルファイルは、 `m2t_workspace/models/m2t_auto_transporter.asta` です。

サンプルには、システムの構造を示したクラス図と、2つのクラスの振る舞いを表したステートマシン図があります。

* システムのクラス図

![auto_transporter_systemのクラス図](images/class_diagram.png)

* auto_transporterクラスのtransportメソッドのステートマシン図

![auto_transporterクラスのtransportメソッドのステートマシン図](images/auto_transporter_transport_stm.png)

* line_tracerクラスのrunnerメソッドのステートマシン図

![line_tracerクラスのrunnerメソッドのステートマシン図](images/line_tracer_runner_stm.png)

### 生成用テンプレートの設定

Astah*にm2tプラグインがインストールできていれば、「ツール」メニューを開くと「m2t」がメニューの下端に追加されています。

このリポジトリが提供しているサンプルからコードを生成するためのテンプレートは、 `m2t_workspace/m2t_ev3rt_templates/` ディレクトリにあります。

初めてサンプルモデル図を開いたときには、この場所が設定に反映できていません。
「m2t＞setting」をひらいて、次のように設定しましょう（パス名は、みなさんの環境によって異なっているでしょうから、適宜読み替えてください）。

![m2tプラグインが使うテンプレートの設定](images/template_settings_jp.png)


### プログラムの生成

テンプレートの設定ができたら、サンプルモデル図からEV3RT用のソースコードを生成してみましょう。

「ツール」メニューの「m2t＞generate」を選ぶと、テンプレート設定で `Destination Path` に設定したディレクトリにソースコードが生成されます。

```shell
（説明に関係しないディレクトリは省略）
sdk/m2t_workspace
├── m2t_auto_transporter（指定した生成先ディレクトリにファイルが生成されている）
│   ├── Makefile.inc
│   ├── app.c
│   ├── app.cfg
│   ├── app.h
│   ├── auto_transporter.c
│   ├── auto_transporter.h
│   ├── （以下略）
│   └── wall_detector.h
├── m2t_ev3rt_templates
│   └── （生成に使ったテンプレート）
└── models
    └── m2t_auto_transporter.asta（生成に使ったモデル図）

```

### app.cfgの編集

まだ生成規則が行き届いていないため、2つの実装環境の差異を吸収できていません。
ビルドの前に `app.cfg` を編集してください（どちらかしか使わない人は、テンプレートを直してしまってもよいでしょう）。

#### 実機用にビルド・実行する場合

実機用にビルド・実行する場合は、 `app.cfg` を次のように編集してください。

* `INCLUDE("tecsgen.cfg");` を削除する

```C
INCLUDE("app_common.cfg");

#include "app.h"
#include "ev3.h"

DOMAIN(TDOM_APP) {
CRE_TSK( MAIN_TASK, { TA_NULL, 0, main_task,  MAIN_PRIORITY, STACK_SIZE, NULL } );
CRE_CYC( CYC0, { TA_STA, { TNFY_ACTTSK, MAIN_TASK }, 50U * 1000U, 1});
}

（以下省略）
```

#### 箱庭用にビルド・実行する場合

箱庭用にビルド・実行する場合は、 `app.cfg` を次のように編集してください。

* `DOMAIN` を削除する

```C
INCLUDE("app_common.cfg");
INCLUDE("tecsgen.cfg");

#include "app.h"
#include "ev3.h"

CRE_TSK( MAIN_TASK, { TA_NULL, 0, main_task,  MAIN_PRIORITY, STACK_SIZE, NULL } );
CRE_CYC( CYC0, { TA_STA, { TNFY_ACTTSK, MAIN_TASK }, 50U * 1000U, 1});

（以下省略）
```

### プログラムのビルドと実行

編集できたら、生成したコードをビルドして実行してみましょう。

#### 実機の場合

`make` コマンドを使って `app` ファイルを作りましょう。

```shell
$ cd {EV3RTのインストールディレクトリ}/hrp3/sdk/m2t_workspace
$ make app=m2t_auto_transporter
$ ls -l app
-rwxr-xr-x  1 kuboaki  staff  101480  8 30 00:42 app
```

`app` ファイルが作成できたら、TOPPERS/EV3RTのページにあるプログラムの転送方法に従って転送して動かしてみてください。

いかがでしょう。期待通り動いたでしょうか。

`auto_transporter` クラスの `transport` メソッドのステートマシン図と同じ動作になっているか、確認してみましょう。



#### 箱庭の場合

まず、ビルドの前に、端末Aでdockerコンテナを動かしておくのをお忘れなく。

```shell
$ cd {hakoniwa-single_robotのディレクトリ}
$ bash run-proxy.bash m2t_auto_transporter
```

次に、端末Bで、生成したソースコードを `workspace` へコピーしましょう。

```shell
$ cd {自分がm2t_workspaceディレクトリを置いた場所}
$ cp -prf m2t_auto_transporter {hakoniwa-single_robotのディレクトリ}/sdk/workspace
$ cd {hakoniwa-single_robotのディレクトリ}
$ ls sdk/workspace/m2t_auto_transporter
drwxr-xr-x  35 kuboaki  staff    1120  8 30 01:39 m2t_auto_transporter
```

続けて端末Bで、ビルド用のシェルスクリプトを使って、ビルドします。

```shell
$ cd {hakoniwa-single_robotのディレクトリ}
$ bash build-app.bash clean
$ bash build-app.bash m2t_auto_transporter
$ ls -l sdk/workspace/asp
-rwxr-xr-x  1 kuboaki  staff  101480  8 30 00:42 asp
```

端末Cで、シミュレーションを開始します。

NOTE: コマンドラインで指定するのはUnityアプリの名前であることに注意しましょう。

```shell
$ cd {hakoniwa-single_robotのディレクトリ}
$ bash star-unity.bash auto-transporter2　# 引数にはUnityアプリ名を指定することに注意
```

いかがでしょう。期待通り動いたでしょうか。

`auto_transporter` クラスの `transport` メソッドのステートマシン図と同じ動作になっているか、確認してみましょう。


## モデルを変更してみる

モデルを変更して、生成したコードが変わるか、確認してみましょう。
たとえば、次のようなことを実現するには、どのようにすればよいか、考えてみてください。

* 変更1）配達先で荷物が降ろされていなかったら、発車しない
* 変更2）待機場所で荷物を受け取らずに発車したときは、配達先で停車せず、通過して車庫へ進んで停車する


おそらく、細かい話を除けば、 `auto_transporter` のステートマシン図を変更すれば、実現できるでしょう。

## ステートマシン図とコードの対応
d
このリポジトリで提供しているサンプルは、1つのタスク（ `main_task` ）を周期ハンドラ（ `cyc0`  ）で繰り返し起動する動作モデルを使っています。
また、センサー値の読み込みも同じタスクの中でセンサーのAPIを呼び出し、その値で判定する簡便な作りにしています（とはいえ、サンプリング周期はハンドラの起動間隔前後で一定になります）。

* サンプルにおける周期ハンドラとタスクの関係

![周期ハンドラとタスクの関係](images/cyclic_handler_and_main_task.png)

その代わりに、この作り方では、それぞれのセンサーの値は周期ハンドラの周期ごとに読み込むよう、プログラムの内部に閉じたループを作らないように気をつけます。
このサンプルの作り方では、プログラムの内部に閉じたループがあると、そのループにいる間、ほかのセンサーの値を取得できなくなるからです。

※ このような、実装時の処理方式を決める設計作業を実装方式と呼ぶ人もいます。モデル駆動のコミュニティ以外ではあまり語られていませんが、実装と設計の乖離を減らすには、設計の冒頭で実装方式を決定して、それから構造や振る舞いのモデルを作ることが大切です。

ステートマシン図の各要素とコードは、次のように対応づけてあります。

* ステートマシン図とコードの対応

![ステートマシン図とコードの対応](images/stm_to_code.png)

イベントの検出が、変化点（エッジ）となるか取得時点の値の評価になるかは、イベントとして割り当てられている関数の内部処理によって異なります。
doアクティビティの処理は周期ごとに呼び出されます。
ここでは、経路に沿って走行する処理が、経路（コース上のライン）を読み取るために、周期ごとに呼び出されています。

## どうやって生成ルールを作るのか

コード生成では、万能の生成エンジンがあって、それがみなさんの望みを叶えてくれるわけではありません。
その代わりに、自分たちの都合にあった変換規則を用意して使えばよいのです。
100%うまくいく方法を目指すのではなくて、8割方うまくいく方法を決めて残り2割は例外扱い（たとえば生成対象から外して手書きのコードを使うとか）でもかまわないでしょう。

自分が欲しいコードを生成するには、まず自分たちが書いているコードを、処理パターンとその処理で用いるパラメータとでパターン化します。
そして、クラス（あるいはメソッド）によて異なる箇所をモデルから取得できる要素によってパラメータ化します。

たとえば、`m2t_auto_transporter.c` ファイル中には、こんなコードが生成されています。

```C
typedef enum _auto_transporter_state_t {
    ATST_PSEUDO_END_STATE,
    ATST_WAIT_FOR_LOADING,
    ATST_TRANSPORTING,
    ATST_WAIT_FOR_UNLOADING,
    ATST_WAIT_FOR_START,
    ATST_WAIT_FOR_RETURN,
    ATST_WAIT_FOR_PASSING_STATION,
    ATST_ARRIVED,
    ATST_RUNNING_TOWARD_GARAGE
} auto_transporter_state_t;
```

Cの `enum` や `tyepdef` の構文は決まっています。
そこで、クラス名に紐づけて定義する型の名前を決めることにします。

つまり、次のような名前です。

```C
{クラス名}_state_t
```

ステートマシン図で使っている状態名のリストはモデル図から手に入ります。
m2tプラグインでは、 `u.states`  に格納されています。
これを、プログラムで使う列挙名にするには、次のような形を考えればよさそうです。

```C
すべての状態から取り出した1つの状態ごとに
    プレフィックス_{状態名}を大文字にしたもの
```

まず、状態ごとに繰り返して、各状態名を得るところまでをやりましょう。

状態名のリストから1つずつ取り出すには、m2tプラグインがテンプレートエンジンとして使っているGroovyの `for` を使います。

```Groovy
<% for(st in u.states){%>\
${st.name}
<%}%>\
```

`<%` から `%>` までは、出力の対象ではない部分を囲んでいます。
行末の `\` には、改行の出力を抑制する働きがあります。

これで、すべての状態について繰り返し処理し、各状態名は `st.name` で参照できるようになりました。

次はプレフィックスです。
クラス名をそのまま使ってもよいのですが、長くなりすぎますね。
そこで、モデル図の方でそれぞれのクラスに短い「別名」をつけておきます（これは Astah* Professionalが提供している機能を使っています）。
そして、この別名を grooby のメソッドで大文字に変換して、プレフィクスに使うことにします。

```C
u.iclass.alias1.toUpperCase()
```

このような、モデル図のなかの情報を取得する場合には、Astah* のAPIを使います。
APIの利用者ガイドのなかに、Java Doc形式のAPIリファレンスがあります。

[astah* API 利用者ガイド](https://members.change-vision.com/javadoc/astah-api/8_1_0/api/ja/doc/index.html)

これで、プレフィックス、状態名が手に入ったので、あとは整形するだけです。

```Groovy
<% if(u.statemachine){%>\
<% for(st in u.states){%>\
    ${u.iclass.alias1.toUpperCase()}ST_${st.name.toUpperCase()},
<%}%>\
<%}%>\
```

全体を、 `<% if(u.statemachine){%>\` から `<%}%>\` で囲んであります。
このコードを生成する必要があるのは、ステートマシン図が提供されてい（ `u.statemachine` が真になる）クラスだけだからです。

実際に使っているテンプレートでは、ヘルパーメソッドを使ったり、 `collect` や `join` を使ったりしています。

```Groovy
<% if(u.statemachine){%>\
typedef enum _${u.name}_state_t {
    ${getStateName("PSEUDO_END_STATE")}, // 疑似終了状態を追加しています
${u.states.collect({"    " + getStateName(it)}).join(',\n')}
} ${u.name}_state_t;
<%}%>\
```

このようにして、ソースコードのそれぞれの箇所について、自分たちがほしいかたちになるよう、テンプレートを作成していけば、手で書くコードとだいたい同じ（もう少し整理した）コードを生成できるようになります。

## Tips

テンプレートの中に `${u.properties}` と書いておくと、m2tプラグインがプロパティとして取得しておいてくれている情報が一覧できます。参考になるでしょう。


## 参考リンク

* [LEGO Mindstorms EV3(Wikipedia)](https://ja.wikipedia.org/wiki/Lego_Mindstorms_EV3)
* [hakoniwa-single_robot(TOPPERS Hakoniwa WG)](https://github.com/toppers/hakoniwa-single_robot)
* [TOPPERS/EV3RT(TOPPERS Project)](https://dev.toppers.jp/trac_user/ev3pf/wiki/WhatsEV3RT)
* [Astah* Professional(Change Vision Inc.)](https://astah.change-vision.com/ja/product/astah-professional.html)
