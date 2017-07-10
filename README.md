# BGMLoopUtility

BGMのループ情報を調整・埋め込み・取り出しなどするためのツールセット

Tool set for adjusting/saving/extracting loop information on background musics


## 現在できること

* 対応ファイル
    * RIFF Wave (.wav)
    * FLAC (.flac)
* ループ地点半自動検出
    * ループ終了サンプル数を指定すると、そのループ終了地点に対応するループ開始地点(LOOPSTART)とループ長(LOOPLENGTH)を検出できるチャンスがあります
    * 検出できた場合はほぼ間違いなく違和感なくループできる地点が示されますが、検出できないことも多いです
    * どんなデータでどのぐらい検出出来たかは、本リポジトリ内の ExperimentResult.md をご覧下さい。


## 出来るようにしたいこと

* OGG/AAC対応
* ループタグ簡単埋め込み
* ループ地点手動調整 (吉里吉里ループツールの再実装)
* ループ情報による波形切り分け


## 動作環境

* Ubuntu
    * `libFLAC`, `libFLAC++` がパッケージマネージャ等でインストールされていることが必要です


## 本ツールで利用している素材等について

* GUI内で用いているドット絵アイコンは、[化け猫缶](http://neko.moo.jp/)より、加工の上利用させて頂いております。


