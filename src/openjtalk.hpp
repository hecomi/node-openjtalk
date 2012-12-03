#ifndef INCLUDE_JULIUS_HPP
#define INCLUDE_JULIUS_HPP

#include <string>
#include <node.h>
#include <portaudio.h>
#include "mecab.h"
#include "njd.h"
#include "jpcommon.h"
#include "HTS_engine.h"

/**
 * OpenJTalk に与えるデフォルトパラメータ
 */
struct OpenJTalk_params
{
	int    sampling_rate, stage, audio_buff_size;
	double alpha, beta, uv_threshold, gv_weight_mgc, gv_weight_lf0, gv_weight_lpf;
	OpenJTalk_params() :
		sampling_rate(48000),
		stage(0),
		audio_buff_size(48000),
		alpha(0.5),
		beta(0.8),
		uv_threshold(0.5),
		gv_weight_mgc(1.0),
		gv_weight_lf0(1.0),
		gv_weight_lpf(1.0)
	{}
};

/**
 * Open JTalkでTTSするクラス
 */
class OpenJTalk : public node::ObjectWrap {
public:
	/**
	 * OpenJTalk に渡すパラメータを生成
	 * @param[in] voice_dir	音素などが入ったディレクトリ
	 * @param[in] dic_dir	辞書入ったディレクトリ
	 */
	OpenJTalk(const std::string& voice_dir, const std::string& dic_dir, OpenJTalk_params params);

	/**
	 * デストラクタ
	 */
	~OpenJTalk();

	/**
	 *  Node.js の世界へエクスポートする
	 *  @param[out] target  NODE_MODULES でエクスポートする関数の引数
	 */
	static void Init(v8::Handle<v8::Object>& target);

private:
	/**
	 *  JavaScript 側で new された時に呼ばれる
	 *  @param[in] args  JavaScript 側で与えられる引数
	 */
	static v8::Handle<v8::Value> New(const v8::Arguments& args);

	/**
	 *  JavaScript 側で talk した時に呼ばれる
	 *  @param[in] args  JavaScript 側で与えられる引数
	 */
	static v8::Handle<v8::Value> Talk(const v8::Arguments& args);

	/**
	 *  JavaScript 側で stop した時に呼ばれる
	 *  @param[in] args  JavaScript 側で与えられる引数
	 */
	static v8::Handle<v8::Value> Stop(const v8::Arguments& args);

	/**
	 * Open JTalk に必要な情報をまとめておく構造体
	 */
	struct OpenJTalk_data {
		Mecab mecab;
		NJD njd;
		JPCommon jpcommon;
		HTS_Engine engine;
	} open_jtalk_data_;

	//! OpenJTalk を指定されたパラメタで初期化する（open_jtalk.c より抜粋）
	void initialize(
		int sampling_rate, int fperiod, double alpha, int stage, double beta, int audio_buff_size,
		double uv_threshold, HTS_Boolean use_log_gain, double gv_weight_mgc,
		double gv_weight_lf0, double gv_weight_lpf);

	//! 必要なファイル群をロードする（open_jtalk.c より抜粋）
	void load(
		char *dn_mecab, char *fn_ms_dur, char *fn_ts_dur,
		char *fn_ms_mgc, char *fn_ts_mgc, char **fn_ws_mgc, int num_ws_mgc,
		char *fn_ms_lf0, char *fn_ts_lf0, char **fn_ws_lf0, int num_ws_lf0,
		char *fn_ms_lpf, char *fn_ts_lpf, char **fn_ws_lpf, int num_ws_lpf,
		char *fn_ms_gvm, char *fn_ts_gvm, char *fn_ms_gvl, char *fn_ts_gvl,
		char *fn_ms_gvf, char *fn_ts_gvf, char *fn_gv_switch);

	//! 指定したテキストを喋る wav ファイルを作成する
	void synthesis(char *txt, FILE *wavfp);

	/**
	 * 引数の言葉を喋らせる
	 * @param[in] str	喋らせる文章
	 * @param[in] fperiod	ピッチ（default = 240）
	 * @return エラー文言（エラーがない場合は空 = "" ）
	 */
	std::string talk(const std::string& str, const int fperiod = 240, bool async = false);

	/**
	 *  再生中の wav をストップする
	 */
	void stop();

	/**
	 * wav ファイルの名前を取得する
	 * @return UUID をもとに生成したファイル名
	 */
	std::string get_wav_name();

	/**
	 * パラメタなどを整形して synthesis を実行する
	 * @param[in] wav_file_path	wav ファイルの保存先パス
	 * @param[in] sentence	喋らせる文章
	 * @param[in] fperiod
	 */
	//!
	void make_wav(const std::string& wav_file_path, const std::string& sentence, const int fperiod);

	/**
	 * wav ファイルを再生する
	 * @param[in] wav_file_path	wav ファイルの保存先パス
	 * @return エラー文言（エラーがない場合は空 = "" ）
	 */
	std::string play_wav(const std::string& wav_file_path);

	/**
	 * wav ファイルを削除する
	 * @param[in] wav_file_path	wav ファイルの保存先パス
	 */
	void remove_wav(const std::string& wav_file_path) const;

	//! 音素などが入ったディレクトリ
	std::string voice_dir_;

	//! 辞書が入ったディレクトリ
	std::string dic_dir_;

	//! OpenJTalk の設定パラメータ
	OpenJTalk_params params_;
};

#endif // INCLUDE_JULIUS_HPP
