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

#ifndef REAC_FACTS_INVENTORY_H
#define REAC_FACTS_INVENTORY_H

/* ---- The config-announce port table --------------------------------------------
 * A box declares its own geometry: twelve cells of four channels each,
 * spanning the 48-channel fabric ring. Geometry comes from the declaration,
 * not from a hand-kept model list.
 */
/* Block-relative start of the twelve-cell table. [EVIDENCED (corpus).] */
#define REAC_PORTS_TABLE_OFF            8

/* 12 x 4 = the 48-channel fabric. [EVIDENCED (corpus).] */
#define REAC_PORTS_TABLE_SLOTS          12

/* Channels per cell. [EVIDENCED (corpus).] */
#define REAC_PORTS_CH_PER_SLOT          4

/* A 4-output group. [EVIDENCED (corpus).] */
#define REAC_PORT_SLOT_OUT              0x01

/* A 4-input group. [EVIDENCED (corpus).] */
#define REAC_PORT_SLOT_IN               0x02

/* An empty cell. [EVIDENCED (corpus).] */
#define REAC_PORT_SLOT_EMPTY            0x03

/* A 4-input group, as the S-4000H (8 in / 32 out) declares its inputs.
 * Captured only on that chassis (MAC 00:40:ab:c4:25:80); a code this decoder
 * used to REFUSE THE WHOLE TABLE on, which kept a fully declaring box off the
 * graph for minutes (operator ruling 2026-09-17, "we should be able to enrol
 * any stage box"). WHAT SEPARATES 0x00 FROM 0x02 IS NOT DECIDED — one
 * chassis, one capture; a splitter's inputs may be marked apart from a
 * head-amp-owned input, or this may be nothing but an alternate spelling of
 * `analog_input`. [EVIDENCED (corpus, m200-s4000h-coldboot.pcap +
 * m200-s4000h-replug.pcap, box 00:40:ab:c4:25:80, cells = 01x8 00x2 03x2).]
 */
#define REAC_PORT_SLOT_IN_SPLIT         0x00

/* A cell carrying a code outside {00,01,02,03} is no longer a reason to
 * refuse the table. A SLOT CODE SPEAKS FOR ITS OWN FOUR CHANNELS AND NO
 * OTHERS — the box enrols at the width this decoder can read, and the unknown
 * group is reported (`reac_ports_unknown`), never guessed into either role.
 * No such code has been captured; this is the refusal rule for the day one
 * arrives. [EVIDENCED (libreac reac_ports.c; no unknown code seen in the
 * corpus).]
 */
#define REAC_PORT_SLOT_UNKNOWN_COST     1

/* OPEN, not a law. The S-4000H straps board_config_code = 0x00 like the
 * S-0808 and the S-4000S, predicting head-amp base CH 0x00 by `base =
 * board_config_code * 0x10`. An M-200 has been observed addressing this box's
 * preamps at CH 0x20–0x27 instead — a rig check, not a capture, and not yet
 * reconciled with the strap law. Do not derive a base for a 0x00-coded box
 * from the strap alone until this is resolved. [OPEN (rig observation,
 * unreproduced in a capture).]
 */
#define REAC_PORT_SLOT_IN_SPLIT_HEADAMP_BASE 1

/* One per enrolled input group of 8, front-packed. [EVIDENCED (image +
 * corpus).]
 */
#define REAC_ENROLL_GROUP_IN            0x41

/* One per non-input group, back-packed. [EVIDENCED (image + corpus).] */
#define REAC_ENROLL_GROUP_OUT           0xc3

/* Five groups of 8 span exactly the 40-slot audio fabric. [EVIDENCED (image +
 * corpus).]
 */
#define REAC_ENROLL_GROUPS              5

#endif /* REAC_FACTS_INVENTORY_H */
