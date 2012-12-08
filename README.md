node-openjtalk : Node.js TTS module using OpenJTalk
=============

これは何？
--------------
フリーの日本語音声合成エンジン [OpenJTalk](http://open-jtalk.sourceforge.net/) を利用する Node.js モジュールです。

ライセンス
--------------
ライセンスは各ライブラリに準拠します。
私が書いた場所については MIT ライセンスとなります。
+ [OpenJTalk](http://open-jtalk.sourceforge.net/) : 修正BSDライセンス

動作環境
--------------
MacOS X 10.8.2 および Ubuntu 10.04 で動作を確認しています。

インストール
--------------
```sh
$ cd YOUR_NODE_PROJECT_DIR
$ git clone https://github.com/hecomi/node-openjtalk
$ mkdir node_modules
$ mv node-openjtalk node_modules/openjtalk
$ cd node_modules/openjtalk
$ npm install
```

テスト
--------------
```sh
$ npm test
```

使い方
--------------
音声ファイルを含んだディレクトリ、辞書ファイルを含んだディレクトリ、OpenJTalk の設定オプションを引数に渡せます。
引数は省略することもできます。省略した場合は [MMDAgent](http://www.mmdagent.jp/) のメイちゃんの声をデフォルトとして喋ります。
音声ファイルを複数用意すれば以下のように喋り分け出来ます。

```javascript
var OpenJTalk = require('openjtalk');
var mei1 = new OpenJTalk(); // mei_normal を使用
var mei2 = new OpenJTalk({voice: './voice/mei_sad'});
var mei3 = new OpenJTalk({voice: './voice/mei_happy'});

mei1.talk('これはテストです'); // コールバックは省略できる
setTimeout(function() {
	mei2.talk('喋り終わり次第コールバックを呼びます', function(err) {
		if (err) console.log('err', err);
		console.log('コールバックを呼ぶ');
		mei3.talk('エラーが発生したらコールバックの引数からチェックできます', function(err) {
			if (err) console.log('err', err);
			else mei1.talk('エラーは発生しませんでした');
		});
	});
}, 2000);
```

同期して喋らせたい場合は、async 等のモジュールを使えば綺麗に書けると思います。
設定値を変える場合は以下のようにします。

```javascript
var OpenJTalk = require('./openjtalk');
var mei = new OpenJTalk({
	voice   : './voice/mei_normal',
	dic     : './dic/open_jtalk_dic_utf_8-1.05',
	options : {
		sampling_rate   : 48000,
		stage           : 0,
		audio_buff_size : 48000,
		alpha           : 0.5,
		beta            : 0.8,
		uv_threshold    : 0.5,
		gv_weight_mgc   : 1.0,
		gv_weight_lf0   : 1.0,
		gv_weight_lpf   : 1.0
	}
});

// 喋る速度を調整することもできます
mei.talk('すっごい速いです', 100, function(err) {
	mei.talk('普通くらいです', 200, function(err) {
		mei.talk('ゆっくり喋るよ', 300);
	});
});
```
options の各設定値は省略可能です。ちなみに上記がデフォルト値になります。

注意
--------------
処理的には、OpenJTalk で wav を生成、それを afplay/aplay で再生、喋り終わったら削除、としているので、しゃべっている途中に中断すると wav ファイルが実行しているディレクトリに残ります。手動で削除して下さい。

詳細
--------------
その他詳細は Twitter:@hecomi へご質問いただくか、http://d.hatena.ne.jp/hecomi/ をご参照下さい。
