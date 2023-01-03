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
   " ", "�@",
   "!", "�I",
   "\"", "�h",
   "#", "��",
   "$", "��",
   "%", "��",
   "&", "��",
   "'", "�f",
   "(", "�i",
   ")", "�j",
   "*", "��",
   "+", "�{",
   ",", "�C",
   "-", "�|",
   ".", "�D",
   "/", "�^",
   "0", "�O",
   "1", "�P",
   "2", "�Q",
   "3", "�R",
   "4", "�S",
   "5", "�T",
   "6", "�U",
   "7", "�V",
   "8", "�W",
   "9", "�X",
   ":", "�F",
   ";", "�G",
   "<", "��",
   "=", "��",
   ">", "��",
   "?", "�H",
   "@", "��",
   "A", "�`",
   "B", "�a",
   "C", "�b",
   "D", "�c",
   "E", "�d",
   "F", "�e",
   "G", "�f",
   "H", "�g",
   "I", "�h",
   "J", "�i",
   "K", "�j",
   "L", "�k",
   "M", "�l",
   "N", "�m",
   "O", "�n",
   "P", "�o",
   "Q", "�p",
   "R", "�q",
   "S", "�r",
   "T", "�s",
   "U", "�t",
   "V", "�u",
   "W", "�v",
   "X", "�w",
   "Y", "�x",
   "Z", "�y",
   "[", "�m",
   "\\", "��",
   "]", "�n",
   "^", "�O",
   "_", "�Q",
   "`", "�e",
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
   "{", "�o",
   "|", "�b",
   "}", "�p",
   "~", "�`",
   "��", "��",
   "��", "�K",
   "��", "�M",
   "��", "�O",
   "��", "�Q",
   "��", "�S",
   "��", "�U",
   "��", "�W",
   "��", "�Y",
   "��", "�[",
   "��", "�]",
   "��", "�_",
   "��", "�a",
   "��", "�d",
   "��", "�f",
   "��", "�h",
   "��", "�o",
   "��", "�r",
   "��", "�u",
   "��", "�x",
   "��", "�{",
   "��", "�p",
   "��", "�s",
   "��", "�v",
   "��", "�y",
   "��", "�|",
   "�", "�B",
   "�", "�u",
   "�", "�v",
   "�", "�A",
   "�", "�E",
   "�", "��",
   "�", "�@",
   "�", "�B",
   "�", "�D",
   "�", "�F",
   "�", "�H",
   "�", "��",
   "�", "��",
   "�", "��",
   "�", "�b",
   "�", "�[",
   "�", "�A",
   "�", "�C",
   "�", "�E",
   "�", "�G",
   "�", "�I",
   "�", "�J",
   "�", "�L",
   "�", "�N",
   "�", "�P",
   "�", "�R",
   "�", "�T",
   "�", "�V",
   "�", "�X",
   "�", "�Z",
   "�", "�\",
   "�", "�^",
   "�", "�`",
   "�", "�c",
   "�", "�e",
   "�", "�g",
   "�", "�i",
   "�", "�j",
   "�", "�k",
   "�", "�l",
   "�", "�m",
   "�", "�n",
   "�", "�q",
   "�", "�t",
   "�", "�w",
   "�", "�z",
   "�", "�}",
   "�", "�~",
   "�", "��",
   "�", "��",
   "�", "��",
   "�", "��",
   "�", "��",
   "�", "��",
   "�", "��",
   "�", "��",
   "�", "��",
   "�", "��",
   "�", "��",
   "�", "��",
   "�", "��",
   "�", "",
   "�", "",
   NULL, NULL
};

TEXT2MECAB_RULE_H_END;

#endif                          /* !TEXT2MECAB_RULE_H */
