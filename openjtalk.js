var execFile = require('child_process').execFile
  , spawn = require('child_process').spawn
  , path = require('path')
  , uuid = require('uuid-v4')
;

// デフォルトパラメタ
var DefaultOptions = {
	openjtalk_bin : path.join(__dirname, '/bin/open_jtalk'),
	dic_dir       : path.join(__dirname, '/dic/open_jtalk_dic_utf_8-1.09'),
	htsvoice      : path.join(__dirname, '/voice/mei/mei_normal.htsvoice'),
	wav_dir       : '.',
};

// OpenJTalk で wav ファイルを生成するクラス
var OpenJTalk = function(args) {
	var args = args || {};
	var options = DefaultOptions;
	for (var key in args) {
		options[key] = args[key];
	}
	for (var key in options) {
		this[key] = options[key];
	}
};

OpenJTalk.prototype = {
	// 喋らせる
	talk : function (str /*, [pitch, [callback]] */) {
		// 引数の展開
		var pitch    = this.pitch
		  , callback = null
		;
		if (typeof(arguments[1]) == 'number') {
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
		// escape
		wavFileName = wavFileName.split(/\s/).join('');

		var player;
		switch (process.platform) {
			case 'darwin' : player = 'afplay'; break;
			case 'linux'  : player = 'aplay';  break;
			default       : player = 'play';   break;
		}
		execFile(player, [wavFileName], function(err, stdout, stderr) {
			execFile('rm', [wavFileName]);
			if (callback) callback(err, stdout, stderr);
		});
	},

	// exec から open_jtalk を実行して wav ファイルを作る
	_makeWav : function (str, pitch, callback) {
		var wavFileName = uuid() + '.wav';

		var ojtCmd = [this.openjtalk_bin];
		var options = {
			m  : this.htsvoice,
			x  : this.dic_dir,
			s  : this.sampling_rate,
			p  : pitch,
			a  : this.alpha,
			b  : this.beta,
			u  : this.uv_threshold,
			jm : this.gv_weight_mgc,
			jf : this.gv_weight_lf0,
			z  : this.audio_buff_size,
			ow : path.join(this.wav_dir, wavFileName)
		};
		for (var option in options) {
			var value = options[option];
			if (value) {
				ojtCmd.push('-' + option);
				ojtCmd.push(value);
			}
		}

		this._securePipeExec('echo', [str], ojtCmd[0], ojtCmd.slice(1), function(err, stdout, stderr) {
			var result = {
				stdout : stdout,
				stderr : stderr,
				wav    : wavFileName
			};
			if (callback) callback(err, result);
		});
	},

	// Securely execute piped commands
	_securePipeExec : function (cmd1, cmd1Args, cmd2, cmd2Args, callback) {
		let stdout = '';
		let stderr = '';
		const spCmd1 = spawn(cmd1, cmd1Args);
		const spCmd2 = spawn(cmd2, cmd2Args);

		spCmd1.stdout.on('data', (data) => {
			spCmd2.stdin.write(data);
		});

		spCmd1.stderr.on('data', (data) => {
            stderr += data;
		});

		spCmd1.on('close', (code) => {
			if (code !== 0) {
				console.error(`${cmd1} process exited with code ${code}`);
			}
			spCmd2.stdin.end();
		});

		spCmd2.stdout.on('data', (data) => {
			stdout += data.toString();
		});

		spCmd2.stderr.on('data', (data) => {
			stderr+= data;
		});

		spCmd2.on('close', (code) => {
			if (code !== 0) {
				console.error(`${cmd2} process exited with code ${code}`);
			}
			if (callback) callback(code, stdout, stderr);
		});
	}
};

module.exports = OpenJTalk;
