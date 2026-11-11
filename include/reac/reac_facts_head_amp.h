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

#ifndef REAC_FACTS_HEAD_AMP_H
#define REAC_FACTS_HEAD_AMP_H

/* ---- Head-amp — the record, its wire encoding and its actuation ----------------
 * A head-amp record is a Roland DT1 inside op-0403: TAG 0x0101, then
 * {CH, PARAM, VALUE}. Two things about it are routinely got wrong.
 *
 * TWO AXES, NOT THREE GRANULARITIES. This group used to say "three
 * granularities under one name" and list per-channel, per-four and
 * per-eight side by side. Those are not three points on one scale: two of
 * them are WIRE ENCODING (which record carries a field) and one is HARDWARE
 * ACTUATION (how many channels one write switches). Reading them as one
 * list makes a consumer wrong about whichever it picks.
 *
 * AXIS 1 — WIRE ENCODING, what a record carries.
 *
 *   DT1 head-amp record {CH, PARAM, VALUE}, op-0403 TAG 0x0101
 *     PARAM 0x00 phantom, 0x01 pad, 0x02 sens — one channel per record,
 *     all three. NO per-four gate exists on this path anywhere in the
 *     image, and the wire agrees: measured 2026-08-23, three desk
 *     generations address phantom on channels that are not multiples of
 *     four, and a single-channel toggle names only its own channel. See
 *     HEADAMP_GRAN_PHANTOM_SHIFT, which that measurement moved from 2 to 0.
 *
 *   SLOT MAP record {slot, cell+flags, sens}, op-0103 subtype 0x01
 *     FUN_0c002d42 writes the sens byte and the three flag bits (bits 3,
 *     2, 1) for EVERY slot, unconditionally. Only the HIGH NIBBLE is
 *     per-four: the `(slot & 3) == 0` branch hands `flags >> 4` to
 *     FUN_0c00f9aa and FUN_0c004164, the two 12-entry INVENTORY arrays.
 *     So the per-four field in this record format is the INVENTORY CELL,
 *     not a head-amp parameter.
 *
 * AXIS 2 — HARDWARE ACTUATION, what one write switches. PER CHANNEL, for
 * all three parameters. FUN_0c007fbc(bank, group) sets its cursor to
 * `group << 3` and loops EIGHT times; inside the loop, each iteration
 * passes its own within-bank index (0..7) and that slot's own value to
 * FUN_0c00ac1e (phantom), FUN_0c00ac96 (pad) and FUN_0c007e6a ->
 * FUN_0c007e30 (sens). Each channel gets its own value and its own write.
 *
 * SO THERE ARE EXACTLY TWO GRANULARITIES, NOT THREE: per channel and per
 * eight. Per channel is the ACTUATION. Per eight is the REFRESH BANKING —
 * and the readback nibble is the same eight, not a third axis. See
 * HEADAMP_BANK_CHANNELS, which is now the single row for both.
 *
 * BANK AND GROUP ARE DIFFERENT AXES AND OUR DOCS HAVE MIXED THEM UP.
 * Pinned here, once:
 *
 *   GROUP 0..9, and `group == ch >> 3`. It selects WHICH EIGHT CHANNELS'
 *          DATA — an eight-slot window of the 80-slot active table.
 *   BANK selects WHICH EIGHT PHYSICAL PREAMPS receive it. It is NOT a
 *          subdivision of channel space and it does not index the active
 *          table.
 *
 * They are independent, which is why FUN_0c007fbc takes both. At least one
 * doc has them inverted — FUN_0c012162(k) returns a GROUP 0..9 while its
 * argument k is a BANK — so anything reading either word should check it
 * against this definition rather than against neighbouring prose.
 *
 * A NOTE ON A CORRECTION MADE TO THIS FILE'S OWN CORRECTION: the firmware
 * lane's first report said phantom "reaches hardware in groups of EIGHT".
 * That read the loop bound as the actuator width and is wrong in the same
 * shape as the per-four claim it was correcting. The loop is eight long;
 * the write inside it is one channel wide.
 *
 * A RECORD WRITES THE ACTIVE TABLE, AND THE COMMIT OVERWRITES IT. There is
 * no head-amp staging table. So records must FOLLOW the commit, never
 * precede it: a record sent before it is erased, silently — the bytes are
 * right, the checksums are right, the box acknowledges, and the value is
 * gone.
 */
/* The DT1 register page for head-amp. [EVIDENCED (corpus).] */
#define REAC_HEADAMP_TAG                0x0101

/* +48V, value 0 or 1. WHICH BIT IS PHANTOM AND WHICH IS PAD IS OUR NAME, NOT
 * THE FIRMWARE'S — the mapping comes from the corpus and the rig, explicitly
 * NOT from the image. [EVIDENCED (corpus + rig).]
 */
#define REAC_HEADAMP_PARAM_PHANTOM      0x00

/* -20 dB pad, value 0 or 1. [EVIDENCED (corpus + rig).] */
#define REAC_HEADAMP_PARAM_PAD          0x01

/* Sensitivity step. [EVIDENCED (corpus + rig).] */
#define REAC_HEADAMP_PARAM_SENS         0x02

/* 55 — the 56th and last entry of the box's own step table, which is exactly
 * 56 rows with no spares. What each step is WORTH in dB is the headamp_sens
 * group below; this row is only the count. [EVIDENCED (image) — a 56-entry
 * table at 0x0c0327a0 in the S-1608 image, reached by both write paths,
 * ending exactly where the "V03.05" version string begins — in the S-1608
 * image; the S-0808 copy is a byte match only. The count is what that table
 * proves; reading a gain curve off its stage structure did not survive the
 * rig.]
 */
#define REAC_HEADAMP_SENS_MAX           0x37

/* 48 addressable wire channels, 0x00..0x2f. NOT the 40-slot audio fabric — a
 * table bounded by 40 silently rejects a 16-input box based at 0x20, so its
 * inputs 9..16 can never be given phantom, pad or sens. [EVIDENCED (corpus).]
 */
#define REAC_HEADAMP_CH_SPAN            0x30

/* SENS is per channel — ch >> 0. [EVIDENCED (executed trace).] */
#define REAC_HEADAMP_GRAN_SENS_SHIFT    0

/* The flag bits are per channel — ch >> 0. [EVIDENCED (executed trace).] */
#define REAC_HEADAMP_GRAN_FLAGS_SHIFT   0

/* PHANTOM IS PER CHANNEL — ch >> 0, exactly like pad and sens. This row
 * read 2 and was DISPUTED; it was measured on 2026-08-23 and the 2 is
 * withdrawn.
 *
 * THE MEASUREMENT. Taken on the live rig 2026-08-23 as phantom-test.pcap
 * and filed as
 * reacpw-s1608-48k-clean__phantom-ch24-on-off-2026-08-23.pcap in the
 * raw capture set, which is not published (it still needs a MANIFEST
 * row and a distillation pass before it joins the committed corpus):
 * interface enp131s0 (the S-1608 segment), ethertype 0x8819 only,
 * snaplen 200, twelve seconds — idle, then phantom set TRUE on head-amp
 * CH 0x24, four seconds, then phantom set FALSE on 0x24, nothing else
 * touched. 0x24 is box port 5 and the first of the group of four
 * 0x24..0x27 that the retracted reading claimed one record covers.
 * Exactly TWO head-amp records crossed the wire in those twelve seconds
 * and both name CH 0x24 ALONE. 0x25, 0x26 and 0x27 never appear. Every
 * frame was truncated by the snaplen, so that is a claim to check rather
 * than assume: the control block is [18:50] and the record inside it
 * [34:40], both inside the 200 bytes, and all 38 control blocks in the
 * capture pass the block checksum while both head-amp records pass the
 * nested record checksum. Truncation removed audio and nothing the
 * verdict rests on.
 *
 * THE DISCRIMINATOR THIS ROW USED TO ASK FOR DOES NOT EXIST, which is
 * what had kept it stuck. The old note said: write 0x24, write 0x25, and
 * read the box's own RE-BROADCAST back. THERE IS NO RE-BROADCAST. The
 * S-1608 sent 47122 frames in that capture with ZERO dropped — its
 * 16-bit frame counter steps by one across all 47121 intervals — and
 * every one of them is either an audio frame, whose 16-slot descriptor
 * area is a constant `00 7a` per slot and did not move a byte at either
 * toggle, or one of twelve bare link-1 opcode-0x81 heartbeats whose
 * 32-byte block is byte-identical every time. The box volunteers no
 * head-amp state whatsoever. Neither does it to a real desk: in
 * m200-ch7-ON-OFF-ON-20260721-215743.pcap this same box answers an
 * M-200i toggling phantom six times with nothing but its heartbeat. A
 * consumer must therefore treat head-amp as WRITE-ONLY on this wire and
 * keep its own model; there is nothing to query and compare against.
 *
 * SO THE ROW IS SETTLED ON THE AXIS IT ACTUALLY GOVERNS — what a SENDER
 * puts on the wire, since a consumer that trusts a 2 emits phantom on
 * multiples of four only. Our own master emitting one record for 0x24
 * shows what OUR encoder does and nothing about Roland's law, so the
 * corpus supplied the desks. Across 3651 phantom records from three desk
 * generations — M-200i 00:40:ab:c9:cc:03, M-300 00:40:ab:c9:d8:5b,
 * M-5000 00:40:ab:ca:15:4c — 2304 address a channel that is NOT a
 * multiple of four. A full S-1608 sweep names 0x20..0x2f, all sixteen;
 * an S-0808 names 0x00..0x07; an S-4000S names 0x00..0x1f. The decisive
 * single case is m200-ch7-ON-OFF-ON: a real M-200i toggling ONE
 * channel's phantom on and off three times, six records, every one of
 * them CH 0x26. 0x26 & 3 == 2, so a desk obeying "per four" would have
 * had to write 0x24 and could not have expressed that toggle at all.
 *
 * THE READING THAT LOSES, AND WHY IT WAS BELIEVED. It was "phantom is
 * per group of FOUR, ch >> 2", graded EVIDENCED (executed trace). That
 * grade is why the static case was never allowed to flip this row, no
 * matter how strong it got: inference does not overturn an observation.
 * It is overturned here by MORE observations — more desks, more records,
 * and a purpose-built single-channel toggle on a channel that is not a
 * group leader. The static read turns out to have been right the whole
 * time: there is no per-four gate on the DT1 path anywhere in
 * S-1608.BIN. The single channel-indexed `(x & 3) == 0` test in that
 * image is FUN_0c002d42's, it gates `flags >> 4` into the two 12-entry
 * INVENTORY arrays, and it sits on the SLOT-MAP path, not the head-amp
 * path. The per-four number that is real belongs to PORTS_CH_PER_SLOT,
 * the inventory cell, and the likeliest history is that a trace of the
 * CELL moving was read as phantom moving. The capture is consistent with
 * that: the master's slot map reported slot 0x24 after the ON and again
 * after the OFF, flags 0x28 and sens 0x00 both times, and across all 48
 * channel slots it recorded zero state changes in the whole twelve
 * seconds. A phantom write does not touch the slot map.
 *
 * WHAT IS STILL NOT MEASURED, so nobody reads more into this than it
 * says: HARDWARE ACTUATION. No capture can show whether energising 0x24
 * also energises 0x25..0x27 inside the box, because the box reports
 * nothing back. That axis is HEADAMP_ACTUATION_SHIFT; it reads 0 from
 * the image, and confirming it needs a physical 48 V measurement on box
 * inputs 6, 7 and 8 while only input 5 is written — never a soft
 * indicator.
 *   [EVIDENCED (executed trace) —
 *   reacpw-s1608-48k-clean__phantom-ch24-on-off-2026-08-23.pcap (taken as
 *   phantom-test.pcap), enp131s0, snaplen 200 (one record for CH 0x24 alone
 *   per toggle; the box re-broadcasts nothing, 0 dropped frames), together
 *   with 2304 non-group-leader phantom records from three desk generations in
 *   the corpus and m200-ch7-ON-OFF-ON-20260721-215743.pcap as the decisive
 *   single-channel case. OVERTURNS the earlier executed trace that read 2,
 *   and vindicates the image read (S-1608 FUN_0c002d42 gates the inventory
 *   cell, not phantom).]
 */
#define REAC_HEADAMP_GRAN_PHANTOM_SHIFT 0

/* HARDWARE ACTUATION IS PER CHANNEL, for phantom, pad and sens alike.
 * FUN_0c007fbc's loop passes a per-channel index and that slot's own
 * value to each of the three writers on every one of its eight
 * iterations. This is the number that says what one write switches, and
 * it is the axis the three old "granularity" rows never had.
 *   [EVIDENCED (image, S-1608 FUN_0c007fbc -> FUN_0c00ac1e / FUN_0c00ac96 /
 *   FUN_0c007e6a).]
 */
#define REAC_HEADAMP_ACTUATION_SHIFT    0

/* THE PER-EIGHT GRANULARITY, and there is only one of them. This row
 * folds together what used to be two — "the hardware bank" and "the
 * readback nibble is per eight" — because they are arithmetically the
 * same thing and were being read as two independent pieces of evidence.
 *
 * FUN_0c007fbc sets its cursor to `group << 3` and loops exactly eight
 * times, so group g covers [g*8, g*8+8) and therefore `g == ch >> 3` —
 * which is the readback nibble's own index. One axis, two spellings:
 * this width 8 and HEADAMP_BANK_SHIFT's 3.
 *
 * It is a REFRESH AND READBACK banking, not an actuation width: the
 * writers take (bank, 0..7) and each of the eight iterations writes one
 * channel. Two banks of eight cover an S-1608's sixteen analog inputs.
 *   [EVIDENCED (image) — S-1608 FUN_0c007fbc for the loop and the per-channel
 *   writes; its caller, recovered 2026-08-23 from a function Ghidra never
 *   disassembled (clean prologue past the previous function's rts, absent
 *   from the 1395-entry map, reached by a plain bsr), for `group == ch >> 3`.
 *   Supersedes the earlier UNRESOLVED note that the caller could not be
 *   traced.]
 */
#define REAC_HEADAMP_BANK_CHANNELS      8

/* `ch >> 3` gives the bank/group index. THE SAME FACT AS
 * HEADAMP_BANK_CHANNELS above, spelled as a shift instead of a width —
 * consult one or the other, never both as corroboration.
 *
 * It was called HEADAMP_GRAN_READBACK_SHIFT and sat beside the bank row
 * as if the readback were a third, independent granularity. It is not:
 * the apply loop's group index and the readback nibble are the same
 * `ch >> 3` over the same 80 slots.
 *   [EVIDENCED (executed trace for the readback nibble; image for the apply
 *   loop's identical index — S-1608 FUN_0c007fbc and its caller). The two
 *   agree, which is why they are one row.]
 */
#define REAC_HEADAMP_BANK_SHIFT         3

/* Every real desk sweep is ONE contiguous pass over the box's full declared
 * width, every channel getting all three parameters — 24 records for an
 * S-0808, 48 for an S-1608, 96 for an S-4000S. No desk addresses a bank,
 * splits a sweep or repeats one. [EVIDENCED (corpus) — 31 of 47 captures,
 * three desk generations agreeing on the same box.]
 */
#define REAC_HEADAMP_SWEEP_RECORDS_PER_CH 3

/* A box's head-amp CH base is its OWN property, announced, never granted. The
 * config
 * announce `01 03 00 10` carries it at buf[7], and the master addresses the
 * box at
 * base = buf[7] * 0x10. An 8-input and a 32-input box are BOTH addressed at
 * 0x00, which
 * is what rules out an allocation: nothing in the box consumes a granted
 * base.
 *   [RESOLVED (firmware + corpus) — S-1608.BIN (SH-4 LE, base 0x0BFE0000):
 *   FUN_0c003c8a at
 * 0x0c003c8a sets buf[7] = FUN_0c00f6a8() = *0x0c080918. Corroborated on 29
 * captures in
 * reac-captures/analysis/placement_table.csv (S-0808 0x00->0x00, S-1608
 * 0x02->0x20,
 * S-4000S 0x00->0x00) across M-200i, M-300 and M-5000.
 * ]
 */
#define REAC_HEADAMP_BASE_FROM_CONFIG_BYTE7 1

/* base = config-announce buf[7] * 0x10. Sixteen head-amp rows per strap step,
 * which is
 * two 8-slot groups — the same unit the box applies in.
 * Exercised at exactly two points (0 and 2): firmware-grade for the S-1608,
 * corpus-grade
 * for the others.
 *   [RESOLVED (firmware + corpus) — same provenance as
 *   HEADAMP_BASE_FROM_CONFIG_BYTE7.
 * ]
 */
#define REAC_HEADAMP_BASE_MULTIPLIER    0x10

/* A master cannot move where a head-amp write lands by granting differently.
 * The box's
 * fabric-row-to-preamp map is the group number FUN_0c012162 returns, and
 * every input to
 * it is a GPIO strap or a fitted-board inventory. Retires reac-pw's
 * docs/PLACEMENT-EVIDENCE.md five-run rig experiment: declared width was
 * collinear with
 * the base only because a 16-in chassis always straps 2.
 *   [RESOLVED (firmware) — S-1608.BIN: FUN_0c0081f6 at 0x0c0081f6 reads
 *   *0x0c080918 and
 * applies FUN_0c007fbc(bank, FUN_0c012162(k)); FUN_0c007fbc at 0x0c007fbc
 * indexes the
 * head-amp table at 0x0c0cf85a by group*8 + i; the config record is built by
 * FUN_0c0123c0
 * (0x0c0123c0), called only from FUN_0c0052d4 (0x0c0052d4) with constants,
 * and the group
 * table at +0x78 has exactly three writers — FUN_0c0119ac, FUN_0c011bbc,
 * FUN_0c011e2c —
 * none of which reads a frame.
 * ]
 */
#define REAC_HEADAMP_BASE_IS_CHASSIS_NOT_GRANT 1

/* The box applies head-amp in groups of eight fabric rows, one 8-port board
 * at a time,
 * passing the within-group index 0..7 to the preamp. Anything reasoning about
 * head-amp
 * reach reasons in groups of 8 from the box's base, never per channel — note
 * this is the
 * APPLY unit and is a different axis from actuation, which is per channel.
 *   [RESOLVED (firmware) — S-1608.BIN: FUN_0c007fbc at 0x0c007fbc, slot =
 *   group << 3, eight
 * iterations.
 * ]
 */
#define REAC_HEADAMP_APPLY_UNIT_SLOTS   8

#endif /* REAC_FACTS_HEAD_AMP_H */
