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

#ifndef REAC_FACTS_SCENE_H
#define REAC_FACTS_SCENE_H

/* ---- The scene push ------------------------------------------------------------
 * After link-up a desk pushes its scene to the box as one bounded transfer:
 * an op-0101 header declaring the total and carrying the body's first 24
 * bytes, 341 op-0100 chunks of 26, and an op-0102 final of 14.
 *
 *   24 + 341*26 + 14 = 8904 = 0x22c8
 *
 * The three sizes and the total are ONE fact, not four: the lengths a step
 * declares are what must sum to what the header declares. A body whose
 * lengths do not sum leaves the box waiting for bytes that never come.
 *
 * The box completes reassembly ONLY on the final chunk, and completion runs
 * its state-4 commit — the sole promoter of staged head-amp into the active
 * table. A transfer that stops short leaves the box in reassembly for the
 * life of the link.
 */
/* The declared total, 0x22c8. The box gates its header on this exact value.
 * [EVIDENCED (image, both sides) — the same constant resolved out of the
 * S-1608's own image and out of the master's.]
 */
#define REAC_SCENE_BYTES                8904   /* 0x22c8 */

/* Body bytes carried by the op-0101 header, at block[7:31]. [EVIDENCED (image
 * + corpus).]
 */
#define REAC_SCENE_HEAD_BYTES           24

/* Body bytes per op-0100, at block[5:31]. Its declared op_len. [EVIDENCED
 * (image + corpus).]
 */
#define REAC_SCENE_CHUNK_BYTES          26

/* Body bytes in the op-0102 final. 8880 mod 26 — a length like any other
 * chunk's, not a fixed block. [EVIDENCED (image + corpus).]
 */
#define REAC_SCENE_TAIL_BYTES           14

/* op-0100 count for a whole body. [EVIDENCED (corpus) — measured back-to-back
 * in 0.680 s on a real M-200i driving an S-1608.]
 */
#define REAC_SCENE_CHUNKS               341

/* Header + chunks + final. [derived.] */
#define REAC_SCENE_STEPS                343

/* Block offset of the op word. [EVIDENCED (image).] */
#define REAC_SCENE_OP_OFF               0

/* Block offset of the BE payload length. [EVIDENCED (image) — a big-endian
 * 16-bit store from the same variable the master passes to the memcpy that
 * fills the payload.]
 */
#define REAC_SCENE_LEN_OFF              2

/* Block offset of the reserved/subtype byte. Zero on every scene step; the
 * box refuses the frame otherwise. [EVIDENCED (image + executed trace).]
 */
#define REAC_SCENE_SUB_OFF              4

/* Block offset of a chunk's and the final's body bytes. [EVIDENCED (image).] */
#define REAC_SCENE_CHUNK_PAY_OFF        5

/* Block offset of the header's BE declared total. The header's payload
 * therefore starts two bytes later than a continuation's. [EVIDENCED (image)
 * — `movi20]
 */
#define REAC_SCENE_HEAD_TOTAL_OFF       5

/* Block offset of the header's 24 body bytes — which is why a capture of this
 * frame alone shows the ASCII "1234" that opens the body. [EVIDENCED (image +
 * corpus).]
 */
#define REAC_SCENE_HEAD_PAY_OFF         7

#endif /* REAC_FACTS_SCENE_H */
