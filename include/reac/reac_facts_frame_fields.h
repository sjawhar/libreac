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

#ifndef REAC_FACTS_FRAME_FIELDS_H
#define REAC_FACTS_FRAME_FIELDS_H

/* ---- Frame field widths the geometry is built from -----------------------------
 * The widths the header offsets above are sums of. They were literals in
 * the `derived:` expressions of this very file (`2 + CTRL_BLOCK_LEN`) and
 * in every consumer that computed an offset (`frame + 16`, `50 + 2`), so
 * the offsets are now derived from them and a perturbation moves them
 * together.
 */
/* Frame offset of the EtherType, after the two 6-byte MAC addresses. libreac
 * and reac-pw tools open-code `frame[12] == 0x88 && frame[13] == 0x19` rather
 * than naming the position. [EVIDENCED (corpus) — every frame in 72 captures;
 * reac.ksy seq/0..2 (6 + 6, then the contents).]
 */
#define REAC_ETHERTYPE_OFF              12

/* A MAC address — the frame's destination and source, the scene's master_id
 * and peer ids, and the config announce's master MAC. [EVIDENCED (corpus).]
 */
#define REAC_ETH_ADDR_BYTES             6

/* Width of the little-endian frame counter at HDR_COUNTER_OFF. [EVIDENCED
 * (corpus).]
 */
#define REAC_HDR_COUNTER_BYTES          2

/* Width of the big-endian type word at TYPED_BLOCK_OFF, the 2 in
 * TYPED_BLOCK_LEN = 2 + 32 and in every two-byte `pos` of typed_block.
 * [EVIDENCED (corpus).]
 */
#define REAC_TYPE_WORD_BYTES            2

/* The two end-marker bytes, END_MARKER_0 and END_MARKER_1 — the 2 in
 * FRAME_OVERHEAD = 50 + 2. [EVIDENCED (corpus).]
 */
#define REAC_END_MARKER_BYTES           2

/* The braid carries channels in PAIRS — one 6-byte pair group per two
 * channels per sample time — so every legal audio width is even. The
 * byte permutation inside a pair stays libreac's (see the header of
 * this file); the pairing itself is spelled by reac.ksy's
 * `num_channels / 2` and by every even-width check in libreac and
 * reac-pw, so it is shared.
 *   [EVIDENCED (corpus) — reac.ksy time_sample, validated against libreac's
 *   upstream goldens by reac_xcheck.py.]
 */
#define REAC_BRAID_PAIR_CHANNELS        2

/* Neither segment bit — a frame in the middle of a bulk transfer. [EVIDENCED
 * (image) — FUN_0c003398 writes block[1] = 0 for a middle frame
 * (control_header group doc).]
 */
#define REAC_SEG_MIDDLE                 0x00

/* block[0] of a master announce (type word 0xcfea, op 0xffff). [EVIDENCED
 * (corpus).]
 */
#define REAC_LINK_ANNOUNCE              0xff

#endif /* REAC_FACTS_FRAME_FIELDS_H */
