#include "openjtalk.hpp"
#include <vector>
#include <iostream>
#include <sndfile.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/lexical_cast.hpp>

// OpenJTalk headers
#include "text2mecab.h"
#include "mecab2njd.h"
#include "njd_set_pronunciation.h"
#include "njd_set_digit.h"
#include "njd_set_accent_phrase.h"
#include "njd_set_accent_type.h"
#include "njd_set_unvoiced_vowel.h"
#include "njd_set_long_vowel.h"
#include "njd2jpcommon.h"

//! buffer size for text2mecab
const size_t MAXBUFLEN = 1024;

// using namespace node;
using namespace v8;
using namespace std;
using namespace node;

/* ------------------------------------------------------------------------- */
//  グローバル変数 / データやりとり用 構造体
/* ------------------------------------------------------------------------- */
// EventEmitter.emit 用のシンボル
static Persistent<String> emit_symbol;

//! Julius の別スレッドからのアクセス用
static uv_mutex_t m;

// Emit でやりとりするデータ
struct TalkData
{
	TalkData() : self(nullptr), fperiod(220), cb_flag(false) {}
	OpenJTalk            *self;
	std::string          str;
	std::string          err;
	int                  fperiod;
	Persistent<Function> callback;
	bool                 cb_flag;
};

/* ------------------------------------------------------------------------- */
//  文字列生成
/* ------------------------------------------------------------------------- */
vector<char> make_vec_char(const std::string& str) {
	vector<char> buf(str.begin(), str.end());
	buf.push_back('\0');
	return buf;
}

/* ------------------------------------------------------------------------- */
//  Static メンバ
/* ------------------------------------------------------------------------- */
void OpenJTalk::Init(Handle<Object>& target)
{
	auto clazz = FunctionTemplate::New(OpenJTalk::New);
	clazz->SetClassName( String::NewSymbol("OpenJTalk") );
	clazz->InstanceTemplate()->SetInternalFieldCount(1);

	NODE_SET_PROTOTYPE_METHOD(clazz, "talk", OpenJTalk::Talk);
	NODE_SET_PROTOTYPE_METHOD(clazz, "stop", OpenJTalk::Stop);

	target->Set( String::NewSymbol("OpenJTalk"), clazz->GetFunction() );
}


Handle<v8::Value> OpenJTalk::New(const Arguments& args)
{
	HandleScope scope;

	// 引数の数をチェック
	if (args.Length() < 2) {
		Local<String> msg = String::New("[OpenJTalk] Error! Number of arguments must be greater than 2.");
		ThrowException(Exception::TypeError(msg));
		return scope.Close( Undefined() );
	}

	// 音声/辞書ディレクトリの取得
	String::Utf8Value voice_dir(args[0]);
	String::Utf8Value dic_dir(args[1]);

	// OpenJTalk のパラメタ取得
	OpenJTalk_params params;
	if (args[2]->IsObject()) {
		auto obj = Local<Object>::Cast(args[2]);
		if (obj->Get(String::New("sampling_rate"))->IsInt32())
			params.sampling_rate = obj->Get(String::New("sampling_rate"))->Int32Value();
		if (obj->Get(String::New("stage"))->IsInt32())
			params.stage = obj->Get(String::New("stage"))->Int32Value();
		if (obj->Get(String::New("audio_buff_size"))->IsInt32())
			params.audio_buff_size = obj->Get(String::New("audio_buff_size"))->Int32Value();
		if (obj->Get(String::New("alpha"))->IsNumber())
			params.alpha = obj->Get(String::New("alpha"))->NumberValue();
		if (obj->Get(String::New("beta"))->IsNumber())
			params.beta = obj->Get(String::New("beta"))->NumberValue();
		if (obj->Get(String::New("uv_threshold"))->IsNumber())
			params.uv_threshold = obj->Get(String::New("uv_threshold"))->NumberValue();
		if (obj->Get(String::New("gv_weight_mgc"))->IsNumber())
			params.gv_weight_mgc = obj->Get(String::New("gv_weight_mgc"))->NumberValue();
		if (obj->Get(String::New("gv_weight_lf0"))->IsNumber())
			params.gv_weight_lf0 = obj->Get(String::New("gv_weight_lf0"))->NumberValue();
		if (obj->Get(String::New("gv_weight_lpf"))->IsNumber())
			params.gv_weight_lpf = obj->Get(String::New("gv_weight_lpf"))->NumberValue();
	}

	// this に OpenJTalk クラスを格納
	auto _this = new OpenJTalk(*voice_dir, *dic_dir, params);
	_this->Wrap( args.This() );

	return scope.Close( args.This() );
}


Handle<v8::Value> OpenJTalk::Talk(const Arguments& args)
{
	HandleScope scope;

	// やり取りするデータを作成
	String::Utf8Value str(args[0]);
	auto req       = new uv_work_t;
	auto data      = new TalkData();
	data->self     = ObjectWrap::Unwrap<OpenJTalk>( args.This() );
	data->str      = *str;
	if ( args[1]->IsInt32() ) {
		data->fperiod = args[1]->Int32Value();
	}
	for (int i = 1; i <= 2; ++i) {
		if ( args[i]->IsFunction() ) {
			data->callback = Persistent<Function>::New( args[i].As<Function>() );
			data->cb_flag  = true;
		}
	}
	req->data = data;

	// 非同期で喋らせて喋り終わったらコールバックを呼ぶ
	uv_queue_work(
		uv_default_loop(),
		req,
		[](uv_work_t* req) {
			auto data = static_cast<TalkData*>(req->data);
			auto self = static_cast<OpenJTalk*>(data->self);
			data->err = self->talk(data->str, data->fperiod);
		},
		[](uv_work_t* req) {
			HandleScope scope;

			auto data = static_cast<TalkData*>(req->data);
			auto self = static_cast<OpenJTalk*>(data->self);

			TryCatch tc;
			Handle<v8::Value> argv[] = { String::New(data->err.c_str()) };
			if (data->cb_flag) {
				data->callback->Call(self->handle_, 1, argv);
			}
			if ( tc.HasCaught() ) {
				FatalException(tc);
			}
		}
	);

	return scope.Close( Undefined() );
}


Handle<v8::Value> OpenJTalk::Stop(const Arguments& args)
{
	HandleScope scope;

	auto _this = ObjectWrap::Unwrap<OpenJTalk>( args.This() );
	_this->stop();

	return scope.Close( Undefined() );
};


/* ------------------------------------------------------------------------- */
//  Non-static メンバ
/* ------------------------------------------------------------------------- */
OpenJTalk::OpenJTalk(const std::string& voice_dir_, const std::string& dic_dir, OpenJTalk_params params)
	: ObjectWrap(),
	  voice_dir_(voice_dir_),
	  dic_dir_(dic_dir),
	  params_(params)
{}


OpenJTalk::~OpenJTalk()
{
	Mecab_clear(&open_jtalk_data_.mecab);
	NJD_clear(&open_jtalk_data_.njd);
	JPCommon_clear(&open_jtalk_data_.jpcommon);
	HTS_Engine_clear(&open_jtalk_data_.engine);
}


void OpenJTalk::initialize(
	int sampling_rate, int fperiod, double alpha, int stage, double beta, int audio_buff_size,
	double uv_threshold, HTS_Boolean use_log_gain, double gv_weight_mgc,
	double gv_weight_lf0, double gv_weight_lpf)
{
	Mecab_initialize(&open_jtalk_data_.mecab);
	NJD_initialize(&open_jtalk_data_.njd);
	JPCommon_initialize(&open_jtalk_data_.jpcommon);
	HTS_Engine_initialize(&open_jtalk_data_.engine, 2);
	HTS_Engine_set_sampling_rate(&open_jtalk_data_.engine, sampling_rate);
	HTS_Engine_set_fperiod(&open_jtalk_data_.engine, fperiod);
	HTS_Engine_set_alpha(&open_jtalk_data_.engine, alpha);
	HTS_Engine_set_gamma(&open_jtalk_data_.engine, stage);
	HTS_Engine_set_log_gain(&open_jtalk_data_.engine, use_log_gain);
	HTS_Engine_set_beta(&open_jtalk_data_.engine, beta);
	HTS_Engine_set_audio_buff_size(&open_jtalk_data_.engine, audio_buff_size);
	HTS_Engine_set_msd_threshold(&open_jtalk_data_.engine, 1, uv_threshold);
	HTS_Engine_set_gv_weight(&open_jtalk_data_.engine, 0, gv_weight_mgc);
	HTS_Engine_set_gv_weight(&open_jtalk_data_.engine, 1, gv_weight_lf0);
}


void OpenJTalk::load(
	char *dn_mecab, char *fn_ms_dur, char *fn_ts_dur,
	char *fn_ms_mgc, char *fn_ts_mgc, char **fn_ws_mgc, int num_ws_mgc,
	char *fn_ms_lf0, char *fn_ts_lf0, char **fn_ws_lf0, int num_ws_lf0,
	char *fn_ms_lpf, char *fn_ts_lpf, char **fn_ws_lpf, int num_ws_lpf,
	char *fn_ms_gvm, char *fn_ts_gvm, char *fn_ms_gvl, char *fn_ts_gvl,
	char *fn_ms_gvf, char *fn_ts_gvf, char *fn_gv_switch)
{
	Mecab_load(&open_jtalk_data_.mecab, dn_mecab);
	HTS_Engine_load_duration_from_fn(&open_jtalk_data_.engine, &fn_ms_dur, &fn_ts_dur, 1);
	HTS_Engine_load_parameter_from_fn(&open_jtalk_data_.engine, &fn_ms_mgc, &fn_ts_mgc, fn_ws_mgc, 0, FALSE, num_ws_mgc, 1);
	HTS_Engine_load_parameter_from_fn(&open_jtalk_data_.engine, &fn_ms_lf0, &fn_ts_lf0, fn_ws_lf0, 1, TRUE, num_ws_lf0, 1);
	if (HTS_Engine_get_nstream(&open_jtalk_data_.engine) == 3)
		HTS_Engine_load_parameter_from_fn(&open_jtalk_data_.engine, &fn_ms_lpf, &fn_ts_lpf, fn_ws_lpf, 2, FALSE, num_ws_lpf, 1);
	if (fn_ms_gvm != nullptr) {
		if (fn_ts_gvm != nullptr)
			HTS_Engine_load_gv_from_fn(&open_jtalk_data_.engine, &fn_ms_gvm, &fn_ts_gvm, 0, 1);
		else
			HTS_Engine_load_gv_from_fn(&open_jtalk_data_.engine, &fn_ms_gvm, nullptr, 0, 1);
	}
	if (fn_ms_gvl != nullptr) {
		if (fn_ts_gvl != nullptr)
			HTS_Engine_load_gv_from_fn(&open_jtalk_data_.engine, &fn_ms_gvl, &fn_ts_gvl, 1, 1);
		else
			HTS_Engine_load_gv_from_fn(&open_jtalk_data_.engine, &fn_ms_gvl, nullptr, 1, 1);
	}
	if (HTS_Engine_get_nstream(&open_jtalk_data_.engine) == 3 && fn_ms_gvf != nullptr) {
		if (fn_ts_gvf != nullptr)
			HTS_Engine_load_gv_from_fn(&open_jtalk_data_.engine, &fn_ms_gvf, &fn_ts_gvf, 2, 1);
		else
			HTS_Engine_load_gv_from_fn(&open_jtalk_data_.engine, &fn_ms_gvf, nullptr, 2, 1);
	}
	if (fn_gv_switch != nullptr)
		HTS_Engine_load_gv_switch_from_fn(&open_jtalk_data_.engine, fn_gv_switch);
}


void OpenJTalk::synthesis(char *txt, FILE * wavfp)
{
	char buff[MAXBUFLEN];

	text2mecab(buff, txt);
	Mecab_analysis(&open_jtalk_data_.mecab, buff);
	mecab2njd(&open_jtalk_data_.njd, Mecab_get_feature(&open_jtalk_data_.mecab), Mecab_get_size(&open_jtalk_data_.mecab));
	njd_set_pronunciation(&open_jtalk_data_.njd);
	njd_set_digit(&open_jtalk_data_.njd);
	njd_set_accent_phrase(&open_jtalk_data_.njd);
	njd_set_accent_type(&open_jtalk_data_.njd);
	njd_set_unvoiced_vowel(&open_jtalk_data_.njd);
	njd_set_long_vowel(&open_jtalk_data_.njd);
	njd2jpcommon(&open_jtalk_data_.jpcommon, &open_jtalk_data_.njd);
	JPCommon_make_label(&open_jtalk_data_.jpcommon);
	if (JPCommon_get_label_size(&open_jtalk_data_.jpcommon) > 2) {
		HTS_Engine_load_label_from_string_list(
			&open_jtalk_data_.engine,
			JPCommon_get_label_feature(&open_jtalk_data_.jpcommon),
			JPCommon_get_label_size(&open_jtalk_data_.jpcommon)
		);
		HTS_Engine_create_sstream(&open_jtalk_data_.engine);
		HTS_Engine_create_pstream(&open_jtalk_data_.engine);
		HTS_Engine_create_gstream(&open_jtalk_data_.engine);
		if (wavfp != nullptr) {
			HTS_Engine_save_riff(&open_jtalk_data_.engine, wavfp);
		}
		HTS_Engine_refresh(&open_jtalk_data_.engine);
	}
	JPCommon_refresh(&open_jtalk_data_.jpcommon);
	NJD_refresh(&open_jtalk_data_.njd);
	Mecab_refresh(&open_jtalk_data_.mecab);
}


void OpenJTalk::make_wav(const std::string& wav_file_path, const std::string& sentence, int fperiod)
{
	// 喋らせる文字列
	auto talk_str = make_vec_char(sentence);

	// dictionary directory name
	auto dn_mecab = make_vec_char(dic_dir_);

	// model file names
	auto fn_ms_dur  = make_vec_char(voice_dir_ + "/dur.pdf");
	auto fn_ms_mgc  = make_vec_char(voice_dir_ + "/mgc.pdf");
	auto fn_ms_lf0  = make_vec_char(voice_dir_ + "/lf0.pdf");
	char *fn_ms_lpf = nullptr;

	// tree file names
	auto fn_ts_dur = make_vec_char(voice_dir_ + "/tree-dur.inf");
	auto fn_ts_mgc = make_vec_char(voice_dir_ + "/tree-mgc.inf");
	auto fn_ts_lf0 = make_vec_char(voice_dir_ + "/tree-lf0.inf");
	char *fn_ts_lpf = nullptr;

	// window file names
	std::vector<char*> fn_ws_mgc;
	std::vector<char*> fn_ws_lf0;
	char **fn_ws_lpf = nullptr;
	auto fn_ws_mgc_buf1 = make_vec_char(voice_dir_ + "/mgc.win1");
	auto fn_ws_lf0_buf1 = make_vec_char(voice_dir_ + "/lf0.win1");
	auto fn_ws_mgc_buf2 = make_vec_char(voice_dir_ + "/mgc.win2");
	auto fn_ws_lf0_buf2 = make_vec_char(voice_dir_ + "/lf0.win2");
	auto fn_ws_mgc_buf3 = make_vec_char(voice_dir_ + "/mgc.win3");
	auto fn_ws_lf0_buf3 = make_vec_char(voice_dir_ + "/lf0.win3");
	fn_ws_mgc.push_back(&fn_ws_mgc_buf1[0]);
	fn_ws_lf0.push_back(&fn_ws_lf0_buf1[0]);
	fn_ws_mgc.push_back(&fn_ws_mgc_buf2[0]);
	fn_ws_lf0.push_back(&fn_ws_lf0_buf2[0]);
	fn_ws_mgc.push_back(&fn_ws_mgc_buf3[0]);
	fn_ws_lf0.push_back(&fn_ws_lf0_buf3[0]);
	const int num_ws_mgc = 3, num_ws_lf0 = 3, num_ws_lpf = 0;

	// global variance file names
	auto fn_ms_gvm = make_vec_char(voice_dir_ + "/gv-mgc.pdf");
	auto fn_ms_gvf = make_vec_char(voice_dir_ + "/gv-lf0.pdf");
	char *fn_ms_gvl = nullptr;

	// global variance trees file names
	auto fn_ts_gvm = make_vec_char(voice_dir_ + "/tree-gv-mgc.inf");
	auto fn_ts_gvf = make_vec_char(voice_dir_ + "/tree-gv-lf0.inf");
	char *fn_ts_gvl = nullptr;

	// global variance switch file names
	auto fn_gv_switch = make_vec_char(voice_dir_ + "/gv-switch.inf");

	// global parameter
	int    sampling_rate   = params_.sampling_rate;
	double alpha           = params_.alpha;
	int    stage           = params_.stage;
	double beta            = params_.beta;
	int    audio_buff_size = params_.audio_buff_size;
	double uv_threshold    = params_.uv_threshold;
	double gv_weight_mgc   = params_.gv_weight_mgc;
	double gv_weight_lf0   = params_.gv_weight_lf0;
	double gv_weight_lpf   = params_.gv_weight_lpf;
	HTS_Boolean use_log_gain = FALSE;

	// initialize and load
	initialize(sampling_rate, fperiod, alpha, stage, beta,
		audio_buff_size, uv_threshold, use_log_gain, gv_weight_mgc,
		gv_weight_lf0, gv_weight_lpf);
	load(&dn_mecab[0], &fn_ms_dur[0], &fn_ts_dur[0], &fn_ms_mgc[0], &fn_ts_mgc[0],
		&fn_ws_mgc[0], num_ws_mgc, &fn_ms_lf0[0], &fn_ts_lf0[0], &fn_ws_lf0[0], num_ws_lf0,
		fn_ms_lpf, fn_ts_lpf, fn_ws_lpf, num_ws_lpf, &fn_ms_gvm[0], &fn_ts_gvm[0],
		fn_ms_gvl, fn_ts_gvl, &fn_ms_gvf[0], &fn_ts_gvf[0], &fn_gv_switch[0]);

	// output wav file
	FILE *wavfp = fopen(wav_file_path.c_str(), "wb");
	if (wavfp == nullptr) {
		std::cerr << "Cannot open: " << wav_file_path << std::endl;
		return;
	}

	// synthesis
	synthesis(&talk_str[0], wavfp);

	// free
	fclose(wavfp);
}


std::string OpenJTalk::get_wav_name()
{
	using namespace boost::uuids;
	const uuid id = random_generator()();
	const std::string file_path = boost::lexical_cast<std::string>(id) + ".wav";
	return file_path;
}


std::string OpenJTalk::play_wav(const std::string& wav_file_path)
{
	SF_INFO sfinfo;
	SNDFILE *file = sf_open(wav_file_path.c_str(), SFM_READ, &sfinfo);
	float msec = static_cast<float>(sfinfo.frames) / static_cast<float>(sfinfo.samplerate) * 1000;

	// PortAudio の初期化
	PaError err = Pa_Initialize();
	if (err) return Pa_GetErrorText(err);

	PaStreamParameters out_param;
	out_param.device = Pa_GetDefaultOutputDevice();
	if (out_param.device == paNoDevice) {
		return "Haven't found an audio device!";
	}

	// PortAudio の設定
	out_param.channelCount              = sfinfo.channels;
	out_param.sampleFormat              = paInt16;
	out_param.suggestedLatency          = Pa_GetDeviceInfo(out_param.device)->defaultLowOutputLatency;
	out_param.hostApiSpecificStreamInfo = NULL;

	// ファイルを開く
	PaStream *stream;
	err = Pa_OpenStream(
		&stream,
		NULL,
		&out_param,
		sfinfo.samplerate,
		paFramesPerBufferUnspecified,
		paClipOff,
		[](const void *input, void *output, unsigned long frames_per_buffer,
		   const PaStreamCallbackTimeInfo *time_info,
		   PaStreamCallbackFlags flags, void *data) -> int
		{
			sf_read_short(static_cast<SNDFILE*>(data), static_cast<short*>(output), frames_per_buffer);
			return paContinue;
		},
		file
	);
	if (err) return Pa_GetErrorText(err);

	err = Pa_SetStreamFinishedCallback(stream, [](void *data){/* なにもしない */});

	// 再生
	err = Pa_StartStream(stream);
	if (err) return Pa_GetErrorText(err);

	Pa_Sleep(msec + 100);
	Pa_StopStream(stream);

	// 片付け
	err = Pa_CloseStream(stream);
	if (err) return Pa_GetErrorText(err);

	sf_close(file);
	Pa_Terminate();

	return "";
}


void OpenJTalk::stop()
{
	// 未実装
}


void OpenJTalk::remove_wav(const std::string& wav_file_path) const
{
	remove( wav_file_path.c_str() );
}


std::string OpenJTalk::talk(const std::string& str, int fperiod, bool async)
{
	auto wav_file_path = get_wav_name();
	uv_mutex_lock(&m);
	make_wav(wav_file_path, str, fperiod);
	uv_mutex_unlock(&m);
	std::string err_msg = play_wav(wav_file_path);
	remove_wav(wav_file_path);

	return err_msg;
}


/* ------------------------------------------------------------------------- */
//  node.js の addon 化
/* ------------------------------------------------------------------------- */
void init(Handle<Object> target)
{
	assert( uv_mutex_init(&m) == 0 );
	emit_symbol = NODE_PSYMBOL("emit");
	OpenJTalk::Init(target);
}

NODE_MODULE(openjtalk, init)
