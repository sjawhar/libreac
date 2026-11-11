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

#ifndef REAC_FACTS_CONTROL_BLOCK_H
#define REAC_FACTS_CONTROL_BLOCK_H

/* ---- The 32-byte control block and its two checksums ---------------------------
 * Every non-FILLER frame carries a 32-byte control block at frame[18:50],
 * whose last byte is a checksum over the block. A FILLER frame (type word
 * 0x0000) carries audio there instead and is checksum-exempt.
 *
 * There are TWO checksum rules and they differ. The block sums to 0 mod 256.
 * A nested record inside it — the Roland DT1 head-amp record and its
 * relatives — sums to 0x80. The record's is stamped FIRST: a record fixed up
 * after the block is stamped invalidates the block, which is a real bug this
 * ordering exists to prevent.
 */
/* Frame offset of the control block. [EVIDENCED (corpus).] */
#define REAC_CTRL_BLOCK_OFF             18

/* One past the end — and therefore the audio offset. [EVIDENCED (corpus).] */
#define REAC_CTRL_BLOCK_END             50

/* The checksummed span. [EVIDENCED (corpus).] */
#define REAC_CTRL_BLOCK_LEN             32

/* The checksum byte, last of the block. Block-relative 31. [EVIDENCED
 * (corpus).]
 */
#define REAC_CTRL_CKSUM_OFF             49

/* The same byte, block-relative — what a caller stamping a bare 32-byte block
 * indexes. [EVIDENCED (corpus).]
 */
#define REAC_CTRL_CKSUM_OFF_IN_BLOCK    31

/* Sum(block[0..31]) mod 256 must equal this. [EVIDENCED (corpus) — every
 * control frame in the corpus.]
 */
#define REAC_CTRL_BLOCK_SUM             0x00

/* Sum(record TAG..CKSUM) mod 256 must equal this. The Roland DT1 rule, and
 * NOT the block rule. [EVIDENCED (corpus).]
 */
#define REAC_CTRL_RECORD_SUM            0x80

/* Frame offset of the type word — the start of the [16:50] window the goldens
 * store and the C tests use. [EVIDENCED (corpus).]
 */
#define REAC_TYPED_BLOCK_OFF            16

/* Type word (2) + control block (32). [EVIDENCED (corpus).] */
#define REAC_TYPED_BLOCK_LEN            34

#endif /* REAC_FACTS_CONTROL_BLOCK_H */
