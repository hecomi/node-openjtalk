var exec = require('child_process').exec
  , path = require('path')
  , uuid = require('uuid-v4')
;

// デフォルトパラメタ
var DEFAULTS = {
	openjtalk_bin   : path.join(__dirname, '/bin/open_jtalk'),
	dic_dir         : path.join(__dirname, '/dic/open_jtalk_dic_utf_8-1.05'),
	voice_dir       : path.join(__dirname, '/voice/mei_normal'),
	sampling_rate   : 48000,
	stage           : 0,
	pitch           : 220,
	audio_buff_size : 48000,
	alpha           : 0.5,
	beta            : 0.8,
	uv_threshold    : 0.5,
	gv_weight_mgc   : 1.0,
	gv_weight_lf0   : 1.0,
	gv_weight_lpf   : 1.0
}

// OpenJTalk で wav ファイルを生成するクラス
var OpenJTalk = function(args) {
	var args = args || {}
	  , opts = args.hasOwnProperty('options') ? args.options : {}
	;
	// 音素ファイルと辞書ファイルをセット
	this.dicDir   = args.hasOwnProperty('dic')   ? args.dic   : DEFAULTS.dic_dir;
	this.voiceDir = args.hasOwnProperty('voice') ? args.voice : DEFAULTS.voice_dir;

	// パラメタをセット
	this.setOptions(opts);
}

OpenJTalk.prototype = {
	// 喋らせる
	talk : function (str /*, [pitch, [callback]] */) {
		// 引数の展開
		var pitch    = this.pitch
		  , callback = null
		;
		if ( typeof(arguments[1]) == 'number' ) {
			pitch = arguments[1];
		}
		for (var i = 1; i <= 2; ++i) {
			if ( typeof(arguments[i]) == 'function' ) {
				callback = arguments[i];
				break;
			}
		}
		this._makeWav(str, pitch, function(err, result) {
			if (err) {
				if (callback) callback(err, null);
				return;
			}
			this._play(result.wav, callback);
		}.bind(this));
	},

	// wav を再生する
	_play : function(wavFileName, callback) {
		var client;
		switch (process.platform) {
			case 'darwin' : client = 'afplay'; break;
			case 'linux'  : client = 'aplay';  break;
			default       : client = 'play';   break;
		}
		var cmd = client + ' ' + wavFileName + '&& rm ' + wavFileName;
		exec(cmd, function(err, stdout, stderr) {
			if (callback) callback(err, stdout, stderr);
		});
	},

	// パラメタをセットする
	setOptions : function (opts) {
		if (!opts) return;
		this.sampling_rate   = opts.hasOwnProperty('sampling_rate')   ? opts.sampling_rate   : DEFAULTS.sampling_rate;
		this.pitch           = opts.hasOwnProperty('pitch')           ? opts.pitch           : DEFAULTS.pitch;
		this.stage           = opts.hasOwnProperty('stage')           ? opts.stage           : DEFAULTS.stage;
		this.audio_buff_size = opts.hasOwnProperty('audio_buff_size') ? opts.audio_buff_size : DEFAULTS.audio_buff_size;
		this.alpha           = opts.hasOwnProperty('alpha')           ? opts.alpha           : DEFAULTS.alpha;
		this.beta            = opts.hasOwnProperty('beta')            ? opts.beta            : DEFAULTS.beta;
		this.uv_threshold    = opts.hasOwnProperty('uv_threshold')    ? opts.uv_threshold    : DEFAULTS.uv_threshold;
		this.gv_weight_mgc   = opts.hasOwnProperty('gv_weight_mgc')   ? opts.gv_weight_mgc   : DEFAULTS.gv_weight_mgc;
		this.gv_weight_lf0   = opts.hasOwnProperty('gv_weight_lf0')   ? opts.gv_weight_lf0   : DEFAULTS.gv_weight_lf0;
		this.gv_weight_lpf   = opts.hasOwnProperty('gv_weight_lpf')   ? opts.gv_weight_lpf   : DEFAULTS.gv_weight_lpf;
	},

	// exec から open_jtalk を実行して wav ファイルを作る
	_makeWav : function (str, pitch, callback) {
		var wavFileName = uuid() + '.wav';
		var ojtCmd  = DEFAULTS.openjtalk_bin
		            + ' -td ' + this.voiceDir + '/tree-dur.inf'
		            + ' -tf ' + this.voiceDir + '/tree-lf0.inf'
		            + ' -tm ' + this.voiceDir + '/tree-mgc.inf'
		            + ' -md ' + this.voiceDir + '/dur.pdf'
		            + ' -mf ' + this.voiceDir + '/lf0.pdf'
		            + ' -mm ' + this.voiceDir + '/mgc.pdf'
		            + ' -df ' + this.voiceDir + '/lf0.win1'
		            + ' -df ' + this.voiceDir + '/lf0.win2'
		            + ' -df ' + this.voiceDir + '/lf0.win3'
		            + ' -dm ' + this.voiceDir + '/mgc.win1'
		            + ' -dm ' + this.voiceDir + '/mgc.win2'
		            + ' -dm ' + this.voiceDir + '/mgc.win3'
		            + ' -ef ' + this.voiceDir + '/tree-gv-lf0.inf'
		            + ' -em ' + this.voiceDir + '/tree-gv-mgc.inf'
		            + ' -cf ' + this.voiceDir + '/gv-lf0.pdf'
		            + ' -cm ' + this.voiceDir + '/gv-mgc.pdf'
		            + ' -k  ' + this.voiceDir + '/gv-switch.inf'
		            + ' -x  ' + this.dicDir   + ' '
		            + ' -s  ' + this.sampling_rate
		            + ' -p  ' + pitch
		            + ' -a  ' + this.alpha
		            // + ' -b  ' + this.beta
		            + ' -u  ' + this.uv_threshold
		            + ' -jm ' + this.gv_weight_mgc
		            + ' -jf ' + this.gv_weight_lf0
		            // + ' -jl ' + this.gv_weight_lpf
		            + ' -l  '
		            + ' -z  ' + this.audio_buff_size
		            + ' -ow ' + wavFileName;
		var cmd = 'echo ' + str + '|' + ojtCmd;
		exec(cmd, function(err, stdout, stderr) {
			var result = {
				stdout : stdout,
				stderr : stderr,
				wav    : wavFileName
			};
			if (callback) callback(err, result);
		});
	}
};

// エクスポート
module.exports = OpenJTalk;

