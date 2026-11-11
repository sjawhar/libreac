// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 Pau Aliagas <linuxnow@gmail.com>
//
// GENERATED FILE - DO NOT EDIT.
//
// Source:    spec/protocol-facts.yaml   (in FreeREAC/reac-protocol)
// Generator: spec/gen-facts.py
//
// Edit the schema and regenerate. A hand-edit here is erased by the next run
// and, worse, is invisible to the cross-check that keeps reac.ksy and libreac
// agreeing - which is the whole reason this file is generated.

#ifndef REAC_FACTS_DT1_FRAME_H
#define REAC_FACTS_DT1_FRAME_H

/* ---- The Roland DT1 record inside op-0403 --------------------------------------
 * The link-4 container's record, byte for byte. reac.ksy spells it as
 * `dt1_record` contents; libreac's reac_ctrlblk.c and reac_box_synth.c
 * wrote the same bytes and block offsets as literals (`out[9] = 0xf0`,
 * `blk[15] == 0x12`), and reac-pw's pcap-variants.py a third time. Block
 * offsets are block-relative, like every offset in this file.
 */
/* The four bytes at block[4:8] ahead of every DT1 record and record fragment.
 * Its tail `02 00 fe` is the box-return marker's too, which is why
 * SUB_0403_OFF alone discriminates them. [EVIDENCED (corpus).]
 */
#define REAC_DT1_WRAPPER                0x000200fe

/* Width of DT1_WRAPPER. [EVIDENCED (corpus).] */
#define REAC_DT1_WRAPPER_BYTES          4

/* Block offset of the SysEx length echo, right after the wrapper. [EVIDENCED
 * (corpus).]
 */
#define REAC_DT1_LEN_ECHO_OFF           8

/* Block offset of SYSEX_START. [EVIDENCED (corpus).] */
#define REAC_DT1_SYSEX_OFF              9

/* MIDI SysEx start. [EVIDENCED (corpus).] */
#define REAC_SYSEX_START                0xf0

/* Roland's SysEx manufacturer id. [EVIDENCED (corpus).] */
#define REAC_ROLAND_ID                  0x41

/* The device id byte every captured box-built record carries. [EVIDENCED
 * (corpus) — the cold-connect records of matrix-m200-s1608 and
 * matrix-m200-s0808 (2026-07-11). reac.ksy parses it as a free u1 and does
 * not validate it.]
 */
#define REAC_DT1_DEVICE_ID              0x0a

/* SYSEX_START, ROLAND_ID and the device id — the bytes before the model id.
 * [EVIDENCED (corpus).]
 */
#define REAC_DT1_SYSEX_HEAD_BYTES       3

/* The Roland model id, `00 00 12`. [EVIDENCED (corpus).] */
#define REAC_DT1_MODEL_ID_BYTES         3

/* The model id's low byte, which the classifier checks to tell a genuine DT1
 * record from the look-alikes. [EVIDENCED (corpus).]
 */
#define REAC_DT1_MODEL_ID_LO            0x12

/* Block offset of DT1_MODEL_ID_LO. [EVIDENCED (corpus).] */
#define REAC_DT1_MODEL_LO_OFF           14

/* Block offset of the command byte, DT_CMD_RQ1 or DT_CMD_DT1. [EVIDENCED
 * (corpus).]
 */
#define REAC_DT1_CMD_OFF                15

/* Block offset of the big-endian register-page tag (the dt1_tag group).
 * [EVIDENCED (corpus).]
 */
#define REAC_DT1_TAG_OFF                16

/* Roland RQ1 — a read request (the identity poll). [EVIDENCED (corpus).] */
#define REAC_DT_CMD_RQ1                 0x11

/* Roland DT1 — data set. [EVIDENCED (corpus).] */
#define REAC_DT_CMD_DT1                 0x12

/* MIDI SysEx end, after the inner checksum. [EVIDENCED (corpus).] */
#define REAC_SYSEX_END                  0xf7

/* rec_len minus the SysEx record's own length. [EVIDENCED (corpus).] */
#define REAC_DT1_RECORD_OVERHEAD        0x0d

/* rec_len minus the record's data bytes. [EVIDENCED (corpus).] */
#define REAC_DT1_DATA_OVERHEAD          0x10

#endif /* REAC_FACTS_DT1_FRAME_H */
