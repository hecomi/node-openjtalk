/* ----------------------------------------------------------------- */
/*           The Japanese TTS System "Open JTalk"                    */
/*           developed by HTS Working Group                          */
/*           http://open-jtalk.sourceforge.net/                      */
/* ----------------------------------------------------------------- */
/*                                                                   */
/*  Copyright (c) 2008-2016  Nagoya Institute of Technology          */
/*                           Department of Computer Science          */
/*                                                                   */
/* All rights reserved.                                              */
/*                                                                   */
/* Redistribution and use in source and binary forms, with or        */
/* without modification, are permitted provided that the following   */
/* conditions are met:                                               */
/*                                                                   */
/* - Redistributions of source code must retain the above copyright  */
/*   notice, this list of conditions and the following disclaimer.   */
/* - Redistributions in binary form must reproduce the above         */
/*   copyright notice, this list of conditions and the following     */
/*   disclaimer in the documentation and/or other materials provided */
/*   with the distribution.                                          */
/* - Neither the name of the HTS working group nor the names of its  */
/*   contributors may be used to endorse or promote products derived */
/*   from this software without specific prior written permission.   */
/*                                                                   */
/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND            */
/* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,       */
/* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF          */
/* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE          */
/* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS */
/* BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,          */
/* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED   */
/* TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,     */
/* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON */
/* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,   */
/* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY    */
/* OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE           */
/* POSSIBILITY OF SUCH DAMAGE.                                       */
/* ----------------------------------------------------------------- */

#ifndef TEXT2MECAB_RULE_H
#define TEXT2MECAB_RULE_H

#ifdef __cplusplus
#define TEXT2MECAB_RULE_H_START extern "C" {
#define TEXT2MECAB_RULE_H_END   }
#else
#define TEXT2MECAB_RULE_H_START
#define TEXT2MECAB_RULE_H_END
#endif                          /* __CPLUSPLUS */

TEXT2MECAB_RULE_H_START;

static const char text2mecab_control_range[] = {
   0x00, 0x7F
};

static const char text2mecab_kanji_range[] = {
#ifdef CHARSET_EUC_JP
   2, 0xA1, 0xFE,
   3, 0x8F, 0x8F,
#endif                          /* CHARSET_EUC_JP */
#ifdef CHARSET_SHIFT_JIS
   2, 0x81, 0xFC,
#endif                          /* CHARSET_SHIFT_JIS */
#ifdef CHARSET_UTF_8
   2, 0xC0, 0xDF,
   3, 0xE0, 0xEF,
   4, 0xF0, 0xF7,
#endif                          /* CHARSET_UTF_8 */
   -1, -1, -1
};

static const char *text2mecab_conv_list[] = {
   " ", "��",
   "!", "��",
   "\"", "��",
   "#", "��",
   "$", "��",
   "%", "��",
   "&", "��",
   "'", "��",
   "(", "��",
   ")", "��",
   "*", "��",
   "+", "��",
   ",", "��",
   "-", "��",
   ".", "��",
   "/", "��",
   "0", "��",
   "1", "��",
   "2", "��",
   "3", "��",
   "4", "��",
   "5", "��",
   "6", "��",
   "7", "��",
   "8", "��",
   "9", "��",
   ":", "��",
   ";", "��",
   "<", "��",
   "=", "��",
   ">", "��",
   "?", "��",
   "@", "��",
   "A", "��",
   "B", "��",
   "C", "��",
   "D", "��",
   "E", "��",
   "F", "��",
   "G", "��",
   "H", "��",
   "I", "��",
   "J", "��",
   "K", "��",
   "L", "��",
   "M", "��",
   "N", "��",
   "O", "��",
   "P", "��",
   "Q", "��",
   "R", "��",
   "S", "��",
   "T", "��",
   "U", "��",
   "V", "��",
   "W", "��",
   "X", "��",
   "Y", "��",
   "Z", "��",
   "[", "��",
   "\\", "��",
   "]", "��",
   "^", "��",
   "_", "��",
   "`", "��",
   "a", "��",
   "b", "��",
   "c", "��",
   "d", "��",
   "e", "��",
   "f", "��",
   "g", "��",
   "h", "��",
   "i", "��",
   "j", "��",
   "k", "��",
   "l", "��",
   "m", "��",
   "n", "��",
   "o", "��",
   "p", "��",
   "q", "��",
   "r", "��",
   "s", "��",
   "t", "��",
   "u", "��",
   "v", "��",
   "w", "��",
   "x", "��",
   "y", "��",
   "z", "��",
   "{", "��",
   "|", "��",
   "}", "��",
   "~", "��",
   "����", "��",
   "����", "��",
   "����", "��",
   "����", "��",
   "����", "��",
   "����", "��",
   "����", "��",
   "����", "��",
   "����", "��",
   "����", "��",
   "����", "��",
   "����", "��",
   "����", "��",
   "��", "��",
   "�Î�", "��",
   "�Ď�", "��",
   "�ʎ�", "��",
   "�ˎ�", "��",
   "�̎�", "��",
   "�͎�", "��",
   "�Ύ�", "��",
   "�ʎ�", "��",
   "�ˎ�", "��",
   "�̎�", "��",
   "�͎�", "��",
   "�Ύ�", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "��",
   "��", "",
   "��", "",
   NULL, NULL
};

TEXT2MECAB_RULE_H_END;

#endif                          /* !TEXT2MECAB_RULE_H */
