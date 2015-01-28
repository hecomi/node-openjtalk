var OpenJTalk = require('../openjtalk.js');
var mei = new OpenJTalk({
	sampling_rate   : 48000,
	stage           : 0,
	audio_buff_size : 48000,
	alpha           : 0.5,
	beta            : 0.8,
	uv_threshold    : 0.5,
	gv_weight_mgc   : 1.0,
	gv_weight_lf0   : 1.0,
	gv_weight_lpf   : 1.0
});

mei.talk('すっごい速いです', 100, function(err) {
	mei.talk('普通くらいです', 200, function(err) {
		mei.talk('ゆっくり喋るよ', 300);
	});
});

