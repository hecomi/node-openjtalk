{
	'variables': {
		'openjtalk_dir' : '<(module_root_dir)/lib/open_jtalk-1.05',
		'htsengine_dir' : '<(module_root_dir)/lib/hts_engine_API-1.06',
		'cflags'        : '-std=c++0x -fexceptions',
		'cflags!'       : '-fno-exception',
	},
	'targets': [
		{
			'target_name'    : 'openjtalk',
			'sources'        : [
				'src/openjtalk.cpp',
			],
			'cflags'         : [
				'<@(cflags)',
			],
			'cflags_cc'      : [
				'<@(cflags)',
			],
			'cflags!'        : [
				'<@(cflags!)',
			],
			'cflags_cc!'     : [
				'<@(cflags!)',
			],
			'include_dirs'   : [
				'<(openjtalk_dir)/mecab',
				'<(openjtalk_dir)/text2mecab',
				'<(openjtalk_dir)/mecab/src',
				'<(openjtalk_dir)/mecab2njd',
				'<(openjtalk_dir)/njd',
				'<(openjtalk_dir)/njd_set_pronunciation',
				'<(openjtalk_dir)/njd_set_digit',
				'<(openjtalk_dir)/njd_set_accent_phrase',
				'<(openjtalk_dir)/njd_set_accent_type',
				'<(openjtalk_dir)/njd_set_unvoiced_vowel',
				'<(openjtalk_dir)/njd_set_long_vowel',
				'<(openjtalk_dir)/njd2jpcommon',
				'<(openjtalk_dir)/jpcommon',
				'<(htsengine_dir)/include',
			],
			'link_settings': {
				'libraries': [
					'<(openjtalk_dir)/text2mecab/libtext2mecab.a',
					'<(openjtalk_dir)/mecab/src/libmecab.a',
					'<(openjtalk_dir)/mecab2njd/libmecab2njd.a',
					'<(openjtalk_dir)/njd/libnjd.a',
					'<(openjtalk_dir)/njd_set_pronunciation/libnjd_set_pronunciation.a',
					'<(openjtalk_dir)/njd_set_digit/libnjd_set_digit.a',
					'<(openjtalk_dir)/njd_set_accent_phrase/libnjd_set_accent_phrase.a',
					'<(openjtalk_dir)/njd_set_accent_type/libnjd_set_accent_type.a',
					'<(openjtalk_dir)/njd_set_unvoiced_vowel/libnjd_set_unvoiced_vowel.a',
					'<(openjtalk_dir)/njd_set_long_vowel/libnjd_set_long_vowel.a',
					'<(openjtalk_dir)/njd2jpcommon/libnjd2jpcommon.a',
					'<(openjtalk_dir)/jpcommon/libjpcommon.a',
					'<(htsengine_dir)/lib/libHTSEngine.a',
					'-lsndfile',
					'-lportaudio',
				],
				'ldflags': [
				],
			},
			'conditions': [
				['OS=="mac"', {
					'include_dirs' : [
						'/usr/local/include/libcxx',
					],
					'xcode_settings' : {
						'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
						'OTHER_CFLAGS': [
							'<@(cflags)',
						],
					},
				}],
			],
		},
	],
}
