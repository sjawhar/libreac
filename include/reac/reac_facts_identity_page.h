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

#ifndef REAC_FACTS_IDENTITY_PAGE_H
#define REAC_FACTS_IDENTITY_PAGE_H

/* ---- The identity page (DT1 tag 0x0500) ----------------------------------------
 * What a box says it IS, and the one record a console needs to put a box in
 * a menu with a model and a firmware version.
 *
 * The tag is only the HIGH half of a Roland four-byte DT1 address. The low
 * half rides in the record body, so ONE tag covers six records and a
 * consumer that reads 0x0500 as a single struct gets five of them wrong.
 * The console polls all six with RQ1 (command 0x11) in one burst at
 * establishment; the box answers with DT1 (0x12) only for the addresses it
 * implements.
 *
 * MEASURED over the whole corpus: 1005 complete records (438 RQ1 in 6 x 73,
 * 567 DT1 replies) plus 18 fragment pairs, 85 captures.
 *
 * The firmware version is the row that closes the loop with the outside
 * world: its four bytes are four DECIMAL DIGITS, and the number they spell
 * is the version of the Roland release package each image came from. Three
 * models, three independent matches — so the boxes in this corpus run the
 * firmware images this project holds, and no firmware-derived fact in this
 * repo needs a version qualifier.
 */
/* `addr_lo`, the low half of the address, opens every 0x0500 record
 * body. The tag carries the high half, so the full DT1 address is four
 * bytes and an emitter that writes only the tag addresses record
 * 0x0000 by accident.
 *   [EVIDENCED (corpus) — 1005 records, six distinct addr_lo.]
 */
#define REAC_IDENTITY_ADDR_LO_BYTES     2

/* The full DT1 address is four bytes — the 2-byte tag plus the 2-byte
 * addr_lo that opens every 0x0500 record body. An emitter that writes
 * only the tag addresses record 0x0000 by accident.
 *   [EVIDENCED (corpus + image) — S-1608.BIN carries a 12-byte stride DT1
 *   address table at file 0x53154..0x53994, 176 records of {4-byte address,
 *   u32le, u32le byte count}.]
 */
#define REAC_IDENTITY_ADDR_BYTES        4

/* The system firmware version, 4 bytes, ONE DECIMAL DIGIT PER BYTE,
 * most significant first, displayed by Roland as D.DDD.
 *   [EVIDENCED (corpus + vendor package). S-0808 01 00 00 03 = 1.003 vs
 * package s0808_sys_v1003; S-1608 02 02 00 00 = 2.200 vs
 * s1608_sys_ver2200; S-4000S 02 05 00 00 = 2.500 vs s4000_sys_ver2500.
 * S-1608.BIN corroborates itself twice from the inside: boot banner
 * `ECM42 BOOT Ver.2.200` at file 0x200 and the boot-menu version
 * literal `2.200` at 0x9254. Capture
 * captures/m200i-s0808-48k-mirror__m200-BIDIR-coldboot-2026-07-11.pcap
 * frame 3475.
 * ]
 */
#define REAC_IDENTITY_ADDR_FIRMWARE_VERSION 0x0000

/* The REAC PROTOCOL version the box speaks — 8 bytes, four u16be: a
 * reserved word (0 everywhere, undecoded) then MAJOR, MINOR, PATCH. The
 * console prints it `major.minorPP`, the patch zero-padded to two digits.
 * S-0808 00 00 00 01 00 00 00 00 = (0,1,0,0) -> 1.000; S-1608
 * 00 00 00 02 00 03 00 02 = (0,2,3,2) -> 2.302; S-4000S-3208
 * 00 00 00 02 00 01 00 02 = (0,2,1,2) -> 2.102. It is a DIFFERENT number
 * from the firmware version at 0x0000 and neither substitutes for the
 * other: the S-1608 runs firmware 2.200 and speaks REAC 2.302.
 *   [EVIDENCED (corpus + console display) — 274 replies, 5 distinct boxes,
 * 3 models, constant per model. The operator read an M-200i's identity
 * display on 2026-09-14: the S-1608 shows `REAC 2.302` beside `Firmware
 * 2.200`, and the S-4000S-3208 (bench units 0040abc40680 and
 * 0040abc408bc) shows `REAC 2.102` beside `Firmware 2.500`. The decode
 * reproduces both strings from the captured bytes. The S-0808's 1.000 is
 * PREDICTED — no display has been read for one. An earlier reading, that
 * the second u16 tracked the REAC port count, is a coincidence of three
 * models and is dropped.
 * ]
 */
#define REAC_IDENTITY_ADDR_REAC_VERSION 0x0600

/* The model name: 1 byte name_kind (0x01 on every observation) then a
 * FIXED 16-byte NUL-padded ASCII field. 17 bytes of payload do not fit
 * the 36-byte control block, which is the ONLY reason any REAC record
 * is fragmented — this record is the whole population of the 0x0401 /
 * 0x0402 pair.
 *
 * ONLY THE S-0808 IMPLEMENTS IT. The S-1608 and S-4000S never answer
 * this address, so a console cannot read their model as text and must
 * take it from the firmware version plus the config announce's declared
 * width.
 *   [EVIDENCED (corpus + image). 18 fragment pairs in 9 captures, all
 * S-0808, inner checksum closing only across both fragments (data sum
 * 358, 0x1a completes it to 0x80 mod 256). The image agrees with the
 * silence: S-1608.BIN's page-0x0500 address table uses
 * third-address-byte 0x00..0x08 only — there is no 0x10 or 0x11 entry.
 * ]
 */
#define REAC_IDENTITY_ADDR_MODEL_NAME   0x1000

/* The model-name field is fixed width and NUL-padded — "S-0808" plus ten
 * zeros. A reader that stops at the first NUL is right; one that takes all 16
 * bytes as the name is wrong. [EVIDENCED (corpus) — 18 reassembled records,
 * all identical.]
 */
#define REAC_IDENTITY_NAME_FIELD_BYTES  16

/* An RQ1 body is addr_lo plus ONE byte, the number of bytes wanted.
 * A reply MAY BE SHORTER than that: the S-0808 is asked for 9 bytes at
 * 0x1011 and returns 1. Short is normal, not an error.
 *   [EVIDENCED (corpus) — 438 RQ1 records, sizes 4, 8, 17 and 9; 19 one-byte
 *   replies at 0x1011.]
 */
#define REAC_IDENTITY_RQ1_SIZE_BYTES    1

#endif /* REAC_FACTS_IDENTITY_PAGE_H */
