var path = require('path');
var OpenJTalk = require('../openjtalk.js');
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
