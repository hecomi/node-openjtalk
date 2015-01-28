node-openjtalk : Node.js TTS module using OpenJTalk
=============

これは何？
--------------
フリーの日本語音声合成エンジン [OpenJTalk](http://open-jtalk.sourceforge.net/) を利用する Node.js モジュールです。

動作環境
--------------
* Mac OS X 10.10.1
* Node.js v0.10.36

インストール
--------------
```sh
$ npm install openjtalk
```

テスト
--------------
```sh
$ npm test
```

使い方
--------------
もっともシンプルなコードは以下になります。

```javascript
var OpenJTalk = require('openjtalk');
var mei = new OpenJTalk();
mei.talk('こんにちは世界');
```

`.htsvoice` のパスと辞書ファイルを含んだディレクトリ、OpenJTalk の設定オプションを引数に渡せます。
引数は省略することもできます。省略した場合は [MMDAgent](http://www.mmdagent.jp/) のメイちゃんの声をデフォルトとして喋ります。
音声ファイルを複数用意すれば以下のように喋り分け出来ます。

```javascript
var OpenJTalk = require('openjtalk');
var mei1 = new OpenJTalk(); // mei_normal を使用
var mei2 = new OpenJTalk({ htsvoice: './voice/mei/mei_angry.htsvoice' });
var mei3 = new OpenJTalk({ htsvoice: './voice/mei/mei_happy.htsvoice' });

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

設定値を変える場合は以下のようにします。

```javascript
var OpenJTalk = require('./openjtalk');
var mei = new OpenJTalk({
	htsvoice        : './voice/mei/mei_normal.htsvoice',
	dic             : './dic/open_jtalk_dic_utf_8-1.08',
	sampling_rate   : 48000,
	pitch           : 220,
	audio_buff_size : 48000,
	alpha           : 0.5,
	beta            : 0.8,
	uv_threshold    : 0.5,
	gv_weight_mgc   : 1.0,
	gv_weight_lf0   : 1.0
});

// 喋る速度を調整することもできます
mei.talk('すっごい速いです', 100, function(err) {
	mei.talk('普通くらいです', 200, function(err) {
		mei.talk('ゆっくり喋るよ', 300);
	});
});
```

上記がデフォルト値になります。

注意
--------------
処理的には、OpenJTalk で wav を生成、それを afplay / aplay で再生、喋り終わったら削除、としているので、しゃべっている途中に中断すると wav ファイルが実行しているディレクトリに残ります。その際は手動で削除して下さい。

詳細
--------------
その他詳細は Twitter:@hecomi へご質問いただくか、http://tips.hecomi.com/ をご参照下さい。
