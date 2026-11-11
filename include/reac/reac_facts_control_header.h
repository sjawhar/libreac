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

#ifndef REAC_FACTS_CONTROL_HEADER_H
#define REAC_FACTS_CONTROL_HEADER_H

/* ---- The control block's header, as the firmware builds it ---------------------
 * The two bytes at block[0:2] have always been read as one 16-bit op. The
 * stagebox firmware writes them as two independent fields, and the receive
 * side gates on them separately.
 *
 * EVIDENCED (image), S-1608 `FUN_0c003398` @0c003398 — the box's own
 * segmented upload, which writes block[0] = 1, block[4] = 0, then sets
 * block[1] to 3 when the whole body fits in one frame, to 1 for the first of
 * many, to 0 for a middle frame and to 2 for the last. The receiver agrees:
 * `FUN_0c003aae` @0c003aae gates on `buf[1] & 1` and `FUN_0c003b88`
 * @0c003b88 on `buf[1] in {0, 2}`.
 *
 * So there are not seven scene-and-record ops. There is a LINK selector, a
 * two-bit SEGMENT field, a length, and an opcode.
 */
/* block[0] — the link selector. [EVIDENCED (image) — every builder writes it
 * first.]
 */
#define REAC_HDR_LINK_OFF               0

/* block[1] — the segment flags. [EVIDENCED (image).] */
#define REAC_HDR_SEG_OFF                1

/* block[2:4] — the big-endian length. [EVIDENCED (image).] */
#define REAC_HDR_LEN_OFF                2

/* block[4] — the opcode, and the base the length counts from on every family
 * except a link-1 bulk transfer. [EVIDENCED (image) — FUN_0c002c70 @0c002c70
 * writes 25 for eight three-byte records at block[5:29], and 25 = 1 + 8*3.]
 */
#define REAC_HDR_OPCODE_OFF             4

/* block[1] bit 0 — the frame opens a transfer and carries its total.
 * [EVIDENCED (image).]
 */
#define REAC_SEG_FIRST_BIT              0x01

/* block[1] bit 1 — the frame closes a transfer. [EVIDENCED (image).] */
#define REAC_SEG_LAST_BIT               0x02

/* Both bits — a complete message in one frame, which is what every chanmap,
 * heartbeat, declaration and single-frame record is. [EVIDENCED (image +
 * corpus).]
 */
#define REAC_SEG_SINGLE                 0x03

/* The stagebox control link — the scene transfer, the chanmap, the heartbeat
 * and the declarations. [EVIDENCED (image + corpus).]
 */
#define REAC_LINK_CONTROL               0x01

/* A second link the S-4000S image builds for and the S-1608 image has no code
 * for at all. [EVIDENCED (image) — FUN_0c0128b8 @0c0128b8 (S-4000S). NEVER
 * OBSERVED on the wire.]
 */
#define REAC_LINK_AUX_S4000S            0x02

/* The record link — the Roland DT1 container and its two fragments.
 * [EVIDENCED (corpus).]
 */
#define REAC_LINK_RECORD                0x04

/* A link-1 bulk FIRST frame puts its declared total at block[5:7] and its
 * payload at block[7]. [EVIDENCED (image + corpus).]
 */
#define REAC_SEG_FIRST_PAYLOAD_OFF      7

/* Every other bulk frame puts its payload at block[5]. [EVIDENCED (image +
 * corpus).]
 */
#define REAC_SEG_CONT_PAYLOAD_OFF       5

/* 24 — the largest first-frame chunk, and exactly 31 - 7. The builder
 * reserves block[31] for the checksum. [EVIDENCED (image) — FUN_0c003398
 * @0c003398.]
 */
#define REAC_SEG_FIRST_MAX              24   /* 0x0018 */

/* 26 — the largest continuation chunk, and exactly 31 - 5. [EVIDENCED
 * (image).]
 */
#define REAC_SEG_CONT_MAX               26   /* 0x001a */

/* The block offset the length counts from, INCLUSIVE — for every class
 * and subtype except one. A sister branch published this as universal;
 * it is not, and the exception is the commonest record on the wire.
 * See RECLEN_BULK_EXCEPTION.
 *   [EVIDENCED (image + corpus).]
 */
#define REAC_CTRL_RECLEN_BASE           4

/* The one subtype whose length does NOT count from block[4]: the
 * session-class bulk transfer. Its length is THIS FRAGMENT'S PAYLOAD
 * ONLY, at block[7] on a FIRST fragment and block[5] on any other.
 *
 * The scene body is 8904 bytes and arrives as 0x18 + 341 x 0x1a + 0x0e
 * = 24 + 8866 + 14. Under a base of 4 the payloads would be 21 and 25,
 * and 8904 - 21 - 14 = 8869 is not a multiple of 25 — the transfer
 * cannot be reassembled under that reading at all. The box's own sender
 * passes the chunk size both to the length store and to the memcpy that
 * fills block+7 or block+5.
 *   [EVIDENCED (image, S-1608 FUN_0c003398 @0c003398) + the reassembly
 *   arithmetic, asserted both ways in spec/reac_xcheck.py.]
 */
#define REAC_RECLEN_BULK_EXCEPTION      0x00

#endif /* REAC_FACTS_CONTROL_HEADER_H */
