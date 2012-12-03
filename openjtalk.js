var fs           = require('fs')
  , path         = require('path')
  , OpenJTalk_
;
DEFAULT_DIC_DIR   = path.join(__dirname, '/dic/open_jtalk_dic_utf_8-1.05');
DEFAULT_VOICE_DIR = path.join(__dirname, '/voice/mei_normal');

// C++ モジュールの読み込み
if ( fs.existsSync( path.join(__dirname, './build/Debug') ) ) {
	OpenJTalk_ = require('./build/Debug/openjtalk').OpenJTalk;
} else if ( fs.existsSync( path.join(__dirname, './build/Release') ) ) {
	OpenJTalk_ = require('./build/Release/openjtalk').OpenJTalk;
} else {
	throw '"OpenJTalk" has not been compiled yet.'
}

// デフォルト引数設定
var OpenJTalk = function(args) {
	args = args || {};
	var dic     = args.hasOwnProperty('dic')     ? args.dic     : DEFAULT_DIC_DIR;
	var voice   = args.hasOwnProperty('voice')   ? args.voice   : DEFAULT_VOICE_DIR;
	var options = args.hasOwnProperty('options') ? args.options : undefined;
	return new OpenJTalk_(voice, dic, options);
}

// エクスポート
module.exports = OpenJTalk;

