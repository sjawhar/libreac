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

#ifndef REAC_FACTS_SCENE_BODY_H
#define REAC_FACTS_SCENE_BODY_H

/* ---- What the box validates in the body, and what it reads ---------------------
 * The commit checks THREE four-byte tags and nothing else. Fail any one and
 * it promotes nothing and replies nothing, while the transfer still looks
 * complete from the wire. Two of the three ride MIDDLE chunks, so a body
 * whose interior is wrong fails silently.
 *
 * THE TAGS ARE A GATE, NOT A DESCRIPTION OF WHAT THE BOX USES. Measured on
 * hardware: a body of zeros carrying only the three tags PASSES the commit
 * and leaves the box reporting model=unknown with ZERO capture ports, where
 * a recovered body brings it up as s1608 with 16. The unvalidated 8892 bytes
 * are not free — a wrong value there is not rejected, it is acted on.
 */
/* "1234". Rides the op-0101 header. [EVIDENCED (executed trace) — 2 of 70
 * zeroed 128-byte windows break the commit, and they are the two containing a
 * tag.]
 */
#define REAC_SCENE_TAG_ID_OFF           0x000

/* "SYSP". Rides op-0100 chunk 32. [EVIDENCED (executed trace).] */
#define REAC_SCENE_TAG_SYSP_OFF         0x368

/* "SCEN". Rides op-0100 chunk 33. [EVIDENCED (executed trace).] */
#define REAC_SCENE_TAG_SCEN_OFF         0x37c

/* The master's own MAC, INSIDE the body. On-wire identity must equal the L2
 * source, so a master replaying a recovered body substitutes its own.
 * [EVIDENCED (image + corpus).]
 */
#define REAC_SCENE_MAC_OFF              0x340

/* The pace code (0 = 48 kHz, 1 = 96 kHz, 2 = 44.1 kHz), the same value as
 * cfea[19]; see CONSOLE_FIELD_GATES_RATE. One of only two fields an emitter
 * fills in. [EVIDENCED (corpus) — 8 of 8904 bytes vary across 27 real-desk
 * bodies over three desk generations and four box models.]
 */
#define REAC_SCENE_REVISION_OFF         0x014

/* The 80-slot declaration table. [EVIDENCED (image + corpus).] */
#define REAC_SCENE_SLOTS_OFF            0x01a

/* Slots the commit promotes — unconditionally, all of them, with the SAME
 * constant. A scene body therefore CANNOT address an individual channel.
 * [EVIDENCED (executed trace).]
 */
#define REAC_SCENE_SLOT_COUNT           80

/* The scene record stride. 26 mod 10 = 6 and gcd(26,10) = 2 is the whole of
 * the "period-10 probe rotation with a phase step of +6" that was read as a
 * master state for a year. [EVIDENCED (image + corpus).]
 */
#define REAC_SCENE_SLOT_BYTES           10

/* Value at +0x04 on every desk generation and against every box. The commit
 * branches on it. [EVIDENCED (image + corpus).]
 */
#define REAC_SCENE_UNIT_MAP_SELECT      0x0001

/* Value at +0x08 on every capture. What it selects is UNRESOLVED. [EVIDENCED
 * (image + corpus).]
 */
#define REAC_SCENE_MAP_A_ARG            0x0004

#endif /* REAC_FACTS_SCENE_BODY_H */
