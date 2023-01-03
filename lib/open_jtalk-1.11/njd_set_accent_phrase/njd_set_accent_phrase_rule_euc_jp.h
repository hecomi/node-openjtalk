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

#ifndef NJD_SET_ACCENT_PHRASE_RULE_H
#define NJD_SET_ACCENT_PHRASE_RULE_H

#ifdef __cplusplus
#define NJD_SET_ACCENT_PHRASE_RULE_H_START extern "C" {
#define NJD_SET_ACCENT_PHRASE_RULE_H_END   }
#else
#define NJD_SET_ACCENT_PHRASE_RULE_H_START
#define NJD_SET_ACCENT_PHRASE_RULE_H_END
#endif                          /* __CPLUSPLUS */

NJD_SET_ACCENT_PHRASE_RULE_H_START;

/*
  Rule 01 �ǥե���ȤϤ��äĤ���
  Rule 02 ��̾��פ�Ϣ³�Ϥ��äĤ���
  Rule 03 �ַ��ƻ�פθ�ˡ�̾��פ��������̤Υ�������ȶ��
  Rule 04 ��̾��,����ư��촴�פθ�ˡ�̾��פ��������̤Υ�������ȶ��
  Rule 05 ��ư��פθ�ˡַ��ƻ��or��̾��פ��������̤Υ�������ȶ��
  Rule 06 ������ס�����³��ס���Ϣ�λ�פ�ñ�ȤΥ�������ȶ��
  Rule 07 ��̾��,�����ǽ�סʤ��٤ơ��ʤɡˤ�ñ�ȤΥ�������ȶ��
  Rule 08 �ֽ����or�ֽ�ư��ס���°��ˤ����ˤ��äĤ���
  Rule 09 �ֽ����or�ֽ�ư��ס���°��ˤθ�Ρֽ���ס��ֽ�ư��װʳ��ʼ�Ω��ˤ��̤Υ�������ȶ��
  Rule 10 ��*,�����פθ�Ρ�̾��פ��̤Υ�������ȶ��
  Rule 11 �ַ��ƻ�,��Ω�פϡ�ư��,Ϣ��*��or�ַ��ƻ�,Ϣ��*��or�ֽ���,��³����,�ơ�or�ֽ���,��³����,�ǡפ���³����������ˤ��äĤ���
  Rule 12 ��ư��,��Ω�פϡ�ư��,Ϣ��*��or��̾��,������³�פ���³����������ˤ��äĤ���
  Rule 13 ��̾��פθ�ˡ�ư���or�ַ��ƻ��or��̾��,����ư��촴�פ��������̤Υ�������ȶ��
  Rule 14 �ֵ���פ�ñ�ȤΥ�������ȶ��
  Rule 15 ����Ƭ��פ�ñ�ȤΥ�������ȶ��
  Rule 16 ��*,*,*,���פθ�Ρ�̾��פ��̤Υ�������ȶ��
  Rule 17 ��̾��פθ�Ρ�*,*,*,̾�פ��̤Υ�������ȶ��
  Rule 18 ��*,�����פ����ˤ��äĤ���
*/

#define NJD_SET_ACCENT_PHRASE_MEISHI "̾��"
#define NJD_SET_ACCENT_PHRASE_KEIYOUSHI "���ƻ�"
#define NJD_SET_ACCENT_PHRASE_DOUSHI "ư��"
#define NJD_SET_ACCENT_PHRASE_FUKUSHI "����"
#define NJD_SET_ACCENT_PHRASE_SETSUZOKUSHI "��³��"
#define NJD_SET_ACCENT_PHRASE_RENTAISHI "Ϣ�λ�"
#define NJD_SET_ACCENT_PHRASE_JODOUSHI "��ư��"
#define NJD_SET_ACCENT_PHRASE_JOSHI "����"
#define NJD_SET_ACCENT_PHRASE_KIGOU "����"
#define NJD_SET_ACCENT_PHRASE_KEIYOUDOUSHI_GOKAN "����ư��촴"
#define NJD_SET_ACCENT_PHRASE_FUKUSHI_KANOU "�����ǽ"
#define NJD_SET_ACCENT_PHRASE_SETSUBI "����"
#define NJD_SET_ACCENT_PHRASE_HIJIRITSU "��Ω"
#define NJD_SET_ACCENT_PHRASE_RENYOU "Ϣ��"
#define NJD_SET_ACCENT_PHRASE_SETSUZOKUJOSHI "��³����"
#define NJD_SET_ACCENT_PHRASE_SAHEN_SETSUZOKU "������³"
#define NJD_SET_ACCENT_PHRASE_TE "��"
#define NJD_SET_ACCENT_PHRASE_DE "��"
#define NJD_SET_ACCENT_PHRASE_SETTOUSHI "��Ƭ��"
#define NJD_SET_ACCENT_PHRASE_SEI "��"
#define NJD_SET_ACCENT_PHRASE_MEI "̾"

NJD_SET_ACCENT_PHRASE_RULE_H_END;

#endif                          /* !NJD_SET_ACCENT_PHRASE_RULE_H */
