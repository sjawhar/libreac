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

#ifndef REAC_FACTS_FRAME_GEOMETRY_H
#define REAC_FACTS_FRAME_GEOMETRY_H

/* ---- Frame geometry ------------------------------------------------------------
 * A REAC frame is a fixed L2 header, a control block, an audio region of
 * whole 36-byte channels, and a two-byte end marker. Every length in the
 * protocol is 52 + n*36 for some channel count n, and that one law is what
 * lets a parser recover the width from the size — REAC carries no width
 * field in an audio frame.
 *
 * The 52 is 50 bytes of header plus the 2-byte end marker. A length that is
 * not 52 + n*36 is not a REAC frame. The `+2` a mirrored capture path leaves
 * on a frame belongs to the CAPTURE, not to the protocol — 0 such frames in
 * 592,762 captured off a plain NIC (census, 2026-09-21) — so it is not a
 * protocol fact and is not stated here; stripping it is the capture reader's
 * job, in ingest, before any byte reaches a parser.
 */
/* REAC's registered non-IP EtherType. [EVIDENCED (corpus) — every frame in 72
 * captures.]
 */
#define REAC_ETHERTYPE                  0x8819

/* 14 eth + 2 counter + 2 type word + 32 control block. [EVIDENCED (corpus).] */
#define REAC_L2_HEADER_LEN              50

/* Where the audio region starts. Same number as the header length, and it is
 * the same fact. [EVIDENCED (corpus) — a golden offset scan decodes real desk
 * program as noise at every other offset.]
 */
#define REAC_AUDIO_OFFSET               50

/* u16 LITTLE-endian free-running sequence counter, against the big-endian
 * everything else. [EVIDENCED (corpus).]
 */
#define REAC_HDR_COUNTER_OFF            14

/* The non-audio bytes of any frame — 50 header + 2 end marker. The 52 in `52
 * + n*36`. [EVIDENCED (corpus).]
 */
#define REAC_FRAME_OVERHEAD             52

/* The master sets the pace and the slaves follow it unconditionally. There is
 * no
 * per-rate cadence negotiation, no slave-side rate election, and no case in
 * which a box
 * declines a pace. So a frame rate is read off the master's clock, never
 * inferred from
 * a box's model or its declaration.
 * Consequence for our own docs: statements of the form "the upstream cadence
 * at rate R
 * is X" describe what the master chose, not a property the box asserts.
 *   [RULED (operator, 2026-08-23). Consistent with the corpus, which shows
 *   one pace per
 * segment and no negotiation exchange.
 * ]
 */
#define REAC_PACE_IS_THE_MASTERS        1

/* A clock rate is NOT a property of a mixer model. Any legal pace may run on
 * any desk,
 * and the two facts must never be derived from one another.
 * This is stated because our corpus makes them look coupled: each desk we own
 * has been
 * run at a single rate, so model and rate are perfectly correlated in the
 * captures. That
 * correlation is an accident of how the rig was used, not a fact about the
 * protocol, and
 * anything reading a per-desk field as a rate class must justify it on its
 * own evidence.
 *   [RULED (operator, 2026-08-23) — LAW. Not an inference from the corpus,
 *   and it overrides
 * any correlation the corpus appears to show.
 * ]
 */
#define REAC_RATE_IS_INDEPENDENT_OF_MODEL 1

/* The config-announce console_field byte (cfea[19]) PROPOSES the box's rate
 * CLASS; the
 * scene body's `revision` field (+0x14, SCENE_REVISION_OFF) is what a box
 * actually
 * latches. The value is the PACE CODE: 0x00 = 48 kHz, 0x01 = 96 kHz, 0x02 =
 * 44.1 kHz.
 * The same code rides four fields of one enrolment: cfea[19], the scene
 * body's
 * `revision`, the chanmap section marker's flags byte (`fe <code> 00`) and
 * the ENROLL
 * group map's console byte (ENROLL[8]). Enforcement is FIRMWARE-DEPENDENT: an
 * S-0808 (fw 1.003)
 * follows console_field alone; an S-1608 (fw 2.200) requires the scene's
 * `revision` to
 * agree with it, and otherwise holds its prior rate across a full cold
 * power-cycle.
 * This does NOT contradict RATE_IS_INDEPENDENT_OF_MODEL — it is the specific,
 * evidence-justified case that ruling anticipated ("anything reading a
 * per-desk field as a
 * rate class must justify it on its own evidence"). The rate is still the
 * master's choice
 * (PACE_IS_THE_MASTERS); console_field and `revision` are the two wire fields
 * by which the
 * master DECLARES and then RECORDS the class, and the family label (V-Mixer /
 * OHRCA) is
 * only its name. What is independent of a mixer MODEL is a bare clock number;
 * what gates
 * the class is this announce-plus-scene pair.
 * RULED (operator, 2026-09-13): the field is the pace code, not a desk
 * family. An M-200
 * at 44.1 kHz writes 0x02 on all four carriers; "V-Mixer"/"OHRCA" were only
 * the names
 * of 0x00 and 0x01 while no desk had been captured at 44.1 kHz.
 *   [RIG-VERIFIED (2026-08-27): emitting 0x00 ran the live box at 48 kHz and
 *   0x01 at 96 kHz,
 * with a warm follow on a live change; box frames stayed byte-identical
 * between the two,
 * the master byte the only differing field on that box (S-0808, fw 1.003).
 * CORRECTED (2026-08-29): that confirmation was generalised to "the box" and
 * is not
 * universal. An S-1608 (fw 2.200) held 48 kHz through a runtime assertion, a
 * daemon cold
 * boot at 96 kHz and a power-cycle into an already-running 96 kHz stream, all
 * with
 * console_field=0x01 — ten 96 kHz windows all measured WIRE PACE MISMATCH at
 * 4000 pps.
 * Making the scene's `revision` agree (see SCENE_REVISION_OFF) moved it to 96
 * kHz
 * immediately and cleanly, and pinning `revision` made the box LATCH: neither
 * a console
 * assertion nor a daemon cold boot at 48 kHz moved it back, because the value
 * never
 * changed and the box never re-read.
 * LOGIC: an M-5000 running its own box at 48 kHz must emit 0x00, so the byte
 * tracks the
 * pace chosen, not the console it came from — the M-200 already shows this
 * directly,
 * reaching 0x00 at 48 kHz and 0x02 at 44.1 kHz on the very same console.
 * WIRE-CAPTURED (2026-09-13, reac-captures m200-enrol-441k-2026-09-13 and
 * m200-enrol-s4000-441k-2026-09-13): an M-200 at 44.1 kHz (3675 fps measured)
 * enrolling an
 * S-1608 and an S-4000S emits cfea[19]=0x02 (46 announces), scene
 * `revision`=0x0002 (three
 * bodies, byte-identical), chanmap marker flags 0x02 (6 sweeps) and
 * ENROLL[8]=0x02 — the
 * same M-200 at 48 kHz writes 0x00 on every one of them, the eleven other map
 * bytes
 * identical. Both boxes paced 44.1 kHz.
 * ]
 */
#define REAC_CONSOLE_FIELD_GATES_RATE   1

/* 12 samples x 3 bytes, per channel, at EVERY sample rate. The 36 in `52 +
 * n*36`. [EVIDENCED (corpus) at 48k and 96k; RATE-INVARIANT BY CONSTRUCTION
 * (12 x 3).
 * EVIDENCED (corpus) at 44.1k since 2026-09-13: the M-200 sessions in
 * m200-enrol-441k-2026-09-13 and m200-enrol-s4000-441k-2026-09-13 measure
 * 3675 fps from the
 * pcap timestamps, with the same 52 + n*36 frame length.
 * ]
 */
#define REAC_BYTES_PER_CHANNEL          36

/* Samples per channel per frame. The RATE is the packet rate; the frame does
 * not change shape with it. [EVIDENCED (corpus).]
 */
#define REAC_SAMPLES_PER_PKT            12

/* Bytes per sample per channel — 24-bit. [EVIDENCED (corpus).] */
#define REAC_RESOLUTION                 3

/* The downstream audio fabric, 40 slots. NOT the head-amp channel space,
 * which is 48 wide; conflating the two was a real bug. [EVIDENCED (corpus).]
 */
#define REAC_MAX_CHANNELS               40

/* The fixed downstream broadcast — 52 + 40*36. [EVIDENCED (corpus).] */
#define REAC_FRAME_BYTES                1492

/* 40 ch x 12 samples x 3 B. [EVIDENCED (corpus).] */
#define REAC_AUDIO_BYTES                1440

/* First byte of the two-byte end marker. [EVIDENCED (corpus).] */
#define REAC_END_MARKER_0               0xc2

/* Second byte of the end marker. [EVIDENCED (corpus).] */
#define REAC_END_MARKER_1               0xea

#endif /* REAC_FACTS_FRAME_GEOMETRY_H */
