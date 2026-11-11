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

#ifndef REAC_FACTS_HEADAMP_SENS_H
#define REAC_FACTS_HEADAMP_SENS_H

/* ---- The SENS step -> sensitivity curve ----------------------------------------
 * One decibel per step, over all 56 steps, with no duplicates anywhere.
 * Sensitivity runs -10 dBu at 0x00 down to -65 dBu at 0x37 with the pad off,
 * and the pad shifts the whole travel up by 20 dB:
 *
 *   sensitivity_dBu = -10 - value + (pad ? 20 : 0)
 *
 * MEASURED 2026-08-23, S-0808, output 1 cabled to input 1 so the source is an
 * electrical loopback of a level we generated and therefore know — not a
 * microphone in a room, which is what produced the third and wildest of the
 * readings this replaces. All 56 steps at three generator levels whose ranges
 * overlap and agree to 0.05 dB where they meet. Span 54.60 dB against the
 * 55.00 a flat 1 dB implies; least-squares slope 0.988 dB/step with a maximum
 * residual of 0.44 dB, which is the size of the measurement's own scatter, so
 * the law declared here is the round decibel and not the fitted 0.988. The pad
 * measured 20.12 and 20.20 dB at two different steps — the check that this dB
 * axis is the box's own.
 *
 * THE FIRMWARE HOLDS THE CURVE AS A TABLE, and here it is. S-1608.BIN at
 * 0x0c0327a0, 56 entries of two bytes, read by FUN_0c007e30 which clamps
 * the step to 0x37 and hands the pair to the preamp writer FUN_0c00af2a.
 * In the S-1608 image the table ends exactly where the ASCII version banner
 * "V03.05" begins, which is how we know its extent is 56 and not a run of
 * padding.
 *
 * The same 112 bytes appear in S-0808.BIN at file offset 0x45ec8. THAT IS A
 * RAW BYTE MATCH AND NOTHING MORE: there is no S-0808 decompilation, the
 * image is not a code image loadable at the S-1608's base, and its own
 * pointers are a different width and order (big-endian 0x0003xxxx). The
 * banner control above does NOT apply there — S-0808 has zero padding after
 * the table, not a banner. Nothing in this group is sourced from S-0808
 * disassembly; the byte match corroborates the table's content across two
 * models and the reading of it comes from the S-1608 alone.
 *
 *   step stage fine step stage fine step stage fine step stage fine
 *   0x00 3 0x00 0x0e 2 0x0c 0x1c 1 0x08 0x2a 0 0x04
 *   0x01 3 0x02 0x0f 2 0x0e 0x1d 1 0x0a 0x2b 0 0x06
 *   0x02 3 0x04 0x10 2 0x10 0x1e 1 0x0c 0x2c 0 0x08
 *   0x03 3 0x06 0x11 2 0x12 0x1f 1 0x0e 0x2d 0 0x0a
 *   0x04 3 0x08 0x12 2 0x14 0x20 1 0x10 0x2e 0 0x0c
 *   0x05 3 0x0a 0x13 2 0x16 0x21 1 0x12 0x2f 0 0x0e
 *   0x06 3 0x0c 0x14 2 0x18 0x22 1 0x14 0x30 0 0x10
 *   0x07 3 0x0e 0x15 2 0x1a 0x23 1 0x16 0x31 0 0x12
 *   0x08 2 0x00 0x16 2 0x1c 0x24 1 0x18 0x32 0 0x14
 *   0x09 2 0x02 0x17 2 0x1e 0x25 1 0x1a 0x33 0 0x16
 *   0x0a 2 0x04 0x18 1 0x00 0x26 1 0x1c 0x34 0 0x18
 *   0x0b 2 0x06 0x19 1 0x02 0x27 1 0x1e 0x35 0 0x1a
 *   0x0c 2 0x08 0x1a 1 0x04 0x28 0 0x00 0x36 0 0x1c
 *   0x0d 2 0x0a 0x1b 1 0x06 0x29 0 0x02 0x37 0 0x1e
 *
 * HOW TO READ IT. The two bytes are not decibels — they are two hardware
 * registers. `stage` is a two-bit coarse range: FUN_0c00af2a drives it onto
 * a pair of GPIO pins per channel, so it is an analog range switch, and
 * FUN_0c007f20 compares ONLY this byte between two steps, which is a
 * "does this change need the range to move" test. `fine` is a serial gain
 * code, clamped to 0x24 by the writer, and it steps by exactly 2 for every
 * step of the SENS index, everywhere in the table with no exception.
 *
 * WHAT THE TABLE PROVES, AND WHAT IT DOES NOT. It proves the shape: the
 * step is UNIFORM within a range, so any departure from a flat law can only
 * live at the three range breaks, which fall between steps 0x07/0x08,
 * 0x17/0x18 and 0x27/0x28. It does not carry a decibel — the dB per fine
 * LSB and the dB of each range tap are analog component values, in the
 * preamp and not in the image.
 *
 * The stages begin at index 0, 8, 24 and 40, and the fine field restarts at
 * zero at each. That placement is itself a statement: a break sits exactly
 * where the fine field would run out, so the designer intended the ranges
 * to abut with no gap and no overlap. Take the fine LSB as the usual half
 * decibel and the whole table reads out as gain_dB = step, 0 through 55,
 * with the range taps at 0, 8, 24 and 40 dB. That is the round law, and the
 * table is its decomposition into two registers.
 *
 * SO THE LAW IS THE FIRMWARE'S TABLE AND 54.60 IS A MEASUREMENT OF IT. The
 * two are not rival claims about the same quantity. The deficit is 0.40 dB
 * over 55 steps against a sweep whose own maximum residual was 0.44 dB, so
 * the measurement cannot separate 54.60 from 55.00 and does not contradict
 * it. What the rig DID settle, and the table could not, is that the three
 * range breaks are continuous: A/B/A gave +0.92/+1.12, +1.36/+1.31 and
 * +0.97/+0.84 dB at exactly the three indices the table puts them at. That
 * is the firmware's structure and the rig's numbers agreeing on the same
 * three places, which is the strongest form this fact can take.
 *
 * WHAT THIS SETTLES, because it was the schema's one openly contested number.
 * Three readings were live: reac.ksy and reac-pw both spelled the flat 1 dB
 * law, which is how a number nobody had measured came to look confirmed by two
 * sources; libreac carried a 56-entry firmware curve spanning 48.75 dB whose
 * stage breaks at 8, 24 and 40 made three pairs of steps deliver IDENTICAL
 * gain, so the map was not injective and a round trip through it was a
 * different function; and a rig measurement of 1.235 dB/step, since shown to
 * be an artefact of its acoustic source.
 *
 * The twins were the discriminating test and they were run: each pair by rapid
 * A/B/A alternation, twice, at two generator levels, so residual drift shows
 * as a mismatch between the A readings.
 *
 *   7 -> 8 +0.92 and +1.12 dB drift control 0.08 / 0.10 dB
 *   23 -> 24 +1.36 and +1.31 dB drift control 0.34 / 0.15 dB
 *   39 -> 40 +0.97 and +0.84 dB drift control 0.26 / 0.08 dB
 *
 * Every pair steps by about a decibel, an order of magnitude outside its own
 * control. The firmware's four coarse stages are real; gain being continuous
 * across their breaks was an inference from that structure and it is refuted.
 *
 * THE ANCHOR, stated honestly because half of it is not measured here. A
 * loopback measures the SPAN exactly — 54.60 dB between the endpoints, which
 * is what discriminates 48.75 from 55.00 — but the absolute dBu of either
 * endpoint needs one constant this experiment cannot separate: the box's own
 * converter reference, the dBu it puts out at 0 dBFS and the dBFS its
 * sensitivity spec refers to. The loop measures their SUM. So -10 dBu at step
 * 0 is carried over unchanged from every source that already agreed on it, and
 * -65 at 0x37 is what the measured span then makes it. Raw data:
 * reac-pw docs/measurements/sens-sweep-2026-08-23-*.csv.
 *
 * REMOVED 2026-09-25 as dead facts (audit 2026-09-25-contract-copies):
 * four rows describing the firmware's analog STAGES, read by no consumer,
 * no grammar and no copy in any of the three repos. What they recorded:
 * the step table selects between 4 coarse analog ranges, driven onto two
 * GPIO pins per channel by FUN_0c00af2a (EVIDENCED image), whose first
 * steps are 0x08, 0x18 and 0x28; those three breaks are the only places a
 * uniform step could fail, and the rig measured all three at about a
 * decibel (EVIDENCED image + rig) - which is what HEADAMP_SENS_STEP_CDB
 * rests on. Restore them from git history if a consumer ever needs them.
 */
/* Step 0x00 with the pad off, in hundredths of a dBu — the least sensitive
 * setting and the reference the whole travel hangs off. [INFERRED — agreed by
 * every prior reading and not independently measurable through a loopback,
 * which sees only this plus the box's converter reference. The SPAN below is
 * what was measured.]
 */
#define REAC_HEADAMP_SENS_REF_CDB       -1000

/* One decibel, every step, all 55 transitions. The number that was disputed,
 * and the one thing a consumer cannot get wrong quietly. [EVIDENCED (image +
 * rig). Image — the S-1608 table at 0x0c0327a0 steps
 * its fine register by exactly 2 for every SENS step with no exception,
 * so the law is uniform inside each of its four ranges and can only
 * break at three indices. Rig — the 2026-08-23 loopback sweep of all 56
 * steps, span 54.60 dB, slope 0.988, and A/B/A at each of those three
 * indices giving about a decibel against controls of 0.08 to 0.34 dB.
 * The 0.40 dB the span falls short is inside that sweep's own 0.44 dB
 * maximum residual, so it does not stand against the table.
 * ]
 */
#define REAC_HEADAMP_SENS_STEP_CDB      100

/* Entries in the firmware's SENS table, steps 0x00..0x37. The writer
 * FUN_0c007e30 clamps anything above 0x37 to 0x37, so 0x37 is the top of the
 * travel and not merely the last one observed. [EVIDENCED (image, S-1608
 * 0x0c0327a0 = file 0x527a0; the same 112 bytes at S-0808 file 0x45ec8 as a
 * raw byte match, not a disassembly — there is no S-0808 decompilation).]
 */
#define REAC_HEADAMP_SENS_STEPS         56

/* The pad's 20 dB, in hundredths, added to the sensitivity when it is on.
 * Independent of the step, and it earns its place here by being the one
 * number in this group whose absolute value the loopback DOES measure.
 * [EVIDENCED (rig) — 20.12 and 20.20 dB by A/B/A at steps 0x37 and 0x28,
 * against pad-off controls of 0.11 and 0.16 dB.]
 */
#define REAC_HEADAMP_PAD_CDB            2000

#endif /* REAC_FACTS_HEADAMP_SENS_H */
