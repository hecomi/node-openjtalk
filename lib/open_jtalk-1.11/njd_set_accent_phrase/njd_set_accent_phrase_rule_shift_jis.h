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
  Rule 01 �f�t�H���g�͂�������
  Rule 02 �u�����v�̘A���͂�������
  Rule 03 �u�`�e���v�̌�Ɂu�����v��������ʂ̃A�N�Z���g���
  Rule 04 �u����,�`�e�����ꊲ�v�̌�Ɂu�����v��������ʂ̃A�N�Z���g���
  Rule 05 �u�����v�̌�Ɂu�`�e���vor�u�����v��������ʂ̃A�N�Z���g���
  Rule 06 �u�����v�C�u�ڑ����v�C�u�A�̎��v�͒P�Ƃ̃A�N�Z���g���
  Rule 07 �u����,�����\�v�i���ׂāC�Ȃǁj�͒P�Ƃ̃A�N�Z���g���
  Rule 08 �u�����vor�u�������v�i�t����j�͑O�ɂ�������
  Rule 09 �u�����vor�u�������v�i�t����j�̌�́u�����v�C�u�������v�ȊO�i������j�͕ʂ̃A�N�Z���g���
  Rule 10 �u*,�ڔ��v�̌�́u�����v�͕ʂ̃A�N�Z���g���
  Rule 11 �u�`�e��,�񎩗��v�́u����,�A�p*�vor�u�`�e��,�A�p*�vor�u����,�ڑ�����,�āvor�u����,�ڑ�����,�Łv�ɐڑ�����ꍇ�ɑO�ɂ�������
  Rule 12 �u����,�񎩗��v�́u����,�A�p*�vor�u����,�T�ϐڑ��v�ɐڑ�����ꍇ�ɑO�ɂ�������
  Rule 13 �u�����v�̌�Ɂu�����vor�u�`�e���vor�u����,�`�e�����ꊲ�v��������ʂ̃A�N�Z���g���
  Rule 14 �u�L���v�͒P�Ƃ̃A�N�Z���g���
  Rule 15 �u�ړ����v�͒P�Ƃ̃A�N�Z���g���
  Rule 16 �u*,*,*,���v�̌�́u�����v�͕ʂ̃A�N�Z���g���
  Rule 17 �u�����v�̌�́u*,*,*,���v�͕ʂ̃A�N�Z���g���
  Rule 18 �u*,�ڔ��v�͑O�ɂ�������
*/

#define NJD_SET_ACCENT_PHRASE_MEISHI "����"
#define NJD_SET_ACCENT_PHRASE_KEIYOUSHI "�`�e��"
#define NJD_SET_ACCENT_PHRASE_DOUSHI "����"
#define NJD_SET_ACCENT_PHRASE_FUKUSHI "����"
#define NJD_SET_ACCENT_PHRASE_SETSUZOKUSHI "�ڑ���"
#define NJD_SET_ACCENT_PHRASE_RENTAISHI "�A�̎�"
#define NJD_SET_ACCENT_PHRASE_JODOUSHI "������"
#define NJD_SET_ACCENT_PHRASE_JOSHI "����"
#define NJD_SET_ACCENT_PHRASE_KIGOU "�L��"
#define NJD_SET_ACCENT_PHRASE_KEIYOUDOUSHI_GOKAN "�`�e�����ꊲ"
#define NJD_SET_ACCENT_PHRASE_FUKUSHI_KANOU "�����\"
#define NJD_SET_ACCENT_PHRASE_SETSUBI "�ڔ�"
#define NJD_SET_ACCENT_PHRASE_HIJIRITSU "�񎩗�"
#define NJD_SET_ACCENT_PHRASE_RENYOU "�A�p"
#define NJD_SET_ACCENT_PHRASE_SETSUZOKUJOSHI "�ڑ�����"
#define NJD_SET_ACCENT_PHRASE_SAHEN_SETSUZOKU "�T�ϐڑ�"
#define NJD_SET_ACCENT_PHRASE_TE "��"
#define NJD_SET_ACCENT_PHRASE_DE "��"
#define NJD_SET_ACCENT_PHRASE_SETTOUSHI "�ړ���"
#define NJD_SET_ACCENT_PHRASE_SEI "��"
#define NJD_SET_ACCENT_PHRASE_MEI "��"

NJD_SET_ACCENT_PHRASE_RULE_H_END;

#endif                          /* !NJD_SET_ACCENT_PHRASE_RULE_H */
