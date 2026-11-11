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

#ifndef REAC_FACTS_DT1_TAG_H
#define REAC_FACTS_DT1_TAG_H

/* ---- DT1 record tags -----------------------------------------------------------
 * The two bytes after the DT1 command byte select the register page, and
 * they are the discriminator INSIDE the record link the way the subtype is
 * the discriminator inside the session link. Nothing generated them before,
 * so a consumer that wanted to name a record had to spell the numbers
 * itself — which is the drift this file exists to stop.
 *
 * Read them with the class and fragment fields, never alone: the same tag
 * 0x0500 appears in a single-frame record at rec_len 0x0016 and 0x001a AND
 * split across the 0x0401 / 0x0402 fragment pair.
 */
/* The mark record a console emits around a head-amp sweep. [EVIDENCED
 * (corpus).]
 */
#define REAC_DT1_TAG_HEAD_MARK          0x0000

/* The join/cold-connect state record, body 06 00 XX 00. [EVIDENCED (corpus).] */
#define REAC_DT1_TAG_JOIN_GRANT         0x0100

/* The preamp command — {CH, PARAM, VALUE}. The only tag the classifier treats
 * as its own kind. [EVIDENCED (corpus + rig).]
 */
#define REAC_DT1_TAG_HEAD_AMP           0x0101

/* A box-state record in the cold-connect exchange. [EVIDENCED (corpus).] */
#define REAC_DT1_TAG_BOX_READY          0x0302

/* The identity page — the 6- and 10-byte inventory bodies, and the ASCII
 * model name carried across the 0x0401 / 0x0402 fragment pair. [EVIDENCED
 * (corpus).]
 */
#define REAC_DT1_TAG_IDENTITY           0x0500

#endif /* REAC_FACTS_DT1_TAG_H */
